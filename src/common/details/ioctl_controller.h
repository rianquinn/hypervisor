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

#ifndef COMMON_DETAILS_IOCTL_CONTROLLER_H
#define COMMON_DETAILS_IOCTL_CONTROLLER_H

#include "driver.h"

/* -------------------------------------------------------------------------- */
/* Common                                                                     */
/* -------------------------------------------------------------------------- */

#define IOCTL_LOAD_VMM_CMD 0x801
#define IOCTL_UNLOAD_VMM_CMD 0x802
#define IOCTL_START_VMM_CMD 0x803
#define IOCTL_STOP_VMM_CMD 0x804

/* -------------------------------------------------------------------------- */
/* Types                                                                      */
/* -------------------------------------------------------------------------- */

/**
 * @struct ioctl_load_args_t
 *
 * Loads the VMM
 *
 * @var ioctl_load_args_t::file_addr
 *     the address of the VMM in memory
 * @var ioctl_load_args_t::file_size
 *     the size in bytes of the VMM in memory
 * @var ioctl_load_args_t::mem
 *     the size in bytes of the memory to give the VMM
 */
struct ioctl_load_args_t {
    const void *file_addr;
    uint64_t file_size;
    uint64_t mem;
};

/* -------------------------------------------------------------------------- */
/* Linux Interfaces                                                           */
/* -------------------------------------------------------------------------- */

#ifdef __linux__
#define IOCTL_LOAD_VMM _IOW(BAREFLANK_MAJOR, IOCTL_LOAD_VMM_CMD, struct ioctl_load_args_t *)
#define IOCTL_UNLOAD_VMM _IO(BAREFLANK_MAJOR, IOCTL_UNLOAD_VMM_CMD)
#define IOCTL_START_VMM _IO(BAREFLANK_MAJOR, IOCTL_START_VMM_CMD)
#define IOCTL_STOP_VMM _IO(BAREFLANK_MAJOR, IOCTL_STOP_VMM_CMD)
#endif

/* -------------------------------------------------------------------------- */
/* Windows Interfaces                                                         */
/* -------------------------------------------------------------------------- */

#if defined(_WIN32) || defined(__CYGWIN__)
#define IOCTL_LOAD_VMM CTL_CODE(BAREFLANK_DEVICETYPE, IOCTL_LOAD_VMM_CMD, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_UNLOAD_VMM CTL_CODE(BAREFLANK_DEVICETYPE, IOCTL_UNLOAD_VMM_CMD, METHOD_BUFFERED, 0)
#define IOCTL_START_VMM CTL_CODE(BAREFLANK_DEVICETYPE, IOCTL_START_VMM_CMD, METHOD_BUFFERED, 0)
#define IOCTL_STOP_VMM CTL_CODE(BAREFLANK_DEVICETYPE, IOCTL_STOP_VMM_CMD, METHOD_BUFFERED, 0)
#endif

#endif
