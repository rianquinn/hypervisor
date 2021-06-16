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

#ifndef MOCKS_VPS_T_HPP
#define MOCKS_VPS_T_HPP

#include <bf_constants.hpp>
#include <bf_syscall_t.hpp>
#include <gs_t.hpp>
#include <intrinsic_t.hpp>
#include <tls_t.hpp>

#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>

namespace example
{
    /// @class example::vps_t
    ///
    /// <!-- description -->
    ///   @brief Defines the extension's notion of a VPS for unit testing.
    ///
    class vps_t final
    {
        /// @brief stores the ID associated with this vps_t
        bsl::safe_uint16 m_id{bsl::safe_uint16::zero(true)};
        /// @brief stores the ID of the VP this vps_t is assigned to
        bsl::safe_uint16 m_assigned_vpid{syscall::BF_INVALID_ID};
        /// @brief stores the ID of the PP this vps_t is assigned to
        bsl::safe_uint16 m_assigned_ppid{syscall::BF_INVALID_ID};

    public:
        /// <!-- description -->
        ///   @brief Initializes this vps_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param i the ID for this vps_t
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(gs_t &gs, tls_t &tls, bsl::safe_uint16 const &i) &noexcept -> bsl::errc_type
        {
            bsl::discard(gs);

            /// NOTE:
            /// - All mocks should behave the same as the original to ensure
            ///   that unit testing can find weird issues. Some functions
            ///   that the original might call cannot be called, which is
            ///   where the tls.test_ret comes into play. Here, we can set
            ///   specific error codes that when seen by the mock, will cause
            ///   the mock to return pass/fail for a specific thing that it
            ///   cannot mimic outright.
            /// - Most of the original code will use bsl::unlikely_assert
            ///   where checks are not expected to be an issue at runtime,
            ///   and all of these should be changed to bsl::unlikely for the
            ///   mock to ensure that at all times, these are being checked.
            ///

            if (bsl::unlikely(m_id)) {
                bsl::error() << "vps_t already initialized\n" << bsl::here();
                return bsl::errc_precondition;
            }

            if (bsl::unlikely(!i)) {
                bsl::error() << "invalid id\n" << bsl::here();
                return bsl::errc_invalid_argument;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == i)) {
                bsl::error() << "id "                                                  // --
                             << bsl::hex(i)                                            // --
                             << " is invalid and cannot be used for initialization"    // --
                             << bsl::endl                                              // --
                             << bsl::here();                                           // --

                return bsl::errc_invalid_argument;
            }

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

            m_id = i;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vps_t.
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

            /// NOTE:
            /// - Release functions are usually only needed in the event of
            ///   an error, or during unit testing.
            ///

            m_assigned_ppid = syscall::BF_INVALID_ID;
            m_assigned_vpid = syscall::BF_INVALID_ID;
            m_id = bsl::safe_uint16::zero(true);
        }

        /// <!-- description -->
        ///   @brief Allocates a vps_t and returns it's ID
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vpid the ID of the VP to assign the vps_t to
        ///   @param ppid the ID of the PP to assign the vps_t to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        allocate(
            gs_t &gs,
            tls_t &tls,
            syscall::bf_syscall_t &sys,
            intrinsic_t &intrinsic,
            bsl::safe_uint16 const &vpid,
            bsl::safe_uint16 const &ppid) &noexcept -> bsl::errc_type
        {
            bsl::discard(gs);
            bsl::discard(tls);
            bsl::discard(sys);
            bsl::discard(intrinsic);

            /// NOTE:
            /// - All mocks should behave the same as the original to ensure
            ///   that unit testing can find weird issues. Some functions
            ///   that the original might call cannot be called, which is
            ///   where the tls.test_ret comes into play. Here, we can set
            ///   specific error codes that when seen by the mock, will cause
            ///   the mock to return pass/fail for a specific thing that it
            ///   cannot mimic outright.
            /// - Most of the original code will use bsl::unlikely_assert
            ///   where checks are not expected to be an issue at runtime,
            ///   and all of these should be changed to bsl::unlikely for the
            ///   mock to ensure that at all times, these are being checked.
            ///

            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vps_t not initialized\n" << bsl::here();
                return bsl::errc_precondition;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID != m_assigned_ppid)) {
                bsl::error() << "vps "                                            // --
                             << bsl::hex(m_id)                                   // --
                             << " is already allocated and cannot be created"    // --
                             << bsl::endl                                        // --
                             << bsl::here();                                     // --

                return bsl::errc_precondition;
            }

            if (bsl::unlikely(!vpid)) {
                bsl::error() << "invalid vpid\n" << bsl::here();
                return bsl::errc_invalid_argument;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == vpid)) {
                bsl::error() << "vp "                                              // --
                             << bsl::hex(vpid)                                     // --
                             << " is invalid and a vps cannot be assigned to it"    // --
                             << bsl::endl                                          // --
                             << bsl::here();                                       // --

                return bsl::errc_invalid_argument;
            }

            if (bsl::unlikely(!ppid)) {
                bsl::error() << "invalid ppid\n" << bsl::here();
                return bsl::errc_invalid_argument;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == ppid)) {
                bsl::error() << "pp "                                              // --
                             << bsl::hex(ppid)                                     // --
                             << " is invalid and a vps cannot be assigned to it"    // --
                             << bsl::endl                                          // --
                             << bsl::here();                                       // --

                return bsl::errc_invalid_argument;
            }

            /// NOTE:
            /// - This is an example of providing an error case that the
            ///   original code does not have. Any code that is using this
            ///   will have no idea how this function is implemented, and
            ///   at any time it might return an error. This ensure that
            ///   this is handled.
            ///

            if (tls.test_ret == errc_fail_allocate) {
                return bsl::errc_failure;
            }

            /// NOTE:
            /// - Finally, store the IDs of the VP and PP that this vps_t is
            ///   assigned to just like the original.
            ///

            m_assigned_vpid = vpid;
            m_assigned_ppid = ppid;

            return bsl::errc_success;
        }
    };
}

#endif
