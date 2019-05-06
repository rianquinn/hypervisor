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

#ifndef IMPLEMENTATION_VCPU_DUMMY_H
#define IMPLEMENTATION_VCPU_DUMMY_H

#include "../implementation/vcpu.h"

namespace bfvmm::implementation
{

class vcpu_dummy :
    public implementation::vcpu
{
public:

    using id_t = implementation::vcpu::id_t;

    explicit vcpu_dummy(id_t id) noexcept :
        implementation::vcpu{id}
    { }

    static void global_init()
    { }
    // { bfdebug_info(0, "global init"); }

    void demote()
    { bfdebug_info(0, "host os is" bfcolor_green " now " bfcolor_end "in a vm"); }

    void promote()
    { bfdebug_info(0, "host os is" bfcolor_red " not " bfcolor_end "in a vm"); }

    static inline auto make(id_t id)
    { return std::make_unique<vcpu_dummy>(id); }
};

}

using vcpu_t = bfvmm::implementation::vcpu_dummy;

#endif
