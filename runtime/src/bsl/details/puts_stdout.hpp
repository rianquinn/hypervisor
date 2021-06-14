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

#ifndef RUNTIME_BSL_DETAILS_PUTS_STDOUT_HPP
#define RUNTIME_BSL_DETAILS_PUTS_STDOUT_HPP

#include <bsl/cstdio.hpp>
#include <bsl/cstr_type.hpp>

namespace bsl::details
{
    /// <!-- description -->
    ///   @brief Outputs a string to stdout.
    ///
    /// <!-- inputs/outputs -->
    ///   @param str the string to output to stdout
    ///
    constexpr void
    HYPERVISOR_PUTS_STDOUT_NAME(cstr_type const str) noexcept
    {
        bsl::fputs(str);
    }
}

#endif
