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

#include <bootstrap.hpp>
// #include <fast_fail.hpp>
#include <bf_control_ops.hpp>
#include <bf_syscall_t.hpp>
#include <intrinsic_t.hpp>
#include <vmexit_t.hpp>
#include <vp_pool_t.hpp>
#include <vp_t.hpp>
#include <vps_pool_t.hpp>
#include <vps_t.hpp>

#include <bsl/convert.hpp>
#include <bsl/debug.hpp>
#include <bsl/unlikely_assert.hpp>

namespace example
{
    /// @brief stores the bf_syscall_t that this code will use
    constinit syscall::bf_syscall_t<bsl::to_umax(HYPERVISOR_EXT_DIRECT_MAP_ADDR).get()> g_sys{};
    /// @brief stores the vmexit_t that this code will use
    constinit vmexit_t g_vmexit{};
    /// @brief stores the intrinsic_t that this code will use
    constinit intrinsic_t g_intrinsic{};
    /// @brief stores the pool of VPs that we will use
    constinit vp_pool_t<vp_t, bsl::to_umax(HYPERVISOR_MAX_VPS).get()> g_vp_pool{};
    /// @brief stores the pool of VPSs that we will use
    constinit vps_pool_t<vps_t, bsl::to_umax(HYPERVISOR_MAX_VPSS).get()> g_vps_pool{};

    /// <!-- description -->
    ///   @brief Implements the VMExit entry function. This is registered
    ///     by the main function to execute whenever a VMExit occurs.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vpsid the ID of the VPS that generated the VMExit
    ///   @param exit_reason the exit reason associated with the VMExit
    ///
    void
    // NOLINTNEXTLINE(bsl-non-safe-integral-types-are-forbidden)
    vmexit_entry(
        syscall::bf_uint16_t::value_type const vpsid,
        syscall::bf_uint64_t::value_type const exit_reason) noexcept
    {
        bsl::errc_type ret{};

        /// NOTE:
        /// - Call into the vmexit handler. This entry point serves as a
        ///   trampoline between C and C++. Specifically, the microkernel
        ///   cannot call a template function directly, and can only call
        ///   a C style function.
        ///

        ret = g_vmexit.dispatch(g_sys, g_intrinsic, vpsid, exit_reason);
        if (bsl::unlikely_assert(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::bf_control_op_exit();
        }

        /// NOTE:
        /// - This code should never be reached. The VMExit handler should
        ///   always call one of the "run" ABIs to return back to the
        ///   microkernel when a VMExit is finished. If this is called, it
        ///   is because the VMExit handler returned with an error.
        ///

        return syscall::bf_control_op_exit();
    }

    /// <!-- description -->
    ///   @brief Implements the fast fail entry function. This is registered
    ///     by the main function to execute whenever a fast fail occurs.
    ///
    /// <!-- inputs/outputs -->
    ///   @param fail_reason the exit reason associated with the fail
    ///
    void
    // NOLINTNEXTLINE(bsl-non-safe-integral-types-are-forbidden)
    fail_entry(
        syscall::bf_uint16_t::value_type const vpsid,
        syscall::bf_status_t::value_type const fail_reason) noexcept
    {
        // bsl::errc_type ret{};

        /// NOTE:
        /// - Call into the fast fail handler. This entry point serves as a
        ///   trampoline between C and C++. Specifically, the microkernel
        ///   cannot call a template function directly, and can only call
        ///   a C style function.
        ///

        // ret = fast_fail(g_sys, vpsid, fail_reason);
        // if (bsl::unlikely_assert(!ret)) {
        //     bsl::print<bsl::V>() << bsl::here();
        //     return syscall::bf_control_op_exit();
        // }

        /// NOTE:
        /// - This code should never be reached. The fast fail handler should
        ///   always call one of the "run" ABIs to return back to the
        ///   microkernel when a fast fail is finished. If this is called, it
        ///   is because the fast fail handler returned with an error.
        ///

        return syscall::bf_control_op_exit();
    }

    /// <!-- description -->
    ///   @brief Implements the bootstrap entry function. This function is
    ///     called on each PP while the hypervisor is being bootstrapped.
    ///
    /// <!-- inputs/outputs -->
    ///   @param ppid the physical process to bootstrap
    ///
    void
    // NOLINTNEXTLINE(bsl-non-safe-integral-types-are-forbidden)
    bootstrap_entry(syscall::bf_uint16_t::value_type const ppid) noexcept
    {
        bsl::errc_type ret{};

        /// NOTE:
        /// - Call into the bootstrap handler. This entry point serves as a
        ///   trampoline between C and C++. Specifically, the microkernel
        ///   cannot call a template function directly, and can only call
        ///   a C style function.
        ///

        ret = bootstrap(g_sys, g_vp_pool, g_vps_pool, ppid);
        if (bsl::unlikely_assert(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::bf_control_op_exit();
        }

        /// NOTE:
        /// - This code should never be reached. The bootstrap handler should
        ///   always call one of the "run" ABIs to return back to the
        ///   microkernel when a bootstrap is finished. If this is called, it
        ///   is because the bootstrap handler returned with an error.
        ///

        return syscall::bf_control_op_exit();
    }

    /// <!-- description -->
    ///   @brief Implements the main entry function for this example
    ///
    /// <!-- inputs/outputs -->
    ///   @param version the version of the spec implemented by the
    ///     microkernel. This can be used to ensure the extension and the
    ///     microkernel speak the same ABI.
    ///
    extern "C" void
    ext_main_entry(bsl::uint32 const version) noexcept
    {
        bsl::errc_type ret{};

        /// NOTE:
        /// - Initialize the bf_syscall_t. This will validate the ABI version,
        ///   open a handle to the microkernel and register the required
        ///   callbacks. If this fails, we call bf_control_op_exit, which is
        ///   similar to exit() from POSIX, except that the return value is
        ///   always the same.
        ///

        ret = g_sys.initialize(version, &bootstrap_entry, &vmexit_entry, &fail_entry);
        if (bsl::unlikely_assert(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::bf_control_op_exit();
        }

        /// NOTE:
        /// - Initialize the vp_pool_t. This will give all of our vp_t's
        ///   their IDs so that they can be allocated.
        ///

        ret = g_vp_pool.initialize();
        if (bsl::unlikely_assert(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::bf_control_op_exit();
        }

        /// NOTE:
        /// - Initialize the vps_pool_t. This will give all of our vps_t's
        ///   their IDs so that they can be allocated.
        ///

        ret = g_vps_pool.initialize();
        if (bsl::unlikely_assert(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::bf_control_op_exit();
        }

        /// NOTE:
        /// - Wait for callbacks. Note that this function does not return.
        ///   The next time the extension is executed, it will be the
        ///   bootstrap callback that was just previously registered, which
        ///   will be called on each PP that is online. Failure to call this
        ///   function leads to undefined behaviour (likely a page fault).
        /// - This is similar to the wait() function from POSIX after having
        ///   just started some processes, with the difference being that
        ///   this will never return, so there is no need to pass in status
        ///   as there is nothing to process after this call.
        ///

        syscall::bf_control_op_wait();
    }
}
