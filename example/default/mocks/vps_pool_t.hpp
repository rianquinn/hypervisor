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

#ifndef MOCKS_VPS_POOL_T_HPP
#define MOCKS_VPS_POOL_T_HPP

#include <bf_syscall_t.hpp>
#include <gs_t.hpp>
#include <intrinsic_t.hpp>
#include <tls_t.hpp>

#include <bsl/array.hpp>
#include <bsl/debug.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/finally_assert.hpp>
#include <bsl/unlikely.hpp>
#include <bsl/unlikely_assert.hpp>
#include <bsl/safe_integral.hpp>

namespace example
{
    /// @class example::vps_pool_t
    ///
    /// <!-- description -->
    ///   @brief Defines the extension's VPS pool
    ///
    class vps_pool_t final
    {
    public:
        /// <!-- description -->
        ///   @brief Initializes this vps_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(gs_t &gs, tls_t &tls) &noexcept -> bsl::errc_type
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

            /// NOTE:
            /// - Finally, store the ID assigned to this vps_t just like the
            ///   original does.
            ///

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vps_pool_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///
        constexpr void
        release(gs_t &gs, tls_t &tls) &noexcept
        {
            bsl::discard(gs);
            bsl::discard(tls);
        }

        /// <!-- description -->
        ///   @brief Allocates a VPS and returns it's ID
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vpid the ID of the VP to assign the newly created VPS to
        ///   @param ppid the ID of the PP to assign the newly created VPS to
        ///   @return Returns the ID of the newly created VPS on
        ///     success, or bsl::safe_uint16::zero(true) on failure.
        ///
        [[nodiscard]] constexpr auto
        allocate(
            gs_t &gs,
            tls_t &tls,
            syscall::bf_syscall_t &sys,
            intrinsic_t &intrinsic,
            bsl::safe_uint16 const &vpid,
            bsl::safe_uint16 const &ppid) &noexcept -> bsl::safe_uint16
        {
            bsl::discard(gs);
            bsl::discard(sys);
            bsl::discard(intrinsic);
            bsl::discard(vpid);
            bsl::discard(ppid);

            /// NOTE:
            /// - This is an example of providing an error case that the
            ///   original code does not have. Any code that is using this
            ///   will have no idea how this function is implemented, and
            ///   at any time it might return an error. This ensure that
            ///   this is handled.
            ///

            if (tls.test_ret == errc_fail_allocate) {
                return bsl::safe_uint16::zero(true);
            }

            return tls.test_ret_16bit;
        }
    };
}

#endif
