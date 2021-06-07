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

#include <dispatch_syscall_callback_op.hpp>
#include <dispatch_syscall_control_op.hpp>
#include <dispatch_syscall_debug_op.hpp>
#include <dispatch_syscall_handle_op.hpp>
#include <dispatch_syscall_intrinsic_op.hpp>
#include <dispatch_syscall_mem_op.hpp>
#include <dispatch_syscall_vm_op.hpp>
#include <dispatch_syscall_vp_op.hpp>
#include <dispatch_syscall_vps_op.hpp>
#include <mk_interface.hpp>
#include <tls_t.hpp>

#include <bsl/debug.hpp>
#include <bsl/exit_code.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Provides the main entry point for all syscalls. This function
    ///     will dispatch syscalls as needed.
    ///
    /// <!-- inputs/outputs -->

    ///   @tparam EXT_POOL_CONCEPT defines the type of extension pool to use
    ///   @tparam EXT_CONCEPT defines the type of extension to use
    ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
    ///   @tparam HUGE_POOL_CONCEPT defines the type of huge pool to use
    ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @tparam VMEXIT_LOG_CONCEPT defines the type of VMExit log to use
    ///   @param tls the current TLS block
    ///   @param ext_pool the extension pool to use
    ///   @param ext the extension that made the syscall
    ///   @param intrinsic the intrinsics to use
    ///   @param page_pool the page pool to use
    ///   @param huge_pool the huge pool to use
    ///   @param vps_pool the VPS pool to use
    ///   @param vp_pool the VP pool to use
    ///   @param vm_pool the VM pool to use
    ///   @param log the VMExit log to use
    ///   @return Returns bsl::exit_success on success, bsl::exit_failure
    ///     otherwise
    ///
    template<
        typename EXT_POOL_CONCEPT,
        typename EXT_CONCEPT,
        typename INTRINSIC_CONCEPT,
        typename PAGE_POOL_CONCEPT,
        typename HUGE_POOL_CONCEPT,
        typename VPS_POOL_CONCEPT,
        typename VP_POOL_CONCEPT,
        typename VM_POOL_CONCEPT,
        typename VMEXIT_LOG_CONCEPT>
    [[nodiscard]] constexpr auto
    dispatch_syscall(
        tls_t &tls,
        EXT_POOL_CONCEPT &ext_pool,
        EXT_CONCEPT &ext,
        INTRINSIC_CONCEPT &intrinsic,
        PAGE_POOL_CONCEPT &page_pool,
        HUGE_POOL_CONCEPT &huge_pool,
        VPS_POOL_CONCEPT &vps_pool,
        VP_POOL_CONCEPT &vp_pool,
        VM_POOL_CONCEPT &vm_pool,
        VMEXIT_LOG_CONCEPT &log) noexcept -> bsl::exit_code
    {
        bsl::errc_type ret{};

        switch (syscall::bf_syscall_opcode(tls.ext_syscall).get()) {
            case syscall::BF_CONTROL_OP_VAL.get(): {
                ret = dispatch_syscall_control_op(tls, ext);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                return bsl::exit_success;
            }

            case syscall::BF_HANDLE_OP_VAL.get(): {
                ret = dispatch_syscall_handle_op(tls, ext);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                return bsl::exit_success;
            }

            case syscall::BF_DEBUG_OP_VAL.get(): {
                ret = dispatch_syscall_debug_op(
                    tls,
                    ext_pool,
                    intrinsic,
                    page_pool,
                    huge_pool,
                    vps_pool,
                    vp_pool,
                    vm_pool,
                    log);

                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                return bsl::exit_success;
            }

            case syscall::BF_CALLBACK_OP_VAL.get(): {
                ret = dispatch_syscall_callback_op(tls, ext);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                return bsl::exit_success;
            }

            case syscall::BF_VM_OP_VAL.get(): {
                ret = dispatch_syscall_vm_op(tls, ext_pool, ext, vm_pool, vp_pool);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                return bsl::exit_success;
            }

            case syscall::BF_VP_OP_VAL.get(): {
                ret = dispatch_syscall_vp_op(tls, ext, vm_pool, vp_pool, vps_pool);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                return bsl::exit_success;
            }

            case syscall::BF_VPS_OP_VAL.get(): {
                ret = dispatch_syscall_vps_op(
                    tls, ext, intrinsic, page_pool, vm_pool, vp_pool, vps_pool);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                return bsl::exit_success;
            }

            case syscall::BF_INTRINSIC_OP_VAL.get(): {
                ret = dispatch_syscall_intrinsic_op(tls, ext, intrinsic);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                return bsl::exit_success;
            }

            case syscall::BF_MEM_OP_VAL.get(): {
                ret = dispatch_syscall_mem_op(tls, ext);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                return bsl::exit_success;
            }

            default: {
                break;
            }
        }

        bsl::error() << "unknown syscall signature/opcode: "    //--
                     << bsl::hex(tls.ext_syscall)               //--
                     << bsl::endl                               //--
                     << bsl::here();                            //--

        tls.syscall_ret_status = syscall::BF_STATUS_FAILURE_UNSUPPORTED.get();
        return bsl::exit_failure;
    }
}

#endif
