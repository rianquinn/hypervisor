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

#ifndef IMPLEMENTATION_OBJECT_ALLOCATOR_H
#define IMPLEMENTATION_OBJECT_ALLOCATOR_H

#include <bfgsl.h>
#include <bfconstants.h>

#include "../uapis/memory_manager.h"

// -----------------------------------------------------------------------------
// Constants
// -----------------------------------------------------------------------------

constexpr const auto pagepool_size = 255;
constexpr const auto objtpool_size = 255;

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

/// Object Allocator
///
/// The goals of this allocator includes:
/// - O(1) allocation time
/// - O(1) deallocation time
/// - No external fragmentation (internal fragmentation is allowed, and can
///   be high depending on the size of the object)
/// - All external allocations made by the object allocator are a page in size
///
/// To support these features, this allocator uses 4 different stacks.
/// - page stack: this stack stores a pool of page_t structures, each page_t
///   stores the address of a single page that can be used as a backing store
///   for allocations. Each page_stack_t can store 255 page_t structures before
///   anther page_stack_t has to be pushed to the stack
/// - object stack: this stack stores all of the object_t structures. Each
///   object_stack_t can store 255 object_t structures before another
///   object_stack_t has to be pushed to the stack. Each object_t stores an
///   address within a page_t's allocated page, in other words, the object_t
///   struct actually stores the memory that is given out by the allocator.
/// - free / used stacks: these stacks store the object_t structures based
///   on their current status. object_t structures ready to be allocated are
///   stored on the free stack, while object_t structures already allocated
///   are stored on the used stack. Each allocation / deallocation simply
///   moves a object_t structure from one stack to another.
///
/// Limitations:
/// - The largest allocation that can take place is a page. Any
///   allocation larger than this should use the buddy allocator
/// - To achieve O(1) deallocation times, deallocation does not check the
///   validity of the provided pointer. If the pointer provided was not
///   previously allocated using the same allocator, corruption is likely.
///
class object_allocator
{
public:
    using pointer = void *;
    using size_type = std::size_t;

public:
    object_allocator(size_type size) noexcept :
        m_size(size == 0 ? 1 : size)
    { }

    ~object_allocator() = default;

    inline pointer allocate() noexcept
    {
        auto objt = free_stack_pop();
        used_stack_push(objt);

        return objt->addr;
    }

    inline void deallocate(pointer p) noexcept
    {
        auto objt = used_stack_pop();
        free_stack_push(objt);

        objt->addr = p;
    }

    inline bool contains(pointer p) const noexcept
    {
        auto next = m_page_stack_top;

        while (next != nullptr) {

            for (auto i = 0LL; i < next->index; i++) {
                auto s = next->pool[i].addr;
                auto e = next->pool[i].addr + BFPAGE_SIZE;

                if (p >= s && p < e) {
                    return true;
                }
            }

            next = next->next;
        }

        return false;
    }

    inline size_type size(pointer ptr) const noexcept
    { bfignored(ptr); return m_size; }

private:
    struct object_t {
        pointer addr;
        object_t *next;
    };

    struct object_stack_t {
        object_t pool[objtpool_size];

        std::ptrdiff_t index;
        object_stack_t *next;
    };

    struct page_t {
        gsl::byte *addr;
        std::ptrdiff_t index;
    };

    struct page_stack_t {
        page_t pool[pagepool_size];

        std::ptrdiff_t index;
        page_stack_t *next;
    };

    object_t *m_free_stack_top{nullptr};
    object_t *m_used_stack_top{nullptr};

    page_stack_t *m_page_stack_top{nullptr};
    object_stack_t *m_objt_stack_top{nullptr};

private:
    inline page_t *get_next_page() noexcept
    {
        if (m_page_stack_top == nullptr || m_page_stack_top->index == pagepool_size) {
            expand_page_stack();
        }

        auto page = &gsl::at(m_page_stack_top->pool, m_page_stack_top->index);
        page->addr = alloc_page<gsl::byte>();
        page->index = 0;

        ++m_page_stack_top->index;
        return page;
    }

    inline object_t *get_next_object() noexcept
    {
        if (m_objt_stack_top == nullptr || m_objt_stack_top->index == objtpool_size) {
            expand_object_stack();
        }

        return &gsl::at(m_objt_stack_top->pool, m_objt_stack_top->index++);
    }

    inline void free_stack_push(object_t *next) noexcept
    {
        next->next = m_free_stack_top;
        m_free_stack_top = next;
    }

    inline object_t *free_stack_pop() noexcept
    {
        if (m_free_stack_top == nullptr) {
            add_to_free_stack();
        }

        auto top = m_free_stack_top;

        m_free_stack_top = m_free_stack_top->next;
        top->next = nullptr;

        return top;
    }

    inline void used_stack_push(object_t *next) noexcept
    {
        next->next = m_used_stack_top;
        m_used_stack_top = next;
    }

    inline object_t *used_stack_pop() noexcept
    {
        if (GSL_UNLIKELY(m_used_stack_top == nullptr)) {
            used_stack_push(get_next_object());
        }

        auto top = m_used_stack_top;

        m_used_stack_top = m_used_stack_top->next;
        top->next = nullptr;

        return top;
    }

    inline void expand_page_stack() noexcept
    {
        auto next = alloc_page<page_stack_t>();

        next->next = m_page_stack_top;
        m_page_stack_top = next;
    }

    inline void expand_object_stack() noexcept
    {
        auto next = alloc_page<object_stack_t>();

        next->next = m_objt_stack_top;
        m_objt_stack_top = next;
    }

    inline void add_to_free_stack() noexcept
    {
        auto page = get_next_page();

        for (auto i = 0ULL; i + m_size <= BFPAGE_SIZE; i += m_size) {
            auto object = get_next_object();
            free_stack_push(object);

            auto view = gsl::make_span(page->addr, BFPAGE_SIZE);
            object->addr = &view[gsl::index_cast(i)];
        }
    }

private:
    size_type m_size{};

public:
    object_allocator(object_allocator &&) noexcept = delete;
    object_allocator &operator=(object_allocator &&) noexcept = delete;
    object_allocator(const object_allocator &) = delete;
    object_allocator &operator=(const object_allocator &) = delete;
};

#endif
