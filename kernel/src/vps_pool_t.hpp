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

#include "lock_guard_t.hpp"
#include "spinlock_t.hpp"

#include <mk_interface.hpp>
#include <tls_t.hpp>

#include <bsl/array.hpp>
#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally_assert.hpp>
#include <bsl/unlikely.hpp>
#include <bsl/unlikely_assert.hpp>

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
        /// @brief stores the VPS_CONCEPTs in the VPS_CONCEPT linked list
        bsl::array<VPS_CONCEPT, MAX_VPSS> m_pool{};
        /// @brief safe guards operations on the pool.
        mutable spinlock_t m_lock{};

    public:
        /// @brief an alias for VPS_CONCEPT
        using vps_type = VPS_CONCEPT;

        /// <!-- description -->
        ///   @brief Initializes this vps_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
        ///   @param tls the current TLS block
        ///   @param page_pool the page pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename PAGE_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        initialize(tls_t &tls, PAGE_POOL_CONCEPT &page_pool) &noexcept -> bsl::errc_type
        {
            bsl::finally_assert release_on_error{[this, &tls, &page_pool]() noexcept -> void {
                auto const ret{this->release(tls, page_pool)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return;
                }

                bsl::touch();
            }};

            for (auto const vps : m_pool) {
                auto const ret{vps.data->initialize(bsl::to_u16(vps.index))};
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
        ///   @brief Release the vps_pool_t. Note that if this function fails,
        ///     the microkernel is left in a corrupt state and all use of the
        ///     vps_pool_t after calling this function will results in UB.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
        ///   @param tls the current TLS block
        ///   @param page_pool the page pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename PAGE_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        release(tls_t &tls, PAGE_POOL_CONCEPT &page_pool) &noexcept -> bsl::errc_type
        {
            for (auto const vps : m_pool) {
                auto const ret{vps.data->release(tls, page_pool)};
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Allocates a vps from the vps pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
        ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param page_pool the page pool to use
        ///   @param vp_pool the VP pool to use
        ///   @param vpid The ID of the VP to assign the newly created VP to
        ///   @param ppid The ID of the PP to assign the newly created VP to
        ///   @return Returns ID of the newly allocated vps
        ///
        template<typename INTRINSIC_CONCEPT, typename PAGE_POOL_CONCEPT, typename VP_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        allocate(
            tls_t &tls,
            INTRINSIC_CONCEPT &intrinsic,
            PAGE_POOL_CONCEPT &page_pool,
            VP_POOL_CONCEPT &vp_pool,
            bsl::safe_uint16 const &vpid,
            bsl::safe_uint16 const &ppid) &noexcept -> bsl::safe_uint16
        {
            lock_guard_t lock{tls, m_lock};

            VPS_CONCEPT *vps{};
            for (auto const elem : m_pool) {
                if (elem.data->is_deallocated()) {
                    vps = elem.data;
                    break;
                }

                bsl::touch();
            }

            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vps pool out of vpss\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            return vps->allocate(tls, intrinsic, page_pool, vp_pool, vpid, ppid);
        }

        /// <!-- description -->
        ///   @brief Returns a vps previously allocated using the allocate
        ///     function to the vps pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
        ///   @param tls the current TLS block
        ///   @param page_pool the page pool to use
        ///   @param vpsid the ID of the vps to deallocate
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename PAGE_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        deallocate(
            tls_t &tls, PAGE_POOL_CONCEPT &page_pool, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::errc_index_out_of_bounds;
            }

            return vps->deallocate(tls, page_pool);
        }

        /// <!-- description -->
        ///   @brief Sets the requested vps_t's status as zombified, meaning
        ///     it is no longer usable.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpsid the ID of the vps_t to set as a zombie
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        zombify(bsl::safe_uint16 const &vpsid) &noexcept -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::errc_index_out_of_bounds;
            }

            vps->zombify();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vps_t is deallocated, false
        ///     if the provided VPID is invalid, or if the vps_t is not
        ///     deallocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vpsid the ID of the vps_t to query
        ///   @return Returns true if the requested vps_t is deallocated, false
        ///     if the provided VPID is invalid, or if the vps_t is not
        ///     deallocated.
        ///
        [[nodiscard]] constexpr auto
        is_deallocated(tls_t &tls, bsl::safe_uint16 const &vpsid) const &noexcept -> bool
        {
            bsl::discard(tls);

            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return false;
            }

            return vps->is_deallocated();
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vps_t is allocated, false
        ///     if the provided VPID is invalid, or if the vps_t is not
        ///     allocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vpsid the ID of the vps_t to query
        ///   @return Returns true if the requested vps_t is allocated, false
        ///     if the provided VPID is invalid, or if the vps_t is not
        ///     allocated.
        ///
        [[nodiscard]] constexpr auto
        is_allocated(tls_t &tls, bsl::safe_uint16 const &vpsid) const &noexcept -> bool
        {
            bsl::discard(tls);

            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return false;
            }

            return vps->is_allocated();
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vps_t is a zombie, false
        ///     if the provided VPID is invalid, or if the vps_t is not
        ///     a zombie.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vpsid the ID of the vps_t to query
        ///   @return Returns true if the requested vps_t is a zombie, false
        ///     if the provided VPID is invalid, or if the vps_t is not
        ///     a zombie.
        ///
        [[nodiscard]] constexpr auto
        is_zombie(tls_t &tls, bsl::safe_uint16 const &vpsid) const &noexcept -> bool
        {
            bsl::discard(tls);

            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return false;
            }

            return vps->is_zombie();
        }

        /// <!-- description -->
        ///   @brief If a vps_t in the pool is assigned to the requested VP,
        ///     the ID of the first vps_t found is returned. Otherwise, this
        ///     function will return bsl::safe_uint16::zero(true)
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vpid the ID fo the VP to query
        ///   @return If a vps_t in the pool is assigned to the requested VP,
        ///     the ID of the first vps_t found is returned. Otherwise, this
        ///     function will return bsl::safe_uint16::zero(true)
        ///
        [[nodiscard]] constexpr auto
        is_assigned_to_vp(tls_t &tls, bsl::safe_uint16 const &vpid) const &noexcept
            -> bsl::safe_uint16
        {
            bsl::discard(tls);

            if (bsl::unlikely(!vpid)) {
                bsl::error() << "invalid vpid\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == vpid)) {
                bsl::error() << "invalid vpid\n" << bsl::here();
                return bsl::safe_uint16::zero(true);
            }

            for (auto const elem : m_pool) {
                if (elem.data->assigned_vp() == vpid) {
                    return elem.data->id();
                }

                bsl::touch();
            }

            return bsl::safe_uint16::zero(true);
        }

        /// <!-- description -->
        ///   @brief Sets the requested vps_t as active.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the vps_t to set as active
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        set_active(
            tls_t &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::errc_failure;
            }

            return vps->set_active(tls, intrinsic);
        }

        /// <!-- description -->
        ///   @brief Sets the requested vps_t as inactive.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the vps_t to set as inactive
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        set_inactive(
            tls_t &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

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
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

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
        ///   @param tls the current TLS block
        ///   @param vpsid the ID of the vps_t to query
        ///   @return Returns true if this vps_t is active on the current PP,
        ///     false if the provided ID is invalid, or if the vps_t is not
        ///     active on the current PP.
        ///
        [[nodiscard]] constexpr auto
        is_active_on_current_pp(tls_t &tls, bsl::safe_uint16 const &vpsid) &noexcept -> bool
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return false;
            }

            return vps->is_active_on_current_pp(tls);
        }

        /// <!-- description -->
        ///   @brief Migrates the requested vps_t from one PP to another.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @param vpsid the ID of the vps_t to migrate
        ///   @param ppid the ID of the PP to migrate to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        migrate(tls_t &tls, bsl::safe_uint16 const &vpsid, bsl::safe_uint16 const &ppid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

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
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

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
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::safe_uint16::zero(true);
            }

            return vps->assigned_pp();
        }

        /// <!-- description -->
        ///   @brief Stores the provided state in the requested VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to set the state to
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename INTRINSIC_CONCEPT, typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        state_save_to_vps(
            tls_t &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            STATE_SAVE_CONCEPT const &state) &noexcept -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::errc_failure;
            }

            return vps->state_save_to_vps(tls, intrinsic, state);
        }

        /// <!-- description -->
        ///   @brief Stores the requested VPS state in the provided state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to set the state to
        ///   @param state the state save to store the VPS state to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename INTRINSIC_CONCEPT, typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        vps_to_state_save(
            tls_t &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            STATE_SAVE_CONCEPT &state) &noexcept -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

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

        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to read from
        ///   @param index the index of the field to read from the VPS
        ///   @return Returns the value of the requested field from the
        ///     requested VPS or bsl::safe_integral<FIELD_TYPE>::zero(true)
        ///     on failure.
        ///
        template<typename FIELD_TYPE, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        read(
            tls_t &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            bsl::safe_uintmax const &index) &noexcept -> bsl::safe_integral<FIELD_TYPE>
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

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

        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to write to
        ///   @param index the index of the field to write to the VPS
        ///   @param value the value to write to the VPS
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename FIELD_TYPE, typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        write(
            tls_t &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            bsl::safe_uintmax const &index,
            bsl::safe_integral<FIELD_TYPE> const &value) &noexcept -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::errc_failure;
            }

            return vps->template write<FIELD_TYPE>(tls, intrinsic, index, value);
        }

        /// <!-- description -->
        ///   @brief Reads a field from the requested VPS given a bf_reg_t
        ///     defining the field to read.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to read from
        ///   @param reg a bf_reg_t defining the field to read from the VPS
        ///   @return Returns the value of the requested field from the
        ///     requested VPS or bsl::safe_uintmax::zero(true) on failure.
        ///
        template<typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        read_reg(
            tls_t &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            syscall::bf_reg_t const reg) &noexcept -> bsl::safe_uintmax
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::safe_uintmax::zero(true);
            }

            return vps->read_reg(tls, intrinsic, reg);
        }

        /// <!-- description -->
        ///   @brief Writes a field to the requested VPS given a bf_reg_t
        ///     defining the field and a value to write.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to write to
        ///   @param reg a bf_reg_t defining the field to write to the VPS
        ///   @param value the value to write to the VPS
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        write_reg(
            tls_t &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            syscall::bf_reg_t const reg,
            bsl::safe_uintmax const &value) &noexcept -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

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
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @tparam VMEXIT_LOG_CONCEPT defines the type of VMExit log to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param log the VMExit log to use
        ///   @param vpsid the ID of the VPS to run
        ///   @return Returns the VMExit reason on success, or
        ///     bsl::safe_uintmax::zero(true) on failure.
        ///
        template<typename INTRINSIC_CONCEPT, typename VMEXIT_LOG_CONCEPT>
        [[nodiscard]] constexpr auto
        run(tls_t &tls,
            INTRINSIC_CONCEPT &intrinsic,
            bsl::safe_uint16 const &vpsid,
            VMEXIT_LOG_CONCEPT &log) &noexcept -> bsl::safe_uintmax
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::safe_uintmax::zero(true);
            }

            return vps->run(tls, intrinsic, log);
        }

        /// <!-- description -->
        ///   @brief Advance the IP of the requested VPS
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to advance the IP for
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        advance_ip(
            tls_t &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

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
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to clear
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename INTRINSIC_CONCEPT>
        [[nodiscard]] constexpr auto
        clear(tls_t &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
            -> bsl::errc_type
        {
            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return bsl::errc_failure;
            }

            return vps->clear(tls, intrinsic);
        }

        /// <!-- description -->
        ///   @brief Dumps the requested VPS
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
        ///   @param tls the current TLS block
        ///   @param intrinsic the intrinsics to use
        ///   @param vpsid the ID of the VPS to dump
        ///
        template<typename INTRINSIC_CONCEPT>
        constexpr void
        dump(tls_t &tls, INTRINSIC_CONCEPT &intrinsic, bsl::safe_uint16 const &vpsid) &noexcept
        {
            if constexpr (BSL_DEBUG_LEVEL == bsl::CRITICAL_ONLY) {
                return;
            }

            auto *const vps{m_pool.at_if(bsl::to_umax(vpsid))};
            if (bsl::unlikely(nullptr == vps)) {
                bsl::error() << "vpsid "                                                   // --
                             << bsl::hex(vpsid)                                            // --
                             << " is invalid or greater than or equal to the MAX_VPSS "    // --
                             << bsl::hex(bsl::to_u16(MAX_VPSS))                            // --
                             << bsl::endl                                                  // --
                             << bsl::here();                                               // --

                return;
            }

            vps->dump(tls, intrinsic);
        }
    };
}

#endif
