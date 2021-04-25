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
        ///   @brief Initializes this vp_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param i the ID for this vp_t
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(bsl::safe_uint16 const &i) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(m_id)) {
                bsl::error() << "vp_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[this]() noexcept -> void {
                if (bsl::unlikely(!this->release())) {
                    bsl::print<bsl::V>() << bsl::here();
                    return;
                }

                bsl::touch();
            }};

            if (bsl::unlikely(!i)) {
                bsl::error() << "invalid id\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_id = i;

            release_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vp_t. Note that if this function fails,
        ///     the microkernel is left in a corrupt state and all use of the
        ///     vp_t after calling this function will results in UB.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        release() &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!this->deallocate())) {
                bsl::error() << "failed to release vp "         // --
                             << bsl::hex(m_id)                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            m_id = bsl::safe_uint16::zero(true);
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Allocates this vp_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        allocate() &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vp_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_allocated)) {
                bsl::error() << "vp "                           // --
                             << bsl::hex(m_id)                  // --
                             << " was was already allocated"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            m_allocated = true;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Deallocates this vp_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        deallocate() &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!m_id)) {
                return bsl::errc_success;
            }

            if (bsl::unlikely(!m_allocated)) {
                return bsl::errc_success;
            }

            if (bsl::unlikely(this->is_active())) {
                bsl::error() << "vp "                           // --
                            << bsl::hex(m_id)                  // --
                            << " is still active and cannot be deallocated"    // --
                            << bsl::endl                       // --
                            << bsl::here();                    // --

                return bsl::errc_failure;
            }

            m_active_ppid = syscall::BF_INVALID_ID;
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
        ///     otherwise
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
                bsl::error() << "vp "                           // --
                             << bsl::hex(m_id)                  // --
                             << " was was never allocated"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.active_vpid == m_id)) {
                bsl::error() << "vp "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is already active"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_active_ppid != syscall::BF_INVALID_ID)) {
                bsl::error() << "vp "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is already active"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

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
        ///     otherwise
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
                bsl::error() << "vp "                           // --
                             << bsl::hex(m_id)                  // --
                             << " was was never allocated"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.active_vpid != m_id)) {
                bsl::error() << "vp "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is not active"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_active_ppid == syscall::BF_INVALID_ID)) {
                bsl::error() << "vp "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is not active"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

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
            return m_active;
        }

        /// <!-- description -->
        ///   @brief Assigns this vp_t to a VM
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the VM this vp_t is assigned to
        ///
        constexpr void
        assign_vm(bsl::safe_uint16 const &vmid) &noexcept
        {
            m_assigned_vmid = vmid;
        }

        /// <!-- description -->
        ///   @brief Assigns this vp_t to a PP
        ///
        /// <!-- inputs/outputs -->
        ///   @param ppid the PP this vp_t is assigned to
        ///
        constexpr void
        assign_pp(bsl::safe_uint16 const &ppid) &noexcept
        {
            m_assigned_ppid = ppid;
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
            return m_assigned_ppid;
        }

        // /// <!-- description -->
        // ///   @brief Migrates this VP from one PP to another. If this calls
        // ///     completes successfully, the VPSs's assigned PP will not
        // ///     match the VP's assigned PP. Future calls to the run ABI
        // ///     will be able to detect this an migrate mismatched VPSs to
        // ///     the proper PP as needed.
        // ///
        // /// <!-- inputs/outputs -->
        // ///   @tparam TLS_POOL_CONCEPT defines the type of TLS pool to use
        // ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        // ///   @param tls_pool the TLS pool to use
        // ///   @param tls the current TLS block
        // ///   @param ppid the ID of the pP to migrate to
        // ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        // ///     otherwise
        // ///
        // template<typename TLS_POOL_CONCEPT, typename TLS_CONCEPT>
        // [[nodiscard]] constexpr auto
        // migrate(
        //     TLS_POOL_CONCEPT &tls_pool, TLS_CONCEPT &tls, bsl::safe_uint16 const &ppid) &noexcept
        //     -> bsl::safe_uintmax
        // {
        //     if (bsl::unlikely(!this->is_allocated())) {
        //         bsl::error() << "invalid vp\n" << bsl::here();
        //         return bsl::errc_failure;
        //     }

        //     if (bsl::unlikely(!ppid)) {
        //         bsl::error() << "invalid ppid\n" << bsl::here();
        //         return bsl::errc_failure;
        //     }

        //     if (bsl::unlikely(syscall::BF_INVALID_ID == assigned_vm)) {
        //         bsl::error() << "vp "                            // --
        //                      << bsl::hex(m_id)                   // --
        //                      << " was never assigned to a vm"    // --
        //                      << bsl::endl                        // --
        //                      << bsl::here();                     // --

        //         return bsl::errc_failure;
        //     }

        //     if (bsl::unlikely(syscall::BF_INVALID_ID == assigned_pp)) {
        //         bsl::error() << "vp "                            // --
        //                      << bsl::hex(m_id)                   // --
        //                      << " was never assigned to a pp"    // --
        //                      << bsl::endl                        // --
        //                      << bsl::here();                     // --

        //         return bsl::errc_failure;
        //     }

        //     /// NOTE:
        //     /// - The following check is super important as it handles several
        //     ///   different types of issues.
        //     /// - If a VP is active on another PP, it means that it is
        //     ///   executing. This means that a VPS associated with this VP is
        //     ///   also executing, which means it cannot be cleared. Migration
        //     ///   should normally happen by an extension when a VM exit is
        //     ///   taken by one VP to execute another VP. For example, if a
        //     ///   root VP gets a "run this VM using this VP and VPS" command
        //     ///   one a PP that the VP and VPS were not originally assigned
        //     ///   to, which basically means whatever scheduler is in place
        //     ///   decided that it would be best to move the VP and VPS to
        //     ///   another PP. If this happens, the active VP is the root VP,
        //     ///   and so the VP and VPS that need to be run should be in the
        //     ///   inactive state.
        //     /// - The other thing that this does is ensures that we don't have
        //     ///   an issue with a VPS executing on another core. Extensions
        //     ///   can only run a VPS on the VP it was assigned to. This means
        //     ///   that if the VP is inactive, any VPS that was assigned to the
        //     ///   VP must also be inactive. In otherwords, we don't need to
        //     ///   track the activity state of the VPSs as by design, this edge
        //     ///   case is not possible.
        //     ///

        //     if (bsl::unlikely(tls_pool.is_vp_active(m_id))) {
        //         bsl::error() << "vp "                                            // --
        //                      << bsl::hex(vpid)                                   // --
        //                      << " is currently active and cannot be migrated"    // --
        //                      << bsl::endl                                        // --
        //                      << bsl::here();                                     // --

        //         return bsl::errc_failure;
        //     }

        //     if (bsl::unlikely(!(ppid < tls.online_pps))) {
        //         bsl::error() << "pp "                 // --
        //                      << bsl::hex(ppid)        // --
        //                      << " is out of range"    // --
        //                      << bsl::endl             // --
        //                      << bsl::here();          // --

        //         return bsl::errc_failure;
        //     }

        //     this->assign_pp(ppid);
        //     return bsl::errc_success;
        // }

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
            if (m_assigned_vmid != syscall::BF_INVALID_ID) {
                bsl::print() << bsl::grn << "  " << bsl::hex(m_assigned_vmid) << "   ";
            }
            else {
                bsl::print() << bsl::red << "  " << bsl::hex(m_assigned_vmid) << "   ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Assigned VM
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "assigned pp "};
            bsl::print() << bsl::ylw << "| ";
            if (m_assigned_ppid != syscall::BF_INVALID_ID) {
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
