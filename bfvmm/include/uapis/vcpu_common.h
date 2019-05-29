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

#ifndef UAPIS_VCPU_COMMON_H
#define UAPIS_VCPU_COMMON_H

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
    /// return on success and throws on failure.
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
    { return impl<IMPL>(this)->__arch_run(); }

    /// Advance vCPU Instruction Pointer
    ///
    /// This function will advance the vCPU's instruction pointer to the next
    /// instruction.
    ///
    /// Also note that this function always returns true. Most extensions will
    /// not need to execute this function manually, and instead the base will
    /// execute this for you. If you do need to execute this manually, it
    /// should be paired, in most cases, with a "return" indicating that the
    /// handler is done, and no other handlers should execute. In most cases,
    /// extensions will return false in an exit handler indicating that the
    /// base should complete the exit.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return always returns true
    ///
    CONSTEXPR bool advance_ip()
    { return impl<const IMPL>(this)->__arch_advance_ip(); }

    /// Load
    ///
    /// This function loads the vCPU. This is not the same thing as run().
    /// Loading a vCPU allows the vCPUs state to be changed. Some state can be
    /// changed without the need for a load(), which is architecture dependent.
    /// This function should only be used when needed as it is expensive.
    ///
    /// @expects none
    /// @ensures none
    ///
    CONSTEXPR void load()
    { impl<const IMPL>(this)->__arch_load(); }

    /// Clear
    ///
    /// This function clears the vCPU. Note that this does not 0 out the vCPU's
    /// state. It simply tells the vCPU to relaunch itself on the next run().
    /// On some archiectures, this might do nothing. On Intel, this executes a
    /// VMCLear instruction.
    ///
    /// @expects none
    /// @ensures none
    ///
    CONSTEXPR void clear()
    { impl<const IMPL>(this)->__arch_clear(); }
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
