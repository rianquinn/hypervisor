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

#ifndef DISPATCH_SYSCALL_VPS_FAILURE_OP_HPP
#define DISPATCH_SYSCALL_VPS_FAILURE_OP_HPP

#include <mk_interface.hpp>

#include <bsl/convert.hpp>
#include <bsl/debug.hpp>
#include <bsl/finally.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Implements the bf_vps_op_create_vps syscall
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
    ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    ///   @param tls the current TLS block
    ///   @param page_pool the page pool to use
    ///   @param vps_pool the VPS pool to use
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<
        typename TLS_CONCEPT,
        typename PAGE_POOL_CONCEPT,
        typename VPS_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    syscall_vps_op_create_vps_failure(
        TLS_CONCEPT &tls,
        PAGE_POOL_CONCEPT &page_pool,
        VPS_POOL_CONCEPT &vps_pool) -> bsl::errc_type
    {
        bsl::errc_type ret{};

        if (!tls.state_reversal_required) {
            return bsl::errc_success;
        }

        ret = vps_pool.deallocate(tls, page_pool, tls.log_vpsid);
        if (bsl::unlikely(!bsl::success_or_precondition(ret))) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        return bsl::errc_success;
    }

    /// <!-- description -->
    ///   @brief Implements the bf_vps_op_destroy_vps syscall
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    ///   @param tls the current TLS block
    ///   @param vps_pool the VPS pool to use
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename TLS_CONCEPT, typename VPS_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    syscall_vps_op_destroy_vps_failure(TLS_CONCEPT &tls, VPS_POOL_CONCEPT &vps_pool)
        -> bsl::errc_type
    {
        bsl::errc_type ret{};

        if (!tls.state_reversal_required) {
            return bsl::errc_success;
        }

        ret = vps_pool.zombify(bsl::to_u16_unsafe(tls.ext_reg1));
        if (bsl::unlikely(!bsl::success_or_precondition(ret))) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        return bsl::errc_success;
    }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_init_as_root syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_init_as_root_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.state_save_to_vps(
    //         tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg1), *tls.root_vp_state)};

    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return ret;
    //     }

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_read8 syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_read8_failure(TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const val{vps_pool.template read<bsl::uint8>(
    //         tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg1), tls.ext_reg2)};

    //     if (bsl::unlikely(!val)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return bsl::errc_failure;
    //     }

    //     constexpr bsl::safe_uintmax mask{0xFFFFFFFFFFFFFF00U};
    //     tls.ext_reg0 = ((tls.ext_reg0 & mask) | bsl::to_umax(val)).get();

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_read16 syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_read16_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const val{vps_pool.template read<bsl::uint16>(
    //         tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg1), tls.ext_reg2)};

    //     if (bsl::unlikely(!val)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return bsl::errc_failure;
    //     }

    //     constexpr bsl::safe_uintmax mask{0xFFFFFFFFFFFF0000U};
    //     tls.ext_reg0 = ((tls.ext_reg0 & mask) | bsl::to_umax(val)).get();

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_read32 syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_read32_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const val{vps_pool.template read<bsl::uint32>(
    //         tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg1), tls.ext_reg2)};

    //     if (bsl::unlikely(!val)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return bsl::errc_failure;
    //     }

    //     constexpr bsl::safe_uintmax mask{0xFFFFFFFF00000000U};
    //     tls.ext_reg0 = ((tls.ext_reg0 & mask) | bsl::to_umax(val)).get();

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_read64 syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_read64_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const val{vps_pool.template read<bsl::uint64>(
    //         tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg1), tls.ext_reg2)};

    //     if (bsl::unlikely(!val)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return bsl::errc_failure;
    //     }

    //     tls.ext_reg0 = val.get();

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_write8 syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_write8_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.template write<bsl::uint8>(
    //         tls,
    //         intrinsic,
    //         bsl::to_u16_unsafe(tls.ext_reg1),
    //         tls.ext_reg2,
    //         bsl::to_u8_unsafe(tls.ext_reg3))};

    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return bsl::errc_failure;
    //     }

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_write16 syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_write16_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.template write<bsl::uint16>(
    //         tls,
    //         intrinsic,
    //         bsl::to_u16_unsafe(tls.ext_reg1),
    //         tls.ext_reg2,
    //         bsl::to_u16_unsafe(tls.ext_reg3))};

    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return ret;
    //     }

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_write32 syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_write32_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.template write<bsl::uint32>(
    //         tls,
    //         intrinsic,
    //         bsl::to_u16_unsafe(tls.ext_reg1),
    //         tls.ext_reg2,
    //         bsl::to_u32_unsafe(tls.ext_reg3))};

    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return ret;
    //     }

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_write64 syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_write64_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.template write<bsl::uint64>(
    //         tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg1), tls.ext_reg2, tls.ext_reg3)};

    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return ret;
    //     }

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_read_reg syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_read_reg_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const val{vps_pool.read_reg(
    //         tls,
    //         intrinsic,
    //         bsl::to_u16_unsafe(tls.ext_reg1),
    //         static_cast<syscall::bf_reg_t>(tls.ext_reg2))};

    //     if (bsl::unlikely(!val)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return bsl::errc_failure;
    //     }

    //     tls.ext_reg0 = val.get();

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_write_reg syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_write_reg_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.write_reg(
    //         tls,
    //         intrinsic,
    //         bsl::to_u16_unsafe(tls.ext_reg1),
    //         static_cast<syscall::bf_reg_t>(tls.ext_reg2),
    //         tls.ext_reg3)};

    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return ret;
    //     }

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_run syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    // ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vm_pool the VM pool to use
    // ///   @param vp_pool the VP pool to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<
    //     typename TLS_CONCEPT,
    //     typename INTRINSIC_CONCEPT,
    //     typename VM_POOL_CONCEPT,
    //     typename VP_POOL_CONCEPT,
    //     typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_run_failure(
    //     TLS_CONCEPT &tls,
    //     INTRINSIC_CONCEPT &intrinsic,
    //     VM_POOL_CONCEPT &vm_pool,
    //     VP_POOL_CONCEPT &vp_pool,
    //     VPS_POOL_CONCEPT &vps_pool) -> bsl::errc_type
    // {
    //     bsl::errc_type ret{};

    //     // ---------------------------------------------------------------------
    //     // Gather Arguments
    //     // ---------------------------------------------------------------------

    //     auto const vmid{bsl::to_u16_unsafe(tls.ext_reg1)};
    //     if (bsl::unlikely(syscall::BF_INVALID_ID == vmid)) {
    //         bsl::error() << "vmid "           // --
    //                      << bsl::hex(vmid)    // --
    //                      << " is invalid"     // --
    //                      << bsl::endl         // --
    //                      << bsl::here();      // --

    //         tls.syscall_ret_status = syscall::BF_STATUS_INVALID_PARAMS1.get();
    //         return bsl::errc_failure;
    //     }

    //     auto const vpid{bsl::to_u16_unsafe(tls.ext_reg2)};
    //     if (bsl::unlikely(syscall::BF_INVALID_ID == vpid)) {
    //         bsl::error() << "vpid "           // --
    //                      << bsl::hex(vpid)    // --
    //                      << " is invalid"     // --
    //                      << bsl::endl         // --
    //                      << bsl::here();      // --

    //         tls.syscall_ret_status = syscall::BF_STATUS_INVALID_PARAMS2.get();
    //         return bsl::errc_failure;
    //     }

    //     auto const vpsid{bsl::to_u16_unsafe(tls.ext_reg3)};
    //     if (bsl::unlikely(syscall::BF_INVALID_ID == vpsid)) {
    //         bsl::error() << "vpsid "           // --
    //                      << bsl::hex(vpsid)    // --
    //                      << " is invalid"      // --
    //                      << bsl::endl          // --
    //                      << bsl::here();       // --

    //         tls.syscall_ret_status = syscall::BF_STATUS_INVALID_PARAMS3.get();
    //         return bsl::errc_failure;
    //     }

    //     // ---------------------------------------------------------------------
    //     // Validate Assignment
    //     // ---------------------------------------------------------------------

    //     /// TODO:
    //     /// - Add assignment checks here

    //     // ---------------------------------------------------------------------
    //     // Migrate
    //     // ---------------------------------------------------------------------

    //     /// TODO:
    //     /// - Add migration here

    //     // ---------------------------------------------------------------------
    //     // Activate VM
    //     // ---------------------------------------------------------------------

    //     if (tls.active_vmid != vmid) {
    //         if (syscall::BF_INVALID_ID != tls.active_vmid) {
    //             ret = vm_pool.set_inactive(tls, tls.active_vmid);
    //             if (bsl::unlikely(!ret)) {
    //                 bsl::print<bsl::V>() << bsl::here();
    //                 return ret;
    //             }

    //             bsl::touch();
    //         }
    //         else {
    //             bsl::touch();
    //         }

    //         ret = vm_pool.set_active(tls, vmid);
    //         if (bsl::unlikely(!ret)) {
    //             bsl::print<bsl::V>() << bsl::here();
    //             return ret;
    //         }

    //         bsl::touch();
    //     }
    //     else {
    //         bsl::touch();
    //     }

    //     // ---------------------------------------------------------------------
    //     // Activate VP
    //     // ---------------------------------------------------------------------

    //     if (tls.active_vpid != vpid) {
    //         if (syscall::BF_INVALID_ID != tls.active_vpid) {
    //             ret = vp_pool.set_inactive(tls, tls.active_vpid);
    //             if (bsl::unlikely(!ret)) {
    //                 bsl::print<bsl::V>() << bsl::here();
    //                 return ret;
    //             }

    //             bsl::touch();
    //         }
    //         else {
    //             bsl::touch();
    //         }

    //         ret = vp_pool.set_active(tls, vpid);
    //         if (bsl::unlikely(!ret)) {
    //             bsl::print<bsl::V>() << bsl::here();
    //             return ret;
    //         }

    //         bsl::touch();
    //     }
    //     else {
    //         bsl::touch();
    //     }

    //     // ---------------------------------------------------------------------
    //     // Activate VPS
    //     // ---------------------------------------------------------------------

    //     if (tls.active_vpsid != vpsid) {
    //         if (syscall::BF_INVALID_ID != tls.active_vpsid) {
    //             ret = vps_pool.set_inactive(tls, intrinsic, tls.active_vpsid);
    //             if (bsl::unlikely(!ret)) {
    //                 bsl::print<bsl::V>() << bsl::here();
    //                 return ret;
    //             }

    //             bsl::touch();
    //         }
    //         else {
    //             bsl::touch();
    //         }

    //         ret = vps_pool.set_active(tls, intrinsic, vpsid);
    //         if (bsl::unlikely(!ret)) {
    //             bsl::print<bsl::V>() << bsl::here();
    //             return ret;
    //         }

    //         bsl::touch();
    //     }
    //     else {
    //         bsl::touch();
    //     }

    //     // ---------------------------------------------------------------------
    //     // Done
    //     // ---------------------------------------------------------------------

    //     return_to_mk(bsl::exit_success);

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_run_current syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @param tls the current TLS block
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT>
    // [[nodiscard]] inline auto
    // syscall_vps_op_run_current_failure(TLS_CONCEPT &tls) -> bsl::errc_type
    // {
    //     return_to_mk(bsl::exit_success);

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_advance_ip syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_advance_ip_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.advance_ip(tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg1))};
    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return ret;
    //     }

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_advance_ip_and_run_current syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_advance_ip_and_run_current_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.advance_ip(tls, intrinsic, tls.active_vpsid)};
    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return ret;
    //     }

    //     return_to_mk(bsl::exit_success);

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_promote syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_promote_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.vps_to_state_save(
    //         tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg1), *tls.root_vp_state)};

    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return ret;
    //     }

    //     promote(tls.root_vp_state);

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    // /// <!-- description -->
    // ///   @brief Implements the bf_vps_op_clear_vps syscall
    // ///
    // /// <!-- inputs/outputs -->
    // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    // ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    // ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    // ///   @param tls the current TLS block
    // ///   @param intrinsic the intrinsics to use
    // ///   @param vps_pool the VPS pool to use
    // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    // ///     otherwise
    // ///
    // template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VPS_POOL_CONCEPT>
    // [[nodiscard]] constexpr auto
    // syscall_vps_op_clear_vps_failure(
    //     TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, VPS_POOL_CONCEPT &vps_pool)
    //     -> bsl::errc_type
    // {
    //     auto const ret{vps_pool.clear(tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg1))};
    //     if (bsl::unlikely(!ret)) {
    //         bsl::print<bsl::V>() << bsl::here();
    //         return ret;
    //     }

    //     tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
    //     return bsl::errc_success;
    // }

    /// <!-- description -->
    ///   @brief Dispatches the bf_vps_op syscalls
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_CONCEPT defines the type of ext_t to use
    ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
    ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    ///   @param tls the current TLS block
    ///   @param ext the extension that made the syscall
    ///   @param intrinsic the intrinsics to use
    ///   @param page_pool the page pool to use
    ///   @param vm_pool the VM pool to use
    ///   @param vp_pool the VP pool to use
    ///   @param vps_pool the VPS pool to use
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<
        typename TLS_CONCEPT,
        typename EXT_CONCEPT,
        typename INTRINSIC_CONCEPT,
        typename PAGE_POOL_CONCEPT,
        typename VM_POOL_CONCEPT,
        typename VP_POOL_CONCEPT,
        typename VPS_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    dispatch_syscall_vps_op_failure(
        TLS_CONCEPT &tls,
        EXT_CONCEPT &ext,
        INTRINSIC_CONCEPT &intrinsic,
        PAGE_POOL_CONCEPT &page_pool,
        VM_POOL_CONCEPT &vm_pool,
        VP_POOL_CONCEPT &vp_pool,
        VPS_POOL_CONCEPT &vps_pool) -> bsl::errc_type
    {
        bsl::errc_type ret{};

        bsl::discard(tls);
        bsl::discard(ext);
        bsl::discard(intrinsic);
        bsl::discard(page_pool);
        bsl::discard(vm_pool);
        bsl::discard(vp_pool);
        bsl::discard(vps_pool);

        switch (syscall::bf_syscall_index(tls.ext_syscall).get()) {
            case syscall::BF_VPS_OP_CREATE_VPS_IDX_VAL.get(): {
                ret = syscall_vps_op_create_vps_failure(tls, page_pool, vps_pool);
                return ret;
            }

            case syscall::BF_VPS_OP_DESTROY_VPS_IDX_VAL.get(): {
                ret = syscall_vps_op_destroy_vps_failure(tls, vps_pool);
                return ret;
            }

            // case syscall::BF_VPS_OP_INIT_AS_ROOT_IDX_VAL.get(): {
            //     ret = syscall_vps_op_init_as_root_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_READ8_IDX_VAL.get(): {
            //     ret = syscall_vps_op_read8_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_READ16_IDX_VAL.get(): {
            //     ret = syscall_vps_op_read16_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_READ32_IDX_VAL.get(): {
            //     ret = syscall_vps_op_read32_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_READ64_IDX_VAL.get(): {
            //     ret = syscall_vps_op_read64_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_WRITE8_IDX_VAL.get(): {
            //     ret = syscall_vps_op_write8_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_WRITE16_IDX_VAL.get(): {
            //     ret = syscall_vps_op_write16_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_WRITE32_IDX_VAL.get(): {
            //     ret = syscall_vps_op_write32_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_WRITE64_IDX_VAL.get(): {
            //     ret = syscall_vps_op_write64_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_READ_REG_IDX_VAL.get(): {
            //     ret = syscall_vps_op_read_reg_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_WRITE_REG_IDX_VAL.get(): {
            //     ret = syscall_vps_op_write_reg_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_RUN_IDX_VAL.get(): {
            //     ret = syscall_vps_op_run_failure(tls, intrinsic, vm_pool, vp_pool, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_RUN_CURRENT_IDX_VAL.get(): {
            //     ret = syscall_vps_op_run_current_failure(tls);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_ADVANCE_IP_IDX_VAL.get(): {
            //     ret = syscall_vps_op_advance_ip_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_ADVANCE_IP_AND_RUN_CURRENT_IDX_VAL.get(): {
            //     ret = syscall_vps_op_advance_ip_and_run_current_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_PROMOTE_IDX_VAL.get(): {
            //     ret = syscall_vps_op_promote_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            // case syscall::BF_VPS_OP_CLEAR_VPS_IDX_VAL.get(): {
            //     ret = syscall_vps_op_clear_vps_failure(tls, intrinsic, vps_pool);
            //     return ret;
            // }

            default: {
                break;
            }
        }

        return bsl::errc_success;
    }
}

#endif
