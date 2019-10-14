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

#ifndef IOCTL_DETAILS_COMMON_IOCTL_DEBUG_H
#define IOCTL_DETAILS_COMMON_IOCTL_DEBUG_H

#include <ioctl/ioctl_debug.h>
#include <common/details/ioctl_debug.h>

namespace host::details::common
{

class ioctl_debug
{
public:
    auto to_string(
        const debug_ring_t &dr)
    -> std::string
    {
        if (dr.spos == dr.epos) {
            return {};
        }

        std::string str;

        auto view = gsl::span(dr.buf);
        auto spos = dr.spos;
        auto epos = dr.epos;

        while (spos != epos) {
            str += view[spos++];

            if (spos >= view.size()) {
                spos = 0;
            }
        }

        return str;
    }
};

}

#endif
