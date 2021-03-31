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

#ifndef MTRRS_T_HPP
#define MTRRS_T_HPP

#include "intrinsic_cpuid.hpp"
#include "memory_type.hpp"
#include "range_t.hpp"

#include <mk_interface.hpp>

#include <bsl/array.hpp>
#include <bsl/convert.hpp>
#include <bsl/cstdint.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/sort.hpp>

namespace example
{
    namespace details
    {
        /// @brief defines the CPUID feature identifier bit for MTRR
        constexpr bsl::safe_uintmax MAX_RANGES{bsl::to_umax(256)};

        /// @brief defines the CPUID feature identifier bit for MTRR
        constexpr bsl::safe_uintmax CPUID_FEATURE_IDENTIFIERS_MTRR{bsl::to_umax(12)};

        /// @brief defines the MTRRcap MSR
        constexpr bsl::safe_uint32 IA32_MTRRCAP{bsl::to_u32(0x000000FEU)};
        /// @brief defines the MTRRcap MSR VCNT field
        constexpr bsl::safe_uintmax IA32_MTRRCAP_VCNT{bsl::to_umax(0x00000000000000FFU)};

        /// @brief defines the MTRRdefType MSR
        constexpr bsl::safe_uint32 IA32_MTRRDEFTYPE{bsl::to_u32(0x000002FFU)};
        /// @brief defines the MTRRdefType MSR type field
        constexpr bsl::safe_uintmax IA32_MTRRDEFTYPE_TYPE{bsl::to_umax(0x00000000000000FFU)};
        /// @brief defines the MTRRdefType MSR fixed range enable field
        constexpr bsl::safe_uintmax IA32_MTRRDEFTYPE_FE{bsl::to_umax(0x0000000000000400U)};
        /// @brief defines the MTRRdefType MSR enable field
        constexpr bsl::safe_uintmax IA32_MTRRDEFTYPE_E{bsl::to_umax(0x0000000000000800U)};

        /// @brief defines the min address of physical memory
        constexpr bsl::safe_uintmax MIN_PHYSICAL_ADDR{bsl::to_umax(0x0000000000000000U)};
        /// @brief defines the max size of physical memory
        constexpr bsl::safe_uintmax MAX_PHYSICAL_SIZE{bsl::to_umax(0xFFFFFFFFFFFFFFFFU)};

        /// <!-- description -->
        ///   @brief Implements the sort function that we use for a range_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param a the first element to compare
        ///   @param b the second element to compare
        ///   @return Returns true if a is less b, false otherwise
        ///
        [[nodiscard]] constexpr auto
        range_t_sort_cmp(range_t const &a, range_t const &b) noexcept -> bool
        {
            return a.addr < b.addr;
        };
    }

    /// @class mk::mtrrs_t
    ///
    /// <!-- description -->
    ///   @brief Parses the MTRRs and provides a continuous, non-overlapping
    ///     view of the ranges as needed.
    ///
    class mtrrs_t final
    {
        /// @brief stores the ranges associated with this mtrrs_t
        bsl::array<range_t, details::MAX_RANGES.get()> m_ranges{};
        /// @brief stores the number of ranges in the list.
        bsl::safe_uintmax m_ranges_count{};

        /// <!-- description -->
        ///   @brief Returns the combination of two memory type based on the
        ///     memory combining rules defined in the AMD/Intel manuals.
        ///
        /// <!-- inputs/outputs -->
        ///   @param r1 the first range to combine
        ///   @param r2 the second range to combine
        ///   @return Returns the combination of two memory type based on the
        ///     memory combining rules defined in the AMD/Intel manuals.
        ///
        [[nodiscard]] constexpr auto
        combine(range_t const &r1, range_t const &r2) &noexcept -> bsl::safe_uintmax
        {
            return bsl::to_umax(0);
        }

        /// <!-- description -->
        ///   @brief Adds a range to the list. This version of the function
        ///     does not attempt to clean up the ranges in the list. It
        ///     simply adds the range to the list and moves on.
        ///
        /// <!-- inputs/outputs -->
        ///   @param r the range to add
        ///   @return Returns bsl::errc_success on success and bsl::errc_failure
        ///     on failure.
        ///
        [[nodiscard]] constexpr auto
        add_range(range_t const &r) &noexcept -> bsl::errc_type
        {
            auto *const ptr{m_ranges.at_if(m_ranges_count)};
            if (bsl::unlikely(nullptr == ptr)) {
                bsl::error() << "mtrrs_t full\n" << bsl::here();
                return bsl::errc_failure;
            }

            *ptr = r;
            ++m_ranges_count;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Adds a range to the list. If the range that is being added
        ///     is a subset of any other range, or a range is a subset of the
        ///     range being added, the subsets are split. Any intersecting
        ///     ranges that are not subsets will cause this function to fail
        ///     as they are not supported by this algorithm.
        ///
        /// <!-- inputs/outputs -->
        ///   @param addr the address of the range
        ///   @param size the size of the range
        ///   @param type the type of memory in the range
        ///     type for all of memory, false otherwise
        ///   @return Returns bsl::errc_success on success and bsl::errc_failure
        ///     on failure.
        ///
        [[nodiscard]] constexpr auto
        add_range(
            bsl::safe_uintmax const &addr,
            bsl::safe_uintmax const &size,
            bsl::safe_uintmax const &type) &noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            range_t r1{addr, size, type, false};

            for (bsl::safe_uintmax i{}; i < m_ranges.size(); ++i) {
                auto *const r2{m_ranges.at_if(i)};

                auto const r1_l{r1.addr};
                auto const r1_r{r1.addr + r1.size};
                auto const r2_l{r2->addr};
                auto const r2_r{r2->addr + r2->size};

                if (r1.size.is_zero()) {
                    return bsl::errc_success;
                }

                if (!(r2_r > r1_l)) {
                    continue;
                }

                if (r1_l == r2_l) {
                    ret = this->add_range({r1.addr, r1.size, this->combine(r1, *r2), false});
                    if (bsl::unlikely(!ret)) {
                        bsl::print<bsl::V>() << bsl::here();
                        return bsl::errc_failure;
                    }

                    r2->addr = r1.addr + r1.size;
                    return bsl::errc_success;
                }

                if (r1_r < r2_r) {
                    ret = this->add_range({r2->addr, r1.addr - r2->addr, r2->type, false});
                    if (bsl::unlikely(!ret)) {
                        bsl::print<bsl::V>() << bsl::here();
                        return bsl::errc_failure;
                    }

                    ret = this->add_range({r1.addr, r1.size, this->combine(r1, *r2), false});
                    if (bsl::unlikely(!ret)) {
                        bsl::print<bsl::V>() << bsl::here();
                        return bsl::errc_failure;
                    }

                    r2->addr = r1.addr + r1.size;
                    return bsl::errc_success;
                }

                auto const r1_new_addr{r2->addr + r2->size};
                auto const r1_new_size{r1.size - (r1_new_addr - r1.addr)};

                ret = this->add_range(
                    {r1.addr, r1_new_addr - r1.addr, this->combine(r1, *r2), false});
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                r2->size = r1.addr - r2->addr;

                r1.addr = r1_new_addr;
                r1.size = r1_new_size;

                bsl::sort(m_ranges, &details::range_t_sort_cmp);
            }

            return bsl::errc_success;
        }

    public:
        /// <!-- description -->
        ///   @brief Parses the MTRRs and stores the ranges in a continuous
        ///     non-overlapping form. This ensures that every single physical
        ///     address can be looked up by this class and provide the MTRR's
        ///     opinion as to what the memory's type is.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam HANDLE_CONCEPT the type of handle to use
        ///   @param handle the handle to use
        ///   @return Returns bsl::errc_success on success and bsl::errc_failure
        ///     on failure.
        ///
        template<typename HANDLE_CONCEPT>
        [[nodiscard]] constexpr auto
        parse(HANDLE_CONCEPT &handle) &noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            /// NOTE:
            /// - Before we start, we need to ensure that the ranges are
            ///   cleared. This is just in case this function is run more
            ///   than once.
            ///

            for (auto const elem : m_ranges) {
                *elem.data = {};
            }

            m_ranges_count = {};

            /// NOTE:
            /// - The first step is to make sure that MTRRs are supported.
            ///   If they aren't something really weird is going on, but in
            ///   general, that is ok as well we have to do is add a single
            ///   range that marks all of memory as WB.
            ///

            bsl::safe_uintmax rax{};
            bsl::safe_uintmax rbx{};
            bsl::safe_uintmax rcx{};
            bsl::safe_uintmax rdx{};

            intrinsic_cpuid(rax.data(), rbx.data(), rcx.data(), rdx.data());

            if ((rdx & details::CPUID_FEATURE_IDENTIFIERS_MTRR).is_zero()) {
                return this->add_range(
                    details::MIN_PHYSICAL_ADDR, details::MAX_PHYSICAL_SIZE, MEMORY_TYPE_WB);
            }

            /// NOTE:
            /// - The next step is to get the MTRR information from the MSRs.
            ///   We have to ask the kernel for this information.
            ///

            bsl::safe_uintmax cap{};
            bsl::safe_uintmax def{};

            ret = syscall::bf_intrinsic_op_rdmsr(handle, details::IA32_MTRRCAP, cap);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = syscall::bf_intrinsic_op_rdmsr(handle, details::IA32_MTRRDEFTYPE, def);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            auto const default_mem_type{def & details::IA32_MTRRDEFTYPE_TYPE};

            /// NOTE:
            /// - Next we need to add the default range to the list. This sets
            ///   all of memory to this memory type. All calls to add_range()
            ///   after this will split this default type up for each memory
            ///   type defined by BIOS. This ensures that when we are done,
            ///   every physical memory address has a type defined for it.
            /// - It should be noted that the add_range() algorithm expects
            ///   that this initial range is added for it work properly.
            ///

            ret = this->add_range(
                {details::MIN_PHYSICAL_ADDR, details::MAX_PHYSICAL_SIZE, default_mem_type, true});
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            /// NOTE:
            /// - To create a continuous, non-overlapping view of the entire
            ///   physical memory space, we must first start with the default
            ///

            ret = this->add_range(
                {details::MIN_PHYSICAL_ADDR, bsl::to_umax(0x2000), MEMORY_TYPE_WB, true});

            for (bsl::safe_uintmax i{}; i < m_ranges_count; ++i) {
                bsl::print() << "[" << i << "] MTRR range:" << bsl::endl;
                bsl::print() << "  - addr: " << bsl::hex(m_ranges.at_if(i)->addr) << bsl::endl;
                bsl::print() << "  - size: " << bsl::hex(m_ranges.at_if(i)->size) << bsl::endl;
                bsl::print() << "  - type: " << m_ranges.at_if(i)->type << bsl::endl;
            }

            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            /// [ ] Get default type
            /// [ ] Add range for entire space with default type
            /// [ ] create function to add range that splits as needed
            /// [ ] Add range for the fixed width as uncacheable
            /// [ ] Add all variable range
            /// [ ] Sort and set as non-blocking?
            /// [ ] Create dump function
            /// [ ] Implement NP and test
            /// [ ] Implement identify map function in the mtrrs_t.
            ///     This function will loop through all of the ranges and
            ///     1:1 map from there.
            /// [ ] Implement EPT

            /// [ ] Implement map 4k, 2m and 1g
            /// [ ] Implement map identify map range

            return bsl::errc_success;
        }
    };
}

#endif

// /// Contains
// ///
// /// @param addr the address to test
// /// @return returns true if the provided address is contained in the
// ///     range, false otherwise
// ///
// bool contains(uint64_t addr) const
// { return addr >= base && addr <= base + size; }

// /// Distance
// ///
// /// @param addr the address to test
// /// @return returns the distance from the provided address to the end
// ///     of the range. If the provided address is not contained in the
// ///     range, the result is undefined.
// ///
// uint64_t distance(uint64_t addr) const
// { return size - (addr - base);  }
