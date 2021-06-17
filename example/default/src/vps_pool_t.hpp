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

#ifndef VPS_POOL_T_HPP
#define VPS_POOL_T_HPP

#include <bf_syscall_t.hpp>
#include <gs_t.hpp>
#include <intrinsic_t.hpp>
#include <tls_t.hpp>
#include <vps_t.hpp>

#include <bsl/array.hpp>
#include <bsl/debug.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/finally_assert.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>
#include <bsl/unlikely_assert.hpp>

namespace example
{
    /// @class example::vps_pool_t
    ///
    /// <!-- description -->
    ///   @brief Defines the extension's VPS pool
    ///
    class vps_pool_t final
    {
        /// @brief stores the pool of VPSs
        bsl::array<vps_t, bsl::to_umax(HYPERVISOR_MAX_VPSS).get()> m_pool{};

    public:
        /// <!-- description -->
        ///   @brief Initializes this vps_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(
            gs_t &gs, tls_t &tls, syscall::bf_syscall_t &sys, intrinsic_t &intrinsic) &noexcept
            -> bsl::errc_type
        {
            /// NOTE:
            /// - The following is used in the event of an error. Basically,
            ///   whatever is in the bsl::finally will execute once the
            ///   function is returned from unless we explicitly call the
            ///   ignore() function, which we do at the end when all is good.
            ///

            bsl::finally_assert release_on_error{
                [this, &gs, &tls, &sys, &intrinsic]() noexcept -> void {
                    this->release(gs, tls, sys, intrinsic);
                }};

            /// NOTE:
            /// - Initialize all of the VPSs. This basically gives each one it's
            ///   ID. We could spare some execution time if we wanted and only
            ///   initialize VPSs equal to the online PPs (there is an ABI to
            ///   get that), as we are only going to have one VPS per PP, so the
            ///   two totals are the same, but for now, this is just easier,
            ///   and it allows us to create more if needed.
            ///

            bsl::errc_type ret{};
            for (bsl::safe_uintmax i{}; i < m_pool.size(); ++i) {
                ret = m_pool.at_if(i)->initialize(gs, tls, sys, intrinsic, bsl::to_u16(i));
                if (bsl::unlikely_assert(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                /// NOTE:
                /// - The call to bsl::touch is only needed if you plan to
                ///   enforce MC/DC unit testing. Feel free to remove this if
                ///   you have no plans to support MC/DC unit testing.
                ///

                bsl::touch();
            }

            release_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vps_pool_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///
        constexpr void
        release(gs_t &gs, tls_t &tls, syscall::bf_syscall_t &sys, intrinsic_t &intrinsic) &noexcept
        {
            /// NOTE:
            /// - Release functions are usually only needed in the event of
            ///   an error, or during unit testing.
            ///

            for (bsl::safe_uintmax i{}; i < m_pool.size(); ++i) {
                m_pool.at_if(i)->release(gs, tls, sys, intrinsic);
            }
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
            bsl::errc_type ret{};
            bsl::safe_uint16 vpsid{};

            /// NOTE:
            /// - Ask the microkernel to create a VPS and return the ID of the
            ///   newly created VPS. We do not check in this function if the
            ///   provided vmid or ppid are valid as this is done by the
            ///   bf_vp_op_create_vp. We only need to check these types of
            ///   inputs at the point of use, and not when we are just passing
            ///   them to another function.
            ///

            vpsid = sys.bf_vps_op_create_vps(vpid, ppid);
            if (bsl::unlikely_assert(!vpsid)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            /// NOTE:
            /// - The following is used in the event of an error. Basically,
            ///   whatever is in the bsl::finally will execute once the
            ///   function is returned from unless we explicitly call the
            ///   ignore() function, which we do at the end when all is good.
            ///

            bsl::finally destroy_vps_on_error{[&sys, &vpsid]() noexcept -> void {
                bsl::discard(sys.bf_vps_op_destroy_vps(vpsid));
            }};

            /// NOTE:
            /// - We need to check to make sure that the provided ID fits
            ///   inside of our pool. Even with microkernel that use the same
            ///   ABI, this would possibly be an issue if the extension and
            ///   the microkernel did not use the same max limits.
            ///

            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " provided by the microkernel is invalid"                  // --
                             << " or greater than or equal to the HYPERVISOR_MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VPSS))                 // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::safe_uint16::zero(true);
            }

            /// NOTE:
            /// - Finally, we need to allocate the VPS in our pool. This will
            ///   simply tell the VPS which VP and PP it is assigned to. We
            ///   can use this in more complicated extensions, and it also
            ///   serves to make sure that we have not allocated the same VPS
            ///   more than once.
            ///

            ret = vps->allocate(gs, tls, sys, intrinsic, vpid, ppid);
            if (bsl::unlikely_assert(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            destroy_vps_on_error.ignore();
            return vpsid;
        }
    };
}

#endif
