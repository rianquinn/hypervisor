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

#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H

#include <bfgsl.h>
#include <bfdebug.h>
#include <bfconstants.h>

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

/// Round to Next Power of 2
///
/// http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
///
inline auto
next_power_2(uint32_t size) noexcept
{
    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size++;

    return size;
}

/// Log2N
///
inline auto
log2(uint32_t n)
{
    uint32_t val;
    for (val = 0; n > 1; val++, n >>= 1);

    return val;
}

// -----------------------------------------------------------------------------
// Buddy Allocator Definition
// -----------------------------------------------------------------------------

/// Buddy Allocator
///
/// The goals of this allocator includes:
/// - O(log2n) allocation time
/// - O(log2n) deallocation time
/// - No external fragmentation (internal fragmentation is allowed, and can
///   be high depending on the size of the object)
/// - All allocations are a multiple of a page
///
/// To support these features, this allocator uses 2 buffers.
/// - buffer: this is the main buffer that is allocated and returned. This
///   buffer must be page aligned, and a power of 2^k.
/// - node tree buffer: The node tree buffer stores the binary tree that keeps
///   track of each allocation.
///
class buddy_allocator
{
public:

    using pointer = void *;                 ///< Pointer type
    using integer_pointer = uintptr_t;      ///< Integer pointer type
    using size_type = uint32_t;             ///< Size type

private:

    /// @struct node
    ///
    /// This node is used to define the binary tree. child0 and child1 define
    /// the child nodes (left or right) in the binary tree. ptr stores the
    /// location in the provided buffer that this node refers to, and size
    /// defines the size of the allocation. The status tells us if the node
    /// is allocated or not.
    ///
    struct node_t {
        node_t *child0;
        node_t *child1;
        integer_pointer ptr;
        size_type size;
        size_type status;
    };

    static_assert(sizeof(node_t) == 32);

public:

    /// Pointer Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param buffer the buffer that the buddy allocator will manage. Note
    ///     that the buddy allocator will never dereference the address
    ///     provided here, allowing it to be used for virtual memory allocation
    /// @param k the size of the buffer using the formula:
    ///     (1ULL << k) * BAREFLANK_PAGE_SIZE
    /// @param node_tree the buffer that will be used to store the buddy
    ///     allocators binary tree. This buffer is assumed to be
    ///     buddy_allocator::node_tree_size(k).
    ///
    buddy_allocator(
        pointer buffer, size_type k, pointer node_tree) noexcept
    {
        m_buffer = reinterpret_cast<integer_pointer>(buffer);
        m_buffer_size = this->buffer_size(k);

        m_nodes = static_cast<node_t *>(node_tree);
        m_nodes_view = gsl::span<node_t>(
            m_nodes, gsl::index_cast(node_tree_size(k)));

        m_root = &m_nodes_view.at(gsl::index_cast(m_node_index++));
        m_root->ptr = m_buffer;
        m_root->size = m_buffer_size;
    }

    /// Destructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @note The destructor has to be a default as the buddy allocator could
    ///     be used as a global resource, and global destructors are not
    ///     fully supported.
    ///
    ~buddy_allocator() = default;

    /// Move Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param other the allocator being moved
    ///
    buddy_allocator(buddy_allocator &&other) noexcept
    { *this = std::move(other);}

    /// Move Operator
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param other the allocator being moved
    ///
    buddy_allocator &operator=(buddy_allocator &&other) noexcept
    {
        m_buffer = other.m_buffer;
        m_buffer_size = other.m_buffer_size;
        m_nodes = other.m_nodes;
        m_nodes_view = other.m_nodes_view;
        m_root = other.m_root;
        m_node_index = other.m_node_index;

        other.m_buffer = {};
        other.m_buffer_size = {};
        other.m_nodes = {};
        other.m_nodes_view = {};
        other.m_root = {};
        other.m_node_index = {};

        return *this;
    }

    /// Allocate
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param size the size of the allocation
    /// @return an allocated object. Throws otherwise
    ///
    inline pointer allocate(size_type size) noexcept
    {
        if (size > m_buffer_size || size == 0) {
            return nullptr;
        }

        if (size < BAREFLANK_PAGE_SIZE) {
            size = BAREFLANK_PAGE_SIZE;
        }

        return this->private_allocate(next_power_2(size), m_root);
    }

    /// Deallocate
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param ptr a pointer to a previously allocated object to be deallocated
    ///
    inline void deallocate(pointer ptr) noexcept
    {
        if (ptr == nullptr) {
            return;
        }

        this->private_deallocate(
            reinterpret_cast<integer_pointer>(ptr), m_root);
    }

    /// Size
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param ptr a pointer to a previously allocated object
    /// @return the size of ptr
    ///
    inline size_type size(pointer ptr) const noexcept
    {
        if (ptr == nullptr) {
            return 0;
        }

        return
            this->private_size(
                reinterpret_cast<integer_pointer>(ptr), m_root
            );
    }

    /// Contains Address
    ///
    /// Returns true if this buddy allocator contains this address, returns
    /// false otherwise.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param ptr to lookup
    /// @return true if the buddy allocator contains ptr, false otherwise
    ///
    inline bool
    contains(pointer ptr) const noexcept
    {
        auto uintptr = reinterpret_cast<integer_pointer>(ptr);
        return (uintptr >= m_buffer) && (uintptr < m_buffer + m_buffer_size);
    }

    /// Buffer Size
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param k the size of the buffer using the formula:
    ///     (1ULL << k) * BAREFLANK_PAGE_SIZE
    /// @return the size of buffer given size k
    ///
    constexpr static size_type buffer_size(size_type k) noexcept
    { return (1U << k) * static_cast<size_type>(BAREFLANK_PAGE_SIZE); }

    /// Node Tree Size
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param k the size of the buffer using the formula:
    ///     (1ULL << k) * BAREFLANK_PAGE_SIZE
    /// @return the size of the node tree given size k
    ///
    constexpr static size_type node_tree_size(size_type k) noexcept
    { return (2U << k) * static_cast<size_type>(sizeof(node_t)); }

private:

    void get_nodes(node_t *parent) noexcept
    {
        auto child0 = &m_nodes_view[m_node_index++];
        auto child1 = &m_nodes_view[m_node_index++];

        child0->size = parent->size >> 1;
        child1->size = parent->size >> 1;

        child0->ptr = parent->ptr;
        child1->ptr = parent->ptr + child0->size;

        parent->child0 = child0;
        parent->child1 = child1;
    }

    pointer private_allocate(
        size_type size, node_t *node) noexcept
    {
        if (this->is_leaf(node) || this->is_full(node)) {
            return 0;
        }

        if (size == node->size) {
            if (this->is_unused(node)) {
                return reinterpret_cast<pointer>(this->set_leaf(node)->ptr);
            }
        }
        else {
            if (!node->child0) {
                this->get_nodes(node);
            }

            if (size == node->child0->size) {
                if (this->is_unused(node->child0)) {
                    if (auto ptr = private_allocate_next(size, node, node->child0)) {
                        return ptr;
                    }
                }
            }
            else {
                if (!this->is_full(node->child0) && !this->is_leaf(node->child0)) {
                    if (auto ptr = private_allocate_next(size, node, node->child0)) {
                        return ptr;
                    }
                }
            }

            if (size == node->child1->size) {
                if (this->is_unused(node->child1)) {
                    if (auto ptr = private_allocate_next(size, node, node->child1)) {
                        return ptr;
                    }
                }
            }
            else {
                if (!this->is_full(node->child1) && !this->is_leaf(node->child1)) {
                    if (auto ptr = private_allocate_next(size, node, node->child1)) {
                        return ptr;
                    }
                }
            }
        }

        return nullptr;
    }

    pointer private_allocate_next(
        size_type size, node_t *parent, node_t *node) noexcept
    {
        auto ptr = private_allocate(size, node);

        if (ptr && parent) {
            this->set_parent(parent);

            if (this->is_leaf(parent->child0) && this->is_leaf(parent->child1)) {
                this->set_full(parent);
            }

            if (this->is_leaf(parent->child0) && this->is_full(parent->child1)) {
                this->set_full(parent);
            }

            if (this->is_full(parent->child0) && this->is_leaf(parent->child1)) {
                this->set_full(parent);
            }

            if (this->is_full(parent->child0) && this->is_full(parent->child1)) {
                this->set_full(parent);
            }
        }

        return ptr;
    }

private:

    bool private_deallocate(
        integer_pointer ptr, node_t *node) noexcept
    {
        if (this->is_leaf(node)) {
            this->set_unused(node);
            return true;
        }
        else {
            if (!node->child0) {
                return false;
            }

            if (ptr < node->child0->ptr + node->child0->size) {
                return private_deallocate_next(ptr, node, node->child0);
            }
            else {
                return private_deallocate_next(ptr, node, node->child1);
            }
        }

        return false;
    }

    bool private_deallocate_next(
        integer_pointer ptr, node_t *parent, node_t *node) noexcept
    {
        auto res = private_deallocate(ptr, node);

        if (res && parent) {
            this->set_parent(parent);

            if (this->is_unused(parent->child0) && this->is_unused(parent->child1)) {
                this->set_unused(parent);
            }
        }

        return res;
    }

private:

    size_type private_size(
        integer_pointer ptr, node_t *node) const noexcept
    {
        if (this->is_leaf(node)) {
            return node->size;
        }
        else {
            if (!node->child0) {
                return 0;
            }

            if (ptr < node->child0->ptr + node->child0->size) {
                return private_size(ptr, node->child0);
            }
            else {
                return private_size(ptr, node->child1);
            }
        }

        return 0;
    }

private:

    integer_pointer m_buffer{0};
    size_type m_buffer_size{0};

    node_t *m_nodes{nullptr};
    gsl::span<node_t> m_nodes_view;

    node_t *m_root{nullptr};
    size_type m_node_index{0};

private:

    inline bool
    is_unused(const node_t *node) const noexcept
    { return node->status == 0; }

    inline bool
    is_leaf(const node_t *node) const noexcept
    { return node->status == 1; }

    inline bool
    is_parent(const node_t *node) const noexcept
    { return node->status == 2; }

    inline bool
    is_full(const node_t *node) const noexcept
    { return node->status == 3; }

    inline node_t *
    set_unused(node_t *node) noexcept
    {
        node->status = 0;
        return node;
    }

    inline node_t *
    set_leaf(node_t *node) noexcept
    {
        node->status = 1;
        return node;
    }

    inline node_t *
    set_parent(node_t *node) noexcept
    {
        node->status = 2;
        return node;
    }

    inline node_t *
    set_full(node_t *node) noexcept
    {
        node->status = 3;
        return node;
    }

public:

    buddy_allocator(const buddy_allocator &) = delete;
    buddy_allocator &operator=(const buddy_allocator &) = delete;
};

#endif
