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

#include "../papis/vcpu.h"

// -----------------------------------------------------------------------------
// vCPU Definition
// -----------------------------------------------------------------------------

namespace bfvmm::uapis
{

/// Virtual CPU
///
/// To understand what a vCPU is we will need to define some types. Although
/// Bareflank is designed to work with multiple CPU archiectures, the names
/// mostly come from Intel with some mods to make things easier to understand.
///
/// - host: the host is the thing that is executed in ring-1. From an Intel
///   point of view, the host is the collection of exit handlers. It is not
///   all of the code in the "bfvmm" folder as some of that code is run
///   outside of the host. It is simply the code running on the CPU with the
///   highest privileges. It also has its own state including its own page
///   tables, memory etc... When running in the host, DO NOT ASSUME you can
///   access any resource (e.g. memory, kernel function calls, etc...) outside
///   the host. The host is its own isolated entity that does not have access
///   to anything outside of itself unless you explicitly grant it access to
///   other resources.
///
/// - pCPU: A physical CPU. On systems with hyperthreading this is actually
///   a thread, but on systems without hyperthraeding, or hyperthreading
///   disabled, the pCPU is a real-life core.
///
/// - vCPU: a virtual CPU is a virtual representation of a CPU. Another way
///   of looking at it is, a vCPU stores all of the state for a pCPU and allows
///   a hypervisor to swap states on the pCPU from one state to another. This
///   provides the hypervisor with a means to execute multiple operating
///   systems on the same pCPU at the same time.
///
/// - host OS: the host OS is the OS responsible for managing the system.
///   Another way of looking at it is, the host OS is the thing that starts
///   the VMM. When this occurs, all of the physical CPUs are given virtual
///   vCPUs by demoting the host OS (i.e. running the host OS in a VM). Once
///   the VMM is running, the host OS is free to do what it wants, including
///   starting other operating systems (e.g. UEFI starting Linux or Windows).
///
/// - host vCPU: A host vCPU is a vCPU that stores the state for the host OS.
///   It is a vCPU that executes the host OS. There is one host vCPU for every
///   pCPU on the system and host vCPUs should not be created by the user.
///   These are managed by Bareflank.
///
/// - guest vCPU: A guest vCPU is any vCPU that is not a host vCPU. Guest
///   vCPUs can be used to create guest VMs, containerization, etc... There
///   is no limit. Another way of looking at a guest vCPU is a guest vCPU is
///   any vCPU that the user of these APIs creates themselves. If you are
///   using Bareflank to reverse engineer without the help of guest VMs, you
///   are only using host vCPUs. To work with a guest vCPU you have to create
///   it first. Guest vCPUs are also not automatically given host state. For
///   example, when using Bareflank's APIs if you add a handler to a guest
///   vCPU, the handler will be ignored in cases where emulation is possible.
///   In these cases, you must add emulation handles and explicitly give the
///   guest vCPU host state.
///
/// - root: root is another way of saying host. If you are running in root,
///   you are running in the host (i.e. ring-1), which must has originated
///   from an exit handler.
///
/// - nonroot: nonroot is another way of saying anything that is not in root.
///   For example, any code running in an OS kernel, or userspace is in
///   nonroot.
///
template<typename IMPL>
class vcpu :
    public papis::vcpu<IMPL>
{
public:

    /// @cond

    using id_t = typename papis::vcpu<IMPL>::id_t;

    /// @endcond

public:

    /// Constructor
    ///
    /// Creates a vCPU with the provided id.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param id the id of the vcpu
    ///
    explicit vcpu(id_t id) :
        papis::vcpu<IMPL>{id}
    { }

    /// vCPU Id
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return the vCPU's id
    ///
    constexpr id_t id() const noexcept
    { return this->m_impl.id(); }

    /// Generate Guest vCPU Id
    ///
    /// @expects
    /// @ensures
    ///
    /// @return returns a new, unique guest vcpu id
    ///
    constexpr static id_t generate_guest_id() noexcept
    { return IMPL::generate_guest_id(); }

    /// Is Bootstrap vCPU
    ///
    /// The bootstrap vCPU is the vCPU that has a vCPU id of 0. This is the
    /// first vCPU created and it is the last vCPU destroyed when the host is
    /// being promoted. It is possible for the bootstrap vCPU not to be the
    /// last vCPU destroyed if you are managing guest vCPUs.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return true if this vCPU is the bootstrap vCPU, false otherwise
    ///
    constexpr bool is_bootstrap_vcpu() const noexcept
    { return this->m_impl.is_bootstrap_vcpu(); }

    /// Is Host vCPU
    ///
    /// As a reminder, the "host" refers to the VMM, while the "host OS"
    /// refers to the OS that is managing the system. A host vCPU is a
    /// vCPU that controls a physical CPU being used by the host OS. Host
    /// vCPUs cannot be migrated.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return true if the vCPU is a host vCPU
    ///
    constexpr bool is_host_vcpu() const noexcept
    { return this->m_impl.is_host_vcpu(); }

    /// Is Guest VM vCPU
    ///
    /// A guest vCPU is any vCPU that is not controlling a physical CPU
    /// used by the host OS. Guest vCPUs are not given state information from
    /// the host or host OS. Guest vCPUs also have special ids which should
    /// be created using generate_guest_id().
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return true if the vCPU is a host vCPU
    ///
    constexpr bool is_guest_vcpu() const noexcept
    { return this->m_impl.is_guest_vcpu(); }

    /// Get User Data
    ///
    /// Note, you must be explicit about whether you wish to get an l-value,
    /// r-value or reference.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns user data that is stored in the vCPU
    ///
    template<typename T>
    constexpr T data()
    { return this->m_impl.template data<T>(); }

    /// Set User Data
    ///
    /// Provides the ability for an extension to store data in the vCPU without
    /// having to subclass the vCPU if that is not desired in a type-safe way.
    /// It should be noted that this uses std::any which does perform a malloc.
    /// We also use the same API structure as std::any, so you need to be
    /// explicit about whether you wish to have an l-value, r-value or
    /// reference when using the get function.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param t the value to store
    ///
    template<typename T>
    constexpr void set_data(T &&t)
    { return this->m_impl.template set_data<T>(t); }
};

}

#endif
