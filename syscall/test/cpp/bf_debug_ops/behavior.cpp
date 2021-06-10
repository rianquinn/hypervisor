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

#include "../../../src/cpp/bf_debug_ops.hpp"

#include <bsl/discard.hpp>
#include <bsl/ut.hpp>

namespace syscall
{
    /// @brief stores whether or not the impl was executed.
    bool g_executed{};

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_out.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///
    extern "C" void
    bf_debug_op_out_impl(
        bf_uint64_t::value_type const reg0_in, bf_uint64_t::value_type const reg1_in) noexcept
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        g_executed = true;
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_vm.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void
    bf_debug_op_dump_vm_impl(bf_uint16_t::value_type const reg0_in) noexcept
    {
        bsl::discard(reg0_in);
        g_executed = true;
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_vp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void
    bf_debug_op_dump_vp_impl(bf_uint16_t::value_type const reg0_in) noexcept
    {
        bsl::discard(reg0_in);
        g_executed = true;
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_vps.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void
    bf_debug_op_dump_vps_impl(bf_uint16_t::value_type const reg0_in) noexcept
    {
        bsl::discard(reg0_in);
        g_executed = true;
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_vmexit_log.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void
    bf_debug_op_dump_vmexit_log_impl(bf_uint16_t::value_type const reg0_in) noexcept
    {
        bsl::discard(reg0_in);
        g_executed = true;
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_write_c.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void
    bf_debug_op_write_c_impl(bsl::char_type const reg0_in) noexcept
    {
        bsl::discard(reg0_in);
        g_executed = true;
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_write_str.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void
    bf_debug_op_write_str_impl(bsl::char_type const *const reg0_in) noexcept
    {
        bsl::discard(reg0_in);
        g_executed = true;
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_ext.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void
    bf_debug_op_dump_ext_impl(bf_uint16_t::value_type const reg0_in) noexcept
    {
        bsl::discard(reg0_in);
        g_executed = true;
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_page_pool.
    ///
    extern "C" void
    bf_debug_op_dump_page_pool_impl() noexcept
    {
        g_executed = true;
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_huge_pool.
    ///
    extern "C" void
    bf_debug_op_dump_huge_pool_impl() noexcept
    {
        g_executed = true;
    }

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
        bsl::ut_scenario{"bf_debug_op_out executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_out({}, {});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vm executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_dump_vm({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vp executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_dump_vp({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vps executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_dump_vps({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_vmexit_log executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_dump_vmexit_log({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_write_c executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_write_c({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_write_str executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_write_str({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_ext executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_dump_ext({});
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_page_pool executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_dump_page_pool();
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_debug_op_dump_huge_pool executes impl"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                g_executed = {};
                bsl::ut_when{} = []() {
                    bf_debug_op_dump_huge_pool();
                    bsl::ut_then{} = []() {
                        bsl::ut_check(g_executed);
                    };
                };
            };
        };

        return bsl::ut_success();
    }
}

/// <!-- description -->
///   @brief Main function for this unit test. If a call to bsl::ut_check() fails
///     the application will fast fail. If all calls to bsl::ut_check() pass, this
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
