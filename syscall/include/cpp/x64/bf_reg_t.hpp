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

#ifndef BF_REG_T_HPP
#define BF_REG_T_HPP

#include <bsl/cstdint.hpp>

namespace syscall
{
    /// @brief Defines which register is being requested by certain syscalls
    enum class bf_reg_t : bsl::uint64
    {
        /// @brief defines the rax register
        bf_reg_t_rax = static_cast<bsl::uint64>(0),
        /// @brief defines the rbx register
        bf_reg_t_rbx = static_cast<bsl::uint64>(1),
        /// @brief defines the rcx register
        bf_reg_t_rcx = static_cast<bsl::uint64>(2),
        /// @brief defines the rdx register
        bf_reg_t_rdx = static_cast<bsl::uint64>(3),
        /// @brief defines the rbp register
        bf_reg_t_rbp = static_cast<bsl::uint64>(4),
        /// @brief defines the rsi register
        bf_reg_t_rsi = static_cast<bsl::uint64>(5),
        /// @brief defines the rdi register
        bf_reg_t_rdi = static_cast<bsl::uint64>(6),
        /// @brief defines the r8 register
        bf_reg_t_r8 = static_cast<bsl::uint64>(7),
        /// @brief defines the r9 register
        bf_reg_t_r9 = static_cast<bsl::uint64>(8),
        /// @brief defines the r10 register
        bf_reg_t_r10 = static_cast<bsl::uint64>(9),
        /// @brief defines the r11 register
        bf_reg_t_r11 = static_cast<bsl::uint64>(10),
        /// @brief defines the r12 register
        bf_reg_t_r12 = static_cast<bsl::uint64>(11),
        /// @brief defines the r13 register
        bf_reg_t_r13 = static_cast<bsl::uint64>(12),
        /// @brief defines the r14 register
        bf_reg_t_r14 = static_cast<bsl::uint64>(13),
        /// @brief defines the r15 register
        bf_reg_t_r15 = static_cast<bsl::uint64>(14),
        /// @brief defines the rip register
        bf_reg_t_rip = static_cast<bsl::uint64>(15),
        /// @brief defines the rsp register
        bf_reg_t_rsp = static_cast<bsl::uint64>(16),
        /// @brief defines the rflags register
        bf_reg_t_rflags = static_cast<bsl::uint64>(17),
        /// @brief defines the gdtr_base_addr register
        bf_reg_t_gdtr_base_addr = static_cast<bsl::uint64>(18),
        /// @brief defines the gdtr_limit register
        bf_reg_t_gdtr_limit = static_cast<bsl::uint64>(19),
        /// @brief defines the idtr_base_addr register
        bf_reg_t_idtr_base_addr = static_cast<bsl::uint64>(20),
        /// @brief defines the idtr_limit register
        bf_reg_t_idtr_limit = static_cast<bsl::uint64>(21),
        /// @brief defines the es register
        bf_reg_t_es = static_cast<bsl::uint64>(22),
        /// @brief defines the es_base_addr register
        bf_reg_t_es_base_addr = static_cast<bsl::uint64>(23),
        /// @brief defines the es_limit register
        bf_reg_t_es_limit = static_cast<bsl::uint64>(24),
        /// @brief defines the es_attributes register
        bf_reg_t_es_attributes = static_cast<bsl::uint64>(25),
        /// @brief defines the cs register
        bf_reg_t_cs = static_cast<bsl::uint64>(26),
        /// @brief defines the cs_base_addr register
        bf_reg_t_cs_base_addr = static_cast<bsl::uint64>(27),
        /// @brief defines the cs_limit register
        bf_reg_t_cs_limit = static_cast<bsl::uint64>(28),
        /// @brief defines the cs_attributes register
        bf_reg_t_cs_attributes = static_cast<bsl::uint64>(29),
        /// @brief defines the ss register
        bf_reg_t_ss = static_cast<bsl::uint64>(30),
        /// @brief defines the ss_base_addr register
        bf_reg_t_ss_base_addr = static_cast<bsl::uint64>(31),
        /// @brief defines the ss_limit register
        bf_reg_t_ss_limit = static_cast<bsl::uint64>(32),
        /// @brief defines the ss_attributes register
        bf_reg_t_ss_attributes = static_cast<bsl::uint64>(33),
        /// @brief defines the ds register
        bf_reg_t_ds = static_cast<bsl::uint64>(34),
        /// @brief defines the ds_base_addr register
        bf_reg_t_ds_base_addr = static_cast<bsl::uint64>(35),
        /// @brief defines the ds_limit register
        bf_reg_t_ds_limit = static_cast<bsl::uint64>(36),
        /// @brief defines the ds_attributes register
        bf_reg_t_ds_attributes = static_cast<bsl::uint64>(37),
        /// @brief defines the fs register
        bf_reg_t_fs = static_cast<bsl::uint64>(38),
        /// @brief defines the fs_base_addr register
        bf_reg_t_fs_base_addr = static_cast<bsl::uint64>(39),
        /// @brief defines the fs_limit register
        bf_reg_t_fs_limit = static_cast<bsl::uint64>(40),
        /// @brief defines the fs_attributes register
        bf_reg_t_fs_attributes = static_cast<bsl::uint64>(41),
        /// @brief defines the gs register
        bf_reg_t_gs = static_cast<bsl::uint64>(42),
        /// @brief defines the gs_base_addr register
        bf_reg_t_gs_base_addr = static_cast<bsl::uint64>(43),
        /// @brief defines the gs_limit register
        bf_reg_t_gs_limit = static_cast<bsl::uint64>(44),
        /// @brief defines the gs_attributes register
        bf_reg_t_gs_attributes = static_cast<bsl::uint64>(45),
        /// @brief defines the ldtr register
        bf_reg_t_ldtr = static_cast<bsl::uint64>(46),
        /// @brief defines the ldtr_base_addr register
        // We don't have a choice in the naming here
        // NOLINTNEXTLINE(bsl-identifier-typographically-unambiguous)
        bf_reg_t_ldtr_base_addr = static_cast<bsl::uint64>(47),
        /// @brief defines the ldtr_limit register
        // We don't have a choice in the naming here
        // NOLINTNEXTLINE(bsl-identifier-typographically-unambiguous)
        bf_reg_t_ldtr_limit = static_cast<bsl::uint64>(48),
        /// @brief defines the ldtr_attributes register
        bf_reg_t_ldtr_attributes = static_cast<bsl::uint64>(49),
        /// @brief defines the tr register
        bf_reg_t_tr = static_cast<bsl::uint64>(50),
        /// @brief defines the tr_base_addr register
        bf_reg_t_tr_base_addr = static_cast<bsl::uint64>(51),
        /// @brief defines the tr_limit register
        bf_reg_t_tr_limit = static_cast<bsl::uint64>(52),
        /// @brief defines the tr_attributes register
        bf_reg_t_tr_attributes = static_cast<bsl::uint64>(53),
        /// @brief defines the cr0 register
        bf_reg_t_cr0 = static_cast<bsl::uint64>(54),
        /// @brief defines the cr2 register
        bf_reg_t_cr2 = static_cast<bsl::uint64>(55),
        /// @brief defines the cr3 register
        bf_reg_t_cr3 = static_cast<bsl::uint64>(56),
        /// @brief defines the cr4 register
        bf_reg_t_cr4 = static_cast<bsl::uint64>(57),
        /// @brief defines the dr6 register
        bf_reg_t_dr6 = static_cast<bsl::uint64>(58),
        /// @brief defines the dr7 register
        bf_reg_t_dr7 = static_cast<bsl::uint64>(59),
        /// @brief defines the ia32_efer register
        bf_reg_t_ia32_efer = static_cast<bsl::uint64>(60),
        /// @brief defines the ia32_star register
        bf_reg_t_ia32_star = static_cast<bsl::uint64>(61),
        /// @brief defines the ia32_lstar register
        bf_reg_t_ia32_lstar = static_cast<bsl::uint64>(62),
        /// @brief defines the ia32_cstar register
        bf_reg_t_ia32_cstar = static_cast<bsl::uint64>(63),
        /// @brief defines the ia32_fmask register
        bf_reg_t_ia32_fmask = static_cast<bsl::uint64>(64),
        /// @brief defines the ia32_fs_base register
        bf_reg_t_ia32_fs_base = static_cast<bsl::uint64>(65),
        /// @brief defines the ia32_gs_base register
        bf_reg_t_ia32_gs_base = static_cast<bsl::uint64>(66),
        /// @brief defines the ia32_kernel_gs_base register
        bf_reg_t_ia32_kernel_gs_base = static_cast<bsl::uint64>(67),
        /// @brief defines the ia32_sysenter_cs register
        bf_reg_t_ia32_sysenter_cs = static_cast<bsl::uint64>(68),
        /// @brief defines the ia32_sysenter_esp register
        bf_reg_t_ia32_sysenter_esp = static_cast<bsl::uint64>(69),
        /// @brief defines the ia32_sysenter_eip register
        bf_reg_t_ia32_sysenter_eip = static_cast<bsl::uint64>(70),
        /// @brief defines the ia32_pat register
        bf_reg_t_ia32_pat = static_cast<bsl::uint64>(71),
        /// @brief defines the ia32_debugctl register
        bf_reg_t_ia32_debugctl = static_cast<bsl::uint64>(72),
    };
}

#endif
