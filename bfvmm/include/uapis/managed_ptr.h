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

#ifndef UAPIS_MANAGED_PTR_H
#define UAPIS_MANAGED_PTR_H

#include <memory>

#include <bfgsl.h>
#include "../implementation/memory_manager.h"

// -----------------------------------------------------------------------------
// Definition
// -----------------------------------------------------------------------------

/// Managed Ptr
///
/// The std::unique_ptr has a lot of issues with it that prevent it from
/// being useful in our case:
/// - The [] syntax that it has is not C++ Core Guideline compliant so we cannot
///   use it. Really it should be removed from the spec because the unique_ptr
///   has no way of remembering the size of the allocation that is made so it
///   has no way to safely checking bounds. We do however need this
///   functionality in the spec, but using the .at() syntax.
/// - Sometimes we want to allocate a pointer, but we want the total size to
///   be a page and not sizeof(T).
/// - We need the ability to get the HVA and HPA in integer form for the pointer
///   that is allocated.
/// - We don't always want to free the memory that we are getting a pointer to.
///   Normally you would just use a gsl::span for that, but that doesn't work
///   if you need to handle the case where memory should be deleted in one
///   instance, and not in another (like we have if the GDT and IDT).
/// - For some reason, a std::unique_ptr is not easy to work with WRT passing
///   to a poiinter type or through static casting which we also attempt to
///   address here as well.
///
/// The goal of this wrapper is to address this issue with std::unique_ptr.
/// Note that we do not
///
template<typename T, typename D = std::default_delete<T>>
class managed_ptr :
    public std::unique_ptr<T, D>
{
    using base_type = std::unique_ptr<T, D>;

public:

    /// @cond

    using pointer = typename std::unique_ptr<T>::pointer;
    using element_type = typename std::unique_ptr<T>::element_type;
    using deleter_type = decltype(D);
    using integer_pointer = uint64_t;
    using size_type = std::size_t;

    /// @endcond

public:

    constexpr managed_ptr() noexcept :
        base_type{},
        m_hpa{0},
        m_size{0}
    { }

    constexpr managed_ptr(nullptr_t) noexcept :
        base_type{},
        m_hpa{0},
        m_size{0}
    { }

    explicit managed_ptr(pointer p, size_type s = sizeof(T)) noexcept :
        base_type{p},
        m_hpa{g_mm->hva_to_hpa(this->hva())}
        m_size{s}
    { }

    explicit managed_ptr(pointer p, D &&d, size_type s = sizeof(T)) noexcept :
        base_type{p, std::forward<D>(d)},
        m_hpa{g_mm->hva_to_hpa(this->hva())}
        m_size{s}
    { }

    managed_ptr(managed_ptr &&other) noexcept
    { *this = std::move(other); }

    managed_ptr &operator=(managed_ptr &&other) noexcept
    {
        m_hva = std::move(other.m_hva);
        m_size = std::move(other.m_size);
        other.m_hva = 0;
        other.m_size = 0;

        base_type::operator=(std::move(other));
        return *this;
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
    constexpr auto view() const noexcept
    { return gsl::span{this->get(), m_size}; }

private:
    integer_pointer m_hpa{};
    size_type m_size{};
};

#endif
