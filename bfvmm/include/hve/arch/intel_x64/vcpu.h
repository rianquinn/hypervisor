//
// Bareflank Hypervisor
// Copyright (C) 2018 Assured Information Security, Inc.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#ifndef VCPU_INTEL_X64_H
#define VCPU_INTEL_X64_H

#include "vmx.h"
#include "vmcs.h"

#include "delegator/cpuid.h"
#include "delegator/nmi.h"
#include "delegator/cr.h"
#include "delegator/invd.h"
#include "delegator/msr.h"
#include "delegator/unhandled_exit.h"

#include "../../../vcpu/vcpu.h"
#include "../../../memory_manager/arch/x64/cr3.h"

// -----------------------------------------------------------------------------
// Exports
// -----------------------------------------------------------------------------

#include <bfexports.h>

#ifndef STATIC_HVE
#ifdef SHARED_HVE
#define EXPORT_HVE EXPORT_SYM
#else
#define EXPORT_HVE IMPORT_SYM
#endif
#else
#define EXPORT_HVE
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

// -----------------------------------------------------------------------------
// Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64
{

/// Intel vCPU
///
/// This class provides the base implementation for an Intel based vCPU. For
/// more information on how a vCPU works, please @see bfvmm::vcpu
///
class EXPORT_HVE vcpu : public bfvmm::vcpu
{

    using handler_t = bool(gsl::not_null<bfvmm::intel_x64::vcpu *>);
    using handler_delegate_t = delegate<handler_t>;

public:

    /// Default Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param id the id of the vcpu
    ///
    vcpu(vcpuid::type id);

    /// Destructor
    ///
    /// @expects none
    /// @ensures none
    ///
    ~vcpu() override = default;

    /// Run Delegate
    ///
    /// Provides the base implementation for starting the vCPU. This delegate
    /// does not "resume" a vCPU as the base implementation does not support
    /// guest VMs.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param obj ignored
    ///
    VIRTUAL void run_delegate(bfobject *obj);

    /// Halt Delegate
    ///
    /// Provides the base implementation for stopping the vCPU.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param obj ignored
    ///
    VIRTUAL void hlt_delegate(bfobject *obj);

    /// Load vCPU
    ///
    /// Loads the vCPU into hardware.
    ///
    /// @expects none
    /// @ensures none
    ///
    VIRTUAL void load();

    /// Promote vCPU
    ///
    /// Promotes the vCPU.
    ///
    /// @expects none
    /// @ensures none
    ///
    VIRTUAL void promote();

    /// Dump State
    ///
    /// Outputs the state of the vCPU with a custom header
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param str a custom header to add to the dump output
    ///
    VIRTUAL void dump(const char *str);

    /// Halt the vCPU
    ///
    /// Halts the vCPU. The default action is to freeze the physical core
    /// resulting in a hang, but this function can be overrided to provide
    /// a safer action if possible.
    ///
    /// @param str the reason for the halt
    ///
    virtual void halt(const std::string &str = {});

    /// Advance vCPU
    ///
    /// Advances the vCPU.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return always returns true
    ///
    VIRTUAL bool advance();


    /// Initialize vCPU
    ///
    /// Initializes the vCPU.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns true if successful, false otherwise
    ///
    bool init();

    /// De-initialize vCPU
    ///
    /// De-initializes the vCPU.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns true if successful, false otherwise
    ///
    bool fini();

    /// Add exit handler
    ///
    /// Adds an exit handler to be called on every vmexit
    ///
    /// @expects none
    /// @ensures none
    ///
    void add_exit_handler(const handler_delegate_t &d)
    { this->m_all_exit_delegates.push_front(d); }

public:

    /// @cond

    /// vCPU Registers
    ///
    /// These functions read/write the register values of the vCPU. Some of
    /// these functions will touch the save state while others will read/write
    /// to the VMCS which means that the vCPU must be loaded prior to touching
    /// those registers. Care should be taken to ensure that loading the vCPU
    /// is kept at a minimum while at the same time ensuring that the right
    /// VMCS is being modified.
    ///

    VIRTUAL uint64_t rax() const noexcept;
    VIRTUAL void set_rax(uint64_t val) noexcept;
    VIRTUAL uint64_t rbx() const noexcept;
    VIRTUAL void set_rbx(uint64_t val) noexcept;
    VIRTUAL uint64_t rcx() const noexcept;
    VIRTUAL void set_rcx(uint64_t val) noexcept;
    VIRTUAL uint64_t rdx() const noexcept;
    VIRTUAL void set_rdx(uint64_t val) noexcept;
    VIRTUAL uint64_t rbp() const noexcept;
    VIRTUAL void set_rbp(uint64_t val) noexcept;
    VIRTUAL uint64_t rsi() const noexcept;
    VIRTUAL void set_rsi(uint64_t val) noexcept;
    VIRTUAL uint64_t rdi() const noexcept;
    VIRTUAL void set_rdi(uint64_t val) noexcept;
    VIRTUAL uint64_t r08() const noexcept;
    VIRTUAL void set_r08(uint64_t val) noexcept;
    VIRTUAL uint64_t r09() const noexcept;
    VIRTUAL void set_r09(uint64_t val) noexcept;
    VIRTUAL uint64_t r10() const noexcept;
    VIRTUAL void set_r10(uint64_t val) noexcept;
    VIRTUAL uint64_t r11() const noexcept;
    VIRTUAL void set_r11(uint64_t val) noexcept;
    VIRTUAL uint64_t r12() const noexcept;
    VIRTUAL void set_r12(uint64_t val) noexcept;
    VIRTUAL uint64_t r13() const noexcept;
    VIRTUAL void set_r13(uint64_t val) noexcept;
    VIRTUAL uint64_t r14() const noexcept;
    VIRTUAL void set_r14(uint64_t val) noexcept;
    VIRTUAL uint64_t r15() const noexcept;
    VIRTUAL void set_r15(uint64_t val) noexcept;
    VIRTUAL uint64_t rip() const noexcept;
    VIRTUAL void set_rip(uint64_t val) noexcept;
    VIRTUAL uint64_t rsp() const noexcept;
    VIRTUAL void set_rsp(uint64_t val) noexcept;
    VIRTUAL uint64_t gdt_base() const noexcept;
    VIRTUAL void set_gdt_base(uint64_t val) noexcept;
    VIRTUAL uint64_t gdt_limit() const noexcept;
    VIRTUAL void set_gdt_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t idt_base() const noexcept;
    VIRTUAL void set_idt_base(uint64_t val) noexcept;
    VIRTUAL uint64_t idt_limit() const noexcept;
    VIRTUAL void set_idt_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t cr0() const noexcept;
    VIRTUAL void set_cr0(uint64_t val) noexcept;
    VIRTUAL uint64_t cr3() const noexcept;
    VIRTUAL void set_cr3(uint64_t val) noexcept;
    VIRTUAL uint64_t cr4() const noexcept;
    VIRTUAL void set_cr4(uint64_t val) noexcept;
    VIRTUAL uint64_t ia32_efer() const noexcept;
    VIRTUAL void set_ia32_efer(uint64_t val) noexcept;
    VIRTUAL uint64_t ia32_pat() const noexcept;
    VIRTUAL void set_ia32_pat(uint64_t val) noexcept;

    VIRTUAL uint64_t es_selector() const noexcept;
    VIRTUAL void set_es_selector(uint64_t val) noexcept;
    VIRTUAL uint64_t es_base() const noexcept;
    VIRTUAL void set_es_base(uint64_t val) noexcept;
    VIRTUAL uint64_t es_limit() const noexcept;
    VIRTUAL void set_es_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t es_access_rights() const noexcept;
    VIRTUAL void set_es_access_rights(uint64_t val) noexcept;
    VIRTUAL uint64_t cs_selector() const noexcept;
    VIRTUAL void set_cs_selector(uint64_t val) noexcept;
    VIRTUAL uint64_t cs_base() const noexcept;
    VIRTUAL void set_cs_base(uint64_t val) noexcept;
    VIRTUAL uint64_t cs_limit() const noexcept;
    VIRTUAL void set_cs_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t cs_access_rights() const noexcept;
    VIRTUAL void set_cs_access_rights(uint64_t val) noexcept;
    VIRTUAL uint64_t ss_selector() const noexcept;
    VIRTUAL void set_ss_selector(uint64_t val) noexcept;
    VIRTUAL uint64_t ss_base() const noexcept;
    VIRTUAL void set_ss_base(uint64_t val) noexcept;
    VIRTUAL uint64_t ss_limit() const noexcept;
    VIRTUAL void set_ss_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t ss_access_rights() const noexcept;
    VIRTUAL void set_ss_access_rights(uint64_t val) noexcept;
    VIRTUAL uint64_t ds_selector() const noexcept;
    VIRTUAL void set_ds_selector(uint64_t val) noexcept;
    VIRTUAL uint64_t ds_base() const noexcept;
    VIRTUAL void set_ds_base(uint64_t val) noexcept;
    VIRTUAL uint64_t ds_limit() const noexcept;
    VIRTUAL void set_ds_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t ds_access_rights() const noexcept;
    VIRTUAL void set_ds_access_rights(uint64_t val) noexcept;
    VIRTUAL uint64_t fs_selector() const noexcept;
    VIRTUAL void set_fs_selector(uint64_t val) noexcept;
    VIRTUAL uint64_t fs_base() const noexcept;
    VIRTUAL void set_fs_base(uint64_t val) noexcept;
    VIRTUAL uint64_t fs_limit() const noexcept;
    VIRTUAL void set_fs_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t fs_access_rights() const noexcept;
    VIRTUAL void set_fs_access_rights(uint64_t val) noexcept;
    VIRTUAL uint64_t gs_selector() const noexcept;
    VIRTUAL void set_gs_selector(uint64_t val) noexcept;
    VIRTUAL uint64_t gs_base() const noexcept;
    VIRTUAL void set_gs_base(uint64_t val) noexcept;
    VIRTUAL uint64_t gs_limit() const noexcept;
    VIRTUAL void set_gs_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t gs_access_rights() const noexcept;
    VIRTUAL void set_gs_access_rights(uint64_t val) noexcept;
    VIRTUAL uint64_t tr_selector() const noexcept;
    VIRTUAL void set_tr_selector(uint64_t val) noexcept;
    VIRTUAL uint64_t tr_base() const noexcept;
    VIRTUAL void set_tr_base(uint64_t val) noexcept;
    VIRTUAL uint64_t tr_limit() const noexcept;
    VIRTUAL void set_tr_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t tr_access_rights() const noexcept;
    VIRTUAL void set_tr_access_rights(uint64_t val) noexcept;
    VIRTUAL uint64_t ldtr_selector() const noexcept;
    VIRTUAL void set_ldtr_selector(uint64_t val) noexcept;
    VIRTUAL uint64_t ldtr_base() const noexcept;
    VIRTUAL void set_ldtr_base(uint64_t val) noexcept;
    VIRTUAL uint64_t ldtr_limit() const noexcept;
    VIRTUAL void set_ldtr_limit(uint64_t val) noexcept;
    VIRTUAL uint64_t ldtr_access_rights() const noexcept;
    VIRTUAL void set_ldtr_access_rights(uint64_t val) noexcept;

    VIRTUAL gsl::not_null<save_state_t *> save_state() const;

    /// @endcond

public:

    /// @cond

    cpuid::delegator *cpuid_delegator() const
    { return m_cpuid_delegator.get(); }

    nmi::delegator *nmi_delegator() const
    { return m_nmi_delegator.get(); }

    cr::delegator *cr_delegator() const
    { return m_cr_delegator.get(); }

    invd::delegator *invd_delegator() const
    { return m_invd_delegator.get(); }

    msr::delegator *msr_delegator() const
    { return m_msr_delegator.get(); }

    unhandled_exit::delegator *unhandled_exit_delegator() const
    { return m_unhandled_exit_delegator.get(); }

    /// @endcond

private:

    bool m_launched{false};

    std::unique_ptr<vmcs> m_vmcs;
    std::unique_ptr<vmx> m_vmx;

    std::list<handler_delegate_t> m_init_delegates;
    std::list<handler_delegate_t> m_fini_delegates;
    std::array<handler_delegate_t, 128> m_exit_delegates;
    std::list<handler_delegate_t> m_all_exit_delegates;

    std::unique_ptr<cpuid::delegator> m_cpuid_delegator;
    std::unique_ptr<nmi::delegator> m_nmi_delegator;
    std::unique_ptr<cr::delegator> m_cr_delegator;
    std::unique_ptr<invd::delegator> m_invd_delegator;
    std::unique_ptr<msr::delegator> m_msr_delegator;
    std::unique_ptr<unhandled_exit::delegator> m_unhandled_exit_delegator;


private:

    void vmexit_handler() noexcept;
};

}

/// Get Guest vCPU
///
/// Gets a guest vCPU from the vCPU manager given a vcpuid
///
/// @expects
/// @ensures
///
/// @return returns a pointer to the vCPU being queried or throws
///     and exception.
///
#define get_vcpu(a) \
    g_vcm->get<bfvmm::intel_x64::vcpu *>(a, __FILE__ ": invalid vcpuid")

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
