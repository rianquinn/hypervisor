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

#ifndef IOCTL_DETAILS_LINUX_IOCTL_DEBUG_H
#define IOCTL_DETAILS_LINUX_IOCTL_DEBUG_H

#include <ioctl/ioctl_debug.h>
#include <common/details/ioctl_debug.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

namespace host::details::linux_platform
{
    class ioctl_debug
    {
        int m_fd{};
        debug_ring_t m_dr{};

    public:
        ioctl_debug()
        {
            if (m_fd = open("/dev/bareflank", O_RDWR); m_fd < 0) {    // NOLINT
                throw std::runtime_error("failed to open to bfdriver");
            }
        }

        ~ioctl_debug()
        {
            if (m_fd >= 0) {
                close(m_fd);
            }
        }

    public:
        auto
        dump_vmm() -> std::string
        {
            m_dr = {};

            if (::ioctl(m_fd, IOCTL_DUMP_VMM, &m_dr) < 0) {    // NOLINT
                throw std::runtime_error("ioctl IOCTL_DUMP_VMM failed");
            }

            return debugring_to_string(m_dr);
        }

    public:
        // clang-format off

        ioctl_debug(ioctl_debug &&) noexcept = default;
        ioctl_debug &operator=(ioctl_debug &&) noexcept = default;

        ioctl_debug(const ioctl_debug &) = delete;
        ioctl_debug &operator=(const ioctl_debug &) = delete;

        // clang-format on
    };

}    // namespace host::details::linux_platform

#endif
