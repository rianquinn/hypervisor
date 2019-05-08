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

// TIDY_EXCLUSION=-cppcoreguidelines-pro-type-reinterpret-cast
//
// Reason:
//     Although in general this is a good rule, for hypervisor level code that
//     interfaces with the kernel, and raw hardware, this rule is
//     impractical.
//

#include <implementation/memory_manager.h>

// -----------------------------------------------------------------------------
// Mutexes
// -----------------------------------------------------------------------------

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
static uint8_t *g_huge_pool_leafs = nullptr;
static uint8_t *g_huge_pool_nodes = nullptr;

extern "C" status_t
set_huge_pool_leafs(uint64_t addr, uint64_t size) noexcept
{
    g_huge_pool_k = log2n(size) - log2n(BFPAGE_SIZE);
    g_huge_pool_leafs = reinterpret_cast<uint8_t *>(addr);
    return BFSUCCESS;
}

extern "C" status_t
set_huge_pool_nodes(uint64_t addr, uint64_t size) noexcept
{
    if (size != num_nodes(g_huge_pool_k) * BFNODE_SIZE) {
        return BFFAILURE;
    }

    g_huge_pool_nodes = reinterpret_cast<uint8_t *>(addr);
    return BFSUCCESS;
}

// -----------------------------------------------------------------------------
// Map Pool
// -----------------------------------------------------------------------------

static uint8_t g_map_pool_nodes[num_nodes(MAP_POOL_K) * BFNODE_SIZE] = {};

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::implementation
{

memory_manager::integer_pointer
memory_manager::__hva_to_hpa(integer_pointer hva) const
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

memory_manager::integer_pointer
memory_manager::__hpa_to_hva(integer_pointer hpa) const
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

gsl::not_null<memory_manager *>
memory_manager::__instance() noexcept
{
    static memory_manager s_mm;
    return &s_mm;
}

memory_manager::memory_manager() noexcept :
    g_map_pool(MAP_POOL_START, MAP_POOL_K, g_map_pool_nodes),
    g_huge_pool(g_huge_pool_leafs, g_huge_pool_k, g_huge_pool_nodes),
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

memory_manager::pointer
memory_manager::alloc(size_type size) noexcept
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

memory_manager::pointer
memory_manager::alloc_map(size_type size) noexcept
{
    std::lock_guard lock(alloc_map_mutex());

    if ((size & 0xFFFFFFFF00000000) != 0) {
        return nullptr;
    }

    return g_map_pool.allocate(
        gsl::narrow_cast<buddy_allocator::size_type>(size));
}

memory_manager::pointer
memory_manager::alloc_huge(size_type size) noexcept
{
    std::lock_guard lock(alloc_huge_mutex());

    if ((size & 0xFFFFFFFF00000000) != 0) {
        return nullptr;
    }

    auto ptr = g_huge_pool.allocate(
        gsl::narrow_cast<buddy_allocator::size_type>(size));

    if (size == BFPAGE_SIZE) {
        return memset(ptr, 0, BFPAGE_SIZE);
    }

    return ptr;
}

void
memory_manager::free(pointer ptr) noexcept
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
memory_manager::free_map(pointer ptr) noexcept
{
    std::lock_guard lock(alloc_map_mutex());
    return g_map_pool.deallocate(ptr);
}

void
memory_manager::free_huge(pointer ptr) noexcept
{
    std::lock_guard lock(alloc_huge_mutex());
    return g_huge_pool.deallocate(ptr);
}

memory_manager::size_type
memory_manager::size(pointer ptr) const noexcept
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

memory_manager::size_type
memory_manager::size_map(pointer ptr) const noexcept
{
    std::lock_guard lock(alloc_map_mutex());
    return g_map_pool.size(ptr);
}

memory_manager::size_type
memory_manager::size_huge(pointer ptr) const noexcept
{
    std::lock_guard lock(alloc_huge_mutex());
    return g_huge_pool.size(ptr);
}

void
memory_manager::add_md(
    integer_pointer hva, integer_pointer hpa, attr_type attr)
{
    std::lock_guard guard(md_mutex());

    try {
        m_hva_lookup[bfn::upper(hva)] = {bfn::upper(hpa), attr};
        m_hpa_lookup[bfn::upper(hpa)] = {bfn::upper(hva), attr};
    }
    catch (...) {
        m_hva_lookup.erase(hva);
        m_hpa_lookup.erase(hpa);
        throw;
    }
}

}

#ifdef ENABLE_BUILD_VMM

class private_memory_manager
{
public:
    template<typename... Args>
    constexpr static auto alloc(Args &&...args) noexcept
    { return g_mm->alloc(std::forward<Args>(args)...); }

    template<typename... Args>
    constexpr static auto alloc_huge(Args &&...args) noexcept
    { return g_mm->alloc_huge(std::forward<Args>(args)...); }

    template<typename... Args>
    constexpr static void free(Args &&...args) noexcept
    { g_mm->free(std::forward<Args>(args)...); }

    template<typename... Args>
    constexpr static void free_huge(Args &&...args) noexcept
    { g_mm->free_huge(std::forward<Args>(args)...); }

    template<typename... Args>
    constexpr static auto size(Args &&...args) noexcept
    { return g_mm->size(std::forward<Args>(args)...); }
};

using namespace bfvmm::implementation;

extern "C" void *
_malloc_r(struct _reent *, size_t size)
{ return private_memory_manager::alloc(size); }

extern "C" void
_free_r(struct _reent *, void *ptr)
{ private_memory_manager::free(ptr); }

extern "C" void *
_calloc_r(struct _reent *, size_t nmemb, size_t size)
{
    if (auto ptr = private_memory_manager::alloc(nmemb * size)) {
        return memset(ptr, 0, nmemb * size);
    }

    return nullptr;
}

extern "C" void *
_realloc_r(struct _reent *, void *ptr, size_t size)
{
    auto old_sze = private_memory_manager::size(ptr);
    auto new_ptr = private_memory_manager::alloc(size);

    if (new_ptr == nullptr || old_sze == 0) {
        return nullptr;
    }

    if (ptr != nullptr) {
        memcpy(new_ptr, ptr, size > old_sze ? old_sze : size);
        private_memory_manager::free(ptr);
    }

    return new_ptr;
}

void *
alloc_page() noexcept
{ return private_memory_manager::alloc_huge(BFPAGE_SIZE); }

void
free_page(void *ptr) noexcept
{ private_memory_manager::free_huge(ptr); }

#endif
