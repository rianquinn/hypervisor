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

#ifndef IMPLEMENTATION_VMCS_INTEL_X64_H
#define IMPLEMENTATION_VMCS_INTEL_X64_H

#include <list>

#include "../../macros.h"

#include "../../../uapis/unique_page.h"
#include "../../../uapis/arch/intel_x64/vmcs.h"

// -----------------------------------------------------------------------------
// Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::implementation::intel_x64
{

class vmcs :
    public uapis::intel_x64::vmcs<vmcs>
{
PUBLIC:
    explicit vmcs();
    VIRTUAL ~vmcs();

PRIVATE:
    void demote();
    void promote();

    void check() const noexcept;
    void launch();
    void resume();

PRIVATE:
    void __arch_run();
    bool __arch_advance_ip();
    void __arch_load();
    void __arch_clear();

PRIVATE:
    void __vmcs_add_vmlaunch_delegate(const vmcs_delegate_t &d);
    void __vmcs_add_vmresume_delegate(const vmcs_delegate_t &d);
    void __vmcs_add_vmload_delegate(const vmcs_delegate_t &d);
    void __vmcs_add_vmclear_delegate(const vmcs_delegate_t &d);

PRIVATE:
    vmcs_field16_t __virtual_processor_identifier() const;
    void __set_virtual_processor_identifier(vmcs_field16_t val);

    vmcs_field16_t __posted_int_notification_vector() const;
    void __set_posted_int_notification_vector(vmcs_field16_t val);

    vmcs_field16_t __eptp_index() const;
    void __set_eptp_index(vmcs_field16_t val);

PRIVATE:
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

    vmcs_field16_t __int_status() const;
    void __set_int_status(vmcs_field16_t val);

    vmcs_field16_t __pml_index() const;
    void __set_pml_index(vmcs_field16_t val);

PRIVATE:
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

    vmcs_field64_t __vmentry_msr_load_addr() const;
    void __set_vmentry_msr_load_addr(vmcs_field64_t val);

    vmcs_field64_t __executive_vmcs_ptr() const;
    void __set_executive_vmcs_ptr(vmcs_field64_t val);

    vmcs_field64_t __pml_addr() const;
    void __set_pml_addr(vmcs_field64_t val);

    vmcs_field64_t __tsc_offset() const;
    void __set_tsc_offset(vmcs_field64_t val);

    vmcs_field64_t __virtual_apic_addr() const;
    void __set_virtual_apic_addr(vmcs_field64_t val);

    vmcs_field64_t __apic_access_addr() const;
    void __set_apic_access_addr(vmcs_field64_t val);

    vmcs_field64_t __posted_int_descriptor_addr() const;
    void __set_posted_int_descriptor_addr(vmcs_field64_t val);

    vmcs_field64_t __vm_function_ctls() const;
    void __set_vm_function_ctls(vmcs_field64_t val);

    vmcs_field64_t __ept_ptr() const;
    void __set_ept_ptr(vmcs_field64_t val);

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

    vmcs_field64_t __vmread_bitmap_addr() const;
    void __set_vmread_bitmap_addr(vmcs_field64_t val);

    vmcs_field64_t __vmwrite_bitmap_addr() const;
    void __set_vmwrite_bitmap_addr(vmcs_field64_t val);

    vmcs_field64_t __virtualization_exception_info_addr() const;
    void __set_virtualization_exception_info_addr(vmcs_field64_t val);

    vmcs_field64_t __encls_exiting_bitmap() const;
    void __set_encls_exiting_bitmap(vmcs_field64_t val);

    vmcs_field64_t __xss_exiting_bitmap() const;
    void __set_xss_exiting_bitmap(vmcs_field64_t val);

    vmcs_field64_t __tsc_multiplier() const;
    void __set_tsc_multiplier(vmcs_field64_t val);

PRIVATE:
    vmcs_field64_t __gpa() const;

PRIVATE:
    vmcs_field64_t __vmcs_link_ptr() const;
    void __set_vmcs_link_ptr(vmcs_field64_t val);

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

    vmcs_field64_t __ia32_bndcfgs() const;
    void __set_ia32_bndcfgs(vmcs_field64_t val);

PRIVATE:
    vmcs_field32_t __pin_based_vm_execution_ctls() const;
    void __set_pin_based_vm_execution_ctls(vmcs_field32_t val);

    vmcs_field32_t __processor_based_vm_execution_ctls() const;
    void __set_processor_based_vm_execution_ctls(vmcs_field32_t val);

    vmcs_field32_t __exception_bitmap() const;
    void __set_exception_bitmap(vmcs_field32_t val);

    vmcs_field32_t __page_fault_error_code_mask() const;
    void __set_page_fault_error_code_mask(vmcs_field32_t val);

    vmcs_field32_t __page_fault_error_code_match() const;
    void __set_page_fault_error_code_match(vmcs_field32_t val);

    vmcs_field32_t __cr3_target_count() const;
    void __set_cr3_target_count(vmcs_field32_t val);

    vmcs_field32_t __vmexit_ctls() const;
    void __set_vmexit_ctls(vmcs_field32_t val);

    vmcs_field32_t __vmexit_msr_store_count() const;
    void __set_vmexit_msr_store_count(vmcs_field32_t val);

    vmcs_field32_t __vmexit_msr_load_count() const;
    void __set_vmexit_msr_load_count(vmcs_field32_t val);

    vmcs_field32_t __vmentry_ctls() const;
    void __set_vmentry_ctls(vmcs_field32_t val);

    vmcs_field32_t __vmentry_msr_load_count() const;
    void __set_vmentry_msr_load_count(vmcs_field32_t val);

    vmcs_field32_t __vmentry_interruption_info() const;
    void __set_vmentry_interruption_info(vmcs_field32_t val);

    vmcs_field32_t __vmentry_exception_error_code() const;
    void __set_vmentry_exception_error_code(vmcs_field32_t val);

    vmcs_field32_t __vmentry_instr_len() const;
    void __set_vmentry_instr_len(vmcs_field32_t val);

    vmcs_field32_t __tpr_threshold() const;
    void __set_tpr_threshold(vmcs_field32_t val);

    vmcs_field32_t __processor_based_vm_execution_ctls2() const;
    void __set_processor_based_vm_execution_ctls2(vmcs_field32_t val);

    vmcs_field32_t __ple_gap() const;
    void __set_ple_gap(vmcs_field32_t val);

    vmcs_field32_t __ple_window() const;
    void __set_ple_window(vmcs_field32_t val);

PRIVATE:
    vmcs_field32_t __vm_instr_error() const;
    vmcs_field32_t __vmexit_int_info() const;
    vmcs_field32_t __vmexit_int_error_code() const;
    vmcs_field32_t __idt_vectoring_info() const;
    vmcs_field32_t __idt_vectoring_error_code() const;
    vmcs_field32_t __vmexit_instr_len() const;
    vmcs_field32_t __vmexit_instr_info() const;

PRIVATE:
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

    vmcs_field32_t __smbase() const;
    void __set_smbase(vmcs_field32_t val);

    vmcs_field32_t __ia32_sysenter_cs() const;
    void __set_ia32_sysenter_cs(vmcs_field32_t val);

    vmcs_field32_t __preemption_timer_value() const;
    void __set_preemption_timer_value(vmcs_field32_t val);

PRIVATE:
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

PRIVATE:
    vmcs_field64_t __exit_qualification() const;
    vmcs_field64_t __io_rcx() const;
    vmcs_field64_t __io_rsi() const;
    vmcs_field64_t __io_rdi() const;
    vmcs_field64_t __io_rip() const;
    vmcs_field64_t __gva() const;

PRIVATE:
    vmcs_field64_t __cr0() const;
    void __set_cr0(vmcs_field64_t val);

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

    vmcs_field64_t __rsp() const;
    void __set_rsp(vmcs_field64_t val);

    vmcs_field64_t __rip() const;
    void __set_rip(vmcs_field64_t val);

    vmcs_field64_t __rflags() const;
    void __set_rflags(vmcs_field64_t val);

    vmcs_field64_t __pending_debug_exceptions() const;
    void __set_pending_debug_exceptions(vmcs_field64_t val);

    vmcs_field64_t __ia32_sysenter_esp() const;
    void __set_ia32_sysenter_esp(vmcs_field64_t val);

    vmcs_field64_t __ia32_sysenter_eip() const;
    void __set_ia32_sysenter_eip(vmcs_field64_t val);

PRIVATE:
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

PRIVATE:
    bool m_launched{false};
    unique_page<uint32_t> m_vmcs_region{};

    std::list<vmcs_delegate_t> m_vmlaunch_delegates{};
    std::list<vmcs_delegate_t> m_vmresume_delegates{};
    std::list<vmcs_delegate_t> m_vmload_delegates{};
    std::list<vmcs_delegate_t> m_vmclear_delegates{};

PRIVATE:
    MOCK_PROTOTYPE(vmcs)
    COPY_MOVE_SEMANTICS(vmcs)

PRIVATE:
    template<typename T>
    friend struct uapis::intel_x64::vmcs;

    friend class state;
    friend class ::private_entry;
};

}

#endif
