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

#ifndef PAGE_TABLE_ENTRY_X64_H
#define PAGE_TABLE_ENTRY_X64_H

#include <stdint.h>

// -----------------------------------------------------------------------------
// Macros
// -----------------------------------------------------------------------------

#define PAGE_TABLE_SIZE 512

// -----------------------------------------------------------------------------
// Definition
// -----------------------------------------------------------------------------

class page_table_entry_x64
{
public:

    page_table_entry_x64() noexcept;

    page_table_entry_x64(uintptr_t *entry) noexcept;

    /// Destructor
    ///
    virtual ~page_table_entry_x64() {}

private:

    uintptr_t *m_entry;
};

#endif
