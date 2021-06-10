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

#ifndef INTRINSIC_HPP
#define INTRINSIC_HPP

#include <intrinsic_cpuid_impl.hpp>

#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>

namespace example
{
    /// @class example::intrinsic_t
    ///
    /// <!-- description -->
    ///   @brief Provides raw access to intrinsics. Instead of using global
    ///     functions, the intrinsics class provides a means for the rest of
    ///     the extension to mock the intrinsics when needed during testing.
    ///
    class intrinsic_t final
    {
    public:
        /// <!-- description -->
        ///   @brief Initializes this intrinsic_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize() &noexcept -> bsl::errc_type
        {
            /// NOTE:
            /// - Add initialization code here if needed. Otherwise, this
            ///   function can be removed if it is not needed.
            ///

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the intrinsic_t.
        ///
        constexpr void
        release() &noexcept
        {
            /// NOTE:
            /// - Release functions are usually only needed in the event of
            ///   an error, or during unit testing.
            ///
        }

        /// <!-- description -->
        ///   @brief Executes the CPUID instruction given the provided
        ///     EAX and ECX and returns the results.
        ///
        /// <!-- inputs/outputs -->
        ///   @param rax the index used by CPUID, returns resulting rax
        ///   @param rbx returns resulting rbx
        ///   @param rcx the subindex used by CPUID, returns the resulting rcx
        ///   @param rdx returns resulting rdx
        ///
        constexpr void
        cpuid(
            bsl::safe_uint64 &rax,
            bsl::safe_uint64 &rbx,
            bsl::safe_uint64 &rcx,
            bsl::safe_uint64 &rdx) noexcept
        {
            intrinsic_cpuid_impl(rax.data(), rbx.data(), rcx.data(), rdx.data());
        }
    };
}

#endif
