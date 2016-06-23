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

#include <test.h>
#include <stdlib.h>
#include <memory_manager/page_table_x64.h>
#include <memory_manager/memory_manager.h>

void *
malloc_aligned(size_t size, uint64_t alignment)
{
    void *ptr = 0;
    posix_memalign(&ptr, alignment, size);
    return ptr;
}

void *
virt_to_phys(void *)
{
    static uintptr_t phys = 0x0000000ABCDEF0000;
    return (void *)(phys + 0x1000);
}

void
memory_manager_ut::test_page_table_x64_add_page_success()
{
    MockRepository mocks;
    auto mm = mocks.Mock<memory_manager>();
    mocks.OnCallFunc(memory_manager::instance).Return(mm);

    mocks.OnCall(mm, memory_manager::malloc_aligned).Do(malloc_aligned);
    mocks.OnCall(mm, memory_manager::virt_to_phys).Do(virt_to_phys);


    RUN_UNITTEST_WITH_MOCKS(mocks, [&]
    {
        auto virt = 0x0000123456780000;
        auto pml4 = std::make_shared<page_table_x64>();

        for (auto i = 0; i < 4096; i++)
        {
            std::cout << "i: " << i << std::endl;
            pml4->add_page(0x0, (void *)(virt + (i * 0x1000)));
        }
    });

    // EXPECT_TRUE(false);
}
