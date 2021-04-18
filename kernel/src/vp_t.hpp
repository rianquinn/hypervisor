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

#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @brief defines the value of an invalid VPID
    constexpr bsl::safe_uint16 INVALID_VPID{bsl::to_u16(0xFFFFU)};

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
        bsl::safe_uint16 m_assigned_vmid{bsl::safe_uint16::zero(true)};
        /// @brief stores the ID of the PP this vp_t is assigned to
        bsl::safe_uint16 m_assigned_ppid{bsl::safe_uint16::zero(true)};

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
                this->release();
            }};

            if (bsl::unlikely(!i)) {
                bsl::error() << "invalid id\n" << bsl::here();
                return bsl::errc_failure;
            }

            release_on_error.ignore();

            m_id = i;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vp_t
        ///
        constexpr void
        release() &noexcept
        {
            this->deallocate();

            m_id = bsl::safe_uint16::zero(true);
            m_next = {};
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

            if (bsl::unlikely(this->is_allocated())) {
                bsl::error() << "vp_t already allocated\n" << bsl::here();
                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Deallocates this vp_t
        ///
        constexpr void
        deallocate() &noexcept
        {
            m_assigned_ppid = bsl::safe_uint16::zero(true);
            m_assigned_vmid = bsl::safe_uint16::zero(true);
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
            return this == m_next;
        }

        /// <!-- description -->
        ///   @brief Assigns this vp_t to a VM
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the VM this vp_t is assigned to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        assign_vm(bsl::safe_uint16 const &vmid) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vp\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!vmid)) {
                bsl::error() << "invalid vmid\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_assigned_vmid = vmid;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Assigns this vp_t to a PP
        ///
        /// <!-- inputs/outputs -->
        ///   @param ppid the PP this vp_t is assigned to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        assign_pp(bsl::safe_uint16 const &ppid) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vp\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!ppid)) {
                bsl::error() << "invalid ppid\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_assigned_ppid = ppid;
            return bsl::errc_success;
        }

        /// TODO:
        /// - Add a migrate function (and associated syscall API). You should
        ///   only be allowed to migrate a VP to a specific PP. Once this
        ///   occurs, each VPS that is assigned to this VP will also need to
        ///   be migrated as well.
        ///

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

            /// Assigned VM
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "assigned vm "};
            bsl::print() << bsl::ylw << "| ";
            if (m_assigned_vmid) {
                bsl::print() << bsl::grn << "  " << bsl::hex(m_assigned_vmid) << "   ";
            }
            else {
                bsl::print() << bsl::red << bsl::fmt{"^11s", "unassigned "};
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Assigned VM
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "assigned pp "};
            bsl::print() << bsl::ylw << "| ";
            if (m_assigned_ppid) {
                bsl::print() << bsl::grn << "  " << bsl::hex(m_assigned_ppid) << "   ";
            }
            else {
                bsl::print() << bsl::red << bsl::fmt{"^11s", "unassigned "};
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
