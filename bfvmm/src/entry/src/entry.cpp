//
// Bareflank Hypervisor
//
// Copyright (C) 2015 Assured Information Security, Inc.
// Author: Rian Quinn        <quinnr@ainfosec.com>
// Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
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

#include <string.h>
#include <vmm_entry.h>

#include <std/iostream>
#include <debug_ring/debug_ring.h>
#include <memory_manager/memory_manager.h>

#include <vmm/vmm_intel_x64.h>

// =============================================================================
// Singleton Factories
// =============================================================================

debug_ring_base *
get_debug_ring()
{
    return &debug_ring::instance();
}

memory_manager_base *
get_memory_manager()
{
    return &memory_manager::instance();
}

intrinsics_base *
get_intrinsics()
{
    return &intrinsics_intel_x64::instance();
}

vmm_base *
get_vmm()
{
    return &vmm_intel_x64::instance();
}

// =============================================================================
// Entry Functions
// =============================================================================

void *
start_vmm(void *arg)
{
    vmm_resources_t *vmmr = (vmm_resources_t *)arg;

    if (arg == 0)
        return VMM_ERROR_INVALID_ARG;

    debug_ring_base *dr = get_debug_ring();
    memory_manager_base *mm = get_memory_manager();
    intrinsics_base *intrinsics = get_intrinsics();
    vmm_base *vmm = get_vmm();

    if (dr == 0 || mm == 0 || intrinsics == 0 || vmm == 0)
        return VMM_ERROR_INVALID_FACTORY;

    if (dr->init(vmmr->drr) != debug_ring_error::success)
        return VMM_ERROR_DEBUG_RING_INIT_FAILED;

    std::cout.init();

    if (mm->init() != memory_manager_error::success)
        return VMM_ERROR_MEMORY_MANAGER_INIT_FAILED;

    for (auto i = 0; i < MAX_PAGES; i++)
    {
        auto pg = page(vmmr->pages[i]);

        if (mm->add_page(pg) != memory_manager_error::success)
            return VMM_ERROR_INVALID_PAGES;
    }

    if (vmm->init(intrinsics, mm) != vmm_error::success)
        return VMM_ERROR_VMM_INIT_FAILED;

    if (vmm->start() != vmm_error::success)
        return VMM_ERROR_VMM_START_FAILED;

    return 0;
}

void *
stop_vmm(void *arg)
{
    if (arg != 0)
        return VMM_ERROR_INVALID_ARG;

    return 0;
}

// =============================================================================
// C++ Support Functions
// =============================================================================

void operator delete(void *ptr)
{
}

void operator delete[](void *p)
{
}

extern "C"
{

    void __cxa_pure_virtual()
    {
    }

    int atexit(void (*func)(void))
    {
        return 0;
    }

}
