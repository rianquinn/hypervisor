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

#include "../../../../src/cpp/bf_syscall_t.hpp"

#include <bsl/discard.hpp>
#include <bsl/ut.hpp>

namespace syscall
{
    // -------------------------------------------------------------------------
    // TLS ops
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rax.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rax_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rax.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_rax_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rbx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rbx_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rbx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_rbx_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rcx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rcx_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rcx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_rcx_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rdx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rdx_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rdx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_rdx_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rbp.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rbp_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rbp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_rbp_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rsi.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rsi_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rsi.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_rsi_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rdi.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rdi_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rdi.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_rdi_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r8.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r8_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r8.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_r8_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r9.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r9_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r9.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_r9_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r10.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r10_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r10.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_r10_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r11.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r11_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r11.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_r11_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r12.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r12_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r12.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_r12_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r13.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r13_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r13.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_r13_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r14.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r14_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r14.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_r14_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r15.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r15_impl() noexcept -> bf_uint64_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r15.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void
    bf_tls_set_r15_impl(bf_uint64_t::value_type const val) noexcept
    {
        bsl::discard(val);
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_extid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_extid_impl() noexcept -> bf_uint16_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_vmid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_vmid_impl() noexcept -> bf_uint16_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_vpid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_vpid_impl() noexcept -> bf_uint16_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_vpsid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_vpsid_impl() noexcept -> bf_uint16_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_ppid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_ppid_impl() noexcept -> bf_uint16_t::value_type
    {
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_online_pps.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_online_pps_impl() noexcept -> bf_uint16_t::value_type
    {
        return {};
    }

    // -------------------------------------------------------------------------
    // bf_handle_ops
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_handle_op_open_handle.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_handle_op_open_handle_impl(
        bf_uint32_t::value_type const reg0_in, bf_uint64_t::value_type *const reg0_out) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_handle_op_close_handle.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_handle_op_close_handle_impl(bf_uint64_t::value_type const reg0_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        return {};
    }

    // -------------------------------------------------------------------------
    // bf_callback_ops
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_callback_op_register_bootstrap.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_callback_op_register_bootstrap_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_callback_handler_bootstrap_t const reg1_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_callback_op_register_vmexit.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_callback_op_register_vmexit_impl(
        bf_uint64_t::value_type const reg0_in, bf_callback_handler_vmexit_t const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_callback_op_register_fail.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_callback_op_register_fail_impl(
        bf_uint64_t::value_type const reg0_in, bf_callback_handler_fail_t const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    // -------------------------------------------------------------------------
    // bf_vm_ops
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vm_op_create_vm.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vm_op_create_vm_impl(
        bf_uint64_t::value_type const reg0_in, bf_uint16_t::value_type *const reg0_out) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vm_op_destroy_vm.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vm_op_destroy_vm_impl(
        bf_uint64_t::value_type const reg0_in, bf_uint16_t::value_type const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    // -------------------------------------------------------------------------
    // bf_vp_ops
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vp_op_create_vp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vp_op_create_vp_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint16_t::value_type const reg2_in,
        bf_uint16_t::value_type *const reg0_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vp_op_destroy_vp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vp_op_destroy_vp_impl(
        bf_uint64_t::value_type const reg0_in, bf_uint16_t::value_type const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vp_op_migrate.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vp_op_migrate_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint16_t::value_type const reg2_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);

        return {};
    }

    // -------------------------------------------------------------------------
    // bf_vps_ops
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_create_vps.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_create_vps_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint16_t::value_type const reg2_in,
        bf_uint16_t::value_type *const reg0_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_destroy_vps.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_destroy_vps_impl(
        bf_uint64_t::value_type const reg0_in, bf_uint16_t::value_type const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_init_as_root.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_init_as_root_impl(
        bf_uint64_t::value_type const reg0_in, bf_uint16_t::value_type const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read8.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_read8_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in,
        bf_uint8_t::value_type *const reg0_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read16.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_read16_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in,
        bf_uint16_t::value_type *const reg0_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read32.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_read32_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in,
        bf_uint32_t::value_type *const reg0_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read64.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_read64_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in,
        bf_uint64_t::value_type *const reg0_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write8.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_write8_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in,
        bf_uint8_t::value_type const reg3_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg3_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write16.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_write16_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in,
        bf_uint16_t::value_type const reg3_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg3_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write32.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_write32_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in,
        bf_uint32_t::value_type const reg3_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg3_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write64.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_write64_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in,
        bf_uint64_t::value_type const reg3_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg3_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read_reg_impl.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_read_reg_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_reg_t const reg2_in,
        bf_uint64_t::value_type *const reg0_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write_reg.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_write_reg_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_reg_t const reg2_in,
        bf_uint64_t::value_type const reg3_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg3_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_run.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_run_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint16_t::value_type const reg1_in,
        bf_uint16_t::value_type const reg2_in,
        bf_uint16_t::value_type const reg3_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg3_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_run_current.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_run_current_impl(bf_uint64_t::value_type const reg0_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_advance_ip.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_advance_ip_impl(
        bf_uint64_t::value_type const reg0_in, bf_uint16_t::value_type const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_advance_ip_and_run_current.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_advance_ip_and_run_current_impl(bf_uint64_t::value_type const reg0_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_promote.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_promote_impl(
        bf_uint64_t::value_type const reg0_in, bf_uint16_t::value_type const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_clear_vps.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_vps_op_clear_vps_impl(
        bf_uint64_t::value_type const reg0_in, bf_uint16_t::value_type const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    // -------------------------------------------------------------------------
    // bf_intrinsic_ops
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_rdmsr.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_intrinsic_op_rdmsr_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint32_t::value_type const reg1_in,
        bf_uint64_t::value_type *const reg0_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg0_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_wrmsr.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_intrinsic_op_wrmsr_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint32_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_invlpga.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_intrinsic_op_invlpga_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint64_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_invept.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_intrinsic_op_invept_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint64_t::value_type const reg1_in,
        bf_uint64_t::value_type const reg2_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_invvpid.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_intrinsic_op_invvpid_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint64_t::value_type const reg1_in,
        bf_uint16_t::value_type const reg2_in,
        bf_uint64_t::value_type const reg3_in) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg2_in);
        bsl::discard(reg3_in);

        return {};
    }

    // -------------------------------------------------------------------------
    // bf_mem_ops
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_alloc_page.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg0_out n/a
    ///   @param reg1_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_mem_op_alloc_page_impl(
        bf_uint64_t::value_type const reg0_in,
        void **const reg0_out,
        bf_uint64_t::value_type *const reg1_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg0_out);
        bsl::discard(reg1_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_free_page.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_mem_op_free_page_impl(bf_uint64_t::value_type const reg0_in, void *const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_alloc_huge.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg0_out n/a
    ///   @param reg1_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_mem_op_alloc_huge_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint64_t::value_type const reg1_in,
        void **const reg0_out,
        bf_uint64_t::value_type *const reg1_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg0_out);
        bsl::discard(reg1_out);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_free_huge.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_mem_op_free_huge_impl(bf_uint64_t::value_type const reg0_in, void *const reg1_in) noexcept
        -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);

        return {};
    }

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_alloc_heap.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto
    bf_mem_op_alloc_heap_impl(
        bf_uint64_t::value_type const reg0_in,
        bf_uint64_t::value_type const reg1_in,
        void **const reg0_out) noexcept -> bf_status_t::value_type
    {
        bsl::discard(reg0_in);
        bsl::discard(reg1_in);
        bsl::discard(reg0_out);

        return {};
    }

    // -------------------------------------------------------------------------
    // dummy callbacks
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements a dummy bootstrap entry function.
    ///
    /// <!-- inputs/outputs -->
    ///   @param ppid the physical process to bootstrap
    ///
    extern "C" void
    bootstrap_entry(syscall::bf_uint16_t::value_type const ppid) noexcept
    {
        bsl::discard(ppid);
    }

    /// <!-- description -->
    ///   @brief Implements a dummy VMExit entry function.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vpsid the ID of the VPS that generated the VMExit
    ///   @param exit_reason the exit reason associated with the VMExit
    ///
    extern "C" void
    vmexit_entry(
        syscall::bf_uint16_t::value_type const vpsid,
        syscall::bf_uint64_t::value_type const exit_reason) noexcept
    {
        bsl::discard(vpsid);
        bsl::discard(exit_reason);
    }

    /// <!-- description -->
    ///   @brief Implements a dummy fast fail entry function.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vpsid the ID of the VPS that generated the fail
    ///   @param fail_reason the exit reason associated with the fail
    ///
    extern "C" void
    fail_entry(
        syscall::bf_uint16_t::value_type const vpsid,
        syscall::bf_status_t::value_type const fail_reason) noexcept
    {
        bsl::discard(vpsid);
        bsl::discard(fail_reason);
    }

    // -------------------------------------------------------------------------
    // fixtures
    // -------------------------------------------------------------------------

    constinit bf_syscall_t const verify_constinit{};

    // NOLINTNEXTLINE(bsl-user-defined-type-names-match-header-name)
    class fixture_t final
    {
        bf_syscall_t sys{};

    public:
        [[nodiscard]] constexpr auto
        test_member_const() const noexcept -> bool
        {
            bsl::discard(sys.bf_tls_rax());
            bsl::discard(sys.bf_tls_rbx());
            bsl::discard(sys.bf_tls_rcx());
            bsl::discard(sys.bf_tls_rdx());
            bsl::discard(sys.bf_tls_rbp());
            bsl::discard(sys.bf_tls_rsi());
            bsl::discard(sys.bf_tls_rdi());
            bsl::discard(sys.bf_tls_r8());
            bsl::discard(sys.bf_tls_r9());
            bsl::discard(sys.bf_tls_r10());
            bsl::discard(sys.bf_tls_r11());
            bsl::discard(sys.bf_tls_r12());
            bsl::discard(sys.bf_tls_r13());
            bsl::discard(sys.bf_tls_r14());
            bsl::discard(sys.bf_tls_r15());
            bsl::discard(sys.bf_tls_extid());
            bsl::discard(sys.bf_tls_vmid());
            bsl::discard(sys.bf_tls_vpid());
            bsl::discard(sys.bf_tls_vpsid());
            bsl::discard(sys.bf_tls_ppid());
            bsl::discard(sys.bf_tls_online_pps());
            bsl::discard(sys.bf_vps_op_read8({}, {}));
            bsl::discard(sys.bf_vps_op_read16({}, {}));
            bsl::discard(sys.bf_vps_op_read32({}, {}));
            bsl::discard(sys.bf_vps_op_read64({}, {}));
            bsl::discard(sys.bf_vps_op_read_reg({}, {}));
            bsl::discard(sys.bf_intrinsic_op_rdmsr({}));
            bsl::discard(sys.bf_read_phys({}));
            bsl::discard(sys.bf_virt_to_phys({}));
            bsl::discard(sys.bf_phys_to_virt({}));

            return true;
        }

        [[nodiscard]] constexpr auto
        test_member_nonconst() noexcept -> bool
        {
            bf_uint64_t foo{};

            bsl::discard(bf_syscall_t{});
            bsl::discard(sys.initialize(
                BF_ALL_SPECS_SUPPORTED_VAL, bootstrap_entry, vmexit_entry, fail_entry));
            sys.release();
            bsl::discard(sys.bf_tls_rax());
            sys.bf_tls_set_rax({});
            bsl::discard(sys.bf_tls_rbx());
            sys.bf_tls_set_rbx({});
            bsl::discard(sys.bf_tls_rcx());
            sys.bf_tls_set_rcx({});
            bsl::discard(sys.bf_tls_rdx());
            sys.bf_tls_set_rdx({});
            bsl::discard(sys.bf_tls_rbp());
            sys.bf_tls_set_rbp({});
            bsl::discard(sys.bf_tls_rsi());
            sys.bf_tls_set_rsi({});
            bsl::discard(sys.bf_tls_rdi());
            sys.bf_tls_set_rdi({});
            bsl::discard(sys.bf_tls_r8());
            sys.bf_tls_set_r8({});
            bsl::discard(sys.bf_tls_r9());
            sys.bf_tls_set_r9({});
            bsl::discard(sys.bf_tls_r10());
            sys.bf_tls_set_r10({});
            bsl::discard(sys.bf_tls_r11());
            sys.bf_tls_set_r11({});
            bsl::discard(sys.bf_tls_r12());
            sys.bf_tls_set_r12({});
            bsl::discard(sys.bf_tls_r13());
            sys.bf_tls_set_r13({});
            bsl::discard(sys.bf_tls_r14());
            sys.bf_tls_set_r14({});
            bsl::discard(sys.bf_tls_r15());
            sys.bf_tls_set_r15({});
            bsl::discard(sys.bf_tls_extid());
            bsl::discard(sys.bf_tls_vmid());
            bsl::discard(sys.bf_tls_vpid());
            bsl::discard(sys.bf_tls_vpsid());
            bsl::discard(sys.bf_tls_ppid());
            bsl::discard(sys.bf_tls_online_pps());
            bsl::discard(sys.bf_vm_op_create_vm());
            bsl::discard(sys.bf_vm_op_destroy_vm({}));
            bsl::discard(sys.bf_vp_op_create_vp({}, {}));
            bsl::discard(sys.bf_vp_op_destroy_vp({}));
            bsl::discard(sys.bf_vp_op_migrate({}, {}));
            bsl::discard(sys.bf_vps_op_create_vps({}, {}));
            bsl::discard(sys.bf_vps_op_destroy_vps({}));
            bsl::discard(sys.bf_vps_op_init_as_root({}));
            bsl::discard(sys.bf_vps_op_read8({}, {}));
            bsl::discard(sys.bf_vps_op_read16({}, {}));
            bsl::discard(sys.bf_vps_op_read32({}, {}));
            bsl::discard(sys.bf_vps_op_read64({}, {}));
            bsl::discard(sys.bf_vps_op_write8({}, {}, {}));
            bsl::discard(sys.bf_vps_op_write16({}, {}, {}));
            bsl::discard(sys.bf_vps_op_write32({}, {}, {}));
            bsl::discard(sys.bf_vps_op_write64({}, {}, {}));
            bsl::discard(sys.bf_vps_op_read_reg({}, {}));
            bsl::discard(sys.bf_vps_op_write_reg({}, {}, {}));
            bsl::discard(sys.bf_vps_op_run({}, {}, {}));
            bsl::discard(sys.bf_vps_op_run_current());
            bsl::discard(sys.bf_vps_op_advance_ip({}));
            bsl::discard(sys.bf_vps_op_advance_ip_and_run_current());
            bsl::discard(sys.bf_vps_op_promote({}));
            bsl::discard(sys.bf_vps_op_clear_vps({}));
            bsl::discard(sys.bf_intrinsic_op_rdmsr({}));
            bsl::discard(sys.bf_intrinsic_op_wrmsr({}, {}));
            bsl::discard(sys.bf_intrinsic_op_invlpga({}, {}));
            bsl::discard(sys.bf_intrinsic_op_invept({}, {}));
            bsl::discard(sys.bf_intrinsic_op_invvpid({}, {}, {}));
            bsl::discard(sys.bf_mem_op_alloc_page(foo));
            bsl::discard(sys.bf_mem_op_alloc_page());
            bsl::discard(sys.bf_mem_op_free_page(&foo));
            bsl::discard(sys.bf_mem_op_alloc_huge({}, foo));
            bsl::discard(sys.bf_mem_op_alloc_huge({}));
            bsl::discard(sys.bf_mem_op_free_huge(&foo));
            bsl::discard(sys.bf_mem_op_alloc_heap({}));
            bsl::discard(sys.bf_read_phys({}));
            bsl::discard(sys.bf_write_phys({}, foo));
            bsl::discard(sys.bf_virt_to_phys({}));
            bsl::discard(sys.bf_phys_to_virt({}));

            return true;
        }
    };

    constexpr fixture_t fixture1{};
}

/// <!-- description -->
///   @brief Main function for this unit test. If a call to bsl::ut_check() fails
///     the application will fast fail. If all calls to bsl::ut_check() pass, this
///     function will successfully return with bsl::exit_success.
///
/// <!-- inputs/outputs -->
///   @return Always returns bsl::exit_success.
///
[[nodiscard]] auto
main() noexcept -> bsl::exit_code
{
    bsl::ut_scenario{"quiet bootstrap_entry"} = []() {
        bsl::ut_given_at_runtime{} = []() {
            syscall::bf_uint16_t arg0{};
            bsl::ut_then{} = [&arg0]() {
                syscall::bootstrap_entry(arg0.get());
            };
        };
    };

    bsl::ut_scenario{"quiet vmexit_entry"} = []() {
        bsl::ut_given_at_runtime{} = []() {
            syscall::bf_uint16_t arg0{};
            syscall::bf_uint64_t arg1{};
            bsl::ut_then{} = [&arg0, &arg1]() {
                syscall::vmexit_entry(arg0.get(), arg1.get());
            };
        };
    };

    bsl::ut_scenario{"quiet fail_entry"} = []() {
        bsl::ut_given_at_runtime{} = []() {
            syscall::bf_uint16_t arg0{};
            syscall::bf_uint64_t arg1{};
            bsl::ut_then{} = [&arg0, &arg1]() {
                syscall::fail_entry(arg0.get(), arg1.get());
            };
        };
    };

    bsl::ut_scenario{"verify supports constinit"} = []() {
        bsl::discard(syscall::verify_constinit);
    };

    bsl::ut_scenario{"verify noexcept"} = []() {
        bsl::ut_given{} = []() {
            syscall::bf_syscall_t sys{};
            syscall::bf_uint64_t phys{};
            bsl::ut_then{} = []() {
                static_assert(noexcept(syscall::bf_syscall_t{}));
                static_assert(noexcept(sys.initialize(
                    {}, syscall::bootstrap_entry, syscall::vmexit_entry, syscall::fail_entry)));
                static_assert(noexcept(sys.release()));
                static_assert(noexcept(sys.bf_tls_rax()));
                static_assert(noexcept(sys.bf_tls_set_rax({})));
                static_assert(noexcept(sys.bf_tls_rbx()));
                static_assert(noexcept(sys.bf_tls_set_rbx({})));
                static_assert(noexcept(sys.bf_tls_rcx()));
                static_assert(noexcept(sys.bf_tls_set_rcx({})));
                static_assert(noexcept(sys.bf_tls_rdx()));
                static_assert(noexcept(sys.bf_tls_set_rdx({})));
                static_assert(noexcept(sys.bf_tls_rbp()));
                static_assert(noexcept(sys.bf_tls_set_rbp({})));
                static_assert(noexcept(sys.bf_tls_rsi()));
                static_assert(noexcept(sys.bf_tls_set_rsi({})));
                static_assert(noexcept(sys.bf_tls_rdi()));
                static_assert(noexcept(sys.bf_tls_set_rdi({})));
                static_assert(noexcept(sys.bf_tls_r8()));
                static_assert(noexcept(sys.bf_tls_set_r8({})));
                static_assert(noexcept(sys.bf_tls_r9()));
                static_assert(noexcept(sys.bf_tls_set_r9({})));
                static_assert(noexcept(sys.bf_tls_r10()));
                static_assert(noexcept(sys.bf_tls_set_r10({})));
                static_assert(noexcept(sys.bf_tls_r11()));
                static_assert(noexcept(sys.bf_tls_set_r11({})));
                static_assert(noexcept(sys.bf_tls_r12()));
                static_assert(noexcept(sys.bf_tls_set_r12({})));
                static_assert(noexcept(sys.bf_tls_r13()));
                static_assert(noexcept(sys.bf_tls_set_r13({})));
                static_assert(noexcept(sys.bf_tls_r14()));
                static_assert(noexcept(sys.bf_tls_set_r14({})));
                static_assert(noexcept(sys.bf_tls_r15()));
                static_assert(noexcept(sys.bf_tls_set_r15({})));
                static_assert(noexcept(sys.bf_tls_extid()));
                static_assert(noexcept(sys.bf_tls_vmid()));
                static_assert(noexcept(sys.bf_tls_vpid()));
                static_assert(noexcept(sys.bf_tls_vpsid()));
                static_assert(noexcept(sys.bf_tls_ppid()));
                static_assert(noexcept(sys.bf_tls_online_pps()));
                static_assert(noexcept(sys.bf_vm_op_create_vm()));
                static_assert(noexcept(sys.bf_vm_op_destroy_vm({})));
                static_assert(noexcept(sys.bf_vp_op_create_vp({}, {})));
                static_assert(noexcept(sys.bf_vp_op_destroy_vp({})));
                static_assert(noexcept(sys.bf_vp_op_migrate({}, {})));
                static_assert(noexcept(sys.bf_vps_op_create_vps({}, {})));
                static_assert(noexcept(sys.bf_vps_op_destroy_vps({})));
                static_assert(noexcept(sys.bf_vps_op_init_as_root({})));
                static_assert(noexcept(sys.bf_vps_op_read8({}, {})));
                static_assert(noexcept(sys.bf_vps_op_read16({}, {})));
                static_assert(noexcept(sys.bf_vps_op_read32({}, {})));
                static_assert(noexcept(sys.bf_vps_op_read64({}, {})));
                static_assert(noexcept(sys.bf_vps_op_write8({}, {}, {})));
                static_assert(noexcept(sys.bf_vps_op_write16({}, {}, {})));
                static_assert(noexcept(sys.bf_vps_op_write32({}, {}, {})));
                static_assert(noexcept(sys.bf_vps_op_write64({}, {}, {})));
                static_assert(noexcept(sys.bf_vps_op_read_reg({}, {})));
                static_assert(noexcept(sys.bf_vps_op_write_reg({}, {}, {})));
                static_assert(noexcept(sys.bf_vps_op_run({}, {}, {})));
                static_assert(noexcept(sys.bf_vps_op_run_current()));
                static_assert(noexcept(sys.bf_vps_op_advance_ip({})));
                static_assert(noexcept(sys.bf_vps_op_advance_ip_and_run_current()));
                static_assert(noexcept(sys.bf_vps_op_promote({})));
                static_assert(noexcept(sys.bf_vps_op_clear_vps({})));
                static_assert(noexcept(sys.bf_intrinsic_op_rdmsr({})));
                static_assert(noexcept(sys.bf_intrinsic_op_wrmsr({}, {})));
                static_assert(noexcept(sys.bf_intrinsic_op_invlpga({}, {})));
                static_assert(noexcept(sys.bf_intrinsic_op_invept({}, {})));
                static_assert(noexcept(sys.bf_intrinsic_op_invvpid({}, {}, {})));
                static_assert(noexcept(sys.bf_mem_op_alloc_page(phys)));
                static_assert(noexcept(sys.bf_mem_op_alloc_page()));
                static_assert(noexcept(sys.bf_mem_op_free_page({})));
                static_assert(noexcept(sys.bf_mem_op_alloc_huge({}, phys)));
                static_assert(noexcept(sys.bf_mem_op_alloc_huge({})));
                static_assert(noexcept(sys.bf_mem_op_free_huge({})));
                static_assert(noexcept(sys.bf_mem_op_alloc_heap({})));
                static_assert(noexcept(sys.bf_read_phys({})));
                static_assert(noexcept(sys.bf_write_phys({}, syscall::bf_uint64_t{})));
                static_assert(noexcept(sys.bf_virt_to_phys({})));
                static_assert(noexcept(sys.bf_phys_to_virt({})));
            };
        };
    };

    bsl::ut_scenario{"verify constness"} = []() {
        bsl::ut_given{} = []() {
            syscall::fixture_t fixture2{};
            bsl::ut_then{} = [&fixture2]() {
                bsl::ut_check(syscall::fixture1.test_member_const());
                bsl::ut_check(fixture2.test_member_nonconst());
            };
        };
    };

    return bsl::ut_success();
}
