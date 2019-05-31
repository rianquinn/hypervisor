//
// Copyright (C) 2019 Assured Information Security, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <memory>

#include <implementation/vcpu_t.h>
#include <implementation/arch/intel_x64/vmx.h>

#include <uapis/arch/intel_x64/intrinsics/crs.h>
#include <uapis/arch/intel_x64/intrinsics/msrs.h>

namespace bfvmm::implementation::intel_x64
{

// -----------------------------------------------------------------------------
// Global State
// -----------------------------------------------------------------------------

static std::unique_ptr<hpt> g_hpt{};
static std::unique_ptr<gdt> g_gdt{};
static std::unique_ptr<idt> g_idt{};
static std::unique_ptr<tss> g_tss{};

static std::unique_ptr<gsl::byte[]> m_ist;
static std::unique_ptr<gsl::byte[]> m_stack;

static ::intel_x64::cr0::value_type g_host_cr0{};
static ::intel_x64::cr3::value_type g_host_cr3{};
static ::intel_x64::cr4::value_type g_host_cr4{};
static ::intel_x64::msrs::value_type g_host_ia32_pat_msr{};
static ::intel_x64::msrs::value_type g_host_ia32_efer_msr{};

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

void
global_init()
{
    using namespace ::intel_x64;

    g_hpt = std::make_unique<hpt>();
    g_gdt = std::make_unique<gdt>(512);
    g_idt = std::make_unique<idt>(256);
    g_tss = std::make_unique<tss>();

    // g_gdt->set(1, nullptr, 0xFFFFFFFF, ring0_cs_descriptor);
    // g_gdt->set(2, nullptr, 0xFFFFFFFF, ring0_ss_descriptor);
    // g_gdt->set(3, nullptr, 0xFFFFFFFF, ring0_fs_descriptor);
    // g_gdt->set(4, nullptr, 0xFFFFFFFF, ring0_gs_descriptor);
    // g_gdt->set(5, &m_host_tss, sizeof(m_host_tss), ring0_tr_descriptor);

    for (const auto &md : g_mm->descriptors()) {
        if (md.type == (MEMORY_TYPE_R | MEMORY_TYPE_E)) {
            g_hpt->map_4k(md.virt, md.phys, hpt::attr_type::read_execute);
            continue;
        }

        g_hpt->map_4k(md.virt, md.phys, hpt::attr_type::read_write);
    }

    g_host_ia32_efer_msr |= msrs::ia32_efer::lme::mask;
    g_host_ia32_efer_msr |= msrs::ia32_efer::lma::mask;
    g_host_ia32_efer_msr |= msrs::ia32_efer::nxe::mask;

    g_host_cr0 |= cr0::protection_enable::mask;
    g_host_cr0 |= cr0::monitor_coprocessor::mask;
    g_host_cr0 |= cr0::extension_type::mask;
    g_host_cr0 |= cr0::numeric_error::mask;
    g_host_cr0 |= cr0::write_protect::mask;
    g_host_cr0 |= cr0::paging::mask;

    g_host_cr3 = g_hpt->cr3();
    g_host_ia32_pat_msr = 0x0606060606060600;

    g_host_cr4 |= cr4::v8086_mode_extensions::mask;
    g_host_cr4 |= cr4::protected_mode_virtual_interrupts::mask;
    g_host_cr4 |= cr4::time_stamp_disable::mask;
    g_host_cr4 |= cr4::debugging_extensions::mask;
    g_host_cr4 |= cr4::page_size_extensions::mask;
    g_host_cr4 |= cr4::physical_address_extensions::mask;
    g_host_cr4 |= cr4::machine_check_enable::mask;
    g_host_cr4 |= cr4::page_global_enable::mask;
    g_host_cr4 |= cr4::performance_monitor_counter_enable::mask;
    g_host_cr4 |= cr4::osfxsr::mask;
    g_host_cr4 |= cr4::osxmmexcpt::mask;
    g_host_cr4 |= cr4::vmx_enable_bit::mask;

    if (cpuid::feature_information::ecx::xsave::is_enabled()) {
        g_host_cr4 |= cr4::osxsave::mask;
    }

    if (cpuid::extended_feature_flags::subleaf0::ebx::smep::is_enabled()) {
        g_host_cr4 |= cr4::smep_enable_bit::mask;
    }

    if (cpuid::extended_feature_flags::subleaf0::ebx::smap::is_enabled()) {
        g_host_cr4 |= cr4::smap_enable_bit::mask;
    }
}

//==============================================================================
// Initial VMCS State
//==============================================================================

void
write_host_state(vcpu_t *vcpu)
{
    using namespace ::intel_x64::vmcs;
    using namespace ::x64::access_rights;

    host_cs_selector::set(1 << 3);
    host_ss_selector::set(2 << 3);
    host_fs_selector::set(3 << 3);
    host_gs_selector::set(4 << 3);
    host_tr_selector::set(5 << 3);

    host_ia32_pat::set(g_host_ia32_pat_msr);
    host_ia32_efer::set(g_host_ia32_efer_msr);

    host_cr0::set(g_host_cr0);
    host_cr3::set(g_host_cr3);
    host_cr4::set(g_host_cr4);

    host_gs_base::set(reinterpret_cast<uintptr_t>(&m_state));
    host_tr_base::set(m_host_gdt.base(5));

    host_gdtr_base::set(m_host_gdt.base());
    host_idtr_base::set(m_host_idt.base());

    m_host_tss.ist1 = setup_stack(m_ist1.get(), this->id());
    set_default_esrs(&m_host_idt, 8);

    host_rip::set(exit_handler_entry);
    host_rsp::set(setup_stack(m_stack.get(), this->id()));
}

void
vcpu::write_guest_state()
{
    using namespace ::intel_x64;
    using namespace ::intel_x64::vmcs;
    using namespace ::intel_x64::cpuid;

    using namespace ::x64::access_rights;
    using namespace ::x64::segment_register;

    x64::gdt guest_gdt;
    x64::idt guest_idt;

    auto es_index = es::index::get();
    auto cs_index = cs::index::get();
    auto ss_index = ss::index::get();
    auto ds_index = ds::index::get();
    auto fs_index = fs::index::get();
    auto gs_index = gs::index::get();
    auto ldtr_index = ldtr::index::get();
    auto tr_index = tr::index::get();

    vmcs_link_pointer::set(0xFFFFFFFFFFFFFFFF);

    guest_es_selector::set(es::get());
    guest_cs_selector::set(cs::get());
    guest_ss_selector::set(ss::get());
    guest_ds_selector::set(ds::get());
    guest_fs_selector::set(fs::get());
    guest_gs_selector::set(gs::get());
    guest_ldtr_selector::set(ldtr::get());
    guest_tr_selector::set(tr::get());

    guest_ia32_debugctl::set(msrs::ia32_debugctl::get());
    guest_ia32_pat::set(::x64::msrs::ia32_pat::get());
    guest_ia32_efer::set(msrs::ia32_efer::get());

    if (arch_perf_monitoring::eax::version_id::get() >= 2) {
        guest_ia32_perf_global_ctrl::set_if_exists(
            msrs::ia32_perf_global_ctrl::get()
        );
    }

    guest_gdtr_limit::set(guest_gdt.limit());
    guest_idtr_limit::set(guest_idt.limit());

    guest_gdtr_base::set(guest_gdt.base());
    guest_idtr_base::set(guest_idt.base());

    guest_es_limit::set(es_index != 0 ? guest_gdt.limit(es_index) : 0);
    guest_cs_limit::set(cs_index != 0 ? guest_gdt.limit(cs_index) : 0);
    guest_ss_limit::set(ss_index != 0 ? guest_gdt.limit(ss_index) : 0);
    guest_ds_limit::set(ds_index != 0 ? guest_gdt.limit(ds_index) : 0);
    guest_fs_limit::set(fs_index != 0 ? guest_gdt.limit(fs_index) : 0);
    guest_gs_limit::set(gs_index != 0 ? guest_gdt.limit(gs_index) : 0);
    guest_ldtr_limit::set(ldtr_index != 0 ? guest_gdt.limit(ldtr_index) : 0);
    guest_tr_limit::set(tr_index != 0 ? guest_gdt.limit(tr_index) : 0);

    guest_es_access_rights::set(es_index != 0 ? guest_gdt.access_rights(es_index) : unusable);
    guest_cs_access_rights::set(cs_index != 0 ? guest_gdt.access_rights(cs_index) : unusable);
    guest_ss_access_rights::set(ss_index != 0 ? guest_gdt.access_rights(ss_index) : unusable);
    guest_ds_access_rights::set(ds_index != 0 ? guest_gdt.access_rights(ds_index) : unusable);
    guest_fs_access_rights::set(fs_index != 0 ? guest_gdt.access_rights(fs_index) : unusable);
    guest_gs_access_rights::set(gs_index != 0 ? guest_gdt.access_rights(gs_index) : unusable);
    guest_ldtr_access_rights::set(ldtr_index != 0 ? guest_gdt.access_rights(ldtr_index) : unusable);
    guest_tr_access_rights::set(tr_index != 0 ? guest_gdt.access_rights(tr_index) : type::tss_busy | 0x80U);

    guest_es_base::set(es_index != 0 ? guest_gdt.base(es_index) : 0);
    guest_cs_base::set(cs_index != 0 ? guest_gdt.base(cs_index) : 0);
    guest_ss_base::set(ss_index != 0 ? guest_gdt.base(ss_index) : 0);
    guest_ds_base::set(ds_index != 0 ? guest_gdt.base(ds_index) : 0);
    guest_fs_base::set(msrs::ia32_fs_base::get());
    guest_gs_base::set(msrs::ia32_gs_base::get());
    guest_ldtr_base::set(ldtr_index != 0 ? guest_gdt.base(ldtr_index) : 0);
    guest_tr_base::set(tr_index != 0 ? guest_gdt.base(tr_index) : 0);

    this->set_cr0(cr0::get());
    guest_cr3::set(cr3::get());
    this->set_cr4(cr4::get());
    guest_dr7::set(dr7::get());

    guest_rflags::set(::x64::rflags::get());

    guest_ia32_sysenter_cs::set(msrs::ia32_sysenter_cs::get());
    guest_ia32_sysenter_esp::set(msrs::ia32_sysenter_esp::get());
    guest_ia32_sysenter_eip::set(msrs::ia32_sysenter_eip::get());
}

void
vcpu::write_control_state()
{
    using namespace ::intel_x64::vmcs;

    auto ia32_vmx_pinbased_ctls_msr =
        ::intel_x64::msrs::ia32_vmx_true_pinbased_ctls::get();
    auto ia32_vmx_procbased_ctls_msr =
        ::intel_x64::msrs::ia32_vmx_true_procbased_ctls::get();
    auto ia32_vmx_exit_ctls_msr =
        ::intel_x64::msrs::ia32_vmx_true_exit_ctls::get();
    auto ia32_vmx_entry_ctls_msr =
        ::intel_x64::msrs::ia32_vmx_true_entry_ctls::get();

    pin_based_vm_execution_controls::set(
        ((ia32_vmx_pinbased_ctls_msr >> 0) & 0x00000000FFFFFFFF) &
        ((ia32_vmx_pinbased_ctls_msr >> 32) & 0x00000000FFFFFFFF)
    );

    primary_processor_based_vm_execution_controls::set(
        ((ia32_vmx_procbased_ctls_msr >> 0) & 0x00000000FFFFFFFF) &
        ((ia32_vmx_procbased_ctls_msr >> 32) & 0x00000000FFFFFFFF)
    );

    vm_exit_controls::set(
        ((ia32_vmx_exit_ctls_msr >> 0) & 0x00000000FFFFFFFF) &
        ((ia32_vmx_exit_ctls_msr >> 32) & 0x00000000FFFFFFFF)
    );

    vm_entry_controls::set(
        ((ia32_vmx_entry_ctls_msr >> 0) & 0x00000000FFFFFFFF) &
        ((ia32_vmx_entry_ctls_msr >> 32) & 0x00000000FFFFFFFF)
    );

    using namespace pin_based_vm_execution_controls;
    using namespace primary_processor_based_vm_execution_controls;
    using namespace secondary_processor_based_vm_execution_controls;

    address_of_msr_bitmap::set(g_mm->virtptr_to_physint(m_msr_bitmap.get()));
    address_of_io_bitmap_a::set(g_mm->virtptr_to_physint(m_io_bitmap_a.get()));
    address_of_io_bitmap_b::set(g_mm->virtptr_to_physint(m_io_bitmap_b.get()));

    use_msr_bitmap::enable();
    use_io_bitmaps::enable();

    activate_secondary_controls::enable_if_allowed();

    if (this->is_host_vm_vcpu()) {
        enable_rdtscp::enable_if_allowed();
        enable_invpcid::enable_if_allowed();
        enable_xsaves_xrstors::enable_if_allowed();
    }

    vm_exit_controls::save_debug_controls::enable();
    vm_exit_controls::host_address_space_size::enable();
    vm_exit_controls::load_ia32_perf_global_ctrl::enable_if_allowed();
    vm_exit_controls::save_ia32_pat::enable();
    vm_exit_controls::load_ia32_pat::enable();
    vm_exit_controls::save_ia32_efer::enable();
    vm_exit_controls::load_ia32_efer::enable();

    vm_entry_controls::load_debug_controls::enable();
    vm_entry_controls::ia_32e_mode_guest::enable();
    vm_entry_controls::load_ia32_perf_global_ctrl::enable_if_allowed();
    vm_entry_controls::load_ia32_pat::enable();
    vm_entry_controls::load_ia32_efer::enable();
}

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::implementation::intel_x64
{

setup::setup()
{
    bfn::call_once(g_once_flag, setup);

    this->load();

    ::write_host_state();
    ::write_control_state();

    if (this->is_host_vm_vcpu()) {
        ::write_guest_state();
    }
}


    vmcs_link_pointer::set(0xFFFFFFFFFFFFFFFF);
    vcpu_t_cast(this)->set_host_gs_base(m_state.hva());



//==============================================================================
// Fault Handling
//==============================================================================

void
vcpu::dump(const char *str)
{
    using namespace ::intel_x64::vmcs;

    bfdebug_transaction(0, [&](std::string * msg) {

        bferror_lnbr(0, msg);
        bferror_info(0, str, msg);
        bferror_brk1(0, msg);

        bferror_lnbr(0, msg);
        bferror_info(0, "general purpose registers", msg);
        bferror_subnhex(0, "rax", this->rax(), msg);
        bferror_subnhex(0, "rbx", this->rbx(), msg);
        bferror_subnhex(0, "rcx", this->rcx(), msg);
        bferror_subnhex(0, "rdx", this->rdx(), msg);
        bferror_subnhex(0, "rbp", this->rbp(), msg);
        bferror_subnhex(0, "rsi", this->rsi(), msg);
        bferror_subnhex(0, "rdi", this->rdi(), msg);
        bferror_subnhex(0, "r08", this->r08(), msg);
        bferror_subnhex(0, "r09", this->r09(), msg);
        bferror_subnhex(0, "r10", this->r10(), msg);
        bferror_subnhex(0, "r11", this->r11(), msg);
        bferror_subnhex(0, "r12", this->r12(), msg);
        bferror_subnhex(0, "r13", this->r13(), msg);
        bferror_subnhex(0, "r14", this->r14(), msg);
        bferror_subnhex(0, "r15", this->r15(), msg);
        bferror_subnhex(0, "rip", this->rip(), msg);
        bferror_subnhex(0, "rsp", this->rsp(), msg);
        bferror_subnhex(0, "gr1", this->gr1(), msg);
        bferror_subnhex(0, "gr2", this->gr2(), msg);
        bferror_subnhex(0, "gr3", this->gr3(), msg);
        bferror_subnhex(0, "gr4", this->gr4(), msg);

        bferror_lnbr(0, msg);
        bferror_info(0, "control registers", msg);
        bferror_subnhex(0, "cr0", guest_cr0::get(), msg);
        bferror_subnhex(0, "cr2", ::intel_x64::cr2::get(), msg);
        bferror_subnhex(0, "cr3", guest_cr3::get(), msg);
        bferror_subnhex(0, "cr4", guest_cr4::get(), msg);

        bferror_lnbr(0, msg);
        bferror_info(0, "addressing", msg);
        bferror_subnhex(0, "linear address", guest_linear_address::get(), msg);
        bferror_subnhex(0, "physical address", guest_physical_address::get(), msg);

        bferror_lnbr(0, msg);
        bferror_info(0, "exit info", msg);
        bferror_subnhex(0, "reason", exit_reason::get(), msg);
        bferror_subtext(0, "description", exit_reason::basic_exit_reason::description(), msg);
        bferror_subnhex(0, "qualification", exit_qualification::get(), msg);
    });

    if (exit_reason::vm_entry_failure::is_enabled()) {
        m_vmcs.check();
    }
}

void
vcpu::halt(const std::string &str)
{
    this->dump(("halting vcpu: " + str).c_str());
    ::x64::pm::stop();
}


