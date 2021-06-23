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

#include "lock_guard_t.hpp"
#include "spinlock_t.hpp"

#include <tls_t.hpp>

#include <bsl/byte.hpp>
#include <bsl/construct_at.hpp>
#include <bsl/convert.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/is_standard_layout.hpp>
#include <bsl/is_void.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/span.hpp>
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
    class huge_pool_t final
    {
        /// @brief stores true if initialized() has been executed
        bool m_initialized{};
        /// @brief stores the range of memory used by this allocator
        bsl::span<bsl::byte> m_pool{};
        /// @brief stores the huge pool's cursor
        bsl::safe_uintmax m_crsr{};
        /// @brief safe guards operations on the pool.
        mutable spinlock_t m_lock{};

    public:
        /// <!-- description -->
        ///   @brief Creates the huge pool given a mutable_buffer_t to
        ///     the huge pool as well as the virtual address base of the
        ///     huge pool which is used for virt to phys translations.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pool the mutable_buffer_t of the huge pool
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
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
            m_crsr = bsl::safe_uintmax::failure();
            m_pool = {};

            m_initialized = {};
        }

        /// <!-- description -->
        ///   @brief Allocates memory from the huge pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T the type of pointer to return
        ///   @param tls the current TLS block
        ///   @param size the total number of bytes to allocate.
        ///   @return Returns a pointer to the newly allocated memory
        ///
        template<typename T = void>
        [[nodiscard]] constexpr auto
        allocate(tls_t &tls, bsl::safe_uintmax const &size) &noexcept -> T *
        {
            lock_guard_t lock{tls, m_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "huge_pool_t not initialized\n" << bsl::here();
                return nullptr;
            }

            if (bsl::unlikely(!size)) {
                bsl::error() << "invalid size "    // --
                             << bsl::hex(size)     // --
                             << bsl::endl          // --
                             << bsl::here();       // --

                return nullptr;
            }

            constexpr auto aligned{0_umax};
            auto pages{size / HYPERVISOR_PAGE_SIZE};

            if ((size % HYPERVISOR_PAGE_SIZE) != aligned) {
                ++pages;
            }
            else {
                bsl::touch();
            }

            if (bsl::unlikely(m_pool.at_if(m_crsr + (pages * HYPERVISOR_PAGE_SIZE)) == nullptr)) {
                bsl::error() << "huge pool out of memory\n" << bsl::here();
                return nullptr;
            }

            void *const ptr{m_pool.at_if(m_crsr)};
            m_crsr += (pages * HYPERVISOR_PAGE_SIZE);

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
        ///   @param tls the current TLS block
        ///   @param ptr the pointer to the memory to deallocate
        ///
        constexpr void
        deallocate(tls_t &tls, void *const ptr) &noexcept
        {
            lock_guard_t lock{tls, m_lock};
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
        template<typename T = void>
        [[nodiscard]] constexpr auto
        virt_to_phys(T const *const virt) const &noexcept -> bsl::safe_uintmax
        {
            static_assert(bsl::disjunction<bsl::is_void<T>, bsl::is_standard_layout<T>>::value);
            return bsl::to_umax(virt) - HYPERVISOR_MK_HUGE_POOL_ADDR;
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
        template<typename T = void>
        [[nodiscard]] constexpr auto
        phys_to_virt(bsl::safe_uintmax const &phys) const &noexcept -> T *
        {
            static_assert(bsl::disjunction<bsl::is_void<T>, bsl::is_standard_layout<T>>::value);
            return bsl::to_ptr<T *>(phys + HYPERVISOR_MK_HUGE_POOL_ADDR);
        }

        /// <!-- description -->
        ///   @brief Dumps the page_pool_t
        ///
        constexpr void
        dump() const &noexcept
        {
            constexpr auto kb{1024_umax};
            constexpr auto mb{kb * kb};

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
