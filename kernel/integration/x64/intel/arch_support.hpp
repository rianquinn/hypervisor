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

#ifndef ARCH_SUPPORT_HPP
#define ARCH_SUPPORT_HPP

#include <bf_constants.hpp>

#include <bsl/convert.hpp>
#include <bsl/debug.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace integration
{
    /// @brief stores the MSR bitmap used by this extension
    inline void *g_msr_bitmaps{};
    /// @brief stores the physical address of the MSR bitmap
    inline bsl::safe_uintmax g_msr_bitmaps_phys{};

    /// <!-- description -->
    ///   @brief Initializes a VPS with architecture specific stuff.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle the handle to use
    ///   @param vpsid the VPS being intialized
    ///   @return Returns bsl::errc_success on success and bsl::errc_failure
    ///     on failure.
    ///
    [[nodiscard]] constexpr auto
    init_vps(syscall::bf_handle_t &handle, bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
    {
        bsl::errc_type ret{};

        /// NOTE:
        /// - Set up VPID
        ///

        constexpr bsl::safe_uintmax vmcs_vpid_idx{bsl::to_umax(0x0000U)};
        constexpr bsl::safe_uint16 vmcs_vpid_val{bsl::to_u16(0x1)};

        ret = syscall::bf_vps_op_write16(handle, vpsid, vmcs_vpid_idx, vmcs_vpid_val);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Set up the VMCS link pointer
        ///

        constexpr bsl::safe_uintmax vmcs_link_ptr_idx{bsl::to_umax(0x2800U)};
        constexpr bsl::safe_uintmax vmcs_link_ptr_val{bsl::to_umax(0xFFFFFFFFFFFFFFFFU)};

        ret = syscall::bf_vps_op_write64(handle, vpsid, vmcs_link_ptr_idx, vmcs_link_ptr_val);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Set up the VMCS pin based, proc based, exit and entry controls
        /// - We turn on MSR bitmaps so that we do not trap on MSR reads and
        ///   writes. If you do not configure this, or you use the bitmap
        ///   to trap to specific MSR accesses, make sure you keep the VMCS
        ///   in sync with your MSR mods. Any MSR that is in the VMCS also
        ///   needs to be written to the VMCS, otherwise, VMEntry/VMExit will
        ///   replace any values you write.
        /// - We also turn on secondary controls so that we can turn on VPID,
        ///   and turn on instructions that the OS is relying on, like
        ///   RDTSCP. Failure to do this will cause the invalid opcodes to
        ///   occur.
        /// - The lambda below performs the MSR conversion of the CTLS
        ///   registers to determine the bits that must always be set to 1,
        ///   and the bits that must always be set to 0. This allows us to
        ///   turn on as much as possible, letting the MSRs decide what is
        ///   allowed and what is not.
        /// - Also note that we do not attempt to detect support for the
        ///   secondary controls. This is because the loader ensures that
        ///   this support is present as it is a minimum requirement for the
        ///   project.
        ///

        constexpr bsl::safe_uintmax vmcs_pinbased_ctls_idx{bsl::to_umax(0x4000U)};
        constexpr bsl::safe_uintmax vmcs_procbased_ctls_idx{bsl::to_umax(0x4002U)};
        constexpr bsl::safe_uintmax vmcs_exit_ctls_idx{bsl::to_umax(0x400CU)};
        constexpr bsl::safe_uintmax vmcs_entry_ctls_idx{bsl::to_umax(0x4012U)};
        constexpr bsl::safe_uintmax vmcs_procbased_ctls2_idx{bsl::to_umax(0x401EU)};

        constexpr bsl::safe_uint32 ia32_vmx_true_pinbased_ctls{bsl::to_u32(0x48DU)};
        constexpr bsl::safe_uint32 ia32_vmx_true_procbased_ctls{bsl::to_u32(0x48EU)};
        constexpr bsl::safe_uint32 ia32_vmx_true_exit_ctls{bsl::to_u32(0x48FU)};
        constexpr bsl::safe_uint32 ia32_vmx_true_entry_ctls{bsl::to_u32(0x490U)};
        constexpr bsl::safe_uint32 ia32_vmx_true_procbased_ctls2{bsl::to_u32(0x48BU)};

        bsl::safe_uintmax ctls{};

        auto mask = [](bsl::safe_uintmax const &val) noexcept -> bsl::safe_uint32 {
            constexpr bsl::safe_uintmax ctls_mask{bsl::to_umax(0x00000000FFFFFFFFU)};
            constexpr bsl::safe_uintmax ctls_shift{bsl::to_umax(32)};
            return bsl::to_u32_unsafe((val & ctls_mask) & (val >> ctls_shift));
        };

        /// NOTE:
        /// - Configure the pin based controls
        ///

        ret = syscall::bf_intrinsic_op_rdmsr(handle, ia32_vmx_true_pinbased_ctls, ctls);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        ret = syscall::bf_vps_op_write32(handle, vpsid, vmcs_pinbased_ctls_idx, mask(ctls));
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Configure the proc based controls
        ///

        constexpr bsl::safe_uintmax enable_msr_bitmaps{bsl::to_umax(0x10000000U)};
        constexpr bsl::safe_uintmax enable_procbased_ctls2{bsl::to_umax(0x80000000U)};

        ret = syscall::bf_intrinsic_op_rdmsr(handle, ia32_vmx_true_procbased_ctls, ctls);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        ctls |= enable_msr_bitmaps;
        ctls |= enable_procbased_ctls2;

        ret = syscall::bf_vps_op_write32(handle, vpsid, vmcs_procbased_ctls_idx, mask(ctls));
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Configure the exit controls
        ///

        ret = syscall::bf_intrinsic_op_rdmsr(handle, ia32_vmx_true_exit_ctls, ctls);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        ret = syscall::bf_vps_op_write32(handle, vpsid, vmcs_exit_ctls_idx, mask(ctls));
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Configure the entry controls
        ///

        ret = syscall::bf_intrinsic_op_rdmsr(handle, ia32_vmx_true_entry_ctls, ctls);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        ret = syscall::bf_vps_op_write32(handle, vpsid, vmcs_entry_ctls_idx, mask(ctls));
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Configure the secondary proc controls.
        ///

        constexpr bsl::safe_uintmax enable_vpid{bsl::to_umax(0x00000020U)};
        constexpr bsl::safe_uintmax enable_rdtscp{bsl::to_umax(0x00000008U)};
        constexpr bsl::safe_uintmax enable_invpcid{bsl::to_umax(0x00001000U)};
        constexpr bsl::safe_uintmax enable_xsave{bsl::to_umax(0x00100000U)};
        constexpr bsl::safe_uintmax enable_uwait{bsl::to_umax(0x04000000U)};

        ret = syscall::bf_intrinsic_op_rdmsr(handle, ia32_vmx_true_procbased_ctls2, ctls);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        ctls |= enable_vpid;
        ctls |= enable_rdtscp;
        ctls |= enable_invpcid;
        ctls |= enable_xsave;
        ctls |= enable_uwait;

        ret = syscall::bf_vps_op_write32(handle, vpsid, vmcs_procbased_ctls2_idx, mask(ctls));
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Configure the MSR bitmaps. This ensures that we do not trap
        ///   on MSR reads and writes. Also note that in most applications,
        ///   you only need one of these, regardless of the total number of
        ///   CPUs you are running on.
        ///

        constexpr bsl::safe_uintmax vmcs_msr_bitmaps{bsl::to_umax(0x2004U)};

        if (nullptr == g_msr_bitmaps) {
            ret = syscall::bf_mem_op_alloc_page(handle, g_msr_bitmaps, g_msr_bitmaps_phys);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }
        }

        ret = syscall::bf_vps_op_write64(handle, vpsid, vmcs_msr_bitmaps, g_msr_bitmaps_phys);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        /// NOTE:
        /// - Report success. Specifically, when we return to the root OS,
        ///   setting RAX tells the loader that the hypervisor was successfully
        ///   set up.
        ///

        ret = syscall::bf_vps_op_write_reg(
            handle, vpsid, syscall::bf_reg_t::bf_reg_t_rax, bsl::ZERO_UMAX);
        if (bsl::unlikely(!ret)) {
            bsl::print<bsl::V>() << bsl::here();
            return ret;
        }

        return ret;
    }
}

#endif
