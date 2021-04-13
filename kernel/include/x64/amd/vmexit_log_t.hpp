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

#ifndef VMEXIT_LOG_T
#define VMEXIT_LOG_T

#include <bsl/safe_integral.hpp>

namespace mk
{
    /// @struct mk::vmexit_log_t
    ///
    /// <!-- description -->
    ///   @brief Stores information about each VMExit
    ///
    struct vmexit_log_t final
    {
        /// @brief stores the exit reason
        bsl::safe_uintmax exit_reason;
        /// @brief stores the exit info 1
        bsl::safe_uintmax exitinfo1;
        /// @brief stores the exit info 2
        bsl::safe_uintmax exitinfo2;
        /// @brief stores the exit in info
        bsl::safe_uintmax exitininfo;
        /// @brief stores rax
        bsl::safe_uintmax rax;
        /// @brief stores rcx
        bsl::safe_uintmax rcx;
        /// @brief stores rdx
        bsl::safe_uintmax rdx;
        /// @brief stores rip
        bsl::safe_uintmax rip;
        /// @brief stores rsp
        bsl::safe_uintmax rsp;
    };
}

#endif
