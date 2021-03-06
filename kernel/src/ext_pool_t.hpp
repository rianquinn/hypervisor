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

#ifndef EXT_POOL_T_HPP
#define EXT_POOL_T_HPP

#include <ext_t.hpp>
#include <intrinsic_t.hpp>
#include <page_pool_t.hpp>
#include <root_page_table_t.hpp>
#include <start_vmm_args_t.hpp>
#include <tls_t.hpp>

#include <bsl/array.hpp>
#include <bsl/as_const.hpp>
#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/move.hpp>
#include <bsl/touch.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @class mk::ext_pool_t
    ///
    /// <!-- description -->
    ///   @brief Defines the microkernel's extension pool
    ///
    class ext_pool_t final
    {
        /// @brief stores all of the extensions.
        bsl::array<ext_t, HYPERVISOR_MAX_EXTENSIONS.get()> m_pool{};

    public:
        /// <!-- description -->
        ///   @brief Initializes this ext_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_tls the current TLS block
        ///   @param mut_page_pool the page_pool_t to use
        ///   @param system_rpt the system RPT provided by the loader
        ///   @param elf_files the ext_elf_files provided by the loader
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(
            tls_t &mut_tls,
            page_pool_t &mut_page_pool,
            root_page_table_t const &system_rpt,
            loader::ext_elf_files_t const &elf_files) noexcept -> bsl::errc_type
        {
            bsl::finally mut_release_on_error{[this, &mut_tls, &mut_page_pool]() noexcept -> void {
                this->release(mut_tls, mut_page_pool);
            }};

            for (auto const ext : m_pool) {
                if (nullptr == *elf_files.at_if(ext.index)) {
                    break;
                }

                auto const ret{ext.data->initialize(
                    mut_tls,
                    mut_page_pool,
                    bsl::to_u16(ext.index),
                    *elf_files.at_if(ext.index),
                    system_rpt)};

                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            mut_release_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the ext_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_tls the current TLS block
        ///   @param mut_page_pool the page_pool_t to use
        ///
        constexpr void
        release(tls_t &mut_tls, page_pool_t &mut_page_pool) noexcept
        {
            for (auto const ext : m_pool) {
                ext.data->release(mut_tls, mut_page_pool);
            }
        }

        /// <!-- description -->
        ///   @brief Tells each extension that a VM was created so that it
        ///     can initialize it's VM specific resources.
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_tls the current TLS block
        ///   @param mut_page_pool the page_pool_t to use
        ///   @param vmid the VMID of the VM that was created.
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        signal_vm_created(
            tls_t &mut_tls, page_pool_t &mut_page_pool, bsl::safe_uint16 const &vmid) noexcept
            -> bsl::errc_type
        {
            for (auto const ext : m_pool) {
                auto const ret{ext.data->signal_vm_created(mut_tls, mut_page_pool, vmid)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Tells each extension that a VM was destroyed so that it
        ///     can release it's VM specific resources.
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_tls the current TLS block
        ///   @param mut_page_pool the page_pool_t to use
        ///   @param vmid the VMID of the VM that was destroyed.
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        signal_vm_destroyed(
            tls_t &mut_tls, page_pool_t &mut_page_pool, bsl::safe_uint16 const &vmid) noexcept
            -> bsl::errc_type
        {
            for (auto const ext : m_pool) {
                auto const ret{ext.data->signal_vm_destroyed(mut_tls, mut_page_pool, vmid)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Starts this ext_pool_t by calling all of the
        ///     extension's _start entry points.
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_tls the current TLS block
        ///   @param mut_intrinsic the intrinsic_t to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        start(tls_t &mut_tls, intrinsic_t &mut_intrinsic) noexcept -> bsl::errc_type
        {
            for (auto const ext : m_pool) {
                auto const ret{ext.data->start(mut_tls, mut_intrinsic)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Bootstraps this ext_pool_t by calling all of the
        ///     registered bootstrap callbacks for each extension.
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_tls the current TLS block
        ///   @param mut_intrinsic the intrinsic_t to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        bootstrap(tls_t &mut_tls, intrinsic_t &mut_intrinsic) noexcept -> bsl::errc_type
        {
            for (auto const ext : m_pool) {
                auto const ret{ext.data->bootstrap(mut_tls, mut_intrinsic)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Dumps the requested extension
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param page_pool the page_pool_t to use
        ///   @param extid the ID of the extension to dump
        ///
        constexpr void
        dump(tls_t const &tls, page_pool_t const &page_pool, bsl::safe_uint16 const &extid)
            const noexcept
        {
            if constexpr (BSL_DEBUG_LEVEL == bsl::CRITICAL_ONLY) {
                return;
            }

            auto const *const ext{m_pool.at_if(bsl::to_umax(extid))};
            if (bsl::unlikely(nullptr == ext)) {
                bsl::error() << "invalid extid "    // --
                             << bsl::hex(extid)     // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return;
            }

            ext->dump(tls, page_pool);
        }
    };
}

#endif
