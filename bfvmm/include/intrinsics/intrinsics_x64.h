/*
 * Bareflank Hypervisor
 *
 * Copyright (C) 2015 Assured Information Security, Inc.
 * Author: Rian Quinn        <quinnr@ainfosec.com>
 * Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef INTRINSICS_H
#define INTRINSICS_H

#include <stdint.h>

// =============================================================================
// Intrinsics
// =============================================================================

#ifdef __cplusplus
extern "C" {
#endif

uint32_t __cpuid_eax(uint32_t val);
uint32_t __cpuid_ebx(uint32_t val);
uint32_t __cpuid_ecx(uint32_t val);
uint32_t __cpuid_edx(uint32_t val);

uint64_t __read_rflags(void);

uint64_t __read_msr(uint32_t msr);
void __write_msr(uint32_t msr, uint64_t val);

#ifdef __cplusplus
}
#endif

// =============================================================================
// C++ Wrapper
// =============================================================================

class intrinsics_x64
{
public:

    intrinsics_x64() {}
    virtual ~intrinsics_x64() {}

    virtual uint32_t cpuid_eax(uint32_t val)
    { return __cpuid_eax(val); }

    virtual uint32_t cpuid_ebx(uint32_t val)
    { return __cpuid_ebx(val); }

    virtual uint32_t cpuid_ecx(uint32_t val)
    { return __cpuid_ecx(val); }

    virtual uint32_t cpuid_edx(uint32_t val)
    { return __cpuid_edx(val); }

    virtual uint64_t read_rflags(void)
    { return __read_rflags(); }

    virtual uint64_t read_msr(uint32_t msr)
    { return __read_msr(msr); }

    virtual void write_msr(uint32_t msr, uint64_t val)
    { __write_msr(msr, val); }
};

// =============================================================================
// Masks
// =============================================================================

// RFLAGS
// 64-ia-32-architectures-software-developer-manual, section 3.4.3
#define RFLAGS_CF_CARRY_FLAG (1 << 0)
#define RFLAGS_PF_PARITY_FLAG (1 << 2)
#define RFLAGS_AF_AUXILIARY_CARRY_FLAG (1 << 4)
#define RFLAGS_ZF_ZERO_FLAG (1 << 6)
#define RFLAGS_SF_SIGN_FLAG (1 << 7)
#define RFLAGS_TF_TRAP_FLAG (1 << 8)
#define RFLAGS_IF_INTERRUPT_ENABLE_FLAG (1 << 9)
#define RFLAGS_DF_DIRECTION_FLAG (1 << 10)
#define RFLAGS_OF_OVERFLOW_FLAG (1 << 11)
#define RFLAGS_IOPL_PRIVILEGE_LEVEL (2 << 12)
#define RFLAGS_NT_NESTED_TASK (1 << 14)
#define RFLAGS_RF_RESUME_FLAG (1 << 16)
#define RFLAGS_VM_VIRTUAL_8086_MODE (1 << 17)
#define RFLAGS_AC_ALIGNMENT_CHECK_ACCESS_CONTROL (1 << 18)
#define RFLAGS_VIF_VIRTUAL_INTERUPT_FLAG (1 << 19)
#define RFLAGS_VIP_VIRTUAL_INTERUPT_PENDING (1 << 20)
#define RFLAGS_ID_ID_FLAG (1 << 21)

// VMX MSRs
// 64-ia-32-architectures-software-developer-manual, appendix A.1
#define IA32_VMX_BASIC_MSR (0x480)

#endif
