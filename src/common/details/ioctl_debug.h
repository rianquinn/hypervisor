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

#ifndef COMMON_DETAILS_IOCTL_DEBUG_H
#define COMMON_DETAILS_IOCTL_DEBUG_H

#include "driver.h"
#include "debugring.h"

/* -------------------------------------------------------------------------- */
/* Common                                                                     */
/* -------------------------------------------------------------------------- */

#define IOCTL_DUMP_VMM_CMD 0x811

/* -------------------------------------------------------------------------- */
/* Linux Interfaces                                                           */
/* -------------------------------------------------------------------------- */

#ifdef __linux__
#define IOCTL_DUMP_VMM _IOR(BAREFLANK_MAJOR, IOCTL_DUMP_VMM_CMD, struct debug_ring_resources_t *)
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
