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
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef VMMCTL_LINUX_VMCALL_H
#define VMMCTL_LINUX_VMCALL_H

#include <vmmctl/vmcall.h>
#include <common/details/ioctl_vmcall.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

namespace vmmctl::linux_platform
{
    class vmcall : public common::ioctl_vmcall
    {
        int m_fd{};

    public:
        vmcall()
        {
            if (m_fd = open("/dev/bareflank", O_RDWR); m_fd < 0) {    // NOLINT
                throw std::runtime_error("failed to open to bfdriver");
            }
        }

        ~vmcall()
        {
            if (m_fd >= 0) {
                close(m_fd);
            }
        }

    public:
        auto
        call(uint64_t reg1, uint64_t reg2, uint64_t reg3, uint64_t reg4)
            -> uint64_t
        {
            ioctl_vmcall_args_t args = {reg1, reg2, reg3, reg4};

            if (::ioctl(m_fd, IOCTL_VMCALL_CMD, &args) < 0) {    // NOLINT
                throw std::runtime_error("ioctl IOCTL_VMCALL_CMD failed");
            }

            return args.reg1;
        }

    public:
        // clang-format off

        vmcall(vmcall &&) noexcept = default;
        vmcall &operator=(vmcall &&) noexcept = default;

        vmcall(const vmcall &) = delete;
        vmcall &operator=(const vmcall &) = delete;

        // clang-format on
    };

}

#endif
