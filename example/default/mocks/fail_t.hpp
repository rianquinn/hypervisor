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

#ifndef MOCKS_FAIL_T_HPP
#define MOCKS_FAIL_T_HPP

#include <bf_syscall_t.hpp>
#include <gs_t.hpp>
#include <intrinsic_t.hpp>
#include <tls_t.hpp>
#include <vp_pool_t.hpp>
#include <vps_pool_t.hpp>
#include <errc_types.hpp>

#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>

namespace example
{
    /// @class example::fail_t
    ///
    /// <!-- description -->
    ///   @brief Defines the extension's fail handler used for unit testing
    ///
    class fail_t final
    {
    public:
        /// <!-- description -->
        ///   @brief Initializes this fail_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] static constexpr auto
        initialize(gs_t &gs, tls_t &tls) noexcept -> bsl::errc_type
        {
            bsl::discard(gs);

            /// NOTE:
            /// - This is an example of providing an error case that the
            ///   original code does not have. Any code that is using this
            ///   will have no idea how this function is implemented, and
            ///   at any time it might return an error. This ensure that
            ///   this is handled.
            ///

            if (tls.test_ret == errc_fail_initialize) {
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the fail_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///
        static constexpr void
        release(gs_t &gs, tls_t &tls) noexcept
        {
            bsl::discard(gs);
            bsl::discard(tls);
        }

        /// <!-- description -->
        ///   @brief Dispatches the fail as needed, or returns an error so
        ///     that the microkernel can halt the PP.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vp_pool the vp_pool_t to use
        ///   @param vps_pool the vps_pool_t to use
        ///   @param vpsid the ID of the VPS that generated the fail
        ///   @param fail_reason the exit reason associated with the fail
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] static constexpr auto
        dispatch(
            gs_t &gs,
            tls_t &tls,
            syscall::bf_syscall_t &sys,
            intrinsic_t &intrinsic,
            vp_pool_t &vp_pool,
            vps_pool_t &vps_pool,
            bsl::safe_uint16 const &vpsid,
            bsl::safe_uint64 const &fail_reason) noexcept -> bsl::errc_type
        {
            bsl::discard(gs);
            bsl::discard(sys);
            bsl::discard(intrinsic);
            bsl::discard(vp_pool);
            bsl::discard(vps_pool);
            bsl::discard(vpsid);
            bsl::discard(fail_reason);

            /// NOTE:
            /// - This is an example of providing an error case that the
            ///   original code does not have. Any code that is using this
            ///   will have no idea how this function is implemented, and
            ///   at any time it might return an error. This ensure that
            ///   this is handled.
            ///

            if (tls.test_ret == errc_fail_dispatch) {
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }
    };
}

#endif
