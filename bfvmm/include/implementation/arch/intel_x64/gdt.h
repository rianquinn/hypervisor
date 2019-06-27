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

#ifndef IMPLEMENTATION_GDT_INTEL_X64_H
#define IMPLEMENTATION_GDT_INTEL_X64_H

#include "../../macros.h"
#include "../../../uapis/unique_page.h"

// -----------------------------------------------------------------------------
// Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::implementation::intel_x64
{

class gdt
{
    using pointer = void *;
    using size_type = std::size_t;
    using index_type = std::ptrdiff_t;
    using integer_pointer = uint64_t;
    using value_type = uint64_t;

PUBLIC:
    explicit gdt(size_type size = 0) noexcept;
    ~gdt() noexcept = default;

PRIVATE:
    value_type base(index_type index) const;
    void set_base(index_type index, value_type val);

    value_type limit(index_type index) const;
    void set_limit(index_type index, value_type val);

    value_type access_rights(index_type index) const;
    void set_access_rights(index_type index, value_type val);

PRIVATE:
    constexpr value_type base() const noexcept
    { return m_gdt_base; }

    constexpr value_type limit() const noexcept
    { return m_gdt_limit; }

    constexpr void set(
        index_type index,
        value_type base,
        value_type limit,
        value_type access_rights)
    {
        this->set_access_rights(index, access_rights);
        this->set_base(index, base);
        this->set_limit(index, limit);
    }

PRIVATE:

    value_type m_gdt_base;
    value_type m_gdt_limit;

    unique_page<value_type> m_gdt;

PRIVATE:
    COPY_MOVE_SEMANTICS(gdt)
};

}

#endif
