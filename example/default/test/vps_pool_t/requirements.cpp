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

#include "../../src/vps_pool_t.hpp"

#include <bsl/discard.hpp>
#include <bsl/ut.hpp>

namespace example
{
    constinit vps_pool_t const verify_constinit{};

    // NOLINTNEXTLINE(bsl-user-defined-type-names-match-header-name)
    class fixture_t final
    {
        vps_pool_t vps_pool{};

    public:
        [[nodiscard]] constexpr auto
        test_member_const() const noexcept -> bool
        {
            return true;
        }

        [[nodiscard]] constexpr auto
        test_member_nonconst() noexcept -> bool
        {
            example::gs_t gs{};
            example::tls_t tls{};
            syscall::bf_syscall_t sys{};
            example::intrinsic_t intrinsic{};
            bsl::safe_uint16 vmid{};
            bsl::safe_uint16 ppid{};

            bsl::discard(vps_pool_t{});
            bsl::discard(vps_pool.initialize(gs, tls));
            vps_pool.release(gs, tls);
            bsl::discard(vps_pool.allocate(gs, tls, sys, intrinsic, vmid, ppid));

            return true;
        }
    };

    /// NOTE:
    /// - The following verifies that all of our code will compile as a
    ///   constexpr. If test_member_nonconst contains a call to all of the
    ///   functions in your class, the following will not compile if anything
    ///   in the class is not constexpr friendly.
    ///

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
    /// NOTE:
    /// - This is really just here to make some compilers happy that we have
    ///   a global variable and that it is actually being used.
    ///

    bsl::ut_scenario{"verify supports constinit"} = []() {
        bsl::discard(example::verify_constinit);
    };

    /// NOTE:
    /// - The following verifies that all functions are marked as noexcept.
    ///   This list should include not only all of the functions, but all
    ///   constructors as well.
    ///

    bsl::ut_scenario{"verify noexcept"} = []() {
        bsl::ut_given{} = []() {
            example::vps_pool_t vps_pool{};
            example::gs_t gs{};
            example::tls_t tls{};
            syscall::bf_syscall_t sys{};
            example::intrinsic_t intrinsic{};
            bsl::safe_uint16 vmid{};
            bsl::safe_uint16 ppid{};
            bsl::ut_then{} = []() {
                static_assert(noexcept(example::vps_pool_t{}));
                static_assert(noexcept(vps_pool.initialize(gs, tls)));
                static_assert(noexcept(vps_pool.release(gs, tls)));
                static_assert(noexcept(vps_pool.allocate(gs, tls, sys, intrinsic, vmid, ppid)));
            };
        };
    };

    /// NOTE:
    /// - The following is what actually verifies constness. This can be
    ///   left as is in each test. It is important to note that we use a
    ///   static_assert here to ensure that the const functions are also
    ///   constexpr friendly as yet another verifier that this is working
    ///   correctly.
    ///

    bsl::ut_scenario{"verify constness"} = []() {
        bsl::ut_given{} = []() {
            example::fixture_t fixture2{};
            bsl::ut_then{} = [&fixture2]() {
                static_assert(example::fixture1.test_member_const());
                bsl::ut_check(fixture2.test_member_nonconst());
            };
        };
    };

    return bsl::ut_success();
}
