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

#ifndef DISPATCH_SYSCALL_HPP
#define DISPATCH_SYSCALL_HPP

#include <bf_constants.hpp>
#include <dispatch_syscall_callback_op.hpp>
#include <dispatch_syscall_control_op.hpp>
#include <dispatch_syscall_debug_op.hpp>
#include <dispatch_syscall_handle_op.hpp>
#include <dispatch_syscall_intrinsic_op.hpp>
#include <dispatch_syscall_mem_op.hpp>
#include <dispatch_syscall_vm_op.hpp>
#include <dispatch_syscall_vp_op.hpp>
#include <dispatch_syscall_vps_op.hpp>
#include <ext_pool_t.hpp>
#include <ext_t.hpp>
#include <huge_pool_t.hpp>
#include <intrinsic_t.hpp>
#include <page_pool_t.hpp>
#include <tls_t.hpp>
#include <vm_pool_t.hpp>
#include <vmexit_log_t.hpp>
#include <vp_pool_t.hpp>
#include <vps_pool_t.hpp>

#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Provides the main entry point for all syscalls. This function
    ///     will dispatch syscalls as needed.
    ///
    /// <!-- inputs/outputs -->
    ///   @param mut_tls the current TLS block
    ///   @param mut_page_pool the page pool to use
    ///   @param mut_huge_pool the huge pool to use
    ///   @param mut_intrinsic the intrinsics to use
    ///   @param mut_vm_pool the VM pool to use
    ///   @param mut_vp_pool the VP pool to use
    ///   @param mut_vps_pool the VPS pool to use
    ///   @param mut_ext_pool the extension pool to use
    ///   @param mut_ext the extension that made the syscall
    ///   @param mut_log the VMExit log to use
    ///   @return Returns a bf_status_t containing success or failure
    ///
    [[nodiscard]] constexpr auto
    dispatch_syscall(
        tls_t &mut_tls,
        page_pool_t &mut_page_pool,
        huge_pool_t &mut_huge_pool,
        intrinsic_t &mut_intrinsic,
        vm_pool_t &mut_vm_pool,
        vp_pool_t &mut_vp_pool,
        vps_pool_t &mut_vps_pool,
        ext_pool_t &mut_ext_pool,
        ext_t &mut_ext,
        vmexit_log_t &mut_log) noexcept -> syscall::bf_status_t
    {
        switch (syscall::bf_syscall_opcode(bsl::to_u64(mut_tls.ext_syscall)).get()) {
            case syscall::BF_CONTROL_OP_VAL.get(): {
                auto const ret{dispatch_syscall_control_op(mut_tls, mut_ext)};
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_HANDLE_OP_VAL.get(): {
                auto const ret{dispatch_syscall_handle_op(mut_tls, mut_ext)};
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_DEBUG_OP_VAL.get(): {
                auto const ret{dispatch_syscall_debug_op(
                    mut_tls,
                    mut_page_pool,
                    mut_huge_pool,
                    mut_intrinsic,
                    mut_vm_pool,
                    mut_vp_pool,
                    mut_vps_pool,
                    mut_ext_pool,
                    mut_log)};

                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_CALLBACK_OP_VAL.get(): {
                auto const ret{dispatch_syscall_callback_op(mut_tls, mut_ext)};
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_VM_OP_VAL.get(): {
                auto const ret{dispatch_syscall_vm_op(
                    mut_tls, mut_page_pool, mut_vm_pool, mut_vp_pool, mut_ext_pool, mut_ext)};
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_VP_OP_VAL.get(): {
                auto const ret{dispatch_syscall_vp_op(mut_tls, mut_vp_pool, mut_vps_pool, mut_ext)};
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_VPS_OP_VAL.get(): {
                auto const ret{dispatch_syscall_vps_op(
                    mut_tls,
                    mut_page_pool,
                    mut_intrinsic,
                    mut_vm_pool,
                    mut_vp_pool,
                    mut_vps_pool,
                    mut_ext)};

                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_INTRINSIC_OP_VAL.get(): {
                auto const ret{dispatch_syscall_intrinsic_op(mut_tls, mut_intrinsic, mut_ext)};
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_MEM_OP_VAL.get(): {
                auto const ret{
                    dispatch_syscall_mem_op(mut_tls, mut_page_pool, mut_huge_pool, mut_ext)};
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            default: {
                break;
            }
        }

        bsl::error() << "unknown syscall signature/opcode "    //--
                     << bsl::hex(mut_tls.ext_syscall)          //--
                     << bsl::endl                              //--
                     << bsl::here();                           //--

        return syscall::BF_STATUS_FAILURE_UNSUPPORTED;
    }
}

#endif
