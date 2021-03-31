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

#ifndef EXT_T_HPP
#define EXT_T_HPP

#include "huge_t.hpp"
#include "page_t.hpp"

#include <call_ext.hpp>
#include <elf64_ehdr_t.hpp>
#include <elf64_phdr_t.hpp>
#include <map_page_flags.hpp>
#include <mk_interface.hpp>

#include <bsl/array.hpp>
#include <bsl/discard.hpp>
#include <bsl/finally.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @brief defines the value of an invalid EXTID
    constexpr bsl::safe_uint16 INVALID_EXTID{bsl::to_u16(0xFFFFU)};

    /// @class mk::ext_t
    ///
    /// <!-- description -->
    ///   @brief TODO
    ///
    /// <!-- template parameters -->
    ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
    ///   @tparam HUGE_POOL_CONCEPT defines the type of huge pool to use
    ///   @tparam ROOT_PAGE_TABLE_CONCEPT defines the type of RPT pool to use
    ///   @tparam PAGE_SIZE defines the size of a page
    ///   @tparam MAX_PPS the max number of PPs supported
    ///   @tparam MAX_VMS the max number of VMs supported
    ///   @tparam EXT_DIRECT_MAP_ADDR the address of the extension's direct map
    ///   @tparam EXT_DIRECT_MAP_SIZE the size of the extension's direct map
    ///   @tparam EXT_STACK_ADDR the address of the extension's stack
    ///   @tparam EXT_STACK_SIZE the size of the extension's stack
    ///   @tparam EXT_CODE_ADDR the address of the extension's code
    ///   @tparam EXT_CODE_SIZE the size of the extension's code
    ///   @tparam EXT_TLS_ADDR the address of the extension's TLS block
    ///   @tparam EXT_TLS_SIZE the size of the extension's TLS block
    ///   @tparam EXT_PAGE_POOL_ADDR the address of the extension's page pool
    ///   @tparam EXT_PAGE_POOL_SIZE the size of the extension's page pool
    ///   @tparam EXT_HUGE_POOL_ADDR the address of the extension's huge pool
    ///   @tparam EXT_HUGE_POOL_SIZE the size of the extension's huge pool
    ///   @tparam EXT_HEAP_POOL_ADDR the address of the extension's heap pool
    ///   @tparam EXT_HEAP_POOL_SIZE the size of the extension's heap pool
    ///
    template<
        typename INTRINSIC_CONCEPT,
        typename PAGE_POOL_CONCEPT,
        typename HUGE_POOL_CONCEPT,
        typename ROOT_PAGE_TABLE_CONCEPT,
        bsl::uintmax PAGE_SIZE,
        bsl::uintmax MAX_PPS,
        bsl::uintmax MAX_VMS,
        bsl::uintmax EXT_DIRECT_MAP_ADDR,
        bsl::uintmax EXT_DIRECT_MAP_SIZE,
        bsl::uintmax EXT_STACK_ADDR,
        bsl::uintmax EXT_STACK_SIZE,
        bsl::uintmax EXT_CODE_ADDR,
        bsl::uintmax EXT_CODE_SIZE,
        bsl::uintmax EXT_TLS_ADDR,
        bsl::uintmax EXT_TLS_SIZE,
        bsl::uintmax EXT_PAGE_POOL_ADDR,
        bsl::uintmax EXT_PAGE_POOL_SIZE,
        bsl::uintmax EXT_HUGE_POOL_ADDR,
        bsl::uintmax EXT_HUGE_POOL_SIZE,
        bsl::uintmax EXT_HEAP_POOL_ADDR,
        bsl::uintmax EXT_HEAP_POOL_SIZE>
    class ext_t final
    {
        /// @brief stores true if initialized() has been executed
        bool m_initialized{};
        /// @brief stores true if start() has been executed
        bool m_started{};
        /// @brief stores a reference to the intrinsics to use
        INTRINSIC_CONCEPT *m_intrinsic{};
        /// @brief stores a reference to the page pool to use
        PAGE_POOL_CONCEPT *m_page_pool{};
        /// @brief stores a reference to the huge pool to use
        HUGE_POOL_CONCEPT *m_huge_pool{};
        /// @brief stores the ID associated with this ext_t
        bsl::safe_uint16 m_id{bsl::safe_uint16::zero(true)};
        /// @brief stores an extension's ELF file
        bsl::span<bsl::byte const> m_elf_file{};
        /// @brief stores the total number of online PPs
        bsl::safe_uint16 m_online_pps{bsl::safe_uint16::zero(true)};
        /// @brief stores the root page table for the microkernel.
        ROOT_PAGE_TABLE_CONCEPT const *m_system_rpt{};

        /// @brief stores the main rpt
        ROOT_PAGE_TABLE_CONCEPT m_main_rpt{};
        /// @brief stores the direct map rpts
        bsl::array<ROOT_PAGE_TABLE_CONCEPT, MAX_VMS> m_direct_map_rpts{};
        /// @brief stores a pointer to the current direct map rpt
        ROOT_PAGE_TABLE_CONCEPT *m_current_direct_map_rpt{};
        /// @brief stores the main IP registered by the extension
        bsl::safe_uintmax m_main_ip{bsl::safe_uintmax::zero(true)};
        /// @brief stores the bootstrap IP registered by the extension
        bsl::safe_uintmax m_bootstrap_ip{bsl::safe_uintmax::zero(true)};
        /// @brief stores the vmexit IP registered by the extension
        bsl::safe_uintmax m_vmexit_ip{bsl::safe_uintmax::zero(true)};
        /// @brief stores the fail IP registered by the extension
        bsl::safe_uintmax m_fail_ip{bsl::safe_uintmax::zero(true)};
        /// @brief stores the extension's handle
        bsl::safe_uintmax m_handle{bsl::safe_uintmax::zero(true)};
        /// @brief stores the extension's page pool cursor
        bsl::safe_uintmax m_page_pool_crsr{};
        /// @brief stores the extension's huge pool cursor
        bsl::safe_uintmax m_huge_pool_crsr{};
        /// @brief stores the extension's heap pool cursor
        bsl::safe_uintmax m_heap_pool_crsr{};

        /// <!-- description -->
        ///   @brief Validates the provided pt_load segment.
        ///
        /// <!-- inputs/outputs -->
        ///   @param phdr the pt_load segment to validate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        validate_pt_load(bfelf::elf64_phdr_t const *const phdr) &noexcept -> bsl::errc_type
        {
            if ((bsl::to_u32(phdr->p_flags) & bfelf::PF_X).is_pos()) {
                if (bsl::unlikely((bsl::to_u32(phdr->p_flags) & bfelf::PF_W).is_pos())) {
                    bsl::error() << "ELF code segment flags not supported\n" << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                bsl::touch();
            }

            if ((bsl::to_u32(phdr->p_flags) & bfelf::PF_W).is_pos()) {
                if (bsl::unlikely((bsl::to_u32(phdr->p_flags) & bfelf::PF_X).is_pos())) {
                    bsl::error() << "ELF code segment flags not supported\n" << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                bsl::touch();
            }

            if (bsl::unlikely(bsl::to_umax(phdr->p_offset) > m_elf_file.size())) {
                bsl::error() << "ELF code segment offset invalid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(bsl::to_umax(phdr->p_vaddr) < EXT_CODE_ADDR)) {
                bsl::error() << "ELF code segment virtual address not supported\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto const required_memsz{bsl::to_umax(phdr->p_vaddr) + bsl::to_umax(phdr->p_memsz)};
            if (bsl::unlikely(required_memsz > (EXT_CODE_ADDR + EXT_CODE_SIZE))) {
                bsl::error() << "ELF code segment virtual address not supported\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto const required_filesz{bsl::to_umax(phdr->p_filesz) + bsl::to_umax(phdr->p_offset)};
            if (bsl::unlikely(required_filesz > m_elf_file.size())) {
                bsl::error() << "ELF code segment filesz invalid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(bsl::to_umax(phdr->p_memsz) > EXT_CODE_SIZE)) {
                bsl::error() << "ELF code segment memsz invalid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(phdr->p_align != PAGE_SIZE)) {
                bsl::error() << "ELF code segment alignment not supported\n" << bsl::here();
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Validates the provided pt_gnu_stack segment.
        ///
        /// <!-- inputs/outputs -->
        ///   @param phdr the pt_gnu_stack segment to validate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        validate_pt_gnu_stack(bfelf::elf64_phdr_t const *const phdr) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely((bsl::to_u32(phdr->p_flags) & bfelf::PF_X).is_pos())) {
                bsl::error() << "Executable stacks are not supported\n" << bsl::here();
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Validates the provided pt_tls segment.
        ///
        /// <!-- inputs/outputs -->
        ///   @param phdr the pt_tls segment to validate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        validate_pt_tls(bfelf::elf64_phdr_t const *const phdr) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely((bsl::to_u32(phdr->p_flags) & bfelf::PF_X).is_pos())) {
                bsl::error() << "Executable TLS blocks are not supported\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(bsl::to_umax(phdr->p_offset) > m_elf_file.size())) {
                bsl::error() << "ELF TLS segment offset invalid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(bsl::to_umax(phdr->p_vaddr) < EXT_CODE_ADDR)) {
                bsl::error() << "ELF TLS segment virtual address not supported\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto const required_memsz{bsl::to_umax(phdr->p_vaddr) + bsl::to_umax(phdr->p_memsz)};
            if (bsl::unlikely(required_memsz > (EXT_CODE_ADDR + EXT_CODE_SIZE))) {
                bsl::error() << "ELF TLS segment virtual address not supported\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto const required_filesz{bsl::to_umax(phdr->p_filesz) + bsl::to_umax(phdr->p_offset)};
            if (bsl::unlikely(required_filesz > m_elf_file.size())) {
                bsl::error() << "ELF TLS segment filesz invalid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(bsl::to_umax(phdr->p_memsz) > PAGE_SIZE)) {
                bsl::error() << "ELF TLS segment memsz invalid\n" << bsl::here();
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Validates the provided ELF file.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        validate() &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!bfelf::validate_elf64_ehdr(m_elf_file))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            auto const phdrtab{bfelf::get_elf64_phdrtab(m_elf_file)};
            if (bsl::unlikely(phdrtab.empty())) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            /// TODO:
            /// - Add support for GNU RELOC segments so that we can set
            ///   the RW permissions properly
            ///

            bool found_pt_load{};
            bool found_pt_gnu_stack{};

            for (auto const elem : phdrtab) {
                switch (elem.data->p_type) {
                    case bfelf::PT_LOAD.get(): {
                        found_pt_load = true;
                        if (bsl::unlikely(!this->validate_pt_load(elem.data))) {
                            bsl::print<bsl::V>() << bsl::here();
                            return bsl::errc_failure;
                        }
                        break;
                    }

                    case bfelf::PT_GNU_STACK.get(): {
                        found_pt_gnu_stack = true;
                        if (bsl::unlikely(!this->validate_pt_gnu_stack(elem.data))) {
                            bsl::print<bsl::V>() << bsl::here();
                            return bsl::errc_failure;
                        }
                        break;
                    }

                    case bfelf::PT_TLS.get(): {
                        if (bsl::unlikely(!this->validate_pt_tls(elem.data))) {
                            bsl::print<bsl::V>() << bsl::here();
                            return bsl::errc_failure;
                        }
                        break;
                    }

                    default: {
                        break;
                    }
                }
            }

            if (bsl::unlikely(!found_pt_load)) {
                bsl::error() << "PT_LOAD segments missing from ELF file\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!found_pt_gnu_stack)) {
                bsl::error() << "PT_GNU_STACK segment missing from ELF file\n" << bsl::here();
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Adds all of the program segments given an ELF file to
        ///     the provided root page table.
        ///
        /// <!-- inputs/outputs -->
        ///   @param rpt the root page table to add too
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        add_segments(ROOT_PAGE_TABLE_CONCEPT &rpt) &noexcept -> bsl::errc_type
        {
            bsl::span<bsl::byte> page{};

            auto const phdrtab{bfelf::get_elf64_phdrtab(m_elf_file)};
            for (auto const elem : phdrtab) {
                auto const *const phdr{elem.data};

                if (bfelf::PT_LOAD != phdr->p_type) {
                    continue;
                }

                bsl::safe_uintmax const bytes_to_allocate{phdr->p_memsz};
                bsl::safe_uintmax bytes_to_copy{phdr->p_filesz};

                bsl::safe_uintmax bytes_to_next_page{PAGE_SIZE};
                bsl::safe_uintmax bytes_into_page{phdr->p_vaddr & (PAGE_SIZE - bsl::ONE_UMAX)};

                if (bytes_into_page.is_pos()) {
                    bytes_to_next_page -= bytes_into_page;
                }
                else {
                    bsl::touch();
                }

                bsl::safe_uintmax bytes{};
                while (bytes < bytes_to_allocate) {

                    if (bytes_to_next_page == PAGE_SIZE) {
                        if ((phdr->p_flags & bfelf::PF_X).is_pos()) {
                            page = bsl::as_writable_t<bsl::byte>(
                                rpt.allocate_page_rx(phdr->p_vaddr + bytes), PAGE_SIZE);
                        }
                        else {
                            page = bsl::as_writable_t<bsl::byte>(
                                rpt.allocate_page_rw(phdr->p_vaddr + bytes), PAGE_SIZE);
                        }

                        if (bsl::unlikely(!page)) {
                            bsl::print<bsl::V>() << bsl::here();
                            return bsl::errc_failure;
                        }

                        bsl::touch();
                    }
                    else {
                        if (bsl::unlikely(!page)) {
                            bsl::error() << "The first ELF segment is invalid\n" << bsl::here();
                            return bsl::errc_failure;
                        }

                        bsl::touch();
                    }

                    if (bytes_to_copy.is_pos()) {
                        bsl::safe_uintmax bytes_to_copy_in_this_page{bytes_to_copy};
                        if (bytes_to_copy_in_this_page > bytes_to_next_page) {
                            bytes_to_copy_in_this_page = bytes_to_next_page;
                        }
                        else {
                            bsl::touch();
                        }

                        auto *const dst_addr{page.at_if(bytes_into_page)};
                        if (bsl::unlikely(nullptr == dst_addr)) {
                            bsl::print<bsl::V>() << bsl::here();
                            return bsl::errc_failure;
                        }

                        auto const *const src_addr{m_elf_file.at_if(phdr->p_offset + bytes)};
                        if (bsl::unlikely(nullptr == src_addr)) {
                            bsl::print<bsl::V>() << bsl::here();
                            return bsl::errc_failure;
                        }

                        bsl::builtin_memcpy(dst_addr, src_addr, bytes_to_copy_in_this_page);
                        bytes_to_copy -= bytes_to_copy_in_this_page;
                    }
                    else {
                        bsl::touch();
                    }

                    bytes += bytes_to_next_page;
                    bytes_to_next_page = PAGE_SIZE;
                    bytes_into_page = bsl::ZERO_UMAX;
                }
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Adds an exteneion's stack for a specific PP to the
        ///     provided root page table at the provided address.
        ///
        /// <!-- inputs/outputs -->
        ///   @param rpt the root page table to add too
        ///   @param addr the address of where to put the stack
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        add_stack(ROOT_PAGE_TABLE_CONCEPT &rpt, bsl::safe_uintmax const &addr) &noexcept
            -> bsl::errc_type
        {
            for (bsl::safe_uintmax bytes{}; bytes < EXT_STACK_SIZE; bytes += PAGE_SIZE) {
                void *page{rpt.allocate_page_rw(addr + bytes)};
                if (bsl::unlikely(nullptr == page)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Adds the exteneion's stacks to the provided
        ///     root page table.
        ///
        /// <!-- inputs/outputs -->
        ///   @param rpt the root page table to add too
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        add_stacks(ROOT_PAGE_TABLE_CONCEPT &rpt) &noexcept -> bsl::errc_type
        {
            for (bsl::safe_uintmax pp{}; pp < bsl::to_umax(m_online_pps); ++pp) {
                auto const offs{(EXT_STACK_SIZE + PAGE_SIZE) * pp};
                auto const addr{(EXT_STACK_ADDR + offs)};

                if (bsl::unlikely(!this->add_stack(rpt, addr))) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Adds an exteneion's TLS block for a specific PP to the
        ///     provided root page table at the provided address.
        ///
        /// <!-- inputs/outputs -->
        ///   @param rpt the root page table to add too
        ///   @param addr_usr the address the user's portion of the TLS block
        ///   @param addr_abi the address the ABI's portion of the TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        add_tls_block(
            ROOT_PAGE_TABLE_CONCEPT &rpt,
            bsl::safe_uintmax const &addr_usr,
            bsl::safe_uintmax const &addr_abi) &noexcept -> bsl::errc_type
        {
            bsl::span<bsl::uint8> page_usr{};
            bsl::span<bsl::uintmax> page_abi{};

            page_usr = bsl::as_writable_t<bsl::uint8>(rpt.allocate_page_rw(addr_usr), PAGE_SIZE);
            if (bsl::unlikely(!page_usr)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            page_abi = bsl::as_writable_t<bsl::uintmax>(rpt.allocate_page_rw(addr_abi), PAGE_SIZE);
            if (bsl::unlikely(!page_abi)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            *page_abi.front_if() = addr_abi.get();

            auto const phdrtab{bfelf::get_elf64_phdrtab(m_elf_file)};
            for (auto const elem : phdrtab) {
                auto const *const phdr{elem.data};

                if (bfelf::PT_TLS != phdr->p_type) {
                    continue;
                }

                auto const *const src_addr{m_elf_file.at_if(phdr->p_offset)};
                auto const dst_index{PAGE_SIZE - bsl::to_umax(phdr->p_memsz)};
                bsl::builtin_memcpy(page_usr.at_if(dst_index), src_addr, phdr->p_memsz);

                return bsl::errc_success;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Adds the exteneion's TLS block to the provided
        ///     root page table.
        ///
        /// <!-- inputs/outputs -->
        ///   @param rpt the root page table to add too
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        add_tls_blocks(ROOT_PAGE_TABLE_CONCEPT &rpt) &noexcept -> bsl::errc_type
        {
            for (bsl::safe_uintmax pp{}; pp < bsl::to_umax(m_online_pps); ++pp) {
                auto const offs{(EXT_TLS_SIZE + PAGE_SIZE) * pp};
                auto const addr{(EXT_TLS_ADDR + offs)};

                if (bsl::unlikely(!this->add_tls_block(rpt, addr, addr + PAGE_SIZE))) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Initializes a root page table to support the execution
        ///     of this extension.
        ///
        /// <!-- inputs/outputs -->
        ///   @param rpt the root page table to initialize
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize_rpt(ROOT_PAGE_TABLE_CONCEPT &rpt) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!rpt.initialize(m_intrinsic, m_page_pool))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[&rpt]() noexcept -> void {
                rpt.release();
            }};

            if (bsl::unlikely(!rpt.add_tables(*m_system_rpt))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->add_segments(rpt))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->add_stacks(rpt))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->add_tls_blocks(rpt))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            release_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Initializes a direct map root page table to support the
        ///     execution of this extension (with the inclusion of a direct
        ///     map).
        ///
        /// <!-- inputs/outputs -->
        ///   @param rpt the root page table to initialize
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize_direct_map_rpt(ROOT_PAGE_TABLE_CONCEPT &rpt) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!rpt.initialize(m_intrinsic, m_page_pool))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[&rpt]() noexcept -> void {
                rpt.release();
            }};

            if (bsl::unlikely(!rpt.add_tables(m_main_rpt))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            release_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Executes the extension given an instruction pointer to
        ///     execute the extension at, a stack pointer to execute the
        ///     extension with, and a root page table defining the memory
        ///     layout to execute the extension with.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param ip the instruction pointer defining where in the
        ///     extension to start execution at.
        ///   @param rpt the root page table defining the memory layout to
        ///     execute the extension with
        ///   @param arg0 the first argument to pass the extension
        ///   @param arg1 the second argument to pass the extension
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        execute(
            TLS_CONCEPT &tls,
            bsl::safe_uintmax const &ip,
            ROOT_PAGE_TABLE_CONCEPT const &rpt,
            bsl::safe_uintmax const &arg0 = {},
            bsl::safe_uintmax const &arg1 = {}) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "ext_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!ip)) {
                bsl::error() << "invalid instruction pointer\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (tls.ext != this) {
                if (bsl::unlikely(!rpt.activate())) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                tls.ext = this;
                tls.set_extid(m_id);
            }
            else {
                bsl::touch();
            }

            bsl::exit_code const ret{call_ext(ip.get(), tls.sp, arg0.get(), arg1.get())};
            if (bsl::unlikely(ret != bsl::exit_success)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

    public:
        /// @brief an alias for INTRINSIC_CONCEPT
        using intrinsic_type = INTRINSIC_CONCEPT;
        /// @brief an alias for PAGE_POOL_CONCEPT
        using page_pool_type = PAGE_POOL_CONCEPT;
        /// @brief an alias for HUGE_POOL_CONCEPT
        using huge_pool_type = HUGE_POOL_CONCEPT;
        /// @brief an alias for ROOT_PAGE_TABLE_CONCEPT
        using root_page_table_type = ROOT_PAGE_TABLE_CONCEPT;

        /// <!-- description -->
        ///   @brief Default constructor
        ///
        constexpr ext_t() noexcept = default;

        /// <!-- description -->
        ///   @brief Initializes this ext_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param intrinsic the intrinsics to use
        ///   @param page_pool the page pool to use
        ///   @param huge_pool the huge pool to use
        ///   @param i the ID for this ext_t
        ///   @param ext_elf_file the ELF file for this ext_t
        ///   @param online_pps the total number of PPs that are online
        ///   @param system_rpt the system RPT provided by the loader
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(
            INTRINSIC_CONCEPT *const intrinsic,
            PAGE_POOL_CONCEPT *const page_pool,
            HUGE_POOL_CONCEPT *const huge_pool,
            bsl::safe_uint16 const &i,
            bsl::span<bsl::byte const> const &ext_elf_file,
            bsl::safe_uint16 const &online_pps,
            ROOT_PAGE_TABLE_CONCEPT const *const system_rpt) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(m_initialized)) {
                bsl::error() << "ext_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[this]() noexcept -> void {
                this->release();
            }};

            m_intrinsic = intrinsic;
            if (bsl::unlikely(nullptr == intrinsic)) {
                bsl::error() << "invalid intrinsic\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_page_pool = page_pool;
            if (bsl::unlikely(nullptr == page_pool)) {
                bsl::error() << "invalid page_pool\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_huge_pool = huge_pool;
            if (bsl::unlikely(nullptr == huge_pool)) {
                bsl::error() << "invalid huge_pool\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_id = i;
            if (bsl::unlikely(!i)) {
                bsl::error() << "invalid id\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_elf_file = ext_elf_file;
            if (bsl::unlikely(!this->validate())) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_online_pps = online_pps;
            if (bsl::unlikely(!online_pps)) {
                bsl::error() << "invalid online_pps\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_system_rpt = system_rpt;
            if (bsl::unlikely(!this->initialize_rpt(m_main_rpt))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_main_ip = bfelf::get_elf64_ip(ext_elf_file);

            release_on_error.ignore();
            m_initialized = true;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the ext_t
        ///
        constexpr void
        release() &noexcept
        {
            m_heap_pool_crsr = bsl::safe_uintmax::zero(true);
            m_huge_pool_crsr = bsl::safe_uintmax::zero(true);
            m_page_pool_crsr = bsl::safe_uintmax::zero(true);
            m_handle = bsl::safe_uintmax::zero(true);
            m_fail_ip = bsl::safe_uintmax::zero(true);
            m_vmexit_ip = bsl::safe_uintmax::zero(true);
            m_bootstrap_ip = bsl::safe_uintmax::zero(true);
            m_main_ip = bsl::safe_uintmax::zero(true);
            m_current_direct_map_rpt = {};

            for (auto const rpt : m_direct_map_rpts) {
                rpt.data->release();
            }

            m_main_rpt.release();
            m_system_rpt = {};
            m_online_pps = bsl::safe_uint16::zero(true);
            m_elf_file = {};
            m_id = bsl::safe_uint16::zero(true);
            m_huge_pool = {};
            m_page_pool = {};
            m_intrinsic = {};
            m_started = {};
            m_initialized = {};
        }

        /// <!-- description -->
        ///   @brief Destructor
        ///
        constexpr ~ext_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr ext_t(ext_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr ext_t(ext_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(ext_t const &o) &noexcept -> ext_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(ext_t &&o) &noexcept -> ext_t & = default;

        /// <!-- description -->
        ///   @brief Returns the ID of this ext_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of this ext_t
        ///
        [[nodiscard]] constexpr auto
        id() const &noexcept -> bsl::safe_uint16 const &
        {
            return m_id;
        }

        /// <!-- description -->
        ///   @brief Returns the bootstrap IP for this extension.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the bootstrap IP for this extension.
        ///
        [[nodiscard]] constexpr auto
        bootstrap_ip() const &noexcept -> bsl::safe_uintmax const &
        {
            return m_bootstrap_ip;
        }

        /// <!-- description -->
        ///   @brief Sets the bootstrap IP for this extension. This should
        ///     be called by the syscall dispatcher as the result of a
        ///     syscall from the extension defining what IP the extension
        ///     would like to use for bootstrapping.
        ///
        /// <!-- inputs/outputs -->
        ///   @param ip the bootstrap IP to use
        ///
        constexpr void
        set_bootstrap_ip(bsl::safe_uintmax const &ip) &noexcept
        {
            m_bootstrap_ip = ip;
        }

        /// <!-- description -->
        ///   @brief Returns the VMExit IP for this extension.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the VMExit IP for this extension.
        ///
        [[nodiscard]] constexpr auto
        vmexit_ip() const &noexcept -> bsl::safe_uintmax const &
        {
            return m_vmexit_ip;
        }

        /// <!-- description -->
        ///   @brief Sets the VMExit IP for this extension. This should
        ///     be called by the syscall dispatcher as the result of a
        ///     syscall from the extension defining what IP the extension
        ///     would like to use for VMExits.
        ///
        /// <!-- inputs/outputs -->
        ///   @param ip the VMExit IP to use
        ///
        constexpr void
        set_vmexit_ip(bsl::safe_uintmax const &ip) &noexcept
        {
            m_vmexit_ip = ip;
        }

        /// <!-- description -->
        ///   @brief Returns the fast fail IP for this extension.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the fast fail IP for this extension.
        ///
        [[nodiscard]] constexpr auto
        fail_ip() const &noexcept -> bsl::safe_uintmax const &
        {
            return m_fail_ip;
        }

        /// <!-- description -->
        ///   @brief Sets the fast fail IP for this extension. This should
        ///     be called by the syscall dispatcher as the result of a
        ///     syscall from the extension defining what IP the extension
        ///     would like to use for fail callbacks.
        ///
        /// <!-- inputs/outputs -->
        ///   @param ip the fail IP to use
        ///
        constexpr void
        set_fail_ip(bsl::safe_uintmax const &ip) &noexcept
        {
            m_fail_ip = ip;
        }

        /// <!-- description -->
        ///   @brief Opens a handle and returns the resulting handle
        ///
        /// <!-- inputs/outputs -->
        ///   @return Opens a handle and returns the resulting handle
        ///
        [[nodiscard]] constexpr auto
        open_handle() &noexcept -> bsl::safe_uintmax
        {
            if (bsl::unlikely(m_handle)) {
                bsl::error() << "handle already opened\n" << bsl::here();
                return bsl::safe_uintmax::zero(true);
            }

            m_handle = bsl::to_umax(this->id()) + bsl::ONE_UMAX;
            return m_handle;
        }

        /// <!-- description -->
        ///   @brief Closes a previously opened handle
        ///
        constexpr void
        close_handle() &noexcept
        {
            m_handle = bsl::safe_uintmax::zero(true);
        }

        /// <!-- description -->
        ///   @brief Returns true if provided handle is valid
        ///
        /// <!-- inputs/outputs -->
        ///   @param handle the handle to verify
        ///   @return Returns true if provided handle is valid
        ///
        [[nodiscard]] constexpr auto
        is_handle_valid(bsl::safe_uintmax const &handle) const &noexcept -> bool
        {
            return handle == m_handle;
        }

        /// <!-- description -->
        ///   @brief Allocates a page and maps it into the extension's
        ///     address space.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns a page_t containing the virtual address and
        ///     physical address of the page. If an error occurs, this
        ///     function will return an invalid virtual and physical address.
        ///
        [[nodiscard]] constexpr auto
        alloc_page() &noexcept -> page_t
        {
            constexpr auto pool_addr{bsl::to_umax(EXT_PAGE_POOL_ADDR)};
            constexpr auto pool_size{bsl::to_umax(EXT_PAGE_POOL_SIZE)};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "ext_t not initialized\n" << bsl::here();
                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            if (bsl::unlikely((m_page_pool_crsr + PAGE_SIZE) > pool_size)) {
                bsl::error() << "the extension's page pool is out of memory"    // --
                             << bsl::endl                                       // --
                             << bsl::here();                                    // --

                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            auto const *const page{m_page_pool->template allocate<void>()};
            if (bsl::unlikely(nullptr == page)) {
                bsl::print<bsl::V>() << bsl::here();
                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            auto const page_phys{m_page_pool->virt_to_phys(page)};
            if (bsl::unlikely(!page_phys)) {
                bsl::print<bsl::V>() << bsl::here();
                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            auto const page_virt{m_page_pool_crsr + pool_addr};
            if (bsl::unlikely(!page_virt)) {
                bsl::print<bsl::V>() << bsl::here();
                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            auto const ret{m_main_rpt.map_page(
                page_virt, page_phys, MAP_PAGE_FLAG_READ | MAP_PAGE_FLAG_WRITE)};
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            m_page_pool_crsr += PAGE_SIZE;
            return {page_virt, page_phys};
        }

        /// <!-- description -->
        ///   @brief Frees a page that was mapped it into the extension's
        ///     address space.
        ///
        /// <!-- inputs/outputs -->
        ///   @param page_virt the virtual address to free
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        free_page(bsl::safe_uintmax const &page_virt) &noexcept -> bsl::errc_type
        {
            bsl::discard(page_virt);

            bsl::error() << "free_page is currently unsupported\n" << bsl::here();
            return bsl::errc_failure;
        }

        /// <!-- description -->
        ///   @brief Allocates a physically contiguous block of memory and maps
        ///     it into the extension's address space.
        ///
        /// <!-- inputs/outputs -->
        ///   @param size the total number of bytes to allocate
        ///   @return Returns a huge_t containing the virtual address and
        ///     physical address of the memory block. If an error occurs, this
        ///     function will return an invalid virtual and physical address.
        ///
        [[nodiscard]] constexpr auto
        alloc_huge(bsl::safe_uintmax const &size) &noexcept -> huge_t
        {
            constexpr auto pool_addr{bsl::to_umax(EXT_HUGE_POOL_ADDR)};
            constexpr auto pool_size{bsl::to_umax(EXT_HUGE_POOL_SIZE)};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "ext_t not initialized\n" << bsl::here();
                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            if (bsl::unlikely((m_huge_pool_crsr + size) > pool_size)) {
                bsl::error() << "the extension's huge pool is out of memory"    // --
                             << bsl::endl                                       // --
                             << bsl::here();                                    // --

                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            auto const *const huge{m_huge_pool->template allocate<void>(size)};
            if (bsl::unlikely(nullptr == huge)) {
                bsl::print<bsl::V>() << bsl::here();
                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            auto const heap_virt_to_return{m_heap_pool_crsr + pool_addr};
            if (bsl::unlikely(!heap_virt_to_return)) {
                bsl::print<bsl::V>() << bsl::here();
                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            auto const huge_phys_to_return{m_huge_pool->virt_to_phys(huge)};
            if (bsl::unlikely(!huge_phys_to_return)) {
                bsl::print<bsl::V>() << bsl::here();
                return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
            }

            auto const huge_view{bsl::as_bytes(huge, size)};
            for (bsl::safe_uintmax i{}; i < size; i += PAGE_SIZE) {
                auto const huge_phys{m_huge_pool->virt_to_phys(huge_view.at_if(i))};
                if (bsl::unlikely(!huge_phys)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
                }

                auto const huge_virt{m_huge_pool_crsr + pool_addr};
                if (bsl::unlikely(!huge_virt)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
                }

                auto const ret{m_main_rpt.map_page(
                    huge_virt, huge_phys, MAP_PAGE_FLAG_READ | MAP_PAGE_FLAG_WRITE)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return {bsl::safe_uintmax::zero(true), bsl::safe_uintmax::zero(true)};
                }

                m_huge_pool_crsr += PAGE_SIZE;
            }

            return {heap_virt_to_return, huge_phys_to_return};
        }

        /// <!-- description -->
        ///   @brief Frees a physically contiguous block of memory that was
        ///     mapped it into the extension's address space.
        ///
        /// <!-- inputs/outputs -->
        ///   @param huge_virt the virtual address to free
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        free_huge(bsl::safe_uintmax const &huge_virt) &noexcept -> bsl::errc_type
        {
            bsl::discard(huge_virt);

            bsl::error() << "free_huge is currently unsupported\n" << bsl::here();
            return bsl::errc_failure;
        }

        /// <!-- description -->
        ///   @brief Allocates heap memory and maps it into the extension's
        ///     address space.
        ///
        /// <!-- inputs/outputs -->
        ///   @param size the total number of bytes to allocate and add
        ///     to the heap.
        ///   @return On success, alloc_heap returns the previous address
        ///     virtual address of the heap. If an error occurs, this
        ///     function returns bsl::safe_uintmax::zero(true).
        ///
        [[nodiscard]] constexpr auto
        alloc_heap(bsl::safe_uintmax const &size) &noexcept -> bsl::safe_uintmax
        {
            constexpr auto pool_addr{bsl::to_umax(EXT_HEAP_POOL_ADDR)};
            constexpr auto pool_size{bsl::to_umax(EXT_HEAP_POOL_SIZE)};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "ext_t not initialized\n" << bsl::here();
                return bsl::safe_uintmax::zero(true);
            }

            if (bsl::unlikely(!size)) {
                bsl::error() << "invalid size: "    // --
                             << bsl::hex(size)      // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return bsl::safe_uintmax::zero(true);
            }

            auto pages{size / PAGE_SIZE};
            if ((size % PAGE_SIZE) != bsl::ZERO_UMAX) {
                ++pages;
            }
            else {
                bsl::touch();
            }

            if (bsl::unlikely((m_heap_pool_crsr + (pages * PAGE_SIZE)) > pool_size)) {
                bsl::error() << "the extension's heap pool is out of memory"    // --
                             << bsl::endl                                       // --
                             << bsl::here();                                    // --

                return bsl::safe_uintmax::zero(true);
            }

            auto const previous_heap_virt{m_heap_pool_crsr + pool_addr};
            if (bsl::unlikely(!previous_heap_virt)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::safe_uintmax::zero(true);
            }

            for (bsl::safe_uintmax i{}; i < pages; ++i) {
                auto const *const page{m_page_pool->template allocate<void>()};
                if (bsl::unlikely(nullptr == page)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::safe_uintmax::zero(true);
                }

                auto const page_phys{m_page_pool->virt_to_phys(page)};
                if (bsl::unlikely(!page_phys)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::safe_uintmax::zero(true);
                }

                auto const page_virt{m_heap_pool_crsr + pool_addr};
                if (bsl::unlikely(!page_virt)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::safe_uintmax::zero(true);
                }

                auto const ret{m_main_rpt.map_page(
                    page_virt, page_phys, MAP_PAGE_FLAG_READ | MAP_PAGE_FLAG_WRITE)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::safe_uintmax::zero(true);
                }

                m_heap_pool_crsr += PAGE_SIZE;
            }

            return previous_heap_virt;
        }

        /// <!-- description -->
        ///   @brief Converts a virtual address to a physical address given
        ///     the current set of page tables used by the extension.
        ///
        /// <!-- inputs/outputs -->
        ///   @param virt the virtual address to convert
        ///   @return Returns the physical address of the page.
        ///
        [[nodiscard]] constexpr auto
        virt_to_phys(bsl::safe_uintmax const &virt) &noexcept -> bsl::safe_uintmax
        {
            constexpr auto pool_addr{bsl::to_umax(EXT_PAGE_POOL_ADDR)};
            constexpr auto pool_size{bsl::to_umax(EXT_PAGE_POOL_SIZE)};

            constexpr auto min_pool_addr{pool_addr};
            constexpr auto max_pool_addr{pool_addr + (pool_size - bsl::ONE_UMAX)};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "ext_t not initialized\n" << bsl::here();
                return bsl::safe_uintmax::zero(true);
            }

            if (bsl::unlikely(virt < min_pool_addr)) {
                bsl::error() << "invalid virt: "    // --
                             << bsl::hex(virt)      // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return bsl::safe_uintmax::zero(true);
            }

            if (bsl::unlikely(virt > max_pool_addr)) {
                bsl::error() << "invalid virt: "    // --
                             << bsl::hex(virt)      // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return bsl::safe_uintmax::zero(true);
            }

            auto const phys{m_main_rpt.virt_to_phys(virt)};
            if (bsl::unlikely(!phys)) {
                bsl::print<bsl::V>() << bsl::here();
                return phys;
            }

            return phys;
        }

        /// <!-- description -->
        ///   @brief Maps a page into the direct map portion of the current
        ///     direct map root page table that is active.
        ///
        /// <!-- inputs/outputs -->
        ///   @param page_virt the virtual address to map the physical address too
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        map_page_direct(bsl::safe_uintmax const &page_virt) &noexcept -> bsl::errc_type
        {
            constexpr auto dm_addr{bsl::to_umax(EXT_DIRECT_MAP_ADDR)};
            constexpr auto dm_size{bsl::to_umax(EXT_DIRECT_MAP_SIZE)};

            constexpr auto min_dm_addr{dm_addr};
            constexpr auto max_dm_addr{dm_addr + (dm_size - bsl::ONE_UMAX)};

            /// TODO:
            /// - It is possible that 2 physical processors could attempt to
            ///   map the same physical address at the same time. Both would
            ///   generate a page fault. One would succeed at mapping the
            ///   address, and the other would fail. We should create our
            ///   own errc_type for the RPT so that it can tell this code
            ///   that the address is already mapped, as in this case, that
            ///   would not actually be an error.
            ///

            if (bsl::unlikely(page_virt < min_dm_addr)) {
                return bsl::errc_failure;
            }

            if (bsl::unlikely(page_virt > max_dm_addr)) {
                return bsl::errc_failure;
            }

            if (bsl::unlikely(nullptr == m_current_direct_map_rpt)) {
                bsl::error() << "map_page_direct only supported after bootstrapping"    // --
                             << bsl::endl                                               // --
                             << bsl::here();                                            // --

                return bsl::errc_failure;
            }

            auto const ret{m_current_direct_map_rpt->map_page_unaligned(
                page_virt, page_virt - min_dm_addr, MAP_PAGE_FLAG_READ | MAP_PAGE_FLAG_WRITE)};
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            return ret;
        }

        /// <!-- description -->
        ///   @brief Tells the extension that a VM was created so that it
        ///     can initialize it's VM specific resources.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the VMID of the VM that was created.
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        signal_vm_created(bsl::safe_uint16 const &vmid) noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!m_started)) {
                bsl::error() << "ext_t not started\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto *const rpt{m_direct_map_rpts.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == rpt)) {
                bsl::error() << "invalid vmid: "    // --
                             << bsl::hex(vmid)      // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->initialize_direct_map_rpt(*rpt))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Tells the extension that a VM was destroyed so that it
        ///     can release it's VM specific resources.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the VMID of the VM that was destroyed.
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        signal_vm_destroyed(bsl::safe_uint16 const &vmid) noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!m_started)) {
                bsl::error() << "ext_t not started\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto *const rpt{m_direct_map_rpts.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == rpt)) {
                bsl::error() << "invalid vmid: "    // --
                             << bsl::hex(vmid)      // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_current_direct_map_rpt == rpt)) {
                bsl::error() << "attempt to destory the active VM was blocked"    // --
                             << bsl::hex(vmid)                                    // --
                             << bsl::endl                                         // --
                             << bsl::here();                                      // --

                return bsl::errc_failure;
            }

            rpt->release();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Sets the active VM for this extension. This will cause
        ///     the extension to set VM specific resources up including the
        ///     direct map.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid the VMID of the VM to set as active
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_active_vm(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!m_started)) {
                bsl::error() << "ext_t not started\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto *const rpt{m_direct_map_rpts.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == rpt)) {
                bsl::error() << "invalid vmid: "    // --
                             << bsl::hex(vmid)      // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return bsl::errc_failure;
            }

            if (tls.ext == this) {
                if (bsl::unlikely(!rpt->activate())) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                bsl::touch();
            }

            m_current_direct_map_rpt = rpt;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Starts the extension by executing it's _start entry point.
        ///     If the extension has not been initialized, this function will
        ///     return bsl::errc_success.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        start(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            auto const arg{bsl::to_umax(syscall::BF_ALL_SPECS_SUPPORTED_VAL)};
            auto const ret{this->execute(tls, m_main_ip, m_main_rpt, arg)};
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_started = true;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Bootstraps the extension by executing it's bootstrap entry
        ///     point. If the extension has not been initialized, this function
        ///     will return bsl::errc_success.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        bootstrap(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            auto const arg{bsl::to_umax(tls.ppid())};
            auto const ret{this->execute(tls, m_bootstrap_ip, m_main_rpt, arg)};
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Bootstraps the extension by executing it's bootstrap entry
        ///     point. If the extension has not been initialized, this function
        ///     will return bsl::errc_success.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param exit_reason the reason for the VMExit
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        vmexit(TLS_CONCEPT &tls, bsl::safe_uintmax const &exit_reason) &noexcept -> bsl::errc_type
        {
            bsl::safe_uintmax arg0{bsl::to_umax(tls.active_vpsid)};
            bsl::safe_uintmax arg1{exit_reason};

            if (bsl::unlikely(nullptr == m_current_direct_map_rpt)) {
                bsl::error() << "an active VM was never set"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            auto const ret{this->execute(tls, m_vmexit_ip, *m_current_direct_map_rpt, arg0, arg1)};
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            return ret;
        }

        /// <!-- description -->
        ///   @brief Bootstraps the extension by executing it's bootstrap entry
        ///     point. If the extension has not been initialized, this function
        ///     will return bsl::errc_success.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        fail(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            bsl::safe_uintmax arg0{syscall::BF_STATUS_FAILURE_UNKNOWN};

            if (nullptr == m_current_direct_map_rpt) {
                auto const ret{this->execute(tls, m_fail_ip, m_main_rpt, arg0)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            auto const ret{this->execute(tls, m_fail_ip, *m_current_direct_map_rpt, arg0)};
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            return ret;
        }
    };
}

#endif
