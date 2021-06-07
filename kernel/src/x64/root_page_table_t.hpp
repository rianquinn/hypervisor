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

#ifndef ROOT_PAGE_TABLE_T_HPP
#define ROOT_PAGE_TABLE_T_HPP

#include "../lock_guard_t.hpp"
#include "../spinlock_t.hpp"

#include <allocate_tags.hpp>
#include <map_page_flags.hpp>
#include <pdpt_t.hpp>
#include <pdpte_t.hpp>
#include <pdt_t.hpp>
#include <pdte_t.hpp>
#include <pml4t_t.hpp>
#include <pml4te_t.hpp>
#include <pt_t.hpp>
#include <pte_t.hpp>
#include <tls_t.hpp>

#include <bsl/convert.hpp>
#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/fmt.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/touch.hpp>
#include <bsl/unlikely.hpp>
#include <bsl/unlikely_assert.hpp>

namespace mk
{
    /// @class mk::root_page_table_t
    ///
    /// <!-- description -->
    ///   @brief Implements the root pages tables used by the microkernel
    ///     for mapping extension memory.
    ///
    /// <!-- template parameters -->
    ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
    ///   @tparam HUGE_POOL_CONCEPT defines the type of huge pool to use
    ///   @tparam PAGE_SIZE defines the size of a page
    ///   @tparam PAGE_SHIFT defines number of bits in a page
    ///
    template<
        typename INTRINSIC_CONCEPT,
        typename PAGE_POOL_CONCEPT,
        typename HUGE_POOL_CONCEPT,
        bsl::uintmax PAGE_SIZE,
        bsl::uintmax PAGE_SHIFT>
    class root_page_table_t final
    {
        /// @brief stores true if initialized() has been executed
        bool m_initialized{};
        /// @brief stores a reference to the intrinsics to use
        INTRINSIC_CONCEPT *m_intrinsic{};
        /// @brief stores a reference to the page pool to use
        PAGE_POOL_CONCEPT *m_page_pool{};
        /// @brief stores a reference to the huge pool to use
        HUGE_POOL_CONCEPT *m_huge_pool{};
        /// @brief stores a pointer to the pml4t
        pml4t_t *m_pml4t{};
        /// @brief stores the physical address of the pml4t
        bsl::safe_uintmax m_pml4t_phys{bsl::safe_uintmax::zero(true)};
        /// @brief safe guards operations on the RPT.
        mutable spinlock_t m_lock{};

        /// <!-- description -->
        ///   @brief Returns the index of the last entry present in a page
        ///     table.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TABLE_CONCEPT the type of page table to search
        ///   @param table the page table to search
        ///   @return Returns the index of the last entry present in a page
        ///     table.
        ///
        template<typename TABLE_CONCEPT>
        [[nodiscard]] constexpr auto
        get_last_index(TABLE_CONCEPT const *const table) const noexcept -> bsl::safe_uintmax
        {
            bsl::safe_uintmax last_index{};
            for (auto const elem : table->entries) {
                if (bsl::ZERO_UMAX == elem.data->p) {
                    continue;
                }

                last_index = elem.index;
            }

            return last_index;
        }

        /// <!-- description -->
        ///   @brief Given index and the index of the last
        ///     present entry in the page table being dumped, this function
        ///     will output a decoration and the index.
        ///
        /// <!-- inputs/outputs -->
        ///   @param index the current index of the entry being dumped
        ///   @param last_index the index of the last present entry in the page
        ///     table being dumped.
        ///
        constexpr void
        output_decoration_and_index(
            bsl::safe_uintmax const &index, bsl::safe_uintmax const &last_index) const noexcept
        {
            bsl::print() << bsl::rst;

            if (index != last_index) {
                bsl::print() << "├── ";
            }
            else {
                bsl::print() << "└── ";
            }

            bsl::print() << "[" << bsl::ylw << bsl::fmt{"#05x", index} << bsl::rst << "] ";
        }

        /// <!-- description -->
        ///   @brief Given whether or not the page table
        ///     entry is the last entry in the table, this function will
        ///     either output whtspace, or a | and shitespace.
        ///
        /// <!-- inputs/outputs -->
        ///   @param is_last_index true if the entry being outputted is the
        ///     last index in the table.
        ///
        constexpr void
        output_spacing(bool const is_last_index) const noexcept
        {
            bsl::print() << bsl::rst;

            if (!is_last_index) {
                bsl::print() << "│   ";
            }
            else {
                bsl::print() << "    ";
            }
        }

        /// <!-- description -->
        ///   @brief Given a page table entry, this
        ///     function outputs the flags associated with the entry
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam ENTRY_CONCEPT the type of page table entry to output
        ///   @param entry the page table entry to output
        ///
        template<typename ENTRY_CONCEPT>
        constexpr void
        output_entry_and_flags(ENTRY_CONCEPT const *const entry) const noexcept
        {
            bool add_comma{};

            bsl::print() << bsl::hex(
                *static_cast<bsl::uint64 const *>(static_cast<void const *>(entry)));
            bsl::print() << bsl::rst << " (";

            if (bsl::ZERO_UMAX != entry->rw) {
                bsl::print() << bsl::grn << 'W';
                add_comma = true;
            }
            else {
                bsl::touch();
            }

            if (bsl::ZERO_UMAX != entry->us) {
                if (add_comma) {
                    bsl::print() << bsl::rst << ", ";
                }
                else {
                    bsl::touch();
                }

                bsl::print() << bsl::grn << 'U';
                add_comma = true;
            }
            else {
                bsl::touch();
            }

            if (bsl::ZERO_UMAX != entry->nx) {
                if (add_comma) {
                    bsl::print() << bsl::rst << ", ";
                }
                else {
                    bsl::touch();
                }

                bsl::print() << bsl::grn << "NX";
                add_comma = true;
            }
            else {
                bsl::touch();
            }

            if constexpr (bsl::is_same<ENTRY_CONCEPT, loader::pml4te_t>::value) {
                if (bsl::ZERO_UMAX != entry->alias) {
                    if (add_comma) {
                        bsl::print() << bsl::rst << ", ";
                    }
                    else {
                        bsl::touch();
                    }

                    bsl::print() << bsl::grn << "alias";
                    add_comma = true;
                }
                else {
                    bsl::touch();
                }
            }

            if constexpr (bsl::is_same<ENTRY_CONCEPT, loader::pte_t>::value) {
                if (add_comma) {
                    bsl::print() << bsl::rst << ", ";
                }
                else {
                    bsl::touch();
                }

                switch (entry->auto_release) {
                    case MAP_PAGE_AUTO_RELEASE_ALLOC_PAGE.get(): {
                        bsl::print() << bsl::grn << "auto_release_alloc_page";
                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_ALLOC_HUGE.get(): {
                        bsl::print() << bsl::grn << "auto_release_alloc_huge";
                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_ALLOC_HEAP.get(): {
                        bsl::print() << bsl::grn << "auto_release_alloc_heap";
                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_STACK.get(): {
                        bsl::print() << bsl::grn << "auto_release_stack";
                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_TLS.get(): {
                        bsl::print() << bsl::grn << "auto_release_tls";
                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_ELF.get(): {
                        bsl::print() << bsl::grn << "auto_release_elf";
                        break;
                    }

                    default: {
                        bsl::print() << bsl::grn << "manual";
                        break;
                    }
                }

                add_comma = true;
            }

            bsl::print() << bsl::rst << ')';
            bsl::print() << bsl::rst << bsl::endl;
        }

        /// <!-- description -->
        ///   @brief Returns the page-map level-4 (PML4T) offset given a
        ///     virtual address.
        ///
        /// <!-- inputs/outputs -->
        ///   @param virt the virtual address to get the PML4T offset from.
        ///   @return the PML4T offset from the virtual address
        ///
        [[nodiscard]] static constexpr auto
        pml4to(bsl::safe_uintmax const &virt) noexcept -> bsl::safe_uintmax
        {
            constexpr bsl::safe_uintmax mask{bsl::to_umax(0x1FF)};
            constexpr bsl::safe_uintmax shift{bsl::to_umax(39)};
            return (virt >> shift) & mask;
        }

        /// <!-- description -->
        ///   @brief Dumps the provided pml4t_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param pml4t the pml4t_t to dump
        ///
        constexpr void
        dump_pml4t(pml4t_t const *const pml4t) const noexcept
        {
            bsl::safe_uintmax const last_index{this->get_last_index(pml4t)};

            bsl::print() << bsl::blu << bsl::hex(m_pml4t_phys);
            bsl::print() << bsl::rst << bsl::endl;

            for (auto const elem : pml4t->entries) {
                if (bsl::ZERO_UMAX == elem.data->p) {
                    continue;
                }

                this->output_decoration_and_index(elem.index, last_index);

                if (bsl::ZERO_UMAX != elem.data->us) {
                    bsl::print() << bsl::blu;
                    this->output_entry_and_flags(elem.data);
                }
                else {
                    bsl::print() << bsl::blk;
                    this->output_entry_and_flags(elem.data);
                }

                if (bsl::ZERO_UMAX != elem.data->us) {
                    this->dump_pdpt(this->get_pdpt(elem.data), elem.index == last_index);
                }
                else {
                    bsl::touch();
                }
            }
        }

        /// <!-- description -->
        ///   @brief Adds a pdpt_t to the provided pml4te_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param pml4te the pml4te_t to add a pdpt_t too
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        add_pdpt(tls_t &tls, loader::pml4te_t *const pml4te) noexcept -> bsl::errc_type
        {
            auto const *const table{m_page_pool->template allocate<void>(tls, ALLOCATE_TAG_PDPTS)};
            if (bsl::unlikely(nullptr == table)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            auto const table_phys{m_page_pool->virt_to_phys(table)};
            if (bsl::unlikely_assert(!table_phys)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            pml4te->phys = (table_phys >> PAGE_SHIFT).get();
            pml4te->p = bsl::ONE_UMAX.get();
            pml4te->rw = bsl::ONE_UMAX.get();
            pml4te->us = bsl::ONE_UMAX.get();

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Adds a pdpt_t to the provided pml4te_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param pml4te the pml4te_t to add a pdpt_t too
        ///
        constexpr void
        remove_pdpt(tls_t &tls, loader::pml4te_t *const pml4te) noexcept
        {
            for (auto const elem : get_pdpt(pml4te)->entries) {
                if (elem.data->p != bsl::ZERO_UMAX) {
                    this->remove_pdt(tls, elem.data);
                }
                else {
                    bsl::touch();
                }
            }

            m_page_pool->deallocate(tls, get_pdpt(pml4te), ALLOCATE_TAG_PDPTS);
        }

        /// <!-- description -->
        ///   @brief Returns the pdpt_t associated with the provided
        ///     pml4te_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pml4te the pml4te_t to get the pdpt_t from
        ///   @return A pointer to the requested pdpt_t
        ///
        [[nodiscard]] constexpr auto
        get_pdpt(loader::pml4te_t *const pml4te) noexcept -> pdpt_t *
        {
            bsl::safe_uintmax entry_phys{pml4te->phys};
            entry_phys <<= PAGE_SHIFT;

            return m_page_pool->template phys_to_virt<pdpt_t>(entry_phys);
        }

        /// <!-- description -->
        ///   @brief Returns the pdpt_t associated with the provided
        ///     pml4te_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pml4te the pml4te_t to get the pdpt_t from
        ///   @return A pointer to the requested pdpt_t
        ///
        [[nodiscard]] constexpr auto
        get_pdpt(loader::pml4te_t const *const pml4te) const noexcept -> pdpt_t const *
        {
            bsl::safe_uintmax entry_phys{pml4te->phys};
            entry_phys <<= PAGE_SHIFT;

            return m_page_pool->template phys_to_virt<pdpt_t const>(entry_phys);
        }

        /// <!-- description -->
        ///   @brief Returns the page-directory-pointer table (PDPT) offset
        ///     given a virtual address.
        ///
        /// <!-- inputs/outputs -->
        ///   @param virt the virtual address to get the PDPT offset from.
        ///   @return the PDPT offset from the virtual address
        ///
        [[nodiscard]] static constexpr auto
        pdpto(bsl::safe_uintmax const &virt) noexcept -> bsl::safe_uintmax
        {
            constexpr bsl::safe_uintmax mask{bsl::to_umax(0x1FF)};
            constexpr bsl::safe_uintmax shift{bsl::to_umax(30)};
            return (virt >> shift) & mask;
        }

        /// <!-- description -->
        ///   @brief Dumps the provided pdpt_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param pdpt the pdpt_t to dump
        ///   @param is_pml4te_last_index true if the parent pml4te was the
        ///     last pml4te in the table
        ///
        constexpr void
        dump_pdpt(pdpt_t const *const pdpt, bool is_pml4te_last_index) const noexcept
        {
            bsl::safe_uintmax const last_index{this->get_last_index(pdpt)};

            for (auto const elem : pdpt->entries) {
                if (bsl::ZERO_UMAX == elem.data->p) {
                    continue;
                }

                this->output_spacing(is_pml4te_last_index);
                this->output_decoration_and_index(elem.index, last_index);

                bsl::print() << bsl::blu;
                this->output_entry_and_flags(elem.data);

                this->dump_pdt(
                    this->get_pdt(elem.data), is_pml4te_last_index, elem.index == last_index);
            }
        }

        /// <!-- description -->
        ///   @brief Adds a pdt_t to the provided pdpte_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param pdpte the pdpte_t to add a pdt_t too
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        add_pdt(tls_t &tls, loader::pdpte_t *const pdpte) noexcept -> bsl::errc_type
        {
            auto const *const table{m_page_pool->template allocate<void>(tls, ALLOCATE_TAG_PDTS)};
            if (bsl::unlikely(nullptr == table)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            auto const table_phys{m_page_pool->virt_to_phys(table)};
            if (bsl::unlikely_assert(!table_phys)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            pdpte->phys = (table_phys >> PAGE_SHIFT).get();
            pdpte->p = bsl::ONE_UMAX.get();
            pdpte->rw = bsl::ONE_UMAX.get();
            pdpte->us = bsl::ONE_UMAX.get();

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Adds a pdt_t to the provided pdpte_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param pdpte the pdpte_t to add a pdt_t too
        ///
        constexpr void
        remove_pdt(tls_t &tls, loader::pdpte_t *const pdpte) noexcept
        {
            for (auto const elem : get_pdt(pdpte)->entries) {
                if (elem.data->p != bsl::ZERO_UMAX) {
                    this->remove_pt(tls, elem.data);
                }
                else {
                    bsl::touch();
                }
            }

            m_page_pool->deallocate(tls, get_pdt(pdpte), ALLOCATE_TAG_PDTS);
        }

        /// <!-- description -->
        ///   @brief Returns the pdt_t associated with the provided
        ///     pdpte_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pdpte the pdpte_t to get the pdt_t from
        ///   @return A pointer to the requested pdt_t
        ///
        [[nodiscard]] constexpr auto
        get_pdt(loader::pdpte_t *const pdpte) noexcept -> pdt_t *
        {
            bsl::safe_uintmax entry_phys{pdpte->phys};
            entry_phys <<= PAGE_SHIFT;

            return m_page_pool->template phys_to_virt<pdt_t>(entry_phys);
        }

        /// <!-- description -->
        ///   @brief Returns the pdt_t associated with the provided
        ///     pdpte_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pdpte the pdpte_t to get the pdt_t from
        ///   @return A pointer to the requested pdt_t
        ///
        [[nodiscard]] constexpr auto
        get_pdt(loader::pdpte_t const *const pdpte) const noexcept -> pdt_t const *
        {
            bsl::safe_uintmax entry_phys{pdpte->phys};
            entry_phys <<= PAGE_SHIFT;

            return m_page_pool->template phys_to_virt<pdt_t const>(entry_phys);
        }

        /// <!-- description -->
        ///   @brief Returns the page-directory table (PDT) offset given a
        ///     virtual address.
        ///
        /// <!-- inputs/outputs -->
        ///   @param virt the virtual address to get the PDT offset from.
        ///   @return the PDT offset from the virtual address
        ///
        [[nodiscard]] static constexpr auto
        pdto(bsl::safe_uintmax const &virt) noexcept -> bsl::safe_uintmax
        {
            constexpr bsl::safe_uintmax mask{bsl::to_umax(0x1FF)};
            constexpr bsl::safe_uintmax shift{bsl::to_umax(21)};
            return (virt >> shift) & mask;
        }

        /// <!-- description -->
        ///   @brief Dumps the provided pdt_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param pdt the pdt_t to dump
        ///   @param is_pml4te_last_index true if the parent pml4te was the
        ///     last pml4te in the table
        ///   @param is_pdpte_last_index true if the parent pdpte was the
        ///     last pdpte in the table
        ///
        constexpr void
        dump_pdt(pdt_t const *const pdt, bool is_pml4te_last_index, bool is_pdpte_last_index)
            const noexcept
        {
            bsl::safe_uintmax const last_index{this->get_last_index(pdt)};

            for (auto const elem : pdt->entries) {
                if (bsl::ZERO_UMAX == elem.data->p) {
                    continue;
                }

                this->output_spacing(is_pml4te_last_index);
                this->output_spacing(is_pdpte_last_index);
                this->output_decoration_and_index(elem.index, last_index);

                bsl::print() << bsl::blu;
                this->output_entry_and_flags(elem.data);

                this->dump_pt(
                    this->get_pt(elem.data),
                    is_pml4te_last_index,
                    is_pdpte_last_index,
                    elem.index == last_index);
            }
        }

        /// <!-- description -->
        ///   @brief Adds a pt_t to the provided pdte_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param pdte the pdte_t to add a pt_t too
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        add_pt(tls_t &tls, loader::pdte_t *const pdte) noexcept -> bsl::errc_type
        {
            auto const *const table{m_page_pool->template allocate<void>(tls, ALLOCATE_TAG_PTS)};
            if (bsl::unlikely(nullptr == table)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            auto const table_phys{m_page_pool->virt_to_phys(table)};
            if (bsl::unlikely_assert(!table_phys)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            pdte->phys = (table_phys >> PAGE_SHIFT).get();
            pdte->p = bsl::ONE_UMAX.get();
            pdte->rw = bsl::ONE_UMAX.get();
            pdte->us = bsl::ONE_UMAX.get();

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Adds a pt_t to the provided pdte_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param pdte the pdte_t to add a pt_t too
        ///
        constexpr void
        remove_pt(tls_t &tls, loader::pdte_t *const pdte) noexcept
        {
            for (auto const elem : get_pt(pdte)->entries) {
                if (elem.data->p == bsl::ZERO_UMAX) {
                    continue;
                }

                switch (elem.data->auto_release) {
                    case MAP_PAGE_NO_AUTO_RELEASE.get(): {
                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_ALLOC_PAGE.get(): {
                        m_page_pool->deallocate(
                            tls,
                            this->pte_from_page_pool_to_virt(elem.data),
                            ALLOCATE_TAG_BF_MEM_OP_ALLOC_PAGE);

                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_ALLOC_HUGE.get(): {
                        m_huge_pool->deallocate(tls, this->pte_from_huge_pool_to_virt(elem.data));
                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_ALLOC_HEAP.get(): {
                        m_page_pool->deallocate(
                            tls,
                            this->pte_from_page_pool_to_virt(elem.data),
                            ALLOCATE_TAG_BF_MEM_OP_ALLOC_HEAP);

                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_STACK.get(): {
                        m_page_pool->deallocate(
                            tls,
                            this->pte_from_page_pool_to_virt(elem.data),
                            ALLOCATE_TAG_EXT_STACK);

                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_TLS.get(): {
                        m_page_pool->deallocate(
                            tls, this->pte_from_page_pool_to_virt(elem.data), ALLOCATE_TAG_EXT_TLS);

                        break;
                    }

                    case MAP_PAGE_AUTO_RELEASE_ELF.get(): {
                        m_page_pool->deallocate(
                            tls, this->pte_from_page_pool_to_virt(elem.data), ALLOCATE_TAG_EXT_ELF);

                        break;
                    }

                    default: {
                        bsl::error() << "uknown tag\n" << bsl::here();
                        break;
                    }
                }
            }

            m_page_pool->deallocate(tls, get_pt(pdte), ALLOCATE_TAG_PTS);
        }

        /// <!-- description -->
        ///   @brief Returns the pt_t associated with the provided
        ///     pdte_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pdte the pdte_t to get the pt_t from
        ///   @return A pointer to the requested pt_t
        ///
        [[nodiscard]] constexpr auto
        get_pt(loader::pdte_t *const pdte) noexcept -> pt_t *
        {
            bsl::safe_uintmax entry_phys{pdte->phys};
            entry_phys <<= PAGE_SHIFT;

            return m_page_pool->template phys_to_virt<pt_t>(entry_phys);
        }

        /// <!-- description -->
        ///   @brief Returns the pt_t associated with the provided
        ///     pdte_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pdte the pdte_t to get the pt_t from
        ///   @return A pointer to the requested pt_t
        ///
        [[nodiscard]] constexpr auto
        get_pt(loader::pdte_t const *const pdte) const noexcept -> pt_t const *
        {
            bsl::safe_uintmax entry_phys{pdte->phys};
            entry_phys <<= PAGE_SHIFT;

            return m_page_pool->template phys_to_virt<pt_t const>(entry_phys);
        }

        /// <!-- description -->
        ///   @brief Returns the page-table (PT) offset given a
        ///     virtual address.
        ///
        /// <!-- inputs/outputs -->
        ///   @param virt the virtual address to get the PT offset from.
        ///   @return the PT offset from the virtual address
        ///
        [[nodiscard]] static constexpr auto
        pto(bsl::safe_uintmax const &virt) noexcept -> bsl::safe_uintmax
        {
            constexpr bsl::safe_uintmax mask{bsl::to_umax(0x1FF)};
            constexpr bsl::safe_uintmax shift{bsl::to_umax(12)};
            return (virt >> shift) & mask;
        }

        /// <!-- description -->
        ///   @brief Dumps the provided pt_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param pt the pt_t to dump
        ///   @param is_pml4te_last_index true if the parent pml4te was the
        ///     last pml4te in the table
        ///   @param is_pdpte_last_index true if the parent pdpte was the
        ///     last pdpte in the table
        ///   @param is_pdte_last_index true if the parent pdte was the
        ///     last pdte in the table
        ///
        constexpr void
        dump_pt(
            pt_t const *const pt,
            bool is_pml4te_last_index,
            bool is_pdpte_last_index,
            bool is_pdte_last_index) const noexcept
        {
            bsl::safe_uintmax const last_index{this->get_last_index(pt)};

            for (auto const elem : pt->entries) {
                if (bsl::ZERO_UMAX == elem.data->p) {
                    continue;
                }

                this->output_spacing(is_pml4te_last_index);
                this->output_spacing(is_pdpte_last_index);
                this->output_spacing(is_pdte_last_index);
                this->output_decoration_and_index(elem.index, last_index);

                bsl::print() << bsl::rst;
                this->output_entry_and_flags(elem.data);
            }
        }

        /// <!-- description -->
        ///   @brief Returns the virtual address associated with a specific
        ///     pte that was allocated using the page pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pte the pte_t to convert
        ///   @return Returns the virtual address associated with a specific
        ///     pte that was allocated using the page pool.
        ///
        [[nodiscard]] constexpr auto
        pte_from_page_pool_to_virt(loader::pte_t *const pte) noexcept -> void *
        {
            bsl::safe_uintmax entry_phys{pte->phys};
            entry_phys <<= PAGE_SHIFT;

            return m_page_pool->template phys_to_virt<void>(entry_phys);
        }

        /// <!-- description -->
        ///   @brief Returns the virtual address associated with a specific
        ///     pte that was allocated using the huge pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pte the pte_t to convert
        ///   @return Returns the virtual address associated with a specific
        ///     pte that was allocated using the huge pool.
        ///
        [[nodiscard]] constexpr auto
        pte_from_huge_pool_to_virt(loader::pte_t *const pte) noexcept -> void *
        {
            bsl::safe_uintmax entry_phys{pte->phys};
            entry_phys <<= PAGE_SHIFT;

            return m_huge_pool->template phys_to_virt<void>(entry_phys);
        }

        /// <!-- description -->
        ///   @brief Returns the page aligned version of the addr
        ///
        /// <!-- inputs/outputs -->
        ///   @param addr the address to query
        ///   @return Returns the page aligned version of the addr
        ///
        [[nodiscard]] static constexpr auto
        page_aligned(bsl::safe_uintmax const &addr) noexcept -> bsl::safe_uintmax
        {
            return (addr & ~(PAGE_SIZE - bsl::ONE_UMAX));
        }

        /// <!-- description -->
        ///   @brief Returns true if the provided address is page aligned
        ///
        /// <!-- inputs/outputs -->
        ///   @param addr the address to query
        ///   @return Returns true if the provided address is page aligned
        ///
        [[nodiscard]] static constexpr auto
        is_page_aligned(bsl::safe_uintmax const &addr) noexcept -> bool
        {
            return (addr & (PAGE_SIZE - bsl::ONE_UMAX)) == bsl::ZERO_UMAX;
        }

        /// <!-- description -->
        ///   @brief Allocates a page from the provided page pool and maps it
        ///     into the root page table being managed by this class The page
        ///     is marked as "auto release", meaning when this root page table
        ///     is released, the pages allocated by this function will
        ///     automatically be deallocated and put back into the provided
        ///     page pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param page_virt the virtual address to map the allocated
        ///     page to
        ///   @param page_flags defines how memory should be mapped
        ///   @param auto_release defines what auto release tag to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        allocate_page(
            tls_t &tls,
            bsl::safe_uintmax const &page_virt,
            bsl::safe_uintmax const &page_flags,
            bsl::safe_int32 const &auto_release) &noexcept -> void *
        {
            bsl::errc_type ret{};

            void *page{};
            switch (auto_release.get()) {
                case MAP_PAGE_AUTO_RELEASE_STACK.get(): {
                    page = m_page_pool->template allocate<void>(tls, ALLOCATE_TAG_EXT_STACK);
                    break;
                }

                case MAP_PAGE_AUTO_RELEASE_TLS.get(): {
                    page = m_page_pool->template allocate<void>(tls, ALLOCATE_TAG_EXT_TLS);
                    break;
                }

                case MAP_PAGE_AUTO_RELEASE_ELF.get(): {
                    page = m_page_pool->template allocate<void>(tls, ALLOCATE_TAG_EXT_ELF);
                    break;
                }

                default: {
                    bsl::error() << "unknown tag\n" << bsl::here();
                    break;
                }
            }

            if (bsl::unlikely(nullptr == page)) {
                bsl::print<bsl::V>() << bsl::here();
                return nullptr;
            }

            auto const page_phys{m_page_pool->virt_to_phys(page)};
            if (bsl::unlikely_assert(!page_phys)) {
                bsl::error() << "physical address is invalid: "    // --
                             << bsl::hex(page_phys)                // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return nullptr;
            }

            ret = this->map_page(tls, page_virt, page_phys, page_flags, auto_release);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return nullptr;
            }

            return page;
        }

        /// <!-- description -->
        ///   @brief Releases the memory allocated for tables
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///
        constexpr void
        release_tables(tls_t &tls) &noexcept
        {
            if (bsl::unlikely(nullptr == m_pml4t)) {
                return;
            }

            if (bsl::unlikely(nullptr == m_page_pool)) {
                return;
            }

            if (bsl::unlikely(nullptr == m_huge_pool)) {
                return;
            }

            for (auto const elem : m_pml4t->entries) {
                if (elem.data->p == bsl::ZERO_UMAX) {
                    continue;
                }

                if (elem.data->alias != bsl::ZERO_UMAX) {
                    continue;
                }

                this->remove_pdpt(tls, elem.data);
            }

            m_page_pool->deallocate(tls, m_pml4t, ALLOCATE_TAG_PML4TS);
            m_pml4t = {};
            m_pml4t_phys = bsl::safe_uintmax::zero(true);
        }

    public:
        /// @brief an alias for INTRINSIC_CONCEPT
        using intrinsic_type = INTRINSIC_CONCEPT;
        /// @brief an alias for PAGE_POOL_CONCEPT
        using page_pool_type = PAGE_POOL_CONCEPT;
        /// @brief an alias for HUGE_POOL_CONCEPT
        using huge_pool_type = HUGE_POOL_CONCEPT;

        /// <!-- description -->
        ///   @brief Initializes this root_page_table_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param page_pool the page pool to use
        ///   @param huge_pool the huge pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(
            tls_t &tls,
            INTRINSIC_CONCEPT *const intrinsic,
            PAGE_POOL_CONCEPT *const page_pool,
            HUGE_POOL_CONCEPT *const huge_pool) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely_assert(m_initialized)) {
                bsl::error() << "root_page_table_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[this, &tls]() noexcept -> void {
                this->release(tls);
            }};

            m_intrinsic = intrinsic;
            if (bsl::unlikely_assert(nullptr == intrinsic)) {
                bsl::error() << "invalid intrinsic\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_page_pool = page_pool;
            if (bsl::unlikely_assert(nullptr == page_pool)) {
                bsl::error() << "invalid page_pool\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_huge_pool = huge_pool;
            if (bsl::unlikely_assert(nullptr == huge_pool)) {
                bsl::error() << "invalid huge_pool\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_pml4t = m_page_pool->template allocate<pml4t_t>(tls, ALLOCATE_TAG_PML4TS);
            if (bsl::unlikely(nullptr == m_pml4t)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_pml4t_phys = m_page_pool->virt_to_phys(m_pml4t);
            if (bsl::unlikely_assert(!m_pml4t_phys)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            release_on_error.ignore();
            m_initialized = true;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Releases all of the resources used by the RPT.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///
        constexpr void
        release(tls_t &tls) &noexcept
        {
            lock_guard_t lock{tls, m_lock};

            this->release_tables(tls);

            m_huge_pool = {};
            m_page_pool = {};
            m_intrinsic = {};
            m_initialized = false;
        }

        /// <!-- description -->
        ///   @brief Returns true if this RPT is initialized.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this RPT is initialized.
        ///
        [[nodiscard]] constexpr auto
        is_initialized() const &noexcept -> bool
        {
            return m_initialized;
        }

        /// <!-- description -->
        ///   @brief Sets the current root page table to this root page table.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        activate() const &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely_assert(!m_initialized)) {
                bsl::error() << "root_page_table_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_intrinsic->set_cr3(m_pml4t_phys);
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Given a root page table, the pml4te_t enties are aliased
        ///     into this page table, allowing software using this root page
        ///     table to access the memory mapped into the provided root page
        ///     table. The additions are aliases only, meaning when this root
        ///     page table loses scope, aliased entries added by this function
        ///     are not returned back to the page pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param rpt the root page table to add aliases to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        add_tables(tls_t &tls, void const *const rpt) &noexcept -> bsl::errc_type
        {
            lock_guard_t lock{tls, m_lock};

            if (bsl::unlikely_assert(!m_initialized)) {
                bsl::error() << "root_page_table_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto const *const pml4t{static_cast<pml4t_t const *>(rpt)};
            if (bsl::unlikely_assert(nullptr == pml4t)) {
                bsl::error() << "invalid rpt\n" << bsl::here();
                return bsl::errc_failure;
            }

            for (auto const elem : pml4t->entries) {
                if (elem.data->p != bsl::ZERO_UMAX) {
                    auto *const pml4e_dst{m_pml4t->entries.at_if(elem.index)};

                    *pml4e_dst = *elem.data;
                    pml4e_dst->alias = bsl::ONE_UMAX.get();
                }
                else {
                    bsl::touch();
                }
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Given a root page table, the pml4te_t enties are aliased
        ///     into this page table, allowing software using this root page
        ///     table to access the memory mapped into the provided root page
        ///     table. The additions are aliases only, meaning when this root
        ///     page table loses scope, aliased entries added by this function
        ///     are not returned back to the page pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param rpt the root page table to add aliases to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        add_tables(tls_t &tls, root_page_table_t const &rpt) &noexcept -> bsl::errc_type
        {
            return this->add_tables(tls, rpt.m_pml4t);
        }

        /// <!-- description -->
        ///   @brief Maps a page into the root page table being managed
        ///     by this class.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param page_virt the virtual address to map the physical address
        ///     too.
        ///   @param page_phys the physical address to map.
        ///   @param page_flags defines how memory should be mapped
        ///   @param auto_release defines what auto release tag to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        map_page(
            tls_t &tls,
            bsl::safe_uintmax const &page_virt,
            bsl::safe_uintmax const &page_phys,
            bsl::safe_uintmax const &page_flags,
            bsl::safe_int32 const &auto_release) &noexcept -> bsl::errc_type
        {
            lock_guard_t lock{tls, m_lock};

            if (bsl::unlikely_assert(!m_initialized)) {
                bsl::error() << "root_page_table_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(page_virt.is_zero())) {
                bsl::error() << "virtual address is invalid: "    // --
                             << bsl::hex(page_virt)               // --
                             << bsl::endl                         // --
                             << bsl::here();                      // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(!this->is_page_aligned(page_virt))) {
                bsl::error() << "virtual address is not page aligned: "    // --
                             << bsl::hex(page_virt)                        // --
                             << bsl::endl                                  // --
                             << bsl::here();                               // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(page_phys.is_zero())) {
                bsl::error() << "physical address is invalid: "    // --
                             << bsl::hex(page_phys)                // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(!this->is_page_aligned(page_phys))) {
                bsl::error() << "physical address is not page aligned: "    // --
                             << bsl::hex(page_phys)                         // --
                             << bsl::endl                                   // --
                             << bsl::here();                                // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(!page_flags)) {
                bsl::error() << "invalid flags: "       // --
                             << bsl::hex(page_flags)    // --
                             << bsl::endl               // --
                             << bsl::here();            // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(!auto_release)) {
                bsl::error() << "invalid auto release: "    // --
                             << auto_release                // --
                             << bsl::endl                   // --
                             << bsl::here();                // --

                return bsl::errc_failure;
            }

            if ((page_flags & MAP_PAGE_WRITE).is_pos()) {
                if ((page_flags & MAP_PAGE_EXECUTE).is_pos()) {
                    bsl::error() << "invalid page_flags: "    // --
                                 << bsl::hex(page_flags)      // --
                                 << bsl::endl                 // --
                                 << bsl::here();              // --

                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                bsl::touch();
            }

            auto *const pml4te{m_pml4t->entries.at_if(this->pml4to(page_virt))};
            if (pml4te->p == bsl::ZERO_UMAX) {
                if (bsl::unlikely(!this->add_pdpt(tls, pml4te))) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {

                /// NOTE:
                /// - The loader doesn't map in the memory associated with
                ///   the microkernel's page tables. This means this code
                ///   cannot walk any pages mapped to the microkernel, it
                ///   can only alias these pages. For this reason, mapping
                ///   must always take place on userspace specific memory
                ///   and the address spaces must be distinct.
                ///

                if (pml4te->us == bsl::ZERO_UMAX) {
                    bsl::error() << "attempt to map the userspace address "              // --
                                 << bsl::hex(page_virt)                                  // --
                                 << " in an address range owned by the kernel failed"    // --
                                 << bsl::endl                                            // --
                                 << bsl::here();                                         // --

                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            auto *const pdpt{this->get_pdpt(pml4te)};
            auto *const pdpte{pdpt->entries.at_if(this->pdpto(page_virt))};
            if (pdpte->p == bsl::ZERO_UMAX) {
                if (bsl::unlikely(!this->add_pdt(tls, pdpte))) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                bsl::touch();
            }

            auto *const pdt{this->get_pdt(pdpte)};
            auto *const pdte{pdt->entries.at_if(this->pdto(page_virt))};
            if (pdte->p == bsl::ZERO_UMAX) {
                if (bsl::unlikely(!this->add_pt(tls, pdte))) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                bsl::touch();
            }

            auto *const pt{this->get_pt(pdte)};
            auto *const pte{pt->entries.at_if(this->pto(page_virt))};
            if (bsl::unlikely(pte->p != bsl::ZERO_UMAX)) {
                bsl::error() << "virtual address "     // --
                             << bsl::hex(page_virt)    // --
                             << " already mapped"      // --
                             << bsl::endl              // --
                             << bsl::here();           // --

                return bsl::errc_already_exists;
            }

            pte->phys = (page_phys >> PAGE_SHIFT).get();
            pte->p = bsl::ONE_UMAX.get();
            pte->us = bsl::ONE_UMAX.get();
            pte->auto_release = auto_release.get();

            if (!(page_flags & MAP_PAGE_WRITE).is_zero()) {
                pte->rw = bsl::ONE_UMAX.get();
            }
            else {
                pte->rw = bsl::ZERO_UMAX.get();
            }

            if (!(page_flags & MAP_PAGE_EXECUTE).is_zero()) {
                pte->nx = bsl::ZERO_UMAX.get();
            }
            else {
                pte->nx = bsl::ONE_UMAX.get();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Maps a page into the root page table being managed
        ///     by this class. This version allows for unaligned virtual and
        ///     physical addresses and will perform the alignment for you.
        ///     Note that you should only use this function if you actually
        ///     need unaligned support to ensure alignment mistakes are not
        ///     accidentally introduced.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param page_virt the virtual address to map the physical address
        ///     too.
        ///   @param page_phys the physical address to map. If the physical
        ///     address is set to 0, map_page will use the page pool to
        ///     determine the physical address.
        ///   @param page_flags defines how memory should be mapped
        ///   @param auto_release defines what auto release tag to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        map_page_unaligned(
            tls_t &tls,
            bsl::safe_uintmax const &page_virt,
            bsl::safe_uintmax const &page_phys,
            bsl::safe_uintmax const &page_flags,
            bsl::safe_int32 const &auto_release) &noexcept -> bsl::errc_type
        {
            return this->map_page(
                tls,
                this->page_aligned(page_virt),
                this->page_aligned(page_phys),
                page_flags,
                auto_release);
        }

        /// <!-- description -->
        ///   @brief Allocates a page from the provided page pool and maps it
        ///     into the root page table being managed by this class The page
        ///     is marked as "auto release", meaning when this root page table
        ///     is released, the pages allocated by this function will
        ///     automatically be deallocated and put back into the provided
        ///     page pool. Note that this version maps the memory in as
        ///     read/write.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param page_virt the virtual address to map the allocated
        ///     page to
        ///   @param auto_release defines what auto release tag to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        allocate_page_rw(
            tls_t &tls,
            bsl::safe_uintmax const &page_virt,
            bsl::safe_int32 const &auto_release) &noexcept -> void *
        {
            if (bsl::unlikely_assert(!m_initialized)) {
                bsl::error() << "root_page_table_t not initialized\n" << bsl::here();
                return nullptr;
            }

            if (bsl::unlikely_assert(page_virt.is_zero())) {
                bsl::error() << "virtual address is invalid: "    // --
                             << bsl::hex(page_virt)               // --
                             << bsl::endl                         // --
                             << bsl::here();                      // --

                return nullptr;
            }

            if (bsl::unlikely_assert(!this->is_page_aligned(page_virt))) {
                bsl::error() << "virtual address is not page aligned: "    // --
                             << bsl::hex(page_virt)                        // --
                             << bsl::endl                                  // --
                             << bsl::here();                               // --

                return nullptr;
            }

            if (bsl::unlikely_assert(!auto_release)) {
                bsl::error() << "invalid auto release: "    // --
                             << auto_release                // --
                             << bsl::endl                   // --
                             << bsl::here();                // --

                return nullptr;
            }

            return this->allocate_page(
                tls, page_virt, MAP_PAGE_READ | MAP_PAGE_WRITE, auto_release);
        }

        /// <!-- description -->
        ///   @brief Allocates a page from the provided page pool and maps it
        ///     into the root page table being managed by this class The page
        ///     is marked as "auto release", meaning when this root page table
        ///     is released, the pages allocated by this function will
        ///     automatically be deallocated and put back into the provided
        ///     page pool. Note that this version maps the memory in as
        ///     read/execute.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param page_virt the virtual address to map the allocated
        ///     page to
        ///   @param auto_release defines what auto release tag to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        allocate_page_rx(
            tls_t &tls,
            bsl::safe_uintmax const &page_virt,
            bsl::safe_int32 const &auto_release) &noexcept -> void *
        {
            if (bsl::unlikely_assert(!m_initialized)) {
                bsl::error() << "root_page_table_t not initialized\n" << bsl::here();
                return nullptr;
            }

            if (bsl::unlikely_assert(page_virt.is_zero())) {
                bsl::error() << "virtual address is invalid: "    // --
                             << bsl::hex(page_virt)               // --
                             << bsl::endl                         // --
                             << bsl::here();                      // --

                return nullptr;
            }

            if (bsl::unlikely_assert(!this->is_page_aligned(page_virt))) {
                bsl::error() << "virtual address is not page aligned: "    // --
                             << bsl::hex(page_virt)                        // --
                             << bsl::endl                                  // --
                             << bsl::here();                               // --

                return nullptr;
            }

            if (bsl::unlikely_assert(!auto_release)) {
                bsl::error() << "invalid auto release: "    // --
                             << auto_release                // --
                             << bsl::endl                   // --
                             << bsl::here();                // --

                return nullptr;
            }

            return this->allocate_page(
                tls, page_virt, MAP_PAGE_READ | MAP_PAGE_EXECUTE, auto_release);
        }

        /// <!-- description -->
        ///   @brief Dumps the provided pml4_t
        ///
        constexpr void
        dump() const &noexcept
        {
            if constexpr (BSL_DEBUG_LEVEL == bsl::CRITICAL_ONLY) {
                return;
            }

            if (bsl::unlikely_assert(!m_initialized)) {
                bsl::print() << "[error]" << bsl::endl;
                return;
            }

            this->dump_pml4t(m_pml4t);
        }
    };
}

#endif
