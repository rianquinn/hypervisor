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

#ifndef VMMCTL_DEBUG_H
#define VMMCTL_DEBUG_H

#include "../bfpair.h"
#include <string>

namespace vmmctl
{
    /// Debug
    ///
    /// This class is responsible for aiding in the debugging of the VMM
    /// including:
    /// - dumpping the VMM's debug ring
    ///
    template<typename T>
    struct debug
    {
        /// Dump VMM
        ///
        /// Returns the contents of the VMM's debug ring in a std::string
        ///
        /// @return the contents of the VMM's debug ring
        ///
        auto
        dump_vmm() -> std::string
        {
            return T::details(this).dump_vmm();
        }
    };

}

namespace vmmctl
{
    template<typename D>
    using debug = bfpair<debug, D>;
}

#endif
