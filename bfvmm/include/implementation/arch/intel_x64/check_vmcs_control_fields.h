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

#ifndef IMPLEMENTATION_CHECK_VMCS_CONTROLS_INTEL_X64_H
#define IMPLEMENTATION_CHECK_VMCS_CONTROLS_INTEL_X64_H

namespace bfvmm::implementation::intel_x64::check
{

void ctl_pin_based_ctls_reserved_properly_set();
void ctl_proc_based_ctls_reserved_properly_set();
void ctl_proc_based_ctls2_reserved_properly_set();
void ctl_cr3_count_less_then_4();
void ctl_io_bitmap_addr_bits();
void ctl_msr_bitmaps_addr_bits();
void ctl_tpr_shadow_and_virtual_apic();
void ctl_nmi_exiting_and_virtual_nmi();
void ctl_virtual_nmi_and_nmi_window();
void ctl_virtual_apic_addr_bits();
void ctl_x2apic_mode_and_virtual_apic_access();
void ctl_virtual_int_and_external_int();
void ctl_process_posted_int_checks();
void ctl_vpid_checks();
void ctl_enable_ept_checks();
void ctl_enable_pml_checks();
void ctl_unrestricted_guests();
void ctl_enable_vm_functions();
void ctl_enable_vmcs_shadowing();
void ctl_enable_ept_violation_checks();
void ctl_vmexit_ctls_reserved_properly_set();
void ctl_activate_and_save_preemption_timer_must_be_0();
void ctl_exit_msr_store_addr();
void ctl_exit_msr_load_addr();
void ctl_vmentry_ctls_reserved_properly_set();
void ctl_event_injection_type_vector_checks();
void ctl_event_injection_delivery_ec_checks();
void ctl_event_injection_reserved_bits_checks();
void ctl_event_injection_ec_checks();
void ctl_event_injection_instr_len_checks();
void ctl_entry_msr_load_addr();
void ctl_vmexit_ctl_fields_all();

}

#endif
