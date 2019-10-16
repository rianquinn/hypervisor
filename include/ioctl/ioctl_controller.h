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

#ifndef IOCTL_IOCTL_CONTROLLER_H
#define IOCTL_IOCTL_CONTROLLER_H

#include "../bfpair.h"
#include <vector>

namespace host::interface
{
    /// IOCTL Controller
    ///
    /// This class is responsible for controlling the VMM including:
    /// - loading the VMM
    /// - unloading the VMM
    /// - starting the VMM
    /// - stopping the VMM
    ///
    template<typename T>
    struct ioctl_controller
    {
        /// Load VMM
        ///
        /// Loads a VMM from an ELF "file" with a heap size of "heap_size".
        ///
        /// @param file the ELF file that contains the VMM logic to load
        /// @param heap_size the size of the heap to give to the VMM
        ///
        constexpr auto
        load_vmm(const std::vector<char> &file, size_t heap_size) -> void
        {
            expects(!file.empty());
            expects(heap_size > 0);

            T::details(this).load_vmm(file, heap_size);
        }

        /// Unload VMM
        ///
        /// Tells the kernel driver to unload a previously loaded VMM
        ///
        constexpr auto
        unload_vmm() -> void
        {
            T::details(this).unload_vmm();
        }

        /// Start VMM
        ///
        /// Tells the kernel driver to start a previously loaded VMM.
        ///
        constexpr auto
        start_vmm() -> void
        {
            T::details(this).start_vmm();
        }

        /// Stop VMM
        ///
        /// Tells the kernel driver to stop a previously started VMM.
        ///
        constexpr auto
        stop_vmm() -> void
        {
            T::details(this).stop_vmm();
        }
    };

}    // namespace host::interface

namespace host
{
    template<typename D>
    using ioctl_controller = bfpair<interface::ioctl_controller, D>;
}

#endif
