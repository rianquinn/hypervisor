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

#include <mk_interface.hpp>

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
    ///   @brief Defines the microkernel's VM pool
    ///
    /// <!-- template parameters -->
    ///   @tparam VM_CONCEPT the type of vm_t that this class manages.
    ///   @tparam MAX_VMS the max number of VMs supported
    ///
    template<typename VM_CONCEPT, bsl::uintmax MAX_VMS>
    class vm_pool_t final
    {
        /// @brief stores true if initialized() has been executed
        bool m_initialized;
        /// @brief stores the first VM_CONCEPT in the VM_CONCEPT linked list
        VM_CONCEPT *m_head;
        /// @brief stores the VM_CONCEPTs in the VM_CONCEPT linked list
        bsl::array<VM_CONCEPT, MAX_VMS> m_pool;
        /// @brief safe guards operations on the pool.
        mutable bsl::spinlock m_pool_lock;

    public:
        /// @brief an alias for VM_CONCEPT
        using vm_type = VM_CONCEPT;

        /// <!-- description -->
        ///   @brief Creates a vm_pool_t
        ///
        explicit constexpr vm_pool_t() noexcept    // --
            : m_initialized{}, m_head{}, m_pool{}, m_pool_lock{}
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
                if (bsl::unlikely(!this->release())) {
                    bsl::print<bsl::V>() << bsl::here();
                    return;
                }

                bsl::touch();
            }};

            for (auto const vm : m_pool) {
                ret = vm.data->initialize(bsl::to_u16(vm.index));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            VM_CONCEPT *prev{};
            for (auto const vm : m_pool) {
                if (nullptr != prev) {
                    prev->set_next(vm.data);
                }

                prev = vm.data;
            }

            m_head = m_pool.front_if();
            m_initialized = true;

            release_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vm_pool_t. Note that if this function fails,
        ///     the microkernel is left in a corrupt state and all use of the
        ///     vm_pool_t after calling this function will results in UB.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        release() &noexcept -> bsl::errc_type
        {
            for (auto const vm : m_pool) {
                if (bsl::unlikely(!vm.data->release())) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            m_head = {};
            m_initialized = {};

            return bsl::errc_success;
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
                bsl::error() << "vmid "                           // --
                             << bsl::hex(vmid)                  // --
                             << " is greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(!vm->deallocate())) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

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
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                           // --
                             << bsl::hex(vmid)                  // --
                             << " is greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return false;
            }

            return vm->is_allocated();
        }

        /// <!-- description -->
        ///   @brief Sets the requested vm_t as active.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to set as active
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_active(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept  -> bsl::errc_type
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                           // --
                             << bsl::hex(vmid)                  // --
                             << " is greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            return vm->set_active(tls);
        }

        /// <!-- description -->
        ///   @brief Sets the requested vm_t as inactive.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to set as inactive
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_inactive(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept  -> bsl::errc_type
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                           // --
                             << bsl::hex(vmid)                  // --
                             << " is greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            return vm->set_inactive(tls);
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vm_t is active, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     active.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns true if the requested vm_t is active, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     active.
        ///
        [[nodiscard]] constexpr auto
        is_active(bsl::safe_uint16 const &vmid) &noexcept -> bool
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                           // --
                             << bsl::hex(vmid)                  // --
                             << " is greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return false;
            }

            return vm->is_active();
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
            if constexpr (BSL_DEBUG_LEVEL == bsl::CRITICAL_ONLY) {
                return;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                           // --
                             << bsl::hex(vmid)                  // --
                             << " is greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return;
            }

            vm->dump(tls);
        }
    };
}

#endif
