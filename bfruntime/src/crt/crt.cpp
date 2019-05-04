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
#include <bfsupport.h>
#include <bfconstants.h>
#include <bfehframelist.h>

using init_t = void (*)();
using fini_t = void (*)();

eh_frame_t __g_eh_frame = {};

extern "C" status_t
bfmain(uint64_t request, uint64_t arg1, uint64_t arg2);

extern "C" void
__bareflank_init(
    uint64_t init_array_addr, uint64_t init_array_size)
{
    if (init_array_addr != 0) {
        auto n = init_array_size >> 3;
        auto init_array = reinterpret_cast<init_t *>(init_array_addr);

        auto view = gsl::span(init_array, gsl::index_cast(n));
        for (auto i = 0U; i < n && view.at(i) != nullptr; i++) {
            view.at(i)();
        }
    }
}

extern "C" void
__bareflank_register_eh_frame(
    uint64_t eh_frame_addr, uint64_t eh_frame_size)
{
    __g_eh_frame.addr = reinterpret_cast<void *>(eh_frame_addr);
    __g_eh_frame.size = eh_frame_size;
}

extern "C" status_t
_start_c(const _start_args_t *info) noexcept
{
    if (info->request == BF_REQUEST_INIT) {
        __bareflank_init(info->arg1, info->arg2);
        return BFSUCCESS;
    }

    if (info->request == BF_REQUEST_EH_FRAME) {
        __bareflank_register_eh_frame(info->arg1, info->arg2);
        return BFSUCCESS;
    }

    return bfmain(info->request, info->arg1, info->arg2);
}
