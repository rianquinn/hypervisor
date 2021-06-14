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

#ifndef MOCKS_BF_CONTROL_OPS_HPP
#define MOCKS_BF_CONTROL_OPS_HPP

#include <bsl/is_constant_evaluated.hpp>

namespace syscall
{
    /// NOTE:
    /// - These APIs do not support constexpr. Most extensions should have a
    ///   single main.cpp files that contains all of the entry points, which
    ///   also likely do not support constexpr. These entry points should be
    ///   the only place that these APIs are used. All other code should be
    ///   constexpr friendly, so these should only be needed to support
    ///   unit testing a very small piece of code in an extension.
    ///

    /// @brief stores whether or not bf_control_op_exit was executed
    constinit inline bool g_bf_control_op_exit_executed{};
    /// @brief stores whether or not bf_control_op_wait was executed
    constinit inline bool g_bf_control_op_wait_executed{};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to exit the execution
    ///     of an extension, providing a means to fast fail.
    ///
    constexpr void
    bf_control_op_exit() noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        g_bf_control_op_exit_executed = true;
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel that the extension would
    ///     like to wait for a callback. This is a blocking syscall that never
    ///     returns and should be used to return from the successful execution
    ///     of the _start function.
    ///
    constexpr void
    bf_control_op_wait() noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        g_bf_control_op_wait_executed = true;
    }
}

#endif
