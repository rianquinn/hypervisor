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

#include "lock_guard_t.hpp"
#include "spinlock_t.hpp"

#include <bf_constants.hpp>
#include <tls_t.hpp>
#include <vm_t.hpp>
#include <ext_pool_t.hpp>
#include <vp_pool_t.hpp>

#include <bsl/array.hpp>
#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally_assert.hpp>
#include <bsl/unlikely.hpp>
#include <bsl/unlikely_assert.hpp>

namespace mk
{
    /// @class mk::vm_pool_t
    ///
    /// <!-- description -->
    ///   @brief Defines the microkernel's VM pool
    ///
    class vm_pool_t final
    {
        /// @brief stores the pool of vm_ts
        bsl::array<vm_t, HYPERVISOR_MAX_VMS> m_pool{};
        /// @brief safe guards operations on the pool.
        mutable spinlock_t m_lock{};

    public:
        /// @brief an alias for vm_t
        using vm_type = vm_t;

        /// <!-- description -->
        ///   @brief Initializes this vm_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param ext_pool the extension pool to use
        ///   @param vp_pool the VP pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(tls_t &tls, ext_pool_t &ext_pool, vp_pool_t &vp_pool) &noexcept
            -> bsl::errc_type
        {
            bsl::finally_assert release_on_error{
                [this, &tls, &ext_pool, &vp_pool]() noexcept -> void {
                    auto const ret{this->release(tls, ext_pool, vp_pool)};
                    if (bsl::unlikely(!ret)) {
                        bsl::print<bsl::V>() << bsl::here();
                        return;
                    }

                    bsl::touch();
                }};

            for (auto const vm : m_pool) {
                auto const ret{vm.data->initialize(tls, bsl::to_u16(vm.index))};
                if (bsl::unlikely_assert(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            release_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vm_pool_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param ext_pool the extension pool to use
        ///   @param vp_pool the VP pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        release(tls_t &tls, ext_pool_t &ext_pool, vp_pool_t &vp_pool) &noexcept
            -> bsl::errc_type
        {
            for (auto const vm : m_pool) {
                auto const ret{vm.data->release(tls, ext_pool, vp_pool)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Allocates a vm from the vm pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param ext_pool the extension pool to use
        ///   @return Returns ID of the newly allocated vm
        ///
        [[nodiscard]] constexpr auto
        allocate(tls_t &tls, ext_pool_t &ext_pool) &noexcept -> bsl::safe_uint16
        {
            lock_guard_t lock{tls, m_lock};

            vm_t *vm{};
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
        ///   @param tls the current TLS block
        ///   @param ext_pool the extension pool to use
        ///   @param vp_pool the VP pool to use
        ///   @param vmid the ID of the vm to deallocate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        deallocate(
            tls_t &tls,
            ext_pool_t &ext_pool,
            vp_pool_t const &vp_pool,
            bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

                return bsl::errc_index_out_of_bounds;
            }

            return vm->deallocate(tls, ext_pool, vp_pool);
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
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

                return bsl::errc_index_out_of_bounds;
            }

            vm->zombify();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vm_t is deallocated, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     deallocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns true if the requested vm_t is deallocated, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     deallocated.
        ///
        [[nodiscard]] constexpr auto
        is_deallocated(tls_t &tls, bsl::safe_uint16 const &vmid) const &noexcept -> bool
        {
            bsl::discard(tls);

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

                return false;
            }

            return vm->is_deallocated();
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vm_t is allocated, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     allocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns true if the requested vm_t is allocated, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     allocated.
        ///
        [[nodiscard]] constexpr auto
        is_allocated(tls_t &tls, bsl::safe_uint16 const &vmid) const &noexcept -> bool
        {
            bsl::discard(tls);

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

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
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns true if the requested vm_t is a zombie, false
        ///     if the provided VMID is invalid, or if the vm_t is not
        ///     a zombie.
        ///
        [[nodiscard]] constexpr auto
        is_zombie(tls_t &tls, bsl::safe_uint16 const &vmid) const &noexcept -> bool
        {
            bsl::discard(tls);

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

                return false;
            }

            return vm->is_zombie();
        }

        /// <!-- description -->
        ///   @brief Sets the requested vm_t as active.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to set as active
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        set_active(tls_t &tls, bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

                return bsl::errc_index_out_of_bounds;
            }

            return vm->set_active(tls);
        }

        /// <!-- description -->
        ///   @brief Sets the requested vm_t as inactive.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to set as inactive
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        set_inactive(tls_t &tls, bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

                return bsl::errc_index_out_of_bounds;
            }

            return vm->set_inactive(tls);
        }

        /// <!-- description -->
        ///   @brief  Returns the ID of the first PP identified that the
        ///     requested vm_t is still active on. If the vm_t is inactive, this
        ///     function returns bsl::safe_uint16::zero(true)
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns the ID of the first PP identified that the
        ///     requested vm_t is still active on. If the vm_t is inactive, this
        ///     function returns bsl::safe_uint16::zero(true)
        ///
        [[nodiscard]] constexpr auto
        is_active(tls_t &tls, bsl::safe_uint16 const &vmid) const &noexcept -> bsl::safe_uint16
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

                return bsl::safe_uint16::zero(true);
            }

            return vm->is_active(tls);
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vm_t is active on the
        ///     current PP, false if the provided ID is invalid, or if the
        ///     vm_t is not active on the current PP.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the vm_t to query
        ///   @return Returns true if the requested vm_t is active on the
        ///     current PP, false if the provided ID is invalid, or if the
        ///     vm_t is not active on the current PP.
        ///
        [[nodiscard]] constexpr auto
        is_active_on_current_pp(tls_t &tls, bsl::safe_uint16 const &vmid) const &noexcept -> bool
        {
            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

                return false;
            }

            return vm->is_active_on_current_pp(tls);
        }

        /// <!-- description -->
        ///   @brief Dumps the requested VM
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vmid the ID of the VM to dump
        ///
        constexpr void
        dump(tls_t &tls, bsl::safe_uint16 const &vmid) const &noexcept
        {
            if constexpr (BSL_DEBUG_LEVEL == bsl::CRITICAL_ONLY) {
                return;
            }

            auto *const vm{m_pool.at_if(bsl::to_umax(vmid))};
            if (bsl::unlikely(nullptr == vm)) {
                bsl::error() << "vmid "                                                   // --
                             << bsl::hex(vmid)                                            // --
                             << " is invalid or greater than or equal to the HYPERVISOR_MAX_VMS "    // --
                             << bsl::hex(bsl::to_u16(HYPERVISOR_MAX_VMS))                            // --
                             << bsl::endl                                                 // --
                             << bsl::here();                                              // --

                return;
            }

            vm->dump(tls);
        }
    };
}

#endif
