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

#include <mk_interface.hpp>

#include <bsl/discard.hpp>
#include <bsl/safe_integral.hpp>

namespace syscall
{
    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rax.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rax_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rax.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rax_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rbx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rbx_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rbx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rbx_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rcx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rcx_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rcx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rcx_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rdx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rdx_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rdx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rdx_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rbp.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rbp_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rbp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rbp_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rsi.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rsi_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rsi.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rsi_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rdi.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rdi_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rdi.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rdi_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r8.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r8_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r8.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r8_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r9.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r9_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r9.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r9_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r10.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r10_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r10.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r10_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r11.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r11_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r11.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r11_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r12.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r12_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r12.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r12_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r13.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r13_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r13.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r13_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r14.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r14_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r14.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r14_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r15.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r15_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r15.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r15_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_extid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_extid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_vmid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_vmid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_vpid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_vpid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_vpsid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_vpsid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_ppid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_ppid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_online_pps.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_online_pps_impl() noexcept -> bf_uint16_t;

    // -------------------------------------------------------------------------
    // TLS
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Returns the value of tls.rax
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rax
    ///
    [[nodiscard]] constexpr auto
    bf_tls_rax(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_rax_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rax
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rax to
    ///
    constexpr void
    bf_tls_set_rax(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rax_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rbx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rbx
    ///
    [[nodiscard]] constexpr auto
    bf_tls_rbx(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_rbx_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rbx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rbx to
    ///
    constexpr void
    bf_tls_set_rbx(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rbx_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rcx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rcx
    ///
    [[nodiscard]] constexpr auto
    bf_tls_rcx(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_rcx_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rcx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rcx to
    ///
    constexpr void
    bf_tls_set_rcx(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rcx_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rdx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rdx
    ///
    [[nodiscard]] constexpr auto
    bf_tls_rdx(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_rdx_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rdx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rdx to
    ///
    constexpr void
    bf_tls_set_rdx(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rdx_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rbp
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rbp
    ///
    [[nodiscard]] constexpr auto
    bf_tls_rbp(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_rbp_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rbp
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rbp to
    ///
    constexpr void
    bf_tls_set_rbp(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rbp_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rsi
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rsi
    ///
    [[nodiscard]] constexpr auto
    bf_tls_rsi(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_rsi_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rsi
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rsi to
    ///
    constexpr void
    bf_tls_set_rsi(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rsi_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rdi
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rdi
    ///
    [[nodiscard]] constexpr auto
    bf_tls_rdi(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_rdi_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rdi
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rdi to
    ///
    constexpr void
    bf_tls_set_rdi(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rdi_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r8
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r8
    ///
    [[nodiscard]] constexpr auto
    bf_tls_r8(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_r8_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r8
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r8 to
    ///
    constexpr void
    bf_tls_set_r8(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r8_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r9
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r9
    ///
    [[nodiscard]] constexpr auto
    bf_tls_r9(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_r9_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r9
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r9 to
    ///
    constexpr void
    bf_tls_set_r9(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r9_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r10
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r10
    ///
    [[nodiscard]] constexpr auto
    bf_tls_r10(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_r10_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r10
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r10 to
    ///
    constexpr void
    bf_tls_set_r10(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r10_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r11
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r11
    ///
    [[nodiscard]] constexpr auto
    bf_tls_r11(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_r11_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r11
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r11 to
    ///
    constexpr void
    bf_tls_set_r11(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r11_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r12
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r12
    ///
    [[nodiscard]] constexpr auto
    bf_tls_r12(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_r12_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r12
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r12 to
    ///
    constexpr void
    bf_tls_set_r12(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r12_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r13
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r13
    ///
    [[nodiscard]] constexpr auto
    bf_tls_r13(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_r13_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r13
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r13 to
    ///
    constexpr void
    bf_tls_set_r13(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r13_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r14
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r14
    ///
    [[nodiscard]] constexpr auto
    bf_tls_r14(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_r14_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r14
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r14 to
    ///
    constexpr void
    bf_tls_set_r14(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r14_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r15
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r15
    ///
    [[nodiscard]] constexpr auto
    bf_tls_r15(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return bf_tls_r15_impl();
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r15
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r15 to
    ///
    constexpr void
    bf_tls_set_r15(bf_handle_t &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r15_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.extid
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.extid
    ///
    [[nodiscard]] constexpr auto
    bf_tls_extid(bf_handle_t const &handle) noexcept -> bsl::safe_uint16
    {
        bsl::discard(handle);
        return bf_tls_extid_impl();
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.vmid
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.vmid
    ///
    [[nodiscard]] constexpr auto
    bf_tls_vmid(bf_handle_t const &handle) noexcept -> bsl::safe_uint16
    {
        bsl::discard(handle);
        return bf_tls_vmid_impl();
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.vpid
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.vpid
    ///
    [[nodiscard]] constexpr auto
    bf_tls_vpid(bf_handle_t const &handle) noexcept -> bsl::safe_uint16
    {
        bsl::discard(handle);
        return bf_tls_vpid_impl();
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.vpsid
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.vpsid
    ///
    [[nodiscard]] constexpr auto
    bf_tls_vpsid(bf_handle_t const &handle) noexcept -> bsl::safe_uint16
    {
        bsl::discard(handle);
        return bf_tls_vpsid_impl();
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.ppid
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.ppid
    ///
    [[nodiscard]] constexpr auto
    bf_tls_ppid(bf_handle_t const &handle) noexcept -> bsl::safe_uint16
    {
        bsl::discard(handle);
        return bf_tls_ppid_impl();
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.online_pps
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.online_pps
    ///
    [[nodiscard]] constexpr auto
    bf_tls_online_pps(bf_handle_t const &handle) noexcept -> bsl::safe_uint16
    {
        bsl::discard(handle);
        return bf_tls_online_pps_impl();
    }
}
