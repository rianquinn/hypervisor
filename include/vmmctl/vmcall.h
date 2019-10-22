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

#ifndef VMMCTL_VMCALL_H
#define VMMCTL_VMCALL_H

#include "../bfpair.h"

namespace vmmctl
{
    /// VMCall
    ///
    /// This class is responsible for talking to the VMM including
    /// - calling the VMM
    ///
    template<typename T>
    struct vmcall
    {
        /// Call
        ///
        /// Performs a VMCall to the VMM. This is used to communicate with
        /// the VMM from userspace. Note that this is the safer approach
        /// than trying to VMCall directly as this call ensures the VMM is
        /// loaded and running.
        ///
        /// @param reg1 depends on the call being made
        /// @param reg2 depends on the call being made
        /// @param reg3 depends on the call being made
        /// @param reg4 depends on the call being made
        /// @return depends on the call being made
        ///
        constexpr auto
        call(uint64_t reg1, uint64_t reg2, uint64_t reg3, uint64_t reg4)
            -> uint64_t
        {
            return T::details(this).call(reg1, reg2, reg3, reg4);
        }
    };

}

namespace vmmctl
{
    template<typename D>
    using vmcall = bfpair<vmcall, D>;
}

#endif
