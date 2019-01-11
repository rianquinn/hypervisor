//
// Bareflank Hypervisor
// Copyright (C) 2018 Assured Information Security, Inc.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#ifndef BFVMM_DELEGATOR_CPUID_INTEL_X64_H
#define BFVMM_DELEGATOR_CPUID_INTEL_X64_H

#include <stdint.h>
#include <bfdelegate.h>
#include <bfgsl.h>
#include <bftypes.h>
#include <unordered_map>
#include <list>

namespace bfvmm::intel_x64::cpuid
{

/// CPUID leaf data type
///
///
using leaf_t = uint64_t;

/// Info
///
/// This struct is created by cpuid::delegator::handle before being
/// passed to each registered handler.
///
struct info_t {

    /// RAX (in/out)
    ///
    uint64_t rax;

    /// RBX (in/out)
    ///
    uint64_t rbx;

    /// RCX (in/out)
    ///
    uint64_t rcx;

    /// RDX (in/out)
    ///
    uint64_t rdx;

    /// Ignore write (out)
    ///
    /// If true, do not update the guest's register state with the four
    /// register values above. Set this to true if you do not want the guest
    /// rax, rbx, rcx, or rdx to be written to after your handler completes.
    ///
    /// default: false
    ///
    bool ignore_write;

    /// Ignore advance (out)
    ///
    /// If true, do not advance the guest's instruction pointer.
    /// Set this to true if your handler returns true and has already
    /// advanced the guest's instruction pointer.
    ///
    /// default: false
    ///
    bool ignore_advance;
};

using delegate_t = delegate<bool(vcpu_t, info_t &)>;
#define handler(function) delegate_t::create<function>()
#define stateful_handler(class, object, member) delegate_t::create<class, &class::member>(object)

class delegator
{

public:

    delegator();

    ~delegator() = default;

    void add_handler(leaf_t leaf, const delegate_t &d);

    bool handle(vcpu_t vcpu);

private:

    std::unordered_map<cpuid::leaf_t, std::list<cpuid::delegate_t>> m_handlers;
    cpuid::delegate_t m_default_handler;
    // std::unordered_map<leaf_t, bool> m_emulate;

public:

    /// @cond

    delegator(delegator &&) = default;
    delegator &operator=(delegator &&) = default;

    delegator(const delegator &) = delete;
    delegator &operator=(const delegator &) = delete;

    /// @endcond
};

}

#endif
