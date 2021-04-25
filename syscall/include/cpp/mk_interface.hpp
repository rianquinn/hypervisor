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

#ifndef MK_INTERFACE_H
#define MK_INTERFACE_H

#include <bsl/char_type.hpp>
#include <bsl/convert.hpp>
#include <bsl/cstdint.hpp>
#include <bsl/cstr_type.hpp>
#include <bsl/discard.hpp>
#include <bsl/disjunction.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/is_standard_layout.hpp>
#include <bsl/is_void.hpp>
#include <bsl/likely.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace syscall
{
    // -------------------------------------------------------------------------
    // Scalar Types
    // -------------------------------------------------------------------------

    /// @brief Defines the type used for returning status from a function
    using bf_status_t = bsl::safe_uint64;
    /// @brief Defines an unsigned 8bit integer
    using bf_uint8_t = bsl::uint8;
    /// @brief Defines an unsigned 16bit integer
    using bf_uint16_t = bsl::uint16;
    /// @brief Defines an unsigned 32bit integer
    using bf_uint32_t = bsl::uint32;
    /// @brief Defines an unsigned 64bit integer
    using bf_uint64_t = bsl::uint64;
    /// @brief Defines a raw pointer type
    using bf_ptr_t = void *;
    /// @brief Defines a raw const pointer type
    using bf_cptr_t = void const *;

    // -------------------------------------------------------------------------
    // Handle Type
    // -------------------------------------------------------------------------

    /// @class syscall::bf_handle_t
    ///
    /// <!-- description -->
    ///   @brief The bf_handle_t structure is an opaque structure containing
    ///     the handle that is used by most of the syscalls in this
    ///     specification. The opaque structure is used internally by the C
    ///     wrapper interface for storing state as needed and should not be
    ///     accessed directly. The C wrapper is allowed to redefine the
    ///     internal layout of this structure at any time (e.g., the C wrapper
    ///     might provide an alternative layout for unit testing).
    ///
    // IWYU is more important here, and this rule would make this interface
    // needlessly overcomplicated.
    // NOLINTNEXTLINE(bsl-user-defined-type-names-match-header-name)
    struct bf_handle_t final
    {
        /// @brief The handle returned by bf_handle_op_open_handle
        bf_uint64_t hndl;
    };

    // -------------------------------------------------------------------------
    // Register Type
    // -------------------------------------------------------------------------

    /// @brief Defines which register is being requested by certain syscalls
    // IWYU is more important here, and this rule would make this interface
    // needlessly overcomplicated.
    // NOLINTNEXTLINE(bsl-user-defined-type-names-match-header-name)
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

    // -------------------------------------------------------------------------
    // Exit Type
    // -------------------------------------------------------------------------

    /// @brief Defines the exit type used by bf_control_op_exit
    // IWYU is more important here, and this rule would make this interface
    // needlessly overcomplicated.
    // NOLINTNEXTLINE(bsl-user-defined-type-names-match-header-name)
    enum class bf_exit_status_t : bsl::uint64
    {
        /// @brief Exit with a success code
        success = static_cast<bsl::uint64>(0),
        /// @brief Exit with a failure code
        failure = static_cast<bsl::uint64>(1)
    };

    // -------------------------------------------------------------------------
    // Bootstrap Callback Handler Type
    // -------------------------------------------------------------------------

    /// @brief Defines the signature of the bootstrap callback handler
    // Entry points cannot use safe integral types
    // NOLINTNEXTLINE(bsl-non-safe-integral-types-are-forbidden)
    using bf_callback_handler_bootstrap_t = void (*)(bsl::uint16);

    // -------------------------------------------------------------------------
    // VMExit Callback Handler Type
    // -------------------------------------------------------------------------

    /// @brief Defines the signature of the VM exit callback handler
    // Entry points cannot use safe integral types
    // NOLINTNEXTLINE(bsl-non-safe-integral-types-are-forbidden)
    using bf_callback_handler_vmexit_t = void (*)(bsl::uint16, bsl::uint64);

    // -------------------------------------------------------------------------
    // Fast Fail Callback Handler Type
    // -------------------------------------------------------------------------

    /// @brief Defines the signature of the fast fail callback handler
    // Entry points cannot use safe integral types
    // NOLINTNEXTLINE(bsl-non-safe-integral-types-are-forbidden)
    using bf_callback_handler_fail_t = void (*)(bf_status_t::value_type);

    // -------------------------------------------------------------------------
    // Special IDs
    // -------------------------------------------------------------------------

    /// @brief Defines an invalid ID for an extension, VM, VP and VPS
    constexpr bsl::safe_uint16 BF_INVALID_ID{bsl::to_u16(0xFFFFU)};

    /// @brief Defines the bootstrap physical processor ID
    constexpr bsl::safe_uint16 BF_BS_PPID{bsl::to_u16(0x0U)};

    /// @brief Defines the root virtual machine ID
    constexpr bsl::safe_uint16 BF_ROOT_VMID{bsl::to_u16(0x0U)};

    // -------------------------------------------------------------------------
    // Syscall Status Codes
    // -------------------------------------------------------------------------

    /// @brief Defines a mask for BF_STATUS_SIG
    constexpr bsl::safe_uint64 BF_STATUS_SIG_MASK{bsl::to_u64(0xFFFF000000000000U)};
    /// @brief Defines a mask for BF_STATUS_FLAGS
    constexpr bsl::safe_uint64 BF_STATUS_FLAGS_MASK{bsl::to_u64(0x0000FFFFFFFF0000U)};
    /// @brief Defines a mask for BF_STATUS_VALUE
    constexpr bsl::safe_uint64 BF_STATUS_VALUE_MASK{bsl::to_u64(0x000000000000FFFFU)};

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param status n/a
    ///   @return n/a
    ///
    [[nodiscard]] inline auto
    bf_status_sig(bsl::safe_uint64 const &status) noexcept -> bsl::safe_uint64
    {
        return status & BF_STATUS_SIG_MASK;
    }

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param status n/a
    ///   @return n/a
    ///
    [[nodiscard]] inline auto
    bf_status_flags(bsl::safe_uint64 const &status) noexcept -> bsl::safe_uint64
    {
        return status & BF_STATUS_FLAGS_MASK;
    }

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param status n/a
    ///   @return n/a
    ///
    [[nodiscard]] inline auto
    bf_status_value(bsl::safe_uint64 const &status) noexcept -> bsl::safe_uint64
    {
        return status & BF_STATUS_VALUE_MASK;
    }

    /// @brief Used to indicated that the syscall returned successfully
    constexpr bsl::safe_uint64 BF_STATUS_SUCCESS{bsl::to_u64(0x0000000000000000U)};
    /// @brief Indicates an unknown error occurred
    constexpr bsl::safe_uint64 BF_STATUS_FAILURE_UNKNOWN{bsl::to_u64(0xDEAD000000010001U)};
    /// @brief Indicates the syscall is unsupported
    constexpr bsl::safe_uint64 BF_STATUS_FAILURE_INVALID_HANDLE{bsl::to_u64(0xDEAD000000020001U)};
    /// @brief Indicates the provided handle is invalid
    constexpr bsl::safe_uint64 BF_STATUS_FAILURE_UNSUPPORTED{bsl::to_u64(0xDEAD000000040001U)};
    /// @brief Indicates the extension is not allowed to execute this syscall
    constexpr bsl::safe_uint64 BF_STATUS_INVALID_PERM_EXT{bsl::to_u64(0xDEAD000000010002U)};
    /// @brief Indicates the policy engine denied the syscall
    constexpr bsl::safe_uint64 BF_STATUS_INVALID_PERM_DENIED{bsl::to_u64(0xDEAD000000020002U)};
    /// @brief Indicates param 0 is invalid
    constexpr bsl::safe_uint64 BF_STATUS_INVALID_PARAMS0{bsl::to_u64(0xDEAD000000010003U)};
    /// @brief Indicates param 1 is invalid
    constexpr bsl::safe_uint64 BF_STATUS_INVALID_PARAMS1{bsl::to_u64(0xDEAD000000020003U)};
    /// @brief Indicates param 2 is invalid
    constexpr bsl::safe_uint64 BF_STATUS_INVALID_PARAMS2{bsl::to_u64(0xDEAD000000040003U)};
    /// @brief Indicates param 3 is invalid
    constexpr bsl::safe_uint64 BF_STATUS_INVALID_PARAMS3{bsl::to_u64(0xDEAD000000080003U)};
    /// @brief Indicates param 4 is invalid
    constexpr bsl::safe_uint64 BF_STATUS_INVALID_PARAMS4{bsl::to_u64(0xDEAD000000100003U)};
    /// @brief Indicates param 5 is invalid
    constexpr bsl::safe_uint64 BF_STATUS_INVALID_PARAMS5{bsl::to_u64(0xDEAD000000200003U)};

    // -------------------------------------------------------------------------
    // Syscall Inputs
    // -------------------------------------------------------------------------

    /// @brief Defines the BF_SYSCALL_SIG field for RAX
    constexpr bsl::safe_uint64 BF_HYPERCALL_SIG_VAL{bsl::to_u64(0x6642000000000000U)};
    /// @brief Defines a mask for BF_SYSCALL_SIG
    constexpr bsl::safe_uint64 BF_HYPERCALL_SIG_MASK{bsl::to_u64(0xFFFF000000000000U)};
    /// @brief Defines a mask for BF_SYSCALL_FLAGS
    constexpr bsl::safe_uint64 BF_HYPERCALL_FLAGS_MASK{bsl::to_u64(0x0000FFFF00000000U)};
    /// @brief Defines a mask for BF_SYSCALL_OP
    constexpr bsl::safe_uint64 BF_HYPERCALL_OPCODE_MASK{bsl::to_u64(0xFFFF0000FFFF0000U)};
    /// @brief Defines a mask for BF_SYSCALL_OP (with no signature added)
    constexpr bsl::safe_uint64 BF_HYPERCALL_OPCODE_NOSIG_MASK{bsl::to_u64(0x00000000FFFF0000U)};
    /// @brief Defines a mask for BF_SYSCALL_IDX
    constexpr bsl::safe_uint64 BF_HYPERCALL_INDEX_MASK{bsl::to_u64(0x000000000000FFFFU)};

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param rax n/a
    ///   @return n/a
    ///
    [[nodiscard]] constexpr auto
    bf_syscall_sig(bsl::safe_uint64 const &rax) noexcept -> bsl::safe_uint64
    {
        return rax & BF_HYPERCALL_SIG_MASK;
    }

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param rax n/a
    ///   @return n/a
    ///
    [[nodiscard]] constexpr auto
    bf_syscall_flags(bsl::safe_uint64 const &rax) noexcept -> bsl::safe_uint64
    {
        return rax & BF_HYPERCALL_FLAGS_MASK;
    }

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param rax n/a
    ///   @return n/a
    ///
    [[nodiscard]] constexpr auto
    bf_syscall_opcode(bsl::safe_uint64 const &rax) noexcept -> bsl::safe_uint64
    {
        return rax & BF_HYPERCALL_OPCODE_MASK;
    }

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param rax n/a
    ///   @return n/a
    ///
    [[nodiscard]] constexpr auto
    bf_syscall_opcode_nosig(bsl::safe_uint64 const &rax) noexcept -> bsl::safe_uint64
    {
        return rax & BF_HYPERCALL_OPCODE_NOSIG_MASK;
    }

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param rax n/a
    ///   @return n/a
    ///
    [[nodiscard]] constexpr auto
    bf_syscall_index(bsl::safe_uint64 const &rax) noexcept -> bsl::safe_uint64
    {
        return rax & BF_HYPERCALL_INDEX_MASK;
    }

    // -------------------------------------------------------------------------
    // Specification IDs
    // -------------------------------------------------------------------------

    /// @brief Defines the ID for version #1 of this spec
    constexpr bsl::safe_uint32 BF_SPEC_ID1_VAL{bsl::to_u32(0x31236642)};

    /// @brief Defines the mask for checking support for version #1 of this spec
    constexpr bsl::safe_uint32 BF_SPEC_ID1_MASK{bsl::to_u32(0x2)};

    /// @brief Defines the value likely returned by bf_handle_op_version
    constexpr bsl::safe_uint32 BF_ALL_SPECS_SUPPORTED_VAL{bsl::to_u32(0x2)};

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param version n/a
    ///   @return n/a
    ///
    [[nodiscard]] constexpr auto
    bf_is_spec1_supported(bsl::safe_uint32 const &version) noexcept -> bool
    {
        return ((version & BF_SPEC_ID1_MASK) != bsl::ZERO_U32);
    }

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Control Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_control_op
    constexpr bsl::safe_uint64 BF_CONTROL_OP_VAL{bsl::to_u64(0x6642000000000000U)};
    /// @brief Defines the syscall opcode for bf_control_op (nosig)
    constexpr bsl::safe_uint64 BF_CONTROL_OP_NOSIG_VAL{bsl::to_u64(0x0000000000000000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Handle Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_handle_op
    constexpr bsl::safe_uint64 BF_HANDLE_OP_VAL{bsl::to_u64(0x6642000000010000U)};
    /// @brief Defines the syscall opcode for bf_handle_op (nosig)
    constexpr bsl::safe_uint64 BF_HANDLE_OP_NOSIG_VAL{bsl::to_u64(0x0000000000010000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Debug Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_debug_op
    constexpr bsl::safe_uint64 BF_DEBUG_OP_VAL{bsl::to_u64(0x6642000000020000U)};
    /// @brief Defines the syscall opcode for bf_debug_op (nosig)
    constexpr bsl::safe_uint64 BF_DEBUG_OP_NOSIG_VAL{bsl::to_u64(0x00000000000020000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Callback Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_callback_op
    constexpr bsl::safe_uint64 BF_CALLBACK_OP_VAL{bsl::to_u64(0x6642000000030000U)};
    /// @brief Defines the syscall opcode for bf_callback_op (nosig)
    constexpr bsl::safe_uint64 BF_CALLBACK_OP_NOSIG_VAL{bsl::to_u64(0x0000000000030000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - VM Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_vm_op
    constexpr bsl::safe_uint64 BF_VM_OP_VAL{bsl::to_u64(0x6642000000040000U)};
    /// @brief Defines the syscall opcode for bf_vm_op (nosig)
    constexpr bsl::safe_uint64 BF_VM_OP_NOSIG_VAL{bsl::to_u64(0x0000000000040000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - VP Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_vp_op
    constexpr bsl::safe_uint64 BF_VP_OP_VAL{bsl::to_u64(0x6642000000050000U)};
    /// @brief Defines the syscall opcode for bf_vp_op (nosig)
    constexpr bsl::safe_uint64 BF_VP_OP_NOSIG_VAL{bsl::to_u64(0x0000000000050000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - VPS Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_vps_op
    constexpr bsl::safe_uint64 BF_VPS_OP_VAL{bsl::to_u64(0x6642000000060000U)};
    /// @brief Defines the syscall opcode for bf_vps_op (nosig)
    constexpr bsl::safe_uint64 BF_VPS_OP_NOSIG_VAL{bsl::to_u64(0x0000000000060000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Intrinsic Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_intrinsic_op
    constexpr bsl::safe_uint64 BF_INTRINSIC_OP_VAL{bsl::to_u64(0x6642000000070000U)};
    /// @brief Defines the syscall opcode for bf_intrinsic_op (nosig)
    constexpr bsl::safe_uint64 BF_INTRINSIC_OP_NOSIG_VAL{bsl::to_u64(0x0000000000070000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Mem Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_mem_op
    constexpr bsl::safe_uint64 BF_MEM_OP_VAL{bsl::to_u64(0x6642000000080000U)};
    /// @brief Defines the syscall opcode for bf_mem_op (nosig)
    constexpr bsl::safe_uint64 BF_MEM_OP_NOSIG_VAL{bsl::to_u64(0x0000000000080000U)};

    // -------------------------------------------------------------------------
    // TLS Offsets
    // -------------------------------------------------------------------------

    /// @brief stores the offset for rax
    constexpr bsl::safe_uintmax TLS_OFFSET_RAX{bsl::to_umax(0x800U)};
    /// @brief stores the offset for rbx
    constexpr bsl::safe_uintmax TLS_OFFSET_RBX{bsl::to_umax(0x808U)};
    /// @brief stores the offset for rcx
    constexpr bsl::safe_uintmax TLS_OFFSET_RCX{bsl::to_umax(0x810U)};
    /// @brief stores the offset for rdx
    constexpr bsl::safe_uintmax TLS_OFFSET_RDX{bsl::to_umax(0x818U)};
    /// @brief stores the offset for rbp
    constexpr bsl::safe_uintmax TLS_OFFSET_RBP{bsl::to_umax(0x820U)};
    /// @brief stores the offset for rsi
    constexpr bsl::safe_uintmax TLS_OFFSET_RSI{bsl::to_umax(0x828U)};
    /// @brief stores the offset for rdi
    constexpr bsl::safe_uintmax TLS_OFFSET_RDI{bsl::to_umax(0x830U)};
    /// @brief stores the offset for r8
    constexpr bsl::safe_uintmax TLS_OFFSET_R8{bsl::to_umax(0x838U)};
    /// @brief stores the offset for r9
    constexpr bsl::safe_uintmax TLS_OFFSET_R9{bsl::to_umax(0x840U)};
    /// @brief stores the offset for r10
    constexpr bsl::safe_uintmax TLS_OFFSET_R10{bsl::to_umax(0x848U)};
    /// @brief stores the offset for r11
    constexpr bsl::safe_uintmax TLS_OFFSET_R11{bsl::to_umax(0x850U)};
    /// @brief stores the offset for r12
    constexpr bsl::safe_uintmax TLS_OFFSET_R12{bsl::to_umax(0x858U)};
    /// @brief stores the offset for r13
    constexpr bsl::safe_uintmax TLS_OFFSET_R13{bsl::to_umax(0x860U)};
    /// @brief stores the offset for r14
    constexpr bsl::safe_uintmax TLS_OFFSET_R14{bsl::to_umax(0x868U)};
    /// @brief stores the offset for r15
    constexpr bsl::safe_uintmax TLS_OFFSET_R15{bsl::to_umax(0x870U)};
    /// @brief stores the offset of the active extid
    constexpr bsl::safe_uintmax TLS_OFFSET_ACTIVE_EXTID{bsl::to_umax(0xFF0U)};
    /// @brief stores the offset of the active vmid
    constexpr bsl::safe_uintmax TLS_OFFSET_ACTIVE_VMID{bsl::to_umax(0xFF2U)};
    /// @brief stores the offset of the active vpid
    constexpr bsl::safe_uintmax TLS_OFFSET_ACTIVE_VPID{bsl::to_umax(0xFF4U)};
    /// @brief stores the offset of the active vpsid
    constexpr bsl::safe_uintmax TLS_OFFSET_ACTIVE_VPSID{bsl::to_umax(0xFF6U)};
    /// @brief stores the offset of the active ppid
    constexpr bsl::safe_uintmax TLS_OFFSET_ACTIVE_PPID{bsl::to_umax(0xFF8U)};
    /// @brief stores the number of PPs that are online
    constexpr bsl::safe_uintmax TLS_OFFSET_ONLINE_PPS{bsl::to_umax(0xFFAU)};

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rax.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rax_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rax.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rax_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rbx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rbx_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rbx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rbx_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rcx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rcx_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rcx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rcx_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rdx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rdx_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rdx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rdx_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rbp.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rbp_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rbp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rbp_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rsi.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rsi_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rsi.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rsi_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_rdi.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_rdi_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_rdi.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_rdi_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r8.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r8_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r8.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r8_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r9.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r9_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r9.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r9_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r10.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r10_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r10.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r10_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r11.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r11_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r11.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r11_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r12.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r12_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r12.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r12_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r13.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r13_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r13.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r13_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r14.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r14_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r14.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r14_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_r15.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_r15_impl() noexcept -> bf_uint64_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_set_r15.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val n/a
    ///
    extern "C" void bf_tls_set_r15_impl(bf_uint64_t const val) noexcept;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_extid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_extid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_vmid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_vmid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_vpid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_vpid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_vpsid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_vpsid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_ppid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_ppid_impl() noexcept -> bf_uint16_t;

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_tls_online_pps.
    ///
    /// <!-- inputs/outputs -->
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_tls_online_pps_impl() noexcept -> bf_uint16_t;

    // -------------------------------------------------------------------------
    // TLS
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Returns the value of tls.rax
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rax
    ///
    [[nodiscard]] inline auto
    bf_tls_rax(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_rax_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rax
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rax to
    ///
    inline void
    bf_tls_set_rax(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rax_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rbx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rbx
    ///
    [[nodiscard]] inline auto
    bf_tls_rbx(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_rbx_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rbx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rbx to
    ///
    inline void
    bf_tls_set_rbx(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rbx_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rcx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rcx
    ///
    [[nodiscard]] inline auto
    bf_tls_rcx(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_rcx_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rcx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rcx to
    ///
    inline void
    bf_tls_set_rcx(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rcx_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rdx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rdx
    ///
    [[nodiscard]] inline auto
    bf_tls_rdx(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_rdx_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rdx
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rdx to
    ///
    inline void
    bf_tls_set_rdx(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rdx_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rbp
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rbp
    ///
    [[nodiscard]] inline auto
    bf_tls_rbp(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_rbp_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rbp
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rbp to
    ///
    inline void
    bf_tls_set_rbp(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rbp_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rsi
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rsi
    ///
    [[nodiscard]] inline auto
    bf_tls_rsi(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_rsi_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rsi
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rsi to
    ///
    inline void
    bf_tls_set_rsi(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rsi_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.rdi
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.rdi
    ///
    [[nodiscard]] inline auto
    bf_tls_rdi(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_rdi_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.rdi
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.rdi to
    ///
    inline void
    bf_tls_set_rdi(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_rdi_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r8
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r8
    ///
    [[nodiscard]] inline auto
    bf_tls_r8(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_r8_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r8
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r8 to
    ///
    inline void
    bf_tls_set_r8(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r8_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r9
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r9
    ///
    [[nodiscard]] inline auto
    bf_tls_r9(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_r9_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r9
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r9 to
    ///
    inline void
    bf_tls_set_r9(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r9_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r10
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r10
    ///
    [[nodiscard]] inline auto
    bf_tls_r10(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_r10_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r10
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r10 to
    ///
    inline void
    bf_tls_set_r10(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r10_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r11
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r11
    ///
    [[nodiscard]] inline auto
    bf_tls_r11(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_r11_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r11
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r11 to
    ///
    inline void
    bf_tls_set_r11(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r11_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r12
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r12
    ///
    [[nodiscard]] inline auto
    bf_tls_r12(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_r12_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r12
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r12 to
    ///
    inline void
    bf_tls_set_r12(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r12_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r13
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r13
    ///
    [[nodiscard]] inline auto
    bf_tls_r13(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_r13_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r13
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r13 to
    ///
    inline void
    bf_tls_set_r13(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r13_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r14
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r14
    ///
    [[nodiscard]] inline auto
    bf_tls_r14(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_r14_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r14
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r14 to
    ///
    inline void
    bf_tls_set_r14(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r14_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.r15
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @return Returns the value of tls.r15
    ///
    [[nodiscard]] inline auto
    bf_tls_r15(bf_handle_t const &handle) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);
        return {bf_tls_r15_impl()};
    }

    /// <!-- description -->
    ///   @brief Sets the value of tls.r15
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle reserved for unit testing
    ///   @param val The value to set tls.r15 to
    ///
    inline void
    bf_tls_set_r15(bf_handle_t const &handle, bsl::safe_uintmax const &val) noexcept
    {
        bsl::discard(handle);
        bf_tls_set_r15_impl(val.get());
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.extid
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns the value of tls.extid
    ///
    [[nodiscard]] inline auto
    bf_tls_extid() noexcept -> bsl::safe_uint16
    {
        return {bf_tls_extid_impl()};
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.vmid
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns the value of tls.vmid
    ///
    [[nodiscard]] inline auto
    bf_tls_vmid() noexcept -> bsl::safe_uint16
    {
        return {bf_tls_vmid_impl()};
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.vpid
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns the value of tls.vpid
    ///
    [[nodiscard]] inline auto
    bf_tls_vpid() noexcept -> bsl::safe_uint16
    {
        return {bf_tls_vpid_impl()};
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.vpsid
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns the value of tls.vpsid
    ///
    [[nodiscard]] inline auto
    bf_tls_vpsid() noexcept -> bsl::safe_uint16
    {
        return {bf_tls_vpsid_impl()};
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.ppid
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns the value of tls.ppid
    ///
    [[nodiscard]] inline auto
    bf_tls_ppid() noexcept -> bsl::safe_uint16
    {
        return {bf_tls_ppid_impl()};
    }

    /// <!-- description -->
    ///   @brief Returns the value of tls.online_pps
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns the value of tls.online_pps
    ///
    [[nodiscard]] inline auto
    bf_tls_online_pps() noexcept -> bsl::safe_uint16
    {
        return {bf_tls_online_pps_impl()};
    }

    // -------------------------------------------------------------------------
    // bf_control_op_exit
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_control_op_exit.
    ///
    extern "C" void bf_control_op_exit_impl() noexcept;

    /// @brief Defines the syscall index for bf_control_op_exit
    constexpr bsl::safe_uint64 BF_CONTROL_OP_EXIT_IDX_VAL{bsl::to_u64(0x0000000000000000U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to exit the execution
    ///     of an extension, providing a means to fast fail.
    ///
    inline void
    bf_control_op_exit() noexcept
    {
        bf_control_op_exit_impl();
    }

    // -------------------------------------------------------------------------
    // bf_handle_op_open_handle
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_handle_op_open_handle.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_handle_op_open_handle_impl(    // --
        bf_uint32_t const reg0_in,                                  // --
        bf_uint64_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_handle_op_open_handle
    constexpr bsl::safe_uint64 BF_HANDLE_OP_OPEN_HANDLE_IDX_VAL{bsl::to_u64(0x0000000000000000U)};

    /// <!-- description -->
    ///   @brief This syscall returns a handle which is required to execute
    ///     the remaining syscalls. Some versions of Bareflank might provide
    ///     a certain degree of backwards compatibility which can be queried
    ///     using bf_handle_op_version. The version argument of this syscall
    ///     provides software with means to tell the microkernel which version
    ///     of this spec it is trying to use. If software provides a version
    ///     that Bareflank doesn't support (i.e., a version that is not listed
    ///     by bf_handle_op_version), this syscall will fail.
    ///
    /// <!-- inputs/outputs -->
    ///   @param version The version of this spec that software supports
    ///   @param handle The value to set REG0 to for most other syscalls
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_handle_op_open_handle(               // --
        bsl::safe_uint32 const &version,    // --
        bf_handle_t &handle) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_handle_op_open_handle_impl(version.get(), &handle.hndl)};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_handle_op_close_handle
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_handle_op_close_handle.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_handle_op_close_handle_impl(    // --
        bf_uint64_t const reg0_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_handle_op_close_handle
    constexpr bsl::safe_uint64 BF_HANDLE_OP_CLOSE_HANDLE_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// <!-- description -->
    ///   @brief This syscall closes a previously opened handle.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_handle_op_close_handle(    // --
        bf_handle_t &handle) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_handle_op_close_handle_impl(handle.hndl)};
        handle = {};

        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_out
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_out.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///
    extern "C" void bf_debug_op_out_impl(    // --
        bf_uint64_t const reg0_in,           // --
        bf_uint64_t const reg1_in) noexcept;

    /// @brief Defines the syscall index for bf_debug_op_out
    constexpr bsl::safe_uint64 BF_DEBUG_OP_OUT_IDX_VAL{bsl::to_u64(0x0000000000000000U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output RDI and RSI to
    ///     the console device the microkernel is currently using for
    ///     debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val1 The first value to output to the microkernel's console
    ///   @param val2 The second value to output to the microkernel's console
    ///
    inline void
    bf_debug_op_out(                     // --
        bsl::safe_uint64 const &val1,    // --
        bsl::safe_uint64 const &val2) noexcept
    {
        bf_debug_op_out_impl(val1.get(), val2.get());
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_dump_vm
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_vm.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void bf_debug_op_dump_vm_impl(    // --
        bf_uint16_t const reg0_in) noexcept;

    /// @brief Defines the syscall index for bf_debug_op_dump_vm
    constexpr bsl::safe_uint64 BF_DEBUG_OP_DUMP_VM_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the state of a
    ///     VM to the console device the microkernel is currently using for
    ///     debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vmid The VMID of the VM whose state is to be outputted
    ///
    inline void
    bf_debug_op_dump_vm(    // --
        bsl::safe_uint16 const &vmid) noexcept
    {
        bf_debug_op_dump_vm_impl(vmid.get());
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_dump_vp
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_vp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void bf_debug_op_dump_vp_impl(    // --
        bf_uint16_t const reg0_in) noexcept;

    /// @brief Defines the syscall index for bf_debug_op_dump_vp
    constexpr bsl::safe_uint64 BF_DEBUG_OP_DUMP_VP_IDX_VAL{bsl::to_u64(0x0000000000000002U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the state of a
    ///     VP to the console device the microkernel is currently using for
    ///     debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vpid The VPID of the VP whose state is to be outputted
    ///
    inline void
    bf_debug_op_dump_vp(    // --
        bsl::safe_uint16 const &vpid) noexcept
    {
        bf_debug_op_dump_vp_impl(vpid.get());
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_dump_vps
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_vps.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void bf_debug_op_dump_vps_impl(    // --
        bf_uint16_t const reg0_in) noexcept;

    /// @brief Defines the syscall index for bf_debug_op_dump_vps
    constexpr bsl::safe_uint64 BF_DEBUG_OP_DUMP_VPS_IDX_VAL{bsl::to_u64(0x0000000000000003U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the state of a
    ///     VPS to the console device the microkernel is currently using for
    ///     debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vpsid The VPSID of the VPS whose state is to be outputted
    ///
    inline void
    bf_debug_op_dump_vps(    // --
        bsl::safe_uint16 const &vpsid) noexcept
    {
        bf_debug_op_dump_vps_impl(vpsid.get());
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_dump_vmexit_log
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_vmexit_log.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void bf_debug_op_dump_vmexit_log_impl(    // --
        bf_uint16_t const reg0_in) noexcept;

    /// @brief Defines the syscall index for bf_debug_op_dump_vmexit_log
    constexpr bsl::safe_uint64 BF_DEBUG_OP_DUMP_VMEXIT_LOG_IDX_VAL{
        bsl::to_u64(0x0000000000000004U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the VMExit log.
    ///     The VMExit log is a chronological log of the "X" number of exits
    ///     that have occurred on a specific physical processor.
    ///
    /// <!-- inputs/outputs -->
    ///   @param ppid The PPID of the PP to dump the log from
    ///
    inline void
    bf_debug_op_dump_vmexit_log(    // --
        bsl::safe_uint16 const &ppid) noexcept
    {
        bf_debug_op_dump_vmexit_log_impl(ppid.get());
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_write_c
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_write_c.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void bf_debug_op_write_c_impl(    // --
        bsl::char_type const reg0_in) noexcept;

    /// @brief Defines the syscall index for bf_debug_op_write_c
    constexpr bsl::safe_uint64 BF_DEBUG_OP_WRITE_C_IDX_VAL{bsl::to_u64(0x0000000000000005U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output a provided
    ///     character to the microkernel's console.
    ///
    /// <!-- inputs/outputs -->
    ///   @param c The character to output
    ///
    inline void
    bf_debug_op_write_c(    // --
        bsl::char_type const c) noexcept
    {
        bf_debug_op_write_c_impl(c);
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_write_str
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_write_str.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void bf_debug_op_write_str_impl(    // --
        bsl::char_type const *const reg0_in) noexcept;

    /// @brief Defines the syscall index for bf_debug_op_write_str
    constexpr bsl::safe_uint64 BF_DEBUG_OP_WRITE_STR_IDX_VAL{bsl::to_u64(0x0000000000000006U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output a provided
    ///     string to the microkernel's console.
    ///
    /// <!-- inputs/outputs -->
    ///   @param str The virtual address of a null terminated string to output
    ///
    inline void
    bf_debug_op_write_str(    // --
        bsl::cstr_type const str) noexcept
    {
        bf_debug_op_write_str_impl(str);
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_dump_ext
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_ext.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void bf_debug_op_dump_ext_impl(    // --
        bf_uint16_t const reg0_in) noexcept;

    /// @brief Defines the syscall index for bf_debug_op_dump_ext
    constexpr bsl::safe_uint64 BF_DEBUG_OP_DUMP_EXT_IDX_VAL{bsl::to_u64(0x0000000000000007U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output an extension's
    ///     state to the console device the microkernel is currently using
    ///     for debugging.
    ///
    /// <!-- inputs/outputs -->
    ///   @param extid The EXTID of the extensions's state to output
    ///
    inline void
    bf_debug_op_dump_ext(    // --
        bsl::safe_uint16 const &extid) noexcept
    {
        bf_debug_op_dump_ext_impl(extid.get());
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_dump_page_pool
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_page_pool.
    ///
    extern "C" void bf_debug_op_dump_page_pool_impl() noexcept;

    /// @brief Defines the syscall index for bf_debug_op_dump_page_pool
    constexpr bsl::safe_uint64 BF_DEBUG_OP_DUMP_PAGE_POOL_IDX_VAL{bsl::to_u64(0x0000000000000008U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the page pool's
    ///     stats to the console device the microkernel is currently using
    ///     for debugging.
    ///
    inline void
    bf_debug_op_dump_page_pool() noexcept
    {
        bf_debug_op_dump_page_pool_impl();
    }

    // -------------------------------------------------------------------------
    // bf_debug_op_dump_huge_pool
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_dump_huge_pool.
    ///
    extern "C" void bf_debug_op_dump_huge_pool_impl() noexcept;

    /// @brief Defines the syscall index for bf_debug_op_dump_huge_pool
    constexpr bsl::safe_uint64 BF_DEBUG_OP_DUMP_HUGE_POOL_IDX_VAL{bsl::to_u64(0x0000000000000009U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to output the huge pool's
    ///     stats to the console device the microkernel is currently using
    ///     for debugging.
    ///
    inline void
    bf_debug_op_dump_huge_pool() noexcept
    {
        bf_debug_op_dump_huge_pool_impl();
    }

    // -------------------------------------------------------------------------
    // bf_callback_op_wait
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_callback_op_wait.
    ///
    extern "C" void bf_callback_op_wait_impl() noexcept;

    /// @brief Defines the syscall index for bf_callback_op_wait
    constexpr bsl::safe_uint64 BF_CALLBACK_OP_WAIT_IDX_VAL{bsl::to_u64(0x0000000000000000U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel that the extension would
    ///     like to wait for a callback. This is a blocking syscall that never
    ///     returns and should be used to return from the successful execution
    ///     of the _start function.
    ///
    inline void
    bf_callback_op_wait() noexcept
    {
        bf_callback_op_wait_impl();
    }

    // -------------------------------------------------------------------------
    // bf_callback_op_register_bootstrap
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_callback_op_register_bootstrap.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_callback_op_register_bootstrap_impl(    // --
        bf_uint64_t const reg0_in,                                           // --
        bf_callback_handler_bootstrap_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_callback_op_register_bootstrap
    constexpr bsl::safe_uint64 BF_CALLBACK_OP_REGISTER_BOOTSTRAP_IDX_VAL{
        bsl::to_u64(0x0000000000000002U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel that the extension would
    ///     like to receive callbacks for bootstrap events
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param handler Set to the virtual address of the callback
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_callback_op_register_bootstrap(    // --
        bf_handle_t const &handle,        // --
        bf_callback_handler_bootstrap_t const handler) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_callback_op_register_bootstrap_impl(handle.hndl, handler)};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_callback_op_register_vmexit
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_callback_op_register_vmexit.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_callback_op_register_vmexit_impl(    // --
        bf_uint64_t const reg0_in,                                        // --
        bf_callback_handler_vmexit_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_callback_op_register_vmexit
    constexpr bsl::safe_uint64 BF_CALLBACK_OP_REGISTER_VMEXIT_IDX_VAL{
        bsl::to_u64(0x0000000000000003U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel that the extension would
    ///     like to receive callbacks for VM exits
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param handler Set to the virtual address of the callback
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_callback_op_register_vmexit(    // --
        bf_handle_t const &handle,     // --
        bf_callback_handler_vmexit_t const handler) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_callback_op_register_vmexit_impl(handle.hndl, handler)};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_callback_op_register_fail
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_callback_op_register_fail.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_callback_op_register_fail_impl(    // --
        bf_uint64_t const reg0_in,                                      // --
        bf_callback_handler_fail_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_callback_op_register_fail
    constexpr bsl::safe_uint64 BF_CALLBACK_OP_REGISTER_FAIL_IDX_VAL{
        bsl::to_u64(0x0000000000000004U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel that the extension would
    ///     like to receive callbacks for fast fail events. If a fast fail
    ///     event occurs, something really bad has happened, and action must
    ///     be taken, or the physical processor will halt.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param handler Set to the virtual address of the callback
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_callback_op_register_fail(     // --
        bf_handle_t const &handle,    // --
        bf_callback_handler_fail_t const handler) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_callback_op_register_fail_impl(handle.hndl, handler)};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vm_op_create_vm
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vm_op_create_vm.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vm_op_create_vm_impl(    // --
        bf_uint64_t const reg0_in,                            // --
        bf_uint16_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vm_op_create_vm
    constexpr bsl::safe_uint64 BF_VM_OP_CREATE_VM_IDX_VAL{bsl::to_u64(0x0000000000000000U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to create a VM
    ///     and return it's ID.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vmid The resulting VMID of the newly created VM
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vm_op_create_vm(               // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 &vmid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vm_op_create_vm_impl(handle.hndl, vmid.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vm_op_destroy_vm
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vm_op_destroy_vm.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vm_op_destroy_vm_impl(    // --
        bf_uint64_t const reg0_in,                             // --
        bf_uint16_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vm_op_destroy_vm
    constexpr bsl::safe_uint64 BF_VM_OP_DESTROY_VM_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to destroy a VM
    ///     given an ID.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vmid The VMID of the VM to destroy
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vm_op_destroy_vm(              // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 const &vmid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vm_op_destroy_vm_impl(handle.hndl, vmid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vp_op_create_vp
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vp_op_create_vp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vp_op_create_vp_impl(    // --
        bf_uint64_t const reg0_in,                            // --
        bf_uint16_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vp_op_create_vp
    constexpr bsl::safe_uint64 BF_VP_OP_CREATE_VP_IDX_VAL{bsl::to_u64(0x0000000000000000U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to create a VP
    ///     and return it's ID.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpid The resulting VPID of the newly created VP
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vp_op_create_vp(               // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 &vpid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vp_op_create_vp_impl(handle.hndl, vpid.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vp_op_destroy_vp
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vp_op_destroy_vp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vp_op_destroy_vp_impl(    // --
        bf_uint64_t const reg0_in,                             // --
        bf_uint16_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vp_op_destroy_vp
    constexpr bsl::safe_uint64 BF_VP_OP_DESTROY_VP_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to destroy a VP
    ///     given an ID.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpid The VPID of the VP to destroy
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vp_op_destroy_vp(              // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 const &vpid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vp_op_destroy_vp_impl(handle.hndl, vpid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vp_op_migrate
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vp_op_migrate.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vp_op_migrate_impl(    // --
        bf_uint64_t const reg0_in,                          // --
        bf_uint16_t const reg1_in,                          // --
        bf_uint16_t const reg2_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vp_op_migrate
    constexpr bsl::safe_uint64 BF_VP_OP_MIGRATE_IDX_VAL{bsl::to_u64(0x0000000000000002U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to migrate a VP from one PP
    ///     to another PP. This function does not execute the VP (use
    ///     bf_vps_op_run for that), but instead allows bf_vps_op_run to
    ///     execute a VP on a PP that it was not originally assigned to.
    ///
    ///     When a VP is migrated, all of the VPSs that are assigned to the
    ///     requested VP are also migrated to this new PP as well. From an
    ///     AMD/Intel point of view, this clears the VMCS/VMCB for each VPS
    ///     assigned to the VP. On Intel, it also loads the newly cleared VPS
    ///     and sets the launched state to false, ensuring the next
    ///     bf_vps_op_run will use VMLaunch instead of VMResume.
    ///
    ///     It should be noted that the migration of a VPS from one PP to
    ///     another does not happen during the execution of this ABI. This
    ///     ABI simply tells the microkernel that the requested VP may now
    ///     execute on the requested PP. This will cause a mismatch between
    ///     the assigned PP for a VP and the assigned PP for a VPS. The
    ///     microkernel will detect this mismatch when an extension attempts
    ///     to execute bf_vps_op_run. When this occurs, the microkernel will
    ///     ensure the VP is being run on the PP it was assigned to during
    ///     migration, and then it will check to see if the PP of the VPS
    ///     matches. If it doesn't, it will then perform a migration of that
    ///     VPS at that time. This ensures that the microkernel is only
    ///     migrations VPSs when it needs to, and it ensures the VPS is
    ///     cleared an loaded (in the case of Intel) on the PP it will be
    ///     executed on, which is a requirement for VMCS migration. An
    ///     extension can determine which VPSs have been migrated by looking
    ///     at the assigned PP of a VPS. If it doesn't match the VP it was
    ///     assigned to, it has not been migrated. Finally, an extension is
    ///     free to read/write to the VPSs state, even if it has not been
    ///     migrated. The only requirement for migration is execution (meaning
    ///     VMRun/VMLaunch/VMResume).
    ///
    ///     Any additional migration responsibilities, like TSC
    ///     synchronization, must be performed by the extension.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpid The VPID of the VP to migrate
    ///   @param ppid The ID of the PP to assign the provided VP to
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vp_op_migrate(                 // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 const &vpid,
        bsl::safe_uint16 const &ppid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vp_op_migrate_impl(handle.hndl, vpid.get(), ppid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_create_vps
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_create_vps.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_create_vps_impl(    // --
        bf_uint64_t const reg0_in,                              // --
        bf_uint16_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_create_vps
    constexpr bsl::safe_uint64 BF_VPS_OP_CREATE_VPS_IDX_VAL{bsl::to_u64(0x0000000000000000U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to create a VPS
    ///     and return it's ID.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The resulting VPSID of the newly created VPS
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_create_vps(             // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 &vpsid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vps_op_create_vps_impl(handle.hndl, vpsid.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_destroy_vps
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_destroy_vps.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_destroy_vps_impl(    // --
        bf_uint64_t const reg0_in,                               // --
        bf_uint16_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_destroy_vps
    constexpr bsl::safe_uint64 BF_VPS_OP_DESTROY_VPS_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to destroy a VPS
    ///     given an ID.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to destroy
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_destroy_vps(            // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vps_op_destroy_vps_impl(handle.hndl, vpsid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_init_as_root
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_init_as_root.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_init_as_root_impl(    // --
        bf_uint64_t const reg0_in,                                // --
        bf_uint16_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_init_as_root
    constexpr bsl::safe_uint64 BF_VPS_OP_INIT_AS_ROOT_IDX_VAL{bsl::to_u64(0x0000000000000002U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to initialize a VPS using
    ///     the root VP state provided by the loader using the current PPID.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to initialize
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_init_as_root(           // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vps_op_init_as_root_impl(handle.hndl, vpsid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_read8
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read8.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_read8_impl(    // --
        bf_uint64_t const reg0_in,                         // --
        bf_uint16_t const reg1_in,                         // --
        bf_uint64_t const reg2_in,                         // --
        bf_uint8_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_read8
    constexpr bsl::safe_uint64 BF_VPS_OP_READ8_IDX_VAL{bsl::to_u64(0x0000000000000003U)};

    /// <!-- description -->
    ///   @brief Reads an 8bit field from the VPS and returns the value. The
    ///     "index" is architecture-specific. For Intel, Appendix B, "Field
    ///     Encoding in VMCS," defines the index (or encoding). For AMD,
    ///     Appendix B, "Layout of VMCB," defines the index (or offset).
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to read from
    ///   @param index The HVE specific index defining which field to read
    ///   @param value The resulting value
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_read8(                      // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bsl::safe_uint64 const &index,    // --
        bsl::safe_uint8 &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_read8_impl(handle.hndl, vpsid.get(), index.get(), value.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_read16
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read16.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_read16_impl(    // --
        bf_uint64_t const reg0_in,                          // --
        bf_uint16_t const reg1_in,                          // --
        bf_uint64_t const reg2_in,                          // --
        bf_uint16_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_read16
    constexpr bsl::safe_uint64 BF_VPS_OP_READ16_IDX_VAL{bsl::to_u64(0x0000000000000004U)};

    /// <!-- description -->
    ///   @brief Reads an 16bit field from the VPS and returns the value. The
    ///     "index" is architecture-specific. For Intel, Appendix B, "Field
    ///     Encoding in VMCS," defines the index (or encoding). For AMD,
    ///     Appendix B, "Layout of VMCB," defines the index (or offset).
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to read from
    ///   @param index The HVE specific index defining which field to read
    ///   @param value The resulting value
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_read16(                     // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bsl::safe_uint64 const &index,    // --
        bsl::safe_uint16 &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_read16_impl(handle.hndl, vpsid.get(), index.get(), value.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_read32
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read32.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_read32_impl(    // --
        bf_uint64_t const reg0_in,                          // --
        bf_uint16_t const reg1_in,                          // --
        bf_uint64_t const reg2_in,                          // --
        bf_uint32_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_read32
    constexpr bsl::safe_uint64 BF_VPS_OP_READ32_IDX_VAL{bsl::to_u64(0x0000000000000005U)};

    /// <!-- description -->
    ///   @brief Reads an 32bit field from the VPS and returns the value. The
    ///     "index" is architecture-specific. For Intel, Appendix B, "Field
    ///     Encoding in VMCS," defines the index (or encoding). For AMD,
    ///     Appendix B, "Layout of VMCB," defines the index (or offset).
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to read from
    ///   @param index The HVE specific index defining which field to read
    ///   @param value The resulting value
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_read32(                     // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bsl::safe_uint64 const &index,    // --
        bsl::safe_uint32 &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_read32_impl(handle.hndl, vpsid.get(), index.get(), value.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_read64
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read64.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_read64_impl(    // --
        bf_uint64_t const reg0_in,                          // --
        bf_uint16_t const reg1_in,                          // --
        bf_uint64_t const reg2_in,                          // --
        bf_uint64_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_read64
    constexpr bsl::safe_uint64 BF_VPS_OP_READ64_IDX_VAL{bsl::to_u64(0x0000000000000006U)};

    /// <!-- description -->
    ///   @brief Reads an 64bit field from the VPS and returns the value. The
    ///     "index" is architecture-specific. For Intel, Appendix B, "Field
    ///     Encoding in VMCS," defines the index (or encoding). For AMD,
    ///     Appendix B, "Layout of VMCB," defines the index (or offset).
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to read from
    ///   @param index The HVE specific index defining which field to read
    ///   @param value The resulting value
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_read64(                     // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bsl::safe_uint64 const &index,    // --
        bsl::safe_uint64 &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_read64_impl(handle.hndl, vpsid.get(), index.get(), value.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_write8
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write8.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_write8_impl(    // --
        bf_uint64_t const reg0_in,                          // --
        bf_uint16_t const reg1_in,                          // --
        bf_uint64_t const reg2_in,                          // --
        bf_uint8_t const reg3_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_write
    constexpr bsl::safe_uint64 BF_VPS_OP_WRITE8_IDX_VAL{bsl::to_u64(0x0000000000000007U)};

    /// <!-- description -->
    ///   @brief Writes to an 8bit field in the VPS. The "index" is
    ///     architecture-specific. For Intel, Appendix B, "Field Encoding in
    ///     VMCS," defines the index (or encoding). For AMD, Appendix B,
    ///     "Layout of VMCB," defines the index (or offset).
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to write to
    ///   @param index The HVE specific index defining which field to write to
    ///   @param value The value to write to the requested field
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_write8(                     // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bsl::safe_uint64 const &index,    // --
        bsl::safe_uint8 const &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_write8_impl(handle.hndl, vpsid.get(), index.get(), value.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_write16
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write16.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_write16_impl(    // --
        bf_uint64_t const reg0_in,                           // --
        bf_uint16_t const reg1_in,                           // --
        bf_uint64_t const reg2_in,                           // --
        bf_uint16_t const reg3_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_write
    constexpr bsl::safe_uint64 BF_VPS_OP_WRITE16_IDX_VAL{bsl::to_u64(0x0000000000000008U)};

    /// <!-- description -->
    ///   @brief Writes to an 16bit field in the VPS. The "index" is
    ///     architecture-specific. For Intel, Appendix B, "Field Encoding in
    ///     VMCS," defines the index (or encoding). For AMD, Appendix B,
    ///     "Layout of VMCB," defines the index (or offset).
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to write to
    ///   @param index The HVE specific index defining which field to write to
    ///   @param value The value to write to the requested field
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_write16(                    // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bsl::safe_uint64 const &index,    // --
        bsl::safe_uint16 const &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_write16_impl(handle.hndl, vpsid.get(), index.get(), value.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_write32
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write32.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_write32_impl(    // --
        bf_uint64_t const reg0_in,                           // --
        bf_uint16_t const reg1_in,                           // --
        bf_uint64_t const reg2_in,                           // --
        bf_uint32_t const reg3_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_write
    constexpr bsl::safe_uint64 BF_VPS_OP_WRITE32_IDX_VAL{bsl::to_u64(0x0000000000000009U)};

    /// <!-- description -->
    ///   @brief Writes to an 32bit field in the VPS. The "index" is
    ///     architecture-specific. For Intel, Appendix B, "Field Encoding in
    ///     VMCS," defines the index (or encoding). For AMD, Appendix B,
    ///     "Layout of VMCB," defines the index (or offset).
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to write to
    ///   @param index The HVE specific index defining which field to write to
    ///   @param value The value to write to the requested field
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_write32(                    // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bsl::safe_uint64 const &index,    // --
        bsl::safe_uint32 const &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_write32_impl(handle.hndl, vpsid.get(), index.get(), value.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_write64
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write64.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_write64_impl(    // --
        bf_uint64_t const reg0_in,                           // --
        bf_uint16_t const reg1_in,                           // --
        bf_uint64_t const reg2_in,                           // --
        bf_uint64_t const reg3_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_write
    constexpr bsl::safe_uint64 BF_VPS_OP_WRITE64_IDX_VAL{bsl::to_u64(0x000000000000000AU)};

    /// <!-- description -->
    ///   @brief Writes to an 64bit field in the VPS. The "index" is
    ///     architecture-specific. For Intel, Appendix B, "Field Encoding in
    ///     VMCS," defines the index (or encoding). For AMD, Appendix B,
    ///     "Layout of VMCB," defines the index (or offset).
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to write to
    ///   @param index The HVE specific index defining which field to write to
    ///   @param value The value to write to the requested field
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_write64(                    // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bsl::safe_uint64 const &index,    // --
        bsl::safe_uint64 const &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_write64_impl(handle.hndl, vpsid.get(), index.get(), value.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_read_reg
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_read_reg_impl.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_read_reg_impl(    // --
        bf_uint64_t const reg0_in,                            // --
        bf_uint16_t const reg1_in,                            // --
        bf_reg_t const reg2_in,                               // --
        bf_uint64_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_read_reg
    constexpr bsl::safe_uint64 BF_VPS_OP_READ_REG_IDX_VAL{bsl::to_u64(0x000000000000000BU)};

    /// <!-- description -->
    ///   @brief Reads a CPU register from the VPS given a bf_reg_t. Note
    ///     that the bf_reg_t is architecture specific.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to read from
    ///   @param reg A bf_reg_t defining which register to read
    ///   @param value The resulting value
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_read_reg(                   // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bf_reg_t const reg,               // --
        bsl::safe_uint64 &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_read_reg_impl(handle.hndl, vpsid.get(), reg, value.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_write_reg
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_write_reg.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_write_reg_impl(    // --
        bf_uint64_t const reg0_in,                             // --
        bf_uint16_t const reg1_in,                             // --
        bf_reg_t const reg2_in,                                // --
        bf_uint64_t const reg3_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_write_reg
    constexpr bsl::safe_uint64 BF_VPS_OP_WRITE_REG_IDX_VAL{bsl::to_u64(0x000000000000000CU)};

    /// <!-- description -->
    ///   @brief Writes to a CPU register in the VPS given a bf_reg_t and the
    ///     value to write. Note that the bf_reg_t is architecture specific.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to write to
    ///   @param reg A bf_reg_t defining which register to write to
    ///   @param value The value to write to the requested register
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_write_reg(                  // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bf_reg_t const reg,               // --
        bsl::safe_uint64 const &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_write_reg_impl(handle.hndl, vpsid.get(), reg, value.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_run
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_run.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_run_impl(    // --
        bf_uint64_t const reg0_in,                       // --
        bf_uint16_t const reg1_in,                       // --
        bf_uint16_t const reg2_in,                       // --
        bf_uint16_t const reg3_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_run
    constexpr bsl::safe_uint64 BF_VPS_OP_RUN_IDX_VAL{bsl::to_u64(0x000000000000000DU)};

    /// <!-- description -->
    ///   @brief bf_vps_op_run tells the microkernel to execute a given VPS on
    ///     behalf of a given VP and VM. This system call only returns if an
    ///     error occurs. On success, this system call will physically execute
    ///     the requested VM and VP using the requested VPS, and the extension
    ///     will only execute again on the next VMExit.
    ///
    ///     Unless an extension needs to change the active VM, VP or VPS, the
    ///     extension should use bf_vps_op_run_current instead of
    ///     bf_vps_op_run. bf_vps_op_run is slow as it must perform a series of
    ///     checks to determine if it has any work to perform before execution
    ///     of a VM can occur.
    ///
    ///     Unlike bf_vps_op_run_current which is really just a return to
    ///     microkernel execution, bf_vps_op_run must perform the following
    ///     operations:
    ///     - It first verifies that the provided VM, VP and VPS are all
    ///       created. Meaning, and extension must first use the create ABI
    ///       to properly create a VM, VP and VPS before it may be used.
    ///     - Next, it must ensure VM, VP and VPS assignment is correct. A
    ///       newly created VP and VPS are unassigned. Once bf_vps_op_run is
    ///       executed, the VP is assigned to the provided VM and the VPS is
    ///       assigned to the provided VP. The VP and VPS are also both
    ///       assigned to the PP bf_vps_op_run is executed on. Once these
    ///       assignments take place, an extension cannot change them, and any
    ///       attempt to run a VP or VPS on a VM, VP or PP they are not
    ///       assigned to will fail. It is impossible to change the assigned of
    ///       a VM or VP, but an extension can change the assignment of a VP
    ///       and VPSs PP by using the bf_vp_op_migrate function.
    ///     - Next, bf_vps_op_run must determine if it needs to migrate a VPS
    ///       to the PP the VPS is being executed on by bf_vps_op_run. For more
    ///       information about how this works, please see bf_vp_op_migrate.
    ///     - Finally, bf_vps_op_run must ensure the active VM, VP and VPS are
    ///       set to the VM, VP and VPS provided to this ABI. Any changes in
    ///       the active state could cause additional operations to take place.
    ///       For example, the VPS must transfer the TLS state of the general
    ///       purpose registers to its internal cache so that the VPS that is
    ///       about to become active can use the TLS block instead.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to run
    ///   @param vpid The VPID of the VP to run
    ///   @param vmid The VMID of the VM to run
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_run(                        // --
        bf_handle_t const &handle,        // --
        bsl::safe_uint16 const &vpsid,    // --
        bsl::safe_uint16 const &vpid,     // --
        bsl::safe_uint16 const &vmid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_vps_op_run_impl(handle.hndl, vpsid.get(), vpid.get(), vmid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_run_current
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_run_current.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_run_current_impl(    // --
        bf_uint64_t const reg0_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_run_current
    constexpr bsl::safe_uint64 BF_VPS_OP_RUN_CURRENT_IDX_VAL{bsl::to_u64(0x000000000000000EU)};

    /// <!-- description -->
    ///   @brief bf_vps_op_run_current tells the microkernel to execute the
    ///     currently active VPS, VP and VM.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_run_current(    // --
        bf_handle_t const &handle) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vps_op_run_current_impl(handle.hndl)};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_advance_ip
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_advance_ip.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_advance_ip_impl(    // --
        bf_uint64_t const reg0_in,                              // --
        bf_uint16_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_advance_ip
    constexpr bsl::safe_uint64 BF_VPS_OP_ADVANCE_IP_IDX_VAL{bsl::to_u64(0x000000000000000FU)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to advance the instruction
    ///     pointer in the requested VPS.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS advance the IP in
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_advance_ip(             // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vps_op_advance_ip_impl(handle.hndl, vpsid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_advance_ip_and_run_current
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_advance_ip_and_run_current.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_advance_ip_and_run_current_impl(    // --
        bf_uint64_t const reg0_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_advance_ip_and_run_current
    constexpr bsl::safe_uint64 BF_VPS_OP_ADVANCE_IP_AND_RUN_CURRENT_IDX_VAL{
        bsl::to_u64(0x0000000000000010U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to advance the instruction
    ///     pointer in the currently active VPS and run the currently active
    ///     VPS, VP and VM (i.e., this combines bf_vps_op_advance_ip and
    ///     bf_vps_op_advance_ip).
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_advance_ip_and_run_current(    // --
        bf_handle_t const &handle) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vps_op_advance_ip_and_run_current_impl(handle.hndl)};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_promote
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_promote.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_promote_impl(    // --
        bf_uint64_t const reg0_in,                           // --
        bf_uint16_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_promote
    constexpr bsl::safe_uint64 BF_VPS_OP_PROMOTE_IDX_VAL{bsl::to_u64(0x0000000000000011U)};

    /// <!-- description -->
    ///   @brief This syscall tells the microkernel to promote the requested
    ///     VPS. This will stop the hypervisor complete on the physical
    ///     processor that this syscall is executed on and replace it's state
    ///     with the state in the VPS. Note that this syscall only returns
    ///     on error.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to promote
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_promote(                // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vps_op_promote_impl(handle.hndl, vpsid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_vps_op_clear_vps
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_vps_op_clear_vps.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_vps_op_clear_vps_impl(    // --
        bf_uint64_t const reg0_in,                             // --
        bf_uint16_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_vps_op_clear_vps
    constexpr bsl::safe_uint64 BF_VPS_OP_CLEAR_VPS_IDX_VAL{bsl::to_u64(0x0000000000000012U)};

    /// <!-- description -->
    ///   @brief bf_vps_op_clear_vps tells the microkernel to clear the VPS's
    ///     hardware cache, if one exists. How this is used depends entirely
    ///     on the hardware and is associated with AMD's VMCB Clean Bits,
    ///     and Intel's VMClear instruction. See the associated documentation
    ///     for more details. On AMD, this ABI clears the entire VMCB. For more
    ///     fine grained control, use the write ABIs to manually modify the
    ///     VMCB.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param vpsid The VPSID of the VPS to clear
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_vps_op_clear_vps(              // --
        bf_handle_t const &handle,    // --
        bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_vps_op_clear_vps_impl(handle.hndl, vpsid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_intrinsic_op_rdmsr
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_rdmsr.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_intrinsic_op_rdmsr_impl(    // --
        bf_uint64_t const reg0_in,                               // --
        bf_uint32_t const reg1_in,                               // --
        bf_uint64_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_intrinsic_op_rdmsr
    constexpr bsl::safe_uint64 BF_INTRINSIC_OP_RDMSR_IDX_VAL{bsl::to_u64(0x0000000000000000U)};

    /// <!-- description -->
    ///   @brief Reads an MSR directly from the CPU given the address of
    ///     the MSR to read. Note that this is specific to Intel/AMD only.
    ///     Also note that not all MSRs can be read, and which MSRs that
    ///     can be read is up to the microkernel's internal policy as well
    ///     as which architecture the hypervisor is running on.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param msr The address of the MSR to read
    ///   @param value The resulting value
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_intrinsic_op_rdmsr(              // --
        bf_handle_t const &handle,      // --
        bsl::safe_uint32 const &msr,    // --
        bsl::safe_uint64 &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_intrinsic_op_rdmsr_impl(handle.hndl, msr.get(), value.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_intrinsic_op_wrmsr
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_wrmsr.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_intrinsic_op_wrmsr_impl(    // --
        bf_uint64_t const reg0_in,                               // --
        bf_uint32_t const reg1_in,                               // --
        bf_uint64_t const reg2_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_intrinsic_op_wrmsr
    constexpr bsl::safe_uint64 BF_INTRINSIC_OP_WRMSR_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// <!-- description -->
    ///   @brief Writes to an MSR directly from the CPU given the address of
    ///     the MSR to write as well as the value to write. Note that this is
    ///     specific to Intel/AMD only. Also note that not all MSRs can be
    ///     written to, and which MSRs that can be written to is up to the
    ///     microkernel's internal policy as well as which architecture the
    ///     hypervisor is running on.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param msr The address of the MSR to write to
    ///   @param value The value to write to the requested MSR
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_intrinsic_op_wrmsr(              // --
        bf_handle_t const &handle,      // --
        bsl::safe_uint32 const &msr,    // --
        bsl::safe_uint64 const &value) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_intrinsic_op_wrmsr_impl(handle.hndl, msr.get(), value.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_intrinsic_op_invlpga
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_invlpga.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_intrinsic_op_invlpga_impl(    // --
        bf_uint64_t const reg0_in,                                 // --
        bf_uint64_t const reg1_in,                                 // --
        bf_uint64_t const reg2_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_intrinsic_op_invlpga
    constexpr bsl::safe_uint64 BF_INTRINSIC_OP_INVLPGA_IDX_VAL{bsl::to_u64(0x0000000000000002U)};

    /// <!-- description -->
    ///   @brief Invalidates the TLB mapping for a given virtual page and a
    ///     given ASID. Note that this is specific to AMD only.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param addr The address to invalidate
    ///   @param asid The ASID to invalidate
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_intrinsic_op_invlpga(             // --
        bf_handle_t const &handle,       // --
        bsl::safe_uint64 const &addr,    // --
        bsl::safe_uint64 const &asid) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_intrinsic_op_invlpga_impl(handle.hndl, addr.get(), asid.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_intrinsic_op_invept
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_invept.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_intrinsic_op_invept_impl(    // --
        bf_uint64_t const reg0_in,                                // --
        bf_uint64_t const reg1_in,                                // --
        bf_uint64_t const reg2_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_intrinsic_op_invept
    constexpr bsl::safe_uint64 BF_INTRINSIC_OP_INVEPT_IDX_VAL{bsl::to_u64(0x0000000000000003U)};

    /// <!-- description -->
    ///   @brief Invalidates mappings in the translation lookaside buffers
    ///     (TLBs) and paging-structure caches that were derived from extended
    ///     page tables (EPT). Note that this is specific to Intel only.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param eptp The EPTP to invalidate
    ///   @param type The INVEPT type (see the Intel SDM for details)
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_intrinsic_op_invept(              // --
        bf_handle_t const &handle,       // --
        bsl::safe_uint64 const &eptp,    // --
        bsl::safe_uint64 const &type) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_intrinsic_op_invept_impl(handle.hndl, eptp.get(), type.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_intrinsic_op_invvpid
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_intrinsic_op_invvpid.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg2_in n/a
    ///   @param reg3_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_intrinsic_op_invvpid_impl(    // --
        bf_uint64_t const reg0_in,                                 // --
        bf_uint64_t const reg1_in,                                 // --
        bf_uint16_t const reg2_in,                                 // --
        bf_uint64_t const reg3_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_intrinsic_op_invvpid
    constexpr bsl::safe_uint64 BF_INTRINSIC_OP_INVVPID_IDX_VAL{bsl::to_u64(0x0000000000000004U)};

    /// <!-- description -->
    ///   @brief Invalidates mappings in the translation lookaside buffers
    ///     (TLBs) and paging-structure caches based on virtual-processor
    ///     identifier (VPID). Note that this is specific to Intel only.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param addr The address to invalidate
    ///   @param vpid The VPID to invalidate
    ///   @param type The INVVPID type (see the Intel SDM for details)
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_intrinsic_op_invvpid(             // --
        bf_handle_t const &handle,       // --
        bsl::safe_uint64 const &addr,    // --
        bsl::safe_uint16 const &vpid,    // --
        bsl::safe_uint64 const &type) noexcept -> bsl::errc_type
    {
        bf_status_t const status{
            bf_intrinsic_op_invvpid_impl(handle.hndl, addr.get(), vpid.get(), type.get())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_mem_op_alloc_page
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_alloc_page.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg0_out n/a
    ///   @param reg1_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_mem_op_alloc_page_impl(    // --
        bf_uint64_t const reg0_in,                              // --
        bf_ptr_t *const reg0_out,                               // --
        bf_uint64_t *const reg1_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_mem_op_alloc_page
    constexpr bsl::safe_uint64 BF_MEM_OP_ALLOC_PAGE_IDX_VAL{bsl::to_u64(0x0000000000000000U)};

    /// <!-- description -->
    ///   @brief bf_mem_op_alloc_page allocates a page, and maps this page
    ///     into the direct map of the VM.
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam T the type of memory to allocate
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param virt The virtual address of the resulting page
    ///   @param phys The physical address of the resulting page
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename T>
    [[nodiscard]] inline auto
    bf_mem_op_alloc_page(             // --
        bf_handle_t const &handle,    // --
        T *&virt,                     // --
        bsl::safe_uint64 &phys) noexcept -> bsl::errc_type
    {
        T *ptr{};

        bf_status_t const status{bf_mem_op_alloc_page_impl(handle.hndl, &ptr, phys.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        virt = ptr;
        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_mem_op_free_page
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_free_page.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_mem_op_free_page_impl(    // --
        bf_uint64_t const reg0_in,                             // --
        bf_ptr_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_mem_op_free_page
    constexpr bsl::safe_uint64 BF_MEM_OP_FREE_PAGE_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// <!-- description -->
    ///   @brief Frees a page previously allocated by bf_mem_op_alloc_page.
    ///     This operation is optional and not all microkernels may implement
    ///     it.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param virt The virtual address of the page to free
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_mem_op_free_page(              // --
        bf_handle_t const &handle,    // --
        bf_ptr_t virt) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_mem_op_free_page_impl(handle.hndl, virt)};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_mem_op_alloc_huge
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_alloc_huge.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg0_out n/a
    ///   @param reg1_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_mem_op_alloc_huge_impl(    // --
        bf_uint64_t const reg0_in,                              // --
        bf_uint64_t const reg1_in,                              // --
        bf_ptr_t *const reg0_out,                               // --
        bf_uint64_t *const reg1_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_mem_op_alloc_huge
    constexpr bsl::safe_uint64 BF_MEM_OP_ALLOC_HUGE_IDX_VAL{bsl::to_u64(0x0000000000000002U)};

    /// <!-- description -->
    ///   @brief bf_mem_op_alloc_huge allocates a physically contiguous block
    ///     of memory. When allocating a page, the extension should keep in
    ///     mind the following:
    ///       - The total memory available to allocate from this pool is
    ///         extremely limited. This should only be used when absolutely
    ///         needed, and extensions should not expect more than 1 MB (might
    ///         be less) of total memory available.
    ///       - Memory allocated from the huge pool might be allocated using
    ///         different schemes. For example, the microkernel might allocate
    ///         in increments of a page, or it might use a buddy allocator that
    ///         would allocate in multiples of 2. If the allocation size
    ///         doesn't match the algorithm, internal fragmentation could
    ///         occur, further limiting the total number of allocations this
    ///         pool can support.
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam T the type of memory to allocate
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param size The total number of bytes to allocate
    ///   @param virt The virtual address of the resulting memory
    ///   @param phys The physical address of the resulting memory
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename T>
    [[nodiscard]] inline auto
    bf_mem_op_alloc_huge(                // --
        bf_handle_t const &handle,       // --
        bsl::safe_uint64 const &size,    // --
        T *&virt,                        // --
        bsl::safe_uint64 &phys) noexcept -> bsl::errc_type
    {
        T *ptr{};

        bf_status_t const status{
            bf_mem_op_alloc_huge_impl(handle.hndl, size.get(), &ptr, phys.data())};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        virt = ptr;
        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_mem_op_free_huge
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_free_huge.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_mem_op_free_huge_impl(    // --
        bf_uint64_t const reg0_in,                             // --
        bf_ptr_t const reg1_in) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_mem_op_free_huge
    constexpr bsl::safe_uint64 BF_MEM_OP_FREE_HUGE_IDX_VAL{bsl::to_u64(0x0000000000000003U)};

    /// <!-- description -->
    ///   @brief Frees memory previously allocated by bf_mem_op_alloc_huge.
    ///     This operation is optional and not all microkernels may implement
    ///     it.
    ///
    /// <!-- inputs/outputs -->
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param virt The virtual address of the memory to free
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    [[nodiscard]] inline auto
    bf_mem_op_free_huge(              // --
        bf_handle_t const &handle,    // --
        bf_ptr_t virt) noexcept -> bsl::errc_type
    {
        bf_status_t const status{bf_mem_op_free_huge_impl(handle.hndl, virt)};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // bf_mem_op_alloc_heap
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_mem_op_alloc_heap.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///   @param reg0_out n/a
    ///   @return n/a
    ///
    extern "C" [[nodiscard]] auto bf_mem_op_alloc_heap_impl(    // --
        bf_uint64_t const reg0_in,                              // --
        bf_uint64_t const reg1_in,                              // --
        bf_ptr_t *const reg0_out) noexcept -> bf_status_t::value_type;

    /// @brief Defines the syscall index for bf_mem_op_alloc_heap
    constexpr bsl::safe_uint64 BF_MEM_OP_ALLOC_HEAP_IDX_VAL{bsl::to_u64(0x0000000000000004U)};

    /// <!-- description -->
    ///   @brief bf_mem_op_alloc_heap allocates heap memory. When allocating
    ///     heap memory, the extension should keep in mind the following:
    ///       - This ABI is designed to work similar to sbrk() to support
    ///         malloc/free implementations common with existing open source
    ///         libraries.
    ///       - Calling this ABI with with a size of 0 will return the current
    ///         heap location.
    ///       - Calling this ABI with a size (in bytes) will result in return
    ///         the previous heap location. The current heap location will be
    ///         set to the previous location, plus the provide size, rounded to
    ///         the nearest page size.
    ///       - The heap is not mapped into the direct map, so virtual to
    ///         physical (and vice versa) translations are not possible.
    ///       - There is no ability to free heap memory
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam T the type of memory to allocate
    ///   @param handle Set to the result of bf_handle_op_open_handle
    ///   @param size The number of bytes to increase the heap by
    ///   @param virt The virtual address of the previous heap location
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<typename T>
    [[nodiscard]] inline auto
    bf_mem_op_alloc_heap(                // --
        bf_handle_t const &handle,       // --
        bsl::safe_uint64 const &size,    // --
        T *&virt) noexcept -> bsl::errc_type
    {
        T *ptr{};

        bf_status_t const status{bf_mem_op_alloc_heap_impl(handle.hndl, size.get(), &ptr)};
        if (bsl::unlikely(status != BF_STATUS_SUCCESS)) {
            return bsl::errc_failure;
        }

        virt = ptr;
        return bsl::errc_success;
    }

    // -------------------------------------------------------------------------
    // Direct Map
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Returns the value at the provided physical address
    ///     on success, or returns bsl::safe_integral<T>::zero(true)
    ///     on failure.
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam EXT_DIRECT_MAP_ADDR the address of the extension's direct map
    ///   @tparam T the type of integral to read
    ///   @param handle reserved for unit testing
    ///   @param phys the physical address to read
    ///   @return Returns the value at the provided physical address
    ///     on success, or returns bsl::safe_integral<T>::zero(true)
    ///     on failure.
    ///
    template<bsl::uintmax EXT_DIRECT_MAP_ADDR, typename T = bsl::uintmax>
    [[nodiscard]] inline auto
    bf_read_phys(bf_handle_t const &handle, bsl::safe_uintmax const &phys) noexcept
        -> bsl::safe_integral<T>
    {
        bsl::discard(handle);

        auto const virt{EXT_DIRECT_MAP_ADDR + phys};
        if (bsl::likely(virt)) {
            return bsl::safe_integral<T>{*bsl::to_ptr<T *>(virt)};
        }

        return bsl::safe_integral<T>::zero(true);
    }

    /// <!-- description -->
    ///   @brief Writes the provided value at the provided physical address
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam EXT_DIRECT_MAP_ADDR the address of the extension's direct map
    ///   @tparam T the type of integral to write
    ///   @param handle reserved for unit testing
    ///   @param phys the physical address to write
    ///   @param val the value to write to the provided physical address
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     otherwise
    ///
    template<bsl::uintmax EXT_DIRECT_MAP_ADDR, typename T>
    [[nodiscard]] inline auto
    bf_write_phys(
        bf_handle_t const &handle,
        bsl::safe_uintmax const &phys,
        bsl::safe_integral<T> const &val) noexcept -> bsl::errc_type
    {
        bsl::discard(handle);

        auto const virt{EXT_DIRECT_MAP_ADDR + phys};
        if (bsl::likely(virt)) {
            *bsl::to_ptr<T *>(virt) = val.get();
            return bsl::errc_success;
        }

        return bsl::errc_failure;
    }

    /// <!-- description -->
    ///   @brief Performs a virtual address to physical address translation.
    ///     Note that this function only works on direct map memory, which
    ///     includes direct map addresses, allocated pages and allocated
    ///     huge memory.
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam EXT_DIRECT_MAP_ADDR the address of the extension's direct map
    ///   @tparam T the type of virtual address to convert
    ///   @param handle reserved for unit testing
    ///   @param virt the virtual address to convert
    ///   @return Returns the resulting physical address
    ///
    template<bsl::uintmax EXT_DIRECT_MAP_ADDR, typename T>
    [[nodiscard]] constexpr auto
    bf_virt_to_phys(bf_handle_t const &handle, T const *const virt) noexcept -> bsl::safe_uintmax
    {
        bsl::discard(handle);

        static_assert(bsl::disjunction<bsl::is_void<T>, bsl::is_standard_layout<T>>::value);
        return bsl::to_umax(virt) - EXT_DIRECT_MAP_ADDR;
    }

    /// <!-- description -->
    ///   @brief Performs a physical address to virtual address translation.
    ///     Note that this function only works on direct map memory, which
    ///     includes direct map addresses, allocated pages and allocated
    ///     huge memory.
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam EXT_DIRECT_MAP_ADDR the address of the extension's direct map
    ///   @tparam T the type of physical address to convert
    ///   @param handle reserved for unit testing
    ///   @param phys the physical address to convert
    ///   @return Returns the resulting virtual address
    ///
    template<bsl::uintmax EXT_DIRECT_MAP_ADDR, typename T>
    [[nodiscard]] constexpr auto
    phys_to_virt(bf_handle_t const &handle, bsl::safe_uintmax const &phys) noexcept -> T *
    {
        bsl::discard(handle);

        static_assert(bsl::disjunction<bsl::is_void<T>, bsl::is_standard_layout<T>>::value);
        return bsl::to_ptr<T *>(phys + EXT_DIRECT_MAP_ADDR);
    }
}

#endif
