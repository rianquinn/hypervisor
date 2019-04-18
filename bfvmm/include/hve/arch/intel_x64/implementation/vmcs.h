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

#ifndef VMCS_INTEL_X64_H
#define VMCS_INTEL_X64_H

#include "../../../memory_manager/memory_manager.h"

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64
{

class vcpu;

/// Intel x86_64 VMCS
///
/// The following provides the basic VMCS implementation as defined by the
/// Intel Software Developer's Manual (chapters 24-33). To best understand
/// this code, the manual should first be read.
///
/// This class provides the bare minimum to get a virtual machine to execute.
/// It assumes a 64bit VMM, and a 64bit guest. It does not trap on anything
/// by default, and thus the guest is allowed to execute unfettered. If
/// an error should occur, it contains the logic needed to help identify the
/// issue, including a complete implementation of chapter 26 in the Intel
/// manual, that describes all of the checks the CPU will perform prior to
/// a VM launch. We also provide a considerable amount of pre-defined
/// constants for working with the VMCS fields. Please see the VMCS headers
/// for more details. Pro tip: auto-complete works great with the VMCS
/// namespace logic.
///
class vmcs
{
public:

    /// Default Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu The vCPU associated with this VMCS
    ///
    vmcs(gsl::not_null<vcpu *> vcpu);

    /// Destructor
    ///
    /// @expects none
    /// @ensures none
    ///
    VIRTUAL ~vmcs() = default;

    /// Run
    ///
    /// Executes the vCPU. This is executed before a launch/resume. This means
    /// that this is executed in the context of the kernel if this is a host
    /// vCPU and in the context of the parent vCPU if this is a guest vCPU.
    ///
    /// In addition, this is also executed as a means to resume back into the
    /// guest after an exit, so this can also be run from the vCPU's own point
    /// of view if an exit has occurred and you are simply resuming.
    ///
    /// @expects none
    /// @ensures none
    ///
    VIRTUAL void run();

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


    /// Load
    ///
    /// The main purpose of this function is to execute VMPTRLD. Specifically,
    /// this function loads the VMCS that this class contains into the CPU.
    /// There are two different times that this is mainly needed. When the
    /// VMCS is first created, a VM launch is needed to get this VMCS up and
    /// running. Before the launch can occur, the VMCS needs to be loaded so
    /// that vm reads / writes are successful (as the CPU needs to know which
    /// VMCS to read / write to). Once a launch has been done, the VMCS
    /// contains the VM's state. The next time it needs to be run, a VMRESUME
    /// must be executed. Once gain, the CPU needs to know which VMCS to use,
    /// and thus a load is needed.
    ///
    /// @expects none
    /// @ensures none
    ///
    VIRTUAL void load();

    /// Relaunch
    ///
    /// This function clears the VMCS. This is needed for two main reasons:
    /// - During a VMCS migration, the way to do this is to clear the VMCS
    ///   and then do a VMLanuch again.
    /// - During initialization, we need to clear the VMCS just in case the
    ///   VMCS is given the same physical address twice, which does actually
    ///   happen.
    ///
    /// @expects none
    /// @ensures none
    ///
    VIRTUAL void relaunch();

    /// Check
    ///
    /// This function checks to see if the VMCS is configured improperly.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns true if the VMCS is configured properly, false
    ///     otherwise
    ///
    VIRTUAL bool check() const noexcept;

    /// Add Launch Delegate
    ///
    /// Adds a launch delegate to the VCPU. The delegates are added to a queue and
    /// executed in FILO order. All delegates are executed unless an exception
    /// is thrown that is not handled.
    ///
    /// Note that this is executed during a vcpu->run() if the vCPU is being
    /// launched and not resumed.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param d the delegate to add to the vcpu
    ///
    VIRTUAL void add_launch_delegate(const vcpu_delegate_t &d) noexcept
    { m_launch_delegates.push_front(std::move(d)); }

    /// Add Resume Delegate
    ///
    /// Adds a resume delegate to the VCPU. The delegates are added to a queue and
    /// executed in FILO order. All delegates are executed unless an exception
    /// is thrown that is not handled.
    ///
    /// Note that this is executed during a vcpu->run() if the vCPU is being
    /// resumed and not launched.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param d the delegate to add to the vcpu
    ///
    VIRTUAL void add_resume_delegate(const vcpu_delegate_t &d) noexcept
    { m_resume_delegates.push_front(std::move(d)); }

    /// Add Clear Delegate
    ///
    /// Adds a clear delegate to the VCPU. The delegates are added to a queue and
    /// executed in FILO order. All delegates are executed unless an exception
    /// is thrown that is not handled.
    ///
    /// Note that this is executed during a vcpu->clear().
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param d the delegate to add to the vcpu
    ///
    VIRTUAL void add_clear_delegate(const vcpu_delegate_t &d) noexcept
    { m_resume_delegates.push_front(std::move(d)); }

    VIRTUAL void promote();

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

private:

    page_ptr<uint32_t> m_vmcs_region;
    uintptr_t m_vmcs_region_phys;

    bool m_launched{false};

    std::list<vcpu_delegate_t> m_launch_delegates{};
    std::list<vcpu_delegate_t> m_resume_delegates{};
    std::list<vcpu_delegate_t> m_clear_delegates{};

public:

    /// @cond

    vmcs(vmcs &&) noexcept = default;
    vmcs &operator=(vmcs &&) noexcept = default;

    vmcs(const vmcs &) = delete;
    vmcs &operator=(const vmcs &) = delete;

    /// @endcond
};

}

using vmcs_t = bfvmm::intel_x64::vmcs;

#endif
