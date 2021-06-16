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

#ifndef MOCKS_INTRINSIC_HPP
#define MOCKS_INTRINSIC_HPP

#include <gs_t.hpp>
#include <tls_t.hpp>
#include <errc_types.hpp>

#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>

namespace example
{
    /// @class example::intrinsic_t
    ///
    /// <!-- description -->
    ///   @brief Provides raw access to intrinsics used for unit testing.
    ///     Specifically, this version only contains portions that are common
    ///     for all architectures.
    ///
    class intrinsic_t final
    {
    public:
        /// <!-- description -->
        ///   @brief Initializes this intrinsic_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] static constexpr auto
        initialize(gs_t &gs, tls_t &tls) noexcept -> bsl::errc_type
        {
            bsl::discard(gs);

            /// NOTE:
            /// - This is an example of providing an error case that the
            ///   original code does not have. Any code that is using this
            ///   will have no idea how this function is implemented, and
            ///   at any time it might return an error. This ensure that
            ///   this is handled.
            ///

            if (tls.test_ret == errc_fail_initialize) {
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the intrinsic_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///
        static constexpr void
        release(gs_t &gs, tls_t &tls) noexcept
        {
            bsl::discard(gs);
            bsl::discard(tls);
        }
    };
}

#endif
