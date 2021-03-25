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

#ifndef TEST_DISPATCH_SYSCALL_VPS_OP_HPP
#define TEST_DISPATCH_SYSCALL_VPS_OP_HPP

#include <mk_interface.hpp>

#include <bsl/discard.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Dispatches the bf_vps_op syscalls
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
    ///   @tparam EXT_CONCEPT defines the type of ext_t to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
    ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    ///   @param tls the current TLS block
    ///   @param ext_pool the extension pool to use
    ///   @param ext the extension that made the syscall
    ///   @param vm_pool the VM pool to use
    ///   @param vp_pool the VP pool to use
    ///   @param vps_pool the VPS pool to use
    ///   @return Returns syscall::BF_STATUS_SUCCESS on success or an error
    ///     code on failure.
    ///
    template<
        typename TLS_CONCEPT,
        typename EXT_POOL_CONCEPT,
        typename EXT_CONCEPT,
        typename VM_POOL_CONCEPT,
        typename VP_POOL_CONCEPT,
        typename VPS_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    dispatch_syscall_vps_op(
        TLS_CONCEPT &tls,
        EXT_POOL_CONCEPT &ext_pool,
        EXT_CONCEPT &ext,
        VM_POOL_CONCEPT &vm_pool,
        VP_POOL_CONCEPT &vp_pool,
        VPS_POOL_CONCEPT &vps_pool) -> syscall::bf_status_t
    {
        bsl::discard(tls);
        bsl::discard(ext_pool);
        bsl::discard(ext);
        bsl::discard(vm_pool);
        bsl::discard(vp_pool);
        bsl::discard(vps_pool);

        return syscall::BF_STATUS_SUCCESS;
    }
}

#endif
