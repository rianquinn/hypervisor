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

#ifndef VM_POOL_T_HPP
#define VM_POOL_T_HPP

#include <bsl/array.hpp>
#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/lock_guard.hpp>
#include <bsl/spinlock.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @class mk::vm_pool_t
    ///
    /// <!-- description -->
    ///   @brief TODO
    ///
    /// <!-- template parameters -->
    ///   @tparam VM_CONCEPT the type of vm_t that this class manages.
    ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
    ///   @tparam MAX_VMS the max number of VMs supported
    ///
    template<typename VM_CONCEPT, typename PAGE_POOL_CONCEPT, bsl::uintmax MAX_VMS>
    class vm_pool_t final
    {
        /// @brief stores true if initialized() has been executed
        bool m_initialized;
        /// @brief stores a reference to the page pool to use
        PAGE_POOL_CONCEPT &m_page_pool;
        /// @brief stores the first VM_CONCEPT in the VM_CONCEPT linked list
        VM_CONCEPT *m_head;
        /// @brief stores the VM_CONCEPTs in the VM_CONCEPT linked list
        bsl::array<VM_CONCEPT, MAX_VMS> m_pool;
        /// @brief safe guards operations on the pool.
        mutable bsl::spinlock m_pool_lock;

    public:
        /// @brief an alias for VM_CONCEPT
        using vm_type = VM_CONCEPT;
        /// @brief an alias for PAGE_POOL_CONCEPT
        using page_pool_type = PAGE_POOL_CONCEPT;

        /// <!-- description -->
        ///   @brief Creates a vm_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param page_pool the page pool to use
        ///
        explicit constexpr vm_pool_t(PAGE_POOL_CONCEPT &page_pool) noexcept
            : m_initialized{}, m_page_pool{page_pool}, m_head{}, m_pool{}, m_pool_lock{}
        {}

        /// <!-- description -->
        ///   @brief Initializes this vm_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize() &noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::unlikely(m_initialized)) {
                bsl::error() << "vm_pool_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[this]() noexcept -> void {
                this->release();
            }};

            VM_CONCEPT *prev{};
            for (auto const vm : m_pool) {
                ret = vm.data->initialize(&m_page_pool, bsl::to_u16(vm.index));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                if (nullptr != prev) {
                    prev->set_next(vm.data);
                }
                else {
                    m_head = vm.data;
                }

                prev = vm.data;
            }

            release_on_error.ignore();
            m_initialized = true;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vm_t
        ///
        constexpr void
        release() &noexcept
        {
            for (auto const vm : m_pool) {
                vm.data->release();
            }

            m_head = {};
            m_initialized = {};
        }

        /// <!-- description -->
        ///   @brief Destroyes a previously created vm_pool_t
        ///
        constexpr ~vm_pool_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr vm_pool_t(vm_pool_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr vm_pool_t(vm_pool_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vm_pool_t const &o) &noexcept
            -> vm_pool_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vm_pool_t &&o) &noexcept -> vm_pool_t & = default;

        /// <!-- description -->
        ///   @brief Allocates a vm from the vm pool. We set the allocated
        ///     vm_t's next() to itself, which indicates that it has been
        ///     allocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns ID of the newly allocated vm
        ///
        [[nodiscard]] constexpr auto
        allocate() &noexcept -> bsl::safe_uint16
        {
            bsl::lock_guard lock{m_pool_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vm_pool_t not initialized\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            if (bsl::unlikely(nullptr == m_head)) {
                bsl::error() << "vm pool out of vms\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            if (bsl::unlikely(!m_head->allocate())) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            auto *const vm{m_head};
            m_head = m_head->next();

            vm->set_next(vm);
            return vm->id();
        }

        /// <!-- description -->
        ///   @brief Returns a vm previously allocated using the allocate
        ///     function to the vm pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the ID of the vm to deallocate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        deallocate(bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            bsl::lock_guard lock{m_pool_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vm_pool_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "invalid vmid: "    // --
                             << bsl::hex(vmid)      // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return bsl::errc_failure;
            }

            if (vm->next() != vm) {
                bsl::error() << "vm with id "             // --
                             << bsl::hex(vmid)            // --
                             << " was never allocated"    // --
                             << bsl::endl                 // --
                             << bsl::here();              // --

                return bsl::errc_failure;
            }

            vm->deallocate();
            vm->set_next(m_head);
            m_head = vm;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vm_t is allocated, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     allocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns true if the requested vm_t is allocated, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     allocated.
        ///
        [[nodiscard]] constexpr auto
        is_allocated(bsl::safe_uint16 const &vmid) &noexcept -> bool
        {
            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vm_pool_t not initialized\n" << bsl::here();
                return false;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "invalid vmid: "    // --
                             << bsl::hex(vmid)      // --
                             << bsl::endl           // --
                             << bsl::here();        // --

                return false;
            }

            return vm->is_allocated();
        }

        /// <!-- description -->
        ///   @brief Dumps the vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        dump(TLS_CONCEPT &tls) const &noexcept
        {
            bsl::print() << bsl::mag << "vm pool dump: ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Header
            ///

            bsl::print() << bsl::ylw << "+-----------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << "Id     ";
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << "Allocated ";
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << "Active ";
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+-----------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            /// VMs
            ///

            for (auto const vm : m_pool) {
                bsl::print() << bsl::ylw << "| ";
                bsl::print() << bsl::wht << bsl::hex(vm.data->id()) << " ";
                bsl::print() << bsl::ylw << "| ";
                if (vm.data->is_allocated()) {
                    bsl::print() << bsl::grn << bsl::fmt{">10s", "yes "};
                }
                else {
                    bsl::print() << bsl::red << bsl::fmt{">10s", "no "};
                }
                bsl::print() << bsl::ylw << "| ";
                if (tls.vmid() == vm.data->id()) {
                    bsl::print() << bsl::grn << bsl::fmt{">7s", "yes "};
                }
                else {
                    bsl::print() << bsl::red << bsl::fmt{">7s", "no "};
                }
                bsl::print() << bsl::ylw << "| ";
                bsl::print() << bsl::rst << bsl::endl;
            }

            /// Footer
            ///

            bsl::print() << bsl::ylw << "+-----------------------------+";
            bsl::print() << bsl::rst << bsl::endl;
        }

        /// <!-- description -->
        ///   @brief Dumps the requested VM
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the VM to dump
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        dump(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "invalid vmid: "    // --
                             << bsl::hex(vmid)      // --
                             << bsl::endl            // --
                             << bsl::here();         // --

                return;
            }

            vm->dump(tls);
        }
    };
}

#endif
