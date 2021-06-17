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

#include "../../../src/vp_pool_t.hpp"

#include <bsl/ut.hpp>

namespace example
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
        bsl::ut_scenario{"initialize vp_t reports failure"} = []() {
            bsl::ut_given{} = []() {
                vp_pool_t vp_pool{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                    tls.test_ret = bsl::errc_failure;
                    bsl::ut_then{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vp_pool.initialize(gs, tls, sys, intrinsic));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize success"} = []() {
            bsl::ut_given{} = []() {
                vp_pool_t vp_pool{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_then{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_check(vp_pool.initialize(gs, tls, sys, intrinsic));
                };
            };
        };

        bsl::ut_scenario{"release executes without initialize"} = []() {
            bsl::ut_given{} = []() {
                vp_pool_t vp_pool{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_then{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                    vp_pool.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"release executes with initialize"} = []() {
            bsl::ut_given{} = []() {
                vp_pool_t vp_pool{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vp_pool.initialize(gs, tls, sys, intrinsic));
                    bsl::ut_then{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                        vp_pool.release(gs, tls, sys, intrinsic);
                    };
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vp_op_create_vp fails"} = []() {
            bsl::ut_given{} = []() {
                vp_pool_t vp_pool{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vp_pool.initialize(gs, tls, sys, intrinsic));
                    sys.set_bf_vp_op_create_vp({}, {}, bsl::safe_uint16::zero(true));
                    bsl::ut_then{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vp_pool.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vp_op_create_vp returns invalid id"} = []() {
            bsl::ut_given{} = []() {
                vp_pool_t vp_pool{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vp_pool.initialize(gs, tls, sys, intrinsic));
                    sys.set_bf_vp_op_create_vp({}, {}, syscall::BF_INVALID_ID);
                    bsl::ut_then{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vp_pool.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                };
            };
        };

        bsl::ut_scenario{"allocate vp_t allocate fails"} = []() {
            bsl::ut_given{} = []() {
                vp_pool_t vp_pool{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vp_pool.initialize(gs, tls, sys, intrinsic));
                    tls.test_ret = bsl::errc_failure;
                    bsl::ut_then{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vp_pool.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                };
            };
        };

        bsl::ut_scenario{"allocate success"} = []() {
            bsl::ut_given{} = []() {
                vp_pool_t vp_pool{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vp_pool.initialize(gs, tls, sys, intrinsic));
                    bsl::ut_then{} = [&vp_pool, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(vp_pool.allocate(gs, tls, sys, intrinsic, {}, {}));
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

    static_assert(example::tests() == bsl::ut_success());
    return example::tests();
}
