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

#include "../papis/memory_manager.h"

// -----------------------------------------------------------------------------
// Memory Manager Interface Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::uapis
{

/// Memory Manager
///
/// The memory manager has a couple specific functions:
/// - hva->hpa / hpa->hva conversions
/// - allocate pages
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
/// Allocating memory is handled by the m_implementation itself. The VMM has a
/// SLAB/Buddy style allocator scheme which is very similar to the Linux
/// kernel. This is a simple, yet effective allocator designed specifically to
/// ensure external fragmentation is limited as much as possible. As a result,
/// the VMM can be a memory hog if not used properly, just like Linux, but
/// allocations are far less likely to take down the system. The memory manager
/// only exposes the ability to allocate a page of memory, and this is done
/// because the VMM must allocate a lot pages, which must be page aligned.
/// If you need to allocate regular memory, use a std::unique_ptr (as new,
/// delete, malloc, free should be avoided). Any allocate that is greater than
/// or equal to a page is guaranteed to be page aligned, and the allocation
/// size will be a multiple of 2. However, if you need to allocate a page,
/// the memory manager provides a type-safe mechanism for doing this. Note that
/// the resulting object is a std::unqiue_ptr, and the only thing that this
/// function is doing is allocating a page in a type-safe manner.
///
/// Memory mapping (specifically mapping an HPA to a HVA) is also provided by
/// the arch version of the memory manager (adhering to the memory manager
/// concept). These facilities are used to provide the host with a means to
/// access a host physical address. This is mainly needed when the host must
/// access guest memory. It should be noted that this type of access should only
/// be done for introspection. Sadly, host hardware virtualization extensions
/// require the use of instruction emulation, which at times must also map in
/// memory, so these types of instructions should be avoided whenever possible
/// as the mapping operation is slow, and it exposes the VMM to guest memory
/// which should be considered malicious at all times. You might think you can
/// m_implement this type of emulation safely, but you would be wrong. Also note
/// that once again, the memory manager provides the maps, but if you need to
/// access guest memory, you should be using the EPT APIs as these APIs provide
/// the needed conversions for GVA->GPA->HPA which would then be used by these
/// map functions to get a HVA that can be used to access the initial GVA.
///
/// One final note. If you run into allocation issues, it might be because you
/// are using too much host memory. The host has a limited amount of memory,
/// which is provided by the bfdriver. In some cases (i.e. if you are creating
/// multiple, per-vcpu EPT tables with 4k granularity for hundreds of guests)
/// you might need to tell the bfdriver to provide more memory to the host.
/// This can be done using the driver's IOCTL interface.
///
template<typename IMPL>
class memory_manager :
    public papis::memory_manager<IMPL>
{
public:

    /// @cond

    using pointer = typename papis::memory_manager<IMPL>::pointer;
    using integer_pointer = typename papis::memory_manager<IMPL>::integer_pointer;
    using size_type = typename papis::memory_manager<IMPL>::size_type;
    using attr_type = typename papis::memory_manager<IMPL>::attr_type;

    /// @endcond

public:

    /// Default Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    explicit memory_manager() noexcept = default;

    /// Host Virtual Address (HVA) to Host Physical Address (HPA)
    ///
    /// Given a host virtual address, this function will provide the host
    /// physical address for any address that was added using add_md().
    ///
    /// NOTE:
    ///
    /// add_md() is not called when you map in memory into the host page tables
    /// (for example when using a unique_map) and instead is called when memory
    /// is added to the host by bfdriver. If you need a conversion for mapped
    /// memory, use the host page tables.
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
    /// @ensures return != 0
    ///
    /// @param hva the host virtual address to convert
    /// @return host physical address
    ///
    constexpr integer_pointer hva_to_hpa(integer_pointer hva) const
    { return this->m_impl.hva_to_hpa(hva); }

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
    /// @ensures return != 0
    ///
    /// @param hpa the host physical address to convert
    /// @return host virtual address
    ///
    constexpr integer_pointer hpa_to_hva(integer_pointer hpa) const
    { return this->m_impl.hpa_to_hva(hpa); }

    /// Adds Memory Descriptor
    ///
    /// Adds a memory descriptor to the memory manager. A memory descriptor is
    /// is nothing more than a host physical address / host virtual address
    /// pair (as well as the pair's attributes like read, write, etc...). The
    /// host has a chicken/egg problem (much like most kernels) in that it
    /// is given memory to work with, but then needs to be able to perform
    /// virtual to physical conversions to set up the page tables, which could
    /// then be used for this same conversion. To handle this problem, the host
    /// stores these descriptors for the memory it is given in a lookup table.
    /// This not only provides a solution to the chicken/egg issue, but it also
    /// provides a fast mechanism for performing these conversions (instead of
    /// having to use the pages tables), which is important because the mapping
    /// logic needs a fast mechanism for performing these conversions when it
    /// needs to add page tables to the host on a map operation.
    ///
    /// It should be noted that the lookup table comes at a cost. Specifically
    /// these descriptors are stored twice. Once in the lookup table, and again
    /// in the host's page tables. The more memory the host is given, the
    /// larger this lookup table will be. For this reason, the host doesn't give
    /// guests its own memory and instead a guest must donate or share memory
    /// with another guest (with the difference being that a donation prevents
    /// a gust from accessing memory it donates). Compared to other hypervisors
    /// like Xen, this dramatically reduces the issue with bookkeeping in the
    /// host at a cost as now all memory must be allocated by a guest which
    /// must perform GVA -> HPA conversions.
    ///
    /// @expects hva != 0
    /// @expects hpa != 0
    /// @expects attr != 0
    /// @expects hva is page aligned
    /// @expects hpa ia page aligned
    /// @ensures
    ///
    /// @param hva the host virtual address
    /// @param hpa the host physical address that is mapped to the hpa
    /// @param attr how the hva was mapped
    ///
    constexpr void add_md(
        integer_pointer hva, integer_pointer hpa, attr_type attr)
    { this->m_impl.add_md(hva, hpa, attr); }
};

}

// -----------------------------------------------------------------------------
// Instance
// -----------------------------------------------------------------------------

namespace bfvmm::memory_manager
{
    /// Memory Manager Type
    ///
    using memory_manager_t = uapis::memory_manager<implementation::memory_manager>;

    /// Memory Manager Instance
    ///
    /// The host has only one memory manager. We don't make this a global
    /// instance because global construction could be performed in any order
    /// and as a result, we could end up with memory allocation before the
    /// memory manager is constructed, so instead, you must access the
    /// memory manager through this function which ensures static construction.
    ///
    /// @expects
    /// @ensures ret != nullptr
    ///
    /// @return a pointer to the memory manager
    ///
    inline auto instance() noexcept
    {
        static memory_manager_t s_mm;
        return &s_mm;
    }
}

/// Memory Manager Macro
///
/// Since this might be used a lot, this macro provides a simple shortcut
/// for the memory manager to reduce verbosity.
///
#define g_mm bfvmm::memory_manager::instance()

// -----------------------------------------------------------------------------
// Wrappers
// -----------------------------------------------------------------------------

namespace bfvmm::memory_manager
{
    /// @cond

    using pointer = typename memory_manager_t::pointer;
    using integer_pointer = typename memory_manager_t::integer_pointer;
    using size_type = typename memory_manager_t::size_type;
    using attr_type = typename memory_manager_t::attr_type;

    /// @endcond

    /// HVA to HPA (Wrapper)
    ///
    /// Wraps the hva_to_hpa() function.
    ///
    /// @code
    /// instance()->hva_to_hpa(...);
    /// @endcode
    ///
    /// or
    ///
    /// @code
    /// memory_manager::hva_to_hpa(...);
    /// @endcode
    ///
    /// @expects
    /// @ensures
    ///
    /// @param args hva_to_hpa() arguments
    ///
    template<typename... Args>
    constexpr auto hva_to_hpa(Args &&...args)
    { return instance()->hva_to_hpa(std::forward<Args>(args)...); }

    /// HPA to HVA (Wrapper)
    ///
    /// Wraps the hpa_to_hva() function.
    ///
    /// @code
    /// instance()->hpa_to_hva(...);
    /// @endcode
    ///
    /// or
    ///
    /// @code
    /// memory_manager::hpa_to_hva(...);
    /// @endcode
    ///
    /// @expects
    /// @ensures
    ///
    /// @param args hpa_to_hva() arguments
    ///
    template<typename... Args>
    constexpr auto hpa_to_hva(Args &&...args)
    { return instance()->hpa_to_hva(std::forward<Args>(args)...); }

    /// Add Memory Descriptor (Wrapper)
    ///
    /// Wraps the add_md() function.
    ///
    /// @code
    /// instance()->add_md(...);
    /// @endcode
    ///
    /// or
    ///
    /// @code
    /// memory_manager::add_md(...);
    /// @endcode
    ///
    /// @expects
    /// @ensures
    ///
    /// @param args add_md() arguments
    ///
    template<typename... Args>
    constexpr void add_md(Args &&...args)
    { instance()->add_md(std::forward<Args>(args)...); }
}

#endif
