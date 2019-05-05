/*
 * Copyright (C) 2019 Assured Information Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file bfmemory.h
 */

#ifndef BFMEMORY_H
#define BFMEMORY_H

#include <bftypes.h>

#pragma pack(push, 1)

/* @cond */

#define MEMORY_TYPE_R 0x1U
#define MEMORY_TYPE_W 0x2U
#define MEMORY_TYPE_X 0x4U
#define MEMORY_TYPE_RX (MEMORY_TYPE_R | MEMORY_TYPE_X)
#define MEMORY_TYPE_RW (MEMORY_TYPE_R | MEMORY_TYPE_W)

/* @endcond */

/**
 * @struct memory_descriptor
 *
 * Memory Descriptor
 *
 * A memory descriptor provides information about a block of memory.
 * Typically, each page of memory that the VMM uses will have a memory
 * descriptor associated with it. The VMM will use this information to create
 * its resources, as well as generate page tables as needed.
 *
 * @var memory_descriptor::phys
 *     the starting physical address of the block of memory
 * @var memory_descriptor::virt
 *     the starting virtual address of the block of memory
 * @var memory_descriptor::type
 *     the type of memory block. This is likely architecture specific as
 *     this holds information about access rights, etc...
 */
struct memory_descriptor {
    uint64_t phys;
    uint64_t virt;
    uint64_t type;
};

// -----------------------------------------------------------------------------
// Binary Tree Functions
// -----------------------------------------------------------------------------

#define BFNODE_SIZE 32

/// Number of leafs
///
/// Returns the total number of leafs in a binary tree. For a buddy allocator,
/// you can multiply the total number of leafs * the page size to determine
/// the total amount of memory the buddy allocator can distribute.
///
/// @expects none
/// @ensures none
///
/// @param k the height of the tree (0 indexed)
/// @return the total number of leaves
///
#define num_leafs(k) (1U << k)

/// Number of nodes
///
/// Returns the total number of nodes in a binary tree + 1. We add 1 because
/// in all of our calculations where this function is needed, we wish to
/// allocation memory, and the - 1 is problematic as it would result in a non
/// power of 2 allocation. If you want the true value, just -1 from the
/// results of this function.
///
/// @expects none
/// @ensures none
///
/// @param k the height of the tree (0 indexed)
/// @return the total number of nodes
///
#define num_nodes(k) (2U << k)

// -----------------------------------------------------------------------------
// Power of 2 Helpers
// -----------------------------------------------------------------------------

/// Is Power of 2
///
/// @return returns BFSUCCESS if val is a power of 2, BFFAILURE otherwise
///
static inline status_t
is_power_of_2(uint64_t val) NOEXCEPT
{
    if (val == 0) {
        return BFFAILURE;
    }

    while (val > 1) {
        if ((val & 0x1) != 0) {
            return BFFAILURE;
        }

        val >>= 1;
    }

    return BFSUCCESS;
}

/// Log2N
///
/// @return log2(n)
///
static inline uint32_t
log2n(uint64_t n) NOEXCEPT
{
    uint32_t val;
    for (val = 0; n > 1; val++, n >>= 1);

    return val;
}

/// Round to Next Power of 2
///
/// http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
///
static inline uint32_t
next_power_2(uint32_t size) NOEXCEPT
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

#pragma pack(pop)

#endif
