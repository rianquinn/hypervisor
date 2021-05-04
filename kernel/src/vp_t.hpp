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

#ifndef VP_T_HPP
#define VP_T_HPP

#include <mk_interface.hpp>

#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/likely.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @class mk::vp_t
    ///
    /// <!-- description -->
    ///   @brief Defines the microkernel's notion of a VP
    ///
    class vp_t final
    {
        /// @brief stores the next vp_t in the vp_pool_t linked list
        vp_t *m_next{};
        /// @brief stores the ID associated with this vp_t
        bsl::safe_uint16 m_id{bsl::safe_uint16::zero(true)};
        /// @brief stores whether or not this vp_t is allocated.
        bool m_allocated{};
        /// @brief stores the ID of the VM this vp_t is assigned to
        bsl::safe_uint16 m_assigned_vmid{syscall::BF_INVALID_ID};
        /// @brief stores the ID of the PP this vp_t is assigned to
        bsl::safe_uint16 m_assigned_ppid{syscall::BF_INVALID_ID};
        /// @brief stores the ID of the PP this vp_t is active on
        bsl::safe_uint16 m_active_ppid{syscall::BF_INVALID_ID};

    public:
        /// <!-- description -->
        ///   @brief Default constructor
        ///
        constexpr vp_t() noexcept = default;

        /// <!-- description -->
        ///   @brief Destructor
        ///
        constexpr ~vp_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr vp_t(vp_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr vp_t(vp_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vp_t const &o) &noexcept -> vp_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vp_t &&o) &noexcept -> vp_t & = default;

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
            if (bsl::unlikely(m_id)) {
                bsl::error() << "vp_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!i)) {
                bsl::error() << "invalid id\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == i)) {
                bsl::error() << "invalid id\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_id = i;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vp_t. Note that if this function fails,
        ///     the microkernel is left in a corrupt state and all use of the
        ///     vp_t after calling this function will results in UB.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] constexpr auto
        release() &noexcept -> bsl::errc_type
        {
            if (syscall::BF_INVALID_ID != m_active_ppid) {
                bsl::error() << "vp "                        // --
                             << bsl::hex(m_id)               // --
                             << " is still active on pp "    // --
                             << bsl::hex(m_active_ppid)      // --
                             << " and cannot be released"    // --
                             << bsl::endl                    // --
                             << bsl::here();                 // --

                return bsl::errc_failure;
            }

            m_assigned_ppid = syscall::BF_INVALID_ID;
            m_assigned_vmid = syscall::BF_INVALID_ID;
            m_allocated = {};
            m_id = bsl::safe_uint16::zero(true);

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
        ///   @param tls the current TLS block
        ///   @param vmid The ID of the VM to assign the newly created VP to
        ///   @param ppid The ID of the PP to assign the newly created VP to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        allocate(
            TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid, bsl::safe_uint16 const &ppid) &noexcept
            -> bsl::errc_type
        {
            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vp_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_allocated)) {
                bsl::error() << "vp "                      // --
                             << bsl::hex(m_id)             // --
                             << " is already allocated"    // --
                             << bsl::endl                  // --
                             << bsl::here();               // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(!vmid)) {
                bsl::error() << "invalid vmid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == vmid)) {
                bsl::error() << "invalid vmid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!ppid)) {
                bsl::error() << "invalid ppid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == ppid)) {
                bsl::error() << "invalid ppid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!(ppid < tls.online_pps))) {
                bsl::error() << "invalid ppid\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_assigned_vmid = vmid;
            m_assigned_ppid = ppid;
            m_allocated = true;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Deallocates this vp_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        deallocate(TLS_CONCEPT const &tls) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!m_id)) {
                return bsl::errc_success;
            }

            if (bsl::unlikely(!m_allocated)) {
                return bsl::errc_success;
            }

            if (bsl::unlikely(tls.ppid != m_assigned_ppid)) {
                bsl::error() << "vp "                                  // --
                             << bsl::hex(m_id)                         // --
                             << " is assigned to pp "                  // --
                             << bsl::hex(m_assigned_ppid)              // --
                             << " and cannot be deallocated on pp "    // --
                             << bsl::hex(tls.ppid)                     // --
                             << bsl::endl                              // --
                             << bsl::here();                           // --

                return bsl::errc_failure;
            }

            if (syscall::BF_INVALID_ID != m_active_ppid) {
                bsl::error() << "vp "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is still active on pp "       // --
                             << bsl::hex(m_active_ppid)         // --
                             << " and cannot be deallocated"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            m_assigned_ppid = syscall::BF_INVALID_ID;
            m_assigned_vmid = syscall::BF_INVALID_ID;
            m_allocated = {};

            return bsl::errc_success;
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
            return m_allocated;
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
            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vp_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!m_allocated)) {
                bsl::error() << "vp "                     // --
                             << bsl::hex(m_id)            // --
                             << " was never allocated"    // --
                             << bsl::endl                 // --
                             << bsl::here();              // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.ppid != m_assigned_ppid)) {
                bsl::error() << "vp "                                // --
                             << bsl::hex(m_id)                       // --
                             << " is assigned to pp "                // --
                             << bsl::hex(m_assigned_ppid)            // --
                             << " and cannot be activated on pp "    // --
                             << bsl::hex(tls.ppid)                   // --
                             << bsl::endl                            // --
                             << bsl::here();                         // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.active_vpid == m_id)) {
                bsl::error() << "vp "                                 // --
                             << bsl::hex(m_id)                        // --
                             << " is already the active vp on pp "    // --
                             << bsl::hex(tls.ppid)                    // --
                             << bsl::endl                             // --
                             << bsl::here();                          // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID != tls.active_vpid)) {
                bsl::error() << "vp "                        // --
                             << bsl::hex(tls.active_vpid)    // --
                             << " is still active on pp "    // --
                             << bsl::hex(tls.ppid)           // --
                             << bsl::endl                    // --
                             << bsl::here();                 // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID != m_active_ppid)) {
                bsl::error() << "vp "                                 // --
                             << bsl::hex(m_id)                        // --
                             << " is already the active vp on pp "    // --
                             << bsl::hex(m_active_ppid)               // --
                             << bsl::endl                             // --
                             << bsl::here();                          // --

                return bsl::errc_failure;
            }

            tls.active_vpid = m_id.get();
            m_active_ppid = tls.ppid;

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
            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vp_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!m_allocated)) {
                bsl::error() << "vp "                     // --
                             << bsl::hex(m_id)            // --
                             << " was never allocated"    // --
                             << bsl::endl                 // --
                             << bsl::here();              // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.ppid != m_assigned_ppid)) {
                bsl::error() << "vp "                                  // --
                             << bsl::hex(m_id)                         // --
                             << " is assigned to pp "                  // --
                             << bsl::hex(m_assigned_ppid)              // --
                             << " and cannot be deactivated on pp "    // --
                             << bsl::hex(tls.ppid)                     // --
                             << bsl::endl                              // --
                             << bsl::here();                           // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == tls.active_vpid)) {
                bsl::error() << "vp "                      // --
                             << bsl::hex(m_id)             // --
                             << " is not active on pp "    // --
                             << bsl::hex(tls.ppid)         // --
                             << bsl::endl                  // --
                             << bsl::here();               // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.active_vpid != m_id)) {
                bsl::error() << "vp "                        // --
                             << bsl::hex(tls.active_vpid)    // --
                             << " is still active on pp "    // --
                             << bsl::hex(tls.ppid)           // --
                             << bsl::endl                    // --
                             << bsl::here();                 // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == m_active_ppid)) {
                bsl::error() << "vp "                      // --
                             << bsl::hex(m_id)             // --
                             << " is not active on pp "    // --
                             << bsl::hex(tls.ppid)         // --
                             << bsl::endl                  // --
                             << bsl::here();               // --

                return bsl::errc_failure;
            }

            tls.active_vpid = syscall::BF_INVALID_ID.get();
            m_active_ppid = syscall::BF_INVALID_ID;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vp_t is active, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vp_t is active, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_active() const &noexcept -> bool
        {
            return syscall::BF_INVALID_ID != m_active_ppid;
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
        is_active_on_current_pp(TLS_CONCEPT const &tls) const &noexcept -> bool
        {
            return tls.ppid == m_active_ppid;
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
            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vp_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!m_allocated)) {
                bsl::error() << "vp "                     // --
                             << bsl::hex(m_id)            // --
                             << " was never allocated"    // --
                             << bsl::endl                 // --
                             << bsl::here();              // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(!ppid)) {
                bsl::error() << "invalid ppid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == ppid)) {
                bsl::error() << "invalid ppid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!(ppid < tls.online_pps))) {
                bsl::error() << "invalid ppid\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.ppid != ppid)) {
                bsl::error() << "vp "                          // --
                             << bsl::hex(m_id)                 // --
                             << " is being migrated to pp "    // --
                             << bsl::hex(ppid)                 // --
                             << " by pp "                      // --
                             << bsl::hex(tls.ppid)             // --
                             << " which is not allowed "       // --
                             << bsl::endl                      // --
                             << bsl::here();                   // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(ppid == m_assigned_ppid)) {
                bsl::error() << "vp "                              // --
                             << bsl::hex(m_id)                     // --
                             << " is already assigned to a pp "    // --
                             << bsl::hex(m_assigned_ppid)          // --
                             << bsl::endl                          // --
                             << bsl::here();                       // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID != m_active_ppid)) {
                bsl::error() << "vp "                        // --
                             << bsl::hex(m_id)               // --
                             << " is still active on pp "    // --
                             << bsl::hex(m_active_ppid)      // --
                             << bsl::endl                    // --
                             << bsl::here();                 // --

                return bsl::errc_failure;
            }

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
        assigned_vm() const &noexcept -> bsl::safe_uint16 const &
        {
            return m_assigned_vmid;
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the PP this vp_t is assigned to
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of the PP this vp_t is assigned to
        ///
        [[nodiscard]] constexpr auto
        assigned_pp() const &noexcept -> bsl::safe_uint16 const &
        {
            return m_assigned_ppid;
        }

        /// <!-- description -->
        ///   @brief Returns the next vp_t in the vp_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the next vp_t in the vp_pool_t linked list
        ///
        [[nodiscard]] constexpr auto
        next() const &noexcept -> vp_t *
        {
            return m_next;
        }

        /// <!-- description -->
        ///   @brief Sets the next vp_t in the vp_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @param val the next vp_t in the vp_pool_t linked list to set
        ///
        constexpr void
        set_next(vp_t *val) &noexcept
        {
            m_next = val;
        }

        /// <!-- description -->
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

            if constexpr (BSL_DEBUG_LEVEL == bsl::CRITICAL_ONLY) {
                return;
            }

            if (bsl::unlikely(!m_id)) {
                bsl::print() << "[error]" << bsl::endl;
                return;
            }

            bsl::print() << bsl::mag << "vp [";
            bsl::print() << bsl::rst << bsl::hex(m_id);
            bsl::print() << bsl::mag << "] dump: ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Header
            ///

            bsl::print() << bsl::ylw << "+--------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^12s", "description "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^11s", "value "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+--------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            /// Allocated
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "allocated "};
            bsl::print() << bsl::ylw << "| ";
            if (this->is_allocated()) {
                bsl::print() << bsl::grn << bsl::fmt{"^11s", "yes "};
            }
            else {
                bsl::print() << bsl::red << bsl::fmt{"^11s", "no "};
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Active
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "active "};
            bsl::print() << bsl::ylw << "| ";
            if (this->is_active()) {
                bsl::print() << bsl::grn << bsl::fmt{"^11s", "yes "};
            }
            else {
                bsl::print() << bsl::red << bsl::fmt{"^11s", "no "};
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Assigned VM
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "assigned vm "};
            bsl::print() << bsl::ylw << "| ";
            if (syscall::BF_INVALID_ID != m_assigned_vmid) {
                bsl::print() << bsl::grn << "  " << bsl::hex(m_assigned_vmid) << "   ";
            }
            else {
                bsl::print() << bsl::red << "  " << bsl::hex(m_assigned_vmid) << "   ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Assigned PP
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "assigned pp "};
            bsl::print() << bsl::ylw << "| ";
            if (syscall::BF_INVALID_ID != m_assigned_ppid) {
                bsl::print() << bsl::grn << "  " << bsl::hex(m_assigned_ppid) << "   ";
            }
            else {
                bsl::print() << bsl::red << "  " << bsl::hex(m_assigned_ppid) << "   ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Footer
            ///

            bsl::print() << bsl::ylw << "+--------------------------+";
            bsl::print() << bsl::rst << bsl::endl;
        }
    };
}

#endif
