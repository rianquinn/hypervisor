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

#ifndef DISPATCH_SYSCALL_VM_OP_HPP
#define DISPATCH_SYSCALL_VM_OP_HPP

#include <mk_interface.hpp>

#include <bsl/convert.hpp>
#include <bsl/debug.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Implements the bf_vm_op_create_vm syscall
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @param tls the current TLS block
    ///   @param ext_pool the extension pool to use
    ///   @param vm_pool the VM pool to use
    ///   @return Returns syscall::BF_STATUS_SUCCESS on success or an error
    ///     code on failure.
    ///
    template<typename TLS_CONCEPT, typename EXT_POOL_CONCEPT, typename VM_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    syscall_vm_op_create_vm(TLS_CONCEPT &tls, EXT_POOL_CONCEPT &ext_pool, VM_POOL_CONCEPT &vm_pool)
        -> syscall::bf_status_t
    {
        auto const vmid{vm_pool.allocate()};
        if (bsl::unlikely(!vmid)) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::BF_STATUS_FAILURE_UNKNOWN;
        }

        if (bsl::unlikely(!ext_pool.signal_vm_created(vmid))) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::BF_STATUS_FAILURE_UNKNOWN;
        }

        constexpr bsl::safe_uintmax mask{0xFFFFFFFFFFFF0000U};
        tls.ext_reg0 = ((tls.ext_reg0 & mask) | bsl::to_umax(vmid)).get();
        return syscall::BF_STATUS_SUCCESS;
    }

    /// <!-- description -->
    ///   @brief Implements the bf_vm_op_destroy_vm syscall
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @param tls the current TLS block
    ///   @param ext_pool the extension pool to use
    ///   @param vm_pool the VM pool to use
    ///   @return Returns syscall::BF_STATUS_SUCCESS on success or an error
    ///     code on failure.
    ///
    template<typename TLS_CONCEPT, typename EXT_POOL_CONCEPT, typename VM_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    syscall_vm_op_destroy_vm(TLS_CONCEPT &tls, EXT_POOL_CONCEPT &ext_pool, VM_POOL_CONCEPT &vm_pool)
        -> syscall::bf_status_t
    {
        /// TODO:
        /// - This does not prevent you from destroying a VM that is
        ///   active on a different PP. Note that we will need to create
        ///   a TLS pool to solve this. Setting the active VM will
        ///   require holding a lock so that we don't set the active VM
        ///   on one core that is being destroyed.
        ///

        auto const vmid{bsl::to_u16_unsafe(tls.ext_reg1)};
        if (bsl::unlikely(vmid.is_zero())) {
            bsl::error() << "cannot destory the root vm"    // --
                         << bsl::endl                       // --
                         << bsl::here();                    // --

            return syscall::BF_STATUS_FAILURE_UNKNOWN;
        }

        if (bsl::unlikely(tls.vmid() == vmid)) {
            bsl::error() << "cannot destory vm "            // --
                         << bsl::hex(vmid)                  // --
                         << " as it is currently active"    // --
                         << bsl::endl                       // --
                         << bsl::here();                    // --

            return syscall::BF_STATUS_FAILURE_UNKNOWN;
        }

        if (bsl::unlikely(!vm_pool.deallocate(vmid))) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::BF_STATUS_FAILURE_UNKNOWN;
        }

        if (bsl::unlikely(!ext_pool.signal_vm_destroyed(vmid))) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::BF_STATUS_FAILURE_UNKNOWN;
        }

        return syscall::BF_STATUS_SUCCESS;
    }

    /// <!-- description -->
    ///   @brief Dispatches the bf_vm_op syscalls
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
    ///   @tparam EXT_CONCEPT defines the type of ext_t to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @param tls the current TLS block
    ///   @param ext_pool the extension pool to use
    ///   @param ext the extension that made the syscall
    ///   @param vm_pool the VM pool to use
    ///   @return Returns syscall::BF_STATUS_SUCCESS on success or an error
    ///     code on failure.
    ///
    template<
        typename TLS_CONCEPT,
        typename EXT_POOL_CONCEPT,
        typename EXT_CONCEPT,
        typename VM_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    dispatch_syscall_vm_op(
        TLS_CONCEPT &tls,
        EXT_POOL_CONCEPT &ext_pool,
        EXT_CONCEPT const &ext,
        VM_POOL_CONCEPT &vm_pool) -> syscall::bf_status_t
    {
        syscall::bf_status_t ret{};

        if (bsl::unlikely(!ext.is_handle_valid(tls.ext_reg0))) {
            bsl::error() << "invalid handle: "        // --
                         << bsl::hex(tls.ext_reg0)    // --
                         << bsl::endl                 // --
                         << bsl::here();              // --

            return syscall::BF_STATUS_FAILURE_INVALID_HANDLE;
        }

        if (bsl::unlikely(tls.ext != tls.ext_vmexit)) {
            bsl::error() << "vm_ops not allowed by ext "            // --
                         << bsl::hex(ext.id())                      // --
                         << " as it didn't register for vmexits"    // --
                         << bsl::endl                               // --
                         << bsl::here();                            // --

            return syscall::BF_STATUS_FAILURE_UNKNOWN;
        }

        switch (syscall::bf_syscall_index(tls.ext_syscall).get()) {
            case syscall::BF_VM_OP_CREATE_VM_IDX_VAL.get(): {
                ret = syscall_vm_op_create_vm(tls, ext_pool, vm_pool);
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_VM_OP_DESTROY_VM_IDX_VAL.get(): {
                ret = syscall_vm_op_destroy_vm(tls, ext_pool, vm_pool);
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            default: {
                bsl::error() << "unknown syscall index: "    //--
                             << bsl::hex(tls.ext_syscall)    //--
                             << bsl::endl                    //--
                             << bsl::here();                 //--

                break;
            }
        }

        return syscall::BF_STATUS_FAILURE_UNKNOWN;
    }
}

#endif
