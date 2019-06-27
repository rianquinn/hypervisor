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

#ifndef UAPIS_MANAGED_PAGE_H
#define UAPIS_MANAGED_PAGE_H

#include "managed_ptr.h"

// -----------------------------------------------------------------------------
// Definition
// -----------------------------------------------------------------------------

/// Managed Page
///
/// This is the same thing as a managed_ptr with the exception that all
/// allocations are a page in size.
///
template<typename T, typename D = std::default_delete<T>>
class managed_ptr :
    public std::unique_ptr<T, D>
{
public:


    constexpr managed_ptr() noexcept :
        std::unique_ptr<T, D>{},
        m_
    {

    }

constexpr managed_ptr( nullptr_t ) noexcept;
	(1)
explicit managed_ptr( pointer p ) noexcept;
	(2)
managed_ptr( pointer p, /* see below */ d1 ) noexcept;
	(3)
managed_ptr( pointer p, /* see below */ d2 ) noexcept;
	(4)
managed_ptr( managed_ptr&& u ) noexcept;
	(5)


















    /// Default Constructor
    ///
    /// Creates a managed_ptr with a given type.
    ///
    constexpr managed_ptr() :
        __managed_ptr<T>{alloc_page<T>(), free_page},
        m_hpa{g_mm->hva_to_hpa(this->hva())}
    { }

    /// Nullptr Constructor
    ///
    /// This creates an empty version of a page given a type.
    /// It should be noted that this creates a non-valid pointer
    /// so checks should be made if using this constructor
    ///
    constexpr managed_ptr(nullptr_t) noexcept :
        __managed_ptr<T>{nullptr}
    { }

    /// Nullptr Constructor
    ///
    /// This creates an empty version of a page given a type.
    /// It should be noted that this creates a non-valid pointer
    /// so checks should be made if using this constructor
    ///
    constexpr managed_ptr(nullptr_t) noexcept :
        __managed_ptr<T>{nullptr}
    { }

    /// Move Constructor
    ///
    /// @param u the managed_ptr to move from.
    ///
    managed_ptr(managed_ptr &&u) noexcept :
        __managed_ptr<T>{u}
    { *this = std::move(u); }

    /// Move Operator
    ///
    /// @param u the managed_ptr to move from.
    ///
    managed_ptr &operator=(managed_ptr &&u)
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
    /// @return returns a gsl::span for the managed_ptr;
    ///
    constexpr span_type view() const noexcept
    { return span_type{this->get(), count()}; }

private:
    integer_pointer m_hpa{};
    size_type m_size{};
};

#endif
