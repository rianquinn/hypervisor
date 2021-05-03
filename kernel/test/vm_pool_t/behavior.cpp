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

#include "../../src/vm_pool_t.hpp"

#include <bsl/ut.hpp>

#include <lock_guard.hpp>
#include <mk_interface.hpp>
#include <spinlock.hpp>
#include <allocated_status_t.hpp>

namespace mk
{
    /// @class mk::vm_t_base
    ///
    /// <!-- description -->
    ///   @brief Provides the base vm_t for testing.
    ///
    template<typename derived>
    class vm_t_base
    {
        /// @brief stores the next vm_t in the vm_pool_t linked list
        vm_t_base *m_next{};
        /// @brief stores the ID associated with this vm_t
        bsl::safe_uint16 m_id{bsl::safe_uint16::zero(true)};

    public:
        /// <!-- description -->
        ///   @brief Release the vm_t. Note that if this function fails,
        ///     the microkernel is left in a corrupt state and all use of the
        ///     vm_t after calling this function will results in UB.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        release() &noexcept -> bsl::errc_type
        {
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns the next vm_t in the vm_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the next vm_t in the vm_pool_t linked list
        ///
        [[nodiscard]] constexpr auto
        next() const &noexcept -> derived *
        {
            return m_next;
        }

        /// <!-- description -->
        ///   @brief Sets the next vm_t in the vm_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @param val the next vm_t in the vm_pool_t linked list to set
        ///
        constexpr void
        set_next(derived *val) &noexcept
        {
            m_next = val;
        }
    };

    /// @class mk::vm_t_initialize_success
    ///
    /// <!-- description -->
    ///   @brief Returns success on initialization
    ///
    class vm_t_initialize_success final // --
        : public vm_t_base<vm_t_initialize_success>
    {
    public:
        /// <!-- description -->
        ///   @brief Initializes this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param i the ID for this vm_t
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(bsl::safe_uint16 const &i) &noexcept -> bsl::errc_type
        {
            bsl::discard(i);
            return bsl::errc_success;
        }
    };

    /// @class mk::vm_t_initialize_failure
    ///
    /// <!-- description -->
    ///   @brief Returns failure on initialization
    ///
    class vm_t_initialize_failure final // --
        : public vm_t_base<vm_t_initialize_failure>
    {
    public:
        /// <!-- description -->
        ///   @brief Initializes this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param i the ID for this vm_t
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(bsl::safe_uint16 const &i) &noexcept -> bsl::errc_type
        {
            bsl::discard(i);
            return bsl::errc_failure;
        }
    };

    template<bsl::uintmax MAX_PPS>
    class vm_t final
    {
        /// @brief stores the next vm_t in the vm_pool_t linked list
        vm_t *m_next{};
        /// @brief stores the ID associated with this vm_t
        bsl::safe_uint16 m_id{bsl::safe_uint16::zero(true)};
        /// @brief stores whether or not this vm_t is allocated.
        allocated_status_t m_allocated{allocated_status_t::unallocated};
        /// @brief stores whether or not this vm_t is active.
        bsl::array<bool, MAX_PPS> m_active{};
        /// @brief safe guards operations on the pool.
        mutable spinlock m_lock;

    public:
        /// <!-- description -->
        ///   @brief Initializes this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param i the ID for this vm_t
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(bsl::safe_uint16 const &i) &noexcept -> bsl::errc_type
        {
            m_id = i;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vm_t. Note that if this function fails,
        ///     the microkernel is left in a corrupt state and all use of the
        ///     vm_t after calling this function will results in UB.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        release() &noexcept -> bsl::errc_type
        {
            for (auto const elem : m_active) {
                if (bsl::unlikely(*elem.data)) {
                    bsl::error() << "vm "                        // --
                                 << bsl::hex(m_id)               // --
                                 << " is still active on pp "    // --
                                 << bsl::hex(elem.index)         // --
                                 << " and cannot be released"    // --
                                 << bsl::endl                    // --
                                 << bsl::here();                 // --

                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            m_allocated = allocated_status_t::unallocated;
            m_id = bsl::safe_uint16::zero(true);

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns the ID of this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of this vm_t
        ///
        [[nodiscard]] constexpr auto
        id() const &noexcept -> bsl::safe_uint16 const &
        {
            return m_id;
        }

        /// <!-- description -->
        ///   @brief Allocates this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns ID of the newly allocated vm
        ///
        [[nodiscard]] constexpr auto
        allocate() &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vm_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_allocated == allocated_status_t::allocated)) {
                bsl::error() << "vm "                      // --
                             << bsl::hex(m_id)             // --
                             << " is already allocated"    // --
                             << bsl::endl                  // --
                             << bsl::here();               // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_allocated == allocated_status_t::zombie)) {
                bsl::error() << "vm "                      // --
                             << bsl::hex(m_id)             // --
                             << " is a zombie and cannot be allocated"    // --
                             << bsl::endl                  // --
                             << bsl::here();               // --

                return bsl::errc_failure;
            }

            m_allocated = allocated_status_t::allocated;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Deallocates this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        deallocate(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_id)) {
                return bsl::errc_success;
            }

            if (bsl::unlikely(m_id == syscall::BF_ROOT_VMID)) {
                bsl::error() << "vm "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is the root VM which cannot be destroyed"       // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_allocated != allocated_status_t::allocated)) {
                return bsl::errc_success;
            }

            bsl::finally zombify_on_error{[this]() noexcept -> void {
                this->zombify();
            }};

            for (auto const elem : m_active) {
                if (bsl::unlikely(*elem.data)) {
                    bsl::error() << "vm "                           // --
                                 << bsl::hex(m_id)                  // --
                                 << " is still active on pp "       // --
                                 << bsl::hex(elem.index)            // --
                                 << " and cannot be deallocated"    // --
                                 << bsl::endl                       // --
                                 << bsl::here();                    // --

                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            m_allocated = allocated_status_t::unallocated;

            zombify_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Sets this vm_t's status as zombified, meaning it is no
        ///     longer usable.
        ///
        constexpr void
        zombify() &noexcept
        {
            if (bsl::unlikely(m_id == syscall::BF_ROOT_VMID)) {
                bsl::alert() << "attempt to zombify vm "                           // --
                             << bsl::hex(m_id)                  // --
                             << " was ignored as the root VM cannot be a zombie"       // --
                             << bsl::endl;                       // --
            }
            else {
                bsl::alert() << "vm "                      // --
                                << bsl::hex(m_id)             // --
                                << " has been zombified"    // --
                                << bsl::endl;                  // --

                m_allocated = allocated_status_t::zombie;
            }
        }

        /// <!-- description -->
        ///   @brief Returns true if this vm_t is allocated, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vm_t is allocated, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_allocated() const &noexcept -> bool
        {
            return m_allocated == allocated_status_t::allocated;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vm_t is a zombie, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vm_t is a zombie, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_zombie() const &noexcept -> bool
        {
            return m_allocated == allocated_status_t::zombie;
        }

        /// <!-- description -->
        ///   @brief Sets this vm_t as active.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_active(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vm_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_allocated != allocated_status_t::allocated)) {
                bsl::error() << "vm "                     // --
                             << bsl::hex(m_id)            // --
                             << " has not been properly allocated and cannot be used"    // --
                             << bsl::endl                 // --
                             << bsl::here();              // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.active_vmid == m_id)) {
                bsl::error() << "vm "                                 // --
                             << bsl::hex(m_id)                        // --
                             << " is already the active vm on pp "    // --
                             << bsl::hex(tls.ppid)                    // --
                             << bsl::endl                             // --
                             << bsl::here();                          // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID != tls.active_vmid)) {
                bsl::error() << "vm "                        // --
                             << bsl::hex(tls.active_vmid)    // --
                             << " is still active on pp "    // --
                             << bsl::hex(tls.ppid)           // --
                             << bsl::endl                    // --
                             << bsl::here();                 // --

                return bsl::errc_failure;
            }

            auto *const active{m_active.at_if(bsl::to_umax(tls.ppid))};
            if (bsl::unlikely(nullptr == active)) {
                bsl::error() << "tls.ppid "                        // --
                             << bsl::hex(m_id)                     // --
                             << " is greater than the MAX_PPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_PPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(*active)) {
                bsl::error() << "vm "                                 // --
                             << bsl::hex(m_id)                        // --
                             << " is already the active vm on pp "    // --
                             << bsl::hex(tls.ppid)                    // --
                             << bsl::endl                             // --
                             << bsl::here();                          // --

                return bsl::errc_failure;
            }

            tls.active_vmid = m_id.get();
            *active = true;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Sets this vm_t as inactive.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_inactive(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vm_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_allocated != allocated_status_t::allocated)) {
                bsl::error() << "vm "                     // --
                             << bsl::hex(m_id)            // --
                             << " has not been properly allocated and cannot be used"    // --
                             << bsl::endl                 // --
                             << bsl::here();              // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == tls.active_vmid)) {
                bsl::error() << "vm "                      // --
                             << bsl::hex(m_id)             // --
                             << " is not active on pp "    // --
                             << bsl::hex(tls.ppid)         // --
                             << bsl::endl                  // --
                             << bsl::here();               // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.active_vmid != m_id)) {
                bsl::error() << "vm "                        // --
                             << bsl::hex(tls.active_vmid)    // --
                             << " is still active on pp "    // --
                             << bsl::hex(tls.ppid)           // --
                             << bsl::endl                    // --
                             << bsl::here();                 // --

                return bsl::errc_failure;
            }

            auto *const active{m_active.at_if(bsl::to_umax(tls.ppid))};
            if (bsl::unlikely(nullptr == active)) {
                bsl::error() << "tls.ppid "                        // --
                             << bsl::hex(m_id)                     // --
                             << " is greater than the MAX_PPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_PPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(!*active)) {
                bsl::error() << "vm "                      // --
                             << bsl::hex(m_id)             // --
                             << " is not active on pp "    // --
                             << bsl::hex(tls.ppid)         // --
                             << bsl::endl                  // --
                             << bsl::here();               // --

                return bsl::errc_failure;
            }

            tls.active_vmid = syscall::BF_INVALID_ID.get();
            *active = false;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vm_t is active, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns true if this vm_t is active, false otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_active(TLS_CONCEPT &tls) const &noexcept -> bool
        {
            lock_guard lock{tls, m_lock};

            for (auto const elem : m_active) {
                if (*elem.data) {
                    return true;
                }

                bsl::touch();
            }

            return false;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vm_t is active on the current PP,
        ///     false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns true if this vm_t is active on the current PP,
        ///     false otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_active_on_current_pp(TLS_CONCEPT &tls) const &noexcept -> bool
        {
            auto *const active{m_active.at_if(bsl::to_umax(tls.ppid))};
            if (bsl::unlikely(nullptr == active)) {
                bsl::error() << "tls.ppid "                        // --
                             << bsl::hex(m_id)                     // --
                             << " is greater than the MAX_PPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_PPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return false;
            }

            return *active;
        }

        /// <!-- description -->
        ///   @brief Returns the next vm_t in the vm_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the next vm_t in the vm_pool_t linked list
        ///
        [[nodiscard]] constexpr auto
        next() const &noexcept -> vm_t *
        {
            return m_next;
        }

        /// <!-- description -->
        ///   @brief Sets the next vm_t in the vm_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @param val the next vm_t in the vm_pool_t linked list to set
        ///
        constexpr void
        set_next(vm_t *val) &noexcept
        {
            m_next = val;
        }

        /// <!-- description -->
        ///   @brief Dumps the vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        dump(TLS_CONCEPT &tls) const &noexcept
        {
            bsl::discard(tls);
        }
    };

    /// <!-- description -->
    ///   @brief Used to execute the actual checks. We put the checks in this
    ///     function so that we can validate the tests both at compile-time
    ///     and at run-time. If a bsl::ut_check fails, the tests will either
    ///     fail fast at run-time, or will produce a compile-time error.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Always returns bsl::exit_success.
    ///
    [[nodiscard]] constexpr auto
    tests() noexcept -> bsl::exit_code
    {
        bsl::ut_scenario{"initialize"} = []() {
            bsl::ut_given{} = []() {
                vm_pool_t<vm_t_initialize_success, 2> pool{};
                bsl::ut_then{} = [&pool]() {
                    bsl::ut_check(pool.initialize() == bsl::errc_success);
                };
            };

            bsl::ut_given{} = []() {
                vm_pool_t<vm_t_initialize_failure, 2> pool{};
                bsl::ut_then{} = [&pool]() {
                    bsl::ut_check(pool.initialize() == bsl::errc_failure);
                };
            };
        };

        return bsl::ut_success();
    }
}

/// <!-- description -->
///   @brief Main function for this unit test. If a call to bsl::ut_check() fails
///     the application will fast fail. If all calls to bsl::ut_check() pass, this
///     function will successfully return with bsl::exit_success.
///
/// <!-- inputs/outputs -->
///   @return Always returns bsl::exit_success.
///
[[nodiscard]] auto
main() noexcept -> bsl::exit_code
{
    static_assert(mk::tests() == bsl::ut_success());
    return mk::tests();
}
