/// @copyright
/// Copyright (C) 2020 Assured Information Security, Inc.
///
/// @copyright
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// @copyright
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// @copyright
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

#include "../../../../mocks/cpp/bf_syscall_impl.hpp"

#include <bsl/ut.hpp>

namespace syscall
{
    /// <!-- description -->
    ///   @brief Used to execute the actual checks. We put the checks in this
    ///     function so that we can validate the tests both at compile-time
    ///     and at run-time. If a bsl::ut_check fails, the tests will either
    ///     fail fast at run-time, or will produce a compile-time error.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Always returns bsl::exit_success.
    ///
    [[nodiscard]] constexpr auto
    tests() noexcept -> bsl::exit_code
    {
        /// NOTE:
        /// - The impl mock functions should not be used by an extension
        ///   during testing, with the exception of some of the debug and
        ///   possibly control APIs. Non of these functions actually do
        ///   anything, so all we have to do is execute them to check the
        ///   "yes, they have been tested" box.
        ///

        bsl::ut_scenario{"bf_tls_rax_impl/bf_tls_set_rax_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_rax_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_rax_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbx_impl/bf_tls_set_rbx_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_rbx_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_rbx_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rcx_impl/bf_tls_set_rcx_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_rcx_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_rcx_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdx_impl/bf_tls_set_rdx_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_rdx_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_rdx_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbp_impl/bf_tls_set_rbp_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_rbp_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_rbp_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rsi_impl/bf_tls_set_rsi_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_rsi_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_rsi_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdi_impl/bf_tls_set_rdi_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_rdi_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_rdi_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r8_impl/bf_tls_set_r8_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_r8_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_r8_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r9_impl/bf_tls_set_r9_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_r9_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_r9_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r10_impl/bf_tls_set_r10_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_r10_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_r10_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r11_impl/bf_tls_set_r11_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_r11_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_r11_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r12_impl/bf_tls_set_r12_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_r12_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_r12_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r13_impl/bf_tls_set_r13_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_r13_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_r13_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r14_impl/bf_tls_set_r14_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_r14_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_r14_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r15_impl/bf_tls_set_r15_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    bf_tls_set_r15_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(bsl::ZERO_UMAX == bf_tls_r15_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_extid_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_U16 == bf_tls_extid_impl());
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vmid_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_U16 == bf_tls_vmid_impl());
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpid_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_U16 == bf_tls_vpid_impl());
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpsid_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_U16 == bf_tls_vpsid_impl());
                };
            };
        };

        bsl::ut_scenario{"bf_tls_ppid_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_U16 == bf_tls_ppid_impl());
                };
            };
        };

        bsl::ut_scenario{"bf_tls_online_pps_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_U16 == bf_tls_online_pps_impl());
                };
            };
        };

        bsl::ut_scenario{"bf_control_op_exit_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_control_op_exit_impl();
                };
            };
        };

        bsl::ut_scenario{"bf_control_op_wait_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_control_op_wait_impl();
                };
            };
        };

        bsl::ut_scenario{"bf_handle_op_open_handle_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_handle_op_open_handle_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_handle_op_close_handle_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_handle_op_close_handle_impl({}));
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_out_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_out_impl({}, {});
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vm_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_dump_vm_impl({});
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vp_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_dump_vp_impl({});
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vps_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_dump_vps_impl({});
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vmexit_log_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_dump_vmexit_log_impl({});
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vmexit_log_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_dump_vmexit_log_impl({});
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_write_c_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_write_c_impl({});
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_write_str_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_write_str_impl({});
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_ext_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_dump_ext_impl({});
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_page_pool_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_dump_page_pool_impl();
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_huge_pool_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bf_debug_op_dump_huge_pool_impl();
                };
            };
        };

        bsl::ut_scenario{"bf_callback_op_register_bootstrap_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_callback_op_register_bootstrap_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_callback_op_register_vmexit_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_callback_op_register_vmexit_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_callback_op_register_fail_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_callback_op_register_fail_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_create_vm_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vm_op_create_vm_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_destroy_vm_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vm_op_destroy_vm_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vp_op_create_vp_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_destroy_vp_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vp_op_destroy_vp_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vp_op_migrate_impl({}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_create_vps_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_destroy_vps_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_destroy_vps_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_init_as_root_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_init_as_root_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_read8_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_read16_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_read32_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_read64_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_write8_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_write16_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_write32_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_write64_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_read_reg_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_write_reg_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_run_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_current_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_run_current_impl({}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_advance_ip_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_and_run_current_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_advance_ip_and_run_current_impl({}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_promote_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_promote_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_clear_vps_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_vps_op_clear_vps_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_intrinsic_op_rdmsr_impl({}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_intrinsic_op_wrmsr_impl({}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_intrinsic_op_invlpga_impl({}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_intrinsic_op_invept_impl({}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_intrinsic_op_invvpid_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_mem_op_alloc_page_impl({}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_page_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_mem_op_free_page_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_mem_op_alloc_huge_impl({}, {}, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_huge_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_mem_op_free_huge_impl({}, {}));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_heap_impl execute"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_then{} = []() {
                    bsl::ut_check(bsl::ZERO_UMAX == bf_mem_op_alloc_heap_impl({}, {}, {}));
                };
            };
        };

        return bsl::ut_success();
    }
}

/// <!-- description -->
///   @brief Main function for this unit test. If a call to bsl::ut_check(bsl::ZERO_UMAX == ) fails
///     the application will fast fail. If all calls to bsl::ut_check(bsl::ZERO_UMAX == ) pass, this
///     function will successfully return with bsl::exit_success.
///
/// <!-- inputs/outputs -->
///   @return Always returns bsl::exit_success.
///
[[nodiscard]] auto
main() noexcept -> bsl::exit_code
{
    bsl::enable_color();

    static_assert(syscall::tests() == bsl::ut_success());
    return syscall::tests();
}
