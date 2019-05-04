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

// TIDY_EXCLUSION=-cppcoreguidelines-pro-type-vararg
//
// Reason:
//    The Linux APIs require the use of var-args, so this test has to be
//    disabled.
//

#include <bfgsl.h>
#include <ioctl.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

// -----------------------------------------------------------------------------
// Unit Test Seems
// -----------------------------------------------------------------------------

int fd;

int
bfm_ioctl_open()
{
    return open("/dev/bareflank", O_RDWR);
}

int64_t
bfm_send_ioctl(unsigned long request)
{
    return ioctl(fd, request);
}

int64_t
bfm_read_ioctl(unsigned long request, void *data)
{
    return ioctl(fd, request, data);
}

int64_t
bfm_write_ioctl(unsigned long request, const void *data)
{
    return ioctl(fd, request, data);
}

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

ioctl::ioctl()
{
    if (fd = bfm_ioctl_open(); fd < 0) {
        throw std::runtime_error("failed to open to bfdriver");
    }
}

ioctl::~ioctl()
{
    if (fd >= 0) {
        close(fd);
    }
}

void
ioctl::call_ioctl_load_vmm(
    gsl::not_null<const ioctl_load_args_t *> args) const
{
    if (bfm_write_ioctl(IOCTL_LOAD_VMM, args) < 0) {
        throw std::runtime_error("ioctl failed: IOCTL_LOAD_VMM");
    }
}

void
ioctl::call_ioctl_unload_vmm() const
{
    if (bfm_send_ioctl(IOCTL_UNLOAD_VMM) < 0) {
        throw std::runtime_error("ioctl failed: IOCTL_UNLOAD_VMM");
    }
}

void
ioctl::call_ioctl_start_vmm() const
{
    if (bfm_send_ioctl(IOCTL_START_VMM) < 0) {
        throw std::runtime_error("ioctl failed: IOCTL_START_VMM");
    }
}

void
ioctl::call_ioctl_stop_vmm() const
{
    if (bfm_send_ioctl(IOCTL_STOP_VMM) < 0) {
        throw std::runtime_error("ioctl failed: IOCTL_STOP_VMM");
    }
}

void
ioctl::call_ioctl_dump_vmm(
    gsl::not_null<debug_ring_resources_t *> args) const
{
    if (bfm_read_ioctl(IOCTL_DUMP_VMM, args) < 0) {
        throw std::runtime_error("ioctl failed: IOCTL_DUMP_VMM");
    }
}

void
ioctl::call_ioctl_vmm_status(
    gsl::not_null<status_t *> args) const
{
    if (bfm_read_ioctl(IOCTL_VMM_STATUS, args) < 0) {
        throw std::runtime_error("ioctl failed: IOCTL_VMM_STATUS");
    }
}
