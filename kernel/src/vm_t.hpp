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

#ifndef VM_T_HPP
#define VM_T_HPP

#include <mk_interface.hpp>

#include <bsl/debug.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>
#include <bsl/array.hpp>

namespace mk
{
    /// @class mk::vm_t
    ///
    /// <!-- description -->
    ///   @brief Defines the microkernel's notion of a VM. Unlike a VP or
    ///     VPS, a VM can be run on any PP at any time and in any combination.
    ///     For example, you could have PPs 0-2 running VM1 and PPs 3-4
    ///     running VM2. A VM is not dedicated to any specific PP. A VP and
    ///     VPS are different. They are assigned to a specific VM and a
    ///     specific PP (well, a VP is assigned to a VM and a PP, and a VPS
    ///     is assigned to a VP and PP, and so there for a VPS is indirectly
    ///     assigned to a VM since it's parent VP is). VM assignment for a
    ///     VP and VPS cannot change. The only way to change it is to
    ///     deallocate the VP or VPS and they allocate it later as a new
    ///     resource. PP reassignment is done through migration. Basically,
    ///     the VP is migrated to a new PP, and then any time you try to
    ///     run a VPS, if the PP doesn't match the VP's PP, it is migrated
    ///     at that time, which is used to not only prevent the microkernel
    ///     from performing migration on VPSs that don't need it, but it
    ///     also ensures that the VPS is cleared and loaded on the PP that
    ///     it is being migrated to, which is a requirement for Intel. In
    ///     otherwords on Intel, you have to clear the VPS and then load the
    ///     VPS on the PP you plan to run VMLaunch on, which means that
    ///     migration has to occur on the PP you plan to use.
    ///
    ///     So based on the above, we have to track which PP the VM is active
    ///     on as it can be active on a lot of PPs, where as with a VP and
    ///     VPS, we only have to track if it is active or not since it can
    ///     only be active on one PP at a time.
    ///
    /// <!-- template parameters -->
    ///   @tparam MAX_PPS the max number of PPs supported
    ///
    template<bsl::uintmax MAX_PPS>
    class vm_t final
    {
        /// @brief stores the next vm_t in the vm_pool_t linked list
        vm_t *m_next{};
        /// @brief stores the ID associated with this vm_t
        bsl::safe_uint16 m_id{bsl::safe_uint16::zero(true)};
        /// @brief stores whether or not this VM is allocated.
        bool m_allocated{};
        /// @brief stores whether or not this VM is active.
        bsl::array<bool, MAX_PPS> m_active{};

    public:
        /// <!-- description -->
        ///   @brief Default constructor
        ///
        constexpr vm_t() noexcept = default;

        /// <!-- description -->
        ///   @brief Initializes this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param i the ID for this vm_t
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(bsl::safe_uint16 const &i) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(m_id)) {
                bsl::error() << "vm_t already initialized\n" << bsl::here();
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
        ///   @brief Release the vm_t. Note that if this function fails,
        ///     the microkernel is left in a corrupt state and all use of the
        ///     vm_t after calling this function will results in UB.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        release() &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!this->deallocate())) {
                bsl::error() << "failed to release vm "         // --
                             << bsl::hex(m_id)                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            m_id = bsl::safe_uint16::zero(true);
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Allocates this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        allocate() &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vm_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(m_allocated)) {
                bsl::error() << "vm "                           // --
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
        ///   @brief Deallocates this vm_t
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
                bsl::error() << "vm "                           // --
                            << bsl::hex(m_id)                  // --
                            << " is still active and cannot be deallocated"    // --
                            << bsl::endl                       // --
                            << bsl::here();                    // --

                return bsl::errc_failure;
            }

            m_active = {};
            m_allocated = {};

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vm_t is allocated, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vm_t is allocated, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_allocated() const &noexcept -> bool
        {
            return m_allocated;
        }

        /// <!-- description -->
        ///   @brief Sets this vm_t as active.
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
                bsl::error() << "vm_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!m_allocated)) {
                bsl::error() << "vm "                           // --
                             << bsl::hex(m_id)                  // --
                             << " was was never allocated"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.active_vmid == m_id)) {
                bsl::error() << "vm "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is already active"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            auto *const active{m_active.at_if(bsl::to_umax(tls.ppid))};
            if (bsl::unlikely(nullptr == active)) {
                bsl::error() << "tls.ppid "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is greater than the MAX_PPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_PPS))                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(*active)) {
                bsl::error() << "vm "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is already active"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            tls.active_vmid = m_id.get();
            *active = true;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Sets this vm_t as inactive.
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
                bsl::error() << "vm_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!m_allocated)) {
                bsl::error() << "vm "                           // --
                             << bsl::hex(m_id)                  // --
                             << " was was never allocated"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(tls.active_vmid != m_id)) {
                bsl::error() << "vm "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is not active"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            auto *const active{m_active.at_if(bsl::to_umax(tls.ppid))};
            if (bsl::unlikely(nullptr == active)) {
                bsl::error() << "tls.ppid "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is greater than the MAX_PPS "    // --
                             << bsl::hex(bsl::to_u16(MAX_PPS))                  // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely(!*active)) {
                bsl::error() << "vm "                           // --
                             << bsl::hex(m_id)                  // --
                             << " is not active"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            tls.active_vmid = syscall::BF_INVALID_ID.get();
            *active = false;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns true if this vm_t is active, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vm_t is active, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_active() const &noexcept -> bool
        {
            for (auto const elem : m_active) {
                if (*elem.data) {
                    return true;
                }

                bsl::touch();
            }

            return false;
        }

        /// <!-- description -->
        ///   @brief Destructor
        ///
        constexpr ~vm_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr vm_t(vm_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr vm_t(vm_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vm_t const &o) &noexcept -> vm_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vm_t &&o) &noexcept -> vm_t & = default;

        /// <!-- description -->
        ///   @brief Returns the ID of this vm_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of this vm_t
        ///
        [[nodiscard]] constexpr auto
        id() const &noexcept -> bsl::safe_uint16 const &
        {
            return m_id;
        }

        /// <!-- description -->
        ///   @brief Returns the next vm_t in the vm_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the next vm_t in the vm_pool_t linked list
        ///
        [[nodiscard]] constexpr auto
        next() const &noexcept -> vm_t *
        {
            return m_next;
        }

        /// <!-- description -->
        ///   @brief Sets the next vm_t in the vm_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @param val the next vm_t in the vm_pool_t linked list to set
        ///
        constexpr void
        set_next(vm_t *val) &noexcept
        {
            m_next = val;
        }

        /// <!-- description -->
        ///   @brief Dumps the vm_t
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

            bsl::print() << bsl::mag << "vm [";
            bsl::print() << bsl::rst << bsl::hex(m_id);
            bsl::print() << bsl::mag << "] dump: ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Header
            ///

            bsl::print() << bsl::ylw << "+---------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^12s", "description "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^6s", "value "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+---------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            /// Allocated
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "allocated "};
            bsl::print() << bsl::ylw << "| ";
            if (this->is_allocated()) {
                bsl::print() << bsl::grn << bsl::fmt{"^6s", "yes "};
            }
            else {
                bsl::print() << bsl::red << bsl::fmt{"^6s", "no "};
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Active
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<12s", "active "};
            bsl::print() << bsl::ylw << "| ";
            if (this->is_active()) {
                bsl::print() << bsl::grn << bsl::fmt{"^6s", "yes "};
            }
            else {
                bsl::print() << bsl::red << bsl::fmt{"^6s", "no "};
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Footer
            ///

            bsl::print() << bsl::ylw << "+---------------------+";
            bsl::print() << bsl::rst << bsl::endl;
        }
    };
}

#endif
