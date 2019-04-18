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

#include <intrinsics.h>

// -----------------------------------------------------------------------------
// Prototypes
// -----------------------------------------------------------------------------

extern "C" void vmcs_launch(
    bfvmm::intel_x64::vcpu_state_t *vcpu_state) noexcept;

extern "C" void vmcs_promote(
    bfvmm::intel_x64::vcpu_state_t *vcpu_state) noexcept;

extern "C" void vmcs_resume(
    bfvmm::intel_x64::vcpu_state_t *vcpu_state) noexcept;

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64
{

vmcs::vmcs(
    gsl::not_null<vcpu *> vcpu
) :
    m_vcpu{vcpu},
    m_vmcs_region{make_page<uint32_t>()},
    m_vmcs_region_phys{g_mm->virtptr_to_physint(m_vmcs_region.get())}
{
    this->clear();
    this->load();

    gsl::span<uint32_t> id{m_vmcs_region.get(), 1024};
    id[0] = gsl::narrow<uint32_t>(::intel_x64::msrs::ia32_vmx_basic::revision_id::get());

    vmcs_link_pointer::set(0xFFFFFFFFFFFFFFFF);
}

void
vmcs::launch()
{
    try {
        if (m_vcpu->is_host_vcpu()) {
            ::intel_x64::vm::launch_demote();
        }
        else {
            vmcs_launch(m_vcpu->state().get());
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
vmcs::promote()
{
    vmcs_promote(m_vcpu->state());
    throw std::runtime_error("vmcs promote failed");
}

void
vmcs::resume()
{
    vmcs_resume(m_vcpu->state());

    this->check();
    throw std::runtime_error("vmcs resume failed");
}


void
vcpu::run()
{
    if (m_launched) {

        for (const auto &d : m_resume_delegates) {
            d(this);
        }

        m_vmcs.resume();
    }
    else {

        try {

            for (const auto &d : m_launch_delegates) {
                d(this);
            }

            m_launched = true;
            m_vmcs.launch();
        }
        catch (...) {
            m_launched = false;
            throw;
        }
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
{ m_vmcs.promote(); }

bool
vcpu::advance()
{
    using namespace ::intel_x64::vmcs;

    this->set_rip(this->rip() + vm_exit_instruction_length::get());
    return true;
}

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
