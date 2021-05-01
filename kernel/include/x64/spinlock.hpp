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

#ifndef SPINLOCK_HPP
#define SPINLOCK_HPP

#include <mk_interface.hpp>

#include <bsl/debug.hpp>
#include <bsl/is_constant_evaluated.hpp>
#include <bsl/safe_integral.hpp>

#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

namespace mk
{
    /// @class mk::spinlock
    ///
    /// <!-- description -->
    ///   @brief Implements a spinlock
    ///
    /// <!-- notes -->
    ///   @note This spinlock is designed to detect and prevent deadlock
    ///     when the same PP attempts to take the lock more than once. This
    ///     could occur for example if a hardware exception fires before
    ///     the lock is released. It also handles the case when the lock is
    ///     taken, and then an ESR fires that is legit and must take the
    ///     lock as well.
    ///
    class spinlock final
    {
        /// @brief stores the ppid that currently owns the lock (non-ESR)
        bsl::safe_uint16 m_std_ppid;
        /// @brief stores the ppid that currently owns the lock (ESR)
        bsl::safe_uint16 m_esr_ppid;
        /// @brief stores whether or not the lock is acquired
        _Atomic bool m_flag;

    public:
        /// <!-- description -->
        ///   @brief Default constructor.
        ///
        constexpr spinlock() noexcept    // --
            : m_std_ppid{syscall::BF_INVALID_ID}, m_esr_ppid{syscall::BF_INVALID_ID}
        {
            m_flag = false;
        }

        /// <!-- description -->
        ///   @brief Destructor
        ///
        constexpr ~spinlock() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr spinlock(spinlock const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr spinlock(spinlock &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] auto operator=(spinlock const &o) &noexcept -> spinlock & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] auto operator=(spinlock &&o) &noexcept -> spinlock & = default;

        /// <!-- description -->
        ///   @brief Locks the spinlock. This will not return until the
        ///     spinlock can be successfully acquired.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        lock(TLS_CONCEPT const &tls) noexcept
        {
            if (bsl::is_constant_evaluated()) {
                return;
            }

            /// NOTE:
            /// - Perform deadlock detection. If deadlock is detected, we
            ///   return as it means that this PP has already acquired the
            ///   lock with no means that unlock.
            ///

            if (tls.esr_rip == bsl::ZERO_UMAX) {
                if (tls.ppid == m_std_ppid) {
                    bsl::alert() << "pp "                                       // --
                                 << bsl::hex(tls.ppid)                          // --
                                 << " acquired the same lock more than once"    // --
                                 << bsl::endl;                                   // --

                    return;
                }

                bsl::touch();
            }
            else {
                if (tls.ppid == m_esr_ppid) {
                    bsl::alert() << "pp "                                                   // --
                                 << bsl::hex(tls.ppid)                                      // --
                                 << " acquired the same lock more than once from an ESR"    // --
                                 << bsl::endl;                                               // --

                    return;
                }

                bsl::touch();
            }

            /// NOTE:
            /// - The __c11_atomic_exchange here attempts to set the lock to
            ///   true. If it is already true, __c11_atomic_exchange will
            ///   return true, which means that the lock was already taken
            ///   by another PP. If this occurs, we need to wait until the
            ///   value that __c11_atomic_exchange returns is false, meaning
            ///   the lock was released. If __c11_atomic_exchange returns
            ///   false right off the bat, it means that the lock was never
            ///   taken at all, and there is nothing else to do.
            /// - The call to __c11_atomic_load reads the value of the lock,
            ///   and will continue to loop while the lock is true, meaning
            ///   it is held by another PP. The reason that __c11_atomic_load
            ///   is called instead of just looping using __c11_atomic_exchange
            ///   all the time is __c11_atomic_exchange uses a fence to ensure
            ///   proper ordering which is expensive. __c11_atomic_load in
            ///   this case, since we used __ATOMIC_RELAXED does not include
            ///   the fence, and so it can loop without killing the pipeline.
            /// - The only issue with this implementation is that once the
            ///   call to __c11_atomic_load returns, we still have not acquired
            ///   the lock as this is what __c11_atomic_exchange does. It is
            ///   possible that between when __c11_atomic_load returns and
            ///   __c11_atomic_exchange executes, another PP will have grabbed
            ///   the lock. Research has shown however that even with this
            ///   issue, this implemenation is the best for a spinlock WRT
            ///   overall performance.
            ///

            while (__c11_atomic_exchange(&m_flag, true, __ATOMIC_ACQUIRE)) {
                while (__c11_atomic_load(&m_flag, __ATOMIC_RELAXED)) {
                    __builtin_ia32_pause();
                }
            }

            if (tls.esr_rip == bsl::ZERO_UMAX) {
                m_std_ppid = tls.ppid;
            }
            else {
                m_esr_ppid = tls.ppid;
            }
        }

        /// <!-- description -->
        ///   @brief Unlocks the spinlock.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        unlock(TLS_CONCEPT const &tls) noexcept
        {
            if (bsl::is_constant_evaluated()) {
                return;
            }

            /// NOTE:
            /// - Before we release the lock, we need to make sure that
            ///   we are not holding the lock in both the normal case,
            ///   and the ESR case. If both have been released, we are clear
            ///   to release the lock.
            ///

            if (tls.esr_rip == bsl::ZERO_UMAX) {
                m_std_ppid = syscall::BF_INVALID_ID;
            }
            else {
                m_esr_ppid = syscall::BF_INVALID_ID;
            }

            if (m_std_ppid != syscall::BF_INVALID_ID) {
                return;
            }

            if (m_esr_ppid != syscall::BF_INVALID_ID) {
                return;
            }

            /// NOTE:
            /// - Here, we simply need to set the lock flag to false,
            ///   indicating that we no longer are holding the lock. We
            ///   use __ATOMIC_RELEASE to ensure proper memory ordering.
            ///

            __c11_atomic_store(&m_flag, false, __ATOMIC_RELEASE);
        }
    };
}

#endif
