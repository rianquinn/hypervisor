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

#ifndef IOCTL_DETAILS_LINUX_IOCTL_CONTROLLER_H
#define IOCTL_DETAILS_LINUX_IOCTL_CONTROLLER_H

#include <ioctl/ioctl_controller.h>
#include <common/details/ioctl_controller.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

namespace host::details::linux_platform
{
    class ioctl_controller
    {
        int m_fd{};

    public:
        ioctl_controller()
        {
            if (m_fd = open("/dev/bareflank", O_RDWR); m_fd < 0) {    // NOLINT
                throw std::runtime_error("failed to open to bfdriver");
            }
        }

        ~ioctl_controller()
        {
            if (m_fd >= 0) {
                close(m_fd);
            }
        }

    public:
        auto
        load_vmm(const std::vector<char> &file, size_t heap_size) -> void
        {
            ioctl_load_args_t args = {file.data(), file.size(), heap_size};

            if (::ioctl(m_fd, IOCTL_LOAD_VMM, &args) < 0) {    // NOLINT
                throw std::runtime_error("ioctl IOCTL_LOAD_VMM failed");
            }
        }

        auto
        unload_vmm() -> void
        {
            if (::ioctl(m_fd, IOCTL_UNLOAD_VMM) < 0) {    // NOLINT
                throw std::runtime_error("ioctl IOCTL_UNLOAD_VMM failed");
            }
        }

        auto
        start_vmm() -> void
        {
            if (::ioctl(m_fd, IOCTL_START_VMM) < 0) {    // NOLINT
                throw std::runtime_error("ioctl IOCTL_START_VMM failed");
            }
        }

        auto
        stop_vmm() -> void
        {
            if (::ioctl(m_fd, IOCTL_STOP_VMM) < 0) {    // NOLINT
                throw std::runtime_error("ioctl IOCTL_STOP_VMM failed");
            }
        }

    public:
        // clang-format off

        ioctl_controller(ioctl_controller &&) noexcept = default;
        ioctl_controller &operator=(ioctl_controller &&) noexcept = default;

        ioctl_controller(const ioctl_controller &) = delete;
        ioctl_controller &operator=(const ioctl_controller &) = delete;

        // clang-format on
    };

}    // namespace host::details::linux_platform

#endif
