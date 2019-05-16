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

#ifndef IMPLMENETATION_VCPU_INTEL_X64_H
#define IMPLMENETATION_VCPU_INTEL_X64_H

// -----------------------------------------------------------------------------
// vCPU Type
// -----------------------------------------------------------------------------

namespace bfvmm::implementation::intel_x64
{ class vcpu; }

#ifndef VCPU_T
#define VCPU_T
using vcpu_t = bfvmm::implementation::intel_x64::vcpu;
#endif

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------

#include "../../vcpu_base.h"

// #include "uapis/cpuid.h"
// #include "uapis/exit_handler.h"
// #include "uapis/state.h"
// #include "uapis/vmcs.h"

// #include "cpuid.h"
// #include "exit_handler.h"
#include "state.h"
// #include "vmcs.h"
#include "vmx.h"

#include <bfdebug.h>

// -----------------------------------------------------------------------------
// Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::implementation::intel_x64
{

class vcpu :
    public implementation::vcpu_base,
    public implementation::intel_x64::vmx,
    public implementation::intel_x64::state
{
public:
    explicit vcpu(id_t id);

private:
    static void global_init();

    inline void demote()
    { bfdebug_info(0, "host os is" bfcolor_green " now " bfcolor_end "in a vm"); }

    inline void promote()
    { bfdebug_info(0, "host os is" bfcolor_red " not " bfcolor_end "in a vm"); }

    static inline auto make(id_t id)
    { return std::make_unique<vcpu>(id); }

private:
    FRIEND_DEFINITIONS(vcpu)
};

}

#endif
