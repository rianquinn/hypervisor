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

#include "../../../src/cpp/bf_syscall_t.hpp"

#include <string>
#include <unordered_map>

#include <bsl/discard.hpp>
#include <bsl/ut.hpp>

namespace syscall
{
    /// @brief stores the answer to all things
    constexpr bf_uint64_t g_answer{bsl::to_umax(42)};

    /// @brief stores the return values for API's that return an integral type
    bf_uint64_t g_data;

    /// @brief stores the return values for a given API
    std::unordered_map<std::string, bf_status_t::value_type> g_ret;

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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return g_data.get();
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
        g_data = val;
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
        return bsl::to_u16(g_data).get();
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
        return bsl::to_u16(g_data).get();
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
        return bsl::to_u16(g_data).get();
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
        return bsl::to_u16(g_data).get();
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
        return bsl::to_u16(g_data).get();
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
        return bsl::to_u16(g_data).get();
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

        return g_ret.at("bf_handle_op_open_handle_impl");
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
        return g_ret.at("bf_handle_op_close_handle_impl");
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

        return g_ret.at("bf_callback_op_register_bootstrap_impl");
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

        return g_ret.at("bf_callback_op_register_vmexit_impl");
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

        return g_ret.at("bf_callback_op_register_fail_impl");
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

        return g_ret.at("bf_vm_op_create_vm_impl");
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

        return g_ret.at("bf_vm_op_destroy_vm_impl");
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

        return g_ret.at("bf_vp_op_create_vp_impl");
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

        return g_ret.at("bf_vp_op_destroy_vp_impl");
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

        return g_ret.at("bf_vp_op_migrate_impl");
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

        return g_ret.at("bf_vps_op_create_vps_impl");
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

        return g_ret.at("bf_vps_op_destroy_vps_impl");
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

        return g_ret.at("bf_vps_op_init_as_root_impl");
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

        return g_ret.at("bf_vps_op_read8_impl");
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

        return g_ret.at("bf_vps_op_read16_impl");
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

        return g_ret.at("bf_vps_op_read32_impl");
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

        return g_ret.at("bf_vps_op_read64_impl");
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

        return g_ret.at("bf_vps_op_write8_impl");
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

        return g_ret.at("bf_vps_op_write16_impl");
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

        return g_ret.at("bf_vps_op_write32_impl");
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

        return g_ret.at("bf_vps_op_write64_impl");
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

        return g_ret.at("bf_vps_op_read_reg_impl");
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

        return g_ret.at("bf_vps_op_write_reg_impl");
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

        return g_ret.at("bf_vps_op_run_impl");
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
        return g_ret.at("bf_vps_op_run_current_impl");
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

        return g_ret.at("bf_vps_op_advance_ip_impl");
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
        return g_ret.at("bf_vps_op_advance_ip_and_run_current_impl");
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

        return g_ret.at("bf_vps_op_promote_impl");
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

        return g_ret.at("bf_vps_op_clear_vps_impl");
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

        return g_ret.at("bf_intrinsic_op_rdmsr_impl");
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

        return g_ret.at("bf_intrinsic_op_wrmsr_impl");
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

        return g_ret.at("bf_intrinsic_op_invlpga_impl");
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

        return g_ret.at("bf_intrinsic_op_invept_impl");
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

        return g_ret.at("bf_intrinsic_op_invvpid_impl");
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

        if (g_ret.at("bf_mem_op_alloc_page_impl") == BF_STATUS_SUCCESS) {
            *reg0_out = &g_data;
            *reg1_out = g_data.get();
        }

        return g_ret.at("bf_mem_op_alloc_page_impl");
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

        return g_ret.at("bf_mem_op_free_page_impl");
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

        if (g_ret.at("bf_mem_op_alloc_huge_impl") == BF_STATUS_SUCCESS) {
            *reg0_out = &g_data;
            *reg1_out = g_data.get();
        }

        return g_ret.at("bf_mem_op_alloc_huge_impl");
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

        return g_ret.at("bf_mem_op_free_huge_impl");
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

        if (g_ret.at("bf_mem_op_alloc_heap_impl") == BF_STATUS_SUCCESS) {
            *reg0_out = &g_data;
        }

        return g_ret.at("bf_mem_op_alloc_heap_impl");
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
    void
    // NOLINTNEXTLINE(bsl-non-safe-integral-types-are-forbidden)
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
    void
    // NOLINTNEXTLINE(bsl-non-safe-integral-types-are-forbidden)
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
    void
    // NOLINTNEXTLINE(bsl-non-safe-integral-types-are-forbidden)
    fail_entry(
        syscall::bf_uint16_t::value_type const vpsid,
        syscall::bf_status_t::value_type const fail_reason) noexcept
    {
        bsl::discard(vpsid);
        bsl::discard(fail_reason);
    }

    // -------------------------------------------------------------------------
    // tests
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Used to execute the actual checks. We put the checks in this
    ///     function so that we can validate the tests both at compile-time
    ///     and at run-time. If a bsl::ut_check fails, the tests will either
    ///     fail fast at run-time, or will produce a compile-time error.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Always returns bsl::exit_success.
    ///
    [[nodiscard]] constexpr auto
    tests() noexcept -> bsl::exit_code
    {
        bsl::ut_scenario{"initialize invalid version #1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_handle_op_open_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_handle_op_close_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_bootstrap_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_vmexit_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_fail_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.initialize(
                            bf_uint32_t::zero(true), bootstrap_entry, vmexit_entry, fail_entry));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize invalid version #1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_handle_op_open_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_handle_op_close_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_bootstrap_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_vmexit_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_fail_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(
                            !sys.initialize({}, bootstrap_entry, vmexit_entry, fail_entry));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize bf_handle_op_open_handle_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_handle_op_open_handle_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    g_ret["bf_handle_op_close_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_bootstrap_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_vmexit_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_fail_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.initialize(
                            BF_ALL_SPECS_SUPPORTED_VAL, bootstrap_entry, vmexit_entry, fail_entry));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize bf_callback_op_register_bootstrap_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_handle_op_open_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_handle_op_close_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_bootstrap_impl"] =
                        BF_STATUS_FAILURE_UNKNOWN.get();
                    g_ret["bf_callback_op_register_vmexit_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_fail_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.initialize(
                            BF_ALL_SPECS_SUPPORTED_VAL, bootstrap_entry, vmexit_entry, fail_entry));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize bf_callback_op_register_vmexit_impl fail"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_handle_op_open_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_handle_op_close_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_bootstrap_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_vmexit_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    g_ret["bf_callback_op_register_fail_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.initialize(
                            BF_ALL_SPECS_SUPPORTED_VAL, bootstrap_entry, vmexit_entry, fail_entry));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize bf_callback_op_register_fail_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_handle_op_open_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_handle_op_close_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_bootstrap_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_vmexit_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_fail_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.initialize(
                            BF_ALL_SPECS_SUPPORTED_VAL, bootstrap_entry, vmexit_entry, fail_entry));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_handle_op_open_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_handle_op_close_handle_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_bootstrap_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_vmexit_impl"] = BF_STATUS_SUCCESS.get();
                    g_ret["bf_callback_op_register_fail_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.initialize(
                            BF_ALL_SPECS_SUPPORTED_VAL, bootstrap_entry, vmexit_entry, fail_entry));
                    };
                };
            };
        };

        bsl::ut_scenario{"release executes"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_handle_op_close_handle_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        sys.release();
                    };
                };
            };
        };

        // ---------------------------------------------------------------------
        // TLS ops
        // ---------------------------------------------------------------------

        bsl::ut_scenario{"bf_tls_rax/bf_tls_set_rax success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rax(bf_uint64_t::zero(true));
                    sys.bf_tls_set_rax(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rax() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbx/bf_tls_set_rbx success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rbx(bf_uint64_t::zero(true));
                    sys.bf_tls_set_rbx(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rbx() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rcx/bf_tls_set_rcx success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rcx(bf_uint64_t::zero(true));
                    sys.bf_tls_set_rcx(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rcx() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdx/bf_tls_set_rdx success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rdx(bf_uint64_t::zero(true));
                    sys.bf_tls_set_rdx(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rdx() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbp/bf_tls_set_rbp success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rbp(bf_uint64_t::zero(true));
                    sys.bf_tls_set_rbp(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rbp() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rsi/bf_tls_set_rsi success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rsi(bf_uint64_t::zero(true));
                    sys.bf_tls_set_rsi(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rsi() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdi/bf_tls_set_rdi success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rdi(bf_uint64_t::zero(true));
                    sys.bf_tls_set_rdi(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rdi() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r8/bf_tls_set_r8 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r8(bf_uint64_t::zero(true));
                    sys.bf_tls_set_r8(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r8() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r9/bf_tls_set_r9 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r9(bf_uint64_t::zero(true));
                    sys.bf_tls_set_r9(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r9() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r10/bf_tls_set_r10 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r10(bf_uint64_t::zero(true));
                    sys.bf_tls_set_r10(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r10() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r11/bf_tls_set_r11 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r11(bf_uint64_t::zero(true));
                    sys.bf_tls_set_r11(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r11() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r11/bf_tls_set_r11 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r11(bf_uint64_t::zero(true));
                    sys.bf_tls_set_r11(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r11() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r12/bf_tls_set_r12 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r12(bf_uint64_t::zero(true));
                    sys.bf_tls_set_r12(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r12() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r13/bf_tls_set_r13 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r13(bf_uint64_t::zero(true));
                    sys.bf_tls_set_r13(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r13() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r14/bf_tls_set_r14 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r14(bf_uint64_t::zero(true));
                    sys.bf_tls_set_r14(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r14() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r15/bf_tls_set_r15 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r15(bf_uint64_t::zero(true));
                    sys.bf_tls_set_r15(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r15() == g_answer);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_extid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_data = g_answer;
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_extid() == bsl::to_u16(g_answer));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vmid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_data = g_answer;
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_vmid() == bsl::to_u16(g_answer));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_data = g_answer;
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_vpid() == bsl::to_u16(g_answer));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpsid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_data = g_answer;
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_vpsid() == bsl::to_u16(g_answer));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_ppid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_data = g_answer;
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_ppid() == bsl::to_u16(g_answer));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_online_pps"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_data = g_answer;
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_online_pps() == bsl::to_u16(g_answer));
                    };
                };
            };
        };

        // ---------------------------------------------------------------------
        // bf_vm_ops
        // ---------------------------------------------------------------------

        bsl::ut_scenario{"bf_vm_op_create_vm invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vm_op_create_vm_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vm_op_create_vm(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_create_vm bf_vm_op_create_vm_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vm_op_create_vm_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vm_op_create_vm(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_create_vm success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vm_op_create_vm_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_vm_op_create_vm(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_destroy_vm invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vm_op_destroy_vm_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vm_op_destroy_vm(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_destroy_vm bf_vm_op_destroy_vm_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vm_op_destroy_vm_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vm_op_destroy_vm(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_destroy_vm success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vm_op_destroy_vm_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_vm_op_destroy_vm(arg0));
                    };
                };
            };
        };

        // ---------------------------------------------------------------------
        // bf_vp_ops
        // ---------------------------------------------------------------------

        bsl::ut_scenario{"bf_vp_op_create_vp invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_create_vp_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vp_op_create_vp(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_create_vp_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vp_op_create_vp(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp invalid arg2"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_create_vp_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vp_op_create_vp(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp bf_vp_op_create_vp_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_create_vp_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vp_op_create_vp(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_create_vp_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(sys.bf_vp_op_create_vp(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_destroy_vp invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_destroy_vp_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vp_op_destroy_vp(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_destroy_vp bf_vp_op_destroy_vp_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_destroy_vp_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vp_op_destroy_vp(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_destroy_vp success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_destroy_vp_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_vp_op_destroy_vp(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint16_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_migrate_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vp_op_migrate(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_migrate_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vp_op_migrate(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate bf_vp_op_migrate_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_migrate_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vp_op_migrate(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vp_op_migrate_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vp_op_migrate(arg0, arg1));
                    };
                };
            };
        };

        // ---------------------------------------------------------------------
        // bf_vps_ops
        // ---------------------------------------------------------------------

        bsl::ut_scenario{"bf_vps_op_create_vps invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_create_vps_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_create_vps(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_create_vps_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_create_vps(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps invalid arg2"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_create_vps_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_create_vps(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps bf_vps_op_create_vps_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_create_vps_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_create_vps(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_create_vps_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(sys.bf_vps_op_create_vps(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_destroy_vps invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_destroy_vps_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_destroy_vps(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_destroy_vps bf_vps_op_destroy_vps_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_destroy_vps_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_destroy_vps(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_destroy_vps success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_destroy_vps_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_vps_op_destroy_vps(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_init_as_root invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_init_as_root_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_init_as_root(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_init_as_root bf_vps_op_init_as_root_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_init_as_root_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_init_as_root(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_init_as_root success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_init_as_root_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_vps_op_init_as_root(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8 invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read8_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read8(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8 invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read8_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read8(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8 bf_vps_op_read8_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read8_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read8(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read8_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read8(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16 invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read16_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read16(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16 invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read16_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read16(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16 bf_vps_op_read16_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read16_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read16(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read16_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read16(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32 invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read32_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read32(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32 invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read32_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read32(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32 bf_vps_op_read32_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read32_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read32(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read32_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read32(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64 invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read64_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read64(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64 invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read64_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read64(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64 bf_vps_op_read64_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read64_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read64(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read64_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read64(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{};
                bf_uint8_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write8_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write8(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bf_uint8_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write8_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write8(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 invalid arg2"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint8_t arg2{bf_uint8_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write8_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write8(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 bf_vps_op_write8_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint8_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write8_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write8(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint8_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write8_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(sys.bf_vps_op_write8(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write16_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write16(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write16_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write16(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 invalid arg2"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint16_t arg2{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write16_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write16(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 bf_vps_op_write16_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write16_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write16(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write16_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(sys.bf_vps_op_write16(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{};
                bf_uint32_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write32_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write32(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bf_uint32_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write32_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write32(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 invalid arg2"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint32_t arg2{bf_uint32_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write32_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write32(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 bf_vps_op_write32_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint32_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write32_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write32(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint32_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write32_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(sys.bf_vps_op_write32(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write64_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write64(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write64_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write64(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 invalid arg2"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint64_t arg2{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write64_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write64(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 bf_vps_op_write64_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write64_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write64(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write64_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(sys.bf_vps_op_write64(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_reg_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read_reg_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read_reg(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg bf_vps_op_read_reg_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_reg_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read_reg_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read_reg(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_reg_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_read_reg_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read_reg(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_reg_t arg1{};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write_reg_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write_reg(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg invalid arg2"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_reg_t arg1{};
                bf_uint64_t arg2{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write_reg_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write_reg(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg bf_vps_op_write_reg_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_reg_t arg1{};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write_reg_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write_reg(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_reg_t arg1{};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_write_reg_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(sys.bf_vps_op_write_reg(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_run_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_run(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_run_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_run(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run invalid arg2"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_run_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_run(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run bf_vps_op_run_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_run_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_run(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bf_uint16_t arg1{};
                bf_uint16_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_run_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(sys.bf_vps_op_run(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_current bf_vps_op_run_current_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_run_current_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.bf_vps_op_run_current());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_current success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_run_current_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_vps_op_run_current());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_advance_ip_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_advance_ip(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip bf_vps_op_advance_ip_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_advance_ip_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_advance_ip(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_advance_ip_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_vps_op_advance_ip(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_and_run_current bf_vps_op_advance_ip_and_run_current_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_advance_ip_and_run_current_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.bf_vps_op_advance_ip_and_run_current());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_and_run_current success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_advance_ip_and_run_current_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_vps_op_advance_ip_and_run_current());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_promote invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_promote_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_promote(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_promote bf_vps_op_promote_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_promote_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_promote(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_promote success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_promote_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_vps_op_promote(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_clear_vps invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_clear_vps_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_clear_vps(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_clear_vps bf_vps_op_clear_vps_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_clear_vps_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_clear_vps(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_clear_vps success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_vps_op_clear_vps_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_vps_op_clear_vps(arg0));
                    };
                };
            };
        };

        // ---------------------------------------------------------------------
        // bf_intrinsic_ops
        // ---------------------------------------------------------------------

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{bf_uint32_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_rdmsr_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_rdmsr(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr bf_intrinsic_op_rdmsr_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_rdmsr_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_rdmsr(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_rdmsr_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_intrinsic_op_rdmsr(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{bf_uint32_t::zero(true)};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_wrmsr_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_wrmsr(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_wrmsr_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_wrmsr(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr bf_intrinsic_op_wrmsr_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_wrmsr_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_wrmsr(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_wrmsr_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_intrinsic_op_wrmsr(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invlpga_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invlpga(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invlpga_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invlpga(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga bf_intrinsic_op_invlpga_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invlpga_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invlpga(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invlpga_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_intrinsic_op_invlpga(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invept_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invept(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invept_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invept(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept bf_intrinsic_op_invept_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invept_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invept(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invept_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_intrinsic_op_invept(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bf_uint16_t arg1{};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invvpid_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invvpid_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid invalid arg2"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint16_t arg1{};
                bf_uint64_t arg2{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invvpid_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid bf_intrinsic_op_invvpid_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint16_t arg1{};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invvpid_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint16_t arg1{};
                bf_uint64_t arg2{};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    g_ret.clear();
                    g_ret["bf_intrinsic_op_invvpid_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                    };
                };
            };
        };

        // ---------------------------------------------------------------------
        // bf_mem_ops
        // ---------------------------------------------------------------------

        bsl::ut_scenario{"bf_mem_op_alloc_page invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_page_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_page<bf_uint64_t>(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page bf_mem_op_alloc_page_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_page_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_page<bf_uint64_t>(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_page_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(&g_data == sys.bf_mem_op_alloc_page<bf_uint64_t>(arg0));
                        bsl::ut_check(g_data == arg0);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page bf_mem_op_alloc_page_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_page_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_page<bf_uint64_t>());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_page_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(&g_data == sys.bf_mem_op_alloc_page<bf_uint64_t>());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_page invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                void *arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_free_page_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_mem_op_free_page(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_page bf_mem_op_free_page_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                void *arg0{&g_data};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_free_page_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_mem_op_free_page(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_page success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                void *arg0{&g_data};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_free_page_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_mem_op_free_page(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_huge_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_huge<bf_uint64_t>(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge invalid arg1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_huge_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_huge<bf_uint64_t>(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge bf_mem_op_alloc_huge_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_huge_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_huge<bf_uint64_t>(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_huge_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(&g_data == sys.bf_mem_op_alloc_huge<bf_uint64_t>(arg0, arg1));
                        bsl::ut_check(g_data == arg1);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_huge_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_huge<bf_uint64_t>(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge bf_mem_op_alloc_huge_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_huge_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_huge<bf_uint64_t>(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_huge_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(&g_data == sys.bf_mem_op_alloc_huge<bf_uint64_t>(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_huge invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                void *arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_free_huge_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_mem_op_free_huge(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_huge bf_mem_op_free_huge_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                void *arg0{&g_data};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_free_huge_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_mem_op_free_huge(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_huge success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                void *arg0{&g_data};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_free_huge_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_mem_op_free_huge(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_heap invalid arg0"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_heap_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_heap<bf_uint64_t>(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_heap bf_mem_op_alloc_heap_impl fails"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_heap_impl"] = BF_STATUS_FAILURE_UNKNOWN.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(nullptr == sys.bf_mem_op_alloc_heap<bf_uint64_t>(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_heap success"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{};
                bsl::ut_when{} = [&sys, &arg0]() {
                    g_ret.clear();
                    g_ret["bf_mem_op_alloc_heap_impl"] = BF_STATUS_SUCCESS.get();
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(&g_data == sys.bf_mem_op_alloc_heap<bf_uint64_t>(arg0));
                    };
                };
            };
        };








        return bsl::ut_success();
    }
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
    bsl::enable_color();

    static_assert(syscall::tests() == bsl::ut_success());
    return syscall::tests();
}
