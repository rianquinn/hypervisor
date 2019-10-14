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

#ifndef COMMON_DETAILS_IOCTL_VMCALL_H
#define COMMON_DETAILS_IOCTL_VMCALL_H

#include "driver.h"

/* -------------------------------------------------------------------------- */
/* Common                                                                     */
/* -------------------------------------------------------------------------- */

#define IOCTL_VMCALL_CMD 0x821

/* -------------------------------------------------------------------------- */
/* Types                                                                      */
/* -------------------------------------------------------------------------- */

/**
 * @struct ioctl_vmcall_args_t
 *
 * Stores the general registers for a vmcall
 *
 * @var ioctl_vmcall_args_t::reg1
 *     general register #1
 * @var ioctl_vmcall_args_t::reg2
 *     general register #2
 * @var ioctl_vmcall_args_t::reg3
 *     general register #3
 * @var ioctl_vmcall_args_t::reg4
 *     general register #4
 */
struct ioctl_vmcall_args_t {
    uint64_t reg1;
    uint64_t reg2;
    uint64_t reg3;
    uint64_t reg4;
};

/* -------------------------------------------------------------------------- */
/* Linux Interfaces                                                           */
/* -------------------------------------------------------------------------- */

#ifdef __linux__
#define IOCTL_VMCALL _IOWR(BAREFLANK_MAJOR, IOCTL_VMCALL_CMD, struct ioctl_vmcall_args_t *)
#endif

/* -------------------------------------------------------------------------- */
/* Windows Interfaces                                                         */
/* -------------------------------------------------------------------------- */

#if defined(_WIN32) || defined(__CYGWIN__)
#define IOCTL_VMCALL CTL_CODE(BAREFLANK_DEVICETYPE, IOCTL_VMCALL_CMD, METHOD_IN_DIRECT, FILE_READ_WRITE_DATA)
#endif

#endif
