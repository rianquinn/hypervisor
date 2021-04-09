/// @copyright
/// Copyright (C) 2020 Assured Information Security, Inc.
///
/// @copyright
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// @copyright
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// @copyright
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

#ifndef HUGE_POOL_T_HPP
#define HUGE_POOL_T_HPP

#include <bsl/byte.hpp>
#include <bsl/construct_at.hpp>
#include <bsl/convert.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/is_standard_layout.hpp>
#include <bsl/is_void.hpp>
#include <bsl/lock_guard.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/span.hpp>
#include <bsl/spinlock.hpp>
#include <bsl/touch.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @class mk::huge_pool_t
    ///
    /// <!-- description -->
    ///   @brief The huge pool provides access to physically contiguous
    ///     memory. The amount of memory that is available is really, really
    ///     small (likely no more than 1 MB), but some is needed for different
    ///     architectures that require it like AMD. This memory is only needed
    ///     by the extensions, and we currently do not support the ability
    ///     to free memory, so there is no need to over complicate how this
    ///     allocator works. We simply use a cursor that is always increasing.
    ///     Once you allocate all of the memory, that is it.
    ///
    ///   TODO:
    ///   - Implement this allocator using a buddy allocator. This way free
    ///     could be supported.
    ///
    /// <!-- template parameters -->
    ///   @tparam PAGE_SIZE defines the size of a page
    ///   @tparam MK_HUGE_POOL_ADDR defines the base address of the huge pool
    ///
    template<bsl::uintmax PAGE_SIZE, bsl::uintmax MK_HUGE_POOL_ADDR>
    class huge_pool_t final
    {
        /// @brief stores true if initialized() has been executed
        bool m_initialized{};
        /// @brief stores the range of memory used by this allocator
        bsl::span<bsl::byte> m_pool{};
        /// @brief stores the huge pool's cursor
        bsl::safe_uintmax m_crsr{};
        /// @brief safe guards operations on the pool.
        mutable bsl::spinlock m_pool_lock{};

    public:
        /// <!-- description -->
        ///   @brief Default constructor
        ///
        constexpr huge_pool_t() noexcept = default;

        /// <!-- description -->
        ///   @brief Creates the huge pool given a mutable_buffer_t to
        ///     the huge pool as well as the virtual address base of the
        ///     huge pool which is used for virt to phys translations.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pool the mutable_buffer_t of the huge pool
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(bsl::span<bsl::byte> &pool) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(m_initialized)) {
                bsl::error() << "huge_pool_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[this]() noexcept -> void {
                this->release();
            }};

            if (bsl::unlikely(pool.empty())) {
                bsl::error() << "pool is empty\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_pool = pool;

            release_on_error.ignore();
            m_initialized = true;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the huge_pool_t
        ///
        constexpr void
        release() &noexcept
        {
            m_crsr = bsl::safe_uintmax::zero(true);
            m_pool = {};

            m_initialized = {};
        }

        /// <!-- description -->
        ///   @brief Destroyes a previously created huge_pool_t
        ///
        constexpr ~huge_pool_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr huge_pool_t(huge_pool_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr huge_pool_t(huge_pool_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(huge_pool_t const &o) &noexcept
            -> huge_pool_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(huge_pool_t &&o) &noexcept
            -> huge_pool_t & = default;

        /// <!-- description -->
        ///   @brief Allocates memory from the huge pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T the type of pointer to return
        ///   @param size the total number of bytes to allocate.
        ///   @return Returns a pointer to the newly allocated memory
        ///
        template<typename T>
        [[nodiscard]] constexpr auto
        allocate(bsl::safe_uintmax const &size) &noexcept -> T *
        {
            bsl::lock_guard lock{m_pool_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "huge_pool_t not initialized\n" << bsl::here();
                return nullptr;
            }

            if (bsl::unlikely(!size)) {
                bsl::error() << "invalid size: "    // --
                             << bsl::hex(size)      // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return nullptr;
            }

            auto pages{size / PAGE_SIZE};
            if ((size % PAGE_SIZE) != bsl::ZERO_UMAX) {
                ++pages;
            }
            else {
                bsl::touch();
            }

            if (bsl::unlikely(m_pool.at_if(m_crsr + (pages * PAGE_SIZE)) == nullptr)) {
                bsl::error() << "huge pool out of memory: "    // --
                             << bsl::hex(size)                 // --
                             << bsl::endl                      // --
                             << bsl::here();                   // --

                return nullptr;
            }

            void *const ptr{m_pool.at_if(m_crsr)};
            m_crsr += (pages * PAGE_SIZE);

            bsl::builtin_memset(ptr, '\0', size);

            if constexpr (!bsl::is_void<T>::value) {
                static_assert(bsl::is_standard_layout<T>::value, "T must be a standard layout");
                bsl::construct_at<T>(ptr);
            }

            return static_cast<T *>(ptr);
        }

        /// <!-- description -->
        ///   @brief Not supported
        ///
        /// <!-- inputs/outputs -->
        ///   @param ptr the pointer to the memory to deallocate
        ///
        constexpr void
        deallocate(void *const ptr) &noexcept
        {
            bsl::lock_guard lock{m_pool_lock};
            bsl::discard(ptr);

            /// NOTE:
            /// - If this function is implemented, we will have to deal with
            ///   deallocations being a page in size. Specifically, right now
            ///   a huge page is allocated and mapped into the page tables
            ///   one page at a time. When is is time to deallocate, this
            ///   memory is released one page at a time. If the page tables
            ///   are deallocating one page of a larger physically contiguous
            ///   memory region, it should be assumed that the entire region
            ///   will be freed, it will just happen in page increments.
            /// - What this means is this function could see a free for the
            ///   same physically contiguous block of memory (one for each
            ///   page in the block). We could ignore the extras, or we
            ///   could set up the allocator so that it frees one page at a
            ///   time. Just depends on how we want to do this... but in
            ///   general, I would suggest using the later as a buddy allocator
            ///   can support this without any added overhead.
            ///
        }

        /// <!-- description -->
        ///   @brief Converts a virtual address to a physical address for
        ///     any memory allocated by the huge pool. If the provided ptr
        ///     was not allocated using the allocate function by the same
        ///     huge pool, this results of this function are UB. It should
        ///     be noted that any virtual address may be used meaning the
        ///     provided address does not have to be page aligned, it simply
        ///     needs to be allocated using the same huge pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T defines the type of virtual address being converted
        ///   @param virt the virtual address to convert
        ///   @return the resulting physical address
        ///
        template<typename T>
        [[nodiscard]] constexpr auto
        virt_to_phys(T const *const virt) const &noexcept -> bsl::safe_uintmax
        {
            static_assert(bsl::disjunction<bsl::is_void<T>, bsl::is_standard_layout<T>>::value);
            return bsl::to_umax(virt) - MK_HUGE_POOL_ADDR;
        }

        /// <!-- description -->
        ///   @brief Converts a physical address to a virtual address for
        ///     any memory allocated by the huge pool. If the provided address
        ///     was not allocated using the allocate function by the same
        ///     huge pool, this results of this function are UB. It should
        ///     be noted that any physical address may be used meaning the
        ///     provided address does not have to be page aligned, it simply
        ///     needs to be allocated using the same huge pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T defines the type of virtual address to convert to
        ///   @param phys the physical address to convert
        ///   @return the resulting virtual address
        ///
        template<typename T>
        [[nodiscard]] constexpr auto
        phys_to_virt(bsl::safe_uintmax const &phys) const &noexcept -> T *
        {
            static_assert(bsl::disjunction<bsl::is_void<T>, bsl::is_standard_layout<T>>::value);
            return bsl::to_ptr<T *>(phys + MK_HUGE_POOL_ADDR);
        }

        /// <!-- description -->
        ///   @brief Dumps the page_pool_t
        ///
        constexpr void
        dump() const &noexcept
        {
            constexpr auto kb{bsl::to_umax(1024)};
            constexpr auto mb{bsl::to_umax(1024) * bsl::to_umax(1024)};

            if (bsl::unlikely(!m_initialized)) {
                bsl::print() << "[error]" << bsl::endl;
                return;
            }

            bsl::print() << bsl::mag << "huge pool dump: ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Header
            ///

            bsl::print() << bsl::ylw << "+-----------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^12s", "description "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^8s", "value "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+-----------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            /// Total
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "total "};
            bsl::print() << bsl::ylw << "| ";
            if ((m_pool.size() / mb).is_zero()) {
                bsl::print() << bsl::rst << bsl::fmt{"4d", m_pool.size() / kb} << " KB ";
            }
            else {
                bsl::print() << bsl::rst << bsl::fmt{"4d", m_pool.size() / mb} << " MB ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Used
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "used "};
            bsl::print() << bsl::ylw << "| ";
            if ((m_crsr / mb).is_zero()) {
                bsl::print() << bsl::rst << bsl::fmt{"4d", m_crsr / kb} << " KB ";
            }
            else {
                bsl::print() << bsl::rst << bsl::fmt{"4d", m_crsr / mb} << " MB ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Remaining
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "remaining "};
            bsl::print() << bsl::ylw << "| ";
            if (((m_pool.size() - m_crsr) / mb).is_zero()) {
                bsl::print() << bsl::rst << bsl::fmt{"4d", (m_pool.size() - m_crsr) / kb} << " KB ";
            }
            else {
                bsl::print() << bsl::rst << bsl::fmt{"4d", (m_pool.size() - m_crsr) / mb} << " MB ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Footer
            ///

            bsl::print() << bsl::ylw << "+-----------------------+";
            bsl::print() << bsl::rst << bsl::endl;
        }
    };
}

#endif
