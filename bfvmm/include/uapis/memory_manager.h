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

#ifndef UAPIS_MEMORY_MANAGER_H
#define UAPIS_MEMORY_MANAGER_H

#include <bfgsl.h>
#include <bftypes.h>
#include <bfmemory.h>
#include <bfconstants.h>

#include "impl.h"

// -----------------------------------------------------------------------------
// Memory Manager Definition
// -----------------------------------------------------------------------------

namespace bfvmm::uapis
{

/// Memory Manager
///
/// The memory manager has a couple specific functions:
/// - hva->hpa / hpa->hva conversions
/// - allocate memory
/// - map memory
///
/// To support hva->hpa / hpa->hva conversions, the memory manager uses the
/// add_md() to add hva/hpa pairs to a lookup table (which is usually only
/// called by the bfdriver when adding memory to the host) which can then be
/// used by the user to perform any needed conversions. It should be noted that
/// these conversions are only for hva/hpa pairs that were added using add_md()
/// which DOES NOT include maps. If you map memory into the host and then need
/// to perform a conversion (something that should not happen often), you must
/// use the host's page tables to perform the lookup and the only operation that
/// is possible is the hva->hpa conversion. These functions also only work with
/// host memory. This does not include guest memory. As a reminder, the host OS
/// (not to be confused with the host, which is another name for the VMM) is a
/// guest. We call it the host OS simply because it is the OS that is hosting
/// the system, but from the VMM's point of view, it should be viewed as a
/// guest, especially when attempting to work with it's memory. All of these
/// types of guest operations should be done using the EPT APIs.
///
/// Allocating memory is handled by the implementation itself. The VMM has a
/// SLAB/Buddy style allocator scheme which is very similar to the Linux
/// kernel. This is a simple, yet effective allocator designed specifically to
/// ensure external fragmentation is limited as much as possible. As a result,
/// the VMM can be a memory hog if not used properly, just like Linux, but
/// allocations are far less likely to take down the system. Any allocation
/// that is greater than or equal to a page is guaranteed to be page aligned,
/// and the allocation size will be a multiple of 2. To allocate memory, the
/// C++ Core Guideline compliant way to do this is with std::unique_ptr and
/// std::shared_ptr. We also provide a unique_page which is capable of
/// allocating pages, and it provides the HVA/HPA associated with the page as
/// needed.
///
/// Memory mapping (specifically mapping an HPA to a HVA) is provided by the
/// unique_map class. Like the unique_page, this class is the same thing as a
/// unique_ptr with some additional functions for working with the unique_map
/// such as a gsl::span. Although maps should be used rarely as they are
/// expensive, its the only way to work with physical memory. If you are
/// attempting to map in guest memory, you must use the EPT APIs as those APIs
/// are the only APIs capable of working with guest memory, including memory
/// originating from the host OS.
///
/// One final note. If you run into allocation issues, it might be because you
/// are using too much host memory. The host has a limited amount of memory,
/// which is provided by the bfdriver. In some cases (i.e. if you are creating
/// multiple, per-vcpu EPT tables with 4k granularity for hundreds of guests)
/// you might need to tell the bfdriver to provide more memory to the host.
/// This can be done using the driver's IOCTL interface, or simply telling
/// BFM to use more memory.
///
template<typename IMPL>
struct memory_manager
{
    using pointer = void *;                                 ///< Pointer type
    using integer_pointer = uint64_t;                       ///< Interger pointer type
    using size_type = std::size_t;                          ///< Size type
    using attr_type = decltype(memory_descriptor::type);    ///< Attribute type

    /// Host Virtual Address (HVA) to Host Physical Address (HPA)
    ///
    /// Given a host virtual address, this function will provide the host
    /// physical address for any address that was added using add_md().
    ///
    /// NOTE:
    ///
    /// add_md() is not called when you map in memory into the host page tables
    /// (for example when using a unique_map) and instead is called when memory
    /// is added to the host by bfdriver.
    ///
    /// NOTE:
    ///
    /// This does not convert a guest virtual address (GVA) to an HPA. The
    /// host (i.e. the VMM) has its own set of page tables which are different
    /// from the guest (unlike other hypervisors like SimpleVisor) so if you
    /// are used to this type of API set, you need to use the EPT APIs as EPT
    /// provides all of the functions needed to convert a GVA to an HPA as
    /// well as mapping GVAs to an HVA so that the host can access guest memory.
    ///
    /// @expects hva != 0
    /// @ensures ret != 0
    ///
    /// @param hva the host virtual address to convert
    /// @return host physical address
    ///
    constexpr integer_pointer hva_to_hpa(integer_pointer hva) const
    { return impl<const IMPL>(this)->__hva_to_hpa(hva); }

    /// Host Physical Address (HPA) to Host Virtual Address (HVA)
    ///
    /// Given a host physical address, this function will provide the host
    /// virtual address for any address that was added using add_md().
    ///
    /// NOTE:
    ///
    /// add_md() is not called when you map in memory into the host page tables
    /// (for example when using a unique_map) and instead is called when memory
    /// is added to the host by bfdriver. There is no way to perform this
    /// type of conversion as there is no logical way to traverse the host
    /// page tables to convert a physical address to a virtual address. This
    /// function is only used for a small subset of functions that must ensure
    /// the host memory was allocated and not mapped.
    ///
    /// NOTE:
    ///
    /// This does not convert a guest physical address (GPA) to an HVA. The
    /// host (i.e. the VMM) has its own set of page tables which are different
    /// from the guest (unlike other hypervisors like SimpleVisor). Just like
    /// above, we do not provide APIs for performing this type of conversion
    /// as there is no logical way to convert a physical address to a virtual
    /// address. You are welcome to write your own APIs using the EPT APIs
    /// that we do provide, just be warned that it is possible to map the same
    /// physical address to multiple virtual addresses.
    ///
    /// @expects hpa != 0
    /// @ensures ret != 0
    ///
    /// @param hpa the host physical address to convert
    /// @return host virtual address
    ///
    constexpr integer_pointer hpa_to_hva(integer_pointer hpa) const
    { return impl<const IMPL>(this)->__hpa_to_hva(hpa); }

    /// Instance
    ///
    /// @expects
    /// @ensures ret != nullptr
    ///
    /// @return returns a singleton instance of the memory manager.
    ///
    constexpr static gsl::not_null<IMPL *>
    instance() noexcept
    { return IMPL::__instance(); }
};

}

// -----------------------------------------------------------------------------
// Singleton Reference
// -----------------------------------------------------------------------------

/// Single Shortcut
///
/// This macro provides a shortcut to the memory manager (to reduce verbosity).
/// Like the instance function, this will not return a nullptr.
///

#ifndef g_mm
#define g_mm bfvmm::implementation::memory_manager::instance()
#endif

// -----------------------------------------------------------------------------
// Alloc/Free Pages
// -----------------------------------------------------------------------------

/// Allocate Page
///
/// Allocates a page of memory. This is a lot fast than using malloc() as it
/// bypasses some logic to get a page directly from the buddy allocator. Note
/// that this should only be used when a unique_page cannot be as that interface
/// is a lot easier to use and is Core Guideline compliant.
///
/// @expects
/// @ensures
///
/// @return a pointer to a page of memory
///
void *alloc_page() noexcept;

/// Free Page
///
/// Frees a page of memory. This is a lot fast than using free() as it
/// bypasses some logic to free a page directly from the buddy allocator. Note
/// that this should only be used when a unique_page cannot be as that interface
/// is a lot easier to use and is Core Guideline compliant.
///
/// @expects
/// @ensures
///
/// @param ptr a pointer to a page of memory
///
void free_page(void *ptr) noexcept;

/// Alloc Page (Template)
///
/// Allocates a page of memory. This is a lot fast than using malloc() as it
/// bypasses some logic to get a page directly from the buddy allocator. Note
/// that this should only be used when a unique_page cannot be as that interface
/// is a lot easier to use and is Core Guideline compliant.
///
/// @expects
/// @ensures
///
/// @return a pointer to a page of memory
///
template<typename T> T
constexpr *alloc_page() noexcept
{
    static_assert(sizeof(T) <= BFPAGE_SIZE);
    return static_cast<T *>(alloc_page());
}

// -----------------------------------------------------------------------------
// Wrappers
// -----------------------------------------------------------------------------

/// @cond

namespace bfvmm::memory_manager
{

template<typename IMPL>
constexpr auto hva_to_hpa(
    gsl::not_null<IMPL *> mm, typename bfvmm::uapis::memory_manager<IMPL>::integer_pointer hva)
{ return mm->hva_to_hpa(hva); }

template<typename RET, typename IMPL>
constexpr auto hva_to_hpa(
    gsl::not_null<IMPL *> mm, typename bfvmm::uapis::memory_manager<IMPL>::integer_pointer hva)
{ return reinterpret_cast<RET>(mm->hva_to_hpa(hva)); }

template<typename IMPL>
constexpr auto hva_to_hpa(
    gsl::not_null<IMPL *> mm, void *hva)
{ return mm->hva_to_hpa(reinterpret_cast<typename bfvmm::uapis::memory_manager<IMPL>::integer_pointer>(hva)); }

template<typename RET, typename IMPL>
constexpr auto hva_to_hpa(
    gsl::not_null<IMPL *> mm, void *hva)
{ return reinterpret_cast<RET>(mm->hva_to_hpa(reinterpret_cast<typename bfvmm::uapis::memory_manager<IMPL>::integer_pointer>(hva))); }

template<typename IMPL>
constexpr auto hpa_to_hva(
    gsl::not_null<IMPL *> mm, typename bfvmm::uapis::memory_manager<IMPL>::integer_pointer hpa)
{ return mm->hpa_to_hva(hpa); }

template<typename RET, typename IMPL>
constexpr auto hpa_to_hva(
    gsl::not_null<IMPL *> mm, typename bfvmm::uapis::memory_manager<IMPL>::integer_pointer hpa)
{ return reinterpret_cast<RET>(mm->hpa_to_hva(hpa)); }

template<typename IMPL>
constexpr auto hpa_to_hva(
    gsl::not_null<IMPL *> mm, void *hpa)
{ return mm->hpa_to_hva(reinterpret_cast<typename bfvmm::uapis::memory_manager<IMPL>::integer_pointer>(hpa)); }

template<typename RET, typename IMPL>
constexpr auto hpa_to_hva(
    gsl::not_null<IMPL *> mm, void *hpa)
{ return reinterpret_cast<RET>(mm->hpa_to_hva(reinterpret_cast<typename bfvmm::uapis::memory_manager<IMPL>::integer_pointer>(hpa))); }

}

/// @endcond

#endif
