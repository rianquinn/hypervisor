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

#include <debug.h>
#include <string.h>
#include <memory_manager/memory_manager.h>
#include <memory_manager/page_table_x64.h>

page_table_x64::page_table_x64()
{
    m_table = std::unique_ptr<uintptr_t[]>((uintptr_t *)g_mm->malloc_aligned(4096, 4096));
    memset(m_table.get(), 0, 4096);
}

page_table_x64::page_table_x64(uintptr_t *entry) :
    page_table_entry_x64(entry)
{
    m_table = std::unique_ptr<uintptr_t[]>((uintptr_t *)g_mm->malloc_aligned(4096, 4096));
    memset(m_table.get(), 0, 4096);
}

std::shared_ptr<page_table_entry_x64>
page_table_x64::add_page(void *phys_addr, void *virt_addr)
{
    return add_page_with_mask((uintptr_t)phys_addr, (uintptr_t)virt_addr, 39);
}

uintptr_t
page_table_x64::virt_addr() const
{
    return (uintptr_t)m_table.get();
}

uintptr_t
page_table_x64::phys_addr() const
{
    auto addr = g_mm->virt_to_phys(m_table.get());

    if (addr == nullptr)
        throw std::logic_error("phys_addr: virt_to_phys failed");

    return (uintptr_t)addr;
}

std::shared_ptr<page_table_entry_x64>
page_table_x64::add_page_with_mask(uintptr_t phys_addr, uintptr_t virt_addr, uint64_t bits)
{
    auto index = (virt_addr & ((0x1FFULL) << bits)) >> bits;

    if (bits > 12)
    {
        if (index >= 512)
            throw std::out_of_range("add_page_with_mask: index >= 512");

        auto entry = std::dynamic_pointer_cast<page_table_x64>(m_entries[index]);

        if (!m_entries[index])
        {
            entry = std::make_shared<page_table_x64>(&m_table[index]);

            m_table[index] = entry->phys_addr();
            m_table[index] &= 0x000FFFFFFFFFF000;
            m_table[index] |= 0x0000000000000003;

            m_entries[index] = entry;
        }

        return entry->add_page_with_mask(phys_addr, virt_addr, bits - 9);
    }
    else
    {
        if (index >= 512)
            throw std::out_of_range("add_page_with_mask: index >= 512");

        if (m_entries[index])
            throw std::logic_error("add_page_with_mask: page mapping already exists");

        m_entries[index] = std::make_shared<page_table_entry_x64>(&m_table[index]);

        m_table[index] = phys_addr;
        m_table[index] &= 0x000FFFFFFFFFF000;
        m_table[index] |= 0x0000000000000003;

        return m_entries[index];
    }
}
