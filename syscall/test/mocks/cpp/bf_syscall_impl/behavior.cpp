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

#include <bf_constants.hpp>

#include <bsl/ut.hpp>

namespace syscall
{
    // -------------------------------------------------------------------------
    // constants
    // -------------------------------------------------------------------------

    /// @brief stores the answer to all things (in 8 bits)
    constexpr bf_uint8_t g_answer8{bsl::to_u8(42)};
    /// @brief stores the answer to all things (in 16 bits)
    constexpr bf_uint16_t g_answer16{bsl::to_u16(42)};
    /// @brief stores the answer to all things (in 32 bits)
    constexpr bf_uint32_t g_answer32{bsl::to_u32(42)};
    /// @brief stores the answer to all things (in 64 bits)
    constexpr bf_uint64_t g_answer64{bsl::to_u64(42)};

    // -------------------------------------------------------------------------
    // tests
    // -------------------------------------------------------------------------

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
        bsl::ut_scenario{"quiet dummy_bootstrap_entry"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t arg0{};
                bsl::ut_then{} = [&arg0]() {
                    dummy_bootstrap_entry(arg0.get());
                };
            };
        };

        bsl::ut_scenario{"quiet dummy_vmexit_entry"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_then{} = [&arg0, &arg1]() {
                    dummy_vmexit_entry(arg0.get(), arg1.get());
                };
            };
        };

        bsl::ut_scenario{"quiet dummy_fail_entry"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_then{} = [&arg0, &arg1]() {
                    dummy_fail_entry(arg0.get(), arg1.get());
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rax_impl/bf_tls_set_rax_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_rax_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_rax_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbx_impl/bf_tls_set_rbx_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_rbx_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_rbx_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rcx_impl/bf_tls_set_rcx_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_rcx_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_rcx_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdx_impl/bf_tls_set_rdx_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_rdx_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_rdx_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbp_impl/bf_tls_set_rbp_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_rbp_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_rbp_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rsi_impl/bf_tls_set_rsi_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_rsi_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_rsi_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdi_impl/bf_tls_set_rdi_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_rdi_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_rdi_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r8_impl/bf_tls_set_r8_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_r8_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_r8_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r9_impl/bf_tls_set_r9_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_r9_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_r9_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r10_impl/bf_tls_set_r10_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_r10_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_r10_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r11_impl/bf_tls_set_r11_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_r11_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_r11_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r12_impl/bf_tls_set_r12_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_r12_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_r12_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r13_impl/bf_tls_set_r13_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_r13_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_r13_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r14_impl/bf_tls_set_r14_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_r14_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_r14_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r15_impl/bf_tls_set_r15_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    bf_tls_set_r15_impl(g_answer64.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer64 == bf_tls_r15_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_extid_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    g_data.at("bf_tls_extid") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer16 == bf_tls_extid_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vmid_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    g_data.at("bf_tls_vmid") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer16 == bf_tls_vmid_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpid_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    g_data.at("bf_tls_vpid") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer16 == bf_tls_vpid_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpsid_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    g_data.at("bf_tls_vpsid") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer16 == bf_tls_vpsid_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_ppid_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    g_data.at("bf_tls_ppid") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer16 == bf_tls_ppid_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_online_pps_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_data.clear();
                    g_data.at("bf_tls_online_pps") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_answer16 == bf_tls_online_pps_impl());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_control_op_exit_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_control_op_exit_impl_executed = {};
                    bf_control_op_exit_impl();
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_control_op_exit_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_control_op_wait_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_control_op_wait_impl_executed = {};
                    bf_control_op_wait_impl();
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_control_op_wait_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_handle_op_open_handle_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_handle_op_open_handle_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_handle_op_open_handle_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_handle_op_open_handle_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_handle_op_open_handle_impl_reg0_out") = g_answer64;
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_handle_op_open_handle_impl({}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_handle_op_open_handle_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_handle_op_open_handle_impl_reg0_out") = g_answer64;
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_handle_op_open_handle_impl({}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer64 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_handle_op_close_handle_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_handle_op_close_handle_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_handle_op_close_handle_impl({})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_handle_op_close_handle_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_handle_op_close_handle_impl({})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_out_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_out_impl_executed = {};
                    bf_debug_op_out_impl({}, {});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_out_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vm_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_dump_vm_impl_executed = {};
                    bf_debug_op_dump_vm_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_dump_vm_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vp_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_dump_vp_impl_executed = {};
                    bf_debug_op_dump_vp_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_dump_vp_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vps_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_dump_vps_impl_executed = {};
                    bf_debug_op_dump_vps_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_dump_vps_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vmexit_log_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_dump_vmexit_log_impl_executed = {};
                    bf_debug_op_dump_vmexit_log_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_dump_vmexit_log_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vmexit_log_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_dump_vmexit_log_impl_executed = {};
                    bf_debug_op_dump_vmexit_log_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_dump_vmexit_log_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_write_c_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_write_c_impl_executed = {};
                    bf_debug_op_write_c_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_write_c_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_write_str_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_write_str_impl_executed = {};
                    bf_debug_op_write_str_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_write_str_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_ext_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_dump_ext_impl_executed = {};
                    bf_debug_op_dump_ext_impl({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_dump_ext_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_page_pool_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_dump_page_pool_impl_executed = {};
                    bf_debug_op_dump_page_pool_impl();
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_dump_page_pool_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_huge_pool_impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_bf_debug_op_dump_huge_pool_impl_executed = {};
                    bf_debug_op_dump_huge_pool_impl();
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_bf_debug_op_dump_huge_pool_impl_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_callback_op_register_bootstrap_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_callback_op_register_bootstrap_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_callback_op_register_bootstrap_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_callback_op_register_bootstrap_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_callback_op_register_bootstrap_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_callback_op_register_vmexit_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_callback_op_register_vmexit_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_callback_op_register_vmexit_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_callback_op_register_vmexit_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_callback_op_register_vmexit_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_callback_op_register_fail_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_callback_op_register_fail_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_callback_op_register_fail_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_callback_op_register_fail_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_callback_op_register_fail_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_create_vm_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vm_op_create_vm_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_create_vm_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vm_op_create_vm_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_vm_op_create_vm_impl_reg0_out") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vm_op_create_vm_impl({}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_create_vm_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_vm_op_create_vm_impl_reg0_out") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vm_op_create_vm_impl({}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer16 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_destroy_vm_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vm_op_destroy_vm_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vm_op_destroy_vm_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_destroy_vm_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vm_op_destroy_vm_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vp_op_create_vp_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vp_op_create_vp_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_vp_op_create_vp_impl_reg0_out") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vp_op_create_vp_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_vp_op_create_vp_impl_reg0_out") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vp_op_create_vp_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer16 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_destroy_vp_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vp_op_destroy_vp_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vp_op_destroy_vp_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_destroy_vp_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vp_op_destroy_vp_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vp_op_migrate_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vp_op_migrate_impl({}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vp_op_migrate_impl({}, {}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_create_vps_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_create_vps_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_vps_op_create_vps_impl_reg0_out") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_create_vps_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_vps_op_create_vps_impl_reg0_out") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_create_vps_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer16 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_destroy_vps_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_destroy_vps_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_destroy_vps_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_destroy_vps_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_destroy_vps_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_init_as_root_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_init_as_root_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_init_as_root_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_init_as_root_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_init_as_root_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_read8_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint8_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_read8_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_vps_op_read8_impl_reg0_out") = bsl::to_u64(g_answer8);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read8_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint8_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_vps_op_read8_impl_reg0_out") = bsl::to_u64(g_answer8);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read8_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer8 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_read16_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_read16_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_vps_op_read16_impl_reg0_out") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read16_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_vps_op_read16_impl_reg0_out") = bsl::to_u64(g_answer16);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read16_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer16 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_read32_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint32_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_read32_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_vps_op_read32_impl_reg0_out") = bsl::to_u64(g_answer32);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read32_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint32_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_vps_op_read32_impl_reg0_out") = bsl::to_u64(g_answer32);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read32_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer32 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_read64_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_read64_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_vps_op_read64_impl_reg0_out") = bsl::to_u64(g_answer64);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read64_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_vps_op_read64_impl_reg0_out") = bsl::to_u64(g_answer64);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read64_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer64 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_write8_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write8_impl({}, {}, {}, g_answer8.get())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(g_data.at("bf_vps_op_write8_impl").is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write8_impl({}, {}, {}, g_answer8.get())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_data.at("bf_vps_op_write8_impl") == bsl::to_u64(g_answer8));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_write16_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write16_impl({}, {}, {}, g_answer16.get())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(g_data.at("bf_vps_op_write16_impl").is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write16_impl({}, {}, {}, g_answer16.get())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(
                            g_data.at("bf_vps_op_write16_impl") == bsl::to_u64(g_answer16));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_write32_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write32_impl({}, {}, {}, g_answer32.get())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(g_data.at("bf_vps_op_write32_impl").is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write32_impl({}, {}, {}, g_answer32.get())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(
                            g_data.at("bf_vps_op_write32_impl") == bsl::to_u64(g_answer32));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_write64_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write64_impl({}, {}, {}, g_answer64.get())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(g_data.at("bf_vps_op_write64_impl").is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write64_impl({}, {}, {}, g_answer64.get())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(
                            g_data.at("bf_vps_op_write64_impl") == bsl::to_u64(g_answer64));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_read_reg_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_read_reg_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_vps_op_read_reg_impl_reg0_out") = g_answer64;
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read_reg_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_vps_op_read_reg_impl_reg0_out") = g_answer64;
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_vps_op_read_reg_impl({}, {}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer64 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_write_reg_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write_reg_impl({}, {}, {}, g_answer64.get())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(g_data.at("bf_vps_op_write_reg_impl").is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_write_reg_impl({}, {}, {}, g_answer64.get())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_data.at("bf_vps_op_write_reg_impl") == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_run_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_run_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_run_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_current_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_run_current_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_run_current_impl({})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_current_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_run_current_impl({})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_advance_ip_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_advance_ip_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_advance_ip_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_and_run_current_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_advance_ip_and_run_current_impl") =
                        BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_advance_ip_and_run_current_impl({})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_and_run_current_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_advance_ip_and_run_current_impl({})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_promote_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_promote_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_promote_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_promote_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_promote_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_clear_vps_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_vps_op_clear_vps_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_clear_vps_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_clear_vps_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_vps_op_clear_vps_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_intrinsic_op_rdmsr_impl({}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_intrinsic_op_rdmsr_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_intrinsic_op_rdmsr_impl_reg0_out") = g_answer64;
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_intrinsic_op_rdmsr_impl({}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg0_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_intrinsic_op_rdmsr_impl_reg0_out") = g_answer64;
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_intrinsic_op_rdmsr_impl({}, {}, reg0_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer64 == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_intrinsic_op_wrmsr_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_intrinsic_op_wrmsr_impl({}, {}, g_answer64.get())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(g_data.at("bf_intrinsic_op_wrmsr_impl").is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_intrinsic_op_wrmsr_impl({}, {}, g_answer64.get())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_data.at("bf_intrinsic_op_wrmsr_impl") == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_intrinsic_op_invlpga_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_intrinsic_op_invlpga_impl({}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_intrinsic_op_invlpga_impl({}, {}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_intrinsic_op_invept_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_intrinsic_op_invept_impl({}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_intrinsic_op_invept_impl({}, {}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_intrinsic_op_invvpid_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_intrinsic_op_invvpid_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_intrinsic_op_invvpid_impl({}, {}, {}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg1_out{};
                bsl::ut_when{} = [&reg1_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_mem_op_alloc_page_impl_reg1_out") = bsl::to_umax(g_answer64);
                    bsl::ut_then{} = [&reg1_out]() {
                        auto const ret{bf_mem_op_alloc_page_impl({}, {}, reg1_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg1_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                void *reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_mem_op_alloc_page_impl_reg0_out") = bsl::to_umax(g_answer64);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_mem_op_alloc_page_impl({}, &reg0_out, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(nullptr == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                void *reg0_out{};
                bf_uint64_t reg1_out{};
                bsl::ut_when{} = [&reg0_out, &reg1_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_mem_op_alloc_page_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_mem_op_alloc_page_impl_reg0_out") = bsl::to_umax(g_answer64);
                    g_data.at("bf_mem_op_alloc_page_impl_reg1_out") = bsl::to_umax(g_answer64);
                    bsl::ut_then{} = [&reg0_out, &reg1_out]() {
                        auto const ret{bf_mem_op_alloc_page_impl({}, &reg0_out, reg1_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(nullptr == reg0_out);
                        bsl::ut_check(reg1_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                void *reg0_out{};
                bf_uint64_t reg1_out{};
                bsl::ut_when{} = [&reg0_out, &reg1_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_mem_op_alloc_page_impl") = BF_STATUS_SUCCESS;
                    g_data.at("bf_mem_op_alloc_page_impl_reg0_out") = bsl::to_umax(g_answer64);
                    g_data.at("bf_mem_op_alloc_page_impl_reg1_out") = bsl::to_umax(g_answer64);
                    bsl::ut_then{} = [&reg0_out, &reg1_out]() {
                        auto const ret{bf_mem_op_alloc_page_impl({}, &reg0_out, reg1_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer64 == bsl::to_umax(reg0_out));
                        bsl::ut_check(g_answer64 == reg1_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_page_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_mem_op_free_page_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_mem_op_free_page_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_page_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_mem_op_free_page_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint64_t reg1_out{};
                bsl::ut_when{} = [&reg1_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_mem_op_alloc_huge_impl_reg1_out") = bsl::to_umax(g_answer64);
                    bsl::ut_then{} = [&reg1_out]() {
                        auto const ret{bf_mem_op_alloc_huge_impl({}, {}, {}, reg1_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(reg1_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                void *reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_mem_op_alloc_huge_impl_reg0_out") = bsl::to_umax(g_answer64);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_mem_op_alloc_huge_impl({}, {}, &reg0_out, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(nullptr == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                void *reg0_out{};
                bf_uint64_t reg1_out{};
                bsl::ut_when{} = [&reg0_out, &reg1_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_mem_op_alloc_huge_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_mem_op_alloc_huge_impl_reg0_out") = bsl::to_umax(g_answer64);
                    g_data.at("bf_mem_op_alloc_huge_impl_reg1_out") = bsl::to_umax(g_answer64);
                    bsl::ut_then{} = [&reg0_out, &reg1_out]() {
                        auto const ret{
                            bf_mem_op_alloc_huge_impl({}, {}, &reg0_out, reg1_out.data())};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(nullptr == reg0_out);
                        bsl::ut_check(reg1_out.is_zero());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                void *reg0_out{};
                bf_uint64_t reg1_out{};
                bsl::ut_when{} = [&reg0_out, &reg1_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_mem_op_alloc_huge_impl") = BF_STATUS_SUCCESS;
                    g_data.at("bf_mem_op_alloc_huge_impl_reg0_out") = bsl::to_umax(g_answer64);
                    g_data.at("bf_mem_op_alloc_huge_impl_reg1_out") = bsl::to_umax(g_answer64);
                    bsl::ut_then{} = [&reg0_out, &reg1_out]() {
                        auto const ret{
                            bf_mem_op_alloc_huge_impl({}, {}, &reg0_out, reg1_out.data())};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer64 == bsl::to_umax(reg0_out));
                        bsl::ut_check(g_answer64 == reg1_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_huge_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_mem_op_free_huge_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    bsl::ut_then{} = []() {
                        auto const ret{bf_mem_op_free_huge_impl({}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_huge_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_mem_op_free_huge_impl({}, {})};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_heap_impl invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bsl::ut_when{} = []() {
                    g_errc.clear();
                    g_data.clear();
                    bsl::ut_then{} = []() {
                        auto const ret{bf_mem_op_alloc_heap_impl({}, {}, {})};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_heap_impl failure"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                void *reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_errc.at("bf_mem_op_alloc_heap_impl") = BF_STATUS_FAILURE_UNKNOWN;
                    g_data.at("bf_mem_op_alloc_heap_impl_reg0_out") = bsl::to_umax(g_answer64);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_mem_op_alloc_heap_impl({}, {}, &reg0_out)};
                        bsl::ut_check(BF_STATUS_FAILURE_UNKNOWN == ret);
                        bsl::ut_check(nullptr == reg0_out);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_heap_impl success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                void *reg0_out{};
                bsl::ut_when{} = [&reg0_out]() {
                    g_errc.clear();
                    g_data.clear();
                    g_data.at("bf_mem_op_alloc_heap_impl_reg0_out") = bsl::to_u64(g_answer64);
                    bsl::ut_then{} = [&reg0_out]() {
                        auto const ret{bf_mem_op_alloc_heap_impl({}, {}, &reg0_out)};
                        bsl::ut_check(BF_STATUS_SUCCESS == ret);
                        bsl::ut_check(g_answer64 == bsl::to_umax(reg0_out));
                    };
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
