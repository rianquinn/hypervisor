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

#include <memory_manager/memory_manager.h>

// -----------------------------------------------------------------------------
// Macros
// -----------------------------------------------------------------------------

#define FREE_BLOCK (-1)

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

memory_manager::memory_manager()
{
    for (auto i = 0; i < MAX_MEM_POOL; i++)
        m_mem_pool[i] = 0;

    for (auto i = 0; i < MAX_BLOCKS; i++)
        m_block_allocated[i] = FREE_BLOCK;

    for (auto i = 0; i < MAX_NUM_MEMORY_DESCRIPTORS; i++)
        m_mdl[i] = {0};
}

void *
memory_manager::malloc(size_t size)
{
    return malloc_aligned(size, size == MAX_PAGE_SIZE ? MAX_PAGE_SIZE : 0);
}

void *
memory_manager::malloc_aligned(size_t size, int64_t alignment)
{
    if (size == 0)
        return 0;

    auto count = 0;
    auto block = 0;
    auto num_blocks = size / MAX_CACHE_LINE_SIZE;

    if (size % MAX_CACHE_LINE_SIZE != 0)
        num_blocks++;

    for (auto b = 0; b < MAX_BLOCKS && count < num_blocks; b++)
    {
        if (m_block_allocated[b] == FREE_BLOCK)
        {
            if (count == 0)
            {
                if (is_block_aligned(b, alignment) == false)
                    continue;

                block = b;
            }

            count++;
        }
        else
        {
            count = 0;
        }
    }

    if (count == num_blocks)
    {
        for (auto b = block; b < num_blocks; b++)
            m_block_allocated[b] = block;

        return block_to_virt(block);
    }

    return 0;
}

void
memory_manager::free(void *ptr)
{
    if (ptr == 0)
        return;

    auto block = virt_to_block(ptr);

    if (block < 0 || block >= MAX_BLOCKS)
        return;

    auto start = m_block_allocated[block];

    if (start < 0 || start >= MAX_BLOCKS)
        return;

    for (auto b = start; b < MAX_BLOCKS; b++)
    {
        if (m_block_allocated[b] != start)
            break;

        m_block_allocated[b] = FREE_BLOCK;
    }
}

void *
memory_manager::block_to_virt(int64_t block)
{
    if (block >= MAX_BLOCKS)
        return 0;

    return m_mem_pool + (block * MAX_CACHE_LINE_SIZE);
}

void *
memory_manager::virt_to_phys(void *virt)
{
    return 0;
}

void *
memory_manager::phys_to_virt(void *phys)
{
    return 0;
}

int64_t
memory_manager::virt_to_block(void *virt)
{
    if (virt >= m_mem_pool + MAX_MEM_POOL)
        return -1;

    return ((uint8_t *)virt - m_mem_pool) / MAX_CACHE_LINE_SIZE;
}

bool
memory_manager::is_block_aligned(int64_t block, int64_t alignment)
{
    if (block >= MAX_BLOCKS)
        return false;

    if (alignment <= 0)
        return true;

    return ((uint64_t)block_to_virt(block) % alignment) == 0;
}

int64_t
memory_manager::add_mdl(struct memory_descriptor *mdl, int64_t num)
{
    return MEMORY_MANAGER_SUCCESS;
}

memory_manager *mm()
{
    static memory_manager mm;
    return &mm;
}

int64_t
add_mdl_trampoline(struct memory_descriptor *mdl, int64_t num)
{
    return mm()->add_mdl(mdl, num);
}

extern "C" long long int
add_mdl(struct memory_descriptor *mdl, long long int num)
{
    return add_mdl_trampoline(mdl, num);
}
