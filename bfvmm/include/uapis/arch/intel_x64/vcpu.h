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

#ifndef UAPIS_VCPU_INTEL_X64_H
#define UAPIS_VCPU_INTEL_X64_H

#include "../../../papis/arch/intel_x64/vcpu.h"
#include "../../../uapis/vcpu_manager.h"

// -----------------------------------------------------------------------------
// vCPU (Intel x64) Interface Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::uapis::intel_x64
{

/// Intel x64 vCPU
///
/// This is the main vCPU that you will likely end up using when working on
/// Intel based systems. In addition, most of the APIs that you will need
/// (at least the ones that Bareflank supports) are exposed through this vCPU.
/// Please note that this file doesn't contain all of the APIs, but instead
/// most of the APIs are documented in the "uapis" folder, and these APIs are
/// callable from the vCPU (with some exceptions like the memory manager). To
/// see all of the APIs, make sure you read through the "uapis" folder to see
/// what is available.
///
template<typename IMPL>
class vcpu :
    public papis::intel_x64::vcpu<IMPL>
{
public:

    /// @cond

    using id_t = typename papis::intel_x64::vcpu<IMPL>::id_t;

    /// @endcond

public:

    /// Default Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    explicit vcpu(id_t id) :
        papis::intel_x64::vcpu<IMPL>{id}
    { }

    /// Make vCPU
    ///
    /// Creates a new vCPU given an id. Note that generally speaking, you
    /// should create new vCPU using the vCPU manager and not this function
    /// as the vCPU manager will store the vCPU for you as well as provide a
    /// mechanism for getting the vCPU later. This can however be used if
    /// you wish to manage the vCPUs yourself.
    ///
    /// Also note that the id you pick matters. We currently do not support
    /// creating host vCPUs (only guest vCPUs). Host vCPUs are created for
    /// you when the VMM is being bootstrapped and turned on. To get an id
    /// to create guest vCPUs, use the generate_guest_id() function.
    ///
    static inline auto make(id_t id)
    { return std::make_unique<vcpu>(id); }
};

}

#endif
