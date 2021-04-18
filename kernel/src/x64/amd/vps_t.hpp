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

#ifndef VPS_T_HPP
#define VPS_T_HPP

#include <allocate_tags.hpp>
#include <mk_interface.hpp>
#include <vmcb_t.hpp>
#include <vmexit_log_t.hpp>

#include <bsl/cstr_type.hpp>
#include <bsl/debug.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/string_view.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @brief defines the value of an invalid VPSID
    constexpr bsl::safe_uint16 INVALID_VPSID{bsl::to_u16(0xFFFFU)};

    /// <!-- description -->
    ///   @brief Converts attributes in the form 0xF0FF to the form
    ///     0x0FFF.
    ///
    /// <!-- inputs/outputs -->
    ///   @param attrib the attrib to compress
    ///   @return Returns the compressed version of attrib
    ///
    [[nodiscard]] constexpr auto
    compress_attrib(bsl::safe_uint16 const &attrib) noexcept -> bsl::safe_uint16
    {
        constexpr bsl::safe_uint16 mask1{bsl::to_u16(0x00FFU)};
        constexpr bsl::safe_uint16 mask2{bsl::to_u16(0xF000U)};
        constexpr bsl::safe_uint16 shift{bsl::to_u16(4)};

        return (attrib & mask1) | ((attrib & mask2) >> shift);
    }

    /// <!-- description -->
    ///   @brief Converts attributes in the form 0x0FFF to the form
    ///     0xF0FF.
    ///
    /// <!-- inputs/outputs -->
    ///   @param attrib the attrib to decompress
    ///   @return Returns the decompressed version of attrib
    ///
    [[nodiscard]] constexpr auto
    decompress_attrib(bsl::safe_uint16 const &attrib) noexcept -> bsl::safe_uint16
    {
        constexpr bsl::safe_uint16 mask1{bsl::to_u16(0x00FFU)};
        constexpr bsl::safe_uint16 mask2{bsl::to_u16(0x0F00U)};
        constexpr bsl::safe_uint16 shift{bsl::to_u16(4)};

        return (attrib & mask1) | ((attrib & mask2) << shift);
    }

    /// @class mk::vps_t
    ///
    /// <!-- description -->
    ///   @brief Defines the microkernel's notion of a VPS.
    ///
    /// <!-- template parameters -->
    ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
    ///
    template<typename INTRINSIC_CONCEPT, typename PAGE_POOL_CONCEPT>
    class vps_t final
    {
        /// @brief stores a reference to the intrinsics to use
        INTRINSIC_CONCEPT *m_intrinsic{};
        /// @brief stores a reference to the page pool to use
        PAGE_POOL_CONCEPT *m_page_pool{};
        /// @brief stores the next vps_t in the vp_pool_t linked list
        vps_t *m_next{};
        /// @brief stores the ID associated with this vps_t
        bsl::safe_uint16 m_id{bsl::safe_uint16::zero(true)};
        /// @brief stores the ID of the VP this vps_t is assigned to
        bsl::safe_uint16 m_assigned_vpid{bsl::safe_uint16::zero(true)};

        /// @brief stores a pointer to the guest VMCB being managed by this VPS
        vmcb_t *m_guest_vmcb{};
        /// @brief stores the physical address of the guest VMCB
        bsl::safe_uintmax m_guest_vmcb_phys{bsl::safe_uintmax::zero(true)};
        /// @brief stores a pointer to the host VMCB being managed by this VPS
        vmcb_t *m_host_vmcb{};
        /// @brief stores the physical address of the host VMCB
        bsl::safe_uintmax m_host_vmcb_phys{bsl::safe_uintmax::zero(true)};

        /// <!-- description -->
        ///   @brief Dumps the contents of a field
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T the type of field to dump
        ///   @param str the name of the field
        ///   @param val the field to dump
        ///
        template<typename T>
        constexpr void
        dump(bsl::string_view const &str, bsl::safe_integral<T> const &val) const &noexcept
        {
            auto const *rowcolor{bsl::rst};

            if (val.is_zero()) {
                rowcolor = bsl::blk;
            }
            else {
                bsl::touch();
            }

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<30s", str};
            bsl::print() << bsl::ylw << "| ";

            if constexpr (bsl::is_same<T, bsl::uint8>::value) {
                bsl::print() << rowcolor << "       " << bsl::hex(val) << "        ";
            }

            if constexpr (bsl::is_same<T, bsl::uint16>::value) {
                bsl::print() << rowcolor << "      " << bsl::hex(val) << "       ";
            }

            if constexpr (bsl::is_same<T, bsl::uint32>::value) {
                bsl::print() << rowcolor << "    " << bsl::hex(val) << "     ";
            }

            if constexpr (bsl::is_same<T, bsl::uint64>::value) {
                bsl::print() << rowcolor << bsl::hex(val) << ' ';
            }

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;
        }

    public:
        /// @brief an alias for INTRINSIC_CONCEPT
        using intrinsic_type = INTRINSIC_CONCEPT;
        /// @brief an alias for PAGE_POOL_CONCEPT
        using page_pool_type = PAGE_POOL_CONCEPT;

        /// <!-- description -->
        ///   @brief Default constructor
        ///
        constexpr vps_t() noexcept = default;

        /// <!-- description -->
        ///   @brief Initializes this vps_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param intrinsic the intrinsics to use
        ///   @param page_pool the page pool to use
        ///   @param i the ID for this vps_t
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        initialize(
            INTRINSIC_CONCEPT *const intrinsic,
            PAGE_POOL_CONCEPT *const page_pool,
            bsl::safe_uint16 const &i) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(m_id)) {
                bsl::error() << "vm_t already initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally release_on_error{[this]() noexcept -> void {
                this->release();
            }};

            m_intrinsic = intrinsic;
            if (bsl::unlikely(nullptr == m_intrinsic)) {
                bsl::error() << "invalid intrinsic\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_page_pool = page_pool;
            if (bsl::unlikely(nullptr == m_page_pool)) {
                bsl::error() << "invalid page_pool\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!i)) {
                bsl::error() << "invalid id\n" << bsl::here();
                return bsl::errc_failure;
            }

            release_on_error.ignore();

            m_id = i;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vps_t
        ///
        constexpr void
        release() &noexcept
        {
            this->deallocate();

            m_id = bsl::safe_uint16::zero(true);
            m_next = {};
            m_page_pool = {};
            m_intrinsic = {};
        }

        /// <!-- description -->
        ///   @brief Destructor
        ///
        constexpr ~vps_t() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr vps_t(vps_t const &o) noexcept = delete;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///
        constexpr vps_t(vps_t &&o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vps_t const &o) &noexcept -> vps_t & = delete;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(vps_t &&o) &noexcept -> vps_t & = default;

        /// <!-- description -->
        ///   @brief Returns the ID of this vps_t
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of this vps_t
        ///
        [[nodiscard]] constexpr auto
        id() const &noexcept -> bsl::safe_uint16 const &
        {
            return m_id;
        }

        /// <!-- description -->
        ///   @brief Returns the next vps_t in the vps_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the next vps_t in the vps_pool_t linked list
        ///
        [[nodiscard]] constexpr auto
        next() const &noexcept -> vps_t *
        {
            return m_next;
        }

        /// <!-- description -->
        ///   @brief Sets the next vps_t in the vps_pool_t linked list
        ///
        /// <!-- inputs/outputs -->
        ///   @param val the next vps_t in the vps_pool_t linked list to set
        ///
        constexpr void
        set_next(vps_t *val) &noexcept
        {
            m_next = val;
        }

        /// <!-- description -->
        ///   @brief Allocates this vps_t
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        allocate(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            bsl::discard(tls);

            if (bsl::unlikely(!m_id)) {
                bsl::error() << "vps_t not initialized\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(this->is_allocated())) {
                bsl::error() << "vps_t already allocated\n" << bsl::here();
                return bsl::errc_failure;
            }

            bsl::finally deallocate_on_error{[this]() noexcept -> void {
                this->deallocate();
            }};

            m_guest_vmcb = m_page_pool->template allocate<vmcb_t>(ALLOCATE_TAG_GUEST_VMCB);
            if (bsl::unlikely(nullptr == m_guest_vmcb)) {
                bsl::print() << bsl::here();
                return bsl::errc_failure;
            }

            m_guest_vmcb_phys = m_page_pool->virt_to_phys(m_guest_vmcb);
            if (bsl::unlikely(!m_guest_vmcb_phys)) {
                bsl::print() << bsl::here();
                return bsl::errc_failure;
            }

            m_host_vmcb = m_page_pool->template allocate<vmcb_t>(ALLOCATE_TAG_HOST_VMCB);
            if (bsl::unlikely(nullptr == m_host_vmcb)) {
                bsl::print() << bsl::here();
                return bsl::errc_failure;
            }

            m_host_vmcb_phys = m_page_pool->virt_to_phys(m_host_vmcb);
            if (bsl::unlikely(!m_host_vmcb_phys)) {
                bsl::print() << bsl::here();
                return bsl::errc_failure;
            }

            deallocate_on_error.ignore();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Deallocates this vps_t
        ///
        constexpr void
        deallocate() &noexcept
        {
            // m_vmexit_log_crsr = {};
            // for (auto const elem : m_vmexit_log) {
            //     *elem.data = {};
            // }

            m_host_vmcb_phys = bsl::safe_uintmax::zero(true);
            if (nullptr != m_page_pool) {
                m_page_pool->deallocate(m_host_vmcb, ALLOCATE_TAG_HOST_VMCB);
                m_host_vmcb = {};
            }
            else {
                bsl::touch();
            }

            m_guest_vmcb_phys = bsl::safe_uintmax::zero(true);
            if (nullptr != m_page_pool) {
                m_page_pool->deallocate(m_guest_vmcb, ALLOCATE_TAG_GUEST_VMCB);
                m_guest_vmcb = {};
            }
            else {
                bsl::touch();
            }

            m_assigned_vpid = bsl::safe_uint16::zero(true);
        }

        /// <!-- description -->
        ///   @brief Returns true if this vps_t is allocated, false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns true if this vps_t is allocated, false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_allocated() const &noexcept -> bool
        {
            return this == m_next;
        }

        /// <!-- description -->
        ///   @brief Assigns this vps_t to a VP
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpid the VP this vps_t is assigned to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        assign_vp(bsl::safe_uint16 const &vpid) &noexcept -> bsl::errc_type
        {
            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!vpid)) {
                bsl::error() << "invalid vpid\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_assigned_vpid = vpid;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the VP this vps_t is assigned to
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of the VP this vps_t is assigned to
        ///
        [[nodiscard]] constexpr auto
        assigned_vp() const &noexcept -> bsl::safe_uint16
        {
            return m_assigned_vpid;
        }

        /// <!-- description -->
        ///   @brief Stores the provided state in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param tls the current TLS block
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        state_save_to_vps(TLS_CONCEPT &tls, STATE_SAVE_CONCEPT const *const state) &noexcept
            -> bsl::errc_type
        {
            bsl::discard(tls);

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(nullptr == state)) {
                bsl::error() << "invalid state\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RAX, state->rax);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RBX, state->rbx);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RCX, state->rcx);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RDX, state->rdx);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RBP, state->rbp);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RSI, state->rsi);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RDI, state->rdi);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R8, state->r8);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R9, state->r9);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R10, state->r10);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R11, state->r11);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R12, state->r12);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R13, state->r13);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R14, state->r14);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R15, state->r15);

            m_guest_vmcb->rsp = state->rsp;
            m_guest_vmcb->rip = state->rip;

            m_guest_vmcb->rflags = state->rflags;

            m_guest_vmcb->gdtr_limit = bsl::to_u32(state->gdtr.limit).get();
            m_guest_vmcb->gdtr_base = bsl::to_umax(state->gdtr.base).get();
            m_guest_vmcb->idtr_limit = bsl::to_u32(state->idtr.limit).get();
            m_guest_vmcb->idtr_base = bsl::to_umax(state->idtr.base).get();

            m_guest_vmcb->es_selector = state->es_selector;
            m_guest_vmcb->es_attrib = compress_attrib(state->es_attrib).get();
            m_guest_vmcb->es_limit = state->es_limit;
            m_guest_vmcb->es_base = state->es_base;

            m_guest_vmcb->cs_selector = state->cs_selector;
            m_guest_vmcb->cs_attrib = compress_attrib(state->cs_attrib).get();
            m_guest_vmcb->cs_limit = state->cs_limit;
            m_guest_vmcb->cs_base = state->cs_base;

            m_guest_vmcb->ss_selector = state->ss_selector;
            m_guest_vmcb->ss_attrib = compress_attrib(state->ss_attrib).get();
            m_guest_vmcb->ss_limit = state->ss_limit;
            m_guest_vmcb->ss_base = state->ss_base;

            m_guest_vmcb->ds_selector = state->ds_selector;
            m_guest_vmcb->ds_attrib = compress_attrib(state->ds_attrib).get();
            m_guest_vmcb->ds_limit = state->ds_limit;
            m_guest_vmcb->ds_base = state->ds_base;

            m_guest_vmcb->fs_selector = state->fs_selector;
            m_guest_vmcb->fs_attrib = compress_attrib(state->fs_attrib).get();
            m_guest_vmcb->fs_limit = state->fs_limit;

            m_guest_vmcb->gs_selector = state->gs_selector;
            m_guest_vmcb->gs_attrib = compress_attrib(state->gs_attrib).get();
            m_guest_vmcb->gs_limit = state->gs_limit;

            m_guest_vmcb->ldtr_selector = state->ldtr_selector;
            m_guest_vmcb->ldtr_attrib = compress_attrib(state->ldtr_attrib).get();
            m_guest_vmcb->ldtr_limit = state->ldtr_limit;
            m_guest_vmcb->ldtr_base = state->ldtr_base;

            m_guest_vmcb->tr_selector = state->tr_selector;
            m_guest_vmcb->tr_attrib = compress_attrib(state->tr_attrib).get();
            m_guest_vmcb->tr_limit = state->tr_limit;
            m_guest_vmcb->tr_base = state->tr_base;

            m_guest_vmcb->cr0 = state->cr0;
            m_guest_vmcb->cr2 = state->cr2;
            m_guest_vmcb->cr3 = state->cr3;
            m_guest_vmcb->cr4 = state->cr4;

            m_guest_vmcb->dr6 = state->dr6;
            m_guest_vmcb->dr7 = state->dr7;

            m_guest_vmcb->efer = state->ia32_efer;
            m_guest_vmcb->star = state->ia32_star;
            m_guest_vmcb->lstar = state->ia32_lstar;
            m_guest_vmcb->cstar = state->ia32_cstar;
            m_guest_vmcb->sfmask = state->ia32_fmask;
            m_guest_vmcb->fs_base = state->ia32_fs_base;
            m_guest_vmcb->gs_base = state->ia32_gs_base;
            m_guest_vmcb->kernel_gs_base = state->ia32_kernel_gs_base;
            m_guest_vmcb->sysenter_cs = state->ia32_sysenter_cs;
            m_guest_vmcb->sysenter_esp = state->ia32_sysenter_esp;
            m_guest_vmcb->sysenter_eip = state->ia32_sysenter_eip;
            m_guest_vmcb->g_pat = state->ia32_pat;
            m_guest_vmcb->dbgctl = state->ia32_debugctl;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the VPS state in the provided state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param tls the current TLS block
        ///   @param state the state save to store the VPS state to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT, typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        vps_to_state_save(TLS_CONCEPT &tls, STATE_SAVE_CONCEPT *const state) &noexcept
            -> bsl::errc_type
        {
            bsl::discard(tls);

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(nullptr == state)) {
                bsl::error() << "invalid state\n" << bsl::here();
                return bsl::errc_failure;
            }

            state->rax = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RAX).get();
            state->rbx = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBX).get();
            state->rcx = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RCX).get();
            state->rdx = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDX).get();
            state->rbp = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBP).get();
            state->rsi = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RSI).get();
            state->rdi = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDI).get();
            state->r8 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R8).get();
            state->r9 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R9).get();
            state->r10 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R10).get();
            state->r11 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R11).get();
            state->r12 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R12).get();
            state->r13 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R13).get();
            state->r14 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R14).get();
            state->r15 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R15).get();

            state->rsp = m_guest_vmcb->rsp;
            state->rip = m_guest_vmcb->rip;

            state->rflags = m_guest_vmcb->rflags;

            state->gdtr.limit = bsl::to_u16(m_guest_vmcb->gdtr_limit).get();
            state->gdtr.base = bsl::to_ptr<bsl::uint64 *>(m_guest_vmcb->gdtr_base);
            state->idtr.limit = bsl::to_u16(m_guest_vmcb->idtr_limit).get();
            state->idtr.base = bsl::to_ptr<bsl::uint64 *>(m_guest_vmcb->idtr_base);

            state->es_selector = m_guest_vmcb->es_selector;
            state->es_attrib = decompress_attrib(m_guest_vmcb->es_attrib).get();
            state->es_limit = m_guest_vmcb->es_limit;
            state->es_base = m_guest_vmcb->es_base;

            state->cs_selector = m_guest_vmcb->cs_selector;
            state->cs_attrib = decompress_attrib(m_guest_vmcb->cs_attrib).get();
            state->cs_limit = m_guest_vmcb->cs_limit;
            state->cs_base = m_guest_vmcb->cs_base;

            state->ss_selector = m_guest_vmcb->ss_selector;
            state->ss_attrib = decompress_attrib(m_guest_vmcb->ss_attrib).get();
            state->ss_limit = m_guest_vmcb->ss_limit;
            state->ss_base = m_guest_vmcb->ss_base;

            state->ds_selector = m_guest_vmcb->ds_selector;
            state->ds_attrib = decompress_attrib(m_guest_vmcb->ds_attrib).get();
            state->ds_limit = m_guest_vmcb->ds_limit;
            state->ds_base = m_guest_vmcb->ds_base;

            state->fs_selector = m_guest_vmcb->fs_selector;
            state->fs_attrib = decompress_attrib(m_guest_vmcb->fs_attrib).get();
            state->fs_limit = m_guest_vmcb->fs_limit;

            state->gs_selector = m_guest_vmcb->gs_selector;
            state->gs_attrib = decompress_attrib(m_guest_vmcb->gs_attrib).get();
            state->gs_limit = m_guest_vmcb->gs_limit;

            state->ldtr_selector = m_guest_vmcb->ldtr_selector;
            state->ldtr_attrib = decompress_attrib(m_guest_vmcb->ldtr_attrib).get();
            state->ldtr_limit = m_guest_vmcb->ldtr_limit;
            state->ldtr_base = m_guest_vmcb->ldtr_base;

            state->tr_selector = m_guest_vmcb->tr_selector;
            state->tr_attrib = decompress_attrib(m_guest_vmcb->tr_attrib).get();
            state->tr_limit = m_guest_vmcb->tr_limit;
            state->tr_base = m_guest_vmcb->tr_base;

            state->cr0 = m_guest_vmcb->cr0;
            state->cr2 = m_guest_vmcb->cr2;
            state->cr3 = m_guest_vmcb->cr3;
            state->cr4 = m_guest_vmcb->cr4;

            state->dr6 = m_guest_vmcb->dr6;
            state->dr7 = m_guest_vmcb->dr7;

            state->ia32_efer = m_guest_vmcb->efer;
            state->ia32_star = m_guest_vmcb->star;
            state->ia32_lstar = m_guest_vmcb->lstar;
            state->ia32_cstar = m_guest_vmcb->cstar;
            state->ia32_fmask = m_guest_vmcb->sfmask;
            state->ia32_fs_base = m_guest_vmcb->fs_base;
            state->ia32_gs_base = m_guest_vmcb->gs_base;
            state->ia32_kernel_gs_base = m_guest_vmcb->kernel_gs_base;
            state->ia32_sysenter_cs = m_guest_vmcb->sysenter_cs;
            state->ia32_sysenter_esp = m_guest_vmcb->sysenter_esp;
            state->ia32_sysenter_eip = m_guest_vmcb->sysenter_eip;
            state->ia32_pat = m_guest_vmcb->g_pat;
            state->ia32_debugctl = m_guest_vmcb->dbgctl;

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Reads a field from the VPS given the index of
        ///     the field to read.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam FIELD_TYPE the type (i.e., size) of field to read
        ///   @param tls the current TLS block
        ///   @param index the index of the field to read from the VPS
        ///   @return Returns the value of the requested field from the
        ///     VPS or bsl::safe_integral<FIELD_TYPE>::zero(true)
        ///     on failure.
        ///
        template<typename FIELD_TYPE, typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        read(TLS_CONCEPT &tls, bsl::safe_uintmax const &index) &noexcept
            -> bsl::safe_integral<FIELD_TYPE>
        {
            bsl::discard(tls);

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::safe_integral<FIELD_TYPE>::zero(true);
            }

            auto const view{bsl::as_t<FIELD_TYPE>(m_guest_vmcb, sizeof(vmcb_t))};
            auto const view_index{index / sizeof(FIELD_TYPE)};

            auto *const ptr{view.at_if(view_index)};
            if (bsl::unlikely(nullptr == ptr)) {
                bsl::error() << "invalid index: "    // --
                             << bsl::hex(index)      // --
                             << bsl::endl            // --
                             << bsl::here();         // --

                return bsl::safe_integral<FIELD_TYPE>::zero(true);
            }

            return *ptr;
        }

        /// <!-- description -->
        ///   @brief Writes a field to the VPS given the index of
        ///     the field and the value to write.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam FIELD_TYPE the type (i.e., size) of field to write
        ///   @param tls the current TLS block
        ///   @param index the index of the field to write to the VPS
        ///   @param value the value to write to the VPS
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename FIELD_TYPE, typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        write(
            TLS_CONCEPT &tls,
            bsl::safe_uintmax const &index,
            bsl::safe_integral<FIELD_TYPE> const &value) &noexcept -> bsl::errc_type
        {
            bsl::discard(tls);

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!value)) {
                bsl::error() << "invalid val: "    // --
                             << bsl::hex(value)    // --
                             << bsl::endl          // --
                             << bsl::here();       // --

                return bsl::errc_failure;
            }

            auto view{bsl::as_writable_t<FIELD_TYPE>(m_guest_vmcb, sizeof(vmcb_t))};
            auto const view_index{index / sizeof(FIELD_TYPE)};

            auto *const ptr{view.at_if(view_index)};
            if (bsl::unlikely(nullptr == ptr)) {
                bsl::error() << "invalid index: "    // --
                             << bsl::hex(index)      // --
                             << bsl::endl            // --
                             << bsl::here();         // --

                return bsl::errc_failure;
            }

            *ptr = value.get();
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Reads a field from the VPS given a bf_reg_t
        ///     defining the field to read.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param reg a bf_reg_t defining the field to read from the VPS
        ///   @return Returns the value of the requested field from the
        ///     VPS or bsl::safe_uintmax::zero(true) on failure.
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        read_reg(TLS_CONCEPT &tls, syscall::bf_reg_t const reg) &noexcept -> bsl::safe_uintmax
        {
            bsl::discard(tls);

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::safe_uintmax::zero(true);
            }

            switch (reg) {
                case syscall::bf_reg_t::bf_reg_t_rax: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RAX);
                }

                case syscall::bf_reg_t::bf_reg_t_rbx: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBX);
                }

                case syscall::bf_reg_t::bf_reg_t_rcx: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RCX);
                }

                case syscall::bf_reg_t::bf_reg_t_rdx: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDX);
                }

                case syscall::bf_reg_t::bf_reg_t_rbp: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBP);
                }

                case syscall::bf_reg_t::bf_reg_t_rsi: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RSI);
                }

                case syscall::bf_reg_t::bf_reg_t_rdi: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDI);
                }

                case syscall::bf_reg_t::bf_reg_t_r8: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R8);
                }

                case syscall::bf_reg_t::bf_reg_t_r9: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R9);
                }

                case syscall::bf_reg_t::bf_reg_t_r10: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R10);
                }

                case syscall::bf_reg_t::bf_reg_t_r11: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R11);
                }

                case syscall::bf_reg_t::bf_reg_t_r12: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R12);
                }

                case syscall::bf_reg_t::bf_reg_t_r13: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R13);
                }

                case syscall::bf_reg_t::bf_reg_t_r14: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R14);
                }

                case syscall::bf_reg_t::bf_reg_t_r15: {
                    return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R15);
                }

                case syscall::bf_reg_t::bf_reg_t_rsp: {
                    return m_guest_vmcb->rsp;
                }

                case syscall::bf_reg_t::bf_reg_t_rip: {
                    return m_guest_vmcb->rip;
                }

                case syscall::bf_reg_t::bf_reg_t_rflags: {
                    return m_guest_vmcb->rflags;
                }

                case syscall::bf_reg_t::bf_reg_t_gdtr_base_addr: {
                    return m_guest_vmcb->gdtr_base;
                }

                case syscall::bf_reg_t::bf_reg_t_gdtr_limit: {
                    return bsl::to_umax(m_guest_vmcb->gdtr_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_idtr_base_addr: {
                    return m_guest_vmcb->idtr_base;
                }

                case syscall::bf_reg_t::bf_reg_t_idtr_limit: {
                    return bsl::to_umax(m_guest_vmcb->idtr_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_es: {
                    return bsl::to_umax(m_guest_vmcb->es_selector);
                }

                case syscall::bf_reg_t::bf_reg_t_es_base_addr: {
                    return m_guest_vmcb->es_base;
                }

                case syscall::bf_reg_t::bf_reg_t_es_limit: {
                    return bsl::to_umax(m_guest_vmcb->es_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_es_attributes: {
                    return bsl::to_umax(m_guest_vmcb->es_attrib);
                }

                case syscall::bf_reg_t::bf_reg_t_cs: {
                    return bsl::to_umax(m_guest_vmcb->cs_selector);
                }

                case syscall::bf_reg_t::bf_reg_t_cs_base_addr: {
                    return m_guest_vmcb->cs_base;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_limit: {
                    return bsl::to_umax(m_guest_vmcb->cs_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_cs_attributes: {
                    return bsl::to_umax(m_guest_vmcb->cs_attrib);
                }

                case syscall::bf_reg_t::bf_reg_t_ss: {
                    return bsl::to_umax(m_guest_vmcb->ss_selector);
                }

                case syscall::bf_reg_t::bf_reg_t_ss_base_addr: {
                    return m_guest_vmcb->ss_base;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_limit: {
                    return bsl::to_umax(m_guest_vmcb->ss_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_ss_attributes: {
                    return bsl::to_umax(m_guest_vmcb->ss_attrib);
                }

                case syscall::bf_reg_t::bf_reg_t_ds: {
                    return bsl::to_umax(m_guest_vmcb->ds_selector);
                }

                case syscall::bf_reg_t::bf_reg_t_ds_base_addr: {
                    return m_guest_vmcb->ds_base;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_limit: {
                    return bsl::to_umax(m_guest_vmcb->ds_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_ds_attributes: {
                    return bsl::to_umax(m_guest_vmcb->ds_attrib);
                }

                case syscall::bf_reg_t::bf_reg_t_fs: {
                    return bsl::to_umax(m_guest_vmcb->fs_selector);
                }

                case syscall::bf_reg_t::bf_reg_t_fs_base_addr: {
                    return m_guest_vmcb->fs_base;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_limit: {
                    return bsl::to_umax(m_guest_vmcb->fs_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_fs_attributes: {
                    return bsl::to_umax(m_guest_vmcb->fs_attrib);
                }

                case syscall::bf_reg_t::bf_reg_t_gs: {
                    return bsl::to_umax(m_guest_vmcb->gs_selector);
                }

                case syscall::bf_reg_t::bf_reg_t_gs_base_addr: {
                    return m_guest_vmcb->gs_base;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_limit: {
                    return bsl::to_umax(m_guest_vmcb->gs_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_gs_attributes: {
                    return bsl::to_umax(m_guest_vmcb->gs_attrib);
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr: {
                    return bsl::to_umax(m_guest_vmcb->ldtr_selector);
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_base_addr: {
                    return m_guest_vmcb->ldtr_base;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_limit: {
                    return bsl::to_umax(m_guest_vmcb->ldtr_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_attributes: {
                    return bsl::to_umax(m_guest_vmcb->ldtr_attrib);
                }

                case syscall::bf_reg_t::bf_reg_t_tr: {
                    return bsl::to_umax(m_guest_vmcb->tr_selector);
                }

                case syscall::bf_reg_t::bf_reg_t_tr_base_addr: {
                    return m_guest_vmcb->tr_base;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_limit: {
                    return bsl::to_umax(m_guest_vmcb->tr_limit);
                }

                case syscall::bf_reg_t::bf_reg_t_tr_attributes: {
                    return bsl::to_umax(m_guest_vmcb->tr_attrib);
                }

                case syscall::bf_reg_t::bf_reg_t_cr0: {
                    return m_guest_vmcb->cr0;
                }

                case syscall::bf_reg_t::bf_reg_t_cr2: {
                    return m_guest_vmcb->cr2;
                }

                case syscall::bf_reg_t::bf_reg_t_cr3: {
                    return m_guest_vmcb->cr3;
                }

                case syscall::bf_reg_t::bf_reg_t_cr4: {
                    return m_guest_vmcb->cr4;
                }

                case syscall::bf_reg_t::bf_reg_t_dr6: {
                    return m_guest_vmcb->dr6;
                }

                case syscall::bf_reg_t::bf_reg_t_dr7: {
                    return m_guest_vmcb->dr7;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_efer: {
                    return m_guest_vmcb->efer;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_star: {
                    return m_guest_vmcb->star;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_lstar: {
                    return m_guest_vmcb->lstar;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_cstar: {
                    return m_guest_vmcb->cstar;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_fmask: {
                    return m_guest_vmcb->sfmask;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_fs_base: {
                    return m_guest_vmcb->fs_base;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_gs_base: {
                    return m_guest_vmcb->gs_base;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_kernel_gs_base: {
                    return m_guest_vmcb->kernel_gs_base;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_cs: {
                    return m_guest_vmcb->sysenter_cs;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_esp: {
                    return m_guest_vmcb->sysenter_esp;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_eip: {
                    return m_guest_vmcb->sysenter_eip;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_pat: {
                    return m_guest_vmcb->g_pat;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_debugctl: {
                    return m_guest_vmcb->dbgctl;
                }

                default: {
                    bsl::error() << "unknown by bf_reg_t\n" << bsl::here();
                    break;
                }
            }

            return bsl::safe_uintmax::zero(true);
        }

        /// <!-- description -->
        ///   @brief Writes a field to the VPS given a bf_reg_t
        ///     defining the field and a value to write.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param reg a bf_reg_t defining the field to write to the VPS
        ///   @param val the value to write to the VPS
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        write_reg(
            TLS_CONCEPT &tls, syscall::bf_reg_t const reg, bsl::safe_uintmax const &val) &noexcept
            -> bsl::errc_type
        {
            bsl::discard(tls);

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!val)) {
                bsl::error() << "invalid val: "    // --
                             << bsl::hex(val)      // --
                             << bsl::endl          // --
                             << bsl::here();       // --

                return bsl::errc_failure;
            }

            switch (reg) {
                case syscall::bf_reg_t::bf_reg_t_rax: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RAX, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rbx: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RBX, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rcx: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RCX, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rdx: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RDX, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rbp: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RBP, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rsi: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RSI, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rdi: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RDI, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r8: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R8, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r9: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R9, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r10: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R10, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r11: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R11, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r12: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R12, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r13: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R13, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r14: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R14, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r15: {
                    m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R15, val);
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rsp: {
                    m_guest_vmcb->rsp = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rip: {
                    m_guest_vmcb->rip = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rflags: {
                    m_guest_vmcb->rflags = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_gdtr_base_addr: {
                    m_guest_vmcb->gdtr_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_gdtr_limit: {
                    m_guest_vmcb->gdtr_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_idtr_base_addr: {
                    m_guest_vmcb->idtr_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_idtr_limit: {
                    m_guest_vmcb->idtr_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_es: {
                    m_guest_vmcb->es_selector = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_es_base_addr: {
                    m_guest_vmcb->es_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_es_limit: {
                    m_guest_vmcb->es_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_es_attributes: {
                    m_guest_vmcb->es_attrib = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_cs: {
                    m_guest_vmcb->cs_selector = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_base_addr: {
                    m_guest_vmcb->cs_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_limit: {
                    m_guest_vmcb->cs_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_attributes: {
                    m_guest_vmcb->cs_attrib = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ss: {
                    m_guest_vmcb->ss_selector = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_base_addr: {
                    m_guest_vmcb->ss_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_limit: {
                    m_guest_vmcb->ss_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_attributes: {
                    m_guest_vmcb->ss_attrib = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ds: {
                    m_guest_vmcb->ds_selector = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_base_addr: {
                    m_guest_vmcb->ds_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_limit: {
                    m_guest_vmcb->ds_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_attributes: {
                    m_guest_vmcb->ds_attrib = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_fs: {
                    m_guest_vmcb->fs_selector = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_base_addr: {
                    m_guest_vmcb->fs_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_limit: {
                    m_guest_vmcb->fs_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_attributes: {
                    m_guest_vmcb->fs_attrib = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_gs: {
                    m_guest_vmcb->gs_selector = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_base_addr: {
                    m_guest_vmcb->gs_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_limit: {
                    m_guest_vmcb->gs_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_attributes: {
                    m_guest_vmcb->gs_attrib = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr: {
                    m_guest_vmcb->ldtr_selector = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_base_addr: {
                    m_guest_vmcb->ldtr_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_limit: {
                    m_guest_vmcb->ldtr_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_attributes: {
                    m_guest_vmcb->ldtr_attrib = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_tr: {
                    m_guest_vmcb->tr_selector = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_base_addr: {
                    m_guest_vmcb->tr_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_limit: {
                    m_guest_vmcb->tr_limit = bsl::to_u32(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_attributes: {
                    m_guest_vmcb->tr_attrib = bsl::to_u16(val).get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_cr0: {
                    m_guest_vmcb->cr0 = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_cr2: {
                    m_guest_vmcb->cr2 = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_cr3: {
                    m_guest_vmcb->cr3 = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_cr4: {
                    m_guest_vmcb->cr4 = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_dr6: {
                    m_guest_vmcb->dr6 = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_dr7: {
                    m_guest_vmcb->dr7 = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_efer: {
                    m_guest_vmcb->efer = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_star: {
                    m_guest_vmcb->star = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_lstar: {
                    m_guest_vmcb->lstar = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_cstar: {
                    m_guest_vmcb->cstar = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_fmask: {
                    m_guest_vmcb->sfmask = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_fs_base: {
                    m_guest_vmcb->fs_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_gs_base: {
                    m_guest_vmcb->gs_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_kernel_gs_base: {
                    m_guest_vmcb->kernel_gs_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_cs: {
                    m_guest_vmcb->sysenter_cs = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_esp: {
                    m_guest_vmcb->sysenter_esp = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_eip: {
                    m_guest_vmcb->sysenter_eip = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_pat: {
                    m_guest_vmcb->g_pat = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_debugctl: {
                    m_guest_vmcb->dbgctl = val.get();
                    return bsl::errc_success;
                }

                default: {
                    bsl::error() << "unknown by bf_reg_t\n" << bsl::here();
                    break;
                }
            }

            return bsl::errc_failure;
        }

        /// <!-- description -->
        ///   @brief Runs the VPS. Note that this function does not
        ///     return until a VMExit occurs. Once complete, this function
        ///     will return the VMExit reason.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns the VMExit reason on success, or
        ///     bsl::safe_uintmax::zero(true) on failure.
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        run(TLS_CONCEPT &tls) &noexcept -> bsl::safe_uintmax
        {
            constexpr bsl::safe_uintmax invalid_exit_reason{bsl::to_umax(0xFFFFFFFFFFFFFFFFU)};

            if constexpr (!BSL_RELEASE_BUILD) {
                if (bsl::unlikely(!this->is_allocated())) {
                    bsl::error() << "invalid vps\n" << bsl::here();
                    return bsl::safe_uintmax::zero(true);
                }
            }

            bsl::safe_uintmax const exit_reason{intrinsic_vmrun(
                m_guest_vmcb, m_guest_vmcb_phys.get(), m_host_vmcb, m_host_vmcb_phys.get())};

            if (invalid_exit_reason == exit_reason) {
                this->dump(tls);

                bsl::error() << "vmrun failed\n" << bsl::here();
                return bsl::safe_uintmax::zero(true);
            }

            if constexpr (!BSL_RELEASE_BUILD) {
                if constexpr (!(BSL_DEBUG_LEVEL < bsl::VV)) {
                    log.add(
                        tls.ppid,
                        {tls.active_vmid,
                         tls.active_vpid,
                         tls.active_vpsid,
                         exit_reason,
                         m_guest_vmcb->exitinfo1,
                         m_guest_vmcb->exitinfo2,
                         m_guest_vmcb->exitininfo,
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_RAX),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBX),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_RCX),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDX),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBP),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_RSI),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDI),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_R8),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_R9),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_R10),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_R11),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_R12),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_R13),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_R14),
                         m_intrinsic->tls_reg(syscall::TLS_OFFSET_R15),
                         m_guest_vmcb->rsp,
                         m_guest_vmcb->rip});
                }
            }

            /// TODO:
            /// - Add check logic to if an entry failure occurs and output
            ///   what the error was and why.
            ///

            return exit_reason;
        }

        /// <!-- description -->
        ///   @brief Advance the IP of the VPS
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        advance_ip(TLS_CONCEPT &tls) &noexcept -> bsl::errc_type
        {
            bsl::discard(tls);

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_guest_vmcb->rip = m_guest_vmcb->nrip;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Clears the VPS's internal cache. Note that this is a
        ///     hardware specific function and doesn't change the actual
        ///     values stored in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        [[nodiscard]] constexpr auto
        clear() &noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            m_guest_vmcb->vmcb_clean_bits = bsl::ZERO_U32.get();
            return ret;
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

            // clang-format off

            constexpr auto guest_instruction_bytes_0{bsl::to_umax(0x0U)};
            constexpr auto guest_instruction_bytes_1{bsl::to_umax(0x1U)};
            constexpr auto guest_instruction_bytes_2{bsl::to_umax(0x2U)};
            constexpr auto guest_instruction_bytes_3{bsl::to_umax(0x3U)};
            constexpr auto guest_instruction_bytes_4{bsl::to_umax(0x4U)};
            constexpr auto guest_instruction_bytes_5{bsl::to_umax(0x5U)};
            constexpr auto guest_instruction_bytes_6{bsl::to_umax(0x6U)};
            constexpr auto guest_instruction_bytes_7{bsl::to_umax(0x7U)};
            constexpr auto guest_instruction_bytes_8{bsl::to_umax(0x8U)};
            constexpr auto guest_instruction_bytes_9{bsl::to_umax(0x9U)};
            constexpr auto guest_instruction_bytes_a{bsl::to_umax(0xAU)};
            /// NOLINTNEXTLINE(bsl-identifier-typographically-unambiguous)
            constexpr auto guest_instruction_bytes_b{bsl::to_umax(0xBU)};
            constexpr auto guest_instruction_bytes_c{bsl::to_umax(0xCU)};
            constexpr auto guest_instruction_bytes_d{bsl::to_umax(0xDU)};
            constexpr auto guest_instruction_bytes_e{bsl::to_umax(0xEU)};

            if (bsl::unlikely(!m_id)) {
                bsl::print() << "[error]" << bsl::endl;
                return;
            }

            bsl::print() << bsl::mag << "vps [";
            bsl::print() << bsl::rst << bsl::hex(m_id);
            bsl::print() << bsl::mag << "] dump: ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Header
            ///

            bsl::print() << bsl::ylw << "+----------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^30s", "description "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^19s", "value "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+----------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            /// Allocated
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<30s", "allocated "};
            bsl::print() << bsl::ylw << "| ";
            if (this->is_allocated()) {
                bsl::print() << bsl::grn << bsl::fmt{"^19s", "yes "};
            }
            else {
                bsl::print() << bsl::red << bsl::fmt{"^19s", "no "};
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Assigned VM
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<30s", "assigned vp "};
            bsl::print() << bsl::ylw << "| ";
            if (m_assigned_vpid) {
                bsl::print() << bsl::grn << "      " << bsl::hex(m_assigned_vpid) << "       ";
            }
            else {
                bsl::print() << bsl::red << bsl::fmt{"^19s", "unassigned "};
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Guest Missing Fields
            ///

            bsl::print() << bsl::ylw << "+----------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            if (!this->is_allocated()) {
                return;
            }

            this->dump("rax ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_RAX));
            this->dump("rbx ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBX));
            this->dump("rcx ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_RCX));
            this->dump("rdx ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDX));
            this->dump("rbp ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBP));
            this->dump("rsi ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_RSI));
            this->dump("rdi ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDI));
            this->dump("r8 ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_R8));
            this->dump("r9 ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_R9));
            this->dump("r10 ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_R10));
            this->dump("r11 ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_R11));
            this->dump("r12 ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_R12));
            this->dump("r13 ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_R13));
            this->dump("r14 ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_R14));
            this->dump("r15 ", m_intrinsic->tls_reg(syscall::TLS_OFFSET_R15));

            /// Guest Control Area Fields
            ///

            bsl::print() << bsl::ylw << "+----------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("intercept_cr_read ", bsl::make_safe(m_guest_vmcb->intercept_cr_read));
            this->dump("intercept_cr_write ", bsl::make_safe(m_guest_vmcb->intercept_cr_write));
            this->dump("intercept_dr_read ", bsl::make_safe(m_guest_vmcb->intercept_dr_read));
            this->dump("intercept_dr_write ", bsl::make_safe(m_guest_vmcb->intercept_dr_write));
            this->dump("intercept_exception ", bsl::make_safe(m_guest_vmcb->intercept_exception));
            this->dump("intercept_instruction1 ", bsl::make_safe(m_guest_vmcb->intercept_instruction1));
            this->dump("intercept_instruction2 ", bsl::make_safe(m_guest_vmcb->intercept_instruction2));
            this->dump("intercept_instruction3 ", bsl::make_safe(m_guest_vmcb->intercept_instruction3));
            this->dump("pause_filter_threshold ", bsl::make_safe(m_guest_vmcb->pause_filter_threshold));
            this->dump("pause_filter_count ", bsl::make_safe(m_guest_vmcb->pause_filter_count));
            this->dump("iopm_base_pa ", bsl::make_safe(m_guest_vmcb->iopm_base_pa));
            this->dump("msrpm_base_pa ", bsl::make_safe(m_guest_vmcb->msrpm_base_pa));
            this->dump("tsc_offset ", bsl::make_safe(m_guest_vmcb->tsc_offset));
            this->dump("guest_asid ", bsl::make_safe(m_guest_vmcb->guest_asid));
            this->dump("tlb_control ", bsl::make_safe(m_guest_vmcb->tlb_control));
            this->dump("virtual_interrupt_a ", bsl::make_safe(m_guest_vmcb->virtual_interrupt_a));
            this->dump("virtual_interrupt_b ", bsl::make_safe(m_guest_vmcb->virtual_interrupt_b));
            this->dump("exitcode ", bsl::make_safe(m_guest_vmcb->exitcode));
            this->dump("exitinfo1 ", bsl::make_safe(m_guest_vmcb->exitinfo1));
            this->dump("exitinfo2 ", bsl::make_safe(m_guest_vmcb->exitinfo2));
            this->dump("exitininfo ", bsl::make_safe(m_guest_vmcb->exitininfo));
            this->dump("ctls1 ", bsl::make_safe(m_guest_vmcb->ctls1));
            this->dump("avic_apic_bar ", bsl::make_safe(m_guest_vmcb->avic_apic_bar));
            this->dump("guest_pa_of_ghcb ", bsl::make_safe(m_guest_vmcb->guest_pa_of_ghcb));
            this->dump("eventinj ", bsl::make_safe(m_guest_vmcb->eventinj));
            this->dump("n_cr3 ", bsl::make_safe(m_guest_vmcb->n_cr3));
            this->dump("ctls2 ", bsl::make_safe(m_guest_vmcb->ctls2));
            this->dump("vmcb_clean_bits ", bsl::make_safe(m_guest_vmcb->vmcb_clean_bits));
            this->dump("nrip ", bsl::make_safe(m_guest_vmcb->nrip));
            this->dump("number_of_bytes_fetched ", bsl::make_safe(m_guest_vmcb->number_of_bytes_fetched));

            auto const &gib{m_guest_vmcb->guest_instruction_bytes};
            this->dump("guest_instruction_bytes[0]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_0)));
            this->dump("guest_instruction_bytes[1]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_1)));
            this->dump("guest_instruction_bytes[2]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_2)));
            this->dump("guest_instruction_bytes[3]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_3)));
            this->dump("guest_instruction_bytes[4]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_4)));
            this->dump("guest_instruction_bytes[5]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_5)));
            this->dump("guest_instruction_bytes[6]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_6)));
            this->dump("guest_instruction_bytes[7]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_7)));
            this->dump("guest_instruction_bytes[8]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_8)));
            this->dump("guest_instruction_bytes[9]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_9)));
            this->dump("guest_instruction_bytes[a]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_a)));
            this->dump("guest_instruction_bytes[b]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_b)));
            this->dump("guest_instruction_bytes[c]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_c)));
            this->dump("guest_instruction_bytes[d]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_d)));
            this->dump("guest_instruction_bytes[e]", bsl::make_safe(*gib.at_if(guest_instruction_bytes_e)));

            this->dump("avic_apic_backing_page_ptr ", bsl::make_safe(m_guest_vmcb->avic_apic_backing_page_ptr));
            this->dump("avic_logical_table_ptr ", bsl::make_safe(m_guest_vmcb->avic_logical_table_ptr));
            this->dump("avic_physical_table_ptr ", bsl::make_safe(m_guest_vmcb->avic_physical_table_ptr));
            this->dump("vmsa_ptr ", bsl::make_safe(m_guest_vmcb->vmsa_ptr));

            /// Guest State Save Area Fields
            ///

            bsl::print() << bsl::ylw << "+----------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("es_selector ", bsl::make_safe(m_guest_vmcb->es_selector));
            this->dump("es_attrib ", bsl::make_safe(m_guest_vmcb->es_attrib));
            this->dump("es_limit ", bsl::make_safe(m_guest_vmcb->es_limit));
            this->dump("es_base ", bsl::make_safe(m_guest_vmcb->es_base));
            this->dump("cs_selector ", bsl::make_safe(m_guest_vmcb->cs_selector));
            this->dump("cs_attrib ", bsl::make_safe(m_guest_vmcb->cs_attrib));
            this->dump("cs_limit ", bsl::make_safe(m_guest_vmcb->cs_limit));
            this->dump("cs_base ", bsl::make_safe(m_guest_vmcb->cs_base));
            this->dump("ss_selector ", bsl::make_safe(m_guest_vmcb->ss_selector));
            this->dump("ss_attrib ", bsl::make_safe(m_guest_vmcb->ss_attrib));
            this->dump("ss_limit ", bsl::make_safe(m_guest_vmcb->ss_limit));
            this->dump("ss_base ", bsl::make_safe(m_guest_vmcb->ss_base));
            this->dump("ds_selector ", bsl::make_safe(m_guest_vmcb->ds_selector));
            this->dump("ds_attrib ", bsl::make_safe(m_guest_vmcb->ds_attrib));
            this->dump("ds_limit ", bsl::make_safe(m_guest_vmcb->ds_limit));
            this->dump("ds_base ", bsl::make_safe(m_guest_vmcb->ds_base));
            this->dump("fs_selector ", bsl::make_safe(m_guest_vmcb->fs_selector));
            this->dump("fs_attrib ", bsl::make_safe(m_guest_vmcb->fs_attrib));
            this->dump("fs_limit ", bsl::make_safe(m_guest_vmcb->fs_limit));
            this->dump("fs_base ", bsl::make_safe(m_guest_vmcb->fs_base));
            this->dump("gs_selector ", bsl::make_safe(m_guest_vmcb->gs_selector));
            this->dump("gs_attrib ", bsl::make_safe(m_guest_vmcb->gs_attrib));
            this->dump("gs_limit ", bsl::make_safe(m_guest_vmcb->gs_limit));
            this->dump("gs_base ", bsl::make_safe(m_guest_vmcb->gs_base));
            this->dump("gdtr_selector ", bsl::make_safe(m_guest_vmcb->gdtr_selector));
            this->dump("gdtr_attrib ", bsl::make_safe(m_guest_vmcb->gdtr_attrib));
            this->dump("gdtr_limit ", bsl::make_safe(m_guest_vmcb->gdtr_limit));
            this->dump("gdtr_base ", bsl::make_safe(m_guest_vmcb->gdtr_base));
            this->dump("ldtr_selector ", bsl::make_safe(m_guest_vmcb->ldtr_selector));
            this->dump("ldtr_attrib ", bsl::make_safe(m_guest_vmcb->ldtr_attrib));
            this->dump("ldtr_limit ", bsl::make_safe(m_guest_vmcb->ldtr_limit));
            this->dump("ldtr_base ", bsl::make_safe(m_guest_vmcb->ldtr_base));
            this->dump("idtr_selector ", bsl::make_safe(m_guest_vmcb->idtr_selector));
            this->dump("idtr_attrib ", bsl::make_safe(m_guest_vmcb->idtr_attrib));
            this->dump("idtr_limit ", bsl::make_safe(m_guest_vmcb->idtr_limit));
            this->dump("idtr_base ", bsl::make_safe(m_guest_vmcb->idtr_base));
            this->dump("tr_selector ", bsl::make_safe(m_guest_vmcb->tr_selector));
            this->dump("tr_attrib ", bsl::make_safe(m_guest_vmcb->tr_attrib));
            this->dump("tr_limit ", bsl::make_safe(m_guest_vmcb->tr_limit));
            this->dump("tr_base ", bsl::make_safe(m_guest_vmcb->tr_base));
            this->dump("cpl ", bsl::make_safe(m_guest_vmcb->cpl));
            this->dump("efer ", bsl::make_safe(m_guest_vmcb->efer));
            this->dump("cr4 ", bsl::make_safe(m_guest_vmcb->cr4));
            this->dump("cr3 ", bsl::make_safe(m_guest_vmcb->cr3));
            this->dump("cr0 ", bsl::make_safe(m_guest_vmcb->cr0));
            this->dump("dr7 ", bsl::make_safe(m_guest_vmcb->dr7));
            this->dump("dr6 ", bsl::make_safe(m_guest_vmcb->dr6));
            this->dump("rflags ", bsl::make_safe(m_guest_vmcb->rflags));
            this->dump("rip ", bsl::make_safe(m_guest_vmcb->rip));
            this->dump("rsp ", bsl::make_safe(m_guest_vmcb->rsp));
            this->dump("rax ", bsl::make_safe(m_guest_vmcb->rax));
            this->dump("star ", bsl::make_safe(m_guest_vmcb->star));
            this->dump("lstar ", bsl::make_safe(m_guest_vmcb->lstar));
            this->dump("cstar ", bsl::make_safe(m_guest_vmcb->cstar));
            this->dump("sfmask ", bsl::make_safe(m_guest_vmcb->sfmask));
            this->dump("kernel_gs_base ", bsl::make_safe(m_guest_vmcb->kernel_gs_base));
            this->dump("sysenter_cs ", bsl::make_safe(m_guest_vmcb->sysenter_cs));
            this->dump("sysenter_esp ", bsl::make_safe(m_guest_vmcb->sysenter_esp));
            this->dump("sysenter_eip ", bsl::make_safe(m_guest_vmcb->sysenter_eip));
            this->dump("cr2 ", bsl::make_safe(m_guest_vmcb->cr2));
            this->dump("g_pat ", bsl::make_safe(m_guest_vmcb->g_pat));
            this->dump("dbgctl ", bsl::make_safe(m_guest_vmcb->dbgctl));
            this->dump("br_from ", bsl::make_safe(m_guest_vmcb->br_from));
            this->dump("br_to ", bsl::make_safe(m_guest_vmcb->br_to));
            this->dump("lastexcpfrom ", bsl::make_safe(m_guest_vmcb->lastexcpfrom));
            this->dump("lastexcpto ", bsl::make_safe(m_guest_vmcb->lastexcpto));

            /// Footer
            ///

            bsl::print() << bsl::ylw << "+----------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            // clang-format on
        }
    };
}

#endif
