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

#ifndef REQUEST_INIT_FAILS
#define REQUEST_INIT_RETURN ENTRY_SUCCESS
#else
#define REQUEST_INIT_RETURN ENTRY_ERROR_UNKNOWN
#endif

#ifndef REQUEST_FINI_FAILS
#define REQUEST_FINI_RETURN ENTRY_SUCCESS
#else
#define REQUEST_FINI_RETURN ENTRY_ERROR_UNKNOWN
#endif

#ifndef REQUEST_ADD_MDL_FAILS
#define REQUEST_ADD_MDL_RETURN ENTRY_SUCCESS
#else
#define REQUEST_ADD_MDL_RETURN ENTRY_ERROR_UNKNOWN
#endif

#ifndef REQUEST_GET_DRR_FAILS
#define REQUEST_GET_DRR_RETURN ENTRY_SUCCESS
#else
#define REQUEST_GET_DRR_RETURN ENTRY_ERROR_UNKNOWN
#endif

#ifndef REQUEST_SET_RSDP_FAILS
#define REQUEST_SET_RSDP_RETURN ENTRY_SUCCESS
#else
#define REQUEST_SET_RSDP_RETURN ENTRY_ERROR_UNKNOWN
#endif

#ifndef REQUEST_VMM_INIT_FAILS
#define REQUEST_VMM_INIT_RETURN ENTRY_SUCCESS
#else
#define REQUEST_VMM_INIT_RETURN ENTRY_ERROR_UNKNOWN
#endif

#ifndef REQUEST_VMM_FINI_FAILS
#define REQUEST_VMM_FINI_RETURN ENTRY_SUCCESS
#else
#define REQUEST_VMM_FINI_RETURN ENTRY_ERROR_UNKNOWN
#endif

#include <bfgsl.h>
#include <bftypes.h>
#include <bfsupport.h>

int g_errno;
int *__errno() { return &g_errno; }

extern "C" int64_t
bfmain(uintptr_t request, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3)
{
    bfignored(arg1);
    bfignored(arg2);
    bfignored(arg3);

    switch (request) {
        case BF_REQUEST_INIT:
            return REQUEST_INIT_RETURN;

        case BF_REQUEST_FINI:
            return REQUEST_FINI_RETURN;

        case BF_REQUEST_ADD_MDL:
            return REQUEST_ADD_MDL_RETURN;

        case BF_REQUEST_GET_DRR:
            return REQUEST_GET_DRR_RETURN;

        case BF_REQUEST_VMM_INIT:
            return REQUEST_VMM_INIT_RETURN;

        case BF_REQUEST_VMM_FINI:
            return REQUEST_VMM_FINI_RETURN;

        case BF_REQUEST_SET_RSDP:
            return REQUEST_SET_RSDP_RETURN;

        default:
            break;
    }

    return ENTRY_ERROR_UNKNOWN;
}

// -----------------------------------------------------------------------------
// Missing C Functions
// -----------------------------------------------------------------------------

int g_cursor = 0;
char g_memory[0x100000] = {};

extern "C" int
write(int file, const void *buffer, size_t count)
{
    bfignored(file);
    bfignored(buffer);
    bfignored(count);

    return 0;
}

extern "C" uint64_t
unsafe_write_cstr(const char *cstr, size_t len)
{
    bfignored(cstr);
    bfignored(len);

    return 0;
}

extern "C" void *
_malloc_r(struct _reent *ent, size_t size)
{
    bfignored(ent);

    auto addr = &gsl::at(g_memory, g_cursor);
    g_cursor += size;

    return addr;
}

extern "C" void
_free_r(struct _reent *ent, void *ptr)
{
    bfignored(ent);
    bfignored(ptr);
}

extern "C" void *
_calloc_r(struct _reent *ent, size_t nmemb, size_t size)
{
    bfignored(ent);

    if (auto ptr = _malloc_r(nullptr, nmemb * size)) {
        return memset(ptr, 0, nmemb * size);
    }

    return nullptr;
}

extern "C" void *
_realloc_r(struct _reent *ent, void *ptr, size_t size)
{
    bfignored(ent);
    bfignored(ptr);
    bfignored(size);

    return nullptr;
}

extern "C" uint64_t *
thread_context_tlsptr(void)
{
    static uint64_t s_tls[0x1000] = {};
    return s_tls;
}

extern "C" uint64_t
thread_context_cpuid(void)
{
    return 0;
}
