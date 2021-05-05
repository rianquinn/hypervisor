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

#ifndef VM_T_INITIALIZE_AND_RELEASE_FAILURE_HPP
#define VM_T_INITIALIZE_AND_RELEASE_FAILURE_HPP

#include "vm_t_base.hpp"

#include <bsl/discard.hpp>
#include <bsl/debug.hpp>
#include <bsl/safe_integral.hpp>

namespace mk
{
    /// @class mk::vm_t_initialize_and_release_failure
    ///
    /// <!-- description -->
    ///   @brief Returns failure on initialization
    ///
    class vm_t_initialize_and_release_failure final    // --
        : public vm_t_base<vm_t_initialize_and_release_failure>
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
            m_id = i;

            if (i.is_zero()) {
                return bsl::errc_success;
            }

            bsl::error() << "vm_t_initialize_and_release_failure failed as expected"    // --
                         << bsl::endl                                                   // --
                         << bsl::here();                                                // --

            return bsl::errc_failure;
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

            if (m_id.is_zero()) {
                return bsl::errc_success;
            }

            bsl::error() << "vm_t_initialize_and_release_failure failed as expected"    // --
                         << bsl::endl                                                   // --
                         << bsl::here();                                                // --

            return bsl::errc_failure;
        }
    };
}

#endif
