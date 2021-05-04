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

#ifndef VP_POOL_T_HPP
#define VP_POOL_T_HPP

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
    /// @class mk::vp_pool_t
    ///
    /// <!-- description -->
    ///   @brief Defines the microkernel's VP pool
    ///
    /// <!-- template parameters -->
    ///   @tparam VP_CONCEPT the type of vp_t that this class manages.
    ///   @tparam MAX_VPS the max number of VPs supported
    ///
    template<typename VP_CONCEPT, bsl::uintmax MAX_VPS>
    class vp_pool_t final
    {
        /// @brief stores true if initialized() has been executed
        bool m_initialized;
        /// @brief stores the first VP_CONCEPT in the VP_CONCEPT linked list
        VP_CONCEPT *m_head;
        /// @brief stores the VP_CONCEPTs in the VP_CONCEPT linked list
        bsl::array<VP_CONCEPT, MAX_VPS> m_pool;
        /// @brief safe guards operations on the pool.
        mutable spinlock m_lock;

    public:
        /// @brief an alias for VP_CONCEPT
        using vp_type = VP_CONCEPT;

        /// <!-- description -->
        ///   @brief Creates a vp_pool_t
        ///
        explicit constexpr vp_pool_t() noexcept    // --
            : m_initialized{}, m_head{}, m_pool{}, m_lock{}
        {}

        /// <!-- description -->
        ///   @brief Destroyes a previously created vp_pool_t
        ///
        constexpr ~vp_pool_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr vp_pool_t(vp_pool_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr vp_pool_t(vp_pool_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vp_pool_t const &o) &noexcept
            -> vp_pool_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vp_pool_t &&o) &noexcept -> vp_pool_t & = default;

        /// <!-- description -->
        ///   @brief Initializes this vp_pool_t
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
                bsl::error() << "vp_pool_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[this, &ret]() noexcept -> void {
                for (auto const vp : m_pool) {
                    ret = vp.data->release();
                    if (bsl::unlikely(!ret)) {
                        bsl::print<bsl::V>() << bsl::here();
                    }
                    else {
                        bsl::touch();
                    }
                }
            }};

            for (auto const vp : m_pool) {
                ret = vp.data->initialize(bsl::to_u16(vp.index));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            VP_CONCEPT *prev{};
            for (auto const vp : m_pool) {
                if (nullptr != prev) {
                    prev->set_next(vp.data);
                }

                prev = vp.data;
            }

            m_head = m_pool.front_if();
            m_initialized = true;

            release_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vp_pool_t. Note that if this function fails,
        ///     the microkernel is left in a corrupt state and all use of the
        ///     vp_pool_t after calling this function will results in UB.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        release() &noexcept -> bsl::errc_type
        {
            for (auto const vp : m_pool) {
                if (bsl::unlikely(!vp.data->release())) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                vp.data->set_next(nullptr);
            }

            m_head = {};
            m_initialized = {};

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Allocates a vp from the vp pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid The ID of the VM to assign the newly created VP to
        ///   @param ppid The ID of the PP to assign the newly created VP to
        ///   @return Returns ID of the newly allocated vp
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        allocate(
            TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid, bsl::safe_uint16 const &ppid) &noexcept
            -> bsl::safe_uint16
        {
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vp_pool_t not initialized\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            if (bsl::unlikely(nullptr == m_head)) {
                bsl::error() << "vp pool out of vps\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            if (bsl::unlikely(!m_head->allocate(tls, vmid, ppid))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            auto *const vp{m_head};
            m_head = m_head->next();

            return vp->id();
        }

        /// <!-- description -->
        ///   @brief Returns a vp previously allocated using the allocate
        ///     function to the vp pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vpid the ID of the vp to deallocate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        deallocate(TLS_CONCEPT &tls, bsl::safe_uint16 const &vpid) &noexcept -> bsl::errc_type
        {
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vp_pool_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(!vp->deallocate(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            vp->set_next(m_head);
            m_head = vp;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief If a vp_t is assigned to the requested VMID, the ID of
        ///     the vp_t is returned. Otherwise, this function will return
        ///     bsl::safe_uint16::zero(true)
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid the ID fo the VM to query
        ///   @return If a vp_t is assigned to the requested VMID, the ID of
        ///     the vp_t is returned. Otherwise, this function will return
        ///     bsl::safe_uint16::zero(true)
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_vm_assigned(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) const &noexcept
            -> bsl::safe_uint16
        {
            lock_guard lock{tls, m_lock};

            for (auto const elem : m_pool) {
                if (elem.data->assigned_vm() == vmid) {
                    return elem.data->id();
                }

                bsl::touch();
            }

            return bsl::safe_uint16::zero(true);
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vp_t is allocated, false
        ///     if the provided VPID is invalid, or if the vp_t is not
        ///     allocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpid the ID of the vp_t to query
        ///   @return Returns true if the requested vp_t is allocated, false
        ///     if the provided VPID is invalid, or if the vp_t is not
        ///     allocated.
        ///
        [[nodiscard]] constexpr auto
        is_allocated(bsl::safe_uint16 const &vpid) const &noexcept -> bool
        {
            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return false;
            }

            return vp->is_allocated();
        }

        /// <!-- description -->
        ///   @brief Sets the requested vp_t as active.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vpid the ID of the vp_t to set as active
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_active(TLS_CONCEPT &tls, bsl::safe_uint16 const &vpid) &noexcept -> bsl::errc_type
        {
            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            return vp->set_active(tls);
        }

        /// <!-- description -->
        ///   @brief Sets the requested vp_t as inactive.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vpid the ID of the vp_t to set as inactive
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_inactive(TLS_CONCEPT &tls, bsl::safe_uint16 const &vpid) &noexcept -> bsl::errc_type
        {
            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            return vp->set_inactive(tls);
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vp_t is active, false
        ///     if the provided VPID is invalid, or if the vp_t is not
        ///     active.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpid the ID of the vp_t to query
        ///   @return Returns true if the requested vp_t is active, false
        ///     if the provided VPID is invalid, or if the vp_t is not
        ///     active.
        ///
        [[nodiscard]] constexpr auto
        is_active(bsl::safe_uint16 const &vpid) const &noexcept -> bool
        {
            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return false;
            }

            return vp->is_active();
        }

        /// <!-- description -->
        ///   @brief Returns true if this vp_t is active on the current PP,
        ///     false if the provided ID is invalid, or if the vp_t is not
        ///     active on the current PP.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vpid the ID of the vp_t to query
        ///   @return Returns true if this vp_t is active on the current PP,
        ///     false if the provided ID is invalid, or if the vp_t is not
        ///     active on the current PP.
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_active_on_current_pp(TLS_CONCEPT &tls, bsl::safe_uint16 const &vpid) const &noexcept
            -> bool
        {
            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return false;
            }

            return vp->is_active_on_current_pp(tls);
        }

        /// <!-- description -->
        ///   @brief Migrates the requested vp_t from one PP to another.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vpid the ID of the vp_t to migrate
        ///   @param ppid the ID of the PP to migrate to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        migrate(
            TLS_CONCEPT &tls, bsl::safe_uint16 const &vpid, bsl::safe_uint16 const &ppid) &noexcept
            -> bsl::errc_type
        {
            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            return vp->migrate(tls, ppid);
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the VM the requested vp_t is assigned to
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpid the ID of the vp_t to query
        ///   @return Returns the ID of the VM the requested vp_t is assigned to
        ///
        [[nodiscard]] constexpr auto
        assigned_vm(bsl::safe_uint16 const &vpid) const &noexcept -> bsl::safe_uint16
        {
            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::safe_uint16::zero(true);
            }

            return vp->assigned_vm();
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the PP the requested vp_t is assigned to
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpid the ID of the vp_t to query
        ///   @return Returns the ID of the PP the requested vp_t is assigned to
        ///
        [[nodiscard]] constexpr auto
        assigned_pp(bsl::safe_uint16 const &vpid) const &noexcept -> bsl::safe_uint16
        {
            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::safe_uint16::zero(true);
            }

            return vp->assigned_pp();
        }

        /// <!-- description -->
        ///   @brief Dumps the requested VP
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vpid the ID of the VP to dump
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        dump(TLS_CONCEPT &tls, bsl::safe_uint16 const &vpid) &noexcept
        {
            if constexpr (BSL_DEBUG_LEVEL == bsl::CRITICAL_ONLY) {
                return;
            }

            auto *const vp{m_pool.at_if(bsl::to_umax(vpid))};
            if (bsl::unlikely(nullptr == vp)) {
                bsl::error() << "vpid "                            // --
                             << bsl::hex(vpid)                     // --
                             << " is greater than the MAX_VPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPS))     // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return;
            }

            vp->dump(tls);
        }
    };
}

#endif
