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

#ifndef ARCH_SUPPORT_HPP
#define ARCH_SUPPORT_HPP

#include <bf_constants.hpp>

#include <bsl/convert.hpp>
#include <bsl/debug.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace integration
{
    /// <!-- description -->
    ///   @brief Initializes a VPS with architecture specific stuff.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle the handle to use
    ///   @param vpsid the VPS being intialized
    ///   @return Returns bsl::errc_success on success and bsl::errc_failure
    ///     on failure.
    ///
    [[nodiscard]] constexpr auto
    init_vps(syscall::bf_handle_t &handle, bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
    {
        bsl::errc_type ret{};

        /// NOTE:
        /// - Set up ASID
        ///

        constexpr bsl::safe_uint64 guest_asid_idx{bsl::to_u64(0x0058U)};
        constexpr bsl::safe_uint32 guest_asid_val{bsl::to_u32(0x1U)};

        ret = syscall::bf_vps_op_write32(handle, vpsid, guest_asid_idx, guest_asid_val);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Set up intercept controls. On AMD, we need to intercept
        ///   VMRun, and CPUID if we plan to support reporting and stopping.
        ///

        constexpr bsl::safe_uint64 intercept_instruction1_idx{bsl::to_u64(0x000CU)};
        constexpr bsl::safe_uint32 intercept_instruction1_val{bsl::to_u32(0x00040000U)};
        constexpr bsl::safe_uint64 intercept_instruction2_idx{bsl::to_u64(0x0010U)};
        constexpr bsl::safe_uint32 intercept_instruction2_val{bsl::to_u32(0x00000001U)};

        ret = syscall::bf_vps_op_write32(
            handle, vpsid, intercept_instruction1_idx, intercept_instruction1_val);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        ret = syscall::bf_vps_op_write32(
            handle, vpsid, intercept_instruction2_idx, intercept_instruction2_val);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Report success. Specifically, when we return to the root OS,
        ///   setting RAX tells the loader that the hypervisor was successfully
        ///   set up.
        ///

        ret = syscall::bf_vps_op_write_reg(
            handle, vpsid, syscall::bf_reg_t::bf_reg_t_rax, bsl::ZERO_UMAX);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        return ret;
    }
}

#endif
