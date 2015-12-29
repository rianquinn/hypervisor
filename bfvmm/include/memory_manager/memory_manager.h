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

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>
#include <stdint.h>
#include <memory.h>
#include <constants.h>

class memory_manager
{
public:

    /// Manager Constructor
    ///
    memory_manager();

    /// Destructor
    ///
    virtual ~memory_manager() {}

    virtual int64_t free_blocks();

    virtual void *malloc(size_t size);
    virtual void *malloc_aligned(size_t size, int64_t alignment);

    virtual void free(void *ptr);

    virtual void *virt_to_phys(void *virt);
    virtual void *phys_to_virt(void *phys);

    virtual int64_t add_mdl(struct memory_descriptor *mdl, int64_t num);

private:

    virtual void *block_to_virt(int64_t block);
    virtual int64_t virt_to_block(void *virt);

    virtual bool is_block_aligned(int64_t block, int64_t alignment);

private:

    uint32_t m_start;

    uint8_t m_mem_pool[MAX_MEM_POOL] __attribute__ ((aligned (MAX_PAGE_SIZE)));
    uint32_t m_block_allocated[MAX_BLOCKS];

    struct memory_descriptor m_mdl[MAX_NUM_MEMORY_DESCRIPTORS];
};

/// Get Memory Manager
///
/// We cannot use global memory since we don't have support for globally
/// constructor objects. Instead, we provide access to a globally defined
/// memory manager via a statically created global object with still provides
/// global access to a single memory manager, but allows the manager to be
/// properly constructed, and provides a simple means to test the class if
/// needed.
///
/// @return a pointer to the memory manager (never 0)
///
memory_manager *mm();

/// Add Memory Descriptor List
///
/// This is used by the driver entry to add an MDL to VMM. The driver entry
/// will need to collect memory descriptors for every page of memory that the
/// VMM is using so that the memory manager can provide mappings as needed.
///
/// @param mdl the memory descirptor list
/// @param num the number of memory diescriptors in the list
/// @return MEMORY_MANAGER_SUCCESS on success, MEMORY_MANAGER_FAILURE otherwise
///
extern "C" long long int add_mdl(struct memory_descriptor *mdl, long long int num);

#endif
