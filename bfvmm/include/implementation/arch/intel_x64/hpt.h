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

#ifndef IMPLEMENTATION_CR3_INTEL_X64_H
#define IMPLEMENTATION_CR3_INTEL_X64_H

#include <mutex>

#include <bfgsl.h>
#include <bftypes.h>

// -----------------------------------------------------------------------------
// Definition (Host Page Tables)
// -----------------------------------------------------------------------------

namespace bfvmm::implementation::intel_x64
{

class hpt
{
    using phys_addr_type = uint64_t;
    using virt_addr_type = uint64_t;
    using size_type = size_t;
    using entry_type = uint64_t;
    using index_type = std::ptrdiff_t;

    enum class attr_type {
        read_write,
        read_execute,
        read_write_execute
    };

    enum class memory_type {
        uncacheable,
        write_back
    };

    struct pair {
        gsl::span<virt_addr_type> virt_addr{};
        phys_addr_type phys_addr{};
    };

PUBLIC:
    hpt() noexcept;
    ~hpt() = default;

PRIVATE:
    uint64_t cr3();

    entry_type &map_1g(
        void *virt_addr,
        phys_addr_type phys_addr,
        attr_type attr = attr_type::read_write,
        memory_type cache = memory_type::write_back);

    entry_type &map_2m(
        void * virt_addr,
        phys_addr_type phys_addr,
        attr_type attr = attr_type::read_write,
        memory_type cache = memory_type::write_back);

    entry_type &map_4k(
        void * virt_addr,
        phys_addr_type phys_addr,
        attr_type attr = attr_type::read_write,
        memory_type cache = memory_type::write_back);

    void unmap(void * virt_addr);

PRIVATE:
    void map_pdpt(index_type pml4i);
    void map_pd(index_type pdpti);
    void map_pt(index_type pdi);

    entry_type &map_pdpte(
        void *virt_addr, phys_addr_type phys_addr, attr_type attr, memory_type cache);
    entry_type &map_pde(
        void *virt_addr, phys_addr_type phys_addr, attr_type attr, memory_type cache);
    entry_type &map_pte(
        void *virt_addr, phys_addr_type phys_addr, attr_type attr, memory_type cache);

    bool unmap_pdpte(void *virt_addr);
    bool unmap_pde(void *virt_addr);
    bool unmap_pte(void *virt_addr);

PRIVATE:
    pair m_pml4;
    pair m_pdpt;
    pair m_pd;
    pair m_pt;

    mutable std::mutex m_mutex;

PRIVATE:
    hpt(hpt &&) = default;
    hpt &operator=(hpt &&) = default;
    hpt(const hpt &) = delete;
    hpt &operator=(const hpt &) = delete;

PRIVATE:
    friend class implementation::setup;
};

}

#endif
