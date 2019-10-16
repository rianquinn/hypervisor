/*
 * Copyright (C) 2019 Assured Information Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef COMMON_DETAILS_DEBUGRING_H
#define COMMON_DETAILS_DEBUGRING_H

#include <bftypes.h>

#pragma pack(push, 1)

/**
 * @struct debug_ring_t
 *
 * Note there are many different designs for circular buffers, but all of the
 * designs have to face the same problem. How to detect when the buffer is
 * full vs when it is empty. This design uses two counters that grow
 * forever.
 *
 * @var debug_ring_t::epos
 *     the end position in the circular buffer
 * @var debug_ring_t::spos
 *     the start position in the circular buffer
 * @var debug_ring_t::tag1
 *     used to identify the debug ring from a memory dump
 * @var debug_ring_t::buf
 *     the circular buffer that stores the debug strings.
 * @var debug_ring_t::tag2
 *     used to identify the debug ring from a memory dump
 */
struct debug_ring_t
{
    int64_t epos;
    int64_t spos;

    uint64_t tag1;
    char buf[BAREFLANK_DEBUGRING_SIZE];    // NOLINT
    uint64_t tag2;
};

#ifdef __cplusplus

#include <string>
#include <bfgsl.h>

/// Debug Ring to String
///
/// Converts a debug ring to a string.
///
/// @param dr the debug ring to convert
/// @return a string contaning the contents of the debug ring.
///
inline auto
debugring_to_string(const debug_ring_t &dr) -> std::string
{
    if (dr.spos == dr.epos) {
        return {};
    }

    std::string str;

    auto view = gsl::span(dr.buf);
    auto spos = dr.spos;
    auto epos = dr.epos;

    while (spos != epos) {
        str += view[spos++];

        if (spos >= view.size()) {
            spos = 0;
        }
    }

    return str;
}

#endif

#pragma pack(pop)

#endif
