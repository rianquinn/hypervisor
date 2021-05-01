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

#ifndef VPS_POOL_T_HPP
#define VPS_POOL_T_HPP

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
    /// @class mk::vps_pool_t
    ///
    /// <!-- description -->
    ///   @brief Defines the microkernel's VPS pool
    ///
    /// <!-- template parameters -->
    ///   @tparam VPS_CONCEPT the type of vps_t that this class manages.
    ///   @tparam MAX_VPSS the max number of VPSs supported
    ///
    template<typename VPS_CONCEPT, bsl::uintmax MAX_VPSS>
    class vps_pool_t final
    {
        /// @brief stores true if initialized() has been executed
        bool m_initialized;
        /// @brief stores the first VPS_CONCEPT in the VPS_CONCEPT linked list
        VPS_CONCEPT *m_head;
        /// @brief stores the VPS_CONCEPTs in the VPS_CONCEPT linked list
        bsl::array<VPS_CONCEPT, MAX_VPSS> m_pool;
        /// @brief safe guards operations on the pool.
        mutable spinlock m_lock;

    public:
        /// @brief an alias for VPS_CONCEPT
        using vps_type = VPS_CONCEPT;

        /// <!-- description -->
        ///   @brief Creates a vps_pool_t
        ///
        explicit constexpr vps_pool_t() noexcept    // --
            : m_initialized{}, m_head{}, m_pool{}, m_lock{}
        {}

        /// <!-- description -->
        ///   @brief Destroyes a previously created vps_pool_t
        ///
        constexpr ~vps_pool_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr vps_pool_t(vps_pool_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr vps_pool_t(vps_pool_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vps_pool_t const &o) &noexcept
            -> vps_pool_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vps_pool_t &&o) &noexcept
            -> vps_pool_t & = default;

        /// <!-- description -->
        ///   @brief Initializes this vps_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
        ///   @param tls the current TLS block
        ///   @param page_pool the page pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename PAGE_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        initialize(TLS_CONCEPT &tls, PAGE_POOL_CONCEPT &page_pool) &noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::unlikely(m_initialized)) {
                bsl::error() << "vp_pool_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[this, &ret, &tls, &page_pool]() noexcept -> void {
                for (auto const vps : m_pool) {
                    ret = vps.data->release(tls, page_pool);
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

            VPS_CONCEPT *prev{};
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
        ///   @brief Release the vps_pool_t. Note that if this function fails,
        ///     the microkernel is left in a corrupt state and all use of the
        ///     vps_pool_t after calling this function will results in UB.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
        ///   @param tls the current TLS block
        ///   @param page_pool the page pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename PAGE_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        release(TLS_CONCEPT &tls, PAGE_POOL_CONCEPT &page_pool) &noexcept -> bsl::errc_type
        {
            for (auto const vps : m_pool) {
                if (bsl::unlikely(!vps.data->release(tls, page_pool))) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                vps.data->set_next(nullptr);
            }

            m_head = {};
            m_initialized = {};

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Allocates a vps from the vps pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
        ///   @param tls the current TLS block
        ///   @param page_pool the page pool to use
        ///   @param vpid The ID of the VP to assign the newly created VP to
        ///   @param ppid The ID of the PP to assign the newly created VP to
        ///   @return Returns ID of the newly allocated vps
        ///
        template<typename TLS_CONCEPT, typename PAGE_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        allocate(TLS_CONCEPT &tls,
            PAGE_POOL_CONCEPT &page_pool,
            bsl::safe_uint16 const &vpid,
            bsl::safe_uint16 const &ppid) &noexcept -> bsl::safe_uint16
        {
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vps_pool_t not initialized\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            if (bsl::unlikely(nullptr == m_head)) {
                bsl::error() << "vps pool out of vpss\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            if (bsl::unlikely(!m_head->allocate(tls, page_pool, vpid, ppid))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            auto *const vps{m_head};
            m_head = m_head->next();

            return vps->id();
        }

        /// <!-- description -->
        ///   @brief Returns a vps previously allocated using the allocate
        ///     function to the vps pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
        ///   @param tls the current TLS block
        ///   @param page_pool the page pool to use
        ///   @param vpsid the ID of the vps to deallocate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename PAGE_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        deallocate(TLS_CONCEPT &tls, PAGE_POOL_CONCEPT &page_pool, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            lock_guard lock{tls, m_lock};

            if (bsl::unlikely(!m_initialized)) {
                bsl::error() << "vps_pool_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(!vps->deallocate(tls, page_pool))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            vps->set_next(m_head);
            m_head = vps;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vps_t is allocated, false
        ///     if the provided VPSID is invalid, or if the vps_t is not
        ///     allocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpsid the ID of the vps_t to query
        ///   @return Returns true if the requested vps_t is allocated, false
        ///     if the provided VPSID is invalid, or if the vps_t is not
        ///     allocated.
        ///
        [[nodiscard]] constexpr auto
        is_allocated(bsl::safe_uint16 const &vpsid) &noexcept -> bool
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return false;
            }

            return vps->is_allocated();
        }

        /// <!-- description -->
        ///   @brief Sets the requested vps_t as active.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the vps_t to set as active
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        set_active(
            TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            return vps->set_active(tls, intrinsic);
        }

        /// <!-- description -->
        ///   @brief Sets the requested vps_t as inactive.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the vps_t to set as inactive
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        set_inactive(
            TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            return vps->set_inactive(tls, intrinsic);
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vps_t is active, false
        ///     if the provided VPID is invalid, or if the vps_t is not
        ///     active.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpsid the ID of the vps_t to query
        ///   @return Returns true if the requested vps_t is active, false
        ///     if the provided VPID is invalid, or if the vps_t is not
        ///     active.
        ///
        [[nodiscard]] constexpr auto
        is_active(bsl::safe_uint16 const &vpsid) &noexcept -> bool
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return false;
            }

            return vps->is_active();
        }

        /// <!-- description -->
        ///   @brief Returns true if this vps_t is active on the current PP,
        ///     false if the provided ID is invalid, or if the vps_t is not
        ///     active on the current PP.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vpsid the ID of the vps_t to query
        ///   @return Returns true if this vps_t is active on the current PP,
        ///     false if the provided ID is invalid, or if the vps_t is not
        ///     active on the current PP.
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_active_on_current_pp(TLS_CONCEPT &tls, bsl::safe_uint16 const &vpsid) &noexcept -> bool
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return false;
            }

            return vps->is_active_on_current_pp(tls);
        }

        /// <!-- description -->
        ///   @brief Migrates the requested vps_t from one PP to another.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vpsid the ID of the vps_t to migrate
        ///   @param ppid the ID of the PP to migrate to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        migrate(
            TLS_CONCEPT &tls, bsl::safe_uint16 const &vpsid, bsl::safe_uint16 const &ppid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            return vps->migrate(tls, ppid);
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the VP the requested vps_t is assigned to
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpsid the ID of the vps_t to query
        ///   @return Returns the ID of the VP the requested vps_t is assigned to
        ///
        [[nodiscard]] constexpr auto
        assigned_vp(bsl::safe_uint16 const &vpsid) const &noexcept -> bsl::safe_uint16
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::safe_uint16::zero(true);
            }

            return vps->assigned_vp();
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the PP the requested vps_t is assigned to
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpsid the ID of the vps_t to query
        ///   @return Returns the ID of the PP the requested vps_t is assigned to
        ///
        [[nodiscard]] constexpr auto
        assigned_pp(bsl::safe_uint16 const &vpsid) const &noexcept -> bsl::safe_uint16
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::safe_uint16::zero(true);
            }

            return vps->assigned_pp();
        }

        /// <!-- description -->
        ///   @brief Stores the provided state in the requested VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to set the state to
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        state_save_to_vps(
            TLS_CONCEPT &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            STATE_SAVE_CONCEPT const &state) &noexcept -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            return vps->state_save_to_vps(tls, intrinsic, state);
        }

        /// <!-- description -->
        ///   @brief Stores the requested VPS state in the provided state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to set the state to
        ///   @param state the state save to store the VPS state to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        vps_to_state_save(
            TLS_CONCEPT &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            STATE_SAVE_CONCEPT &state) &noexcept -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            return vps->vps_to_state_save(tls, intrinsic, state);
        }

        /// <!-- description -->
        ///   @brief Reads a field from the requested VPS given the index of
        ///     the field to read.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam FIELD_TYPE the type (i.e., size) of field to read
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to read from
        ///   @param index the index of the field to read from the VPS
        ///   @return Returns the value of the requested field from the
        ///     requested VPS or bsl::safe_integral<FIELD_TYPE>::zero(true)
        ///     on failure.
        ///
        template<typename FIELD_TYPE, typename TLS_CONCEPT, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        read(
            TLS_CONCEPT &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            bsl::safe_uintmax const &index) &noexcept -> bsl::safe_integral<FIELD_TYPE>
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::safe_integral<FIELD_TYPE>::zero(true);
            }

            return vps->template read<FIELD_TYPE>(tls, intrinsic, index);
        }

        /// <!-- description -->
        ///   @brief Writes a field to the requested VPS given the index of
        ///     the field and the value to write.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam FIELD_TYPE the type (i.e., size) of field to write
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to write to
        ///   @param index the index of the field to write to the VPS
        ///   @param value the value to write to the VPS
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename FIELD_TYPE, typename TLS_CONCEPT, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        write(
            TLS_CONCEPT &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            bsl::safe_uintmax const &index,
            bsl::safe_integral<FIELD_TYPE> const &value) &noexcept -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            return vps->template write<FIELD_TYPE>(tls, intrinsic, index, value);
        }

        /// <!-- description -->
        ///   @brief Reads a field from the requested VPS given a bf_reg_t
        ///     defining the field to read.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to read from
        ///   @param reg a bf_reg_t defining the field to read from the VPS
        ///   @return Returns the value of the requested field from the
        ///     requested VPS or bsl::safe_uintmax::zero(true) on failure.
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        read_reg(
            TLS_CONCEPT &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            syscall::bf_reg_t const reg) &noexcept -> bsl::safe_uintmax
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::safe_uintmax::zero(true);
            }

            return vps->read_reg(tls, intrinsic, reg);
        }

        /// <!-- description -->
        ///   @brief Writes a field to the requested VPS given a bf_reg_t
        ///     defining the field and a value to write.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to write to
        ///   @param reg a bf_reg_t defining the field to write to the VPS
        ///   @param value the value to write to the VPS
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        write_reg(
            TLS_CONCEPT &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            syscall::bf_reg_t const reg,
            bsl::safe_uintmax const &value) &noexcept -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            return vps->write_reg(tls, intrinsic, reg, value);
        }

        /// <!-- description -->
        ///   @brief Runs the requested VPS. Note that this function does not
        ///     return until a VMExit occurs. Once complete, this function
        ///     will return the VMExit reason.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @tparam VMEXIT_LOG_CONCEPT defines the type of VMExit log to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param log the VMExit log to use
        ///   @param vpsid the ID of the VPS to run
        ///   @return Returns the VMExit reason on success, or
        ///     bsl::safe_uintmax::zero(true) on failure.
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT, typename VMEXIT_LOG_CONCEPT>
        [[nodiscard]] constexpr auto
        run(TLS_CONCEPT &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            VMEXIT_LOG_CONCEPT &log) &noexcept -> bsl::safe_uintmax
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::safe_uintmax::zero(true);
            }

            return vps->run(tls, intrinsic, log);
        }

        /// <!-- description -->
        ///   @brief Advance the IP of the requested VPS
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to advance the IP for
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        advance_ip(
            TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            return vps->advance_ip(tls, intrinsic);
        }

        /// <!-- description -->
        ///   @brief Clears the requested VPS's internal cache. Note that this
        ///     is a hardware specific function and doesn't change the actual
        ///     values stored in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to clear
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        clear(
            TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            return vps->clear(tls, intrinsic);
        }

        /// <!-- description -->
        ///   @brief Dumps the requested VPS
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to dump
        ///
        template<typename TLS_CONCEPT, typename INTRINSIC_CONCEPT>
        constexpr void
        dump(
            TLS_CONCEPT &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
        {
            if constexpr (BSL_DEBUG_LEVEL == bsl::CRITICAL_ONLY) {
                return;
            }

            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                            // --
                             << bsl::hex(vpsid)                     // --
                             << " is greater than the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))     // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return;
            }

            vps->dump(tls, intrinsic);
        }
    };
}

#endif
