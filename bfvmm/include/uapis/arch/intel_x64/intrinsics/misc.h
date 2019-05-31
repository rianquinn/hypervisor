//
// Copyright (C) 2019 Assured Information Security, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef UAPIS_MISC_INTEL_X64_H
#define UAPIS_MISC_INTEL_X64_H

#include <bftypes.h>
#include <bfbitmanip.h>

#include "cpuid.h"

// -----------------------------------------------------------------------------
// C++ Wrappers
// -----------------------------------------------------------------------------

// *INDENT-OFF*

namespace intel_x64
{

constexpr const auto cache_line_size = 64ULL;
constexpr const auto cache_line_shift = 6ULL;

namespace exception
{
    constexpr const auto divide_error = 0U;
    constexpr const auto debug_exception = 1U;
    constexpr const auto nmi_int = 2U;
    constexpr const auto breakpoint = 3U;
    constexpr const auto overflow = 4U;
    constexpr const auto bound_range_exceeded = 5U;
    constexpr const auto invalid_opcode = 6U;
    constexpr const auto device_not_available = 7U;
    constexpr const auto double_fault = 8U;
    constexpr const auto coprocessor_segment_overrun = 9U;
    constexpr const auto invalid_tss= 10U;
    constexpr const auto segment_not_present= 11U;
    constexpr const auto stack_segment_fault= 12U;
    constexpr const auto general_protection= 13U;
    constexpr const auto page_fault= 14U;
    constexpr const auto floating_point_error= 16U;
    constexpr const auto alignment_check= 17U;
    constexpr const auto machine_check= 18U;
    constexpr const auto simd_floating_point_exception= 19U;
    constexpr const auto virtualization_exception= 20U;
}

namespace memory_type
{
    using value_type = uint64_t;

    constexpr const auto uncacheable = 0x00000000ULL;
    constexpr const auto write_combining = 0x00000001ULL;
    constexpr const auto write_through = 0x00000004ULL;
    constexpr const auto write_protected = 0x00000005ULL;
    constexpr const auto write_back = 0x00000006ULL;
    constexpr const auto uncacheable_minus = 0x00000007ULL;
}

inline auto is_addr_canonical(uint64_t addr)
{ return ((addr <= 0x00007FFFFFFFFFFFULL) || (addr >= 0xFFFF800000000000ULL)); }

inline auto is_addr_canonical(void *addr)
{ return is_addr_canonical(reinterpret_cast<uint64_t>(addr)); }

inline auto is_linear_addr_valid(uint64_t addr)
{ return is_addr_canonical(addr); }

inline auto is_linear_addr_valid(void *addr)
{ return is_addr_canonical(addr); }

inline auto is_physical_addr_valid(uint64_t addr)
{
    auto size = cpuid::addr_size::phys::get();
    auto mask = (0xFFFFFFFFFFFFFFFFULL >> size) << size;

    return ((addr & mask) == 0);
}

inline auto is_physical_addr_valid(uint64_t addr, uint64_t size)
{
    auto mask = (0xFFFFFFFFFFFFFFFFULL >> size) << size;
    return ((addr & mask) == 0);
}

inline auto is_physical_addr_valid(void *addr)
{ return is_physical_addr_valid(reinterpret_cast<uint64_t>(addr)); }

}

// *INDENT-ON*

#endif
