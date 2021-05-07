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

#ifndef VP_T_BASE_HPP
#define VP_T_BASE_HPP

#include <allocated_status_t.hpp>

#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>

namespace mk
{
    /// @class mk::vp_t_base
    ///
    /// <!-- description -->
    ///   @brief Provides the base vp_t for testing.
    ///
    template<typename derived>
    class vp_t_base
    {
    protected:
        /// @brief stores the ID associated with this vp_t
        bsl::safe_uint16 m_id{bsl::safe_uint16::zero(true)};
        /// @brief stores whether or not this vp_t is allocated.
        allocated_status_t m_allocated{allocated_status_t::deallocated};
        /// @brief stores the ID of the VM this vp_t is assigned to
        bsl::safe_uint16 m_assigned_vmid{syscall::BF_INVALID_ID};
        /// @brief stores the ID of the PP this vp_t is assigned to
        bsl::safe_uint16 m_assigned_ppid{syscall::BF_INVALID_ID};
        /// @brief stores whether or not this vp_t is active.
        bool m_active{};

    public:
        /// <!-- description -->
        ///   @brief Initializes this vp_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param i the ID for this vp_t
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(bsl::safe_uint16 const &i) &noexcept -> bsl::errc_type
        {
            m_id = i;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vp_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
        ///   @param tls the current TLS block
        ///   @param vps_pool the VPS pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT, typename VPS_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        release(TLS_CONCEPT &tls, VPS_POOL_CONCEPT &vps_pool) &noexcept -> bsl::errc_type
        {
            bsl::discard(tls);
            bsl::discard(vps_pool);

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns the ID of this vp_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of this vp_t
        ///
        [[nodiscard]] constexpr auto
        id() const &noexcept -> bsl::safe_uint16 const &
        {
            return m_id;
        }

        /// <!-- description -->
        ///   @brief Allocates this vp_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
        ///   @param tls the current TLS block
        ///   @param vm_pool the VM pool to use
        ///   @param vmid The ID of the VM to assign the newly created VP to
        ///   @param ppid The ID of the PP to assign the newly created VP to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT, typename VM_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        allocate(
            TLS_CONCEPT &tls,
            VM_POOL_CONCEPT &vm_pool,
            bsl::safe_uint16 const &vmid,
            bsl::safe_uint16 const &ppid) &noexcept -> bsl::safe_uint16
        {
            bsl::discard(tls);
            bsl::discard(vm_pool);

            m_assigned_vmid = vmid;
            m_assigned_ppid = ppid;
            m_allocated = allocated_status_t::allocated;

            return m_id;
        }

        /// <!-- description -->
        ///   @brief Deallocates this vp_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
        ///   @param tls the current TLS block
        ///   @param vps_pool the VPS pool to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT, typename VPS_POOL_CONCEPT>
        [[nodiscard]] constexpr auto
        deallocate(TLS_CONCEPT &tls, VPS_POOL_CONCEPT &vps_pool) &noexcept -> bsl::errc_type
        {
            bsl::discard(tls);
            bsl::discard(vps_pool);

            m_assigned_ppid = syscall::BF_INVALID_ID;
            m_assigned_vmid = syscall::BF_INVALID_ID;
            m_allocated = allocated_status_t::deallocated;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Sets this vp_t's status as zombified, meaning it is no
        ///     longer usable.
        ///
        constexpr void
        zombify() &noexcept
        {
            m_allocated = allocated_status_t::zombie;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vp_t is deallocated, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vp_t is deallocated, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_deallocated() const &noexcept -> bool
        {
            return m_allocated == allocated_status_t::deallocated;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vp_t is allocated, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vp_t is allocated, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_allocated() const &noexcept -> bool
        {
            return m_allocated == allocated_status_t::allocated;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vp_t is a zombie, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vp_t is a zombie, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_zombie() const &noexcept -> bool
        {
            return m_allocated == allocated_status_t::zombie;
        }

        /// <!-- description -->
        ///   @brief Sets this vp_t as active.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_active(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            bsl::discard(tls);

            m_active = true;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Sets this vp_t as inactive.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        set_inactive(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            bsl::discard(tls);

            m_active = {};
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the first PP identified that this VP
        ///     is still active on. If the VP is inactive, this function
        ///     returns bsl::safe_uint16::zero(true)
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns the ID of the first PP identified that this VP
        ///     is still active on. If the VP is inactive, this function
        ///     returns bsl::safe_uint16::zero(true)
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_active(TLS_CONCEPT &tls) const &noexcept -> bsl::safe_uint16
        {
            bsl::discard(tls);

            if (m_active) {
                return bsl::ZERO_U16;
            }

            return bsl::safe_uint16::zero(true);
        }

        /// <!-- description -->
        ///   @brief Returns true if this vp_t is active on the current PP,
        ///     false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns true if this vp_t is active on the current PP,
        ///     false otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        is_active_on_current_pp(TLS_CONCEPT &tls) const &noexcept -> bool
        {
            bsl::discard(tls);
            return m_active;
        }

        /// <!-- description -->
        ///   @brief Migrates this vp_t from one PP to another. If this calls
        ///     completes successfully, the VPS's assigned PP will not
        ///     match the VP's assigned PP. Future calls to the run ABI
        ///     will be able to detect this an migrate mismatched VPSs to
        ///     the proper PP as needed. Note that since the VP doesn't control
        ///     any hardware state, all we have to do here is set which PP
        ///     this VP is allowed to execute on. The VPS is what actually
        ///     needs to be migrated, and that will not happen until a call
        ///     to the run ABIs made. Once the run ABI detects a mismatch with
        ///     the VPS and it's assigned VP, it will be migrated then.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param ppid the ID of the PP to migrate to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        migrate(TLS_CONCEPT &tls, bsl::safe_uint16 const &ppid) &noexcept -> bsl::errc_type
        {
            bsl::discard(tls);
            bsl::discard(ppid);

            m_assigned_ppid = ppid;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the VM this vp_t is assigned to
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of the VM this vp_t is assigned to
        ///
        [[nodiscard]] constexpr auto
        assigned_vm() const &noexcept -> bsl::safe_uint16
        {
            if (bsl::unlikely(syscall::BF_INVALID_ID == m_assigned_vmid)) {
                return bsl::safe_uint16::zero(true);
            }

            return m_assigned_vmid;
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the PP this vp_t is assigned to
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of the PP this vp_t is assigned to
        ///
        [[nodiscard]] constexpr auto
        assigned_pp() const &noexcept -> bsl::safe_uint16
        {
            if (bsl::unlikely(syscall::BF_INVALID_ID == m_assigned_ppid)) {
                return bsl::safe_uint16::zero(true);
            }

            return m_assigned_ppid;
        }

        // <!-- description -->
        ///   @brief Dumps the vp_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        dump(TLS_CONCEPT &tls) const &noexcept
        {
            bsl::discard(tls);
        }
    };
}

#endif
