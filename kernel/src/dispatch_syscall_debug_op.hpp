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

#ifndef DISPATCH_SYSCALL_DEBUG_OP_HPP
#define DISPATCH_SYSCALL_DEBUG_OP_HPP

#include <mk_interface.hpp>

#include <bsl/char_type.hpp>
#include <bsl/cstr_type.hpp>
#include <bsl/debug.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Dispatches the bf_debug_op syscalls
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_POOL_CONCEPT defines the type of extension pool to use
    ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
    ///   @tparam HUGE_POOL_CONCEPT defines the type of huge pool to use
    ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @tparam VMEXIT_LOG_CONCEPT defines the type of VMExit log to use
    ///   @param tls the current TLS block
    ///   @param ext_pool the extension pool to use
    ///   @param intrinsic the intrinsics to use
    ///   @param page_pool the page pool to use
    ///   @param huge_pool the huge pool to use
    ///   @param vps_pool the VPS pool to use
    ///   @param vp_pool the VP pool to use
    ///   @param vm_pool the VM pool to use
    ///   @param log the VMExit log to use
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    /// <!-- exception safety -->
    ///   @note IMPORTANT: This call assumes exceptions ARE POSSIBLE and
    ///     that state reversal MIGHT BE REQUIRED.
    ///
    template<
        typename TLS_CONCEPT,
        typename EXT_POOL_CONCEPT,
        typename INTRINSIC_CONCEPT,
        typename PAGE_POOL_CONCEPT,
        typename HUGE_POOL_CONCEPT,
        typename VPS_POOL_CONCEPT,
        typename VP_POOL_CONCEPT,
        typename VM_POOL_CONCEPT,
        typename VMEXIT_LOG_CONCEPT>
    [[nodiscard]] constexpr auto
    dispatch_syscall_debug_op(
        TLS_CONCEPT &tls,
        EXT_POOL_CONCEPT &ext_pool,
        INTRINSIC_CONCEPT &intrinsic,
        PAGE_POOL_CONCEPT &page_pool,
        HUGE_POOL_CONCEPT &huge_pool,
        VPS_POOL_CONCEPT &vps_pool,
        VP_POOL_CONCEPT &vp_pool,
        VM_POOL_CONCEPT &vm_pool,
        VMEXIT_LOG_CONCEPT &log) noexcept -> bsl::errc_type
    {
        switch (syscall::bf_syscall_index(tls.ext_syscall).get()) {
            case syscall::BF_DEBUG_OP_OUT_IDX_VAL.get(): {
                bsl::print() << bsl::hex(tls.ext_reg0)    //--
                             << " "                       //--
                             << bsl::hex(tls.ext_reg1)    //--
                             << bsl::endl;                //--

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            case syscall::BF_DEBUG_OP_DUMP_VM_IDX_VAL.get(): {
                vm_pool.dump(tls, bsl::to_u16_unsafe(tls.ext_reg0));

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            case syscall::BF_DEBUG_OP_DUMP_VP_IDX_VAL.get(): {
                vp_pool.dump(tls, bsl::to_u16_unsafe(tls.ext_reg0));

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            case syscall::BF_DEBUG_OP_DUMP_VPS_IDX_VAL.get(): {
                vps_pool.dump(tls, intrinsic, bsl::to_u16_unsafe(tls.ext_reg0));

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            case syscall::BF_DEBUG_OP_DUMP_VMEXIT_LOG_IDX_VAL.get(): {
                log.dump(bsl::to_u16_unsafe(tls.ext_reg0));

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            case syscall::BF_DEBUG_OP_WRITE_C_IDX_VAL.get(): {
                bsl::print() << static_cast<bsl::char_type>(bsl::to_u8(tls.ext_reg0).get());

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            case syscall::BF_DEBUG_OP_WRITE_STR_IDX_VAL.get(): {

                /// NOTE:
                /// - This is the only syscall that might produce an
                ///   exception, and that is due to the need to access user
                ///   space memory. If this occurs, reversal is not needed.
                /// - The function is still marked as exception unsafe, but
                ///   in reality, if an exception fires, there is nothing to
                ///   do, and likely will just result in corrupt debugging
                ///   information.
                ///

                bsl::print() << bsl::to_ptr<bsl::cstr_type>(tls.ext_reg0);

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            case syscall::BF_DEBUG_OP_DUMP_EXT_IDX_VAL.get(): {
                ext_pool.dump(tls, bsl::to_u16_unsafe(tls.ext_reg0));

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            case syscall::BF_DEBUG_OP_DUMP_PAGE_POOL_IDX_VAL.get(): {
                page_pool.dump();

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            case syscall::BF_DEBUG_OP_DUMP_HUGE_POOL_IDX_VAL.get(): {
                huge_pool.dump();

                tls.syscall_ret_status = syscall::BF_STATUS_SUCCESS.get();
                return bsl::errc_success;
            }

            default: {
                break;
            }
        }

        bsl::error() << "unknown syscall index: "    //--
                     << bsl::hex(tls.ext_syscall)    //--
                     << bsl::endl                    //--
                     << bsl::here();                 //--

        tls.syscall_ret_status = syscall::BF_STATUS_FAILURE_UNSUPPORTED.get();
        return bsl::errc_failure;
    }
}

#endif
