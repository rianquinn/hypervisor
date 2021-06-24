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

#include "../../../../../src/x64/amd/vps_t.hpp"

#include <bsl/discard.hpp>
#include <bsl/ut.hpp>

namespace
{
    constinit example::gs_t g_gs{};
    constinit example::tls_t g_tls{};
    constinit syscall::bf_syscall_t g_sys{};
    constinit example::intrinsic_t g_intrinsic{};

    constinit example::vps_t const verify_constinit{};

    // NOLINTNEXTLINE(bsl-user-defined-type-names-match-header-name)
    class fixture_t final
    {
        example::vps_t vps_pool{};

    public:
        [[nodiscard]] static constexpr auto
        test_member_const() noexcept -> bool
        {
            /// NOTE:
            /// - vps_t does not contain const member functions
            ///

            return true;
        }

        [[nodiscard]] constexpr auto
        test_member_nonconst() noexcept -> bool
        {
            bsl::discard(example::vps_t{});
            bsl::discard(vps_pool.initialize(g_gs, g_tls, g_sys, g_intrinsic, {}));
            vps_pool.release(g_gs, g_tls, g_sys, g_intrinsic);
            bsl::discard(vps_pool.allocate(g_gs, g_tls, g_sys, g_intrinsic, {}, {}));

            return true;
        }
    };

    constexpr fixture_t fixture1{};
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
    bsl::ut_scenario{"verify supports constinit"} = []() {
        bsl::discard(verify_constinit);
    };

    bsl::ut_scenario{"verify noexcept"} = []() {
        bsl::ut_given{} = []() {
            example::vps_t vps_pool{};
            bsl::ut_then{} = []() {
                static_assert(noexcept(example::vps_t{}));
                static_assert(noexcept(vps_pool.initialize(g_gs, g_tls, g_sys, g_intrinsic, {})));
                static_assert(noexcept(vps_pool.release(g_gs, g_tls, g_sys, g_intrinsic)));
                static_assert(noexcept(vps_pool.allocate(g_gs, g_tls, g_sys, g_intrinsic, {}, {})));
            };
        };
    };

    bsl::ut_scenario{"verify constness"} = []() {
        bsl::ut_given{} = []() {
            fixture_t fixture2{};
            bsl::ut_then{} = [&]() {
                static_assert(fixture1.test_member_const());
                bsl::ut_check(fixture2.test_member_nonconst());
            };
        };
    };

    return bsl::ut_success();
}
