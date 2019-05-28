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
// vCPU Definition
// -----------------------------------------------------------------------------

namespace bfvmm::uapis
{

/// Virtual CPU (vCPU) Base
///
/// The general vCPU is broken up into two different generic interfaces, the
/// "base" and "common". The base provides the base APIs that are needed by
/// all of the vCPU APIs, which is why it exists in the first place. We need
/// this class because some of the functionality of the other APIs depends on
/// it to function properly. This functionality actually has an implementation
/// as part of it. The "common" APIs do not have an implementation. These are
/// APIs that architectural vCPUs have to provide, but all of them share in
/// common. For example, all vCPU have to provide a run() function as this is
/// the function that is used to execute a vCPU.
///
/// For more information about what a vCPU is, please see the entry.h file as
/// this has all of the documentation about a lot of the naming schemes that
/// are found in this file, as well as the common version of the vCPU. That
/// file should be read and well understood before continuing onto these APIs
/// as they will not make any sense without it.
///
template<typename IMPL>
struct vcpu_base
{
    using id_t = uint64_t;          ///< vCPU ip type

    /// vCPU Id
    ///
    /// @expects
    /// @ensures
    ///
    /// @return the vCPU's id
    ///
    CONSTEXPR id_t id() const noexcept
    { return impl<const IMPL>(this)->__id(); }

    /// Generate Guest vCPU Id
    ///
    /// If you are creating a vCPU, you should ALWAYS use this function to
    /// generate the ID. If you do not, the base APIs will execute host vCPU
    /// functions that are only meant to be executed once.
    ///
    /// @expects
    /// @ensures
    ///
    /// @return returns a new, unique guest vCPU id
    ///
    constexpr static id_t generate_guest_vcpu_id() noexcept
    { return IMPL::__generate_guest_vcpu_id(); }

    /// Is Bootstrap vCPU
    ///
    /// The bootstrap vCPU is the vCPU that has a vCPU id of 0. This is the
    /// first vCPU created and it is the last vCPU destroyed when the host is
    /// being promoted. It is possible for the bootstrap vCPU not to be the
    /// last vCPU destroyed if you are managing guest vCPUs.
    ///
    /// @expects
    /// @ensures
    ///
    /// @return true if this vCPU is the bootstrap vCPU, false otherwise
    ///
    CONSTEXPR bool is_bootstrap_vcpu() const noexcept
    { return impl<const IMPL>(this)->__is_bootstrap_vcpu(); }

    /// Is Host vCPU
    ///
    /// As a reminder, the "host" refers to the VMM, while the "host OS"
    /// refers to the OS that is managing the system. A host vCPU is a
    /// vCPU that controls a physical CPU being used by the host OS. Host
    /// vCPUs cannot be migrated.
    ///
    /// @expects
    /// @ensures
    ///
    /// @return true if the vCPU is a host vCPU
    ///
    CONSTEXPR bool is_host_vcpu() const noexcept
    { return impl<const IMPL>(this)->__is_host_vcpu(); }

    /// Is Guest VM vCPU
    ///
    /// A guest vCPU is any vCPU that is not controlling a physical CPU
    /// used by the host OS. Guest vCPUs are not given state information from
    /// the host or host OS. Guest vCPUs also have special ids which should
    /// be created using generate_guest_vm_id().
    ///
    /// @expects
    /// @ensures
    ///
    /// @return true if the vCPU is a host vCPU
    ///
    CONSTEXPR bool is_guest_vcpu() const noexcept
    { return impl<const IMPL>(this)->__is_guest_vcpu(); }

    /// Get User Data
    ///
    /// Note, you must be explicit about whether you wish to get an l-value,
    /// r-value or reference.
    ///
    /// @expects
    /// @ensures
    ///
    /// @return returns user data that is stored in the vCPU
    ///
    template<typename T>
    constexpr T data()
    { return impl<IMPL>(this)->template __data<T>(); }

    /// Set User Data
    ///
    /// Provides the ability for an extension to store data in the vCPU without
    /// having to subclass the vCPU if that is not desired in a type-safe way.
    /// It should be noted that this uses std::any which does perform a malloc.
    /// We also use the same API structure as std::any, so you need to be
    /// explicit about whether you wish to have an l-value, r-value or
    /// reference when using the get function.
    ///
    /// @expects
    /// @ensures
    ///
    /// @param t the value to store
    ///
    template<typename T, typename... Args>
    constexpr void set_data(Args &&...args)
    { impl<const IMPL>(this)->template set_data<T>(std::forward<Args>(args)...); }
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
