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

#ifndef BF_CONSTANTS_HPP
#define BF_CONSTANTS_HPP

#include <bf_types.hpp>

#include <bsl/convert.hpp>

namespace syscall
{
    // -------------------------------------------------------------------------
    // Special IDs
    // -------------------------------------------------------------------------

    /// @brief Defines an invalid ID for an extension, VM, VP and VPS
    constexpr bf_uint16_t BF_INVALID_ID{bsl::to_u16(0xFFFFU)};

    /// @brief Defines the bootstrap physical processor ID
    constexpr bf_uint16_t BF_BS_PPID{bsl::to_u16(0x0U)};

    /// @brief Defines the root virtual machine ID
    constexpr bf_uint16_t BF_ROOT_VMID{bsl::to_u16(0x0U)};

    // -------------------------------------------------------------------------
    // Syscall Status Codes
    // -------------------------------------------------------------------------

    /// @brief Used to indicated that the syscall returned successfully
    constexpr bf_uint64_t BF_STATUS_SUCCESS{bsl::to_u64(0x0000000000000000U)};
    /// @brief Indicates an unknown error occurred
    constexpr bf_uint64_t BF_STATUS_FAILURE_UNKNOWN{bsl::to_u64(0xDEAD000000010001U)};
    /// @brief Indicates the syscall is unsupported
    constexpr bf_uint64_t BF_STATUS_FAILURE_INVALID_HANDLE{bsl::to_u64(0xDEAD000000020001U)};
    /// @brief Indicates the provided handle is invalid
    constexpr bf_uint64_t BF_STATUS_FAILURE_UNSUPPORTED{bsl::to_u64(0xDEAD000000040001U)};
    /// @brief Indicates the extension is not allowed to execute this syscall
    constexpr bf_uint64_t BF_STATUS_INVALID_PERM_EXT{bsl::to_u64(0xDEAD000000010002U)};
    /// @brief Indicates the policy engine denied the syscall
    constexpr bf_uint64_t BF_STATUS_INVALID_PERM_DENIED{bsl::to_u64(0xDEAD000000020002U)};
    /// @brief Indicates param 0 is invalid
    constexpr bf_uint64_t BF_STATUS_INVALID_PARAMS0{bsl::to_u64(0xDEAD000000010003U)};
    /// @brief Indicates param 1 is invalid
    constexpr bf_uint64_t BF_STATUS_INVALID_PARAMS1{bsl::to_u64(0xDEAD000000020003U)};
    /// @brief Indicates param 2 is invalid
    constexpr bf_uint64_t BF_STATUS_INVALID_PARAMS2{bsl::to_u64(0xDEAD000000040003U)};
    /// @brief Indicates param 3 is invalid
    constexpr bf_uint64_t BF_STATUS_INVALID_PARAMS3{bsl::to_u64(0xDEAD000000080003U)};
    /// @brief Indicates param 4 is invalid
    constexpr bf_uint64_t BF_STATUS_INVALID_PARAMS4{bsl::to_u64(0xDEAD000000100003U)};
    /// @brief Indicates param 5 is invalid
    constexpr bf_uint64_t BF_STATUS_INVALID_PARAMS5{bsl::to_u64(0xDEAD000000200003U)};

    // -------------------------------------------------------------------------
    // Syscall Inputs
    // -------------------------------------------------------------------------

    /// @brief Defines the BF_SYSCALL_SIG field for RAX
    constexpr bf_uint64_t BF_HYPERCALL_SIG_VAL{bsl::to_u64(0x6642000000000000U)};
    /// @brief Defines a mask for BF_SYSCALL_SIG
    constexpr bf_uint64_t BF_HYPERCALL_SIG_MASK{bsl::to_u64(0xFFFF000000000000U)};
    /// @brief Defines a mask for BF_SYSCALL_FLAGS
    constexpr bf_uint64_t BF_HYPERCALL_FLAGS_MASK{bsl::to_u64(0x0000FFFF00000000U)};
    /// @brief Defines a mask for BF_SYSCALL_OP
    constexpr bf_uint64_t BF_HYPERCALL_OPCODE_MASK{bsl::to_u64(0xFFFF0000FFFF0000U)};
    /// @brief Defines a mask for BF_SYSCALL_OP (with no signature added)
    constexpr bf_uint64_t BF_HYPERCALL_OPCODE_NOSIG_MASK{bsl::to_u64(0x00000000FFFF0000U)};
    /// @brief Defines a mask for BF_SYSCALL_IDX
    constexpr bf_uint64_t BF_HYPERCALL_INDEX_MASK{bsl::to_u64(0x000000000000FFFFU)};

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param rax n/a
    ///   @return n/a
    ///
    [[nodiscard]] constexpr auto
    bf_syscall_sig(bf_uint64_t const &rax) noexcept -> bf_uint64_t
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
    bf_syscall_flags(bf_uint64_t const &rax) noexcept -> bf_uint64_t
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
    bf_syscall_opcode(bf_uint64_t const &rax) noexcept -> bf_uint64_t
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
    bf_syscall_opcode_nosig(bf_uint64_t const &rax) noexcept -> bf_uint64_t
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
    bf_syscall_index(bf_uint64_t const &rax) noexcept -> bf_uint64_t
    {
        return rax & BF_HYPERCALL_INDEX_MASK;
    }

    // -------------------------------------------------------------------------
    // Specification IDs
    // -------------------------------------------------------------------------

    /// @brief Defines the ID for version #1 of this spec
    constexpr bf_uint32_t BF_SPEC_ID1_VAL{bsl::to_u32(0x31236642)};

    /// @brief Defines the mask for checking support for version #1 of this spec
    constexpr bf_uint32_t BF_SPEC_ID1_MASK{bsl::to_u32(0x2)};

    /// @brief Defines the value likely returned by bf_handle_op_version
    constexpr bf_uint32_t BF_ALL_SPECS_SUPPORTED_VAL{bsl::to_u32(0x2)};

    /// <!-- description -->
    ///   @brief n/a
    ///
    /// <!-- inputs/outputs -->
    ///   @param version n/a
    ///   @return n/a
    ///
    [[nodiscard]] constexpr auto
    bf_is_spec1_supported(bf_uint32_t const &version) noexcept -> bool
    {
        return ((version & BF_SPEC_ID1_MASK) != bsl::ZERO_U32);
    }

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Control Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_control_op
    constexpr bf_uint64_t BF_CONTROL_OP_VAL{bsl::to_u64(0x6642000000000000U)};
    /// @brief Defines the syscall opcode for bf_control_op (nosig)
    constexpr bf_uint64_t BF_CONTROL_OP_NOSIG_VAL{bsl::to_u64(0x0000000000000000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Handle Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_handle_op
    constexpr bf_uint64_t BF_HANDLE_OP_VAL{bsl::to_u64(0x6642000000010000U)};
    /// @brief Defines the syscall opcode for bf_handle_op (nosig)
    constexpr bf_uint64_t BF_HANDLE_OP_NOSIG_VAL{bsl::to_u64(0x0000000000010000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Debug Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_debug_op
    constexpr bf_uint64_t BF_DEBUG_OP_VAL{bsl::to_u64(0x6642000000020000U)};
    /// @brief Defines the syscall opcode for bf_debug_op (nosig)
    constexpr bf_uint64_t BF_DEBUG_OP_NOSIG_VAL{bsl::to_u64(0x00000000000020000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Callback Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_callback_op
    constexpr bf_uint64_t BF_CALLBACK_OP_VAL{bsl::to_u64(0x6642000000030000U)};
    /// @brief Defines the syscall opcode for bf_callback_op (nosig)
    constexpr bf_uint64_t BF_CALLBACK_OP_NOSIG_VAL{bsl::to_u64(0x0000000000030000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - VM Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_vm_op
    constexpr bf_uint64_t BF_VM_OP_VAL{bsl::to_u64(0x6642000000040000U)};
    /// @brief Defines the syscall opcode for bf_vm_op (nosig)
    constexpr bf_uint64_t BF_VM_OP_NOSIG_VAL{bsl::to_u64(0x0000000000040000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - VP Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_vp_op
    constexpr bf_uint64_t BF_VP_OP_VAL{bsl::to_u64(0x6642000000050000U)};
    /// @brief Defines the syscall opcode for bf_vp_op (nosig)
    constexpr bf_uint64_t BF_VP_OP_NOSIG_VAL{bsl::to_u64(0x0000000000050000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - VPS Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_vps_op
    constexpr bf_uint64_t BF_VPS_OP_VAL{bsl::to_u64(0x6642000000060000U)};
    /// @brief Defines the syscall opcode for bf_vps_op (nosig)
    constexpr bf_uint64_t BF_VPS_OP_NOSIG_VAL{bsl::to_u64(0x0000000000060000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Intrinsic Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_intrinsic_op
    constexpr bf_uint64_t BF_INTRINSIC_OP_VAL{bsl::to_u64(0x6642000000070000U)};
    /// @brief Defines the syscall opcode for bf_intrinsic_op (nosig)
    constexpr bf_uint64_t BF_INTRINSIC_OP_NOSIG_VAL{bsl::to_u64(0x0000000000070000U)};

    // -------------------------------------------------------------------------
    // Syscall Opcodes - Mem Support
    // -------------------------------------------------------------------------

    /// @brief Defines the syscall opcode for bf_mem_op
    constexpr bf_uint64_t BF_MEM_OP_VAL{bsl::to_u64(0x6642000000080000U)};
    /// @brief Defines the syscall opcode for bf_mem_op (nosig)
    constexpr bf_uint64_t BF_MEM_OP_NOSIG_VAL{bsl::to_u64(0x0000000000080000U)};

    // -------------------------------------------------------------------------
    // TLS Offsets
    // -------------------------------------------------------------------------

    /// @brief stores the offset for rax
    constexpr bf_uint64_t TLS_OFFSET_RAX{bsl::to_u64(0x800U)};
    /// @brief stores the offset for rbx
    constexpr bf_uint64_t TLS_OFFSET_RBX{bsl::to_u64(0x808U)};
    /// @brief stores the offset for rcx
    constexpr bf_uint64_t TLS_OFFSET_RCX{bsl::to_u64(0x810U)};
    /// @brief stores the offset for rdx
    constexpr bf_uint64_t TLS_OFFSET_RDX{bsl::to_u64(0x818U)};
    /// @brief stores the offset for rbp
    constexpr bf_uint64_t TLS_OFFSET_RBP{bsl::to_u64(0x820U)};
    /// @brief stores the offset for rsi
    constexpr bf_uint64_t TLS_OFFSET_RSI{bsl::to_u64(0x828U)};
    /// @brief stores the offset for rdi
    constexpr bf_uint64_t TLS_OFFSET_RDI{bsl::to_u64(0x830U)};
    /// @brief stores the offset for r8
    constexpr bf_uint64_t TLS_OFFSET_R8{bsl::to_u64(0x838U)};
    /// @brief stores the offset for r9
    constexpr bf_uint64_t TLS_OFFSET_R9{bsl::to_u64(0x840U)};
    /// @brief stores the offset for r10
    constexpr bf_uint64_t TLS_OFFSET_R10{bsl::to_u64(0x848U)};
    /// @brief stores the offset for r11
    constexpr bf_uint64_t TLS_OFFSET_R11{bsl::to_u64(0x850U)};
    /// @brief stores the offset for r12
    constexpr bf_uint64_t TLS_OFFSET_R12{bsl::to_u64(0x858U)};
    /// @brief stores the offset for r13
    constexpr bf_uint64_t TLS_OFFSET_R13{bsl::to_u64(0x860U)};
    /// @brief stores the offset for r14
    constexpr bf_uint64_t TLS_OFFSET_R14{bsl::to_u64(0x868U)};
    /// @brief stores the offset for r15
    constexpr bf_uint64_t TLS_OFFSET_R15{bsl::to_u64(0x870U)};
    /// @brief stores the offset of the active extid
    constexpr bf_uint64_t TLS_OFFSET_ACTIVE_EXTID{bsl::to_u64(0xFF0U)};
    /// @brief stores the offset of the active vmid
    constexpr bf_uint64_t TLS_OFFSET_ACTIVE_VMID{bsl::to_u64(0xFF2U)};
    /// @brief stores the offset of the active vpid
    constexpr bf_uint64_t TLS_OFFSET_ACTIVE_VPID{bsl::to_u64(0xFF4U)};
    /// @brief stores the offset of the active vpsid
    constexpr bf_uint64_t TLS_OFFSET_ACTIVE_VPSID{bsl::to_u64(0xFF6U)};
    /// @brief stores the offset of the active ppid
    constexpr bf_uint64_t TLS_OFFSET_ACTIVE_PPID{bsl::to_u64(0xFF8U)};
    /// @brief stores the number of PPs that are online
    constexpr bf_uint64_t TLS_OFFSET_ONLINE_PPS{bsl::to_u64(0xFFAU)};

    // -------------------------------------------------------------------------
    // Syscall Indexes
    // -------------------------------------------------------------------------

    // clang-format off

    /// @brief Defines the syscall index for bf_control_op_exit
    constexpr bf_uint64_t BF_CONTROL_OP_EXIT_IDX_VAL{bsl::to_u64(0x0000000000000000U)};
    /// @brief Defines the syscall index for bf_control_op_wait
    constexpr bf_uint64_t BF_CONTROL_OP_WAIT_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// @brief Defines the syscall index for bf_handle_op_open_handle
    constexpr bf_uint64_t BF_HANDLE_OP_OPEN_HANDLE_IDX_VAL{bsl::to_u64(0x0000000000000000U)};
    /// @brief Defines the syscall index for bf_handle_op_close_handle
    constexpr bf_uint64_t BF_HANDLE_OP_CLOSE_HANDLE_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// @brief Defines the syscall index for bf_debug_op_out
    constexpr bf_uint64_t BF_DEBUG_OP_OUT_IDX_VAL{bsl::to_u64(0x0000000000000000U)};
    /// @brief Defines the syscall index for bf_debug_op_dump_vm
    constexpr bf_uint64_t BF_DEBUG_OP_DUMP_VM_IDX_VAL{bsl::to_u64(0x0000000000000001U)};
    /// @brief Defines the syscall index for bf_debug_op_dump_vp
    constexpr bf_uint64_t BF_DEBUG_OP_DUMP_VP_IDX_VAL{bsl::to_u64(0x0000000000000002U)};
    /// @brief Defines the syscall index for bf_debug_op_dump_vps
    constexpr bf_uint64_t BF_DEBUG_OP_DUMP_VPS_IDX_VAL{bsl::to_u64(0x0000000000000003U)};
    /// @brief Defines the syscall index for bf_debug_op_dump_vmexit_log
    constexpr bf_uint64_t BF_DEBUG_OP_DUMP_VMEXIT_LOG_IDX_VAL{bsl::to_u64(0x0000000000000004U)};
    /// @brief Defines the syscall index for bf_debug_op_write_c
    constexpr bf_uint64_t BF_DEBUG_OP_WRITE_C_IDX_VAL{bsl::to_u64(0x0000000000000005U)};
    /// @brief Defines the syscall index for bf_debug_op_write_str
    constexpr bf_uint64_t BF_DEBUG_OP_WRITE_STR_IDX_VAL{bsl::to_u64(0x0000000000000006U)};
    /// @brief Defines the syscall index for bf_debug_op_dump_ext
    constexpr bf_uint64_t BF_DEBUG_OP_DUMP_EXT_IDX_VAL{bsl::to_u64(0x0000000000000007U)};
    /// @brief Defines the syscall index for bf_debug_op_dump_page_pool
    constexpr bf_uint64_t BF_DEBUG_OP_DUMP_PAGE_POOL_IDX_VAL{bsl::to_u64(0x0000000000000008U)};
    /// @brief Defines the syscall index for bf_debug_op_dump_huge_pool
    constexpr bf_uint64_t BF_DEBUG_OP_DUMP_HUGE_POOL_IDX_VAL{bsl::to_u64(0x0000000000000009U)};

    /// @brief Defines the syscall index for bf_callback_op_register_bootstrap
    constexpr bf_uint64_t BF_CALLBACK_OP_REGISTER_BOOTSTRAP_IDX_VAL{bsl::to_u64(0x0000000000000002U)};
    /// @brief Defines the syscall index for bf_callback_op_register_vmexit
    constexpr bf_uint64_t BF_CALLBACK_OP_REGISTER_VMEXIT_IDX_VAL{bsl::to_u64(0x0000000000000003U)};
    /// @brief Defines the syscall index for bf_callback_op_register_fail
    constexpr bf_uint64_t BF_CALLBACK_OP_REGISTER_FAIL_IDX_VAL{bsl::to_u64(0x0000000000000004U)};

    /// @brief Defines the syscall index for bf_vm_op_create_vm
    constexpr bf_uint64_t BF_VM_OP_CREATE_VM_IDX_VAL{bsl::to_u64(0x0000000000000000U)};
    /// @brief Defines the syscall index for bf_vm_op_destroy_vm
    constexpr bf_uint64_t BF_VM_OP_DESTROY_VM_IDX_VAL{bsl::to_u64(0x0000000000000001U)};

    /// @brief Defines the syscall index for bf_vp_op_create_vp
    constexpr bf_uint64_t BF_VP_OP_CREATE_VP_IDX_VAL{bsl::to_u64(0x0000000000000000U)};
    /// @brief Defines the syscall index for bf_vp_op_destroy_vp
    constexpr bf_uint64_t BF_VP_OP_DESTROY_VP_IDX_VAL{bsl::to_u64(0x0000000000000001U)};
    /// @brief Defines the syscall index for bf_vp_op_migrate
    constexpr bf_uint64_t BF_VP_OP_MIGRATE_IDX_VAL{bsl::to_u64(0x0000000000000002U)};

    /// @brief Defines the syscall index for bf_vps_op_create_vps
    constexpr bf_uint64_t BF_VPS_OP_CREATE_VPS_IDX_VAL{bsl::to_u64(0x0000000000000000U)};
    /// @brief Defines the syscall index for bf_vps_op_destroy_vps
    constexpr bf_uint64_t BF_VPS_OP_DESTROY_VPS_IDX_VAL{bsl::to_u64(0x0000000000000001U)};
    /// @brief Defines the syscall index for bf_vps_op_init_as_root
    constexpr bf_uint64_t BF_VPS_OP_INIT_AS_ROOT_IDX_VAL{bsl::to_u64(0x0000000000000002U)};
    /// @brief Defines the syscall index for bf_vps_op_read8
    constexpr bf_uint64_t BF_VPS_OP_READ8_IDX_VAL{bsl::to_u64(0x0000000000000003U)};
    /// @brief Defines the syscall index for bf_vps_op_read16
    constexpr bf_uint64_t BF_VPS_OP_READ16_IDX_VAL{bsl::to_u64(0x0000000000000004U)};
    /// @brief Defines the syscall index for bf_vps_op_read32
    constexpr bf_uint64_t BF_VPS_OP_READ32_IDX_VAL{bsl::to_u64(0x0000000000000005U)};
    /// @brief Defines the syscall index for bf_vps_op_read64
    constexpr bf_uint64_t BF_VPS_OP_READ64_IDX_VAL{bsl::to_u64(0x0000000000000006U)};
    /// @brief Defines the syscall index for bf_vps_op_write
    constexpr bf_uint64_t BF_VPS_OP_WRITE8_IDX_VAL{bsl::to_u64(0x0000000000000007U)};
    /// @brief Defines the syscall index for bf_vps_op_write
    constexpr bf_uint64_t BF_VPS_OP_WRITE16_IDX_VAL{bsl::to_u64(0x0000000000000008U)};
    /// @brief Defines the syscall index for bf_vps_op_write
    constexpr bf_uint64_t BF_VPS_OP_WRITE32_IDX_VAL{bsl::to_u64(0x0000000000000009U)};
    /// @brief Defines the syscall index for bf_vps_op_write
    constexpr bf_uint64_t BF_VPS_OP_WRITE64_IDX_VAL{bsl::to_u64(0x000000000000000AU)};
    /// @brief Defines the syscall index for bf_vps_op_read_reg
    constexpr bf_uint64_t BF_VPS_OP_READ_REG_IDX_VAL{bsl::to_u64(0x000000000000000BU)};
    /// @brief Defines the syscall index for bf_vps_op_write_reg
    constexpr bf_uint64_t BF_VPS_OP_WRITE_REG_IDX_VAL{bsl::to_u64(0x000000000000000CU)};
    /// @brief Defines the syscall index for bf_vps_op_run
    constexpr bf_uint64_t BF_VPS_OP_RUN_IDX_VAL{bsl::to_u64(0x000000000000000DU)};
    /// @brief Defines the syscall index for bf_vps_op_run_current
    constexpr bf_uint64_t BF_VPS_OP_RUN_CURRENT_IDX_VAL{bsl::to_u64(0x000000000000000EU)};
    /// @brief Defines the syscall index for bf_vps_op_advance_ip
    constexpr bf_uint64_t BF_VPS_OP_ADVANCE_IP_IDX_VAL{bsl::to_u64(0x000000000000000FU)};
    /// @brief Defines the syscall index for bf_vps_op_advance_ip_and_run_current
    constexpr bf_uint64_t BF_VPS_OP_ADVANCE_IP_AND_RUN_CURRENT_IDX_VAL{bsl::to_u64(0x0000000000000010U)};
    /// @brief Defines the syscall index for bf_vps_op_promote
    constexpr bf_uint64_t BF_VPS_OP_PROMOTE_IDX_VAL{bsl::to_u64(0x0000000000000011U)};
    /// @brief Defines the syscall index for bf_vps_op_clear_vps
    constexpr bf_uint64_t BF_VPS_OP_CLEAR_VPS_IDX_VAL{bsl::to_u64(0x0000000000000012U)};

    /// @brief Defines the syscall index for bf_intrinsic_op_rdmsr
    constexpr bf_uint64_t BF_INTRINSIC_OP_RDMSR_IDX_VAL{bsl::to_u64(0x0000000000000000U)};
    /// @brief Defines the syscall index for bf_intrinsic_op_wrmsr
    constexpr bf_uint64_t BF_INTRINSIC_OP_WRMSR_IDX_VAL{bsl::to_u64(0x0000000000000001U)};
    /// @brief Defines the syscall index for bf_intrinsic_op_invlpga
    constexpr bf_uint64_t BF_INTRINSIC_OP_INVLPGA_IDX_VAL{bsl::to_u64(0x0000000000000002U)};
    /// @brief Defines the syscall index for bf_intrinsic_op_invept
    constexpr bf_uint64_t BF_INTRINSIC_OP_INVEPT_IDX_VAL{bsl::to_u64(0x0000000000000003U)};
    /// @brief Defines the syscall index for bf_intrinsic_op_invvpid
    constexpr bf_uint64_t BF_INTRINSIC_OP_INVVPID_IDX_VAL{bsl::to_u64(0x0000000000000004U)};

    /// @brief Defines the syscall index for bf_mem_op_alloc_page
    constexpr bf_uint64_t BF_MEM_OP_ALLOC_PAGE_IDX_VAL{bsl::to_u64(0x0000000000000000U)};
    /// @brief Defines the syscall index for bf_mem_op_free_page
    constexpr bf_uint64_t BF_MEM_OP_FREE_PAGE_IDX_VAL{bsl::to_u64(0x0000000000000001U)};
    /// @brief Defines the syscall index for bf_mem_op_alloc_huge
    constexpr bf_uint64_t BF_MEM_OP_ALLOC_HUGE_IDX_VAL{bsl::to_u64(0x0000000000000002U)};
    /// @brief Defines the syscall index for bf_mem_op_free_huge
    constexpr bf_uint64_t BF_MEM_OP_FREE_HUGE_IDX_VAL{bsl::to_u64(0x0000000000000003U)};
    /// @brief Defines the syscall index for bf_mem_op_alloc_heap
    constexpr bf_uint64_t BF_MEM_OP_ALLOC_HEAP_IDX_VAL{bsl::to_u64(0x0000000000000004U)};
}

#endif
