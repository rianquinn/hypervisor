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

#ifndef VM_T_BASE_HPP
#define VM_T_BASE_HPP

#include <allocated_status_t.hpp>

#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>

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
    protected:
        /// @brief stores the ID associated with this vm_t
        bsl::safe_uint16 m_id{bsl::safe_uint16::zero(true)};
        /// @brief stores whether or not this vm_t is allocated.
        allocated_status_t m_allocated{allocated_status_t::deallocated};
        /// @brief stores whether or not this vm_t is active.
        bool m_active{};

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
        ///   @brief Release the vm_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
        ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
        ///   @param tls the current TLS block
        ///   @param ext_pool the extension pool to use
        ///   @param vp_pool the VP pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT, typename EXT_POOL_CONCEPT, typename VP_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        release(TLS_CONCEPT &tls, EXT_POOL_CONCEPT &ext_pool, VP_POOL_CONCEPT &vp_pool) &noexcept
            -> bsl::errc_type
        {
            bsl::discard(tls);
            bsl::discard(ext_pool);
            bsl::discard(vp_pool);

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Allocates this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
        ///   @param tls the current TLS block
        ///   @param ext_pool the extension pool to use
        ///   @return Returns ID of the newly allocated vm
        ///
        template<typename TLS_CONCEPT, typename EXT_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        allocate(TLS_CONCEPT &tls, EXT_POOL_CONCEPT &ext_pool) &noexcept -> bsl::safe_uint16
        {
            bsl::discard(tls);
            bsl::discard(ext_pool);

            m_allocated = allocated_status_t::allocated;
            return m_id;
        }

        /// <!-- description -->
        ///   @brief Deallocates this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
        ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
        ///   @param tls the current TLS block
        ///   @param ext_pool the extension pool to use
        ///   @param vp_pool the VP pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT, typename EXT_POOL_CONCEPT, typename VP_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        deallocate(TLS_CONCEPT &tls, EXT_POOL_CONCEPT &ext_pool, VP_POOL_CONCEPT &vp_pool) &noexcept
            -> bsl::errc_type
        {
            bsl::discard(tls);
            bsl::discard(ext_pool);
            bsl::discard(vp_pool);

            m_allocated = allocated_status_t::deallocated;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Sets this vm_t's status as zombified, meaning it is no
        ///     longer usable.
        ///
        constexpr void
        zombify() &noexcept
        {
            m_allocated = allocated_status_t::zombie;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vm_t is deallocated, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vm_t is deallocated, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_deallocated() const &noexcept -> bool
        {
            return m_allocated == allocated_status_t::deallocated;
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
            bsl::discard(tls);

            m_active = true;
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
            bsl::discard(tls);

            m_active = {};
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the first PP identified that this VM
        ///     is still active on. If the VM is inactive, this function
        ///     returns bsl::safe_uint16::zero(true)
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns the ID of the first PP identified that this VM
        ///     is still active on. If the VM is inactive, this function
        ///     returns bsl::safe_uint16::zero(true)
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_active(TLS_CONCEPT &tls) const &noexcept -> bsl::safe_uint16
        {
            bsl::discard(tls);

            if (m_active) {
                return bsl::ZERO_U16;
            }

            return bsl::safe_uint16::zero(true);
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
            bsl::discard(tls);
            return m_active;
        }

        // <!-- description -->
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
}

#endif
