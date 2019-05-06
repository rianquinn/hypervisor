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

#include <bfgsl.h>
#include <bftypes.h>

#include <implementation/debug_ring.h>

// -----------------------------------------------------------------------------
// Global
// -----------------------------------------------------------------------------

bfvmm::implementation::debug_ring g_debug_ring;

static auto g_drr = debug_ring_resources_t{};
static auto g_drr_view = gsl::span(g_drr.buf);

extern "C" status_t
get_drr(uint64_t arg) noexcept
{
    if (auto drr = reinterpret_cast<debug_ring_resources_t **>(arg)) {
        *drr = &g_drr;
    }

    return BFSUCCESS;
}

// -----------------------------------------------------------------------------
// Debug Ring Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::implementation
{

debug_ring::debug_ring() noexcept
{
    g_drr.epos = 0;
    g_drr.spos = 0;
    g_drr.tag1 = 0xDB60DB60DB60DB60;
    g_drr.tag2 = 0x06BD06BD06BD06BD;
}

void
debug_ring::write(const char c) noexcept
{
    g_drr_view[g_drr.epos++] = c;

    if (g_drr.epos == DEBUG_RING_SIZE) {
        g_drr.epos = 0;
    }

    if (g_drr.epos == g_drr.spos) {
        g_drr.spos++;
    }

    if (g_drr.spos == DEBUG_RING_SIZE) {
        g_drr.spos = 0;
    }
}

}
