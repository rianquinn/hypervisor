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

#ifndef PAPIS_VCPU_INTEL_X64_H
#define PAPIS_VCPU_INTEL_X64_H

#include "../../macros.h"
#include "../../../uapis/vcpu.h"

namespace bfvmm::papis::intel_x64
{

template<typename IMPL>
class vcpu :
    public uapis::vcpu<IMPL>
{
    PRIVATE_INTERFACES(vcpu)

public:

    using id_t = typename IMPL::id_t;

    explicit vcpu(id_t id) :
        uapis::vcpu<IMPL>{id},
        m_impl{id}
    { }

    static constexpr void global_init()
    { return IMPL::global_init(); }

    constexpr void demote()
    { }

    constexpr void promote()
    { }
};

}

#endif
