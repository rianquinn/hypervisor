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

#include <bfstring.h>
#include <bfupperlower.h>
#include <uapis/arch/intel_x64/intrinsics/pt.h>

#include <implementation/memory_manager.h>
#include <implementation/arch/intel_x64/hpt.h>

namespace bfvmm::implementation::intel_x64
{

using namespace ::intel_x64;
using namespace ::bfvmm::memory_manager;

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

static inline auto
allocate_span(hpt::size_type num_entries)
{
    return
        gsl::span(
            alloc_page<hpt::virt_addr_type>(),
            static_cast<hpt::index_type>(num_entries)
        );
}

static inline auto
allocate(hpt::size_type num_entries)
{
    auto span = allocate_span(num_entries);

    return hpt::pair {
        span, hva_to_hpa(g_mm, span.data())
    };
}

static inline void
free(const gsl::span<hpt::virt_addr_type> &virt_addr)
{ free_page(virt_addr.data()); }

static inline auto
phys_to_pair(hpt::phys_addr_type phys_addr, hpt::size_type num_entries)
{
    auto virt_addr =
        hpa_to_hva<hpt::virt_addr_type *>(g_mm, phys_addr);

    return hpt::pair {
        gsl::span(virt_addr, static_cast<hpt::index_type>(num_entries)),
        phys_addr
    };
}

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

hpt::hpt() :
    m_pml4{allocate_span(pml4::num_entries), 0}
{ }

uintptr_t
hpt::cr3()
{
    std::lock_guard lock(m_mutex);
    return hva_to_hpa(g_mm, m_pml4.virt_addr.data());
}

hpt::entry_type &
hpt::map_1g(
    void *virt_addr, phys_addr_type phys_addr, attr_type attr, memory_type cache)
{
    std::lock_guard lock(m_mutex);

    expects(bfn::lower(virt_addr, pdpt::from) == 0);
    expects(bfn::lower(phys_addr, pdpt::from) == 0);

    this->map_pdpt(pml4::index(virt_addr));
    return this->map_pdpte(virt_addr, phys_addr, attr, cache);
}

hpt::entry_type &
hpt::map_2m(
    void *virt_addr, phys_addr_type phys_addr, attr_type attr, memory_type cache)
{
    std::lock_guard lock(m_mutex);

    expects(bfn::lower(virt_addr, pd::from) == 0);
    expects(bfn::lower(phys_addr, pd::from) == 0);

    this->map_pdpt(pml4::index(virt_addr));
    this->map_pd(pdpt::index(virt_addr));

    return this->map_pde(virt_addr, phys_addr, attr, cache);
}

hpt::entry_type &
hpt::map_4k(
    void *virt_addr, phys_addr_type phys_addr, attr_type attr, memory_type cache)
{
    std::lock_guard lock(m_mutex);

    expects(bfn::lower(virt_addr, pt::from) == 0);
    expects(bfn::lower(phys_addr, pt::from) == 0);

    this->map_pdpt(pml4::index(virt_addr));
    this->map_pd(pdpt::index(virt_addr));
    this->map_pt(pd::index(virt_addr));

    return this->map_pte(virt_addr, phys_addr, attr, cache);
}

void
hpt::unmap(void *virt_addr)
{
    std::lock_guard lock(m_mutex);

    if (this->unmap_pdpte(virt_addr)) {
        m_pml4.virt_addr.at(pml4::index(virt_addr)) = 0;
    }
}

void
hpt::map_pdpt(index_type pml4i)
{
    auto &entry = m_pml4.virt_addr.at(pml4i);

    if (entry != 0) {
        auto phys_addr = pml4::entry::phys_addr::get(entry);

        if (m_pdpt.phys_addr == phys_addr) {
            return;
        }

        m_pdpt = phys_to_pair(phys_addr, pdpt::num_entries);
        return;
    }

    m_pdpt = allocate(pdpt::num_entries);

    pml4::entry::phys_addr::set(entry, m_pdpt.phys_addr);
    pml4::entry::pat_index::set(entry, 1);
    pml4::entry::present::enable(entry);
    pml4::entry::rw::enable(entry);
}

void
hpt::map_pd(index_type pdpti)
{
    auto &entry = m_pdpt.virt_addr.at(pdpti);

    if (entry != 0) {
        auto phys_addr = pdpt::entry::phys_addr::get(entry);

        if (m_pd.phys_addr == phys_addr) {
            return;
        }

        m_pd = phys_to_pair(phys_addr, pd::num_entries);
        return;
    }

    m_pd = allocate(pd::num_entries);

    pdpt::entry::phys_addr::set(entry, m_pd.phys_addr);
    pdpt::entry::pat_index::set(entry, 1);
    pdpt::entry::present::enable(entry);
    pdpt::entry::rw::enable(entry);
}

void
hpt::map_pt(index_type pdi)
{
    auto &entry = m_pd.virt_addr.at(pdi);

    if (entry != 0) {
        auto phys_addr = pd::entry::phys_addr::get(entry);

        if (m_pt.phys_addr == phys_addr) {
            return;
        }

        m_pt = phys_to_pair(phys_addr, pt::num_entries);
        return;
    }

    m_pt = allocate(pt::num_entries);

    pd::entry::phys_addr::set(entry, m_pt.phys_addr);
    pd::entry::pat_index::set(entry, 1);
    pd::entry::present::enable(entry);
    pd::entry::rw::enable(entry);
}

hpt::entry_type &
hpt::map_pdpte(
    void *virt_addr, phys_addr_type phys_addr, attr_type attr, memory_type cache)
{
    auto &entry = m_pdpt.virt_addr.at(pdpt::index(virt_addr));

    if (entry != 0) {
        throw std::runtime_error(
            "map_pdpte: map failed, virt / phys map already exists: " +
            bfn::to_string(phys_addr, 16)
        );
    }

    pdpt::entry::phys_addr::set(entry, phys_addr);
    pdpt::entry::present::enable(entry);

    switch (attr) {
        case attr_type::read_write:
            pdpt::entry::rw::enable(entry);
            pdpt::entry::xd::enable(entry);
            break;

        case attr_type::read_execute:
            pdpt::entry::rw::disable(entry);
            pdpt::entry::xd::disable(entry);
            break;

        case attr_type::read_write_execute:
            pdpt::entry::rw::enable(entry);
            pdpt::entry::xd::disable(entry);
            break;
    };

    switch (cache) {
        case memory_type::uncacheable:
            pdpt::entry::pat_index::set(entry, 0);
            break;

        case memory_type::write_back:
            pdpt::entry::pat_index::set(entry, 1);
            break;
    };

    pdpt::entry::ps::enable(entry);
    return entry;
}

hpt::entry_type &
hpt::map_pde(
    void *virt_addr, phys_addr_type phys_addr, attr_type attr, memory_type cache)
{
    auto &entry = m_pd.virt_addr.at(pd::index(virt_addr));

    if (entry != 0) {
        throw std::runtime_error(
            "map_pde: map failed, virt / phys map already exists: " +
            bfn::to_string(phys_addr, 16)
        );
    }

    pd::entry::phys_addr::set(entry, phys_addr);
    pd::entry::present::enable(entry);

    switch (attr) {
        case attr_type::read_write:
            pd::entry::rw::enable(entry);
            pd::entry::xd::enable(entry);
            break;

        case attr_type::read_execute:
            pd::entry::rw::disable(entry);
            pd::entry::xd::disable(entry);
            break;

        case attr_type::read_write_execute:
            pd::entry::rw::enable(entry);
            pd::entry::xd::disable(entry);
            break;
    };

    switch (cache) {
        case memory_type::uncacheable:
            pd::entry::pat_index::set(entry, 0);
            break;

        case memory_type::write_back:
            pd::entry::pat_index::set(entry, 1);
            break;
    };

    pd::entry::ps::enable(entry);
    return entry;
}

hpt::entry_type &
hpt::map_pte(
    void *virt_addr, phys_addr_type phys_addr, attr_type attr, memory_type cache)
{
    auto &entry = m_pt.virt_addr.at(pt::index(virt_addr));

    if (entry != 0) {
        throw std::runtime_error(
            "map_pte: map failed, virt / phys map already exists: " +
            bfn::to_string(phys_addr, 16)
        );
    }

    pt::entry::phys_addr::set(entry, phys_addr);
    pt::entry::present::enable(entry);

    switch (attr) {
        case attr_type::read_write:
            pt::entry::rw::enable(entry);
            pt::entry::xd::enable(entry);
            break;

        case attr_type::read_execute:
            pt::entry::rw::disable(entry);
            pt::entry::xd::disable(entry);
            break;

        case attr_type::read_write_execute:
            pt::entry::rw::enable(entry);
            pt::entry::xd::disable(entry);
            break;
    };

    switch (cache) {
        case memory_type::uncacheable:
            pt::entry::pat_index::set(entry, 0);
            break;

        case memory_type::write_back:
            pt::entry::pat_index::set(entry, 1);
            break;
    };

    return entry;
}

bool
hpt::unmap_pdpte(void *virt_addr)
{
    this->map_pdpt(pml4::index(virt_addr));
    auto &entry = m_pdpt.virt_addr.at(pdpt::index(virt_addr));

    if (pdpt::entry::ps::is_disabled(entry)) {
        if (!this->unmap_pde(virt_addr)) {
            return false;
        }
    }

    entry = 0;

    auto empty = true;
    for (auto pdpti = 0; pdpti < pdpt::num_entries; pdpti++) {
        if (m_pdpt.virt_addr.at(pdpti) != 0) {
            empty = false;
        }
    }

    if (empty) {
        free(m_pdpt.virt_addr);
        return true;
    }

    return false;
}

bool
hpt::unmap_pde(void *virt_addr)
{
    this->map_pd(pdpt::index(virt_addr));
    auto &entry = m_pd.virt_addr.at(pd::index(virt_addr));

    if (pd::entry::ps::is_disabled(entry)) {
        if (!this->unmap_pte(virt_addr)) {
            return false;
        }
    }

    entry = 0;

    auto empty = true;
    for (auto pdi = 0; pdi < pd::num_entries; pdi++) {
        if (m_pd.virt_addr.at(pdi) != 0) {
            empty = false;
        }
    }

    if (empty) {
        free(m_pd.virt_addr);
        return true;
    }

    return false;
}

bool
hpt::unmap_pte(void *virt_addr)
{
    this->map_pt(pd::index(virt_addr));
    m_pt.virt_addr.at(pt::index(virt_addr)) = 0;

    auto empty = true;
    for (auto pti = 0; pti < pt::num_entries; pti++) {
        if (m_pt.virt_addr.at(pti) != 0) {
            empty = false;
        }
    }

    if (empty) {
        free(m_pt.virt_addr);
        return true;
    }

    return false;
}

}
