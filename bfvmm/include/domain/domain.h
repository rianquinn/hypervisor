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

#ifndef BFVMM_DOMAIN_H
#define BFVMM_DOMAIN_H

#include <bftypes.h>
#include <bfobject.h>
#include <bfgsl.h>
#include <bfarch.h>
#include <bfvcpuid.h>
#include <list>

#include "../vcpu/vcpu.h"

// -----------------------------------------------------------------------------
// Exports
// -----------------------------------------------------------------------------

#include <bfexports.h>

#ifndef BFVMM_STATIC_DOMAIN
#ifdef BFVMM_SHARED_DOMAIN
#define BFVMM_EXPORT_DOMAIN EXPORT_SYM
#else
#define BFVMM_EXPORT_DOMAIN IMPORT_SYM
#endif
#else
#define BFVMM_EXPORT_DOMAIN
#endif

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

namespace bfvmm
{

/// Domain
///
class BFVMM_EXPORT_DOMAIN domain : public bfobject
{
public:

    using domainid_type = uint64_t;

public:

    /// Constructor
    ///
    /// @expects
    /// @ensures
    ///
    domain(domainid_type domainid);

    /// Destructor
    ///
    /// @expects
    /// @ensures
    ///
    virtual ~domain() = default;

    /// Run
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param obj object that can be passed around as needed
    ///     by extensions of Bareflank
    ///
    VIRTUAL void run(bfobject *obj = nullptr);

    /// Halt
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param obj object that can be passed around as needed
    ///     by extensions of Bareflank
    ///
    VIRTUAL void hlt(bfobject *obj = nullptr);

    /// Init vCPU
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param obj object that can be passed around as needed
    ///     by extensions of Bareflank
    ///
    VIRTUAL void init(bfobject *obj = nullptr);

    /// Fini vCPU
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param obj object that can be passed around as needed
    ///     by extensions of Bareflank
    ///
    VIRTUAL void fini(bfobject *obj = nullptr);

    /// Get ID
    ///
    /// @expects
    /// @ensures
    ///
    /// @return Returns the domain ID
    ///
    domainid_type id() const noexcept;

    /// Generate Domain ID
    ///
    /// @expects
    /// @ensures
    ///
    /// @return Returns a new, unique domain id
    ///
    static domainid_type generate_domainid()
    {
        static domainid_type s_id = 1;
        return s_id++;
    }

    void add_vcpu(vcpu_t vcpu)
    {
        m_vcpus.push_back(vcpu);
    }

    std::list<vcpu_t>
    vcpus()
    {
        return m_vcpus;
    }

private:

    domainid_type m_id;
    std::list<vcpu_t> m_vcpus;

public:

    /// @cond

    domain(domain &&) = default;
    domain &operator=(domain &&) = default;

    domain(const domain &) = delete;
    domain &operator=(const domain &) = delete;

    /// @endcond
};

// -----------------------------------------------------------------------------
// Constants
// -----------------------------------------------------------------------------

constexpr domain::domainid_type invalid_domainid = 0xFFFFFFFFFFFFFFFF;

}

#if defined(BF_INTEL_X64)
#include "../hve/arch/intel_x64/domain.h"
#else
#   error "domain.h: unsupported architecture"
#endif

#endif
