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
#include "memory_type_t.hpp"
#include "range_t.hpp"

#include <mk_interface.hpp>

#include <bsl/array.hpp>
#include <bsl/convert.hpp>
#include <bsl/cstdint.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>

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
        /// @brief defines the MTRRdefType MSR type field
        constexpr bsl::safe_uintmax IA32_MTRRDEFTYPE_E{bsl::to_umax(0x0000000000000800U)};

        /// @brief defines the min address of physical memory
        constexpr bsl::safe_uintmax MIN_PHYSICAL_ADDR{bsl::to_umax(0x0000000000000000U)};
        /// @brief defines the max size of physical memory
        constexpr bsl::safe_uintmax MAX_PHYSICAL_SIZE{bsl::to_umax(0xFFFFFFFFFFFFFFFFU)};
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

        /// <!-- description -->
        ///   @brief Adds a range to the list. If the range overlaps with any
        ///     of the existing ranges, they are split.
        ///
        /// <!-- inputs/outputs -->
        ///   @param addr the address of the range
        ///   @param size the size of the range
        ///   @param type the type of memory in the range
        ///   @return Returns bsl::errc_success on success and bsl::errc_failure
        ///     on failure.
        ///
        [[nodiscard]] constexpr auto
        add_range(
            bsl::safe_uintmax const &addr,
            bsl::safe_uintmax const &size,
            memory_type_t const type) &noexcept -> bsl::errc_type
        {
            (void)addr;
            (void)size;
            (void)type;

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
            syscall::bf_status_t status{};

            /// NOTE:
            /// - Before we start, we need to ensure that the ranges are
            ///   cleared. This is just in case this function is run more
            ///   than once.
            ///

            for (auto const elem : m_ranges) {
                *elem.data = {};
            }

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
                    details::MIN_PHYSICAL_ADDR, details::MAX_PHYSICAL_SIZE, memory_type_t::wb);
            }

            /// NOTE:
            /// - The next step is to get the MTRR information from the MSRs.
            ///   We have to ask the kernel for this information.
            ///

            bsl::safe_uintmax cap{};
            bsl::safe_uintmax def{};

            status = syscall::bf_intrinsic_op_read_msr(handle, details::IA32_MTRRCAP, cap);
            if (bsl::unlikely(status != syscall::BF_STATUS_SUCCESS)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            status = syscall::bf_intrinsic_op_read_msr(handle, details::IA32_MTRRDEFTYPE, def);
            if (bsl::unlikely(status != syscall::BF_STATUS_SUCCESS)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            /// NOTE:
            /// - Next we need to add the default range to the list. This sets
            ///   all of memory to this memory type. All calls to add_range()
            ///   after this will split this default type up for each memory
            ///   type defined by BIOS. This ensures that when we are done,
            ///   every physical memory address has a type defined for it.
            ///

            // chaneg memory type to an int type
            // add split logic

            // ret = this->add_range(
            //     details::MIN_PHYSICAL_ADDR, details::MAX_PHYSICAL_SIZE, );
            // if (bsl::unlikely(!ret)) {
            //     bsl::print<bsl::V>() << bsl::here();
            //     return bsl::errc_failure;
            // }

            /// NOTE:
            /// - To create a continuous, non-overlapping view of the entire
            ///   physical memory space, we must first start with the default
            ///

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
