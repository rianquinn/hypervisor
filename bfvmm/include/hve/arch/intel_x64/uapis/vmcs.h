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

#ifndef UAPIS_VMCS_INTEL_X64_H
#define UAPIS_VMCS_INTEL_X64_H

#include "../private.h"

// -----------------------------------------------------------------------------
// Types/Namespaces
// -----------------------------------------------------------------------------

// *INDENT-OFF*

namespace bfvmm::intel_x64::vmcs
{
    /// VMCS Field Type (16bit)
    ///
    /// This defines the vmcs field type that is used in this interface
    ///
    using vmcs_field16_t = uint16_t;

    /// VMCS Field Type (32bit)
    ///
    /// This defines the vmcs field type that is used in this interface
    ///
    using vmcs_field32_t = uint32_t;

    /// VMCS Field Type (64bit)
    ///
    /// This defines the vmcs field type that is used in this interface
    ///
    using vmcs_field64_t = uint64_t;
}

/// VMCS Namespace
///
namespace vmcs_n = bfvmm::intel_x64::vmcs;

// *INDENT-ON*

// -----------------------------------------------------------------------------
// Interface Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64::uapis
{

/// VMCS
///
/// Defines the VMCS interfaces provided by the vCPU.
///
template<typename IMPL>
class vmcs
{
public:

    /// Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu the vCPU that is associated with this interface
    ///
    explicit vmcs(gsl::not_null<vcpu *> vcpu) :
        m_impl{vcpu}
    { }

public:

    /// Run
    ///
    /// Executes the vCPU. On Intel, this will either execute a VMLaunch or a
    /// VMResume, depending on the state of the VMCS. The first time this is
    /// executed, a VMLaunch will be executed, all times after that, a VMResume
    /// will be executed. If you need a VMLaunch to execute again, for example
    /// when coming out of S3 or migrating the vCPU to a different pCPU, you
    /// can run the clear() function which will execute a VMClear on the VMCS
    /// ultimately resulting in a VMLaunch executing again the next time this
    /// function is executed.
    ///
    /// Also note that you can register delegates with the different VMCS
    /// instructions that could be executed by this interface including on a
    /// VMLaunch, VMResume, VMCLear, VMLoad and a promotion. Simply ensure that
    /// you register with the proper instruction, and you ensure the code
    /// executes as quickly as possible as some of these instructions like a
    /// VMResume and VMLoad execute a lot.
    ///
    /// @expects none
    /// @ensures none
    ///
    ///
    ///
    inline void run()
    { m_impl.run(); }

    /// Advance vCPU
    ///
    /// This function will advance the vCPU's instruction pointer to the next
    /// instruction. Note that this function only makes sense for VMExits that
    /// handle instruction execution. VMExits that handle things like interrupts
    /// should not use this function.
    ///
    /// Also note that this function always returns true. Most extensions will
    /// not need to execute this function manually, and instead the base will
    /// execute this for you. If you do need to execute this manually, it
    /// should be paired, in most cases, with a "return" indicating that the
    /// handler is done, and no other handlers should execute. In most cases,
    /// extensions will return false in a VMExit handler indicating that the
    /// base should complete the exit.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return always returns true
    ///
    inline bool advance()
    { return m_impl.advance(); }

    /// Load
    ///
    /// This function performs a VMLoad. A VMLoad is am expensive operation, so
    /// this should be used only when needed. When debugging is enabled, the
    /// setters/getters will perform a VMRead to ensure the VMCS has been loaded
    /// and will output a warning if this is not the case. In release mode, this
    /// code is removed to ensure the hypervisor executes as fast as possible.
    ///
    /// To put it another way, we do not execute a VMLoad every time a VMCS
    /// operation is executed. Instead, we only run a VMLoad when as know that
    /// a different vCPU is currently loaded. This ensures that we do not add
    /// additional overhead to the system. The downside of this is the user has
    /// to track when a vCPU is loaded or not, which can either be done in
    /// design, or it can be done by maintaining your own internal state as an
    /// extension, either way, it is up to the author of the extension to pick
    /// how much overhead they want to introduce so that they can manage the
    /// stability/performance tradoffs. This is why the setters/getters double
    /// check in debug mode. While debugging, the system will help to sort out
    /// any issues with your design if you choose to side with performance.
    ///
    /// @expects none
    /// @ensures none
    ///
    inline void load()
    { return m_impl.load(); }


    /// VMCS Clear
    ///
    /// This function executes a VMClear. This does _not_ 0 out the VMCS or any
    /// of the vCPU's state. All this does is mark the VMCS so that the next
    /// time a vcpu->run() is executed, a VMLaunch is executed instead of a
    /// VMResume.
    ///
    /// @expects none
    /// @ensures none
    ///
    inline void vmcs_clear()
    { return m_impl.vmcs_clear(); }

    /// VMCS Check
    ///
    /// This function checks to see if the VMCS is configured improperly. The
    /// Intel SDM has a whole chapter (v3, chatper 26) that describes all of the
    /// conditions in which a VMEntry might fail. This function can be used to
    /// check the state of the VMCS to see if/why a VMEntry will/did fail.
    /// Also note that if a VMEntry fails, an exception is thrown so this
    /// function must be labled as noexcept to ensure that the checks do not
    /// throw in additional the to VMEntry exception.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns true if the VMCS is configured properly, false
    ///     otherwise
    ///
    inline bool vmcs_check() const noexcept
    { return m_impl.vmcs_check(); }

public:

    /// Add VMLaunch Delegate
    ///
    /// Adds a VMLaunch delegate to the vCPU. A VMLaunch delegate is executed
    /// just prior to when the VMLaunch instruction is executed and provides
    /// extensions with a means to extend the functionality provided by the
    /// base for the VMLaunch instruction
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param d the delegate to add to the vcpu
    ///
    inline void vmcs_add_vmlaunch_delegate(const vmcs_delegate_t &d)
    { m_impl.vmcs_add_vmlaunch_delegate(d); }

    /// Add VMResume Delegate
    ///
    /// Adds a VMResume delegate to the vCPU. A VMResume delegate is executed
    /// just prior to when the VMResume instruction is executed and provides
    /// extensions with a means to extend the functionality provided by the
    /// base for the VMResume instruction.
    ///
    /// WARNING:
    ///
    /// The VMResume instruction is executed a lot. You should only add a
    /// VMResume delegate if you absolutely have to and if you do, it needs to
    /// execute as fast as possible as it will add overhead to every single
    /// VMEntry that occurs.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param d the delegate to add to the vcpu
    ///
    inline void vmcs_add_vmresume_delegate(const vmcs_delegate_t &d)
    { m_impl.vmcs_add_vmresume_delegate(d); }

    /// Add VMLoad Delegate
    ///
    /// Adds a VMLoad delegate to the vCPU. A VMLoad delegate is executed
    /// just prior to when the VMLoad instruction is executed and provides
    /// extensions with a means to extend the functionality provided by the
    /// base for the VMLoad instruction
    ///
    /// WARNING:
    ///
    /// The VMLoad instruction is executed a lot. You should only add a
    /// VMLoad delegate if you absolutely have to and if you do, it needs to
    /// execute as fast as possible as it will add overhead to every single
    /// VMEntry that occurs.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param d the delegate to add to the vcpu
    ///
    inline void vmcs_add_vmload_delegate(const vmcs_delegate_t &d)
    { m_impl.vmcs_add_vmload_delegate(d); }

    /// Add VMClear Delegate
    ///
    /// Adds a VMClear delegate to the vCPU. A VMClear delegate is executed
    /// just prior to when the VMClear instruction is executed and provides
    /// extensions with a means to extend the functionality provided by the
    /// base for the VMClear instruction
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param d the delegate to add to the vcpu
    ///
    inline void vmcs_add_vmclear_delegate(const vmcs_delegate_t &d)
    { m_impl.vmcs_add_vmclear_delegate(d); }

public:

    inline vmcs_field16_t vpid() const;
    inline void set_vpid(vmcs_field16_t val);

    inline vmcs_field16_t posted_interrupt_notification_vector() const;
    inline void set_posted_interrupt_notification_vector(vmcs_field16_t val);

    inline vmcs_field16_t es_selector() const;
    inline void set_es_selector(vmcs_field16_t val);

    inline vmcs_field16_t cs_selector() const;
    inline void set_cs_selector(vmcs_field16_t val);

    inline vmcs_field16_t ss_selector() const;
    inline void set_ss_selector(vmcs_field16_t val);

    inline vmcs_field16_t ds_selector() const;
    inline void set_ds_selector(vmcs_field16_t val);

    inline vmcs_field16_t fs_selector() const;
    inline void set_fs_selector(vmcs_field16_t val);

    inline vmcs_field16_t gs_selector() const;
    inline void set_gs_selector(vmcs_field16_t val);

    inline vmcs_field16_t ldtr_selector() const;
    inline void set_ldtr_selector(vmcs_field16_t val);

    inline vmcs_field16_t tr_selector() const;
    inline void set_tr_selector(vmcs_field16_t val);

    inline vmcs_field16_t interrupt_status() const;
    inline void set_interrupt_status(vmcs_field16_t val);

    inline vmcs_field16_t pml_index() const;
    inline void set_pml_index(vmcs_field16_t val);

public:

    // Missing Fields
    //
    // - Executive-VMCS Pointer: Needed for STM
    // - VMREAD-bitmap address: Needed for Nested Virtualization
    // - VMWRITE-bitmap address: Needed for Nested Virtualization
    // - ENCLS-exiting bitmap: Needed for SGX Emulation
    //

    inline vmcs_field64_t io_bitmap_a_addr() const;
    inline void set_io_bitmap_a_addr(vmcs_field64_t val);

    inline vmcs_field64_t io_bitmap_b_addr() const;
    inline void set_io_bitmap_b_addr(vmcs_field64_t val);

    inline vmcs_field64_t msr_bitmaps_addr() const;
    inline void set_msr_bitmaps_addr(vmcs_field64_t val);

    inline vmcs_field64_t vmexit_msr_store_addr() const;
    inline void set_vmexit_msr_store_addr(vmcs_field64_t val);

    inline vmcs_field64_t vmexit_msr_load_addr() const;
    inline void set_vmexit_msr_load_addr(vmcs_field64_t val);

    inline vmcs_field64_t pml_addr() const;
    inline void set_pml_addr(vmcs_field64_t val);

    inline vmcs_field64_t tsc_offset() const;
    inline void set_tsc_offset(vmcs_field64_t val);

    inline vmcs_field64_t vapic_addr() const;
    inline void set_vapic_addr(vmcs_field64_t val);

    inline vmcs_field64_t apic_access_addr() const;
    inline void set_apic_access_addr(vmcs_field64_t val);

    inline vmcs_field64_t posted_interrupt_descriptor_addr() const;
    inline void set_posted_interrupt_descriptor_addr(vmcs_field64_t val);

    inline vmcs_field64_t vm_function_ctls() const;
    inline void set_vm_function_ctls(vmcs_field64_t val);

    inline vmcs_field64_t eptp() const;
    inline void set_eptp(vmcs_field64_t val);

    inline vmcs_field64_t eoi_exit_bitmap_0() const;
    inline void set_eoi_exit_bitmap_0(vmcs_field64_t val);

    inline vmcs_field64_t eoi_exit_bitmap_1() const;
    inline void set_eoi_exit_bitmap_1(vmcs_field64_t val);

    inline vmcs_field64_t eoi_exit_bitmap_2() const;
    inline void set_eoi_exit_bitmap_2(vmcs_field64_t val);

    inline vmcs_field64_t eoi_exit_bitmap_3() const;
    inline void set_eoi_exit_bitmap_3(vmcs_field64_t val);

    inline vmcs_field64_t eptp_list_addr() const;
    inline void set_eptp_list_addr(vmcs_field64_t val);

    inline vmcs_field64_t vexception_info_addr() const;
    inline void set_vexception_info_addr(vmcs_field64_t val);

    inline vmcs_field64_t xss_exiting_bitmap() const;
    inline void set_xss_exiting_bitmap(vmcs_field64_t val);

    inline vmcs_field64_t tsc_multiplier() const;
    inline void set_tsc_multiplier(vmcs_field64_t val);

public:

    inline vmcs_field64_t gpa() const;

public:

    // Missing Fields
    //
    // - VMCS-link pointer: Needed for Nested Virtualization
    // - Guest IA32_BNDCFGS: Needed for MPX Emulation
    //

    inline vmcs_field64_t ia32_debugctl() const;
    inline void set_ia32_debugctl(vmcs_field64_t val);

    inline vmcs_field64_t ia32_pat() const;
    inline void set_ia32_pat(vmcs_field64_t val);

    inline vmcs_field64_t ia32_efer() const;
    inline void set_ia32_efer(vmcs_field64_t val);

    inline vmcs_field64_t ia32_perf_global_ctrl() const;
    inline void set_ia32_perf_global_ctrl(vmcs_field64_t val);

    inline vmcs_field64_t pdpte0() const;
    inline void set_pdpte0(vmcs_field64_t val);

    inline vmcs_field64_t pdpte1() const;
    inline void set_pdpte1(vmcs_field64_t val);

    inline vmcs_field64_t pdpte2() const;
    inline void set_pdpte2(vmcs_field64_t val);

    inline vmcs_field64_t pdpte3() const;
    inline void set_pdpte3(vmcs_field64_t val);

public:

    inline vmcs_field32_t pin_based_ctls() const;
    inline void set_pin_based_ctls(vmcs_field32_t val);

    inline vmcs_field32_t proc_based_ctls() const;
    inline void set_proc_based_ctls(vmcs_field32_t val);

    inline vmcs_field32_t exception_bitmap() const;
    inline void set_exception_bitmap(vmcs_field32_t val);

    inline vmcs_field32_t pf_error_code_mask() const;
    inline void set_pf_error_code_mask(vmcs_field32_t val);

    inline vmcs_field32_t pf_error_code_match() const;
    inline void set_pf_error_code_match(vmcs_field32_t val);

    inline vmcs_field32_t cr3_target_count() const;
    inline void set_cr3_target_count(vmcs_field32_t val);

    inline vmcs_field32_t vmexit_ctls() const;
    inline void set_vmexit_ctls(vmcs_field32_t val);

    inline vmcs_field32_t vmexit_msr_store_count() const;
    inline void set_vmexit_msr_store_count(vmcs_field32_t val);

    inline vmcs_field32_t vmexit_load_count() const;
    inline void set_vmexit_load_count(vmcs_field32_t val);

    inline vmcs_field32_t vmentry_ctls() const;
    inline void set_vmentry_ctls(vmcs_field32_t val);

    inline vmcs_field32_t vmentry_msr_load_count() const;
    inline void set_vmentry_msr_load_count(vmcs_field32_t val);

    inline vmcs_field32_t vmentry_int_info() const;
    inline void set_vmentry_int_info(vmcs_field32_t val);

    inline vmcs_field32_t vmentry_exception_error_code() const;
    inline void set_vmentry_exception_error_code(vmcs_field32_t val);

    inline vmcs_field32_t vmentry_instr_len() const;
    inline void set_vmentry_instr_len(vmcs_field32_t val);

    inline vmcs_field32_t tpr_threshold() const;
    inline void set_tpr_threshold(vmcs_field32_t val);

    inline vmcs_field32_t proc_based_ctls2() const;
    inline void set_proc_based_ctls2(vmcs_field32_t val);

    inline vmcs_field32_t ple_gap() const;
    inline void set_ple_gap(vmcs_field32_t val);

    inline vmcs_field32_t ple_window() const;
    inline void set_ple_window(vmcs_field32_t val);

public:

    inline vmcs_field32_t vm_instr_error() const;
    inline vmcs_field32_t vmexit_int_info() const;
    inline vmcs_field32_t vmexit_int_error_code() const;
    inline vmcs_field32_t idt_vectoring_info() const;
    inline vmcs_field32_t idt_vectoring_error_code() const;
    inline vmcs_field32_t vmexit_instr_len() const;
    inline vmcs_field32_t vmexit_instr_info() const;

public:

    // Missing Fields
    //
    // - Guest SMBASE: Needed for STM
    //

    inline vmcs_field32_t es_limit() const;
    inline void set_es_limit(vmcs_field32_t val);

    inline vmcs_field32_t cs_limit() const;
    inline void set_cs_limit(vmcs_field32_t val);

    inline vmcs_field32_t ss_limit() const;
    inline void set_ss_limit(vmcs_field32_t val);

    inline vmcs_field32_t ds_limit() const;
    inline void set_ds_limit(vmcs_field32_t val);

    inline vmcs_field32_t fs_limit() const;
    inline void set_fs_limit(vmcs_field32_t val);

    inline vmcs_field32_t gs_limit() const;
    inline void set_gs_limit(vmcs_field32_t val);

    inline vmcs_field32_t ldtr_limit() const;
    inline void set_ldtr_limit(vmcs_field32_t val);

    inline vmcs_field32_t tr_limit() const;
    inline void set_tr_limit(vmcs_field32_t val);

    inline vmcs_field32_t gdtr_limit() const;
    inline void set_gdtr_limit(vmcs_field32_t val);

    inline vmcs_field32_t idtr_limit() const;
    inline void set_idtr_limit(vmcs_field32_t val);

    inline vmcs_field32_t es_access_rights() const;
    inline void set_es_access_rights(vmcs_field32_t val);

    inline vmcs_field32_t cs_access_rights() const;
    inline void set_cs_access_rights(vmcs_field32_t val);

    inline vmcs_field32_t ss_access_rights() const;
    inline void set_ss_access_rights(vmcs_field32_t val);

    inline vmcs_field32_t ds_access_rights() const;
    inline void set_ds_access_rights(vmcs_field32_t val);

    inline vmcs_field32_t fs_access_rights() const;
    inline void set_fs_access_rights(vmcs_field32_t val);

    inline vmcs_field32_t gs_access_rights() const;
    inline void set_gs_access_rights(vmcs_field32_t val);

    inline vmcs_field32_t ldtr_access_rights() const;
    inline void set_ldtr_access_rights(vmcs_field32_t val);

    inline vmcs_field32_t tr_access_rights() const;
    inline void set_tr_access_rights(vmcs_field32_t val);

    inline vmcs_field32_t interuptability_state() const;
    inline void set_interuptability_state(vmcs_field32_t val);

    inline vmcs_field32_t activity_state() const;
    inline void set_activity_state(vmcs_field32_t val);

    inline vmcs_field32_t ia32_sysenter_cs() const;
    inline void set_ia32_sysenter_cs(vmcs_field32_t val);

    inline vmcs_field32_t preemption_timer_value() const;
    inline void set_preemption_timer_value(vmcs_field32_t val);

public:

    inline vmcs_field64_t cr0_mask() const;
    inline void set_cr0_mask(vmcs_field64_t val);

    inline vmcs_field64_t cr4_mask() const;
    inline void set_cr4_mask(vmcs_field64_t val);

    inline vmcs_field64_t cr0_read_shadow() const;
    inline void set_cr0_read_shadow(vmcs_field64_t val);

    inline vmcs_field64_t cr4_read_shadow() const;
    inline void set_cr4_read_shadow(vmcs_field64_t val);

    inline vmcs_field64_t cr3_target0() const;
    inline void set_cr3_target0(vmcs_field64_t val);

    inline vmcs_field64_t cr3_target1() const;
    inline void set_cr3_target1(vmcs_field64_t val);

    inline vmcs_field64_t cr3_target2() const;
    inline void set_cr3_target2(vmcs_field64_t val);

    inline vmcs_field64_t cr3_target3() const;
    inline void set_cr3_target3(vmcs_field64_t val);

public:

    inline vmcs_field64_t exit_qualification() const;
    inline vmcs_field64_t io_rcx() const;
    inline vmcs_field64_t io_rsi() const;
    inline vmcs_field64_t io_rdi() const;
    inline vmcs_field64_t io_rip() const;
    inline vmcs_field64_t gva() const;

public:

    inline vmcs_field64_t cr0() const;
    inline void set_cr0(vmcs_field64_t val);

    inline vmcs_field64_t cr3() const;
    inline void set_cr3(vmcs_field64_t val);

    inline vmcs_field64_t cr4() const;
    inline void set_cr4(vmcs_field64_t val);

    inline vmcs_field64_t es_base() const;
    inline void set_es_base(vmcs_field64_t val);

    inline vmcs_field64_t cs_base() const;
    inline void set_cs_base(vmcs_field64_t val);

    inline vmcs_field64_t ss_base() const;
    inline void set_ss_base(vmcs_field64_t val);

    inline vmcs_field64_t ds_base() const;
    inline void set_ds_base(vmcs_field64_t val);

    inline vmcs_field64_t fs_base() const;
    inline void set_fs_base(vmcs_field64_t val);

    inline vmcs_field64_t gs_base() const;
    inline void set_gs_base(vmcs_field64_t val);

    inline vmcs_field64_t ldtr_base() const;
    inline void set_ldtr_base(vmcs_field64_t val);

    inline vmcs_field64_t tr_base() const;
    inline void set_tr_base(vmcs_field64_t val);

    inline vmcs_field64_t gdtr_base() const;
    inline void set_gdtr_base(vmcs_field64_t val);

    inline vmcs_field64_t idtr_base() const;
    inline void set_idtr_base(vmcs_field64_t val);

    inline vmcs_field64_t dr7() const;
    inline void set_dr7(vmcs_field64_t val);

    inline vmcs_field64_t rflags() const;
    inline void set_rflags(vmcs_field64_t val);

    inline vmcs_field64_t pending_debug_exceptions() const;
    inline void set_pending_debug_exceptions(vmcs_field64_t val);

    inline vmcs_field64_t ia32_sysenter_esp() const;
    inline void set_ia32_sysenter_esp(vmcs_field64_t val);

    inline vmcs_field64_t ia32_sysenter_eip() const;
    inline void set_ia32_sysenter_eip(vmcs_field64_t val);

private:

    /// Private
    ///
    /// The following APIs are private and should not be used by an end user.
    /// These are made public for internal use only, and these APIs are subject
    /// to change. You have been warned.
    ///
    /// @cond
    ///

    inline void promote();
    { return m_impl.promote(); }

    inline vmcs_field16_t host_es_selector() const;
    inline void set_host_es_selector(vmcs_field16_t val);

    inline vmcs_field16_t host_cs_selector() const;
    inline void set_host_cs_selector(vmcs_field16_t val);

    inline vmcs_field16_t host_ss_selector() const;
    inline void set_host_ss_selector(vmcs_field16_t val);

    inline vmcs_field16_t host_ds_selector() const;
    inline void set_host_ds_selector(vmcs_field16_t val);

    inline vmcs_field16_t host_fs_selector() const;
    inline void set_host_fs_selector(vmcs_field16_t val);

    inline vmcs_field16_t host_gs_selector() const;
    inline void set_host_gs_selector(vmcs_field16_t val);

    inline vmcs_field16_t host_tr_selector() const;
    inline void set_host_tr_selector(vmcs_field16_t val);

    inline vmcs_field64_t host_ia32_pat() const;
    inline void set_host_ia32_pat(vmcs_field64_t val);

    inline vmcs_field64_t host_ia32_efer() const;
    inline void set_host_ia32_efer(vmcs_field64_t val);

    inline vmcs_field64_t host_ia32_perf_global_ctrl() const;
    inline void set_host_ia32_perf_global_ctrl(vmcs_field64_t val);

    inline vmcs_field64_t host_ia32_sysenter_cs() const;
    inline void set_host_ia32_sysenter_cs(vmcs_field64_t val);

    inline vmcs_field64_t host_cr0() const;
    inline void set_host_cr0(vmcs_field64_t val);

    inline vmcs_field64_t host_cr3() const;
    inline void set_host_cr3(vmcs_field64_t val);

    inline vmcs_field64_t host_cr4() const;
    inline void set_host_cr4(vmcs_field64_t val);

    inline vmcs_field64_t host_fs_base() const;
    inline void set_host_fs_base(vmcs_field64_t val);

    inline vmcs_field64_t host_gs_base() const;
    inline void set_host_gs_base(vmcs_field64_t val);

    inline vmcs_field64_t host_tr_base() const;
    inline void set_host_tr_base(vmcs_field64_t val);

    inline vmcs_field64_t host_gdtr_base() const;
    inline void set_host_gdtr_base(vmcs_field64_t val);

    inline vmcs_field64_t host_idtr_base() const;
    inline void set_host_idtr_base(vmcs_field64_t val);

    inline vmcs_field64_t host_ia32_sysenter_esp() const;
    inline void set_host_ia32_sysenter_esp(vmcs_field64_t val);

    inline vmcs_field64_t host_ia32_sysenter_eip() const;
    inline void set_host_ia32_sysenter_eip(vmcs_field64_t val);

    inline vmcs_field64_t host_rsp() const;
    inline void set_host_rsp(vmcs_field64_t val);

    inline vmcs_field64_t host_rip() const;
    inline void set_host_rip(vmcs_field64_t val);

    /// @endcond

private:

    page_ptr<uint32_t> m_vmcs_region{};
    uintptr_t m_vmcs_region_phys{};

    bool m_launched{false};

    std::list<vmcs_delegate_t> m_vmlaunch_delegates{};
    std::list<vmcs_delegate_t> m_vmresume_delegates{};
    std::list<vmcs_delegate_t> m_vmload_delegates{};
    std::list<vmcs_delegate_t> m_vmclear_delegates{};

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
