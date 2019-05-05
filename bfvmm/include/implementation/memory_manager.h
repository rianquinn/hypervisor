//
// Copyright (C) 2019 Assured Information Security, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef IMPLEMENTATION_MEMORY_MANAGER_H
#define IMPLEMENTATION_MEMORY_MANAGER_H

#include "../papis/macros.h"

#include "buddy_allocator.h"
#include "object_allocator.h"

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

void *alloc_page() noexcept;
void free_page(void *ptr) noexcept;

template<typename T> T *alloc_page()
{ return static_cast<T *>(alloc_page()); }

extern "C" status_t set_huge_pool_leafs(uint64_t addr, uint64_t size) noexcept;
extern "C" status_t set_huge_pool_nodes(uint64_t addr, uint64_t size) noexcept;

// -----------------------------------------------------------------------------
// Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::implementation
{

class memory_manager
{
public:

    using pointer = void *;
    using integer_pointer = uintptr_t;
    using size_type = std::size_t;
    using attr_type = decltype(memory_descriptor::type);

    memory_manager() noexcept;

    pointer alloc(size_type size) noexcept;
    pointer alloc_map(size_type size) noexcept;
    pointer alloc_huge(size_type size) noexcept;

    void free(pointer ptr) noexcept;
    void free_map(pointer ptr) noexcept;
    void free_huge(pointer ptr) noexcept;

    size_type size(pointer ptr) const noexcept;
    size_type size_map(pointer ptr) const noexcept;
    size_type size_huge(pointer ptr) const noexcept;

    integer_pointer hva_to_hpa(integer_pointer hva) const;
    integer_pointer hpa_to_hva(integer_pointer hpa) const;

    void add_md(integer_pointer hva,integer_pointer hpa,attr_type attr);

private:

    struct hva_t {
        integer_pointer hpa;
        integer_pointer attr;
    };

    struct hpa_t {
        integer_pointer hva;
        integer_pointer attr;
    };

    std::unordered_map<integer_pointer, hva_t> m_hva_lookup;
    std::unordered_map<integer_pointer, hpa_t> m_hpa_lookup;

    buddy_allocator g_map_pool;
    buddy_allocator g_huge_pool;

    object_allocator slab008;
    object_allocator slab010;
    object_allocator slab018;
    object_allocator slab020;
    object_allocator slab030;
    object_allocator slab040;
    object_allocator slab080;
    object_allocator slab100;
    object_allocator slab200;
    object_allocator slab400;
    object_allocator slab800;

public:
    MOCK_PROTOTYPE(memory_manager)
    COPY_MOVE_SEMANTICS(memory_manager)
};

}

#endif
