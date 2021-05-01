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

#include <lock_guard.hpp>
#include <mk_interface.hpp>
#include <spinlock.hpp>

#include <bsl/array.hpp>
#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
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
        mutable spinlock m_lock;

    public:
        /// @brief an alias for VM_CONCEPT
        using vm_type = VM_CONCEPT;

        /// <!-- description -->
        ///   @brief Creates a vm_pool_t
        ///
        explicit constexpr vm_pool_t() noexcept    // --
            : m_initialized{}, m_head{}, m_pool{}, m_lock{}
        {}

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

            bsl::finally release_on_error{[this, &ret]() noexcept -> void {
                for (auto const vm : m_pool) {
                    ret = vm.data->release();
                    if (bsl::unlikely(!ret)) {
                        bsl::print<bsl::V>() << bsl::here();
                    }
                    else {
                        bsl::touch();
                    }
                }
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

                vm.data->set_next(nullptr);
            }

            m_head = {};
            m_initialized = {};

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Allocates a vm from the vm pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns ID of the newly allocated vm
        ///
        /// <!-- exception safety -->
        ///   @note IMPORTANT: This call assumes exceptions ARE POSSIBLE and
        ///     that state reversal MIGHT BE REQUIRED.
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        allocate(TLS_CONCEPT &tls) &noexcept -> bsl::safe_uint16
        {
            lock_guard lock{tls, m_lock};
            auto *const vm{m_head};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vm_pool_t not initialized\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            if (bsl::unlikely(tls.log_vmid != syscall::BF_INVALID_ID)) {
                bsl::error() << "log_vmid contains an unexpected value of "                      // --
                             << bsl::hex(tls.log_vmid)             // --
                             << bsl::endl                  // --
                             << bsl::here();               // --

                return bsl::safe_uint16::zero(true);
            }

            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vm pool out of vms\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            tls.log_vmid = vm->id().get();

            if (bsl::unlikely(!vm->allocate())) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            m_head = vm->next();

bsl::debug() << "successfully allocated vm " << tls.log_vmid << bsl::endl;
            return tls.log_vmid;
        }

        /// <!-- description -->
        ///   @brief Returns a vm previously allocated using the allocate
        ///     function to the vm pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm to deallocate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        deallocate(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vm_pool_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (syscall::BF_INVALID_ID == vmid) {
                return bsl::errc_success;
            }

            if (bsl::unlikely(vmid == syscall::BF_ROOT_VMID)) {
                bsl::error() << "vm "                           // --
                             << bsl::hex(vmid)                  // --
                             << " is the root VM which cannot be destroyed"       // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid or greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(!vm->is_allocated())) {
                return bsl::errc_success;
            }

            // The VM
            // - must be allocated
            // - must not be active
            // - must not have any VPs assigned to it.

            // Get rid of the linked lists. If we have to search through
            // lists during creating, O(N) is not the end of the world,
            // and it is a lot safer, and will consume less memory. Even
            // if we have to search through the max number of objects support
            // for 

            bsl::finally zombify_on_error{[&vm]() noexcept -> void {
                vm->zombify();
            }};

            if (bsl::unlikely(!vm->deallocate(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_head == vm)) {
                return bsl::errc_success;
            }

            vm->set_next(m_head);
            m_head = vm;

            zombify_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Sets the requested vm_t's status as zombified, meaning
        ///     it is no longer usable.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the ID of the vm_t to set as a zombie
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        zombify(bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            if (syscall::BF_INVALID_ID == vmid) {
                return bsl::errc_success;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid or greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            vm->zombify();
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
            if (syscall::BF_INVALID_ID == vmid) {
                return false;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid or greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return false;
            }

            return vm->is_allocated();
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vm_t is a zombie, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     a zombie.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns true if the requested vm_t is a zombie, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     a zombie.
        ///
        [[nodiscard]] constexpr auto
        is_zombie(bsl::safe_uint16 const &vmid) &noexcept -> bool
        {
            if (syscall::BF_INVALID_ID == vmid) {
                return false;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid or greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return false;
            }

            return vm->is_zombie();
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
        set_active(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            if (syscall::BF_INVALID_ID == vmid) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid"    // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid or greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

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
        set_inactive(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            if (syscall::BF_INVALID_ID == vmid) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid"    // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid or greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

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
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns true if the requested vm_t is active, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     active.
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_active(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept -> bool
        {
            if (syscall::BF_INVALID_ID == vmid) {
                return false;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid or greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return false;
            }

            return vm->is_active(tls);
        }

        /// <!-- description -->
        ///   @brief Returns true if this vm_t is active on the current PP,
        ///     false if the provided ID is invalid, or if the vm_t is not
        ///     active on the current PP.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns true if this vm_t is active on the current PP,
        ///     false if the provided ID is invalid, or if the vm_t is not
        ///     active on the current PP.
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_active_on_current_pp(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept -> bool
        {
            if (syscall::BF_INVALID_ID == vmid) {
                return false;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid or greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return false;
            }

            return vm->is_active_on_current_pp(tls);
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

            if (syscall::BF_INVALID_ID == vmid) {
                return;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                            // --
                             << bsl::hex(vmid)                     // --
                             << " is invalid or greater than the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return;
            }

            vm->dump(tls);
        }
    };
}

#endif
