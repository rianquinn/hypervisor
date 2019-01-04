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

#ifndef DOMAIN_MANAGER_H
#define DOMAIN_MANAGER_H

#include <bfmanager.h>

#include "domain.h"
#include "domain_factory.h"

/// Domain Manager Macro
///
/// The following macro can be used to quickly call the domain manager as
/// this class will likely be called by a lot of code. This call is guaranteed
/// to not be NULL
///
/// @expects none
/// @ensures ret != nullptr
///
#define g_dm                                                                   \
    bfmanager<                                                                 \
    bfvmm::domain,                                                             \
    bfvmm::domain_factory,                                                     \
    bfvmm::domain::domainid_type>::instance()

#endif
