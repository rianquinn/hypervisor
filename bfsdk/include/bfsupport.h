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
 * @file bfsupport.h
 */

#ifndef BFSUPPORT_H
#define BFSUPPORT_H

#include <bftypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct _start_args_t
 *
 * Provides information needed when executing _start
 *
 * @var section_info_t::request
 *      the request being made
 * @var section_info_t::arg1
 *      an optional argument
 * @var section_info_t::arg2
 *      an optional argument
 */
struct _start_args_t {
    uintptr_t request;
    uintptr_t arg1;
    uintptr_t arg2;
};

/**
 * Request IDs
 *
 * The following defines the different types of requests that can be made
 * when calling bfmain.
 *
 * @cond
 */

#define BF_REQUEST_SET_MEM 10
#define BF_REQUEST_SET_MEM_NODE_TREE 11
#define BF_REQUEST_INIT 20
#define BF_REQUEST_EH_FRAME 21
#define BF_REQUEST_ADD_MD 30
#define BF_REQUEST_VMM_INIT 31
#define BF_REQUEST_VMM_FINI 32
#define BF_REQUEST_GET_DRR 33

/* @endcond */

#ifdef __cplusplus

/**
 * Start Type
 *
 * Defines the function signature for the _start function
 */
using _start_t = status_t (*)(uintptr_t stack, const struct _start_args_t *args);

/**
 * Main Function. This is called by the runtime code and is the main entry
 * point for any program that uses this environment.
 * 
 * @param request the request being made
 * @param arg1 optional arg #1
 * @param arg2 optional arg #2
 * @return BFSUCCESS on success, BFFAILURE otherwise
 */
extern "C" status_t
bfmain(uint64_t request, uint64_t arg1, uint64_t arg2) noexcept;

#else

/**
 * Start Type
 *
 * Defines the function signature for the _start function
 */
typedef status_t (*_start_t)(uintptr_t stack, const struct _start_args_t *args);

#endif

#ifdef __cplusplus
}
#endif

#endif
