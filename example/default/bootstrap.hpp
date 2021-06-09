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

#ifndef BOOTSTRAP_HPP
#define BOOTSTRAP_HPP

#include <bf_constants.hpp>
#include <bf_types.hpp>

#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/unlikely_assert.hpp>

namespace example
{
    /// <!-- description -->
    ///   @brief Implements the bootstrap function. This function is
    ///     called on each PP while the hypervisor is being bootstrapped.
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam BF_SYSCALL_TYPE the type of bf_syscall_t to use. Note that
    ///     we do not use syscall::bf_syscall_t directly as using a template
    ///     provides a simple way to unit test this code as each unit test
    ///     can provide a mock of syscall::bf_syscall_t that calls test code
    ///     instead of a real microkernel. If you do not plan on implementing
    ///     unit tests, this extra template logic can be removed.
    ///   @tparam VP_POOL_CONCEPT the type of vp_pool_t to use. Note that
    ///     we do not use example::vp_pool_t directly as using a template
    ///     provides a simple way to unit test this code as each unit test
    ///     can provide a mock of example::vp_pool_t that calls test code
    ///     instead of a real microkernel. If you do not plan on implementing
    ///     unit tests, this extra template logic can be removed.
    ///   @tparam VPS_POOL_CONCEPT the type of vps_pool_t to use. Note that
    ///     we do not use example::vps_pool_t directly as using a template
    ///     provides a simple way to unit test this code as each unit test
    ///     can provide a mock of example::vps_pool_t that calls test code
    ///     instead of a real microkernel. If you do not plan on implementing
    ///     unit tests, this extra template logic can be removed.
    ///   @param ppid the physical process to bootstrap
    ///
    template<typename BF_SYSCALL_TYPE, typename VP_POOL_CONCEPT, typename VPS_POOL_CONCEPT>
    [[nodiscard]] constexpr auto
    bootstrap(
        BF_SYSCALL_TYPE &sys,
        VP_POOL_CONCEPT &vp_pool,
        VPS_POOL_CONCEPT &vps_pool,
        syscall::bf_uint16_t const &ppid) noexcept -> bsl::errc_type
    {
        /// NOTE:
        /// - In order to execcute bf_vps_op_run, which is what executes
        ///   hypervisor, we must have a VM, VP and VPS.
        /// - The root VM is already created for us, so we don't need to
        ///   create this ourselves. You only need to create VM's if you plan
        ///   to add guest support with your extensions.
        /// - The VP in this simple example does nothing, but we still need
        ///   to create one. The VP is used when you have more than one VPS
        ///   per VP (e.g., if you are implementing HyperV's VSM, or nested
        ///   virtualization support). Otherwise, you will always have one VP
        ///   for each VPS.
        /// - The VPS is what stores the state associated with the VPS. It is
        ///   the thing that does most of the work, including storing the
        ///   VMCS/VMCB and other CPU register state that is needed.
        ///

        auto const vpid{vp_pool.allocate(sys, syscall::BF_ROOT_VMID, ppid)};
        if (bsl::unlikely_assert(!vpid)) {
            bsl::print<bsl::V>() << bsl::here();
            return bsl::errc_failure;
        }

        auto const vpsid{vps_pool.allocate(sys, vpid, ppid)};
        if (bsl::unlikely_assert(!vpsid)) {
            bsl::print<bsl::V>() << bsl::here();
            return bsl::errc_failure;
        }

        /// NOTE:
        /// - Run the newly created VP on behalf of the root VM using the
        ///   newly created and initialized VPS.
        ///

        return sys.bf_vps_op_run(syscall::BF_ROOT_VMID, vpid, vpsid);
    }
}

#endif
