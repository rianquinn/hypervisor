//
// Bareflank Hypervisor
// Copyright (C) 2015 Assured Information Security, Inc.
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

#ifndef DOMAIN_FACTORY_H
#define DOMAIN_FACTORY_H

#include <memory>
#include "domain.h"

// -----------------------------------------------------------------------------
// Exports
// -----------------------------------------------------------------------------

#include <bfexports.h>

#ifndef STATIC_DOMAIN
#ifdef SHARED_DOMAIN
#define EXPORT_DOMAIN EXPORT_SYM
#else
#define EXPORT_DOMAIN IMPORT_SYM
#endif
#else
#define EXPORT_DOMAIN
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

namespace bfvmm
{

/// Domain Factory
///
class EXPORT_DOMAIN domain_factory
{
public:

    /// Default Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    domain_factory() noexcept = default;

    /// Destructor
    ///
    /// @expects none
    /// @ensures none
    ///
    virtual ~domain_factory() = default;

    /// Make vCPU
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param domainid the domainid for the domain to create
    /// @param obj object passed to the domain
    /// @return returns a pointer to a newly created vCPU.
    ///
    virtual std::unique_ptr<domain> make(
        domain::domainid_type domainid, bfobject *obj = nullptr);

public:

    /// @cond

    domain_factory(domain_factory &&) noexcept = default;
    domain_factory &operator=(domain_factory &&) noexcept = default;

    domain_factory(const domain_factory &) = delete;
    domain_factory &operator=(const domain_factory &) = delete;

    /// @endcond
};

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
