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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file bfdebugringinterface.h
 */

#ifndef BFDEBUGRINGINTERFACE_H
#define BFDEBUGRINGINTERFACE_H

#include <bftypes.h>
#include <bfconstants.h>

#pragma pack(push, 1)

/**
 * @struct debug_ring_resources_t
 *
 * Note there are many different designs for cicular buffers, but all of the
 * designs have to face the same problem. How to detect when the buffer is
 * full vs when it is empty. This design uses two counters that grow
 * forever.
 *
 * @var debug_ring_resources_t::epos
 *     the end position in the circular buffer
 * @var debug_ring_resources_t::spos
 *     the start position in the circular buffer
 * @var debug_ring_resources_t::tag1
 *     used to identify the debug ring from a memory dump
 * @var debug_ring_resources_t::buf
 *     the circular buffer that stores the debug strings.
 * @var debug_ring_resources_t::tag2
 *     used to identify the debug ring from a memory dump
 */
struct debug_ring_resources_t {
    int64_t epos;
    int64_t spos;

    uint64_t tag1;
    char buf[DEBUG_RING_SIZE];
    uint64_t tag2;
};

#ifdef __cplusplus

#include <bfgsl.h>
#include <iostream>

/**
 * Dump Debug Ring
 *
 * @param drr the debug_ring_resource
 */
static inline void
dump_debug_ring(const struct debug_ring_resources_t *drr) noexcept
{
    expects(drr != nullptr);
    auto view = gsl::span(drr->buf);

    if (drr->spos == drr->epos) {
        return;
    }

    auto spos = drr->spos;
    auto epos = drr->epos;

    while (spos != epos) {
        std::cout << view[spos++];

        if (spos == DEBUG_RING_SIZE) {
            spos = 0;
        }
    }

    std::cout << '\n';
}

#endif

#pragma pack(pop)

#endif
