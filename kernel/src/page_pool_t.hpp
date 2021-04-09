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

#ifndef PAGE_POOL_T_HPP
#define PAGE_POOL_T_HPP

#include <page_pool_record_t.hpp>

#include <bsl/array.hpp>
#include <bsl/construct_at.hpp>
#include <bsl/convert.hpp>
#include <bsl/cstring.hpp>
#include <bsl/debug.hpp>
#include <bsl/disjunction.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/is_standard_layout.hpp>
#include <bsl/is_void.hpp>
#include <bsl/lock_guard.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/span.hpp>
#include <bsl/spinlock.hpp>
#include <bsl/string_view.hpp>
#include <bsl/touch.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @brief stores the max number of records the page pool can store
    constexpr bsl::safe_uintmax PAGE_POOL_MAX_RECORDS{bsl::to_umax(25)};

    /// @class mk::page_pool_t
    ///
    /// <!-- description -->
    ///   @brief The page pool is responsible for allocating and freeing
    ///      pages. The page pool exists in the MK's direct map and so the
    ///      page pool can also return the physical address of any page
    ///      that it has allocated. The page pool itself is actually initalized
    ///      by the loader, which has all of the information about each page
    ///      in the pool as well as what it's physical address is, which is
    ///      encoded in the resulting virtual address, thus creating a
    ///      direct map. The way that the loader sets this page pool up is
    ///      as follows:
    ///
    ///      ----------       ----------       ----------
    ///      | [] ----|------>| [] ----|------>|        |
    ///      |        |       |        |       |        |
    ///      |        |       |        |       |        |
    ///      ----------       ----------       ----------
    ///
    ///      The head (a void *) is actually a pointer to another void *. Each
    ///      pointer actually points to a page, and it assumes that the first
    ///      64bits in the page are a pointer to the next page. This is
    ///      repeated until the last page is linked which stores a nullptr.
    ///      To allocate, all you have to do is pop off of the head of the
    ///      stack and set the new head to the page the popped page was
    ///      storing. To deallocate, all you have to do is set the page being
    ///      deallocated to point to the current head, and then set the head
    ///      to this newly deallocated page. This ensures the page pool can
    ///      allocate and deallocate in O(1), and there is no metadata that
    ///      is needed, so no additional overhead.
    ///
    ///      To handle virt to phys and phys to virt conversions, each page
    ///      is mapped into the microkernel's address space at the physical
    ///      address + some offset. This means that virt to phys conversions
    ///      can all be done with simple arithmetic (i.e., no lookups are
    ///      needed). This is what is typically called a direct map.
    ///
    /// <!-- template parameters -->
    ///   @tparam PAGE_SIZE defines the size of a page
    ///   @tparam MK_PAGE_POOL_ADDR defines the base address of the page pool
    ///
    template<bsl::uintmax PAGE_SIZE, bsl::uintmax MK_PAGE_POOL_ADDR>
    class page_pool_t final
    {
        /// @brief stores true if initialized() has been executed
        bool m_initialized{};
        /// @brief stores the head of the page pool stack.
        void *m_head{};
        /// @brief stores the total number of bytes given to the page pool.
        bsl::safe_uintmax m_size{};
        /// @brief stores information about how memory is allocated
        bsl::array<page_pool_record_t, PAGE_POOL_MAX_RECORDS.get()> m_rcds{};
        /// @brief safe guards operations on the pool.
        mutable bsl::spinlock m_pool_lock{};

    public:
        /// <!-- description -->
        ///   @brief Default constructor
        ///
        constexpr page_pool_t() noexcept = default;

        /// <!-- description -->
        ///   @brief Creates the page pool given a mutable_buffer_t to
        ///     the page pool as well as the virtual address base of the
        ///     page pool which is used for virt to phys translations.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pool the mutable_buffer_t of the page pool
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(bsl::span<bsl::byte> &pool) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(m_initialized)) {
                bsl::error() << "page_pool_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[this]() noexcept -> void {
                this->release();
            }};

            if (bsl::unlikely(pool.empty())) {
                bsl::error() << "pool is empty\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_head = pool.data();
            m_size = pool.size();

            release_on_error.ignore();
            m_initialized = true;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the page_pool_t
        ///
        constexpr void
        release() &noexcept
        {
            for (auto const elem : m_rcds) {
                *elem.data = {};
            }

            m_size = {};
            m_head = {};

            m_initialized = {};
        }

        /// <!-- description -->
        ///   @brief Destroyes a previously created page_pool_t
        ///
        constexpr ~page_pool_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr page_pool_t(page_pool_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr page_pool_t(page_pool_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(page_pool_t const &o) &noexcept
            -> page_pool_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(page_pool_t &&o) &noexcept
            -> page_pool_t & = default;

        /// <!-- description -->
        ///   @brief Allocates a page from the page pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T the type of pointer to return
        ///   @param tag the tag to mark the allocation with
        ///   @return Returns a pointer to the newly allocated page
        ///
        template<typename T>
        [[nodiscard]] constexpr auto
        allocate(bsl::string_view const &tag) &noexcept -> T *
        {
            bsl::lock_guard lock{m_pool_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "page_pool_t not initialized\n" << bsl::here();
                return nullptr;
            }

            if (tag.empty()) {
                bsl::error() << "invalid empty tag"    // --
                             << bsl::endl              // --
                             << bsl::here();           // --

                return nullptr;
            }

            if (bsl::unlikely(nullptr == m_head)) {
                bsl::error() << "page pool out of pages\n" << bsl::here();
                return nullptr;
            }

            page_pool_record_t *record{};
            for (auto const elem : m_rcds) {
                if (elem.data->tag.data() == tag.data()) {
                    record = elem.data;
                    break;
                }

                bsl::touch();
            }

            if (nullptr == record) {
                for (auto const elem : m_rcds) {
                    if (elem.data->tag.empty()) {
                        record = elem.data;
                        record->tag = tag;
                        break;
                    }

                    bsl::touch();
                }
            }
            else {
                bsl::touch();
            }

            if (nullptr == record) {
                bsl::error() << "page pool out of space for tags\n" << bsl::here();
                return nullptr;
            }

            void *const ptr{m_head};
            m_head = *static_cast<void **>(m_head);
            record->usd += PAGE_SIZE;

            bsl::builtin_memset(ptr, '\0', PAGE_SIZE);

            if constexpr (!bsl::is_void<T>::value) {
                static_assert(bsl::is_standard_layout<T>::value, "T must be a standard layout");
                bsl::construct_at<T>(ptr);
            }

            return static_cast<T *>(ptr);
        }

        /// <!-- description -->
        ///   @brief Returns a page previously allocated using the allocate
        ///     function to the page pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @param ptr the pointer to the page to deallocate
        ///   @param tag the tag the allocation was marked with
        ///
        constexpr void
        deallocate(void *const ptr, bsl::string_view const &tag) &noexcept
        {
            bsl::lock_guard lock{m_pool_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "page_pool_t not initialized\n" << bsl::here();
                return;
            }

            if (bsl::unlikely(nullptr == ptr)) {
                return;
            }

            if (bsl::to_umax(ptr) < MK_PAGE_POOL_ADDR) {
                bsl::error() << "invalid ptr"    // --
                             << ptr              // --
                             << bsl::endl        // --
                             << bsl::here();

                return;
            }

            if (tag.empty()) {
                bsl::error() << "invalid empty tag"    // --
                             << bsl::endl              // --
                             << bsl::here();           // --

                return;
            }

            page_pool_record_t *record{};
            for (auto const elem : m_rcds) {
                if (elem.data->tag.data() == tag.data()) {
                    record = elem.data;
                    break;
                }

                bsl::touch();
            }

            if (nullptr == record) {
                bsl::error() << "invalid tag: "    // --
                             << tag                // --
                             << bsl::endl          // --
                             << bsl::here();       // --

                return;
            }

            *static_cast<void **>(ptr) = m_head;
            m_head = ptr;
            record->usd -= PAGE_SIZE;
        }

        /// <!-- description -->
        ///   @brief Converts a virtual address to a physical address for
        ///     any page allocated by the page pool. If the provided ptr
        ///     was not allocated using the allocate function by the same
        ///     page pool, this results of this function are UB. It should
        ///     be noted that any virtual address may be used meaning the
        ///     provided address does not have to be page aligned, it simply
        ///     needs to be allocated using the same page pool.
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
            return bsl::to_umax(virt) - MK_PAGE_POOL_ADDR;
        }

        /// <!-- description -->
        ///   @brief Converts a physical address to a virtual address for
        ///     any page allocated by the page pool. If the provided address
        ///     was not allocated using the allocate function by the same
        ///     page pool, this results of this function are UB. It should
        ///     be noted that any physical address may be used meaning the
        ///     provided address does not have to be page aligned, it simply
        ///     needs to be allocated using the same page pool.
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
            return bsl::to_ptr<T *>(phys + MK_PAGE_POOL_ADDR);
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

            bsl::print() << bsl::mag << "page pool dump: ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Header
            ///

            bsl::print() << bsl::ylw << "+----------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::blu << bsl::fmt{"^33s", "overview "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+----------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^23s", "description "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^8s", "value "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+----------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::safe_uintmax usd{};
            for (auto const elem : m_rcds) {
                usd += elem.data->usd;
            }

            /// Total
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<23s", "total "};
            bsl::print() << bsl::ylw << "| ";
            if ((m_size / mb).is_zero()) {
                bsl::print() << bsl::rst << bsl::fmt{"4d", m_size / kb} << " KB ";
            }
            else {
                bsl::print() << bsl::rst << bsl::fmt{"4d", m_size / mb} << " MB ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Used
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<23s", "used "};
            bsl::print() << bsl::ylw << "| ";
            if ((usd / mb).is_zero()) {
                bsl::print() << bsl::rst << bsl::fmt{"4d", usd / kb} << " KB ";
            }
            else {
                bsl::print() << bsl::rst << bsl::fmt{"4d", usd / mb} << " MB ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Remaining
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<23s", "remaining "};
            bsl::print() << bsl::ylw << "| ";
            if (((m_size - usd) / mb).is_zero()) {
                bsl::print() << bsl::rst << bsl::fmt{"4d", (m_size - usd) / kb} << " KB ";
            }
            else {
                bsl::print() << bsl::rst << bsl::fmt{"4d", (m_size - usd) / mb} << " MB ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Tags
            ///

            bsl::print() << bsl::ylw << "+----------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::rst << bsl::endl;
            bsl::print() << bsl::ylw << "+----------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::blu << bsl::fmt{"^33s", "breakdown "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+----------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^23s", "description "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^8s", "value "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+----------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            for (auto const elem : m_rcds) {
                if (elem.data->tag.empty()) {
                    continue;
                }

                bsl::print() << bsl::ylw << "| ";
                bsl::print() << bsl::rst << bsl::fmt{"<23s", elem.data->tag};
                bsl::print() << bsl::ylw << "| ";
                if ((elem.data->usd / mb).is_zero()) {
                    bsl::print() << bsl::rst << bsl::fmt{"4d", elem.data->usd / kb} << " KB ";
                }
                else {
                    bsl::print() << bsl::rst << bsl::fmt{"4d", elem.data->usd / mb} << " MB ";
                }
                bsl::print() << bsl::ylw << "| ";
                bsl::print() << bsl::rst << bsl::endl;
            }

            /// Footer
            ///

            bsl::print() << bsl::ylw << "+----------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;
        }
    };
}

#endif
