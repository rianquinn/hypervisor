///
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

#include <gsl/gsl_algorithm>

#include <implementation/arch/intel_x64/gdt.h>
#include <uapis/arch/intel_x64/intrinsics/gdt.h>

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::implementation::intel_x64
{

gdt::gdt(size_type size) noexcept
{
    if (size == 0) {
        m_gdt_base = ::intel_x64::gdt_reg::base::get();
        m_gdt_limit = ::intel_x64::gdt_reg::limit::get();

        gsl::copy(m_gdt.view(), {
            reinterpret_cast<value_type *>(m_gdt_base),
            static_cast<index_type>(m_gdt_limit + 1) >> 3
        });
    }
    else {
        m_gdt_base = m_gdt.hva();
        m_gdt_limit = (size << 3) - 1;
    }
}

gdt::value_type
gdt::base(index_type index) const
{
    auto view = m_gdt.view();
    expects(index != 0 && index < view.size());

    auto sd1 = view.at(index);
    auto base_15_00 = ((sd1 & 0x00000000FFFF0000ULL) >> 16);
    auto base_23_16 = ((sd1 & 0x000000FF00000000ULL) >> 16);
    auto base_31_24 = ((sd1 & 0xFF00000000000000ULL) >> 32);

    if ((sd1 & 0x100000000000ULL) == 0) {
        auto sd2 = view.at(index + 1U);
        auto base_63_32 = ((sd2 & 0x00000000FFFFFFFFULL) << 32);

        return base_63_32 | base_31_24 | base_23_16 | base_15_00;
    }

    return base_31_24 | base_23_16 | base_15_00;
}

void
gdt::set_base(index_type index, value_type val)
{
    auto view = m_gdt.view();
    expects(index != 0 && index < view.size());

    auto sd1 = view.at(index) & 0x00FFFF000000FFFFULL;
    auto base_15_00 = ((val & 0x000000000000FFFFULL) << 16);
    auto base_23_16 = ((val & 0x0000000000FF0000ULL) << 16);
    auto base_31_24 = ((val & 0x00000000FF000000ULL) << 32);
    auto base_63_32 = ((val & 0xFFFFFFFF00000000ULL) >> 32);

    if ((sd1 & 0x100000000000ULL) == 0) {
        auto sd2 = view.at(index + 1U) & 0xFFFFFFFF00000000ULL;
        view.at(index + 0U) = sd1 | base_31_24 | base_23_16 | base_15_00;
        view.at(index + 1U) = sd2 | base_63_32;
    }
    else {
        view.at(index + 0U) = sd1 | base_31_24 | base_23_16 | base_15_00;
    }
}

gdt::value_type
gdt::limit(index_type index) const
{
    auto view = m_gdt.view();
    expects(index != 0 && index < view.size());

    auto sd1 = view.at(index);
    if ((sd1 & 0x80000000000000ULL) != 0) {
        auto limit_15_00 = (sd1 & 0x000000000000FFFFULL) >> 0;
        auto limit_19_16 = (sd1 & 0x000F000000000000ULL) >> 32;

        return ((limit_19_16 | limit_15_00) << 12) | 0x0000000000000FFFULL;
    }

    auto limit_15_00 = (sd1 & 0x000000000000FFFFULL) >> 0;
    auto limit_19_16 = (sd1 & 0x000F000000000000ULL) >> 32;

    return limit_19_16 | limit_15_00;
}

void
gdt::set_limit(index_type index, value_type val)
{
    auto view = m_gdt.view();
    expects(index != 0 && index < view.size());

    auto sd1 = view.at(index) & 0xFFF0FFFFFFFF0000ULL;
    if ((sd1 & 0x80000000000000ULL) != 0) {
        limit = (limit >> 12);
    }

    auto limit_15_00 = (limit & 0x000000000000FFFFULL) << 0);
    auto limit_19_16 = (limit & 0x00000000000F0000ULL) << 32);

    view.at(index) = sd1 | limit_19_16 | limit_15_00;
}

gdt::value_type
gdt::access_rights(index_type index) const
{
    auto view = m_gdt.view();
    expects(index != 0 && index < view.size());

    auto sd1 = view.at(index);
    auto access_rights_07_00 = static_cast<access_rights_type>((sd1 & 0x0000FF0000000000ULL) >> 40);
    auto access_rights_15_12 = static_cast<access_rights_type>((sd1 & 0x00F0000000000000ULL) >> 40);

    return access_rights_15_12 | access_rights_07_00;
}

void
gdt::set_access_rights(index_type index, value_type val)
{
    auto view = m_gdt.view();
    expects(index != 0 && index < view.size());

    auto sd1 = view.at(index) & 0xFF0F00FFFFFFFFFFULL;
    auto access_rights_07_00 = (access_rights & 0x00000000000000FFULL) << 40);
    auto access_rights_15_12 = (access_rights & 0x000000000000F000ULL) << 40);

    view.at(index) = sd1 | access_rights_15_12 | access_rights_07_00;
}

}
