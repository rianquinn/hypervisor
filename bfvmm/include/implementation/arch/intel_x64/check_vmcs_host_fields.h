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

#ifndef IMPLEMENTATION_CHECK_VMCS_HOST_INTEL_X64_H
#define IMPLEMENTATION_CHECK_VMCS_HOST_INTEL_X64_H

namespace bfvmm::implementation::intel_x64::check
{

void host_cr0_for_unsupported_bits();
void host_cr4_for_unsupported_bits();
void host_cr3_for_unsupported_bits();
void host_ia32_sysenter_esp_canonical_addr();
void host_ia32_sysenter_eip_canonical_addr();
void host_verify_load_ia32_perf_global_ctrl();
void host_verify_load_ia32_pat();
void host_verify_load_ia32_efer();
void host_es_selector_rpl_ti_equal_zero();
void host_cs_selector_rpl_ti_equal_zero();
void host_ss_selector_rpl_ti_equal_zero();
void host_ds_selector_rpl_ti_equal_zero();
void host_fs_selector_rpl_ti_equal_zero();
void host_gs_selector_rpl_ti_equal_zero();
void host_tr_selector_rpl_ti_equal_zero();
void host_cs_not_equal_zero();
void host_tr_not_equal_zero();
void host_ss_not_equal_zero();
void host_fs_canonical_base_addr();
void host_gs_canonical_base_addr();
void host_gdtr_canonical_base_addr();
void host_idtr_canonical_base_addr();
void host_tr_canonical_base_addr();
void host_if_outside_ia32e_mode();
void host_addr_space_size_exit_ctl_is_set();
void host_addr_space_disabled();
void host_addr_space_enabled();

}

#endif
