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

#ifndef VMCS_INTEL_X64_DEBUG_H
#define VMCS_INTEL_X64_DEBUG_H

#include "16bit_control_fields.h"
#include "16bit_guest_state_fields.h"
#include "16bit_host_state_fields.h"
#include "32bit_control_fields.h"
#include "32bit_guest_state_fields.h"
#include "32bit_host_state_fields.h"
#include "32bit_read_only_data_fields.h"
#include "64bit_control_fields.h"
#include "64bit_guest_state_fields.h"
#include "64bit_host_state_fields.h"
#include "64bit_read_only_data_fields.h"
#include "natural_width_control_fields.h"
#include "natural_width_guest_state_fields.h"
#include "natural_width_host_state_fields.h"
#include "natural_width_read_only_data_fields.h"

// *INDENT-OFF*

namespace intel_x64::vmcs
{

inline void dump(int level = 0)
{
    bfdebug_transaction(level, [&](std::string * msg) {
        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "16bit ctl fields", msg);
        bfdebug_brk3(level, msg);

        virtual_processor_identifier::dump(level, msg);
        posted_int_notification_vector::dump(level, msg);
        eptp_index::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "16bit guest state fields", msg);
        bfdebug_brk3(level, msg);

        guest_es_selector::dump(level, msg);
        guest_cs_selector::dump(level, msg);
        guest_ss_selector::dump(level, msg);
        guest_ds_selector::dump(level, msg);
        guest_fs_selector::dump(level, msg);
        guest_gs_selector::dump(level, msg);
        guest_ldtr_selector::dump(level, msg);
        guest_tr_selector::dump(level, msg);
        guest_int_status::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "16bit host state fields", msg);
        bfdebug_brk3(level, msg);

        host_es_selector::dump(level, msg);
        host_cs_selector::dump(level, msg);
        host_ss_selector::dump(level, msg);
        host_ds_selector::dump(level, msg);
        host_fs_selector::dump(level, msg);
        host_gs_selector::dump(level, msg);
        host_tr_selector::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "64bit ctl fields", msg);
        bfdebug_brk3(level, msg);

        io_bitmap_a_addr::dump(level, msg);
        io_bitmap_b_addr::dump(level, msg);
        msr_bitmaps_addr::dump(level, msg);
        vmexit_msr_store_addr::dump(level, msg);
        vmexit_msr_load_addr::dump(level, msg);
        vmentry_msr_load_addr::dump(level, msg);
        executive_vmcs_ptr::dump(level, msg);
        tsc_offset::dump(level, msg);
        virtual_apic_addr::dump(level, msg);
        apic_access_addr::dump(level, msg);
        posted_int_descriptor_addr::dump(level, msg);
        vm_function_ctls::dump(level, msg);
        ept_ptr::dump(level, msg);
        eoi_exit_bitmap_0::dump(level, msg);
        eoi_exit_bitmap_1::dump(level, msg);
        eoi_exit_bitmap_2::dump(level, msg);
        eoi_exit_bitmap_3::dump(level, msg);
        eptp_list_addr::dump(level, msg);
        vmread_bitmap_addr::dump(level, msg);
        vmwrite_bitmap_addr::dump(level, msg);
        virtualization_exception_info_addr::dump(level, msg);
        xss_exiting_bitmap::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "64bit read-only data fields", msg);
        bfdebug_brk3(level, msg);

        guest_physical_addr::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "64bit guest state fields", msg);
        bfdebug_brk3(level, msg);

        vmcs_link_ptr::dump(level, msg);
        guest_ia32_debugctl::dump(level, msg);
        guest_ia32_pat::dump(level, msg);
        guest_ia32_efer::dump(level, msg);
        guest_ia32_perf_global_ctrl::dump(level, msg);
        guest_pdpte0::dump(level, msg);
        guest_pdpte1::dump(level, msg);
        guest_pdpte2::dump(level, msg);
        guest_pdpte3::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "64bit host state fields", msg);
        bfdebug_brk3(level, msg);

        host_ia32_pat::dump(level, msg);
        host_ia32_efer::dump(level, msg);
        host_ia32_perf_global_ctrl::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "32bit ctl fields", msg);
        bfdebug_brk3(level, msg);

        pin_based_vm_execution_ctls::dump(level, msg);
        processor_based_vm_execution_ctls::dump(level, msg);
        exception_bitmap::dump(level, msg);
        page_fault_error_code_mask::dump(level, msg);
        page_fault_error_code_match::dump(level, msg);
        cr3_target_count::dump(level, msg);
        vmexit_ctls::dump(level, msg);
        vmexit_msr_store_count::dump(level, msg);
        vmexit_msr_load_count::dump(level, msg);
        vmentry_ctls::dump(level, msg);
        vmentry_msr_load_count::dump(level, msg);
        vmentry_interruption_info::dump(level, msg);
        vmentry_exception_error_code::dump(level, msg);
        vmentry_instr_len::dump(level, msg);
        tpr_threshold::dump(level, msg);
        processor_based_vm_execution_ctls2::dump(level, msg);
        ple_gap::dump(level, msg);
        ple_window::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "32bit read-only data fields", msg);
        bfdebug_brk3(level, msg);

        exit_reason::dump(level, msg);
        vmexit_interruption_info::dump(level, msg);
        vmexit_interruption_error_code::dump(level, msg);
        idt_vectoring_info::dump(level, msg);
        idt_vectoring_error_code::dump(level, msg);
        vmexit_instr_len::dump(level, msg);
        vmexit_instr_info::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "32bit guest state fields", msg);
        bfdebug_brk3(level, msg);

        guest_es_limit::dump(level, msg);
        guest_cs_limit::dump(level, msg);
        guest_ss_limit::dump(level, msg);
        guest_ds_limit::dump(level, msg);
        guest_fs_limit::dump(level, msg);
        guest_gs_limit::dump(level, msg);
        guest_ldtr_limit::dump(level, msg);
        guest_tr_limit::dump(level, msg);
        guest_gdtr_limit::dump(level, msg);
        guest_idtr_limit::dump(level, msg);
        guest_es_access_rights::dump(level, msg);
        guest_cs_access_rights::dump(level, msg);
        guest_ss_access_rights::dump(level, msg);
        guest_ds_access_rights::dump(level, msg);
        guest_fs_access_rights::dump(level, msg);
        guest_gs_access_rights::dump(level, msg);
        guest_ldtr_access_rights::dump(level, msg);
        guest_tr_access_rights::dump(level, msg);
        guest_interruptibility_state::dump(level, msg);
        guest_activity_state::dump(level, msg);
        guest_smbase::dump(level, msg);
        guest_ia32_sysenter_cs::dump(level, msg);
        preemption_timer_value::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "32bit host state fields", msg);
        bfdebug_brk3(level, msg);

        host_ia32_sysenter_cs::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "natural width ctl fields", msg);
        bfdebug_brk3(level, msg);

        cr0_guest_host_mask::dump(level, msg);
        cr4_guest_host_mask::dump(level, msg);
        cr0_read_shadow::dump(level, msg);
        cr4_read_shadow::dump(level, msg);
        cr3_target0::dump(level, msg);
        cr3_target1::dump(level, msg);
        cr3_target2::dump(level, msg);
        cr3_target3::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "natural width read-only data fields", msg);
        bfdebug_brk3(level, msg);

        exit_qualification::dump(level, msg);
        io_rcx::dump(level, msg);
        io_rsi::dump(level, msg);
        io_rdi::dump(level, msg);
        io_rip::dump(level, msg);
        guest_linear_addr::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "natural width guest state fields", msg);
        bfdebug_brk3(level, msg);

        guest_cr0::dump(level, msg);
        guest_cr3::dump(level, msg);
        guest_cr4::dump(level, msg);
        guest_es_base::dump(level, msg);
        guest_cs_base::dump(level, msg);
        guest_ss_base::dump(level, msg);
        guest_ds_base::dump(level, msg);
        guest_fs_base::dump(level, msg);
        guest_gs_base::dump(level, msg);
        guest_ldtr_base::dump(level, msg);
        guest_tr_base::dump(level, msg);
        guest_gdtr_base::dump(level, msg);
        guest_idtr_base::dump(level, msg);
        guest_dr7::dump(level, msg);
        guest_rsp::dump(level, msg);
        guest_rip::dump(level, msg);
        guest_rflags::dump(level, msg);
        guest_pending_debug_exceptions::dump(level, msg);
        guest_ia32_sysenter_esp::dump(level, msg);
        guest_ia32_sysenter_eip::dump(level, msg);

        bfdebug_lnbr(level, msg);
        bfdebug_info(level, "natural width host state fields", msg);
        bfdebug_brk3(level, msg);

        host_cr0::dump(level, msg);
        host_cr3::dump(level, msg);
        host_cr4::dump(level, msg);
        host_fs_base::dump(level, msg);
        host_gs_base::dump(level, msg);
        host_tr_base::dump(level, msg);
        host_gdtr_base::dump(level, msg);
        host_idtr_base::dump(level, msg);
        host_ia32_sysenter_esp::dump(level, msg);
        host_ia32_sysenter_eip::dump(level, msg);
        host_rsp::dump(level, msg);
        host_rip::dump(level, msg);
    });
}

}

// *INDENT-ON*

#endif
