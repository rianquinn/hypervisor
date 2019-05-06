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

#ifndef IMPLEMENTATION_DEBUG_RING_H
#define IMPLEMENTATION_DEBUG_RING_H

#include <bftypes.h>
#include <bfdebugringinterface.h>

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

namespace bfvmm::implementation
{

/// Debug Ring
///
/// The debug ring is a simple debug facility that allows the vmm to write
/// string data into a ring buffer while a reader that has shared access to
/// the same buffer can read from the debug ring to extract the strings
/// that are written to the buffer.
///
class debug_ring
{
public:

    /// Default Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    debug_ring() noexcept;

    /// Write to Debug Ring
    ///
    /// Writes a char to the debug ring. If the string is larger than
    /// the debug ring's internal buffer, the write will fail. If the debug
    /// ring is full, the write will keep removing existing strings in the
    /// buffer until enough space is made, to add the string.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param str the string to write to the debug ring
    ///
    void write(const char) noexcept;

public:

    debug_ring(debug_ring &&) noexcept = default;
    debug_ring &operator=(debug_ring &&) noexcept = default;

    debug_ring(const debug_ring &) = delete;
    debug_ring &operator=(const debug_ring &) = delete;
};

}

/// Get Debug Ring Resource
///
/// Returns a pointer to a debug_ring_resources_t for a given CPU.
///
/// @expects drr != nullptr
/// @ensures none
///
/// @param arg a pointer to the drr
/// @return BFSUCCESS on success, BFFAILURE otherwise
///
extern "C" status_t get_drr(uint64_t arg) noexcept;

/// Global Debug Ring
///
/// This provides the global debug ring that is used by the VMM.
/// This can be used to add debug information to the debug ring.
/// Note that this does not include any other debug devices, so
/// you probably should use the APIs in bfdebug.h instead.
///
extern bfvmm::implementation::debug_ring g_debug_ring;

#endif
