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
    inline bool yourmom{};

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
        bool m_initialized{};
        /// @brief stores the VM_CONCEPTs in the VM_CONCEPT linked list
        bsl::array<VM_CONCEPT, MAX_VMS> m_pool{};
        /// @brief safe guards operations on the pool.
        mutable spinlock m_lock{};

    public:
        /// @brief an alias for VM_CONCEPT
        using vm_type = VM_CONCEPT;

        /// <!-- description -->
        ///   @brief Initializes this vm_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize() &noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::unlikely(m_initialized)) {
                bsl::error() << "vm_pool_t already initialized\n" << bsl::here();
                return bsl::errc_precondition;
            }

            bsl::finally release_on_error{[this, &ret]() noexcept -> void {
                this->release();
            }};

            for (auto const vm : m_pool) {
                ret = vm.data->initialize(bsl::to_u16(vm.index));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            m_initialized = true;

            release_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vm_pool_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        release() &noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            for (auto const vm : m_pool) {
                ret = vm.data->release();
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            m_initialized = {};
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Allocates a vm from the vm pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
        ///   @param tls the current TLS block
        ///   @param ext_pool the extension pool to use
        ///   @return Returns ID of the newly allocated vm
        ///
        template<typename TLS_CONCEPT, typename EXT_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        allocate(TLS_CONCEPT &tls, EXT_POOL_CONCEPT &ext_pool) &noexcept -> bsl::safe_uint16
        {
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vm_pool_t not initialized\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            VM_CONCEPT *vm{};
            for (auto const elem : m_pool) {
                if (elem.data->is_deallocated()) {
                    vm = elem.data;
                    break;
                }

                bsl::touch();
            }

            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vm pool out of vms\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            return vm->allocate(tls, ext_pool);
        }

        /// <!-- description -->
        ///   @brief Returns a vm previously allocated using the allocate
        ///     function to the vm pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam EXT_POOL_CONCEPT defines the type of ext_pool_t to use
        ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
        ///   @param tls the current TLS block
        ///   @param ext_pool the extension pool to use
        ///   @param vp_pool the VP pool to use
        ///   @param vmid the ID of the vm to deallocate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT, typename EXT_POOL_CONCEPT, typename VP_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        deallocate(
            TLS_CONCEPT &tls,
            EXT_POOL_CONCEPT &ext_pool,
            VP_POOL_CONCEPT const &vp_pool,
            bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vm_pool_t not initialized\n" << bsl::here();
                return bsl::errc_precondition;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                       // --
                             << bsl::hex(vmid)                                // --
                             << " is invalid or greater than or equal to the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

                return bsl::errc_index_out_of_bounds;
            }

            ret = vm->deallocate(tls, ext_pool, vp_pool);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

// if (vm->id().is_pos()) {
//     if (!yourmom) {
//         yourmom = true;
//         int *i{};
//         *i = 42;
//     }
// }
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Sets the requested vm_t's status as zombified, meaning
        ///     it is no longer usable.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the ID of the vm_t to set as a zombie
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        zombify(bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                       // --
                             << bsl::hex(vmid)                                // --
                             << " is invalid or greater than or equal to the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

                return bsl::errc_index_out_of_bounds;
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
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                       // --
                             << bsl::hex(vmid)                                // --
                             << " is invalid or greater than or equal to the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

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
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                       // --
                             << bsl::hex(vmid)                                // --
                             << " is invalid or greater than or equal to the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

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
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_active(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                       // --
                             << bsl::hex(vmid)                                // --
                             << " is invalid or greater than or equal to the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

                return bsl::errc_index_out_of_bounds;
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
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_inactive(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                       // --
                             << bsl::hex(vmid)                                // --
                             << " is invalid or greater than or equal to the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

                return bsl::errc_index_out_of_bounds;
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
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                       // --
                             << bsl::hex(vmid)                                // --
                             << " is invalid or greater than or equal to the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

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
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                       // --
                             << bsl::hex(vmid)                                // --
                             << " is invalid or greater than or equal to the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

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

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                       // --
                             << bsl::hex(vmid)                                // --
                             << " is invalid or greater than or equal to the MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VMS))                // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

                return;
            }

            vm->dump(tls);
        }
    };
}

#endif
