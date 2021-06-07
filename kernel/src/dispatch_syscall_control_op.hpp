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

#ifndef DISPATCH_SYSCALL_CONTROL_OP_HPP
#define DISPATCH_SYSCALL_CONTROL_OP_HPP

#include <mk_interface.hpp>
#include <return_to_mk.hpp>
#include <tls_t.hpp>

#include <bsl/debug.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Dispatches the bf_callback_op syscalls
    ///
    /// <!-- inputs/outputs -->

    ///   @tparam EXT_CONCEPT defines the type of ext_t to use
    ///   @param tls the current TLS block
    ///   @param ext the extension that made the syscall
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename EXT_CONCEPT>
    [[nodiscard]] constexpr auto
    dispatch_syscall_control_op(tls_t &tls, EXT_CONCEPT &ext) noexcept -> bsl::errc_type
    {
        switch (syscall::bf_syscall_index(tls.ext_syscall).get()) {
            case syscall::BF_CONTROL_OP_EXIT_IDX_VAL.get(): {
                return_to_mk(bsl::exit_failure);

                // Unreachable
                return bsl::errc_success;
            }

            case syscall::BF_CONTROL_OP_WAIT_IDX_VAL.get(): {
                if (ext.is_started()) {
                    return_to_mk(bsl::exit_failure);
                }
                else {
                    return_to_mk(bsl::exit_success);
                }

                // Unreachable
                return bsl::errc_success;
            }

            default: {
                break;
            }
        }

        bsl::error() << "unknown syscall index: "    //--
                     << bsl::hex(tls.ext_syscall)    //--
                     << bsl::endl                    //--
                     << bsl::here();                 //--

        tls.syscall_ret_status = syscall::BF_STATUS_FAILURE_UNSUPPORTED.get();
        return bsl::errc_failure;
    }
}

#endif
