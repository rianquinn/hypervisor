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

// TIDY_EXCLUSION=-cert-err58-cpp
//
// Reason:
//     This triggers a false positive WRT the allocators, which are marked
//     as noexcept, yet this check still thinks an exception could occur.
//

// TIDY_EXCLUSION=-cppcoreguidelines-pro-type-reinterpret-cast
//
// Reason:
//     Although in general this is a good rule, for hypervisor level code that
//     interfaces with the kernel, and raw hardware, this rule is
//     impractical.
//

#include <bfupperlower.h>
#include <uapis/memory_manager.h>

// -----------------------------------------------------------------------------
// Mutexes
// -----------------------------------------------------------------------------

#include <mutex>

static inline auto &md_mutex()
{
    static std::mutex s_mutex{};
    return s_mutex;
}

static inline auto &alloc_mutex()
{
    static std::mutex s_mutex{};
    return s_mutex;
}

static inline auto &alloc_map_mutex()
{
    static std::mutex s_mutex{};
    return s_mutex;
}

static inline auto &alloc_huge_mutex()
{
    static std::mutex s_mutex{};
    return s_mutex;
}

// -----------------------------------------------------------------------------
// Memory Pool
// -----------------------------------------------------------------------------

static uint32_t g_huge_pool_k = 0;
static uint8_t *g_huge_pool_buffer = nullptr;
static uint8_t *g_huge_pool_node_tree = nullptr;

extern "C" int64_t
set_huge_pool(uint64_t addr, uint64_t size) noexcept
{
    g_huge_pool_buffer = reinterpret_cast<uint8_t *>(addr);
    g_huge_pool_k = static_cast<uint32_t>(log2(size)) - 10;

    return static_cast<int64_t>(buddy_allocator::node_tree_size(g_huge_pool_k));
}

extern "C" status_t
set_huge_pool_node_tree(uint64_t addr) noexcept
{
    g_huge_pool_node_tree = reinterpret_cast<uint8_t *>(addr);
    return BFSUCCESS;
}

// -----------------------------------------------------------------------------
// Map Pool
// -----------------------------------------------------------------------------

static uint8_t g_map_pool_node_tree[buddy_allocator::node_tree_size(MAP_POOL_K)] = {};

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::implementation
{

memory_manager::memory_manager() noexcept :
    g_map_pool(MAP_POOL_START, MAP_POOL_K, g_map_pool_node_tree),
    g_huge_pool(g_huge_pool_buffer, g_huge_pool_k, g_huge_pool_node_tree),
    slab008(0x008),
    slab010(0x010),
    slab018(0x018),
    slab020(0x020),
    slab030(0x030),
    slab040(0x040),
    slab080(0x080),
    slab100(0x100),
    slab200(0x200),
    slab400(0x400),
    slab800(0x800)
{ }

memory_manager_n::pointer
memory_manager::alloc(memory_manager_n::size_type size) noexcept
{
    std::lock_guard lock(alloc_mutex());

    if ((size & 0xFFFFFFFF00000000) != 0) {
        return nullptr;
    }

    // TODO
    //
    // Run an analysis on the frequency of each allocation so that we can
    // determine the order of these allocations
    //

    if (size > 0x800) {
        return alloc_huge(size);
    }

    if (size <= 0x008) {
        return slab008.allocate();
    }

    if (size <= 0x010) {
        return slab010.allocate();
    }

    if (size <= 0x018) {
        return slab018.allocate();
    }

    if (size <= 0x020) {
        return slab020.allocate();
    }

    if (size <= 0x030) {
        return slab030.allocate();
    }

    if (size <= 0x040) {
        return slab040.allocate();
    }

    if (size <= 0x080) {
        return slab080.allocate();
    }

    if (size <= 0x100) {
        return slab100.allocate();
    }

    if (size <= 0x200) {
        return slab200.allocate();
    }

    if (size <= 0x400) {
        return slab400.allocate();
    }

    if (size <= 0x800) {
        return slab800.allocate();
    }

    return nullptr;
}

memory_manager_n::pointer
memory_manager::alloc_map(memory_manager_n::size_type size) noexcept
{
    std::lock_guard lock(alloc_map_mutex());

    if ((size & 0xFFFFFFFF00000000) != 0) {
        return nullptr;
    }

    return g_map_pool.allocate(
        gsl::narrow_cast<buddy_allocator::size_type>(size));
}

memory_manager_n::pointer
memory_manager::alloc_huge(memory_manager_n::size_type size) noexcept
{
    std::lock_guard lock(alloc_huge_mutex());

    if ((size & 0xFFFFFFFF00000000) != 0) {
        return nullptr;
    }

    auto ptr = g_huge_pool.allocate(
        gsl::narrow_cast<buddy_allocator::size_type>(size));

    if (size == BAREFLANK_PAGE_SIZE) {
        return memset(ptr, 0, BAREFLANK_PAGE_SIZE);
    }

    return ptr;
}

void
memory_manager::free(memory_manager_n::pointer ptr) noexcept
{
    std::lock_guard lock(alloc_mutex());

    if (ptr == nullptr) {
        return;
    }

    if (slab008.contains(ptr)) {
        return slab008.deallocate(ptr);
    }

    if (slab010.contains(ptr)) {
        return slab010.deallocate(ptr);
    }

    if (slab018.contains(ptr)) {
        return slab018.deallocate(ptr);
    }

    if (slab020.contains(ptr)) {
        return slab020.deallocate(ptr);
    }

    if (slab030.contains(ptr)) {
        return slab030.deallocate(ptr);
    }

    if (slab040.contains(ptr)) {
        return slab040.deallocate(ptr);
    }

    if (slab080.contains(ptr)) {
        return slab080.deallocate(ptr);
    }

    if (slab100.contains(ptr)) {
        return slab100.deallocate(ptr);
    }

    if (slab200.contains(ptr)) {
        return slab200.deallocate(ptr);
    }

    if (slab400.contains(ptr)) {
        return slab400.deallocate(ptr);
    }

    if (slab800.contains(ptr)) {
        return slab800.deallocate(ptr);
    }

    return this->free_huge(ptr);
}

void
memory_manager::free_map(memory_manager_n::pointer ptr) noexcept
{
    std::lock_guard lock(alloc_map_mutex());
    return g_map_pool.deallocate(ptr);
}

void
memory_manager::free_huge(memory_manager_n::pointer ptr) noexcept
{
    std::lock_guard lock(alloc_huge_mutex());
    return g_huge_pool.deallocate(ptr);
}

memory_manager_n::size_type
memory_manager::size(memory_manager_n::pointer ptr) const noexcept
{
    std::lock_guard lock(alloc_mutex());

    if (slab008.contains(ptr)) {
        return slab008.size(ptr);
    }

    if (slab010.contains(ptr)) {
        return slab010.size(ptr);
    }

    if (slab018.contains(ptr)) {
        return slab018.size(ptr);
    }

    if (slab020.contains(ptr)) {
        return slab020.size(ptr);
    }

    if (slab030.contains(ptr)) {
        return slab030.size(ptr);
    }

    if (slab040.contains(ptr)) {
        return slab040.size(ptr);
    }

    if (slab080.contains(ptr)) {
        return slab080.size(ptr);
    }

    if (slab100.contains(ptr)) {
        return slab100.size(ptr);
    }

    if (slab200.contains(ptr)) {
        return slab200.size(ptr);
    }

    if (slab400.contains(ptr)) {
        return slab400.size(ptr);
    }

    if (slab800.contains(ptr)) {
        return slab800.size(ptr);
    }

    return this->size_huge(ptr);
}

memory_manager_n::size_type
memory_manager::size_map(memory_manager_n::pointer ptr) const noexcept
{
    std::lock_guard lock(alloc_map_mutex());
    return g_map_pool.size(ptr);
}

memory_manager_n::size_type
memory_manager::size_huge(memory_manager_n::pointer ptr) const noexcept
{
    std::lock_guard lock(alloc_huge_mutex());
    return g_huge_pool.size(ptr);
}

memory_manager_n::integer_pointer
memory_manager::hva_to_hpa(memory_manager_n::integer_pointer hva) const
{
    auto lower = bfn::lower(hva);
    auto upper = bfn::upper(hva);

    std::lock_guard guard(md_mutex());

    if (auto iter = m_hva_lookup.find(upper); iter != m_hva_lookup.end()) {
        return iter->second.hpa | lower;
    }

    throw std::runtime_error(
        "memory_manager::hva_to_hpa failed: " + bfn::to_string(hva, 16)
    );
}

memory_manager_n::integer_pointer
memory_manager::hpa_to_hva(memory_manager_n::integer_pointer hpa) const
{
    auto lower = bfn::lower(hpa);
    auto upper = bfn::upper(hpa);

    std::lock_guard guard(md_mutex());

    if (auto iter = m_hpa_lookup.find(upper); iter != m_hpa_lookup.end()) {
        return iter->second.hva | lower;
    }

    throw std::runtime_error(
        "memory_manager::hpa_to_hva failed: " + bfn::to_string(hpa, 16)
    );
}

void
memory_manager::add_md(
    memory_manager_n::integer_pointer hva,
    memory_manager_n::integer_pointer hpa,
    memory_manager_n::attr_type attr)
{
    std::lock_guard guard(md_mutex());

    try {
        m_hva_lookup[bfn::lower(hva)] = {bfn::lower(hpa), attr};
        m_hpa_lookup[bfn::lower(hpa)] = {bfn::lower(hva), attr};
    }
    catch (...) {
        m_hva_lookup.erase(hva);
        m_hpa_lookup.erase(hpa);
        throw;
    }
}

void
memory_manager::dump_stats() const noexcept
{ bfalert_info(0, "currently not supported"); }

}

#ifdef ENABLE_BUILD_VMM

extern "C" void *
_malloc_r(struct _reent *ent, size_t size)
{
    bfignored(ent);
    return memory_manager_n::instance()->alloc(size);
}

extern "C" void
_free_r(struct _reent *ent, void *ptr)
{
    bfignored(ent);
    memory_manager_n::instance()->free(ptr);
}

extern "C" void *
_calloc_r(struct _reent *ent, size_t nmemb, size_t size)
{
    bfignored(ent);

    if (auto ptr = memory_manager_n::instance()->alloc(nmemb * size)) {
        return memset(ptr, 0, nmemb * size);
    }

    return nullptr;
}

extern "C" void *
_realloc_r(struct _reent *ent, void *ptr, size_t size)
{
    bfignored(ent);

    auto old_sze = memory_manager_n::instance()->size(ptr);
    auto new_ptr = memory_manager_n::instance()->alloc(size);

    if (new_ptr == nullptr || old_sze == 0) {
        return nullptr;
    }

    if (ptr != nullptr) {
        memcpy(new_ptr, ptr, size > old_sze ? old_sze : size);
        memory_manager_n::instance()->free(ptr);
    }

    return new_ptr;
}

extern "C" void *
alloc_page()
{ return memory_manager_n::instance()->alloc_huge(BAREFLANK_PAGE_SIZE); }

extern "C" void
free_page(void *ptr)
{ memory_manager_n::instance()->free_huge(ptr); }

#endif
