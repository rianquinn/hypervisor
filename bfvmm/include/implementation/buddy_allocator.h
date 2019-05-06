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

#ifndef IMPLEMENTATION_BUDDY_ALLOCATOR_H
#define IMPLEMENTATION_BUDDY_ALLOCATOR_H

#include <bfgsl.h>
#include <bfmemory.h>
#include <bfconstants.h>

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
/// To support these features, this allocator uses 2 leafss.
/// - leafs: this is the main leafs that is allocated and returned. This
///   leafs must be page aligned, and a power of 2^k.
/// - node tree leafs: The node tree leafs stores the binary tree that keeps
///   track of each allocation.
///
class buddy_allocator
{
public:

    using pointer = void *;
    using integer_pointer = uintptr_t;
    using size_type = uint32_t;

private:

    /// @struct node
    ///
    /// This node is used to define the binary tree. child0 and child1 define
    /// the child nodes (left or right) in the binary tree. ptr stores the
    /// location in the provided leafs that this node refers to, and size
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

    static_assert(sizeof(node_t) == BFNODE_SIZE);

public:

    /// Pointer Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param leafs the buffer that the buddy allocator will manage. Note
    ///     that the buddy allocator will never dereference the address
    ///     provided here, allowing it to be used for virtual memory allocation
    /// @param The height of the binary tree.
    /// @param nodes the buffer that will be used to store the buddy
    ///     allocators binary tree. This buffer is assumed to be
    ///     num_nodes(k) * BFNODE_SIZE
    ///
    buddy_allocator(pointer leafs, size_type k, pointer nodes) noexcept
    {
        m_leafs = reinterpret_cast<integer_pointer>(leafs);
        m_leafs_size = num_leafs(k) * BFPAGE_SIZE;

        m_nodes = static_cast<node_t *>(nodes);
        m_nodes_view = gsl::span(m_nodes, gsl::index_cast(num_nodes(k)));

        m_root = &m_nodes_view.at(gsl::index_cast(m_node_index++));
        m_root->ptr = m_leafs;
        m_root->size = m_leafs_size;
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

    /// Allocate
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param size the size of the allocation
    /// @return an allocated object. Throws otherwise
    ///
    inline pointer allocate(size_type size)
    {
        if (size > m_leafs_size || size == 0) {
            return nullptr;
        }

        if (size < BFPAGE_SIZE) {
            size = BFPAGE_SIZE;
        }

        if (auto ptr = this->private_allocate(next_power_2(size), m_root)) {
            return ptr;
        }

        throw std::bad_alloc();
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
        return (uintptr >= m_leafs) && (uintptr < m_leafs + m_leafs_size);
    }

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

    integer_pointer m_leafs{0};
    size_type m_leafs_size{0};

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

    buddy_allocator(buddy_allocator &&) noexcept = delete;
    buddy_allocator &operator=(buddy_allocator &&) noexcept = delete;

    buddy_allocator(const buddy_allocator &) = delete;
    buddy_allocator &operator=(const buddy_allocator &) = delete;
};

#endif
