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

#ifndef DISPATCH_SYSCALL_HANDLE_OP_FAILURE_HPP
#define DISPATCH_SYSCALL_HANDLE_OP_FAILURE_HPP

#include <mk_interface.hpp>

#include <bsl/debug.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Implements the bf_handle_op_open_handle syscall failure logic
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_CONCEPT defines the type of ext_t to use
    ///   @param tls the current TLS block
    ///   @param ext the extension that made the syscall
    ///
    template<typename TLS_CONCEPT, typename EXT_CONCEPT>
    constexpr void
    syscall_handle_op_open_handle_failure(TLS_CONCEPT &tls, EXT_CONCEPT &ext)
    {
        if (!tls.state_reversal_required) {
            return;
        }

        if (ext.is_handle_open()) {
            ext.close_handle();
        }
        else {
            bsl::touch();
        }

        tls.ext_reg0 = {};
    }

    /// <!-- description -->
    ///   @brief Implements the bf_handle_op_close_handle syscall failure logic
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_CONCEPT defines the type of ext_t to use
    ///   @param tls the current TLS block
    ///   @param ext the extension that made the syscall
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename TLS_CONCEPT, typename EXT_CONCEPT>
    [[nodiscard]] constexpr auto
    syscall_handle_op_close_handle_failure(TLS_CONCEPT &tls, EXT_CONCEPT &ext) -> bsl::errc_type
    {
        if (!tls.state_reversal_required) {
            return bsl::errc_success;
        }

        if (!ext.is_handle_open()) {
            auto const handle{ext.open_handle()};
            if (bsl::unlikely(!handle)) {
                bsl::print<bsl::V>() << bsl::red << bsl::here();
                return bsl::errc_failure;
            }

            bsl::touch();
        }
        else {
            bsl::touch();
        }

        return bsl::errc_success;
    }

    /// <!-- description -->
    ///   @brief Dispatches the bf_handle_op syscalls
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_CONCEPT defines the type of ext_t to use
    ///   @param tls the current TLS block
    ///   @param ext the extension that made the syscall
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename TLS_CONCEPT, typename EXT_CONCEPT>
    [[nodiscard]] constexpr auto
    dispatch_syscall_handle_op_failure(TLS_CONCEPT &tls, EXT_CONCEPT &ext) -> bsl::errc_type
    {
        bsl::errc_type ret{};

        switch (syscall::bf_syscall_index(tls.ext_syscall).get()) {
            case syscall::BF_HANDLE_OP_OPEN_HANDLE_IDX_VAL.get(): {
                syscall_handle_op_open_handle_failure(tls, ext);
                return bsl::errc_success;
            }

            case syscall::BF_HANDLE_OP_CLOSE_HANDLE_IDX_VAL.get(): {
                ret = syscall_handle_op_close_handle_failure(tls, ext);
                return ret;
            }

            default: {
                break;
            }
        }

        return bsl::errc_success;
    }
}

#endif
