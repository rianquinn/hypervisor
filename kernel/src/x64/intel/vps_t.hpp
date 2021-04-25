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
#include <general_purpose_regs_t.hpp>
#include <mk_interface.hpp>
#include <vmcs_missing_registers_t.hpp>
#include <vmcs_t.hpp>

#include <bsl/array.hpp>
#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/finally.hpp>
#include <bsl/is_same.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/string_view.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @brief entry point prototype
    extern "C" void intrinsic_vmexit(void) noexcept;

    /// @brief defines the IA32_VMX_BASIC MSR
    constexpr bsl::safe_uint32 IA32_VMX_BASIC{bsl::to_u32(0x480U)};
    /// @brief defines the IA32_PAT MSR
    constexpr bsl::safe_uint32 IA32_PAT{bsl::to_u32(0x277U)};
    /// @brief defines the IA32_SYSENTER_CS MSR
    constexpr bsl::safe_uint32 IA32_SYSENTER_CS{bsl::to_u32(0x174U)};
    /// @brief defines the IA32_SYSENTER_ESP MSR
    constexpr bsl::safe_uint32 IA32_SYSENTER_ESP{bsl::to_u32(0x175U)};
    /// @brief defines the IA32_SYSENTER_EIP MSR
    constexpr bsl::safe_uint32 IA32_SYSENTER_EIP{bsl::to_u32(0x176U)};
    /// @brief defines the IA32_EFER MSR
    constexpr bsl::safe_uint32 IA32_EFER{bsl::to_u32(0xC0000080U)};
    /// @brief defines the IA32_STAR MSR
    constexpr bsl::safe_uint32 IA32_STAR{bsl::to_u32(0xC0000081U)};
    /// @brief defines the IA32_LSTAR MSR
    constexpr bsl::safe_uint32 IA32_LSTAR{bsl::to_u32(0xC0000082U)};
    /// @brief defines the IA32_CSTAR MSR
    constexpr bsl::safe_uint32 IA32_CSTAR{bsl::to_u32(0xC0000083U)};
    /// @brief defines the IA32_FMASK MSR
    constexpr bsl::safe_uint32 IA32_FMASK{bsl::to_u32(0xC0000084U)};
    /// @brief defines the IA32_FS_BASE MSR
    constexpr bsl::safe_uint32 IA32_FS_BASE{bsl::to_u32(0xC0000100U)};
    /// @brief defines the IA32_GS_BASE MSR
    constexpr bsl::safe_uint32 IA32_GS_BASE{bsl::to_u32(0xC0000101U)};
    /// @brief defines the IA32_KERNEL_GS_BASE MSR
    constexpr bsl::safe_uint32 IA32_KERNEL_GS_BASE{bsl::to_u32(0xC0000102U)};

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
        bsl::safe_uint16 m_assigned_vpid{syscall::BF_INVALID_ID};
        /// @brief stores the ID of the PP this vps_t is assigned to
        bsl::safe_uint16 m_assigned_ppid{syscall::BF_INVALID_ID};

        /// @brief stores a pointer to the guest vmcs being managed by this VPS
        vmcs_t *m_vmcs{};
        /// @brief stores the physical address of the guest vmcs
        bsl::safe_uintmax m_vmcs_phys{bsl::safe_uintmax::zero(true)};
        /// @brief stores the rest of the state the vmcs doesn't
        vmcs_missing_registers_t m_vmcs_missing_registers{};
        /// @brief stores the general purpose registers
        general_purpose_regs_t m_gprs{};

        /// <!-- description -->
        ///   @brief Stores the provided ES segment state info in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        set_es_segment_descriptor(STATE_SAVE_CONCEPT const *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::ZERO_U16 == state->es_selector) {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_ES_SELECTOR, bsl::ZERO_U16);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_ES_ACCESS_RIGHTS, VMCS_UNUSABLE_SEGMENT);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_ES_LIMIT, bsl::ZERO_U32);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_ES_BASE, bsl::ZERO_U64);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_ES_SELECTOR, state->es_selector);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(
                    VMCS_GUEST_ES_ACCESS_RIGHTS, bsl::to_u32(state->es_attrib));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_ES_LIMIT, state->es_limit);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_ES_BASE, state->es_base);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the provided CS segment state info in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        set_cs_segment_descriptor(STATE_SAVE_CONCEPT const *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::ZERO_U16 == state->cs_selector) {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_CS_SELECTOR, bsl::ZERO_U16);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_CS_ACCESS_RIGHTS, VMCS_UNUSABLE_SEGMENT);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_CS_LIMIT, bsl::ZERO_U32);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_CS_BASE, bsl::ZERO_U64);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_CS_SELECTOR, state->cs_selector);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(
                    VMCS_GUEST_CS_ACCESS_RIGHTS, bsl::to_u32(state->cs_attrib));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_CS_LIMIT, state->cs_limit);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_CS_BASE, state->cs_base);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the provided SS segment state info in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        set_ss_segment_descriptor(STATE_SAVE_CONCEPT const *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::ZERO_U16 == state->ss_selector) {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_SS_SELECTOR, bsl::ZERO_U16);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_SS_ACCESS_RIGHTS, VMCS_UNUSABLE_SEGMENT);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_SS_LIMIT, bsl::ZERO_U32);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_SS_BASE, bsl::ZERO_U64);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_SS_SELECTOR, state->ss_selector);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(
                    VMCS_GUEST_SS_ACCESS_RIGHTS, bsl::to_u32(state->ss_attrib));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_SS_LIMIT, state->ss_limit);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_SS_BASE, state->ss_base);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the provided DS segment state info in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        set_ds_segment_descriptor(STATE_SAVE_CONCEPT const *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::ZERO_U16 == state->ds_selector) {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_DS_SELECTOR, bsl::ZERO_U16);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_DS_ACCESS_RIGHTS, VMCS_UNUSABLE_SEGMENT);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_DS_LIMIT, bsl::ZERO_U32);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_DS_BASE, bsl::ZERO_U64);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_DS_SELECTOR, state->ds_selector);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(
                    VMCS_GUEST_DS_ACCESS_RIGHTS, bsl::to_u32(state->ds_attrib));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_DS_LIMIT, state->ds_limit);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_DS_BASE, state->ds_base);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the provided FS segment state info in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        set_fs_segment_descriptor(STATE_SAVE_CONCEPT const *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::ZERO_U16 == state->fs_selector) {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_FS_SELECTOR, bsl::ZERO_U16);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_FS_ACCESS_RIGHTS, VMCS_UNUSABLE_SEGMENT);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_FS_LIMIT, bsl::ZERO_U32);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_FS_BASE, bsl::ZERO_U64);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_FS_SELECTOR, state->fs_selector);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(
                    VMCS_GUEST_FS_ACCESS_RIGHTS, bsl::to_u32(state->fs_attrib));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_FS_LIMIT, state->fs_limit);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_FS_BASE, state->fs_base);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the provided GS segment state info in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        set_gs_segment_descriptor(STATE_SAVE_CONCEPT const *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::ZERO_U16 == state->gs_selector) {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_GS_SELECTOR, bsl::ZERO_U16);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_GS_ACCESS_RIGHTS, VMCS_UNUSABLE_SEGMENT);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_GS_LIMIT, bsl::ZERO_U32);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_GS_BASE, bsl::ZERO_U64);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_GS_SELECTOR, state->gs_selector);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(
                    VMCS_GUEST_GS_ACCESS_RIGHTS, bsl::to_u32(state->gs_attrib));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_GS_LIMIT, state->gs_limit);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_GS_BASE, state->gs_base);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the provided LDTR segment state info in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        set_ldtr_segment_descriptor(STATE_SAVE_CONCEPT const *const state) &noexcept
            -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::ZERO_U16 == state->ldtr_selector) {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_LDTR_SELECTOR, bsl::ZERO_U16);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_LDTR_ACCESS_RIGHTS, VMCS_UNUSABLE_SEGMENT);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_LDTR_LIMIT, bsl::ZERO_U32);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_LDTR_BASE, bsl::ZERO_U64);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_LDTR_SELECTOR, state->ldtr_selector);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(
                    VMCS_GUEST_LDTR_ACCESS_RIGHTS, bsl::to_u32(state->ldtr_attrib));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_LDTR_LIMIT, state->ldtr_limit);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_LDTR_BASE, state->ldtr_base);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the provided TR segment state info in the VPS.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set the VPS to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        set_tr_segment_descriptor(STATE_SAVE_CONCEPT const *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (bsl::ZERO_U16 == state->tr_selector) {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_TR_SELECTOR, bsl::ZERO_U16);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_TR_ACCESS_RIGHTS, VMCS_UNUSABLE_SEGMENT);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_TR_LIMIT, bsl::ZERO_U32);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_TR_BASE, bsl::ZERO_U64);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                ret = m_intrinsic->vmwrite16(VMCS_GUEST_TR_SELECTOR, state->tr_selector);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(
                    VMCS_GUEST_TR_ACCESS_RIGHTS, bsl::to_u32(state->tr_attrib));
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite32(VMCS_GUEST_TR_LIMIT, state->tr_limit);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                ret = m_intrinsic->vmwrite64(VMCS_GUEST_TR_BASE, state->tr_base);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the ES segment info in the VPS to the provided
        ///     state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        get_es_segment_descriptor(STATE_SAVE_CONCEPT *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            bsl::safe_uint16 selector{};
            bsl::safe_uint32 access_rights{};
            bsl::safe_uint32 limit{};
            bsl::safe_uint64 base{};

            ret = m_intrinsic->vmread16(VMCS_GUEST_ES_SELECTOR, selector.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_ES_ACCESS_RIGHTS, access_rights.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_ES_LIMIT, limit.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_ES_BASE, base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (VMCS_UNUSABLE_SEGMENT == access_rights) {
                state->es_selector = bsl::ZERO_U16.get();
                state->es_attrib = bsl::ZERO_U16.get();
                state->es_limit = bsl::ZERO_U32.get();
                state->es_base = bsl::ZERO_U64.get();
            }
            else {
                state->es_selector = selector.get();
                state->es_attrib = bsl::to_u16(access_rights).get();
                state->es_limit = limit.get();
                state->es_base = base.get();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the CS segment info in the VPS to the provided
        ///     state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        get_cs_segment_descriptor(STATE_SAVE_CONCEPT *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            bsl::safe_uint16 selector{};
            bsl::safe_uint32 access_rights{};
            bsl::safe_uint32 limit{};
            bsl::safe_uint64 base{};

            ret = m_intrinsic->vmread16(VMCS_GUEST_CS_SELECTOR, selector.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_CS_ACCESS_RIGHTS, access_rights.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_CS_LIMIT, limit.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_CS_BASE, base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (VMCS_UNUSABLE_SEGMENT == access_rights) {
                state->cs_selector = bsl::ZERO_U16.get();
                state->cs_attrib = bsl::ZERO_U16.get();
                state->cs_limit = bsl::ZERO_U32.get();
                state->cs_base = bsl::ZERO_U64.get();
            }
            else {
                state->cs_selector = selector.get();
                state->cs_attrib = bsl::to_u16(access_rights).get();
                state->cs_limit = limit.get();
                state->cs_base = base.get();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the SS segment info in the VPS to the provided
        ///     state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        get_ss_segment_descriptor(STATE_SAVE_CONCEPT *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            bsl::safe_uint16 selector{};
            bsl::safe_uint32 access_rights{};
            bsl::safe_uint32 limit{};
            bsl::safe_uint64 base{};

            ret = m_intrinsic->vmread16(VMCS_GUEST_SS_SELECTOR, selector.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_SS_ACCESS_RIGHTS, access_rights.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_SS_LIMIT, limit.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_SS_BASE, base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (VMCS_UNUSABLE_SEGMENT == access_rights) {
                state->ss_selector = bsl::ZERO_U16.get();
                state->ss_attrib = bsl::ZERO_U16.get();
                state->ss_limit = bsl::ZERO_U32.get();
                state->ss_base = bsl::ZERO_U64.get();
            }
            else {
                state->ss_selector = selector.get();
                state->ss_attrib = bsl::to_u16(access_rights).get();
                state->ss_limit = limit.get();
                state->ss_base = base.get();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the DS segment info in the VPS to the provided
        ///     state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        get_ds_segment_descriptor(STATE_SAVE_CONCEPT *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            bsl::safe_uint16 selector{};
            bsl::safe_uint32 access_rights{};
            bsl::safe_uint32 limit{};
            bsl::safe_uint64 base{};

            ret = m_intrinsic->vmread16(VMCS_GUEST_DS_SELECTOR, selector.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_DS_ACCESS_RIGHTS, access_rights.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_DS_LIMIT, limit.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_DS_BASE, base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (VMCS_UNUSABLE_SEGMENT == access_rights) {
                state->ds_selector = bsl::ZERO_U16.get();
                state->ds_attrib = bsl::ZERO_U16.get();
                state->ds_limit = bsl::ZERO_U32.get();
                state->ds_base = bsl::ZERO_U64.get();
            }
            else {
                state->ds_selector = selector.get();
                state->ds_attrib = bsl::to_u16(access_rights).get();
                state->ds_limit = limit.get();
                state->ds_base = base.get();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the GS segment info in the VPS to the provided
        ///     state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        get_gs_segment_descriptor(STATE_SAVE_CONCEPT *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            bsl::safe_uint16 selector{};
            bsl::safe_uint32 access_rights{};
            bsl::safe_uint32 limit{};
            bsl::safe_uint64 base{};

            ret = m_intrinsic->vmread16(VMCS_GUEST_GS_SELECTOR, selector.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_GS_ACCESS_RIGHTS, access_rights.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_GS_LIMIT, limit.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_GS_BASE, base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (VMCS_UNUSABLE_SEGMENT == access_rights) {
                state->gs_selector = bsl::ZERO_U16.get();
                state->gs_attrib = bsl::ZERO_U16.get();
                state->gs_limit = bsl::ZERO_U32.get();
                state->gs_base = bsl::ZERO_U64.get();
            }
            else {
                state->gs_selector = selector.get();
                state->gs_attrib = bsl::to_u16(access_rights).get();
                state->gs_limit = limit.get();
                state->gs_base = base.get();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the FS segment info in the VPS to the provided
        ///     state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        get_fs_segment_descriptor(STATE_SAVE_CONCEPT *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            bsl::safe_uint16 selector{};
            bsl::safe_uint32 access_rights{};
            bsl::safe_uint32 limit{};
            bsl::safe_uint64 base{};

            ret = m_intrinsic->vmread16(VMCS_GUEST_FS_SELECTOR, selector.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_FS_ACCESS_RIGHTS, access_rights.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_FS_LIMIT, limit.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_FS_BASE, base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (VMCS_UNUSABLE_SEGMENT == access_rights) {
                state->fs_selector = bsl::ZERO_U16.get();
                state->fs_attrib = bsl::ZERO_U16.get();
                state->fs_limit = bsl::ZERO_U32.get();
                state->fs_base = bsl::ZERO_U64.get();
            }
            else {
                state->fs_selector = selector.get();
                state->fs_attrib = bsl::to_u16(access_rights).get();
                state->fs_limit = limit.get();
                state->fs_base = base.get();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the LDTR segment info in the VPS to the provided
        ///     state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        get_ldtr_segment_descriptor(STATE_SAVE_CONCEPT *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            bsl::safe_uint16 selector{};
            bsl::safe_uint32 access_rights{};
            bsl::safe_uint32 limit{};
            bsl::safe_uint64 base{};

            ret = m_intrinsic->vmread16(VMCS_GUEST_LDTR_SELECTOR, selector.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_LDTR_ACCESS_RIGHTS, access_rights.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_LDTR_LIMIT, limit.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_LDTR_BASE, base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (VMCS_UNUSABLE_SEGMENT == access_rights) {
                state->ldtr_selector = bsl::ZERO_U16.get();
                state->ldtr_attrib = bsl::ZERO_U16.get();
                state->ldtr_limit = bsl::ZERO_U32.get();
                state->ldtr_base = bsl::ZERO_U64.get();
            }
            else {
                state->ldtr_selector = selector.get();
                state->ldtr_attrib = bsl::to_u16(access_rights).get();
                state->ldtr_limit = limit.get();
                state->ldtr_base = base.get();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Stores the TR segment info in the VPS to the provided
        ///     state save.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam STATE_SAVE_CONCEPT the type of state save to use
        ///   @param state the state to set
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename STATE_SAVE_CONCEPT>
        [[nodiscard]] constexpr auto
        get_tr_segment_descriptor(STATE_SAVE_CONCEPT *const state) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            bsl::safe_uint16 selector{};
            bsl::safe_uint32 access_rights{};
            bsl::safe_uint32 limit{};
            bsl::safe_uint64 base{};

            ret = m_intrinsic->vmread16(VMCS_GUEST_TR_SELECTOR, selector.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_TR_ACCESS_RIGHTS, access_rights.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread32(VMCS_GUEST_TR_LIMIT, limit.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_TR_BASE, base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (VMCS_UNUSABLE_SEGMENT == access_rights) {
                state->tr_selector = bsl::ZERO_U16.get();
                state->tr_attrib = bsl::ZERO_U16.get();
                state->tr_limit = bsl::ZERO_U32.get();
                state->tr_base = bsl::ZERO_U64.get();
            }
            else {
                state->tr_selector = selector.get();
                state->tr_attrib = bsl::to_u16(access_rights).get();
                state->tr_limit = limit.get();
                state->tr_base = base.get();
            }

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Ensures that this VPS is loaded
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        ensure_this_vps_is_loaded(TLS_CONCEPT &tls) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (m_id == tls.loaded_vpsid) {
                return bsl::errc_success;
            }

            ret = m_intrinsic->vmload(&m_vmcs_phys);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            tls.loaded_vpsid = m_id.get();
            return ret;
        }

        /// <!-- description -->
        ///   @brief This is executed on each core when a VPS is first
        ///     allocated, and ensures the VMCS contains the current host
        ///     states of the CPU it is running on. We don't use the state
        ///     that the loader provides as this state can change as the
        ///     microkernel completes it's bootstrapping process.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        init_vmcs(TLS_CONCEPT &tls) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};
            auto *const state{tls.mk_state};

            m_vmcs->revision_id = bsl::to_u32_unsafe(m_intrinsic->rdmsr(IA32_VMX_BASIC)).get();

            if (bsl::unlikely(!this->ensure_this_vps_is_loaded(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite16(VMCS_HOST_ES_SELECTOR, m_intrinsic->es_selector());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite16(VMCS_HOST_CS_SELECTOR, m_intrinsic->cs_selector());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite16(VMCS_HOST_SS_SELECTOR, m_intrinsic->ss_selector());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite16(VMCS_HOST_DS_SELECTOR, m_intrinsic->ds_selector());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite16(VMCS_HOST_FS_SELECTOR, m_intrinsic->fs_selector());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite16(VMCS_HOST_GS_SELECTOR, m_intrinsic->gs_selector());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite16(VMCS_HOST_TR_SELECTOR, m_intrinsic->tr_selector());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_IA32_PAT, m_intrinsic->rdmsr(IA32_PAT));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_IA32_EFER, m_intrinsic->rdmsr(IA32_EFER));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(
                VMCS_HOST_IA32_SYSENTER_CS, m_intrinsic->rdmsr(IA32_SYSENTER_CS));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_CR0, m_intrinsic->cr0());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_CR3, m_intrinsic->cr3());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_CR4, m_intrinsic->cr4());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_FS_BASE, m_intrinsic->rdmsr(IA32_FS_BASE));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_GS_BASE, m_intrinsic->rdmsr(IA32_GS_BASE));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_TR_BASE, state->tr_base);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_GDTR_BASE, bsl::to_umax(state->gdtr.base));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_IDTR_BASE, bsl::to_umax(state->idtr.base));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(
                VMCS_HOST_IA32_SYSENTER_ESP, m_intrinsic->rdmsr(IA32_SYSENTER_ESP));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(
                VMCS_HOST_IA32_SYSENTER_EIP, m_intrinsic->rdmsr(IA32_SYSENTER_EIP));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_HOST_RIP, bsl::to_umax(&intrinsic_vmexit));
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_vmcs_missing_registers.host_ia32_star =              // --
                m_intrinsic->rdmsr(IA32_STAR).get();               // --
            m_vmcs_missing_registers.host_ia32_lstar =             // --
                m_intrinsic->rdmsr(IA32_LSTAR).get();              // --
            m_vmcs_missing_registers.host_ia32_cstar =             // --
                m_intrinsic->rdmsr(IA32_CSTAR).get();              // --
            m_vmcs_missing_registers.host_ia32_fmask =             // --
                m_intrinsic->rdmsr(IA32_FMASK).get();              // --
            m_vmcs_missing_registers.host_ia32_kernel_gs_base =    // --
                m_intrinsic->rdmsr(IA32_KERNEL_GS_BASE).get();     // --

            return bsl::errc_success;
        }

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
            bsl::print() << bsl::rst << bsl::fmt{"<40s", str};
            bsl::print() << bsl::ylw << "| ";

            if (val) {
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
            }
            else {
                bsl::print() << bsl::blk << bsl::fmt{"^19s", "unsupported"};
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

            m_vmcs = m_page_pool->template allocate<vmcs_t>(ALLOCATE_TAG_VMCS);
            if (bsl::unlikely(nullptr == m_vmcs)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_vmcs_phys = m_page_pool->virt_to_phys(m_vmcs);
            if (bsl::unlikely(!m_vmcs_phys)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->init_vmcs(tls))) {
                bsl::print<bsl::V>() << bsl::here();
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
            m_gprs = {} m_vmcs_missing_registers = {};

            m_vmcs_phys = bsl::safe_uintmax::zero(true);
            if (nullptr != m_page_pool) {
                m_page_pool->deallocate(m_vmcs, ALLOCATE_TAG_VMCS);
                m_vmcs = {};
            }
            else {
                bsl::touch();
            }

            m_assigned_ppid = syscall::BF_INVALID_ID;
            m_assigned_vpid = syscall::BF_INVALID_ID;
            m_next = {};
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
        ///   @brief Sets this vps_t as active.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        set_active(TLS_CONCEPT &tls) &noexcept
        {
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RAX, m_gprs.rax);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RBX, m_gprs.rbx);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RCX, m_gprs.rcx);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RDX, m_gprs.rdx);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RBP, m_gprs.rbp);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RSI, m_gprs.rsi);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RDI, m_gprs.rdi);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R8, m_gprs.r8);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R9, m_gprs.r9);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R10, m_gprs.r10);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R11, m_gprs.r11);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R12, m_gprs.r12);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R13, m_gprs.r13);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R14, m_gprs.r14);
            m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R15, m_gprs.r15);

            tls.active_vpsid = m_id.get();
        }

        /// <!-- description -->
        ///   @brief Sets this vps_t as inactive.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        set_inactive(TLS_CONCEPT &tls) &noexcept
        {
            if (tls.active_vpsid == m_id) {
                m_gprs.rax = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RAX).get();
                m_gprs.rbx = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBX).get();
                m_gprs.rcx = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RCX).get();
                m_gprs.rdx = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDX).get();
                m_gprs.rbp = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBP).get();
                m_gprs.rsi = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RSI).get();
                m_gprs.rdi = m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDI).get();
                m_gprs.r8 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R8).get();
                m_gprs.r9 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R9).get();
                m_gprs.r10 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R10).get();
                m_gprs.r11 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R11).get();
                m_gprs.r12 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R12).get();
                m_gprs.r13 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R13).get();
                m_gprs.r14 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R14).get();
                m_gprs.r15 = m_intrinsic->tls_reg(syscall::TLS_OFFSET_R15).get();

                tls.active_vpsid = syscall::BF_INVALID_ID.get();
            }
            else {
                bsl::error() << "unable to save TLS state. corruption likely\n" << bsl::here();
            }
        }

        /// <!-- description -->
        ///   @brief Assigns this vps_t to a VP
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpid the VP this vps_t is assigned to
        ///
        constexpr void
        assign_vp(bsl::safe_uint16 const &vpid) &noexcept
        {
            m_assigned_vpid = vpid;
        }

        /// <!-- description -->
        ///   @brief Assigns this vps_t to a PP
        ///
        /// <!-- inputs/outputs -->
        ///   @param ppid the PP this vps_t is assigned to
        ///
        constexpr void
        assign_pp(bsl::safe_uint16 const &ppid) &noexcept
        {
            m_assigned_ppid = ppid;
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
        ///   @brief Returns the ID of the PP this vps_t is assigned to
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the ID of the PP this vps_t is assigned to
        ///
        [[nodiscard]] constexpr auto
        assigned_pp() const &noexcept -> bsl::safe_uint16
        {
            return m_assigned_ppid;
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
            bsl::errc_type ret{};

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(nullptr == state)) {
                bsl::error() << "invalid state\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->ensure_this_vps_is_loaded(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (tls.active_vpsid == m_id) {
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
            }
            else {
                m_gprs.rax = state->rax;
                m_gprs.rbx = state->rbx;
                m_gprs.rcx = state->rcx;
                m_gprs.rdx = state->rdx;
                m_gprs.rbp = state->rbp;
                m_gprs.rsi = state->rsi;
                m_gprs.rdi = state->rdi;
                m_gprs.r8 = state->r8;
                m_gprs.r9 = state->r9;
                m_gprs.r10 = state->r10;
                m_gprs.r11 = state->r11;
                m_gprs.r12 = state->r12;
                m_gprs.r13 = state->r13;
                m_gprs.r14 = state->r14;
                m_gprs.r15 = state->r15;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_RSP, state->rsp);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_RIP, state->rip);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_RFLAGS, state->rflags);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            auto const gdtr_limit{bsl::to_u32(state->gdtr.limit)};
            ret = m_intrinsic->vmwrite32(VMCS_GUEST_GDTR_LIMIT, gdtr_limit);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            auto const gdtr_base{bsl::to_umax(state->gdtr.base)};
            ret = m_intrinsic->vmwrite64(VMCS_GUEST_GDTR_BASE, gdtr_base);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            auto const idtr_limit{bsl::to_u32(state->idtr.limit)};
            ret = m_intrinsic->vmwrite32(VMCS_GUEST_IDTR_LIMIT, idtr_limit);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            auto const idtr_base{bsl::to_umax(state->idtr.base)};
            ret = m_intrinsic->vmwrite64(VMCS_GUEST_IDTR_BASE, idtr_base);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->set_es_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->set_cs_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->set_ss_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->set_ds_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->set_fs_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->set_gs_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->set_ldtr_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->set_tr_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_CR0, state->cr0);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_vmcs_missing_registers.cr2 = state->cr2;

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_CR3, state->cr3);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_CR4, state->cr4);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_vmcs_missing_registers.dr6 = state->dr6;

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_DR7, state->dr7);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_IA32_EFER, state->ia32_efer);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_vmcs_missing_registers.guest_ia32_star = state->ia32_star;
            m_vmcs_missing_registers.guest_ia32_lstar = state->ia32_lstar;
            m_vmcs_missing_registers.guest_ia32_cstar = state->ia32_cstar;
            m_vmcs_missing_registers.guest_ia32_fmask = state->ia32_fmask;

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_FS_BASE, state->ia32_fs_base);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_GS_BASE, state->ia32_gs_base);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_vmcs_missing_registers.guest_ia32_kernel_gs_base = state->ia32_kernel_gs_base;

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_IA32_SYSENTER_CS, state->ia32_sysenter_cs);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_IA32_SYSENTER_ESP, state->ia32_sysenter_esp);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_IA32_SYSENTER_EIP, state->ia32_sysenter_eip);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_IA32_PAT, state->ia32_pat);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_IA32_DEBUGCTL, state->ia32_debugctl);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

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
            bsl::errc_type ret{};

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(nullptr == state)) {
                bsl::error() << "invalid state\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->ensure_this_vps_is_loaded(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (tls.active_vpsid == m_id) {
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
            }
            else {
                state->rax = m_gprs.rax;
                state->rbx = m_gprs.rbx;
                state->rcx = m_gprs.rcx;
                state->rdx = m_gprs.rdx;
                state->rbp = m_gprs.rbp;
                state->rsi = m_gprs.rsi;
                state->rdi = m_gprs.rdi;
                state->r8 = m_gprs.r8;
                state->r9 = m_gprs.r9;
                state->r10 = m_gprs.r10;
                state->r11 = m_gprs.r11;
                state->r12 = m_gprs.r12;
                state->r13 = m_gprs.r13;
                state->r14 = m_gprs.r14;
                state->r15 = m_gprs.r15;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_RSP, &state->rsp);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_RIP, &state->rip);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_RFLAGS, &state->rflags);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread16(VMCS_GUEST_GDTR_LIMIT, &state->gdtr.limit);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            bsl::safe_uint64 gdtr_base{};
            ret = m_intrinsic->vmread64(VMCS_GUEST_GDTR_BASE, gdtr_base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            state->gdtr.base = bsl::to_ptr<bsl::uint64 *>(gdtr_base);

            ret = m_intrinsic->vmread16(VMCS_GUEST_IDTR_LIMIT, &state->idtr.limit);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            bsl::safe_uint64 idtr_base{};
            ret = m_intrinsic->vmread64(VMCS_GUEST_IDTR_BASE, idtr_base.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            state->idtr.base = bsl::to_ptr<bsl::uint64 *>(idtr_base);

            if (bsl::unlikely(!this->get_es_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->get_cs_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->get_ss_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->get_ds_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->get_fs_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->get_gs_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->get_ldtr_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->get_tr_segment_descriptor(state))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_CR0, &state->cr0);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            state->cr2 = m_vmcs_missing_registers.cr2;

            ret = m_intrinsic->vmread64(VMCS_GUEST_CR3, &state->cr3);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_CR4, &state->cr4);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            state->dr6 = m_vmcs_missing_registers.dr6;

            ret = m_intrinsic->vmread64(VMCS_GUEST_DR7, &state->dr7);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_IA32_EFER, &state->ia32_efer);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            state->ia32_star = m_vmcs_missing_registers.guest_ia32_star;
            state->ia32_lstar = m_vmcs_missing_registers.guest_ia32_lstar;
            state->ia32_cstar = m_vmcs_missing_registers.guest_ia32_cstar;
            state->ia32_fmask = m_vmcs_missing_registers.guest_ia32_fmask;

            ret = m_intrinsic->vmread64(VMCS_GUEST_FS_BASE, &state->ia32_fs_base);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_GS_BASE, &state->ia32_gs_base);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            state->ia32_kernel_gs_base = m_vmcs_missing_registers.guest_ia32_kernel_gs_base;

            ret = m_intrinsic->vmread64(VMCS_GUEST_IA32_SYSENTER_CS, &state->ia32_sysenter_cs);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_IA32_SYSENTER_ESP, &state->ia32_sysenter_esp);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_IA32_SYSENTER_EIP, &state->ia32_sysenter_eip);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_IA32_PAT, &state->ia32_pat);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_IA32_DEBUGCTL, &state->ia32_debugctl);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

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
            /// TODO:
            /// - Implement a field type checker to make sure the user is
            ///   using the proper field type here. Make sure that this field
            ///   type checker is only turned on with debug builds.
            ///

            bsl::errc_type ret{};
            bsl::safe_integral<FIELD_TYPE> val{};

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::safe_integral<FIELD_TYPE>::zero(true);
            }

            if (bsl::unlikely(!this->ensure_this_vps_is_loaded(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::safe_integral<FIELD_TYPE>::zero(true);
            }

            if constexpr (bsl::is_same<FIELD_TYPE, bsl::uint16>::value) {
                ret = m_intrinsic->vmread16(index, val.data());
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return val;
                }

                return val;
            }

            if constexpr (bsl::is_same<FIELD_TYPE, bsl::uint32>::value) {
                ret = m_intrinsic->vmread32(index, val.data());
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return val;
                }

                return val;
            }

            if constexpr (bsl::is_same<FIELD_TYPE, bsl::uint64>::value) {
                ret = m_intrinsic->vmread64(index, val.data());
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return val;
                }

                return val;
            }

            bsl::error() << "unsupported field type\n" << bsl::here();
            return bsl::safe_integral<FIELD_TYPE>::zero(true);
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
            /// TODO:
            /// - Implement a field type checker to make sure the user is
            ///   using the proper field type here. Make sure that this field
            ///   type checker is only turned on with debug builds.
            ///

            bsl::errc_type ret{};

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

            if (bsl::unlikely(!this->ensure_this_vps_is_loaded(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            constexpr auto vmcs_pinbased_ctls_idx{bsl::to_umax(0x4000U)};
            constexpr auto vmcs_exit_ctls_idx{bsl::to_umax(0x400CU)};
            constexpr auto vmcs_entry_ctls_idx{bsl::to_umax(0x4012U)};

            bsl::safe_integral<FIELD_TYPE> sanitized{value};

            if constexpr (bsl::is_same<FIELD_TYPE, bsl::uint32>::value) {
                switch (index.get()) {
                    case vmcs_pinbased_ctls_idx.get(): {
                        constexpr auto vmcs_pinbased_ctls_mask{bsl::to_u32(0x28U)};
                        sanitized |= vmcs_pinbased_ctls_mask;
                        break;
                    }

                    case vmcs_exit_ctls_idx.get(): {
                        constexpr auto vmcs_exit_ctls_mask{bsl::to_u32(0x3C0204U)};
                        sanitized |= vmcs_exit_ctls_mask;
                        break;
                    }

                    case vmcs_entry_ctls_idx.get(): {
                        constexpr auto vmcs_entry_ctls_mask{bsl::to_u32(0xC204U)};
                        sanitized |= vmcs_entry_ctls_mask;
                        break;
                    }

                    default: {
                        break;
                    }
                }
            }
            else {
                switch (index.get()) {
                    case vmcs_pinbased_ctls_idx.get(): {
                        bsl::error()
                            << "invalid integer type for field: " << bsl::hex(index) << bsl::endl
                            << bsl::here();

                        return bsl::errc_failure;
                    }

                    case vmcs_exit_ctls_idx.get(): {
                        bsl::error()
                            << "invalid integer type for field: " << bsl::hex(index) << bsl::endl
                            << bsl::here();

                        return bsl::errc_failure;
                    }

                    case vmcs_entry_ctls_idx.get(): {
                        bsl::error()
                            << "invalid integer type for field: " << bsl::hex(index) << bsl::endl
                            << bsl::here();

                        return bsl::errc_failure;
                    }

                    default: {
                        break;
                    }
                }
            }

            if constexpr (bsl::is_same<FIELD_TYPE, bsl::uint16>::value) {
                ret = m_intrinsic->vmwrite16(index, sanitized);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            if constexpr (bsl::is_same<FIELD_TYPE, bsl::uint32>::value) {
                ret = m_intrinsic->vmwrite32(index, sanitized);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            if constexpr (bsl::is_same<FIELD_TYPE, bsl::uint64>::value) {
                ret = m_intrinsic->vmwrite64(index, sanitized);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            bsl::error() << "unsupported field type\n" << bsl::here();
            return bsl::errc_failure;
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
            bsl::safe_uint64 index{bsl::safe_uint64::zero(true)};

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::safe_uintmax::zero(true);
            }

            switch (reg) {
                case syscall::bf_reg_t::bf_reg_t_rax: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RAX);
                    }

                    return m_gprs.rax;
                }

                case syscall::bf_reg_t::bf_reg_t_rbx: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBX);
                    }

                    return m_gprs.rbx;
                }

                case syscall::bf_reg_t::bf_reg_t_rcx: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RCX);
                    }

                    return m_gprs.rcx;
                }

                case syscall::bf_reg_t::bf_reg_t_rdx: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDX);
                    }

                    return m_gprs.rdx;
                }

                case syscall::bf_reg_t::bf_reg_t_rbp: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RBP);
                    }

                    return m_gprs.rbp;
                }

                case syscall::bf_reg_t::bf_reg_t_rsi: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RSI);
                    }

                    return m_gprs.rsi;
                }

                case syscall::bf_reg_t::bf_reg_t_rdi: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_RDI);
                    }

                    return m_gprs.rdi;
                }

                case syscall::bf_reg_t::bf_reg_t_r8: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R8);
                    }

                    return m_gprs.r8;
                }

                case syscall::bf_reg_t::bf_reg_t_r9: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R9);
                    }

                    return m_gprs.r9;
                }

                case syscall::bf_reg_t::bf_reg_t_r10: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R10);
                    }

                    return m_gprs.r10;
                }

                case syscall::bf_reg_t::bf_reg_t_r11: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R11);
                    }

                    return m_gprs.r11;
                }

                case syscall::bf_reg_t::bf_reg_t_r12: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R12);
                    }

                    return m_gprs.r12;
                }

                case syscall::bf_reg_t::bf_reg_t_r13: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R13);
                    }

                    return m_gprs.r13;
                }

                case syscall::bf_reg_t::bf_reg_t_r14: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R14);
                    }

                    return m_gprs.r14;
                }

                case syscall::bf_reg_t::bf_reg_t_r15: {
                    if (tls.active_vpsid == m_id) {
                        return m_intrinsic->tls_reg(syscall::TLS_OFFSET_R15);
                    }

                    return m_gprs.r15;
                }

                case syscall::bf_reg_t::bf_reg_t_rip: {
                    index = VMCS_GUEST_RIP;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_rsp: {
                    index = VMCS_GUEST_RSP;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_rflags: {
                    index = VMCS_GUEST_RFLAGS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gdtr_base_addr: {
                    index = VMCS_GUEST_GDTR_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gdtr_limit: {
                    index = VMCS_GUEST_GDTR_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_idtr_base_addr: {
                    index = VMCS_GUEST_IDTR_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_idtr_limit: {
                    index = VMCS_GUEST_IDTR_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_es: {
                    index = VMCS_GUEST_ES_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_es_base_addr: {
                    index = VMCS_GUEST_ES_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_es_limit: {
                    index = VMCS_GUEST_ES_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_es_attributes: {
                    index = VMCS_GUEST_ES_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cs: {
                    index = VMCS_GUEST_CS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_base_addr: {
                    index = VMCS_GUEST_CS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_limit: {
                    index = VMCS_GUEST_CS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_attributes: {
                    index = VMCS_GUEST_CS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ss: {
                    index = VMCS_GUEST_SS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_base_addr: {
                    index = VMCS_GUEST_SS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_limit: {
                    index = VMCS_GUEST_SS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_attributes: {
                    index = VMCS_GUEST_SS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ds: {
                    index = VMCS_GUEST_DS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_base_addr: {
                    index = VMCS_GUEST_DS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_limit: {
                    index = VMCS_GUEST_DS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_attributes: {
                    index = VMCS_GUEST_DS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_fs: {
                    index = VMCS_GUEST_FS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_base_addr: {
                    index = VMCS_GUEST_FS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_limit: {
                    index = VMCS_GUEST_FS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_attributes: {
                    index = VMCS_GUEST_FS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gs: {
                    index = VMCS_GUEST_GS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_base_addr: {
                    index = VMCS_GUEST_GS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_limit: {
                    index = VMCS_GUEST_GS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_attributes: {
                    index = VMCS_GUEST_GS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr: {
                    index = VMCS_GUEST_LDTR_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_base_addr: {
                    index = VMCS_GUEST_LDTR_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_limit: {
                    index = VMCS_GUEST_LDTR_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_attributes: {
                    index = VMCS_GUEST_LDTR_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_tr: {
                    index = VMCS_GUEST_TR_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_base_addr: {
                    index = VMCS_GUEST_TR_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_limit: {
                    index = VMCS_GUEST_TR_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_attributes: {
                    index = VMCS_GUEST_TR_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cr0: {
                    index = VMCS_GUEST_CR0;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cr2: {
                    return m_vmcs_missing_registers.cr2;
                }

                case syscall::bf_reg_t::bf_reg_t_cr3: {
                    index = VMCS_GUEST_CR3;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cr4: {
                    index = VMCS_GUEST_CR4;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_dr6: {
                    return m_vmcs_missing_registers.dr6;
                }

                case syscall::bf_reg_t::bf_reg_t_dr7: {
                    index = VMCS_GUEST_DR7;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_efer: {
                    index = VMCS_GUEST_IA32_EFER;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_star: {
                    return m_vmcs_missing_registers.guest_ia32_star;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_lstar: {
                    return m_vmcs_missing_registers.guest_ia32_lstar;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_cstar: {
                    return m_vmcs_missing_registers.guest_ia32_cstar;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_fmask: {
                    return m_vmcs_missing_registers.guest_ia32_fmask;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_fs_base: {
                    index = VMCS_GUEST_FS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_gs_base: {
                    index = VMCS_GUEST_GS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_kernel_gs_base: {
                    return m_vmcs_missing_registers.guest_ia32_kernel_gs_base;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_cs: {
                    index = VMCS_GUEST_IA32_SYSENTER_CS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_esp: {
                    index = VMCS_GUEST_IA32_SYSENTER_ESP;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_eip: {
                    index = VMCS_GUEST_IA32_SYSENTER_EIP;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_pat: {
                    index = VMCS_GUEST_IA32_PAT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_debugctl: {
                    index = VMCS_GUEST_IA32_DEBUGCTL;
                    break;
                }

                default: {
                    bsl::error() << "unknown by bf_reg_t\n" << bsl::here();
                    break;
                }
            }

            auto val{this->read<bsl::uint64>(tls, index)};
            if (bsl::unlikely(!val)) {
                bsl::print<bsl::V>() << bsl::here();
                return val;
            }

            return val;
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
            bsl::safe_uint64 index{bsl::safe_uint64::zero(true)};

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
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RAX, val);
                    }
                    else {
                        m_gprs.rax = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rbx: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RBX, val);
                    }
                    else {
                        m_gprs.rbx = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rcx: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RCX, val);
                    }
                    else {
                        m_gprs.rcx = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rdx: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RDX, val);
                    }
                    else {
                        m_gprs.rdx = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rbp: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RBP, val);
                    }
                    else {
                        m_gprs.rbp = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rsi: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RSI, val);
                    }
                    else {
                        m_gprs.rsi = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rdi: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_RDI, val);
                    }
                    else {
                        m_gprs.rdi = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r8: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R8, val);
                    }
                    else {
                        m_gprs.r8 = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r9: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R9, val);
                    }
                    else {
                        m_gprs.r9 = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r10: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R10, val);
                    }
                    else {
                        m_gprs.r10 = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r11: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R11, val);
                    }
                    else {
                        m_gprs.r11 = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r12: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R12, val);
                    }
                    else {
                        m_gprs.r12 = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r13: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R13, val);
                    }
                    else {
                        m_gprs.r13 = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r14: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R14, val);
                    }
                    else {
                        m_gprs.r14 = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_r15: {
                    if (tls.active_vpsid == m_id) {
                        m_intrinsic->set_tls_reg(syscall::TLS_OFFSET_R15, val);
                    }
                    else {
                        m_gprs.r15 = val.get();
                    }
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_rip: {
                    index = VMCS_GUEST_RIP;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_rsp: {
                    index = VMCS_GUEST_RSP;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_rflags: {
                    index = VMCS_GUEST_RFLAGS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gdtr_base_addr: {
                    index = VMCS_GUEST_GDTR_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gdtr_limit: {
                    index = VMCS_GUEST_GDTR_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_idtr_base_addr: {
                    index = VMCS_GUEST_IDTR_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_idtr_limit: {
                    index = VMCS_GUEST_IDTR_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_es: {
                    index = VMCS_GUEST_ES_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_es_base_addr: {
                    index = VMCS_GUEST_ES_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_es_limit: {
                    index = VMCS_GUEST_ES_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_es_attributes: {
                    index = VMCS_GUEST_ES_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cs: {
                    index = VMCS_GUEST_CS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_base_addr: {
                    index = VMCS_GUEST_CS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_limit: {
                    index = VMCS_GUEST_CS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cs_attributes: {
                    index = VMCS_GUEST_CS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ss: {
                    index = VMCS_GUEST_SS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_base_addr: {
                    index = VMCS_GUEST_SS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_limit: {
                    index = VMCS_GUEST_SS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ss_attributes: {
                    index = VMCS_GUEST_SS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ds: {
                    index = VMCS_GUEST_DS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_base_addr: {
                    index = VMCS_GUEST_DS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_limit: {
                    index = VMCS_GUEST_DS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ds_attributes: {
                    index = VMCS_GUEST_DS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_fs: {
                    index = VMCS_GUEST_FS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_base_addr: {
                    index = VMCS_GUEST_FS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_limit: {
                    index = VMCS_GUEST_FS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_fs_attributes: {
                    index = VMCS_GUEST_FS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gs: {
                    index = VMCS_GUEST_GS_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_base_addr: {
                    index = VMCS_GUEST_GS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_limit: {
                    index = VMCS_GUEST_GS_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_gs_attributes: {
                    index = VMCS_GUEST_GS_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr: {
                    index = VMCS_GUEST_LDTR_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_base_addr: {
                    index = VMCS_GUEST_LDTR_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_limit: {
                    index = VMCS_GUEST_LDTR_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ldtr_attributes: {
                    index = VMCS_GUEST_LDTR_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_tr: {
                    index = VMCS_GUEST_TR_SELECTOR;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_base_addr: {
                    index = VMCS_GUEST_TR_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_limit: {
                    index = VMCS_GUEST_TR_LIMIT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_tr_attributes: {
                    index = VMCS_GUEST_TR_ACCESS_RIGHTS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cr0: {
                    index = VMCS_GUEST_CR0;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cr2: {
                    m_vmcs_missing_registers.cr2 = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_cr3: {
                    index = VMCS_GUEST_CR3;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_cr4: {
                    index = VMCS_GUEST_CR4;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_dr6: {
                    m_vmcs_missing_registers.dr6 = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_dr7: {
                    index = VMCS_GUEST_DR7;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_efer: {
                    index = VMCS_GUEST_IA32_EFER;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_star: {
                    m_vmcs_missing_registers.guest_ia32_star = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_lstar: {
                    m_vmcs_missing_registers.guest_ia32_lstar = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_cstar: {
                    m_vmcs_missing_registers.guest_ia32_cstar = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_fmask: {
                    m_vmcs_missing_registers.guest_ia32_fmask = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_fs_base: {
                    index = VMCS_GUEST_FS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_gs_base: {
                    index = VMCS_GUEST_GS_BASE;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_kernel_gs_base: {
                    m_vmcs_missing_registers.guest_ia32_kernel_gs_base = val.get();
                    return bsl::errc_success;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_cs: {
                    index = VMCS_GUEST_IA32_SYSENTER_CS;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_esp: {
                    index = VMCS_GUEST_IA32_SYSENTER_ESP;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_sysenter_eip: {
                    index = VMCS_GUEST_IA32_SYSENTER_EIP;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_pat: {
                    index = VMCS_GUEST_IA32_PAT;
                    break;
                }

                case syscall::bf_reg_t::bf_reg_t_ia32_debugctl: {
                    index = VMCS_GUEST_IA32_DEBUGCTL;
                    break;
                }

                default: {
                    bsl::error() << "unknown by bf_reg_t\n" << bsl::here();
                    break;
                }
            }

            auto const ret{this->write<bsl::uint64>(tls, index, val)};
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            return ret;
        }

        /// <!-- description -->
        ///   @brief Runs the VPS. Note that this function does not
        ///     return until a VMExit occurs. Once complete, this function
        ///     will return the VMExit reason.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @tparam VMEXIT_LOG_CONCEPT defines the type of VMExit log to use
        ///   @param tls the current TLS block
        ///   @param log the VMExit log to use
        ///   @return Returns the VMExit reason on success, or
        ///     bsl::safe_uintmax::zero(true) on failure.
        ///
        template<typename TLS_CONCEPT, typename VMEXIT_LOG_CONCEPT>
        [[nodiscard]] constexpr auto
        run(TLS_CONCEPT &tls, VMEXIT_LOG_CONCEPT &log) &noexcept -> bsl::safe_uintmax
        {
            constexpr bsl::safe_uintmax invalid_exit_reason{bsl::to_umax(0xFFFFFFFF00000000U)};

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::safe_uintmax::zero(true);
            }

            if (bsl::unlikely(!this->ensure_this_vps_is_loaded(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::safe_uintmax::zero(true);
            }

            bsl::safe_uintmax const exit_reason{intrinsic_vmrun(&m_vmcs_missing_registers)};
            if (bsl::unlikely(exit_reason > invalid_exit_reason)) {
                bsl::error() << "vmlaunch/vmresume failed with error code "    // --
                             << (exit_reason & (~invalid_exit_reason))         // --
                             << bsl::endl                                      // --
                             << bsl::here();                                   // --

                return bsl::safe_uintmax::zero(true);
            }

            if constexpr (!(BSL_DEBUG_LEVEL < bsl::VV)) {
                log.add(
                    tls.ppid,
                    {tls.active_vmid,
                     tls.active_vpid,
                     tls.active_vpsid,
                     exit_reason,
                     m_intrinsic->vmread64_quiet(VMCS_EXIT_QUALIFICATION),
                     m_intrinsic->vmread64_quiet(VMCS_VMEXIT_INSTRUCTION_INFORMATION),
                     bsl::ZERO_UMAX,
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
                     m_intrinsic->vmread64_quiet(VMCS_GUEST_RSP),
                     m_intrinsic->vmread64_quiet(VMCS_GUEST_RIP)});
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
            bsl::errc_type ret{};
            bsl::safe_uint64 rip{};
            bsl::safe_uint64 len{};

            if (bsl::unlikely(!this->is_allocated())) {
                bsl::error() << "invalid vps\n" << bsl::here();
                return bsl::errc_failure;
            }

            if (bsl::unlikely(!this->ensure_this_vps_is_loaded(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_GUEST_RIP, rip.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmread64(VMCS_VMEXIT_INSTRUCTION_LENGTH, len.data());
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_intrinsic->vmwrite64(VMCS_GUEST_RIP, rip + len);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            return ret;
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

            ret = m_intrinsic->vmclear(&m_vmcs_phys);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            ret = m_intrinsic->vmload(&m_vmcs_phys);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            tls.loaded_vpsid = m_id.get();
            m_vmcs_missing_registers.launched = {};

            return ret;
        }

        /// <!-- description -->
        ///   @brief Dumps the contents of the VPS to the console
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        dump(TLS_CONCEPT &tls) &noexcept
        {
            bsl::discard(tls);

            if constexpr (BSL_DEBUG_LEVEL == bsl::CRITICAL_ONLY) {
                return;
            }

            // clang-format off

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

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^40s", "description "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::cyn << bsl::fmt{"^19s", "value "};
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            /// Allocated
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<40s", "allocated "};
            bsl::print() << bsl::ylw << "| ";
            if (this->is_allocated()) {
                bsl::print() << bsl::grn << bsl::fmt{"^19s", "yes "};
            }
            else {
                bsl::print() << bsl::red << bsl::fmt{"^19s", "no "};
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Assigned VP
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<40s", "assigned vp "};
            bsl::print() << bsl::ylw << "| ";
            if (m_assigned_vpid != syscall::BF_INVALID_ID) {
                bsl::print() << bsl::grn << "      " << bsl::hex(m_assigned_vpid) << "       ";
            }
            else {
                bsl::print() << bsl::red << "      " << bsl::hex(m_assigned_vpid) << "       ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Assigned PP
            ///

            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::fmt{"<40s", "assigned pp "};
            bsl::print() << bsl::ylw << "| ";
            if (m_assigned_ppid != syscall::BF_INVALID_ID) {
                bsl::print() << bsl::grn << "      " << bsl::hex(m_assigned_ppid) << "       ";
            }
            else {
                bsl::print() << bsl::red << "      " << bsl::hex(m_assigned_ppid) << "       ";
            }
            bsl::print() << bsl::ylw << "| ";
            bsl::print() << bsl::rst << bsl::endl;

            /// Guest Missing Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            if (!this->is_allocated()) {
                return;
            }

            if (tls.active_vpsid == m_id) {
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
            }
            else {
                this->dump("rax ", bsl::make_safe(m_gprs.rax));
                this->dump("rbx ", bsl::make_safe(m_gprs.rbx));
                this->dump("rcx ", bsl::make_safe(m_gprs.rcx));
                this->dump("rdx ", bsl::make_safe(m_gprs.rdx));
                this->dump("rbp ", bsl::make_safe(m_gprs.rbp));
                this->dump("rsi ", bsl::make_safe(m_gprs.rsi));
                this->dump("rdi ", bsl::make_safe(m_gprs.rdi));
                this->dump("r8 ", bsl::make_safe(m_gprs.r8));
                this->dump("r9 ", bsl::make_safe(m_gprs.r9));
                this->dump("r10 ", bsl::make_safe(m_gprs.r10));
                this->dump("r11 ", bsl::make_safe(m_gprs.r11));
                this->dump("r12 ", bsl::make_safe(m_gprs.r12));
                this->dump("r13 ", bsl::make_safe(m_gprs.r13));
                this->dump("r14 ", bsl::make_safe(m_gprs.r14));
                this->dump("r15 ", bsl::make_safe(m_gprs.r15));
            }

            /// 16 Bit Control Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("virtual_processor_identifier ", m_intrinsic->vmread16_quiet(VMCS_VIRTUAL_PROCESSOR_IDENTIFIER));
            this->dump("posted_interrupt_notification_vector ", m_intrinsic->vmread16_quiet(VMCS_POSTED_INTERRUPT_NOTIFICATION_VECTOR));
            this->dump("eptp_index ", m_intrinsic->vmread16_quiet(VMCS_EPTP_INDEX));

            /// 16 Bit Guest Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("es_selector ", m_intrinsic->vmread16_quiet(VMCS_GUEST_ES_SELECTOR));
            this->dump("cs_selector ", m_intrinsic->vmread16_quiet(VMCS_GUEST_CS_SELECTOR));
            this->dump("ss_selector ", m_intrinsic->vmread16_quiet(VMCS_GUEST_SS_SELECTOR));
            this->dump("ds_selector ", m_intrinsic->vmread16_quiet(VMCS_GUEST_DS_SELECTOR));
            this->dump("fs_selector ", m_intrinsic->vmread16_quiet(VMCS_GUEST_FS_SELECTOR));
            this->dump("gs_selector ", m_intrinsic->vmread16_quiet(VMCS_GUEST_GS_SELECTOR));
            this->dump("ldtr_selector ", m_intrinsic->vmread16_quiet(VMCS_GUEST_LDTR_SELECTOR));
            this->dump("tr_selector ", m_intrinsic->vmread16_quiet(VMCS_GUEST_TR_SELECTOR));
            this->dump("interrupt_status ", m_intrinsic->vmread16_quiet(VMCS_GUEST_INTERRUPT_STATUS));
            this->dump("pml_index ", m_intrinsic->vmread16_quiet(VMCS_PML_INDEX));

            /// 64 Bit Control Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("address_of_io_bitmap_a ", m_intrinsic->vmread64_quiet(VMCS_ADDRESS_OF_IO_BITMAP_A));
            this->dump("address_of_io_bitmap_b ", m_intrinsic->vmread64_quiet(VMCS_ADDRESS_OF_IO_BITMAP_B));
            this->dump("address_of_msr_bitmaps ", m_intrinsic->vmread64_quiet(VMCS_ADDRESS_OF_MSR_BITMAPS));
            this->dump("vmexit_msr_store_address ", m_intrinsic->vmread64_quiet(VMCS_VMEXIT_MSR_STORE_ADDRESS));
            this->dump("vmexit_msr_load_address ", m_intrinsic->vmread64_quiet(VMCS_VMEXIT_MSR_LOAD_ADDRESS));
            this->dump("vmentry_msr_load_address ", m_intrinsic->vmread64_quiet(VMCS_VMENTRY_MSR_LOAD_ADDRESS));
            this->dump("executive_vmcs_pointer ", m_intrinsic->vmread64_quiet(VMCS_EXECUTIVE_VMCS_POINTER));
            this->dump("pml_address ", m_intrinsic->vmread64_quiet(VMCS_PML_ADDRESS));
            this->dump("tsc_offset ", m_intrinsic->vmread64_quiet(VMCS_TSC_OFFSET));
            this->dump("virtual_apic_address ", m_intrinsic->vmread64_quiet(VMCS_VIRTUAL_APIC_ADDRESS));
            this->dump("apic_access_address ", m_intrinsic->vmread64_quiet(VMCS_APIC_ACCESS_ADDRESS));
            this->dump("posted_interrupt_descriptor_address ", m_intrinsic->vmread64_quiet(VMCS_POSTED_INTERRUPT_DESCRIPTOR_ADDRESS));
            this->dump("vm_function_controls ", m_intrinsic->vmread64_quiet(VMCS_VM_FUNCTION_CONTROLS));
            this->dump("ept_pointer ", m_intrinsic->vmread64_quiet(VMCS_EPT_POINTER));
            this->dump("eoi_exit_bitmap0 ", m_intrinsic->vmread64_quiet(VMCS_EOI_EXIT_BITMAP0));
            this->dump("eoi_exit_bitmap1 ", m_intrinsic->vmread64_quiet(VMCS_EOI_EXIT_BITMAP1));
            this->dump("eoi_exit_bitmap2 ", m_intrinsic->vmread64_quiet(VMCS_EOI_EXIT_BITMAP2));
            this->dump("eoi_exit_bitmap3 ", m_intrinsic->vmread64_quiet(VMCS_EOI_EXIT_BITMAP3));
            this->dump("eptp_list_address ", m_intrinsic->vmread64_quiet(VMCS_EPTP_LIST_ADDRESS));
            this->dump("vmread_bitmap_address ", m_intrinsic->vmread64_quiet(VMCS_VMREAD_BITMAP_ADDRESS));
            this->dump("vmwrite_bitmap_address ", m_intrinsic->vmread64_quiet(VMCS_VMWRITE_BITMAP_ADDRESS));
            this->dump("virt_exception_information_address ", m_intrinsic->vmread64_quiet(VMCS_VIRT_EXCEPTION_INFORMATION_ADDRESS));
            this->dump("xss_exiting_bitmap ", m_intrinsic->vmread64_quiet(VMCS_XSS_EXITING_BITMAP));
            this->dump("encls_exiting_bitmap ", m_intrinsic->vmread64_quiet(VMCS_ENCLS_EXITING_BITMAP));
            this->dump("sub_page_permission_table_pointer ", m_intrinsic->vmread64_quiet(VMCS_SUB_PAGE_PERMISSION_TABLE_POINTER));
            this->dump("tls_multiplier ", m_intrinsic->vmread64_quiet(VMCS_TLS_MULTIPLIER));

            /// 64 Bit Read-Only Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("guest_physical_address ", m_intrinsic->vmread64_quiet(VMCS_GUEST_PHYSICAL_ADDRESS));

            /// 64 Bit Guest Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("vmcs_link_pointer ", m_intrinsic->vmread64_quiet(VMCS_VMCS_LINK_POINTER));
            this->dump("ia32_debugctl ", m_intrinsic->vmread64_quiet(VMCS_GUEST_IA32_DEBUGCTL));
            this->dump("ia32_pat ", m_intrinsic->vmread64_quiet(VMCS_GUEST_IA32_PAT));
            this->dump("ia32_efer ", m_intrinsic->vmread64_quiet(VMCS_GUEST_IA32_EFER));
            this->dump("ia32_perf_global_ctrl ", m_intrinsic->vmread64_quiet(VMCS_GUEST_IA32_PERF_GLOBAL_CTRL));
            this->dump("guest_pdpte0 ", m_intrinsic->vmread64_quiet(VMCS_GUEST_PDPTE0));
            this->dump("guest_pdpte1 ", m_intrinsic->vmread64_quiet(VMCS_GUEST_PDPTE1));
            this->dump("guest_pdpte2 ", m_intrinsic->vmread64_quiet(VMCS_GUEST_PDPTE2));
            this->dump("guest_pdpte3 ", m_intrinsic->vmread64_quiet(VMCS_GUEST_PDPTE3));
            this->dump("ia32_bndcfgs ", m_intrinsic->vmread64_quiet(VMCS_GUEST_IA32_BNDCFGS));
            this->dump("guest_rtit_ctl ", m_intrinsic->vmread64_quiet(VMCS_GUEST_RTIT_CTL));
            this->dump("ia32_star ", bsl::make_safe(m_vmcs_missing_registers.guest_ia32_star));
            this->dump("ia32_lstar ", bsl::make_safe(m_vmcs_missing_registers.guest_ia32_lstar));
            this->dump("ia32_cstar ", bsl::make_safe(m_vmcs_missing_registers.guest_ia32_cstar));
            this->dump("ia32_fmask ", bsl::make_safe(m_vmcs_missing_registers.guest_ia32_fmask));
            this->dump("ia32_kernel_gs_base ", bsl::make_safe(m_vmcs_missing_registers.guest_ia32_kernel_gs_base));

            /// 32 Bit Control Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("pin_based_vm_execution_ctls ", m_intrinsic->vmread32_quiet(VMCS_PIN_BASED_VM_EXECUTION_CTLS));
            this->dump("primary_proc_based_vm_execution_ctls ", m_intrinsic->vmread32_quiet(VMCS_PRIMARY_PROC_BASED_VM_EXECUTION_CTLS));
            this->dump("exception_bitmap ", m_intrinsic->vmread32_quiet(VMCS_EXCEPTION_BITMAP));
            this->dump("page_fault_error_code_mask ", m_intrinsic->vmread32_quiet(VMCS_PAGE_FAULT_ERROR_CODE_MASK));
            this->dump("page_fault_error_code_match ", m_intrinsic->vmread32_quiet(VMCS_PAGE_FAULT_ERROR_CODE_MATCH));
            this->dump("cr3_target_count ", m_intrinsic->vmread32_quiet(VMCS_CR3_TARGET_COUNT));
            this->dump("vmexit_ctls ", m_intrinsic->vmread32_quiet(VMCS_VMEXIT_CTLS));
            this->dump("vmexit_msr_store_count ", m_intrinsic->vmread32_quiet(VMCS_VMEXIT_MSR_STORE_COUNT));
            this->dump("vmexit_msr_load_count ", m_intrinsic->vmread32_quiet(VMCS_VMEXIT_MSR_LOAD_COUNT));
            this->dump("vmentry_ctls ", m_intrinsic->vmread32_quiet(VMCS_VMENTRY_CTLS));
            this->dump("vmentry_msr_load_count ", m_intrinsic->vmread32_quiet(VMCS_VMENTRY_MSR_LOAD_COUNT));
            this->dump("vmentry_interrupt_information_field ", m_intrinsic->vmread32_quiet(VMCS_VMENTRY_INTERRUPT_INFORMATION_FIELD));
            this->dump("vmentry_exception_error_code ", m_intrinsic->vmread32_quiet(VMCS_VMENTRY_EXCEPTION_ERROR_CODE));
            this->dump("vmentry_instruction_length ", m_intrinsic->vmread32_quiet(VMCS_VMENTRY_INSTRUCTION_LENGTH));
            this->dump("tpr_threshold ", m_intrinsic->vmread32_quiet(VMCS_TPR_THRESHOLD));
            this->dump("secondary_proc_based_vm_execution_ctls ", m_intrinsic->vmread32_quiet(VMCS_SECONDARY_PROC_BASED_VM_EXECUTION_CTLS));
            this->dump("ple_gap ", m_intrinsic->vmread32_quiet(VMCS_PLE_GAP));
            this->dump("ple_window ", m_intrinsic->vmread32_quiet(VMCS_PLE_WINDOW));

            /// 32 Bit Read-Only Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("exit_reason ", m_intrinsic->vmread32_quiet(VMCS_EXIT_REASON));
            this->dump("vmexit_interruption_information ", m_intrinsic->vmread32_quiet(VMCS_VMEXIT_INTERRUPTION_INFORMATION));
            this->dump("vmexit_interruption_error_code ", m_intrinsic->vmread32_quiet(VMCS_VMEXIT_INTERRUPTION_ERROR_CODE));
            this->dump("idt_vectoring_information_field ", m_intrinsic->vmread32_quiet(VMCS_IDT_VECTORING_INFORMATION_FIELD));
            this->dump("idt_vectoring_error_code ", m_intrinsic->vmread32_quiet(VMCS_IDT_VECTORING_ERROR_CODE));
            this->dump("vmexit_instruction_length ", m_intrinsic->vmread32_quiet(VMCS_VMEXIT_INSTRUCTION_LENGTH));
            this->dump("vmexit_instruction_information ", m_intrinsic->vmread32_quiet(VMCS_VMEXIT_INSTRUCTION_INFORMATION));

            /// 32 Bit Guest Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("es_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_ES_LIMIT));
            this->dump("cs_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_CS_LIMIT));
            this->dump("ss_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_SS_LIMIT));
            this->dump("ds_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_DS_LIMIT));
            this->dump("fs_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_FS_LIMIT));
            this->dump("gs_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_GS_LIMIT));
            this->dump("ldtr_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_LDTR_LIMIT));
            this->dump("tr_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_TR_LIMIT));
            this->dump("gdtr_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_GDTR_LIMIT));
            this->dump("idtr_limit ", m_intrinsic->vmread32_quiet(VMCS_GUEST_IDTR_LIMIT));
            this->dump("es_access_rights ", m_intrinsic->vmread32_quiet(VMCS_GUEST_ES_ACCESS_RIGHTS));
            this->dump("cs_access_rights ", m_intrinsic->vmread32_quiet(VMCS_GUEST_CS_ACCESS_RIGHTS));
            this->dump("ss_access_rights ", m_intrinsic->vmread32_quiet(VMCS_GUEST_SS_ACCESS_RIGHTS));
            this->dump("ds_access_rights ", m_intrinsic->vmread32_quiet(VMCS_GUEST_DS_ACCESS_RIGHTS));
            this->dump("fs_access_rights ", m_intrinsic->vmread32_quiet(VMCS_GUEST_FS_ACCESS_RIGHTS));
            this->dump("gs_access_rights ", m_intrinsic->vmread32_quiet(VMCS_GUEST_GS_ACCESS_RIGHTS));
            this->dump("ldtr_access_rights ", m_intrinsic->vmread32_quiet(VMCS_GUEST_LDTR_ACCESS_RIGHTS));
            this->dump("tr_access_rights ", m_intrinsic->vmread32_quiet(VMCS_GUEST_TR_ACCESS_RIGHTS));
            this->dump("guest_interruptibility_state ", m_intrinsic->vmread32_quiet(VMCS_GUEST_INTERRUPTIBILITY_STATE));
            this->dump("guest_activity_state ", m_intrinsic->vmread32_quiet(VMCS_GUEST_ACTIVITY_STATE));
            this->dump("guest_smbase ", m_intrinsic->vmread32_quiet(VMCS_GUEST_SMBASE));
            this->dump("ia32_sysenter_cs ", m_intrinsic->vmread32_quiet(VMCS_GUEST_IA32_SYSENTER_CS));
            this->dump("vmx_preemption_timer_value ", m_intrinsic->vmread32_quiet(VMCS_VMX_PREEMPTION_TIMER_VALUE));

            /// Natural-Width Control Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("cr0_guest_host_mask ", m_intrinsic->vmread64_quiet(VMCS_CR0_GUEST_HOST_MASK));
            this->dump("cr4_guest_host_mask ", m_intrinsic->vmread64_quiet(VMCS_CR4_GUEST_HOST_MASK));
            this->dump("cr0_read_shadow ", m_intrinsic->vmread64_quiet(VMCS_CR0_READ_SHADOW));
            this->dump("cr4_read_shadow ", m_intrinsic->vmread64_quiet(VMCS_CR4_READ_SHADOW));
            this->dump("cr3_target_value0 ", m_intrinsic->vmread64_quiet(VMCS_CR3_TARGET_VALUE0));
            this->dump("cr3_target_value1 ", m_intrinsic->vmread64_quiet(VMCS_CR3_TARGET_VALUE1));
            this->dump("cr3_target_value2 ", m_intrinsic->vmread64_quiet(VMCS_CR3_TARGET_VALUE2));
            this->dump("cr3_target_value3 ", m_intrinsic->vmread64_quiet(VMCS_CR3_TARGET_VALUE3));

            /// Natural-Width Read-Only Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("exit_qualification ", m_intrinsic->vmread64_quiet(VMCS_EXIT_QUALIFICATION));
            this->dump("io_rcx ", m_intrinsic->vmread64_quiet(VMCS_IO_RCX));
            this->dump("io_rsi ", m_intrinsic->vmread64_quiet(VMCS_IO_RSI));
            this->dump("io_rdi ", m_intrinsic->vmread64_quiet(VMCS_IO_RDI));
            this->dump("io_rip ", m_intrinsic->vmread64_quiet(VMCS_IO_RIP));
            this->dump("guest_linear_address ", m_intrinsic->vmread64_quiet(VMCS_GUEST_LINEAR_ADDRESS));

            /// Natural-Width Guest Fields
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            this->dump("cr0 ", m_intrinsic->vmread64_quiet(VMCS_GUEST_CR0));
            this->dump("cr2 ", bsl::make_safe(m_vmcs_missing_registers.cr2));
            this->dump("cr3 ", m_intrinsic->vmread64_quiet(VMCS_GUEST_CR3));
            this->dump("cr4 ", m_intrinsic->vmread64_quiet(VMCS_GUEST_CR4));
            this->dump("es_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_ES_BASE));
            this->dump("cs_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_CS_BASE));
            this->dump("ss_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_SS_BASE));
            this->dump("ds_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_DS_BASE));
            this->dump("fs_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_FS_BASE));
            this->dump("gs_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_GS_BASE));
            this->dump("ldtr_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_LDTR_BASE));
            this->dump("tr_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_TR_BASE));
            this->dump("gdtr_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_GDTR_BASE));
            this->dump("idtr_base ", m_intrinsic->vmread64_quiet(VMCS_GUEST_IDTR_BASE));
            this->dump("dr6 ", bsl::make_safe(m_vmcs_missing_registers.dr6));
            this->dump("dr7 ", m_intrinsic->vmread64_quiet(VMCS_GUEST_DR7));
            this->dump("rsp ", m_intrinsic->vmread64_quiet(VMCS_GUEST_RSP));
            this->dump("rip ", m_intrinsic->vmread64_quiet(VMCS_GUEST_RIP));
            this->dump("rflags ", m_intrinsic->vmread64_quiet(VMCS_GUEST_RFLAGS));
            this->dump("guest_pending_debug_exceptions ", m_intrinsic->vmread64_quiet(VMCS_GUEST_PENDING_DEBUG_EXCEPTIONS));
            this->dump("ia32_sysenter_esp ", m_intrinsic->vmread64_quiet(VMCS_GUEST_IA32_SYSENTER_ESP));
            this->dump("ia32_sysenter_eip ", m_intrinsic->vmread64_quiet(VMCS_GUEST_IA32_SYSENTER_EIP));

            /// Footer
            ///

            bsl::print() << bsl::ylw << "+--------------------------------------------------------------+";
            bsl::print() << bsl::rst << bsl::endl;

            // clang-format on
        }
    };
}

#endif
