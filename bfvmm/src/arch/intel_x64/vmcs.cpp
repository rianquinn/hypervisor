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

#include <bfgsl.h>
#include <bfdebug.h>
#include <bfconstants.h>
#include <bfthreadcontext.h>

#include <hve/arch/intel_x64/vmcs.h>
#include <hve/arch/intel_x64/check.h>
#include <hve/arch/intel_x64/vcpu.h>

// -----------------------------------------------------------------------------
// Prototypes
// -----------------------------------------------------------------------------

extern "C" bool vmcs_launch(
    bfvmm::intel_x64::vcpu_state_t *vcpu_state) noexcept;

extern "C" bool vmcs_resume(
    bfvmm::intel_x64::vcpu_state_t *vcpu_state) noexcept;

extern "C" bool vmcs_promote(
    bfvmm::intel_x64::vcpu_state_t *vcpu_state) noexcept;

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64
{


void
vmcs::launch()
{
    try {
        if (vcpu_t_cast(this)->is_host_vcpu()) {
            ::intel_x64::vm::launch_demote();
        }
        else {
            vmcs_launch(vcpu_t_cast(this)->state().get());
            throw std::runtime_error("vmcs launch failed");
        }
    }
    catch (...) {
        auto e = std::current_exception();

        this->check();
        std::rethrow_exception(e);
    }
}





void
vmcs::launch()
{
    try {
        for (const auto &d : *m_vmlaunch_delegates) {
            d(this);
        }

        if (!vmcs_launch(vcpu_t_cast(this)->state())) {
            throw std::runtime_error("launch failed");
        }

    }
    catch (...) {
        this->check();
        throw;
    }
}

void
vmcs::resume()
{

}






void
vcpu::run()
{
    try {


            try {
                m_launched = true;
                vmcs_launch(vcpu_t_cast(this)->state());
            }
            catch (...) {
                m_launched = false;
            }
        }
    }
    catch (...) {
        this->check();
        throw;
    }
}


void
vcpu::load()
{ m_vmcs.load(); }

void
vcpu::clear()
{
    for (const auto &d : m_clear_delegates) {
        d(this);
    }

    m_vmcs.clear();
    m_launched = false;
}

void
vcpu::promote()
{  }

bool
vcpu::advance()
{
    using namespace ::intel_x64::vmcs;

    this->set_rip(this->rip() + vm_exit_instruction_length::get());
    return true;
}















vmcs::vmcs()
{
    using namespace ::intel_x64::msrs::ia32_vmx_basic;

    this->clear();
    this->load();

    auto view = m_vmcs_region.view();
    view[0] = gsl::narrow<uint32_t>(revision_id::get());
}

void
vcpu::demote()
{
    this->run();
    ::x64::cpuid::get(0x4BF00010, 0, 0, 0);
    ::x64::cpuid::get(0x4BF00011, 0, 0, 0);
}

void
vcpu::promote()
{
    ::x64::cpuid::get(0x4BF00020, 0, 0, 0);
    ::x64::cpuid::get(0x4BF00021, 0, 0, 0);

    if (!vmcs_promote(vcpu_t_cast(this)->state())) {
        throw std::runtime_error("promote failed");
    }
}


PRIVATE:
    void __arch_run();
    bool __arch_advance();
    void __arch_load();
    void __arch_clear();
    bool __arch_check() const noexcept;

PRIVATE:
    void __vmcs_add_vmlaunch_delegate(const vmcs_delegate_t &d);
    void __vmcs_add_vmresume_delegate(const vmcs_delegate_t &d);
    void __vmcs_add_vmload_delegate(const vmcs_delegate_t &d);
    void __vmcs_add_vmclear_delegate(const vmcs_delegate_t &d);

PRIVATE:
    vmcs_field16_t __vpid() const;
    void __set_vpid(vmcs_field16_t val);

    vmcs_field16_t __posted_interrupt_notification_vector() const;
    void __set_posted_interrupt_notification_vector(vmcs_field16_t val);

    vmcs_field16_t __es_selector() const;
    void __set_es_selector(vmcs_field16_t val);

    vmcs_field16_t __cs_selector() const;
    void __set_cs_selector(vmcs_field16_t val);

    vmcs_field16_t __ss_selector() const;
    void __set_ss_selector(vmcs_field16_t val);

    vmcs_field16_t __ds_selector() const;
    void __set_ds_selector(vmcs_field16_t val);

    vmcs_field16_t __fs_selector() const;
    void __set_fs_selector(vmcs_field16_t val);

    vmcs_field16_t __gs_selector() const;
    void __set_gs_selector(vmcs_field16_t val);

    vmcs_field16_t __ldtr_selector() const;
    void __set_ldtr_selector(vmcs_field16_t val);

    vmcs_field16_t __tr_selector() const;
    void __set_tr_selector(vmcs_field16_t val);

    vmcs_field16_t __interrupt_status() const;
    void __set_interrupt_status(vmcs_field16_t val);

    vmcs_field16_t __pml_index() const;
    void __set_pml_index(vmcs_field16_t val);

    vmcs_field64_t __io_bitmap_a_addr() const;
    void __set_io_bitmap_a_addr(vmcs_field64_t val);

    vmcs_field64_t __io_bitmap_b_addr() const;
    void __set_io_bitmap_b_addr(vmcs_field64_t val);

    vmcs_field64_t __msr_bitmaps_addr() const;
    void __set_msr_bitmaps_addr(vmcs_field64_t val);

    vmcs_field64_t __vmexit_msr_store_addr() const;
    void __set_vmexit_msr_store_addr(vmcs_field64_t val);

    vmcs_field64_t __vmexit_msr_load_addr() const;
    void __set_vmexit_msr_load_addr(vmcs_field64_t val);

    vmcs_field64_t __pml_addr() const;
    void __set_pml_addr(vmcs_field64_t val);

    vmcs_field64_t __tsc_offset() const;
    void __set_tsc_offset(vmcs_field64_t val);

    vmcs_field64_t __vapic_addr() const;
    void __set_vapic_addr(vmcs_field64_t val);

    vmcs_field64_t __apic_access_addr() const;
    void __set_apic_access_addr(vmcs_field64_t val);

    vmcs_field64_t __posted_interrupt_descriptor_addr() const;
    void __set_posted_interrupt_descriptor_addr(vmcs_field64_t val);

    vmcs_field64_t __vm_function_ctls() const;
    void __set_vm_function_ctls(vmcs_field64_t val);

    vmcs_field64_t __eptp() const;
    void __set_eptp(vmcs_field64_t val);

    vmcs_field64_t __eoi_exit_bitmap_0() const;
    void __set_eoi_exit_bitmap_0(vmcs_field64_t val);

    vmcs_field64_t __eoi_exit_bitmap_1() const;
    void __set_eoi_exit_bitmap_1(vmcs_field64_t val);

    vmcs_field64_t __eoi_exit_bitmap_2() const;
    void __set_eoi_exit_bitmap_2(vmcs_field64_t val);

    vmcs_field64_t __eoi_exit_bitmap_3() const;
    void __set_eoi_exit_bitmap_3(vmcs_field64_t val);

    vmcs_field64_t __eptp_list_addr() const;
    void __set_eptp_list_addr(vmcs_field64_t val);

    vmcs_field64_t __vexception_info_addr() const;
    void __set_vexception_info_addr(vmcs_field64_t val);

    vmcs_field64_t __xss_exiting_bitmap() const;
    void __set_xss_exiting_bitmap(vmcs_field64_t val);

    vmcs_field64_t __tsc_multiplier() const;
    void __set_tsc_multiplier(vmcs_field64_t val);

    vmcs_field64_t __gpa() const;

    vmcs_field64_t __ia32_debugctl() const;
    void __set_ia32_debugctl(vmcs_field64_t val);

    vmcs_field64_t __ia32_pat() const;
    void __set_ia32_pat(vmcs_field64_t val);

    vmcs_field64_t __ia32_efer() const;
    void __set_ia32_efer(vmcs_field64_t val);

    vmcs_field64_t __ia32_perf_global_ctrl() const;
    void __set_ia32_perf_global_ctrl(vmcs_field64_t val);

    vmcs_field64_t __pdpte0() const;
    void __set_pdpte0(vmcs_field64_t val);

    vmcs_field64_t __pdpte1() const;
    void __set_pdpte1(vmcs_field64_t val);

    vmcs_field64_t __pdpte2() const;
    void __set_pdpte2(vmcs_field64_t val);

    vmcs_field64_t __pdpte3() const;
    void __set_pdpte3(vmcs_field64_t val);

    vmcs_field32_t __pin_based_ctls() const;
    void __set_pin_based_ctls(vmcs_field32_t val);

    vmcs_field32_t __proc_based_ctls() const;
    void __set_proc_based_ctls(vmcs_field32_t val);

    vmcs_field32_t __exception_bitmap() const;
    void __set_exception_bitmap(vmcs_field32_t val);

    vmcs_field32_t __pf_error_code_mask() const;
    void __set_pf_error_code_mask(vmcs_field32_t val);

    vmcs_field32_t __pf_error_code_match() const;
    void __set_pf_error_code_match(vmcs_field32_t val);

    vmcs_field32_t __cr3_target_count() const;
    void __set_cr3_target_count(vmcs_field32_t val);

    vmcs_field32_t __vmexit_ctls() const;
    void __set_vmexit_ctls(vmcs_field32_t val);

    vmcs_field32_t __vmexit_msr_store_count() const;
    void __set_vmexit_msr_store_count(vmcs_field32_t val);

    vmcs_field32_t __vmexit_load_count() const;
    void __set_vmexit_load_count(vmcs_field32_t val);

    vmcs_field32_t __vmentry_ctls() const;
    void __set_vmentry_ctls(vmcs_field32_t val);

    vmcs_field32_t __vmentry_msr_load_count() const;
    void __set_vmentry_msr_load_count(vmcs_field32_t val);

    vmcs_field32_t __vmentry_int_info() const;
    void __set_vmentry_int_info(vmcs_field32_t val);

    vmcs_field32_t __vmentry_exception_error_code() const;
    void __set_vmentry_exception_error_code(vmcs_field32_t val);

    vmcs_field32_t __vmentry_instr_len() const;
    void __set_vmentry_instr_len(vmcs_field32_t val);

    vmcs_field32_t __tpr_threshold() const;
    void __set_tpr_threshold(vmcs_field32_t val);

    vmcs_field32_t __proc_based_ctls2() const;
    void __set_proc_based_ctls2(vmcs_field32_t val);

    vmcs_field32_t __ple_gap() const;
    void __set_ple_gap(vmcs_field32_t val);

    vmcs_field32_t __ple_window() const;
    void __set_ple_window(vmcs_field32_t val);

    vmcs_field32_t __vm_instr_error() const;
    vmcs_field32_t __vmexit_int_info() const;

    vmcs_field32_t __es_limit() const;
    void __set_es_limit(vmcs_field32_t val);

    vmcs_field32_t __cs_limit() const;
    void __set_cs_limit(vmcs_field32_t val);

    vmcs_field32_t __ss_limit() const;
    void __set_ss_limit(vmcs_field32_t val);

    vmcs_field32_t __ds_limit() const;
    void __set_ds_limit(vmcs_field32_t val);

    vmcs_field32_t __fs_limit() const;
    void __set_fs_limit(vmcs_field32_t val);

    vmcs_field32_t __gs_limit() const;
    void __set_gs_limit(vmcs_field32_t val);

    vmcs_field32_t __ldtr_limit() const;
    void __set_ldtr_limit(vmcs_field32_t val);

    vmcs_field32_t __tr_limit() const;
    void __set_tr_limit(vmcs_field32_t val);

    vmcs_field32_t __gdtr_limit() const;
    void __set_gdtr_limit(vmcs_field32_t val);

    vmcs_field32_t __idtr_limit() const;
    void __set_idtr_limit(vmcs_field32_t val);

    vmcs_field32_t __es_access_rights() const;
    void __set_es_access_rights(vmcs_field32_t val);

    vmcs_field32_t __cs_access_rights() const;
    void __set_cs_access_rights(vmcs_field32_t val);

    vmcs_field32_t __ss_access_rights() const;
    void __set_ss_access_rights(vmcs_field32_t val);

    vmcs_field32_t __ds_access_rights() const;
    void __set_ds_access_rights(vmcs_field32_t val);

    vmcs_field32_t __fs_access_rights() const;
    void __set_fs_access_rights(vmcs_field32_t val);

    vmcs_field32_t __gs_access_rights() const;
    void __set_gs_access_rights(vmcs_field32_t val);

    vmcs_field32_t __ldtr_access_rights() const;
    void __set_ldtr_access_rights(vmcs_field32_t val);

    vmcs_field32_t __tr_access_rights() const;
    void __set_tr_access_rights(vmcs_field32_t val);

    vmcs_field32_t __interuptability_state() const;
    void __set_interuptability_state(vmcs_field32_t val);

    vmcs_field32_t __activity_state() const;
    void __set_activity_state(vmcs_field32_t val);

    vmcs_field32_t __ia32_sysenter_cs() const;
    void __set_ia32_sysenter_cs(vmcs_field32_t val);

    vmcs_field32_t __preemption_timer_value() const;
    void __set_preemption_timer_value(vmcs_field32_t val);

    vmcs_field64_t __cr0_mask() const;
    void __set_cr0_mask(vmcs_field64_t val);

    vmcs_field64_t __cr4_mask() const;
    void __set_cr4_mask(vmcs_field64_t val);

    vmcs_field64_t __cr0_read_shadow() const;
    void __set_cr0_read_shadow(vmcs_field64_t val);

    vmcs_field64_t __cr4_read_shadow() const;
    void __set_cr4_read_shadow(vmcs_field64_t val);

    vmcs_field64_t __cr3_target0() const;
    void __set_cr3_target0(vmcs_field64_t val);

    vmcs_field64_t __cr3_target1() const;
    void __set_cr3_target1(vmcs_field64_t val);

    vmcs_field64_t __cr3_target2() const;
    void __set_cr3_target2(vmcs_field64_t val);

    vmcs_field64_t __cr3_target3() const;
    void __set_cr3_target3(vmcs_field64_t val);

    vmcs_field64_t __exit_qualification() const;
    vmcs_field64_t __io_rcx() const;

    vmcs_field64_t __cr3() const;
    void __set_cr3(vmcs_field64_t val);

    vmcs_field64_t __cr4() const;
    void __set_cr4(vmcs_field64_t val);

    vmcs_field64_t __es_base() const;
    void __set_es_base(vmcs_field64_t val);

    vmcs_field64_t __cs_base() const;
    void __set_cs_base(vmcs_field64_t val);

    vmcs_field64_t __ss_base() const;
    void __set_ss_base(vmcs_field64_t val);

    vmcs_field64_t __ds_base() const;
    void __set_ds_base(vmcs_field64_t val);

    vmcs_field64_t __fs_base() const;
    void __set_fs_base(vmcs_field64_t val);

    vmcs_field64_t __gs_base() const;
    void __set_gs_base(vmcs_field64_t val);

    vmcs_field64_t __ldtr_base() const;
    void __set_ldtr_base(vmcs_field64_t val);

    vmcs_field64_t __tr_base() const;
    void __set_tr_base(vmcs_field64_t val);

    vmcs_field64_t __gdtr_base() const;
    void __set_gdtr_base(vmcs_field64_t val);

    vmcs_field64_t __idtr_base() const;
    void __set_idtr_base(vmcs_field64_t val);

    vmcs_field64_t __dr7() const;
    void __set_dr7(vmcs_field64_t val);

    vmcs_field64_t __rflags() const;
    void __set_rflags(vmcs_field64_t val);

    vmcs_field64_t __pending_debug_exceptions() const;
    void __set_pending_debug_exceptions(vmcs_field64_t val);

    vmcs_field64_t __ia32_sysenter_esp() const;
    void __set_ia32_sysenter_esp(vmcs_field64_t val);

    vmcs_field64_t __ia32_sysenter_eip() const;
    void __set_ia32_sysenter_eip(vmcs_field64_t val);

PRIVATE
    vmcs_field16_t host_es_selector() const;
    void set_host_es_selector(vmcs_field16_t val);

    vmcs_field16_t host_cs_selector() const;
    void set_host_cs_selector(vmcs_field16_t val);

    vmcs_field16_t host_ss_selector() const;
    void set_host_ss_selector(vmcs_field16_t val);

    vmcs_field16_t host_ds_selector() const;
    void set_host_ds_selector(vmcs_field16_t val);

    vmcs_field16_t host_fs_selector() const;
    void set_host_fs_selector(vmcs_field16_t val);

    vmcs_field16_t host_gs_selector() const;
    void set_host_gs_selector(vmcs_field16_t val);

    vmcs_field16_t host_tr_selector() const;
    void set_host_tr_selector(vmcs_field16_t val);

    vmcs_field64_t host_ia32_pat() const;
    void set_host_ia32_pat(vmcs_field64_t val);

    vmcs_field64_t host_ia32_efer() const;
    void set_host_ia32_efer(vmcs_field64_t val);

    vmcs_field64_t host_ia32_perf_global_ctrl() const;
    void set_host_ia32_perf_global_ctrl(vmcs_field64_t val);

    vmcs_field64_t host_ia32_sysenter_cs() const;
    void set_host_ia32_sysenter_cs(vmcs_field64_t val);

    vmcs_field64_t host_cr0() const;
    void set_host_cr0(vmcs_field64_t val);

    vmcs_field64_t host_cr3() const;
    void set_host_cr3(vmcs_field64_t val);

    vmcs_field64_t host_cr4() const;
    void set_host_cr4(vmcs_field64_t val);

    vmcs_field64_t host_fs_base() const;
    void set_host_fs_base(vmcs_field64_t val);

    vmcs_field64_t host_gs_base() const;
    void set_host_gs_base(vmcs_field64_t val);

    vmcs_field64_t host_tr_base() const;
    void set_host_tr_base(vmcs_field64_t val);

    vmcs_field64_t host_gdtr_base() const;
    void set_host_gdtr_base(vmcs_field64_t val);

    vmcs_field64_t host_idtr_base() const;
    void set_host_idtr_base(vmcs_field64_t val);

    vmcs_field64_t host_ia32_sysenter_esp() const;
    void set_host_ia32_sysenter_esp(vmcs_field64_t val);

    vmcs_field64_t host_ia32_sysenter_eip() const;
    void set_host_ia32_sysenter_eip(vmcs_field64_t val);

    vmcs_field64_t host_rsp() const;
    void set_host_rsp(vmcs_field64_t val);

    vmcs_field64_t host_rip() const;
    void set_host_rip(vmcs_field64_t val);





































uint64_t
vcpu::gdt_base() const noexcept
{ return vmcs_n::guest_gdtr_base::get(); }

void
vcpu::set_gdt_base(uint64_t val) noexcept
{ vmcs_n::guest_gdtr_base::set(val); }

uint64_t
vcpu::gdt_limit() const noexcept
{ return vmcs_n::guest_gdtr_limit::get(); }

void
vcpu::set_gdt_limit(uint64_t val) noexcept
{ vmcs_n::guest_gdtr_limit::set(val); }

uint64_t
vcpu::idt_base() const noexcept
{ return vmcs_n::guest_idtr_base::get(); }

void
vcpu::set_idt_base(uint64_t val) noexcept
{ vmcs_n::guest_idtr_base::set(val); }

uint64_t
vcpu::idt_limit() const noexcept
{ return vmcs_n::guest_idtr_limit::get(); }

void
vcpu::set_idt_limit(uint64_t val) noexcept
{ vmcs_n::guest_idtr_limit::set(val); }

uint64_t
vcpu::cr0() const noexcept
{ return vmcs_n::cr0_read_shadow::get(); }

void
vcpu::set_cr0(uint64_t val) noexcept
{
    vmcs_n::cr0_read_shadow::set(val);

    ::intel_x64::cr0::extension_type::enable(val);
    ::intel_x64::cr0::not_write_through::disable(val);
    ::intel_x64::cr0::cache_disable::disable(val);

    vmcs_n::guest_cr0::set(val | m_global_state->ia32_vmx_cr0_fixed0);
}

uint64_t
vcpu::cr3() const noexcept
{ return vmcs_n::guest_cr3::get(); }

void
vcpu::set_cr3(uint64_t val) noexcept
{
    vmcs_n::guest_cr3::set(val & 0x7FFFFFFFFFFFFFFF);
}

uint64_t
vcpu::cr4() const noexcept
{ return vmcs_n::cr4_read_shadow::get(); }

void
vcpu::set_cr4(uint64_t val) noexcept
{
    vmcs_n::cr4_read_shadow::set(val);
    vmcs_n::guest_cr4::set(val | m_global_state->ia32_vmx_cr4_fixed0);
}

uint64_t
vcpu::ia32_efer() const noexcept
{ return vmcs_n::guest_ia32_efer::get(); }

void
vcpu::set_ia32_efer(uint64_t val) noexcept
{ vmcs_n::guest_ia32_efer::set(val); }

uint64_t
vcpu::ia32_pat() const noexcept
{ return vmcs_n::guest_ia32_pat::get(); }

void
vcpu::set_ia32_pat(uint64_t val) noexcept
{ vmcs_n::guest_ia32_pat::set(val); }


uint64_t
vcpu::es_selector() const noexcept
{ return vmcs_n::guest_es_selector::get(); }

void
vcpu::set_es_selector(uint64_t val) noexcept
{ vmcs_n::guest_es_selector::set(val); }

uint64_t
vcpu::es_base() const noexcept
{ return vmcs_n::guest_es_base::get(); }

void
vcpu::set_es_base(uint64_t val) noexcept
{ vmcs_n::guest_es_base::set(val); }

uint64_t
vcpu::es_limit() const noexcept
{ return vmcs_n::guest_es_limit::get(); }

void
vcpu::set_es_limit(uint64_t val) noexcept
{ vmcs_n::guest_es_limit::set(val); }

uint64_t
vcpu::es_access_rights() const noexcept
{ return vmcs_n::guest_es_access_rights::get(); }

void
vcpu::set_es_access_rights(uint64_t val) noexcept
{ vmcs_n::guest_es_access_rights::set(val); }

uint64_t
vcpu::cs_selector() const noexcept
{ return vmcs_n::guest_cs_selector::get(); }

void
vcpu::set_cs_selector(uint64_t val) noexcept
{ vmcs_n::guest_cs_selector::set(val); }

uint64_t
vcpu::cs_base() const noexcept
{ return vmcs_n::guest_cs_base::get(); }

void
vcpu::set_cs_base(uint64_t val) noexcept
{ vmcs_n::guest_cs_base::set(val); }

uint64_t
vcpu::cs_limit() const noexcept
{ return vmcs_n::guest_cs_limit::get(); }

void
vcpu::set_cs_limit(uint64_t val) noexcept
{ vmcs_n::guest_cs_limit::set(val); }

uint64_t
vcpu::cs_access_rights() const noexcept
{ return vmcs_n::guest_cs_access_rights::get(); }

void
vcpu::set_cs_access_rights(uint64_t val) noexcept
{ vmcs_n::guest_cs_access_rights::set(val); }

uint64_t
vcpu::ss_selector() const noexcept
{ return vmcs_n::guest_ss_selector::get(); }

void
vcpu::set_ss_selector(uint64_t val) noexcept
{ vmcs_n::guest_ss_selector::set(val); }

uint64_t
vcpu::ss_base() const noexcept
{ return vmcs_n::guest_ss_base::get(); }

void
vcpu::set_ss_base(uint64_t val) noexcept
{ vmcs_n::guest_ss_base::set(val); }

uint64_t
vcpu::ss_limit() const noexcept
{ return vmcs_n::guest_ss_limit::get(); }

void
vcpu::set_ss_limit(uint64_t val) noexcept
{ vmcs_n::guest_ss_limit::set(val); }

uint64_t
vcpu::ss_access_rights() const noexcept
{ return vmcs_n::guest_ss_access_rights::get(); }

void
vcpu::set_ss_access_rights(uint64_t val) noexcept
{ vmcs_n::guest_ss_access_rights::set(val); }

uint64_t
vcpu::ds_selector() const noexcept
{ return vmcs_n::guest_ds_selector::get(); }

void
vcpu::set_ds_selector(uint64_t val) noexcept
{ vmcs_n::guest_ds_selector::set(val); }

uint64_t
vcpu::ds_base() const noexcept
{ return vmcs_n::guest_ds_base::get(); }

void
vcpu::set_ds_base(uint64_t val) noexcept
{ vmcs_n::guest_ds_base::set(val); }

uint64_t
vcpu::ds_limit() const noexcept
{ return vmcs_n::guest_ds_limit::get(); }

void
vcpu::set_ds_limit(uint64_t val) noexcept
{ vmcs_n::guest_ds_limit::set(val); }

uint64_t
vcpu::ds_access_rights() const noexcept
{ return vmcs_n::guest_ds_access_rights::get(); }

void
vcpu::set_ds_access_rights(uint64_t val) noexcept
{ vmcs_n::guest_ds_access_rights::set(val); }

uint64_t
vcpu::fs_selector() const noexcept
{ return vmcs_n::guest_fs_selector::get(); }

void
vcpu::set_fs_selector(uint64_t val) noexcept
{ vmcs_n::guest_fs_selector::set(val); }

uint64_t
vcpu::fs_base() const noexcept
{ return vmcs_n::guest_fs_base::get(); }

void
vcpu::set_fs_base(uint64_t val) noexcept
{ vmcs_n::guest_fs_base::set(val); }

uint64_t
vcpu::fs_limit() const noexcept
{ return vmcs_n::guest_fs_limit::get(); }

void
vcpu::set_fs_limit(uint64_t val) noexcept
{ vmcs_n::guest_fs_limit::set(val); }

uint64_t
vcpu::fs_access_rights() const noexcept
{ return vmcs_n::guest_fs_access_rights::get(); }

void
vcpu::set_fs_access_rights(uint64_t val) noexcept
{ vmcs_n::guest_fs_access_rights::set(val); }

uint64_t
vcpu::gs_selector() const noexcept
{ return vmcs_n::guest_gs_selector::get(); }

void
vcpu::set_gs_selector(uint64_t val) noexcept
{ vmcs_n::guest_gs_selector::set(val); }

uint64_t
vcpu::gs_base() const noexcept
{ return vmcs_n::guest_gs_base::get(); }

void
vcpu::set_gs_base(uint64_t val) noexcept
{ vmcs_n::guest_gs_base::set(val); }

uint64_t
vcpu::gs_limit() const noexcept
{ return vmcs_n::guest_gs_limit::get(); }

void
vcpu::set_gs_limit(uint64_t val) noexcept
{ vmcs_n::guest_gs_limit::set(val); }

uint64_t
vcpu::gs_access_rights() const noexcept
{ return vmcs_n::guest_gs_access_rights::get(); }

void
vcpu::set_gs_access_rights(uint64_t val) noexcept
{ vmcs_n::guest_gs_access_rights::set(val); }

uint64_t
vcpu::tr_selector() const noexcept
{ return vmcs_n::guest_tr_selector::get(); }

void
vcpu::set_tr_selector(uint64_t val) noexcept
{ vmcs_n::guest_tr_selector::set(val); }

uint64_t
vcpu::tr_base() const noexcept
{ return vmcs_n::guest_tr_base::get(); }

void
vcpu::set_tr_base(uint64_t val) noexcept
{ vmcs_n::guest_tr_base::set(val); }

uint64_t
vcpu::tr_limit() const noexcept
{ return vmcs_n::guest_tr_limit::get(); }

void
vcpu::set_tr_limit(uint64_t val) noexcept
{ vmcs_n::guest_tr_limit::set(val); }

uint64_t
vcpu::tr_access_rights() const noexcept
{ return vmcs_n::guest_tr_access_rights::get(); }

void
vcpu::set_tr_access_rights(uint64_t val) noexcept
{ vmcs_n::guest_tr_access_rights::set(val); }

uint64_t
vcpu::ldtr_selector() const noexcept
{ return vmcs_n::guest_ldtr_selector::get(); }

void
vcpu::set_ldtr_selector(uint64_t val) noexcept
{ vmcs_n::guest_ldtr_selector::set(val); }

uint64_t
vcpu::ldtr_base() const noexcept
{ return vmcs_n::guest_ldtr_base::get(); }

void
vcpu::set_ldtr_base(uint64_t val) noexcept
{ vmcs_n::guest_ldtr_base::set(val); }

uint64_t
vcpu::ldtr_limit() const noexcept
{ return vmcs_n::guest_ldtr_limit::get(); }

void
vcpu::set_ldtr_limit(uint64_t val) noexcept
{ vmcs_n::guest_ldtr_limit::set(val); }

uint64_t
vcpu::ldtr_access_rights() const noexcept
{ return vmcs_n::guest_ldtr_access_rights::get(); }

void
vcpu::set_ldtr_access_rights(uint64_t val) noexcept
{ vmcs_n::guest_ldtr_access_rights::set(val); }

void
vmcs::load()
{ ::intel_x64::vm::load(&m_vmcs_region_phys); }

void
vmcs::clear()
{ ::intel_x64::vm::clear(&m_vmcs_region_phys); }

bool
vmcs::check() const noexcept
{
    try {
        check::all();
    }
    catch (std::exception &e) {
        bfdebug_transaction(0, [&](std::string * msg) {
            bferror_lnbr(0, msg);
            bferror_brk1(0, msg);
            bferror_info(0, typeid(e).name(), msg);
            bferror_brk1(0, msg);
            bferror_info(0, e.what(), msg);
        });

        return false;
    }

    return true;
}

}
