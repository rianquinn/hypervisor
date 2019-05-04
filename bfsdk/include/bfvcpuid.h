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

#ifndef BFVCPUID_H
#define BFVCPUID_H

#include <bftypes.h>

namespace vcpuid
{

using type = uint64_t;

/// Is Bootstrap vCPU
///
/// @expects none
/// @ensures none
///
/// @param id the id to check
/// @return true if this vCPU is the bootstrap vCPU, false otherwise
///
constexpr bool is_bootstrap_vcpu(type id)
{ return id == 0; }

/// Is Host VM vCPU
///
/// @expects none
/// @ensures none
///
/// @param id the id to check
/// @return true if this vCPU belongs to the host VM, false otherwise
///
constexpr bool is_host_vcpu(type id)
{ return (id & 0xFFFFFFFFFFFF0000UL) == 0; }

/// Is Guest VM vCPU
///
/// @expects none
/// @ensures none
///
/// @param id the id to check
/// @return true if this vCPU belongs to a guest VM, false otherwise
///
constexpr bool is_guest_vcpu(type id)
{ return !is_host_vcpu(id); }

}

#endif
