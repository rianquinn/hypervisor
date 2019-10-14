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

#ifndef IOCTL_DETAILS_LINUX_IOCTL_VMCALL_H
#define IOCTL_DETAILS_LINUX_IOCTL_VMCALL_H

#include "../common/ioctl_vmcall.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

namespace host::details::linux_platform
{

class ioctl_vmcall :
    public common::ioctl_vmcall
{
    int m_fd{};

public:
    ioctl_vmcall()
    {
        if (m_fd = open("/dev/bareflank", O_RDWR); m_fd < 0) {
            throw std::runtime_error("failed to open to bfdriver");
        }
    }

    ~ioctl_vmcall()
    {
        if (m_fd >= 0) {
            close(m_fd);
        }
    }

public:
    auto call(
        uint64_t reg1, uint64_t reg2, uint64_t reg3, uint64_t reg4)
    -> uint64_t
    {
        ioctl_vmcall_args_t args = {
            reg1, reg2, reg3, reg4
        };

        if (::ioctl(m_fd, IOCTL_VMCALL_CMD, &args) < 0) {
            throw std::runtime_error("ioctl failed: IOCTL_VMCALL_CMD");
        }

        return args.reg1;
    }
};

}

#endif
