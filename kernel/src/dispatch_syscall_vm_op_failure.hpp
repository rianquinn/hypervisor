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

#ifndef DISPATCH_SYSCALL_VM_OP_FAILURE_HPP
#define DISPATCH_SYSCALL_VM_OP_FAILURE_HPP

#include <mk_interface.hpp>
#include <tls_t.hpp>

#include <bsl/convert.hpp>
#include <bsl/debug.hpp>
#include <bsl/finally.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Implements the bf_vm_op_create_vm syscall
    ///
    /// <!-- inputs/outputs -->

    ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
    ///   @param tls the current TLS block
    ///   @param ext_pool the extension pool to use
    ///   @param vm_pool the VM pool to use
    ///   @param vp_pool the VP pool to use
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename EXT_POOL_CONCEPT, typename VM_POOL_CONCEPT, typename VP_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    syscall_vm_op_create_vm_failure(
        tls_t &tls,
        EXT_POOL_CONCEPT &ext_pool,
        VM_POOL_CONCEPT &vm_pool,
        VP_POOL_CONCEPT &vp_pool) noexcept -> bsl::errc_type
    {
        bsl::errc_type ret{};

        if (!tls.state_reversal_required) {
            return bsl::errc_success;
        }

        ret = vm_pool.deallocate(tls, ext_pool, vp_pool, tls.log_vmid);
        if (bsl::unlikely(!bsl::success_or_precondition(ret))) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        ret = ext_pool.signal_vm_destroyed(tls, tls.log_vmid);
        if (bsl::unlikely(!bsl::success_or_precondition(ret))) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        return bsl::errc_success;
    }

    /// <!-- description -->
    ///   @brief Implements the bf_vm_op_destroy_vm syscall
    ///
    /// <!-- inputs/outputs -->

    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @param tls the current TLS block
    ///   @param vm_pool the VM pool to use
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename VM_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    syscall_vm_op_destroy_vm_failure(tls_t &tls, VM_POOL_CONCEPT &vm_pool) noexcept
        -> bsl::errc_type
    {
        bsl::errc_type ret{};

        if (!tls.state_reversal_required) {
            return bsl::errc_success;
        }

        ret = vm_pool.zombify(bsl::to_u16_unsafe(tls.ext_reg1));
        if (bsl::unlikely(!bsl::success_or_precondition(ret))) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        return bsl::errc_success;
    }

    /// <!-- description -->
    ///   @brief Dispatches the bf_vm_op syscalls
    ///
    /// <!-- inputs/outputs -->

    ///   @tparam EXT_POOL_CONCEPT defines the type of extension pool to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
    ///   @param tls the current TLS block
    ///   @param ext_pool the extension pool to use
    ///   @param vm_pool the VM pool to use
    ///   @param vp_pool the VM pool to use
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename EXT_POOL_CONCEPT, typename VM_POOL_CONCEPT, typename VP_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    dispatch_syscall_vm_op_failure(
        tls_t &tls,
        EXT_POOL_CONCEPT &ext_pool,
        VM_POOL_CONCEPT &vm_pool,
        VP_POOL_CONCEPT &vp_pool) noexcept -> bsl::errc_type
    {
        bsl::errc_type ret{};

        switch (syscall::bf_syscall_index(tls.ext_syscall).get()) {
            case syscall::BF_VM_OP_CREATE_VM_IDX_VAL.get(): {
                ret = syscall_vm_op_create_vm_failure(tls, ext_pool, vm_pool, vp_pool);
                return ret;
            }

            case syscall::BF_VM_OP_DESTROY_VM_IDX_VAL.get(): {
                ret = syscall_vm_op_destroy_vm_failure(tls, vm_pool);
                return ret;
            }

            default: {
                break;
            }
        }

        return bsl::errc_success;
    }
}

#endif
