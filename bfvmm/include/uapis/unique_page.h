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

#ifndef UAPIS_UNIQUE_PAGE_H
#define UAPIS_UNIQUE_PAGE_H

#include <memory>

#include <bfgsl.h>
#include "memory_manager.h"

// -----------------------------------------------------------------------------
// Definition
// -----------------------------------------------------------------------------

template<typename T>
using __unique_ptr_page = std::unique_ptr<T, void(*)(void *)>;

/// Unique Page
///
/// A unique_page is nothing more than a wrapper around a std::unique_ptr with
/// a couple of added functions. Specifically, it provides an hva() and hpa()
/// function that returns an integer version of the host virtual and host
/// physical address associated with the page. It also returns a span that can
/// be used to access the page. Note that we do not support the custom deleter
/// types as the page needs to be handled specifically.
///
template<typename T>
class unique_page :
    public __unique_ptr_page<T>
{
    uint64_t m_hpa{};

    static constexpr auto count() noexcept
    {
        static_assert(sizeof(T) <= BFPAGE_SIZE);
        return BFPAGE_SIZE / sizeof(T);
    }

public:

    /// @cond

    using pointer = typename std::unique_ptr<T>::pointer;
    using element_type = typename std::unique_ptr<T>::element_type;
    using deleter_type = typename std::unique_ptr<T>::deleter_type;
    using integer_pointer = uint64_t;
    using span_type = gsl::span<T, count()>;

    /// @endcond

public:

    /// Default Constructor
    ///
    /// Creates a unique_page with a given type.
    ///
    constexpr unique_page() :
        __unique_ptr_page<T>{alloc_page<T>(), free_page},
        m_hpa{g_mm->hva_to_hpa(this->hva())}
    { }

    /// Nullptr Constructor
    ///
    /// This creates an empty version of a page given a type.
    /// It should be noted that this creates a non-valid pointer
    /// so checks should be made if using this constructor
    ///
    constexpr unique_page(nullptr_t) noexcept :
        __unique_ptr_page<T>{nullptr}
    { }

    /// Move Constructor
    ///
    /// @param u the unique_page to move from.
    ///
    unique_page(unique_page &&u) noexcept :
        __unique_ptr_page<T>{u}
    { *this = std::move(u); }

    /// Move Operator
    ///
    /// @param u the unique_page to move from.
    ///
    unique_page &operator=(unique_page &&u)
    {
        m_hpa = std::move(u.m_hpa);
        u.m_hpa = 0;
    }

    /// Host Virtual Address (HVA)
    ///
    /// @return returns an integer_pointer of the HVA for this page
    ///
    constexpr integer_pointer hva() const noexcept
    { return reinterpret_cast<integer_pointer>(this->get()); }

    /// Host Physical Address (HPA)
    ///
    /// @return returns an integer_pointer of the HPA for this page
    ///
    constexpr integer_pointer hpa() const noexcept
    { return m_hpa; }

    /// View
    ///
    /// @return returns a gsl::span for the unique_page;
    ///
    constexpr span_type view() const noexcept
    { return span_type{this->get(), count()}; }
};

#endif
