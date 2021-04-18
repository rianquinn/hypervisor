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

#ifndef TLS_POOL_T_HPP
#define TLS_POOL_T_HPP

#include <bsl/array.hpp>
#include <bsl/debug.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @class mk::tls_pool_t
    ///
    /// <!-- description -->
    ///   @brief Defines a wrapper around the pool of TLS blocks so that
    ///     properties about all of the TLS blocks can be queried.
    ///
    /// <!-- template parameters -->
    ///   @tparam TLS_CONCEPT the type of tls_t that this class manages.
    ///   @tparam MAX_PPS the max number of PPs supported
    ///
    template<typename TLS_CONCEPT, bsl::uintmax MAX_PPS>
    class tls_pool_t final
    {
        /// @brief stores the TLS_CONCEPTs in the TLS_CONCEPT linked list
        bsl::array<TLS_CONCEPT, bsl::to_umax(MAX_PPS).get()> const &m_tls_pool;

    public:
        /// @brief an alias for TLS_CONCEPT
        using tls_type = TLS_CONCEPT;

        /// <!-- description -->
        ///   @brief Creates a tls_pool_t
        ///
        explicit constexpr tls_pool_t(
            bsl::array<TLS_CONCEPT, bsl::to_umax(MAX_PPS).get()> const &tls_pool) noexcept
            : m_tls_pool{tls_pool}
        {}

        /// <!-- description -->
        ///   @brief Destroyes a previously created tls_pool_t
        ///
        constexpr ~tls_pool_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr tls_pool_t(tls_pool_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr tls_pool_t(tls_pool_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(tls_pool_t const &o) &noexcept
            -> tls_pool_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(tls_pool_t &&o) &noexcept
            -> tls_pool_t & = default;

        /// <!-- description -->
        ///   @brief Returns true if the VM associated with the provided vmid
        ///     is active on any of the PPs.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the vmid to query
        ///   @return Returns true if the VM associated with the provided vmid
        ///     is active on any of the PPs.
        ///
        [[nodiscard]] constexpr auto
        is_vm_active(bsl::safe_uint16 const &vmid) &noexcept -> bool
        {
            for (bsl::safe_uintmax i{}; i < bsl::to_umax(m_tls_pool.front().online_pps); ++i) {
                if (m_tls_pool.at_if(i)->active_vmid == vmid) {
                    return true;
                }

                bsl::touch();
            }

            return false;
        }

        /// <!-- description -->
        ///   @brief Returns true if the VP associated with the provided vpid
        ///     is active on any of the PPs.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpid the vpid to query
        ///   @return Returns true if the VP associated with the provided vpid
        ///     is active on any of the PPs.
        ///
        [[nodiscard]] constexpr auto
        is_vp_active(bsl::safe_uint16 const &vpid) &noexcept -> bool
        {
            for (bsl::safe_uintmax i{}; i < bsl::to_umax(m_tls_pool.front().online_pps); ++i) {
                if (m_tls_pool.at_if(i)->active_vpid == vpid) {
                    return true;
                }

                bsl::touch();
            }

            return false;
        }

        /// <!-- description -->
        ///   @brief Returns true if the VPS associated with the provided vpsid
        ///     is active on any of the PPs.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpsid the vpsid to query
        ///   @return Returns true if the VPS associated with the provided vpsid
        ///     is active on any of the PPs.
        ///
        [[nodiscard]] constexpr auto
        is_vps_active(bsl::safe_uint16 const &vpsid) &noexcept -> bool
        {
            for (bsl::safe_uintmax i{}; i < bsl::to_umax(m_tls_pool.front().online_pps); ++i) {
                if (m_tls_pool.at_if(i)->active_vpsid == vpsid) {
                    return true;
                }

                bsl::touch();
            }

            return false;
        }
    };
}

#endif
