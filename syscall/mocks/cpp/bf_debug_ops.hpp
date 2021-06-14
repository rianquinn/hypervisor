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

#ifndef MOCKS_BF_DEBUG_OPS_HPP
#define MOCKS_BF_DEBUG_OPS_HPP

#include <bf_types.hpp>
#include <iomanip>
#include <iostream>

#include <bsl/char_type.hpp>
#include <bsl/cstr_type.hpp>
#include <bsl/is_constant_evaluated.hpp>

namespace syscall
{
    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output RDI and RSI to
    ///     the console device the microkernel is currently using for
    ///     debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val1 The first value to output to the microkernel's console
    ///   @param val2 The second value to output to the microkernel's console
    ///
    constexpr void
    bf_debug_op_out(bf_uint64_t const &val1, bf_uint64_t const &val2) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << std::hex << "0x" << val1.get() << " 0x" << val2.get() << '\n';
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the state of a
    ///     VM to the console device the microkernel is currently using for
    ///     debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vmid The VMID of the VM whose state is to be outputted
    ///
    constexpr void
    bf_debug_op_dump_vm(bf_uint16_t const &vmid) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << std::hex << "vm [0x" << vmid.get() << "] dump: mock empty\n";
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the state of a
    ///     VP to the console device the microkernel is currently using for
    ///     debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vpid The VPID of the VP whose state is to be outputted
    ///
    constexpr void
    bf_debug_op_dump_vp(bf_uint16_t const &vpid) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << std::hex << "vp [0x" << vpid.get() << "] dump: mock empty\n";
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the state of a
    ///     VPS to the console device the microkernel is currently using for
    ///     debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vpsid The VPSID of the VPS whose state is to be outputted
    ///
    constexpr void
    bf_debug_op_dump_vps(bf_uint16_t const &vpsid) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << std::hex << "vps [0x" << vpsid.get() << "] dump: mock empty\n";
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the VMExit log.
    ///     The VMExit log is a chronological log of the "X" number of exits
    ///     that have occurred on a specific physical processor.
    ///
    /// <!-- inputs/outputs -->
    ///   @param ppid The PPID of the PP to dump the log from
    ///
    constexpr void
    bf_debug_op_dump_vmexit_log(bf_uint16_t const &ppid) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << std::hex << "vmexit log for pp [0x" << ppid.get() << "]: mock empty\n";
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output a provided
    ///     character to the microkernel's console.
    ///
    /// <!-- inputs/outputs -->
    ///   @param c The character to output
    ///
    constexpr void
    bf_debug_op_write_c(bsl::char_type const c) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << c;
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output a provided
    ///     string to the microkernel's console.
    ///
    /// <!-- inputs/outputs -->
    ///   @param str The virtual address of a null terminated string to output
    ///
    constexpr void
    bf_debug_op_write_str(bsl::cstr_type const str) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << str;
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output an extension's
    ///     state to the console device the microkernel is currently using
    ///     for debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param extid The EXTID of the extensions's state to output
    ///
    constexpr void
    bf_debug_op_dump_ext(bf_uint16_t const &extid) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << std::hex << "ext [0x" << extid.get() << "] dump: mock empty\n";
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the page pool's
    ///     stats to the console device the microkernel is currently using
    ///     for debugging.
    ///
    constexpr void
    bf_debug_op_dump_page_pool() noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << "page pool dump: mock empty\n";
    }

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the huge pool's
    ///     stats to the console device the microkernel is currently using
    ///     for debugging.
    ///
    constexpr void
    bf_debug_op_dump_huge_pool() noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        std::cout << "huge pool dump: mock empty\n";
    }
}

#endif
