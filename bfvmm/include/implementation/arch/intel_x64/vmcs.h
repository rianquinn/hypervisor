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
    /// VMCS Delegate Type
    ///
    /// This defines the function prototype for vmcs operations. This provides an
    /// extension with the ability to extend most the VMCS operations that take
    /// place within the vCPU
    ///
    using vmcs_delegate_t = delegate<void(vcpu_t *)>;

public:

    /// Default Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu The vCPU associated with this VMCS
    ///
    explicit vmcs(gsl::not_null<vcpu *> vcpu);

    /// Destructor
    ///
    /// @expects none
    /// @ensures none
    ///
    VIRTUAL ~vmcs() = default;

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

public:

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
    { return m_impl.vpid(); }

    inline void set_vpid(vmcs_field16_t val);
    { m_impl.set_vpid(val); }

    inline vmcs_field16_t posted_interrupt_notification_vector() const;
    { return m_impl.posted_interrupt_notification_vector(); }

    inline void set_posted_interrupt_notification_vector(vmcs_field16_t val);
    { m_impl.set_posted_interrupt_notification_vector(val); }

    inline vmcs_field16_t es_selector() const;
    { return m_impl.es_selector(); }

    inline void set_es_selector(vmcs_field16_t val);
    { m_impl.set_es_selector(val); }

    inline vmcs_field16_t cs_selector() const;
    { return m_impl.cs_selector(); }

    inline void set_cs_selector(vmcs_field16_t val);
    { m_impl.set_cs_selector(val); }

    inline vmcs_field16_t ss_selector() const;
    { return m_impl.ss_selector(); }

    inline void set_ss_selector(vmcs_field16_t val);
    { m_impl.set_ss_selector(val); }

    inline vmcs_field16_t ds_selector() const;
    { return m_impl.ds_selector(); }

    inline void set_ds_selector(vmcs_field16_t val);
    { m_impl.set_ds_selector(val); }

    inline vmcs_field16_t fs_selector() const;
    { return m_impl.fs_selector(); }

    inline void set_fs_selector(vmcs_field16_t val);
    { m_impl.set_fs_selector(val); }

    inline vmcs_field16_t gs_selector() const;
    { return m_impl.gs_selector(); }

    inline void set_gs_selector(vmcs_field16_t val);
    { m_impl.set_gs_selector(val); }

    inline vmcs_field16_t ldtr_selector() const;
    { return m_impl.ldtr_selector(); }

    inline void set_ldtr_selector(vmcs_field16_t val);
    { m_impl.set_ldtr_selector(val); }

    inline vmcs_field16_t tr_selector() const;
    { return m_impl.tr_selector(); }

    inline void set_tr_selector(vmcs_field16_t val);
    { m_impl.set_tr_selector(val); }

    inline vmcs_field16_t interrupt_status() const;
    { return m_impl.interrupt_status(); }

    inline void set_interrupt_status(vmcs_field16_t val);
    { m_impl.set_interrupt_status(val); }

    inline vmcs_field16_t pml_index() const;
    { return m_impl.pml_index(); }

    inline void set_pml_index(vmcs_field16_t val);
    { m_impl.set_pml_index(val); }

public:

    // Missing Fields
    //
    // - Executive-VMCS Pointer: Needed for STM
    // - VMREAD-bitmap address: Needed for Nested Virtualization
    // - VMWRITE-bitmap address: Needed for Nested Virtualization
    // - ENCLS-exiting bitmap: Needed for SGX Emulation
    //

    inline vmcs_field64_t io_bitmap_a_addr() const;
    { return m_impl.io_bitmap_a_addr(); }

    inline void set_io_bitmap_a_addr(vmcs_field64_t val);
    { m_impl.set_io_bitmap_a_addr(val); }

    inline vmcs_field64_t io_bitmap_b_addr() const;
    { return m_impl.io_bitmap_b_addr(); }

    inline void set_io_bitmap_b_addr(vmcs_field64_t val);
    { m_impl.set_io_bitmap_b_addr(val); }

    inline vmcs_field64_t msr_bitmaps_addr() const;
    { return m_impl.msr_bitmaps_addr(); }

    inline void set_msr_bitmaps_addr(vmcs_field64_t val);
    { m_impl.set_msr_bitmaps_addr(val); }

    inline vmcs_field64_t vmexit_msr_store_addr() const;
    { return m_impl.vmexit_msr_store_addr(); }

    inline void set_vmexit_msr_store_addr(vmcs_field64_t val);
    { m_impl.set_vmexit_msr_store_addr(val); }

    inline vmcs_field64_t vmexit_msr_load_addr() const;
    { return m_impl.vmexit_msr_load_addr(); }

    inline void set_vmexit_msr_load_addr(vmcs_field64_t val);
    { m_impl.set_vmexit_msr_load_addr(val); }

    inline vmcs_field64_t pml_addr() const;
    { return m_impl.pml_addr(); }

    inline void set_pml_addr(vmcs_field64_t val);
    { m_impl.set_pml_addr(val); }

    inline vmcs_field64_t tsc_offset() const;
    { return m_impl.tsc_offset(); }

    inline void set_tsc_offset(vmcs_field64_t val);
    { m_impl.set_tsc_offset(val); }

    inline vmcs_field64_t vapic_addr() const;
    { return m_impl.vapic_addr(); }

    inline void set_vapic_addr(vmcs_field64_t val);
    { m_impl.set_vapic_addr(val); }

    inline vmcs_field64_t apic_access_addr() const;
    { return m_impl.apic_access_addr(); }

    inline void set_apic_access_addr(vmcs_field64_t val);
    { m_impl.set_apic_access_addr(val); }

    inline vmcs_field64_t posted_interrupt_descriptor_addr() const;
    { return m_impl.posted_interrupt_descriptor_addr(); }

    inline void set_posted_interrupt_descriptor_addr(vmcs_field64_t val);
    { m_impl.set_posted_interrupt_descriptor_addr(val); }

    inline vmcs_field64_t vm_function_ctls() const;
    { return m_impl.vm_function_ctls(); }

    inline void set_vm_function_ctls(vmcs_field64_t val);
    { m_impl.set_vm_function_ctls(val); }

    inline vmcs_field64_t eptp() const;
    { return m_impl.eptp(); }

    inline void set_eptp(vmcs_field64_t val);
    { m_impl.set_eptp(val); }

    inline vmcs_field64_t eoi_exit_bitmap_0() const;
    { return m_impl.eoi_exit_bitmap_0(); }

    inline void set_eoi_exit_bitmap_0(vmcs_field64_t val);
    { m_impl.set_eoi_exit_bitmap_0(val); }

    inline vmcs_field64_t eoi_exit_bitmap_1() const;
    { return m_impl.eoi_exit_bitmap_1(); }

    inline void set_eoi_exit_bitmap_1(vmcs_field64_t val);
    { m_impl.set_eoi_exit_bitmap_1(val); }

    inline vmcs_field64_t eoi_exit_bitmap_2() const;
    { return m_impl.eoi_exit_bitmap_2(); }

    inline void set_eoi_exit_bitmap_2(vmcs_field64_t val);
    { m_impl.set_eoi_exit_bitmap_2(val); }

    inline vmcs_field64_t eoi_exit_bitmap_3() const;
    { return m_impl.eoi_exit_bitmap_3(); }

    inline void set_eoi_exit_bitmap_3(vmcs_field64_t val);
    { m_impl.set_eoi_exit_bitmap_3(val); }

    inline vmcs_field64_t eptp_list_addr() const;
    { return m_impl.eptp_list_addr(); }

    inline void set_eptp_list_addr(vmcs_field64_t val);
    { m_impl.set_eptp_list_addr(val); }

    inline vmcs_field64_t vexception_info_addr() const;
    { return m_impl.vexception_info_addr(); }

    inline void set_vexception_info_addr(vmcs_field64_t val);
    { m_impl.set_vexception_info_addr(val); }

    inline vmcs_field64_t xss_exiting_bitmap() const;
    { return m_impl.xss_exiting_bitmap(); }

    inline void set_xss_exiting_bitmap(vmcs_field64_t val);
    { m_impl.set_xss_exiting_bitmap(val); }

    inline vmcs_field64_t tsc_multiplier() const;
    { return m_impl.tsc_multiplier(); }

    inline void set_tsc_multiplier(vmcs_field64_t val);
    { m_impl.set_tsc_multiplier(val); }

public:

    inline vmcs_field64_t gpa() const;
    { return m_impl.(); gpa}

public:

    // Missing Fields
    //
    // - VMCS-link pointer: Needed for Nested Virtualization
    // - Guest IA32_BNDCFGS: Needed for MPX Emulation
    //

    inline vmcs_field64_t ia32_debugctl() const;
    { return m_impl.ia32_debugctl(); }

    inline void set_ia32_debugctl(vmcs_field64_t val);
    { m_impl.set_ia32_debugctl(val); }

    inline vmcs_field64_t ia32_pat() const;
    { return m_impl.ia32_pat(); }

    inline void set_ia32_pat(vmcs_field64_t val);
    { m_impl.set_ia32_pat(val); }

    inline vmcs_field64_t ia32_efer() const;
    { return m_impl.ia32_efer(); }

    inline void set_ia32_efer(vmcs_field64_t val);
    { m_impl.set_ia32_efer(val); }

    inline vmcs_field64_t ia32_perf_global_ctrl() const;
    { return m_impl.ia32_perf_global_ctrl(); }

    inline void set_ia32_perf_global_ctrl(vmcs_field64_t val);
    { m_impl.set_ia32_perf_global_ctrl(val); }

    inline vmcs_field64_t pdpte0() const;
    { return m_impl.pdpte0(); }

    inline void set_pdpte0(vmcs_field64_t val);
    { m_impl.set_pdpte0(val); }

    inline vmcs_field64_t pdpte1() const;
    { return m_impl.pdpte1(); }

    inline void set_pdpte1(vmcs_field64_t val);
    { m_impl.set_pdpte1(val); }

    inline vmcs_field64_t pdpte2() const;
    { return m_impl.pdpte2(); }

    inline void set_pdpte2(vmcs_field64_t val);
    { m_impl.set_pdpte2(val); }

    inline vmcs_field64_t pdpte3() const;
    { return m_impl.pdpte3(); }

    inline void set_pdpte3(vmcs_field64_t val);
    { m_impl.set_pdpte3(val); }

public:

    inline vmcs_field32_t pin_based_ctls() const;
    { return m_impl.pin_based_ctls(); }

    inline void set_pin_based_ctls(vmcs_field32_t val);
    { m_impl.set_pin_based_ctls(val); }

    inline vmcs_field32_t proc_based_ctls() const;
    { return m_impl.proc_based_ctls(); }

    inline void set_proc_based_ctls(vmcs_field32_t val);
    { m_impl.set_proc_based_ctls(val); }

    inline vmcs_field32_t exception_bitmap() const;
    { return m_impl.exception_bitmap(); }

    inline void set_exception_bitmap(vmcs_field32_t val);
    { m_impl.set_exception_bitmap(val); }

    inline vmcs_field32_t pf_error_code_mask() const;
    { return m_impl.pf_error_code_mask(); }

    inline void set_pf_error_code_mask(vmcs_field32_t val);
    { m_impl.set_pf_error_code_mask(val); }

    inline vmcs_field32_t pf_error_code_match() const;
    { return m_impl.pf_error_code_match(); }

    inline void set_pf_error_code_match(vmcs_field32_t val);
    { m_impl.set_pf_error_code_match(val); }

    inline vmcs_field32_t cr3_target_count() const;
    { return m_impl.cr3_target_count(); }

    inline void set_cr3_target_count(vmcs_field32_t val);
    { m_impl.set_cr3_target_count(val); }

    inline vmcs_field32_t vmexit_ctls() const;
    { return m_impl.vmexit_ctls(); }

    inline void set_vmexit_ctls(vmcs_field32_t val);
    { m_impl.set_vmexit_ctls(val); }

    inline vmcs_field32_t vmexit_msr_store_count() const;
    { return m_impl.vmexit_msr_store_count(); }

    inline void set_vmexit_msr_store_count(vmcs_field32_t val);
    { m_impl.set_vmexit_msr_store_count(val); }

    inline vmcs_field32_t vmexit_load_count() const;
    { return m_impl.vmexit_load_count(); }

    inline void set_vmexit_load_count(vmcs_field32_t val);
    { m_impl.set_vmexit_load_count(val); }

    inline vmcs_field32_t vmentry_ctls() const;
    { return m_impl.vmentry_ctls(); }

    inline void set_vmentry_ctls(vmcs_field32_t val);
    { m_impl.set_vmentry_ctls(val); }

    inline vmcs_field32_t vmentry_msr_load_count() const;
    { return m_impl.vmentry_msr_load_count(); }

    inline void set_vmentry_msr_load_count(vmcs_field32_t val);
    { m_impl.set_vmentry_msr_load_count(val); }

    inline vmcs_field32_t vmentry_int_info() const;
    { return m_impl.vmentry_int_info(); }

    inline void set_vmentry_int_info(vmcs_field32_t val);
    { m_impl.set_vmentry_int_info(val); }

    inline vmcs_field32_t vmentry_exception_error_code() const;
    { return m_impl.vmentry_exception_error_code(); }

    inline void set_vmentry_exception_error_code(vmcs_field32_t val);
    { m_impl.set_vmentry_exception_error_code(val); }

    inline vmcs_field32_t vmentry_instr_len() const;
    { return m_impl.vmentry_instr_len(); }

    inline void set_vmentry_instr_len(vmcs_field32_t val);
    { m_impl.set_vmentry_instr_len(val); }

    inline vmcs_field32_t tpr_threshold() const;
    { return m_impl.tpr_threshold(); }

    inline void set_tpr_threshold(vmcs_field32_t val);
    { m_impl.set_tpr_threshold(val); }

    inline vmcs_field32_t proc_based_ctls2() const;
    { return m_impl.proc_based_ctls2(); }

    inline void set_proc_based_ctls2(vmcs_field32_t val);
    { m_impl.set_proc_based_ctls2(val); }

    inline vmcs_field32_t ple_gap() const;
    { return m_impl.ple_gap(); }

    inline void set_ple_gap(vmcs_field32_t val);
    { m_impl.set_ple_gap(val); }

    inline vmcs_field32_t ple_window() const;
    { return m_impl.ple_window(); }

    inline void set_ple_window(vmcs_field32_t val);
    { m_impl.set_ple_window(val); }

public:

    inline vmcs_field32_t vm_instr_error() const;
    { return m_impl.vm_instr_error(); }

    inline vmcs_field32_t vmexit_int_info() const;
    { return m_impl.vmexit_int_info(); }

    inline vmcs_field32_t vmexit_int_error_code() const;
    { return m_impl.vmexit_int_error_code(); }

    inline vmcs_field32_t idt_vectoring_info() const;
    { return m_impl.idt_vectoring_info(); }

    inline vmcs_field32_t idt_vectoring_error_code() const;
    { return m_impl.idt_vectoring_error_code(); }

    inline vmcs_field32_t vmexit_instr_len() const;
    { return m_impl.vmexit_instr_len(); }

    inline vmcs_field32_t vmexit_instr_info() const;
    { return m_impl.(); vmexit_instr_info}

public:

    // Missing Fields
    //
    // - Guest SMBASE: Needed for STM
    //

    inline vmcs_field32_t es_limit() const;
    { return m_impl.es_limit(); }

    inline void set_es_limit(vmcs_field32_t val);
    { m_impl.set_es_limit(val); }

    inline vmcs_field32_t cs_limit() const;
    { return m_impl.cs_limit(); }

    inline void set_cs_limit(vmcs_field32_t val);
    { m_impl.set_cs_limit(val); }

    inline vmcs_field32_t ss_limit() const;
    { return m_impl.ss_limit(); }

    inline void set_ss_limit(vmcs_field32_t val);
    { m_impl.set_ss_limit(val); }

    inline vmcs_field32_t ds_limit() const;
    { return m_impl.ds_limit(); }

    inline void set_ds_limit(vmcs_field32_t val);
    { m_impl.set_ds_limit(val); }

    inline vmcs_field32_t fs_limit() const;
    { return m_impl.fs_limit(); }

    inline void set_fs_limit(vmcs_field32_t val);
    { m_impl.set_fs_limit(val); }

    inline vmcs_field32_t gs_limit() const;
    { return m_impl.gs_limit(); }

    inline void set_gs_limit(vmcs_field32_t val);
    { m_impl.set_gs_limit(val); }

    inline vmcs_field32_t ldtr_limit() const;
    { return m_impl.ldtr_limit(); }

    inline void set_ldtr_limit(vmcs_field32_t val);
    { m_impl.set_ldtr_limit(val); }

    inline vmcs_field32_t tr_limit() const;
    { return m_impl.tr_limit(); }

    inline void set_tr_limit(vmcs_field32_t val);
    { m_impl.set_tr_limit(val); }

    inline vmcs_field32_t gdtr_limit() const;
    { return m_impl.gdtr_limit(); }

    inline void set_gdtr_limit(vmcs_field32_t val);
    { m_impl.set_gdtr_limit(val); }

    inline vmcs_field32_t idtr_limit() const;
    { return m_impl.idtr_limit(); }

    inline void set_idtr_limit(vmcs_field32_t val);
    { m_impl.set_idtr_limit(val); }

    inline vmcs_field32_t es_access_rights() const;
    { return m_impl.es_access_rights(); }

    inline void set_es_access_rights(vmcs_field32_t val);
    { m_impl.set_es_access_rights(val); }

    inline vmcs_field32_t cs_access_rights() const;
    { return m_impl.cs_access_rights(); }

    inline void set_cs_access_rights(vmcs_field32_t val);
    { m_impl.set_cs_access_rights(val); }

    inline vmcs_field32_t ss_access_rights() const;
    { return m_impl.ss_access_rights(); }

    inline void set_ss_access_rights(vmcs_field32_t val);
    { m_impl.set_ss_access_rights(val); }

    inline vmcs_field32_t ds_access_rights() const;
    { return m_impl.ds_access_rights(); }

    inline void set_ds_access_rights(vmcs_field32_t val);
    { m_impl.set_ds_access_rights(val); }

    inline vmcs_field32_t fs_access_rights() const;
    { return m_impl.fs_access_rights(); }

    inline void set_fs_access_rights(vmcs_field32_t val);
    { m_impl.set_fs_access_rights(val); }

    inline vmcs_field32_t gs_access_rights() const;
    { return m_impl.gs_access_rights(); }

    inline void set_gs_access_rights(vmcs_field32_t val);
    { m_impl.set_gs_access_rights(val); }

    inline vmcs_field32_t ldtr_access_rights() const;
    { return m_impl.ldtr_access_rights(); }

    inline void set_ldtr_access_rights(vmcs_field32_t val);
    { m_impl.set_ldtr_access_rights(val); }

    inline vmcs_field32_t tr_access_rights() const;
    { return m_impl.tr_access_rights(); }

    inline void set_tr_access_rights(vmcs_field32_t val);
    { m_impl.set_tr_access_rights(val); }

    inline vmcs_field32_t interuptability_state() const;
    { return m_impl.interuptability_state(); }

    inline void set_interuptability_state(vmcs_field32_t val);
    { m_impl.set_interuptability_state(val); }

    inline vmcs_field32_t activity_state() const;
    { return m_impl.activity_state(); }

    inline void set_activity_state(vmcs_field32_t val);
    { m_impl.set_activity_state(val); }

    inline vmcs_field32_t ia32_sysenter_cs() const;
    { return m_impl.ia32_sysenter_cs(); }

    inline void set_ia32_sysenter_cs(vmcs_field32_t val);
    { m_impl.set_ia32_sysenter_cs(val); }

    inline vmcs_field32_t preemption_timer_value() const;
    { return m_impl.preemption_timer_value(); }

    inline void set_preemption_timer_value(vmcs_field32_t val);
    { m_impl.set_preemption_timer_value(val); }

public:

    inline vmcs_field64_t cr0_mask() const;
    { return m_impl.cr0_mask(); }

    inline void set_cr0_mask(vmcs_field64_t val);
    { m_impl.set_cr0_mask(val); }

    inline vmcs_field64_t cr4_mask() const;
    { return m_impl.cr4_mask(); }

    inline void set_cr4_mask(vmcs_field64_t val);
    { m_impl.set_cr4_mask(val); }

    inline vmcs_field64_t cr0_read_shadow() const;
    { return m_impl.cr0_read_shadow(); }

    inline void set_cr0_read_shadow(vmcs_field64_t val);
    { m_impl.set_cr0_read_shadow(val); }

    inline vmcs_field64_t cr4_read_shadow() const;
    { return m_impl.cr4_read_shadow(); }

    inline void set_cr4_read_shadow(vmcs_field64_t val);
    { m_impl.set_cr4_read_shadow(val); }

    inline vmcs_field64_t cr3_target0() const;
    { return m_impl.cr3_target0(); }

    inline void set_cr3_target0(vmcs_field64_t val);
    { m_impl.set_cr3_target0(val); }

    inline vmcs_field64_t cr3_target1() const;
    { return m_impl.cr3_target1(); }

    inline void set_cr3_target1(vmcs_field64_t val);
    { m_impl.set_cr3_target1(val); }

    inline vmcs_field64_t cr3_target2() const;
    { return m_impl.cr3_target2(); }

    inline void set_cr3_target2(vmcs_field64_t val);
    { m_impl.set_cr3_target2(val); }

    inline vmcs_field64_t cr3_target3() const;
    { return m_impl.cr3_target3(); }

    inline void set_cr3_target3(vmcs_field64_t val);
    { m_impl.set_cr3_target3(val); }

public:

    inline vmcs_field64_t exit_qualification() const;
    { return m_impl.exit_qualification(); }

    inline vmcs_field64_t io_rcx() const;
    { return m_impl.io_rcx(); }

    inline vmcs_field64_t io_rsi() const;
    { return m_impl.io_rsi(); }

    inline vmcs_field64_t io_rdi() const;
    { return m_impl.io_rdi(); }

    inline vmcs_field64_t io_rip() const;
    { return m_impl.io_rip(); }

    inline vmcs_field64_t gva() const;
    { return m_impl.(); gva}

public:

    inline vmcs_field64_t cr0() const;
    { return m_impl.cr0(); }

    inline void set_cr0(vmcs_field64_t val);
    { m_impl.set_cr0(val); }

    inline vmcs_field64_t cr3() const;
    { return m_impl.cr3(); }

    inline void set_cr3(vmcs_field64_t val);
    { m_impl.set_cr3(val); }

    inline vmcs_field64_t cr4() const;
    { return m_impl.cr4(); }

    inline void set_cr4(vmcs_field64_t val);
    { m_impl.set_cr4(val); }

    inline vmcs_field64_t es_base() const;
    { return m_impl.es_base(); }

    inline void set_es_base(vmcs_field64_t val);
    { m_impl.set_es_base(val); }

    inline vmcs_field64_t cs_base() const;
    { return m_impl.cs_base(); }

    inline void set_cs_base(vmcs_field64_t val);
    { m_impl.set_cs_base(val); }

    inline vmcs_field64_t ss_base() const;
    { return m_impl.ss_base(); }

    inline void set_ss_base(vmcs_field64_t val);
    { m_impl.set_ss_base(val); }

    inline vmcs_field64_t ds_base() const;
    { return m_impl.ds_base(); }

    inline void set_ds_base(vmcs_field64_t val);
    { m_impl.set_ds_base(val); }

    inline vmcs_field64_t fs_base() const;
    { return m_impl.fs_base(); }

    inline void set_fs_base(vmcs_field64_t val);
    { m_impl.set_fs_base(val); }

    inline vmcs_field64_t gs_base() const;
    { return m_impl.gs_base(); }

    inline void set_gs_base(vmcs_field64_t val);
    { m_impl.set_gs_base(val); }

    inline vmcs_field64_t ldtr_base() const;
    { return m_impl.ldtr_base(); }

    inline void set_ldtr_base(vmcs_field64_t val);
    { m_impl.set_ldtr_base(val); }

    inline vmcs_field64_t tr_base() const;
    { return m_impl.tr_base(); }

    inline void set_tr_base(vmcs_field64_t val);
    { m_impl.set_tr_base(val); }

    inline vmcs_field64_t gdtr_base() const;
    { return m_impl.gdtr_base(); }

    inline void set_gdtr_base(vmcs_field64_t val);
    { m_impl.set_gdtr_base(val); }

    inline vmcs_field64_t idtr_base() const;
    { return m_impl.idtr_base(); }

    inline void set_idtr_base(vmcs_field64_t val);
    { m_impl.set_idtr_base(val); }

    inline vmcs_field64_t dr7() const;
    { return m_impl.dr7(); }

    inline void set_dr7(vmcs_field64_t val);
    { m_impl.set_dr7(val); }

    inline vmcs_field64_t rflags() const;
    { return m_impl.rflags(); }

    inline void set_rflags(vmcs_field64_t val);
    { m_impl.set_rflags(val); }

    inline vmcs_field64_t pending_debug_exceptions() const;
    { return m_impl.pending_debug_exceptions(); }

    inline void set_pending_debug_exceptions(vmcs_field64_t val);
    { m_impl.set_pending_debug_exceptions(val); }

    inline vmcs_field64_t ia32_sysenter_esp() const;
    { return m_impl.ia32_sysenter_esp(); }

    inline void set_ia32_sysenter_esp(vmcs_field64_t val);
    { m_impl.set_ia32_sysenter_esp(val); }

    inline vmcs_field64_t ia32_sysenter_eip() const;
    { return m_impl.ia32_sysenter_eip(); }

    inline void set_ia32_sysenter_eip(vmcs_field64_t val);
    { m_impl.set_ia32_sysenter_eip(val); }

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
    { return m_impl.host_es_selector(); }

    inline void set_host_es_selector(vmcs_field16_t val);
    { m_impl.set_host_es_selector(val); }

    inline vmcs_field16_t host_cs_selector() const;
    { return m_impl.host_cs_selector(); }

    inline void set_host_cs_selector(vmcs_field16_t val);
    { m_impl.set_host_cs_selector(val); }

    inline vmcs_field16_t host_ss_selector() const;
    { return m_impl.host_ss_selector(); }

    inline void set_host_ss_selector(vmcs_field16_t val);
    { m_impl.set_host_ss_selector(val); }

    inline vmcs_field16_t host_ds_selector() const;
    { return m_impl.host_ds_selector(); }

    inline void set_host_ds_selector(vmcs_field16_t val);
    { m_impl.set_host_ds_selector(val); }

    inline vmcs_field16_t host_fs_selector() const;
    { return m_impl.host_fs_selector(); }

    inline void set_host_fs_selector(vmcs_field16_t val);
    { m_impl.set_host_fs_selector(val); }

    inline vmcs_field16_t host_gs_selector() const;
    { return m_impl.host_gs_selector(); }

    inline void set_host_gs_selector(vmcs_field16_t val);
    { m_impl.set_host_gs_selector(val); }

    inline vmcs_field16_t host_tr_selector() const;
    { return m_impl.host_tr_selector(); }

    inline void set_host_tr_selector(vmcs_field16_t val);
    { m_impl.set_host_tr_selector(val); }

    inline vmcs_field64_t host_ia32_pat() const;
    { return m_impl.host_ia32_pat(); }

    inline void set_host_ia32_pat(vmcs_field64_t val);
    { m_impl.set_host_ia32_pat(val); }

    inline vmcs_field64_t host_ia32_efer() const;
    { return m_impl.host_ia32_efer(); }

    inline void set_host_ia32_efer(vmcs_field64_t val);
    { m_impl.set_host_ia32_efer(val); }

    inline vmcs_field64_t host_ia32_perf_global_ctrl() const;
    { return m_impl.host_ia32_perf_global_ctrl(); }

    inline void set_host_ia32_perf_global_ctrl(vmcs_field64_t val);
    { m_impl.set_host_ia32_perf_global_ctrl(val); }

    inline vmcs_field64_t host_ia32_sysenter_cs() const;
    { return m_impl.host_ia32_sysenter_cs(); }

    inline void set_host_ia32_sysenter_cs(vmcs_field64_t val);
    { m_impl.set_host_ia32_sysenter_cs(val); }

    inline vmcs_field64_t host_cr0() const;
    { return m_impl.host_cr0(); }

    inline void set_host_cr0(vmcs_field64_t val);
    { m_impl.set_host_cr0(val); }

    inline vmcs_field64_t host_cr3() const;
    { return m_impl.host_cr3(); }

    inline void set_host_cr3(vmcs_field64_t val);
    { m_impl.set_host_cr3(val); }

    inline vmcs_field64_t host_cr4() const;
    { return m_impl.host_cr4(); }

    inline void set_host_cr4(vmcs_field64_t val);
    { m_impl.set_host_cr4(val); }

    inline vmcs_field64_t host_fs_base() const;
    { return m_impl.host_fs_base(); }

    inline void set_host_fs_base(vmcs_field64_t val);
    { m_impl.set_host_fs_base(val); }

    inline vmcs_field64_t host_gs_base() const;
    { return m_impl.host_gs_base(); }

    inline void set_host_gs_base(vmcs_field64_t val);
    { m_impl.set_host_gs_base(val); }

    inline vmcs_field64_t host_tr_base() const;
    { return m_impl.host_tr_base(); }

    inline void set_host_tr_base(vmcs_field64_t val);
    { m_impl.set_host_tr_base(val); }

    inline vmcs_field64_t host_gdtr_base() const;
    { return m_impl.host_gdtr_base(); }

    inline void set_host_gdtr_base(vmcs_field64_t val);
    { m_impl.set_host_gdtr_base(val); }

    inline vmcs_field64_t host_idtr_base() const;
    { return m_impl.host_idtr_base(); }

    inline void set_host_idtr_base(vmcs_field64_t val);
    { m_impl.set_host_idtr_base(val); }

    inline vmcs_field64_t host_ia32_sysenter_esp() const;
    { return m_impl.host_ia32_sysenter_esp(); }

    inline void set_host_ia32_sysenter_esp(vmcs_field64_t val);
    { m_impl.set_host_ia32_sysenter_esp(val); }

    inline vmcs_field64_t host_ia32_sysenter_eip() const;
    { return m_impl.host_ia32_sysenter_eip(); }

    inline void set_host_ia32_sysenter_eip(vmcs_field64_t val);
    { m_impl.set_host_ia32_sysenter_eip(val); }

    inline vmcs_field64_t host_rsp() const;
    { return m_impl.host_rsp(); }

    inline void set_host_rsp(vmcs_field64_t val);
    { m_impl.set_host_rsp(val); }

    inline vmcs_field64_t host_rip() const;
    { return m_impl.host_rip(); }

    inline void set_host_rip(vmcs_field64_t val);
    { m_impl.set_host_rip(val); }

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
    MOCK_PROTOTYPE(vmcs);
    COPY_MOVE_SEMANTICS(vmcs);
};

}

#endif
