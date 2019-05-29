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

#include <bfgsl.h>
#include <bftypes.h>
#include <bfdelegate.h>

#include "../../impl.h"
#include "../../../implementation/vcpu_t.h"

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

namespace bfvmm::uapis::intel_x64
{

/// Intel x86_64 VMCS
///
/// The following provides the VMCS implementation as defined by the
/// Intel Software Developer's Manual (chapters 24-33). To best understand
/// this code, the manual should first be read.
///
/// This class provides all of the VMCS operations that are defined in the
/// manual including access to most of the fields in the VMCS. These functions
/// should be used instead of directly accessing the VMCS as this class will
/// not only ensure the proper VMCS is loaded when debugging is enabled, but
/// it will also handle vCPU specific logic that might be needed. Also note
/// that this class provides the ability to add delegates for the VMCS
/// operations if an extension needs to execute logic prior to a VMCS function
/// being executed. These delegates should be added with care as some might
/// impose large performance hits.
///
template<typename IMPL>
struct vmcs
{
    using vmcs_field16_t = uint16_t;                    ///< VMCS 16bit Type
    using vmcs_field32_t = uint32_t;                    ///< VMCS 32bit Type
    using vmcs_field64_t = uint64_t;                    ///< VMCS 64bit Type
    using vmcs_delegate_t = delegate<void(vcpu_t *)>;   ///< VMCS Delegate Type

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
    CONSTEXPR void vmcs_add_vmlaunch_delegate(const vmcs_delegate_t &d)
    { impl<const IMPL>(this)->__vmcs_add_vmlaunch_delegate(d); }

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
    CONSTEXPR void vmcs_add_vmresume_delegate(const vmcs_delegate_t &d)
    { impl<const IMPL>(this)->__vmcs_add_vmresume_delegate(d); }

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
    CONSTEXPR void vmcs_add_vmload_delegate(const vmcs_delegate_t &d)
    { impl<const IMPL>(this)->__vmcs_add_vmload_delegate(d); }

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
    CONSTEXPR void vmcs_add_vmclear_delegate(const vmcs_delegate_t &d)
    { impl<const IMPL>(this)->__vmcs_add_vmclear_delegate(d); }

    /// @cond
    ///
    /// VMCS Fields
    ///
    /// The remaining functions are all setters and getters for the VMCS
    /// fields that are defined in the Intel SDM. These setters and getters
    /// should be used instead of directly calling the VMCS intrinsics as
    /// these functions provide additional facilities when debugging is
    /// enabled, and they are handle special functionality based on how the
    /// fields are supposed to be populated (and internal state).
    ///
    /// @expects none
    /// @ensures none
    ///

    CONSTEXPR vmcs_field16_t vpid() const
    { return impl<const IMPL>(this)->__vpid(); }

    CONSTEXPR void set_vpid(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_vpid(val); }

    CONSTEXPR vmcs_field16_t posted_interrupt_notification_vector() const
    { return impl<const IMPL>(this)->__posted_interrupt_notification_vector(); }

    CONSTEXPR void set_posted_interrupt_notification_vector(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_posted_interrupt_notification_vector(val); }

    CONSTEXPR vmcs_field16_t es_selector() const
    { return impl<const IMPL>(this)->__es_selector(); }

    CONSTEXPR void set_es_selector(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_es_selector(val); }

    CONSTEXPR vmcs_field16_t cs_selector() const
    { return impl<const IMPL>(this)->__cs_selector(); }

    CONSTEXPR void set_cs_selector(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_cs_selector(val); }

    CONSTEXPR vmcs_field16_t ss_selector() const
    { return impl<const IMPL>(this)->__ss_selector(); }

    CONSTEXPR void set_ss_selector(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_ss_selector(val); }

    CONSTEXPR vmcs_field16_t ds_selector() const
    { return impl<const IMPL>(this)->__ds_selector(); }

    CONSTEXPR void set_ds_selector(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_ds_selector(val); }

    CONSTEXPR vmcs_field16_t fs_selector() const
    { return impl<const IMPL>(this)->__fs_selector(); }

    CONSTEXPR void set_fs_selector(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_fs_selector(val); }

    CONSTEXPR vmcs_field16_t gs_selector() const
    { return impl<const IMPL>(this)->__gs_selector(); }

    CONSTEXPR void set_gs_selector(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_gs_selector(val); }

    CONSTEXPR vmcs_field16_t ldtr_selector() const
    { return impl<const IMPL>(this)->__ldtr_selector(); }

    CONSTEXPR void set_ldtr_selector(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_ldtr_selector(val); }

    CONSTEXPR vmcs_field16_t tr_selector() const
    { return impl<const IMPL>(this)->__tr_selector(); }

    CONSTEXPR void set_tr_selector(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_tr_selector(val); }

    CONSTEXPR vmcs_field16_t interrupt_status() const
    { return impl<const IMPL>(this)->__interrupt_status(); }

    CONSTEXPR void set_interrupt_status(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_interrupt_status(val); }

    CONSTEXPR vmcs_field16_t pml_index() const
    { return impl<const IMPL>(this)->__pml_index(); }

    CONSTEXPR void set_pml_index(vmcs_field16_t val)
    { impl<IMPL>(this)->__set_pml_index(val); }

    // Missing Fields
    //
    // - Executive-VMCS Pointer: Needed for STM
    // - VMREAD-bitmap address: Needed for Nested Virtualization
    // - VMWRITE-bitmap address: Needed for Nested Virtualization
    // - ENCLS-exiting bitmap: Needed for SGX Emulation
    //

    CONSTEXPR vmcs_field64_t io_bitmap_a_addr() const
    { return impl<const IMPL>(this)->__io_bitmap_a_addr(); }

    CONSTEXPR void set_io_bitmap_a_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_io_bitmap_a_addr(val); }

    CONSTEXPR vmcs_field64_t io_bitmap_b_addr() const
    { return impl<const IMPL>(this)->__io_bitmap_b_addr(); }

    CONSTEXPR void set_io_bitmap_b_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_io_bitmap_b_addr(val); }

    CONSTEXPR vmcs_field64_t msr_bitmaps_addr() const
    { return impl<const IMPL>(this)->__msr_bitmaps_addr(); }

    CONSTEXPR void set_msr_bitmaps_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_msr_bitmaps_addr(val); }

    CONSTEXPR vmcs_field64_t vmexit_msr_store_addr() const
    { return impl<const IMPL>(this)->__vmexit_msr_store_addr(); }

    CONSTEXPR void set_vmexit_msr_store_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_vmexit_msr_store_addr(val); }

    CONSTEXPR vmcs_field64_t vmexit_msr_load_addr() const
    { return impl<const IMPL>(this)->__vmexit_msr_load_addr(); }

    CONSTEXPR void set_vmexit_msr_load_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_vmexit_msr_load_addr(val); }

    CONSTEXPR vmcs_field64_t pml_addr() const
    { return impl<const IMPL>(this)->__pml_addr(); }

    CONSTEXPR void set_pml_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_pml_addr(val); }

    CONSTEXPR vmcs_field64_t tsc_offset() const
    { return impl<const IMPL>(this)->__tsc_offset(); }

    CONSTEXPR void set_tsc_offset(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_tsc_offset(val); }

    CONSTEXPR vmcs_field64_t vapic_addr() const
    { return impl<const IMPL>(this)->__vapic_addr(); }

    CONSTEXPR void set_vapic_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_vapic_addr(val); }

    CONSTEXPR vmcs_field64_t apic_access_addr() const
    { return impl<const IMPL>(this)->__apic_access_addr(); }

    CONSTEXPR void set_apic_access_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_apic_access_addr(val); }

    CONSTEXPR vmcs_field64_t posted_interrupt_descriptor_addr() const
    { return impl<const IMPL>(this)->__posted_interrupt_descriptor_addr(); }

    CONSTEXPR void set_posted_interrupt_descriptor_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_posted_interrupt_descriptor_addr(val); }

    CONSTEXPR vmcs_field64_t vm_function_ctls() const
    { return impl<const IMPL>(this)->__vm_function_ctls(); }

    CONSTEXPR void set_vm_function_ctls(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_vm_function_ctls(val); }

    CONSTEXPR vmcs_field64_t eptp() const
    { return impl<const IMPL>(this)->__eptp(); }

    CONSTEXPR void set_eptp(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_eptp(val); }

    CONSTEXPR vmcs_field64_t eoi_exit_bitmap_0() const
    { return impl<const IMPL>(this)->__eoi_exit_bitmap_0(); }

    CONSTEXPR void set_eoi_exit_bitmap_0(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_eoi_exit_bitmap_0(val); }

    CONSTEXPR vmcs_field64_t eoi_exit_bitmap_1() const
    { return impl<const IMPL>(this)->__eoi_exit_bitmap_1(); }

    CONSTEXPR void set_eoi_exit_bitmap_1(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_eoi_exit_bitmap_1(val); }

    CONSTEXPR vmcs_field64_t eoi_exit_bitmap_2() const
    { return impl<const IMPL>(this)->__eoi_exit_bitmap_2(); }

    CONSTEXPR void set_eoi_exit_bitmap_2(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_eoi_exit_bitmap_2(val); }

    CONSTEXPR vmcs_field64_t eoi_exit_bitmap_3() const
    { return impl<const IMPL>(this)->__eoi_exit_bitmap_3(); }

    CONSTEXPR void set_eoi_exit_bitmap_3(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_eoi_exit_bitmap_3(val); }

    CONSTEXPR vmcs_field64_t eptp_list_addr() const
    { return impl<const IMPL>(this)->__eptp_list_addr(); }

    CONSTEXPR void set_eptp_list_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_eptp_list_addr(val); }

    CONSTEXPR vmcs_field64_t vexception_info_addr() const
    { return impl<const IMPL>(this)->__vexception_info_addr(); }

    CONSTEXPR void set_vexception_info_addr(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_vexception_info_addr(val); }

    CONSTEXPR vmcs_field64_t xss_exiting_bitmap() const
    { return impl<const IMPL>(this)->__xss_exiting_bitmap(); }

    CONSTEXPR void set_xss_exiting_bitmap(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_xss_exiting_bitmap(val); }

    CONSTEXPR vmcs_field64_t tsc_multiplier() const
    { return impl<const IMPL>(this)->__tsc_multiplier(); }

    CONSTEXPR void set_tsc_multiplier(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_tsc_multiplier(val); }

    CONSTEXPR vmcs_field64_t gpa() const
    { return impl<const IMPL>(this)->__gpa(); }

    // Missing Fields
    //
    // - VMCS-link pointer: Needed for Nested Virtualization
    // - Guest IA32_BNDCFGS: Needed for MPX Emulation
    //

    CONSTEXPR vmcs_field64_t ia32_debugctl() const
    { return impl<const IMPL>(this)->__ia32_debugctl(); }

    CONSTEXPR void set_ia32_debugctl(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_ia32_debugctl(val); }

    CONSTEXPR vmcs_field64_t ia32_pat() const
    { return impl<const IMPL>(this)->__ia32_pat(); }

    CONSTEXPR void set_ia32_pat(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_ia32_pat(val); }

    CONSTEXPR vmcs_field64_t ia32_efer() const
    { return impl<const IMPL>(this)->__ia32_efer(); }

    CONSTEXPR void set_ia32_efer(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_ia32_efer(val); }

    CONSTEXPR vmcs_field64_t ia32_perf_global_ctrl() const
    { return impl<const IMPL>(this)->__ia32_perf_global_ctrl(); }

    CONSTEXPR void set_ia32_perf_global_ctrl(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_ia32_perf_global_ctrl(val); }

    CONSTEXPR vmcs_field64_t pdpte0() const
    { return impl<const IMPL>(this)->__pdpte0(); }

    CONSTEXPR void set_pdpte0(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_pdpte0(val); }

    CONSTEXPR vmcs_field64_t pdpte1() const
    { return impl<const IMPL>(this)->__pdpte1(); }

    CONSTEXPR void set_pdpte1(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_pdpte1(val); }

    CONSTEXPR vmcs_field64_t pdpte2() const
    { return impl<const IMPL>(this)->__pdpte2(); }

    CONSTEXPR void set_pdpte2(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_pdpte2(val); }

    CONSTEXPR vmcs_field64_t pdpte3() const
    { return impl<const IMPL>(this)->__pdpte3(); }

    CONSTEXPR void set_pdpte3(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_pdpte3(val); }

    CONSTEXPR vmcs_field32_t pin_based_ctls() const
    { return impl<const IMPL>(this)->__pin_based_ctls(); }

    CONSTEXPR void set_pin_based_ctls(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_pin_based_ctls(val); }

    CONSTEXPR vmcs_field32_t proc_based_ctls() const
    { return impl<const IMPL>(this)->__proc_based_ctls(); }

    CONSTEXPR void set_proc_based_ctls(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_proc_based_ctls(val); }

    CONSTEXPR vmcs_field32_t exception_bitmap() const
    { return impl<const IMPL>(this)->__exception_bitmap(); }

    CONSTEXPR void set_exception_bitmap(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_exception_bitmap(val); }

    CONSTEXPR vmcs_field32_t pf_error_code_mask() const
    { return impl<const IMPL>(this)->__pf_error_code_mask(); }

    CONSTEXPR void set_pf_error_code_mask(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_pf_error_code_mask(val); }

    CONSTEXPR vmcs_field32_t pf_error_code_match() const
    { return impl<const IMPL>(this)->__pf_error_code_match(); }

    CONSTEXPR void set_pf_error_code_match(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_pf_error_code_match(val); }

    CONSTEXPR vmcs_field32_t cr3_target_count() const
    { return impl<const IMPL>(this)->__cr3_target_count(); }

    CONSTEXPR void set_cr3_target_count(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_cr3_target_count(val); }

    CONSTEXPR vmcs_field32_t vmexit_ctls() const
    { return impl<const IMPL>(this)->__vmexit_ctls(); }

    CONSTEXPR void set_vmexit_ctls(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_vmexit_ctls(val); }

    CONSTEXPR vmcs_field32_t vmexit_msr_store_count() const
    { return impl<const IMPL>(this)->__vmexit_msr_store_count(); }

    CONSTEXPR void set_vmexit_msr_store_count(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_vmexit_msr_store_count(val); }

    CONSTEXPR vmcs_field32_t vmexit_load_count() const
    { return impl<const IMPL>(this)->__vmexit_load_count(); }

    CONSTEXPR void set_vmexit_load_count(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_vmexit_load_count(val); }

    CONSTEXPR vmcs_field32_t vmentry_ctls() const
    { return impl<const IMPL>(this)->__vmentry_ctls(); }

    CONSTEXPR void set_vmentry_ctls(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_vmentry_ctls(val); }

    CONSTEXPR vmcs_field32_t vmentry_msr_load_count() const
    { return impl<const IMPL>(this)->__vmentry_msr_load_count(); }

    CONSTEXPR void set_vmentry_msr_load_count(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_vmentry_msr_load_count(val); }

    CONSTEXPR vmcs_field32_t vmentry_int_info() const
    { return impl<const IMPL>(this)->__vmentry_int_info(); }

    CONSTEXPR void set_vmentry_int_info(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_vmentry_int_info(val); }

    CONSTEXPR vmcs_field32_t vmentry_exception_error_code() const
    { return impl<const IMPL>(this)->__vmentry_exception_error_code(); }

    CONSTEXPR void set_vmentry_exception_error_code(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_vmentry_exception_error_code(val); }

    CONSTEXPR vmcs_field32_t vmentry_instr_len() const
    { return impl<const IMPL>(this)->__vmentry_instr_len(); }

    CONSTEXPR void set_vmentry_instr_len(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_vmentry_instr_len(val); }

    CONSTEXPR vmcs_field32_t tpr_threshold() const
    { return impl<const IMPL>(this)->__tpr_threshold(); }

    CONSTEXPR void set_tpr_threshold(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_tpr_threshold(val); }

    CONSTEXPR vmcs_field32_t proc_based_ctls2() const
    { return impl<const IMPL>(this)->__proc_based_ctls2(); }

    CONSTEXPR void set_proc_based_ctls2(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_proc_based_ctls2(val); }

    CONSTEXPR vmcs_field32_t ple_gap() const
    { return impl<const IMPL>(this)->__ple_gap(); }

    CONSTEXPR void set_ple_gap(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_ple_gap(val); }

    CONSTEXPR vmcs_field32_t ple_window() const
    { return impl<const IMPL>(this)->__ple_window(); }

    CONSTEXPR void set_ple_window(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_ple_window(val); }

    CONSTEXPR vmcs_field32_t vm_instr_error() const
    { return impl<const IMPL>(this)->__vm_instr_error(); }

    CONSTEXPR vmcs_field32_t vmexit_int_info() const
    { return impl<const IMPL>(this)->__vmexit_int_info(); }

    CONSTEXPR vmcs_field32_t vmexit_int_error_code() const
    { return impl<const IMPL>(this)->__vmexit_int_error_code(); }

    CONSTEXPR vmcs_field32_t idt_vectoring_info() const
    { return impl<const IMPL>(this)->__idt_vectoring_info(); }

    CONSTEXPR vmcs_field32_t idt_vectoring_error_code() const
    { return impl<const IMPL>(this)->__idt_vectoring_error_code(); }

    CONSTEXPR vmcs_field32_t vmexit_instr_len() const
    { return impl<const IMPL>(this)->__vmexit_instr_len(); }

    CONSTEXPR vmcs_field32_t vmexit_instr_info() const
    { return impl<const IMPL>(this)->__vmexit_instr_info(); }

    // Missing Fields
    //
    // - Guest SMBASE: Needed for STM
    //

    CONSTEXPR vmcs_field32_t es_limit() const
    { return impl<const IMPL>(this)->__es_limit(); }

    CONSTEXPR void set_es_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_es_limit(val); }

    CONSTEXPR vmcs_field32_t cs_limit() const
    { return impl<const IMPL>(this)->__cs_limit(); }

    CONSTEXPR void set_cs_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_cs_limit(val); }

    CONSTEXPR vmcs_field32_t ss_limit() const
    { return impl<const IMPL>(this)->__ss_limit(); }

    CONSTEXPR void set_ss_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_ss_limit(val); }

    CONSTEXPR vmcs_field32_t ds_limit() const
    { return impl<const IMPL>(this)->__ds_limit(); }

    CONSTEXPR void set_ds_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_ds_limit(val); }

    CONSTEXPR vmcs_field32_t fs_limit() const
    { return impl<const IMPL>(this)->__fs_limit(); }

    CONSTEXPR void set_fs_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_fs_limit(val); }

    CONSTEXPR vmcs_field32_t gs_limit() const
    { return impl<const IMPL>(this)->__gs_limit(); }

    CONSTEXPR void set_gs_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_gs_limit(val); }

    CONSTEXPR vmcs_field32_t ldtr_limit() const
    { return impl<const IMPL>(this)->__ldtr_limit(); }

    CONSTEXPR void set_ldtr_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_ldtr_limit(val); }

    CONSTEXPR vmcs_field32_t tr_limit() const
    { return impl<const IMPL>(this)->__tr_limit(); }

    CONSTEXPR void set_tr_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_tr_limit(val); }

    CONSTEXPR vmcs_field32_t gdtr_limit() const
    { return impl<const IMPL>(this)->__gdtr_limit(); }

    CONSTEXPR void set_gdtr_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_gdtr_limit(val); }

    CONSTEXPR vmcs_field32_t idtr_limit() const
    { return impl<const IMPL>(this)->__idtr_limit(); }

    CONSTEXPR void set_idtr_limit(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_idtr_limit(val); }

    CONSTEXPR vmcs_field32_t es_access_rights() const
    { return impl<const IMPL>(this)->__es_access_rights(); }

    CONSTEXPR void set_es_access_rights(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_es_access_rights(val); }

    CONSTEXPR vmcs_field32_t cs_access_rights() const
    { return impl<const IMPL>(this)->__cs_access_rights(); }

    CONSTEXPR void set_cs_access_rights(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_cs_access_rights(val); }

    CONSTEXPR vmcs_field32_t ss_access_rights() const
    { return impl<const IMPL>(this)->__ss_access_rights(); }

    CONSTEXPR void set_ss_access_rights(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_ss_access_rights(val); }

    CONSTEXPR vmcs_field32_t ds_access_rights() const
    { return impl<const IMPL>(this)->__ds_access_rights(); }

    CONSTEXPR void set_ds_access_rights(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_ds_access_rights(val); }

    CONSTEXPR vmcs_field32_t fs_access_rights() const
    { return impl<const IMPL>(this)->__fs_access_rights(); }

    CONSTEXPR void set_fs_access_rights(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_fs_access_rights(val); }

    CONSTEXPR vmcs_field32_t gs_access_rights() const
    { return impl<const IMPL>(this)->__gs_access_rights(); }

    CONSTEXPR void set_gs_access_rights(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_gs_access_rights(val); }

    CONSTEXPR vmcs_field32_t ldtr_access_rights() const
    { return impl<const IMPL>(this)->__ldtr_access_rights(); }

    CONSTEXPR void set_ldtr_access_rights(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_ldtr_access_rights(val); }

    CONSTEXPR vmcs_field32_t tr_access_rights() const
    { return impl<const IMPL>(this)->__tr_access_rights(); }

    CONSTEXPR void set_tr_access_rights(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_tr_access_rights(val); }

    CONSTEXPR vmcs_field32_t interuptability_state() const
    { return impl<const IMPL>(this)->__interuptability_state(); }

    CONSTEXPR void set_interuptability_state(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_interuptability_state(val); }

    CONSTEXPR vmcs_field32_t activity_state() const
    { return impl<const IMPL>(this)->__activity_state(); }

    CONSTEXPR void set_activity_state(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_activity_state(val); }

    CONSTEXPR vmcs_field32_t ia32_sysenter_cs() const
    { return impl<const IMPL>(this)->__ia32_sysenter_cs(); }

    CONSTEXPR void set_ia32_sysenter_cs(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_ia32_sysenter_cs(val); }

    CONSTEXPR vmcs_field32_t preemption_timer_value() const
    { return impl<const IMPL>(this)->__preemption_timer_value(); }

    CONSTEXPR void set_preemption_timer_value(vmcs_field32_t val)
    { impl<IMPL>(this)->__set_preemption_timer_value(val); }

    CONSTEXPR vmcs_field64_t cr0_mask() const
    { return impl<const IMPL>(this)->__cr0_mask(); }

    CONSTEXPR void set_cr0_mask(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr0_mask(val); }

    CONSTEXPR vmcs_field64_t cr4_mask() const
    { return impl<const IMPL>(this)->__cr4_mask(); }

    CONSTEXPR void set_cr4_mask(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr4_mask(val); }

    CONSTEXPR vmcs_field64_t cr0_read_shadow() const
    { return impl<const IMPL>(this)->__cr0_read_shadow(); }

    CONSTEXPR void set_cr0_read_shadow(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr0_read_shadow(val); }

    CONSTEXPR vmcs_field64_t cr4_read_shadow() const
    { return impl<const IMPL>(this)->__cr4_read_shadow(); }

    CONSTEXPR void set_cr4_read_shadow(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr4_read_shadow(val); }

    CONSTEXPR vmcs_field64_t cr3_target0() const
    { return impl<const IMPL>(this)->__cr3_target0(); }

    CONSTEXPR void set_cr3_target0(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr3_target0(val); }

    CONSTEXPR vmcs_field64_t cr3_target1() const
    { return impl<const IMPL>(this)->__cr3_target1(); }

    CONSTEXPR void set_cr3_target1(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr3_target1(val); }

    CONSTEXPR vmcs_field64_t cr3_target2() const
    { return impl<const IMPL>(this)->__cr3_target2(); }

    CONSTEXPR void set_cr3_target2(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr3_target2(val); }

    CONSTEXPR vmcs_field64_t cr3_target3() const
    { return impl<const IMPL>(this)->__cr3_target3(); }

    CONSTEXPR void set_cr3_target3(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr3_target3(val); }

    CONSTEXPR vmcs_field64_t exit_qualification() const
    { return impl<const IMPL>(this)->__exit_qualification(); }

    CONSTEXPR vmcs_field64_t io_rcx() const
    { return impl<const IMPL>(this)->__io_rcx(); }

    CONSTEXPR vmcs_field64_t io_rsi() const
    { return impl<const IMPL>(this)->__io_rsi(); }

    CONSTEXPR vmcs_field64_t io_rdi() const
    { return impl<const IMPL>(this)->__io_rdi(); }

    CONSTEXPR vmcs_field64_t io_rip() const
    { return impl<const IMPL>(this)->__io_rip(); }

    CONSTEXPR vmcs_field64_t gva() const
    { return impl<const IMPL>(this)->__gva(); }

    CONSTEXPR vmcs_field64_t cr0() const
    { return impl<const IMPL>(this)->__cr0(); }

    CONSTEXPR void set_cr0(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr0(val); }

    CONSTEXPR vmcs_field64_t cr3() const
    { return impl<const IMPL>(this)->__cr3(); }

    CONSTEXPR void set_cr3(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr3(val); }

    CONSTEXPR vmcs_field64_t cr4() const
    { return impl<const IMPL>(this)->__cr4(); }

    CONSTEXPR void set_cr4(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cr4(val); }

    CONSTEXPR vmcs_field64_t es_base() const
    { return impl<const IMPL>(this)->__es_base(); }

    CONSTEXPR void set_es_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_es_base(val); }

    CONSTEXPR vmcs_field64_t cs_base() const
    { return impl<const IMPL>(this)->__cs_base(); }

    CONSTEXPR void set_cs_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_cs_base(val); }

    CONSTEXPR vmcs_field64_t ss_base() const
    { return impl<const IMPL>(this)->__ss_base(); }

    CONSTEXPR void set_ss_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_ss_base(val); }

    CONSTEXPR vmcs_field64_t ds_base() const
    { return impl<const IMPL>(this)->__ds_base(); }

    CONSTEXPR void set_ds_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_ds_base(val); }

    CONSTEXPR vmcs_field64_t fs_base() const
    { return impl<const IMPL>(this)->__fs_base(); }

    CONSTEXPR void set_fs_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_fs_base(val); }

    CONSTEXPR vmcs_field64_t gs_base() const
    { return impl<const IMPL>(this)->__gs_base(); }

    CONSTEXPR void set_gs_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_gs_base(val); }

    CONSTEXPR vmcs_field64_t ldtr_base() const
    { return impl<const IMPL>(this)->__ldtr_base(); }

    CONSTEXPR void set_ldtr_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_ldtr_base(val); }

    CONSTEXPR vmcs_field64_t tr_base() const
    { return impl<const IMPL>(this)->__tr_base(); }

    CONSTEXPR void set_tr_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_tr_base(val); }

    CONSTEXPR vmcs_field64_t gdtr_base() const
    { return impl<const IMPL>(this)->__gdtr_base(); }

    CONSTEXPR void set_gdtr_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_gdtr_base(val); }

    CONSTEXPR vmcs_field64_t idtr_base() const
    { return impl<const IMPL>(this)->__idtr_base(); }

    CONSTEXPR void set_idtr_base(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_idtr_base(val); }

    CONSTEXPR vmcs_field64_t dr7() const
    { return impl<const IMPL>(this)->__dr7(); }

    CONSTEXPR void set_dr7(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_dr7(val); }

    CONSTEXPR vmcs_field64_t rflags() const
    { return impl<const IMPL>(this)->__rflags(); }

    CONSTEXPR void set_rflags(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_rflags(val); }

    CONSTEXPR vmcs_field64_t pending_debug_exceptions() const
    { return impl<const IMPL>(this)->__pending_debug_exceptions(); }

    CONSTEXPR void set_pending_debug_exceptions(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_pending_debug_exceptions(val); }

    CONSTEXPR vmcs_field64_t ia32_sysenter_esp() const
    { return impl<const IMPL>(this)->__ia32_sysenter_esp(); }

    CONSTEXPR void set_ia32_sysenter_esp(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_ia32_sysenter_esp(val); }

    CONSTEXPR vmcs_field64_t ia32_sysenter_eip() const
    { return impl<const IMPL>(this)->__ia32_sysenter_eip(); }

    CONSTEXPR void set_ia32_sysenter_eip(vmcs_field64_t val)
    { impl<IMPL>(this)->__set_ia32_sysenter_eip(val); }

    /// @endcond
};

}

// -----------------------------------------------------------------------------
// Wrappers
// -----------------------------------------------------------------------------

/// @cond

namespace bfvmm::intel_x64::vmcs
{

template<typename IMPL>
constexpr void vmcs_run(
    gsl::not_null<IMPL *> vcpu)
{ vcpu->vmcs_run(); }

template<typename IMPL>
constexpr auto vmcs_advance(
    gsl::not_null<IMPL *> vcpu)
{ return vcpu->vmcs_advance(); }

template<typename IMPL>
constexpr void vmcs_load(
    gsl::not_null<IMPL *> vcpu)
{ vcpu->vmcs_load(); }

template<typename IMPL>
constexpr void vmcs_clear(
    gsl::not_null<IMPL *> vcpu)
{ vcpu->vmcs_clear(); }

template<typename IMPL>
constexpr auto vmcs_check(
    gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->vmcs_check(); }

template<typename IMPL, typename... Args>
constexpr void vmcs_add_vmlaunch_delegate(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->vmcs_add_vmlaunch_delegate(std::forward<Args>(args)...); }

template<typename IMPL, typename... Args>
constexpr void vmcs_add_vmresume_delegate(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->vmcs_add_vmresume_delegate(std::forward<Args>(args)...); }

template<typename IMPL, typename... Args>
constexpr void vmcs_add_vmload_delegate(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->vmcs_add_vmload_delegate(std::forward<Args>(args)...); }

template<typename IMPL, typename... Args>
constexpr void vmcs_add_vmclear_delegate(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->vmcs_add_vmclear_delegate(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vpid(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vpid(); }

template<typename IMPL, typename... Args>
constexpr void set_vpid(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vpid(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto posted_interrupt_notification_vector(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->posted_interrupt_notification_vector(); }

template<typename IMPL, typename... Args>
constexpr void set_posted_interrupt_notification_vector(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_posted_interrupt_notification_vector(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto es_selector(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->es_selector(); }

template<typename IMPL, typename... Args>
constexpr void set_es_selector(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_es_selector(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cs_selector(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cs_selector(); }

template<typename IMPL, typename... Args>
constexpr void set_cs_selector(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cs_selector(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ss_selector(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ss_selector(); }

template<typename IMPL, typename... Args>
constexpr void set_ss_selector(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ss_selector(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ds_selector(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ds_selector(); }

template<typename IMPL, typename... Args>
constexpr void set_ds_selector(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ds_selector(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto fs_selector(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->fs_selector(); }

template<typename IMPL, typename... Args>
constexpr void set_fs_selector(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_fs_selector(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto gs_selector(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->gs_selector(); }

template<typename IMPL, typename... Args>
constexpr void set_gs_selector(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_gs_selector(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ldtr_selector(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ldtr_selector(); }

template<typename IMPL, typename... Args>
constexpr void set_ldtr_selector(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ldtr_selector(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto tr_selector(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->tr_selector(); }

template<typename IMPL, typename... Args>
constexpr void set_tr_selector(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_tr_selector(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto interrupt_status(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->interrupt_status(); }

template<typename IMPL, typename... Args>
constexpr void set_interrupt_status(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_interrupt_status(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pml_index(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pml_index(); }

template<typename IMPL, typename... Args>
constexpr void set_pml_index(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pml_index(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto io_bitmap_a_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->io_bitmap_a_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_io_bitmap_a_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_io_bitmap_a_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto io_bitmap_b_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->io_bitmap_b_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_io_bitmap_b_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_io_bitmap_b_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto msr_bitmaps_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->msr_bitmaps_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_msr_bitmaps_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_msr_bitmaps_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmexit_msr_store_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmexit_msr_store_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_vmexit_msr_store_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmexit_msr_store_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmexit_msr_load_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmexit_msr_load_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_vmexit_msr_load_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmexit_msr_load_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pml_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pml_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_pml_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pml_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto tsc_offset(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->tsc_offset(); }

template<typename IMPL, typename... Args>
constexpr void set_tsc_offset(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_tsc_offset(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vapic_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vapic_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_vapic_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vapic_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto apic_access_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->apic_access_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_apic_access_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_apic_access_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto posted_interrupt_descriptor_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->posted_interrupt_descriptor_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_posted_interrupt_descriptor_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_posted_interrupt_descriptor_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vm_function_ctls(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vm_function_ctls(); }

template<typename IMPL, typename... Args>
constexpr void set_vm_function_ctls(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vm_function_ctls(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto eptp(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->eptp(); }

template<typename IMPL, typename... Args>
constexpr void set_eptp(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_eptp(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto eoi_exit_bitmap_0(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->eoi_exit_bitmap_0(); }

template<typename IMPL, typename... Args>
constexpr void set_eoi_exit_bitmap_0(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_eoi_exit_bitmap_0(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto eoi_exit_bitmap_1(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->eoi_exit_bitmap_1(); }

template<typename IMPL, typename... Args>
constexpr void set_eoi_exit_bitmap_1(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_eoi_exit_bitmap_1(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto eoi_exit_bitmap_2(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->eoi_exit_bitmap_2(); }

template<typename IMPL, typename... Args>
constexpr void set_eoi_exit_bitmap_2(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_eoi_exit_bitmap_2(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto eoi_exit_bitmap_3(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->eoi_exit_bitmap_3(); }

template<typename IMPL, typename... Args>
constexpr void set_eoi_exit_bitmap_3(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_eoi_exit_bitmap_3(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto eptp_list_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->eptp_list_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_eptp_list_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_eptp_list_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vexception_info_addr(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vexception_info_addr(); }

template<typename IMPL, typename... Args>
constexpr void set_vexception_info_addr(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vexception_info_addr(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto xss_exiting_bitmap(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->xss_exiting_bitmap(); }

template<typename IMPL, typename... Args>
constexpr void set_xss_exiting_bitmap(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_xss_exiting_bitmap(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto tsc_multiplier(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->tsc_multiplier(); }

template<typename IMPL, typename... Args>
constexpr void set_tsc_multiplier(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_tsc_multiplier(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto gpa(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->gpa(); }

template<typename IMPL>
constexpr auto ia32_debugctl(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ia32_debugctl(); }

template<typename IMPL, typename... Args>
constexpr void set_ia32_debugctl(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ia32_debugctl(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ia32_pat(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ia32_pat(); }

template<typename IMPL, typename... Args>
constexpr void set_ia32_pat(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ia32_pat(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ia32_efer(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ia32_efer(); }

template<typename IMPL, typename... Args>
constexpr void set_ia32_efer(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ia32_efer(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ia32_perf_global_ctrl(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ia32_perf_global_ctrl(); }

template<typename IMPL, typename... Args>
constexpr void set_ia32_perf_global_ctrl(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ia32_perf_global_ctrl(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pdpte0(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pdpte0(); }

template<typename IMPL, typename... Args>
constexpr void set_pdpte0(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pdpte0(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pdpte1(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pdpte1(); }

template<typename IMPL, typename... Args>
constexpr void set_pdpte1(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pdpte1(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pdpte2(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pdpte2(); }

template<typename IMPL, typename... Args>
constexpr void set_pdpte2(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pdpte2(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pdpte3(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pdpte3(); }

template<typename IMPL, typename... Args>
constexpr void set_pdpte3(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pdpte3(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pin_based_ctls(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pin_based_ctls(); }

template<typename IMPL, typename... Args>
constexpr void set_pin_based_ctls(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pin_based_ctls(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto proc_based_ctls(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->proc_based_ctls(); }

template<typename IMPL, typename... Args>
constexpr void set_proc_based_ctls(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_proc_based_ctls(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto exception_bitmap(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->exception_bitmap(); }

template<typename IMPL, typename... Args>
constexpr void set_exception_bitmap(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_exception_bitmap(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pf_error_code_mask(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pf_error_code_mask(); }

template<typename IMPL, typename... Args>
constexpr void set_pf_error_code_mask(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pf_error_code_mask(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pf_error_code_match(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pf_error_code_match(); }

template<typename IMPL, typename... Args>
constexpr void set_pf_error_code_match(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pf_error_code_match(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr3_target_count(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr3_target_count(); }

template<typename IMPL, typename... Args>
constexpr void set_cr3_target_count(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr3_target_count(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmexit_ctls(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmexit_ctls(); }

template<typename IMPL, typename... Args>
constexpr void set_vmexit_ctls(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmexit_ctls(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmexit_msr_store_count(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmexit_msr_store_count(); }

template<typename IMPL, typename... Args>
constexpr void set_vmexit_msr_store_count(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmexit_msr_store_count(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmexit_load_count(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmexit_load_count(); }

template<typename IMPL, typename... Args>
constexpr void set_vmexit_load_count(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmexit_load_count(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmentry_ctls(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmentry_ctls(); }

template<typename IMPL, typename... Args>
constexpr void set_vmentry_ctls(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmentry_ctls(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmentry_msr_load_count(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmentry_msr_load_count(); }

template<typename IMPL, typename... Args>
constexpr void set_vmentry_msr_load_count(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmentry_msr_load_count(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmentry_int_info(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmentry_int_info(); }

template<typename IMPL, typename... Args>
constexpr void set_vmentry_int_info(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmentry_int_info(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmentry_exception_error_code(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmentry_exception_error_code(); }

template<typename IMPL, typename... Args>
constexpr void set_vmentry_exception_error_code(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmentry_exception_error_code(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vmentry_instr_len(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmentry_instr_len(); }

template<typename IMPL, typename... Args>
constexpr void set_vmentry_instr_len(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_vmentry_instr_len(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto tpr_threshold(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->tpr_threshold(); }

template<typename IMPL, typename... Args>
constexpr void set_tpr_threshold(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_tpr_threshold(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto proc_based_ctls2(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->proc_based_ctls2(); }

template<typename IMPL, typename... Args>
constexpr void set_proc_based_ctls2(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_proc_based_ctls2(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ple_gap(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ple_gap(); }

template<typename IMPL, typename... Args>
constexpr void set_ple_gap(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ple_gap(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ple_window(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ple_window(); }

template<typename IMPL, typename... Args>
constexpr void set_ple_window(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ple_window(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto vm_instr_error(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vm_instr_error(); }

template<typename IMPL>
constexpr auto vmexit_int_info(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmexit_int_info(); }

template<typename IMPL>
constexpr auto vmexit_int_error_code(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmexit_int_error_code(); }

template<typename IMPL>
constexpr auto idt_vectoring_info(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->idt_vectoring_info(); }

template<typename IMPL>
constexpr auto idt_vectoring_error_code(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->idt_vectoring_error_code(); }

template<typename IMPL>
constexpr auto vmexit_instr_len(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmexit_instr_len(); }

template<typename IMPL>
constexpr auto vmexit_instr_info(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->vmexit_instr_info(); }

template<typename IMPL>
constexpr auto es_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->es_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_es_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_es_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cs_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cs_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_cs_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cs_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ss_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ss_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_ss_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ss_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ds_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ds_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_ds_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ds_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto fs_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->fs_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_fs_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_fs_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto gs_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->gs_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_gs_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_gs_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ldtr_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ldtr_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_ldtr_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ldtr_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto tr_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->tr_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_tr_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_tr_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto gdtr_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->gdtr_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_gdtr_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_gdtr_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto idtr_limit(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->idtr_limit(); }

template<typename IMPL, typename... Args>
constexpr void set_idtr_limit(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_idtr_limit(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto es_access_rights(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->es_access_rights(); }

template<typename IMPL, typename... Args>
constexpr void set_es_access_rights(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_es_access_rights(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cs_access_rights(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cs_access_rights(); }

template<typename IMPL, typename... Args>
constexpr void set_cs_access_rights(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cs_access_rights(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ss_access_rights(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ss_access_rights(); }

template<typename IMPL, typename... Args>
constexpr void set_ss_access_rights(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ss_access_rights(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ds_access_rights(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ds_access_rights(); }

template<typename IMPL, typename... Args>
constexpr void set_ds_access_rights(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ds_access_rights(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto fs_access_rights(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->fs_access_rights(); }

template<typename IMPL, typename... Args>
constexpr void set_fs_access_rights(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_fs_access_rights(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto gs_access_rights(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->gs_access_rights(); }

template<typename IMPL, typename... Args>
constexpr void set_gs_access_rights(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_gs_access_rights(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ldtr_access_rights(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ldtr_access_rights(); }

template<typename IMPL, typename... Args>
constexpr void set_ldtr_access_rights(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ldtr_access_rights(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto tr_access_rights(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->tr_access_rights(); }

template<typename IMPL, typename... Args>
constexpr void set_tr_access_rights(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_tr_access_rights(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto interuptability_state(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->interuptability_state(); }

template<typename IMPL, typename... Args>
constexpr void set_interuptability_state(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_interuptability_state(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto activity_state(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->activity_state(); }

template<typename IMPL, typename... Args>
constexpr void set_activity_state(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_activity_state(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ia32_sysenter_cs(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ia32_sysenter_cs(); }

template<typename IMPL, typename... Args>
constexpr void set_ia32_sysenter_cs(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ia32_sysenter_cs(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto preemption_timer_value(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->preemption_timer_value(); }

template<typename IMPL, typename... Args>
constexpr void set_preemption_timer_value(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_preemption_timer_value(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr0_mask(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr0_mask(); }

template<typename IMPL, typename... Args>
constexpr void set_cr0_mask(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr0_mask(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr4_mask(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr4_mask(); }

template<typename IMPL, typename... Args>
constexpr void set_cr4_mask(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr4_mask(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr0_read_shadow(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr0_read_shadow(); }

template<typename IMPL, typename... Args>
constexpr void set_cr0_read_shadow(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr0_read_shadow(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr4_read_shadow(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr4_read_shadow(); }

template<typename IMPL, typename... Args>
constexpr void set_cr4_read_shadow(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr4_read_shadow(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr3_target0(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr3_target0(); }

template<typename IMPL, typename... Args>
constexpr void set_cr3_target0(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr3_target0(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr3_target1(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr3_target1(); }

template<typename IMPL, typename... Args>
constexpr void set_cr3_target1(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr3_target1(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr3_target2(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr3_target2(); }

template<typename IMPL, typename... Args>
constexpr void set_cr3_target2(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr3_target2(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr3_target3(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr3_target3(); }

template<typename IMPL, typename... Args>
constexpr void set_cr3_target3(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr3_target3(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto exit_qualification(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->exit_qualification(); }

template<typename IMPL>
constexpr auto io_rcx(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->io_rcx(); }

template<typename IMPL>
constexpr auto io_rsi(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->io_rsi(); }

template<typename IMPL>
constexpr auto io_rdi(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->io_rdi(); }

template<typename IMPL>
constexpr auto io_rip(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->io_rip(); }

template<typename IMPL>
constexpr auto gva(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->gva(); }

template<typename IMPL>
constexpr auto cr0(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr0(); }

template<typename IMPL, typename... Args>
constexpr void set_cr0(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr0(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr3(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr3(); }

template<typename IMPL, typename... Args>
constexpr void set_cr3(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr3(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cr4(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cr4(); }

template<typename IMPL, typename... Args>
constexpr void set_cr4(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cr4(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto es_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->es_base(); }

template<typename IMPL, typename... Args>
constexpr void set_es_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_es_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto cs_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->cs_base(); }

template<typename IMPL, typename... Args>
constexpr void set_cs_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_cs_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ss_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ss_base(); }

template<typename IMPL, typename... Args>
constexpr void set_ss_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ss_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ds_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ds_base(); }

template<typename IMPL, typename... Args>
constexpr void set_ds_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ds_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto fs_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->fs_base(); }

template<typename IMPL, typename... Args>
constexpr void set_fs_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_fs_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto gs_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->gs_base(); }

template<typename IMPL, typename... Args>
constexpr void set_gs_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_gs_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ldtr_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ldtr_base(); }

template<typename IMPL, typename... Args>
constexpr void set_ldtr_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ldtr_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto tr_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->tr_base(); }

template<typename IMPL, typename... Args>
constexpr void set_tr_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_tr_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto gdtr_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->gdtr_base(); }

template<typename IMPL, typename... Args>
constexpr void set_gdtr_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_gdtr_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto idtr_base(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->idtr_base(); }

template<typename IMPL, typename... Args>
constexpr void set_idtr_base(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_idtr_base(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto dr7(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->dr7(); }

template<typename IMPL, typename... Args>
constexpr void set_dr7(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_dr7(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto rflags(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->rflags(); }

template<typename IMPL, typename... Args>
constexpr void set_rflags(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_rflags(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto pending_debug_exceptions(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->pending_debug_exceptions(); }

template<typename IMPL, typename... Args>
constexpr void set_pending_debug_exceptions(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_pending_debug_exceptions(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ia32_sysenter_esp(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ia32_sysenter_esp(); }

template<typename IMPL, typename... Args>
constexpr void set_ia32_sysenter_esp(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ia32_sysenter_esp(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ia32_sysenter_eip(
    gsl::not_null<const IMPL *> vcpu)
{ return vcpu->ia32_sysenter_eip(); }

template<typename IMPL, typename... Args>
constexpr void set_ia32_sysenter_eip(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->set_ia32_sysenter_eip(std::forward<Args>(args)...); }

}

/// @endcond

#endif
