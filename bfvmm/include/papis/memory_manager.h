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

#ifndef PAPIS_MEMORY_MANAGER_H
#define PAPIS_MEMORY_MANAGER_H

#include <bfmemory.h>
#include <bfconstants.h>

#ifndef ENABLE_BUILD_TEST
#include "../implementation/memory_manager.h"
#else
#include "../../tests/memory_manager.h"
#endif

namespace bfvmm::papis
{

template<typename IMPL>
class memory_manager
{
    PRIVATE_INTERFACES(memory_manager)

public:

    using pointer = typename IMPL::pointer;
    using integer_pointer = typename IMPL::integer_pointer;
    using size_type = typename IMPL::size_type;
    using attr_type = typename IMPL::attr_type;

    explicit memory_manager() = default;

private:

    inline pointer alloc(size_type size) noexcept
    { return m_impl.alloc(size); }
    inline pointer alloc_map(size_type size) noexcept
    { return m_impl.alloc_map(size); }
    inline pointer alloc_huge(size_type size) noexcept
    { return m_impl.alloc_huge(size); }

    inline void free(pointer ptr) noexcept
    { m_impl.free(ptr); }
    inline void free_map(pointer ptr) noexcept
    { m_impl.free_map(ptr); }
    inline void free_huge(pointer ptr) noexcept
    { m_impl.free_huge(ptr); }

    inline size_type size(pointer ptr) const noexcept
    { return m_impl.size(ptr); }
    inline size_type size_map(pointer ptr) const noexcept
    { return m_impl.size_map(ptr); }
    inline size_type size_huge(pointer ptr) const noexcept
    { return m_impl.size_huge(ptr); }

    friend void *::_malloc_r(struct _reent *ent, size_t size);
    friend void ::_free_r(struct _reent *ent, void *ptr);
    friend void *::_calloc_r(struct _reent *ent, size_t nmemb, size_t size);
    friend void *::_realloc_r(struct _reent *ent, void *ptr, size_t size);
    friend void *::alloc_page() noexcept;
    friend void ::free_page(void *ptr) noexcept;
};

}

#endif
