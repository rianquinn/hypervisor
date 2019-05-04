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

#include <unordered_map>

#include "buddy_allocator.h"
#include "object_allocator.h"

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

extern "C" void *alloc_page();
extern "C" void free_page(void *ptr);

extern "C" int64_t set_huge_pool(uint64_t addr, uint64_t size) noexcept;
extern "C" status_t set_huge_pool_node_tree(uint64_t addr) noexcept;

// -----------------------------------------------------------------------------
// Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::implementation
{

class memory_manager
{
public:

    memory_manager() noexcept;
    ~memory_manager() = default;

    memory_manager_n::pointer alloc(
        memory_manager_n::size_type size) noexcept;
    memory_manager_n::pointer alloc_map(
        memory_manager_n::size_type size) noexcept;
    memory_manager_n::pointer alloc_huge(
        memory_manager_n::size_type size) noexcept;

    void free(memory_manager_n::pointer ptr) noexcept;
    void free_map(memory_manager_n::pointer ptr) noexcept;
    void free_huge(memory_manager_n::pointer ptr) noexcept;

    memory_manager_n::size_type size(
        memory_manager_n::pointer ptr) const noexcept;
    memory_manager_n::size_type size_map(
        memory_manager_n::pointer ptr) const noexcept;
    memory_manager_n::size_type size_huge(
        memory_manager_n::pointer ptr) const noexcept;

    memory_manager_n::integer_pointer hva_to_hpa(
        memory_manager_n::integer_pointer hva) const;

    memory_manager_n::integer_pointer hpa_to_hva(
        memory_manager_n::integer_pointer hpa) const;

    void add_md(
        memory_manager_n::integer_pointer hva,
        memory_manager_n::integer_pointer hpa,
        memory_manager_n::attr_type attr);

    void dump_stats() const noexcept;

private:

    struct hva_t {
        memory_manager_n::integer_pointer hpa;
        memory_manager_n::integer_pointer attr;
    };

    struct hpa_t {
        memory_manager_n::integer_pointer hva;
        memory_manager_n::integer_pointer attr;
    };

    std::unordered_map<memory_manager_n::integer_pointer, hva_t> m_hva_lookup;
    std::unordered_map<memory_manager_n::integer_pointer, hpa_t> m_hpa_lookup;

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
