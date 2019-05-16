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

#ifndef UAPIS_VCPU_H
#define UAPIS_VCPU_H

#include <bfgsl.h>
#include <bftypes.h>

#include "impl.h"

// -----------------------------------------------------------------------------
// vCPU Notes
// -----------------------------------------------------------------------------

namespace bfvmm::uapis
{

/// vCPU Common
///
///
template<typename IMPL>
struct vcpu
{
    /// Run
    ///
    /// Executes the vCPU. On most architectures, this function will not
    /// return on success and throw on failure.
    ///
    /// Notes:
    ///
    /// This is an architural specific function, and how it is implemented
    /// depends on the implementation provided by the architecture. For more
    /// information, please see the arch/xxx/vcpu.h version of the vCPU for
    /// the architecture of interest.
    ///
    /// @expects none
    /// @ensures none
    ///
    constexpr void run()
    { return impl<IMPL>(this)->arch_run(); }
};

}

// -----------------------------------------------------------------------------
// Wrappers
// -----------------------------------------------------------------------------

/// @cond

namespace bfvmm::vcpu
{

template<typename IMPL>
constexpr auto id(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->id(); }

template<typename IMPL>
constexpr auto is_bootstrap_vcpu(
    gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->is_bootstrap_vcpu(); }

template<typename IMPL>
constexpr auto is_host_vcpu(
    gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->is_host_vcpu(); }

template<typename IMPL>
constexpr auto is_guest_vcpu(
    gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->is_guest_vcpu(); }

template<typename IMPL, typename T>
constexpr auto data(
    gsl::not_null<IMPL *> vcpu)
{ return vcpu->template data<T>(); }

template<typename IMPL, typename T, typename... Args>
constexpr void set_data(
    gsl::not_null<IMPL *> vcpu, Args &&...args)
{ vcpu->template set_data<T>(std::forward<Args>(args)...); }

}

/// @endcond

#endif
