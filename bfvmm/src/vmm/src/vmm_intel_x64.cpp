//
// Bareflank Hypervisor
//
// Copyright (C) 2015 Assured Information Security, Inc.
// Author: Rian Quinn        <quinnr@ainfosec.com>
// Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include <iostream>
#include <vmm/vmm_intel_x64.h>

vmm_intel_x64 &
vmm_intel_x64::instance()
{
    static vmm_intel_x64 self;
    return self;
}

vmm_error::type
vmm_intel_x64::init(intrinsics_intel_x64 *intrinsics)
{
    if(intrinsics == 0)
        return vmm_error::failure;

    m_intrinsics = intrinsics;

    return vmm_error::success;
}

vmm_error::type
vmm_intel_x64::start()
{
    vmm_error::type ret;

    // The following process is documented in the Intel Software Developers
    // Manual, Section 31.5 Setup VMM & Teardown.

    ret = verify_cpuid_vmx_supported();
    if(ret != vmm_error::success)
        return ret;

    ret = verify_vmx_capabilities_msr();
    if(ret != vmm_error::success)
        return ret;

    // The following are additional checks that are documented in the VMXON
    // instructions itself in the Intel Software Developers Manual,
    // Section 30.3

    ret = verify_v8086_disabled();
    if(ret != vmm_error::success)
        return ret;

    return vmm_error::success;
}

vmm_error::type
vmm_intel_x64::stop()
{
    return vmm_error::success;
}

vmm_error::type
vmm_intel_x64::verify_cpuid_vmx_supported()
{
    auto cpuid_eax = m_intrinsics->cpuid_ecx(1);

    // The CPUID instruction is huge, so we don't use macros here. For further
    // information on how this works, see the Intel Software Developers Manual,
    // CPUID instruction reference, table 3-19

    if((cpuid_eax & (1 << 5)) == 0)
    {
        std::cout << "VMXON failed. " << "VMX extensions not supported" << std::endl;
        return vmm_error::not_supported;
    }

    return vmm_error::success;
}

vmm_error::type
vmm_intel_x64::verify_vmx_capabilities_msr()
{
    auto vmx_basic_msr = m_intrinsics->read_msr(IA32_VMX_BASIC_MSR);

    // The information regading this MSR can be found in appendix A.1. For
    // the VMX capabilities check, we need the following:
    //
    // - Bits 44:32 report the number of bytes that software should allocate
    //   for the VMXON region and any VMCS region. It is a value greater
    //   than 0 and at most 4096 (bit 44 is set if and only if bits 43:32 are
    //   clear).
    //
    //   Note: We basically ignore the above bits and just allocate 4K for each
    //   VMX region.
    //
    // - Bit 48 indicates the width of the physical addresses that may be
    //   used for the VMXON region, each VMCS, and data structures referenced
    //   by pointers in a VMCS (I/O bitmaps, virtual-APIC page, MSR areas for
    //   VMX transi- tions). If the bit is 0, these addresses are limited to
    //   the processor’s physical-address width. If the bit is 1, these
    //   addresses are limited to 32 bits. This bit is always 0 for processors
    //   that support Intel 64 architecture.
    //
    // - Bits 53:50 report the memory type that should be used for the VMCS,
    //   for data structures referenced by pointers in the VMCS (I/O bitmaps,
    //   virtual-APIC page, MSR areas for VMX transitions), and for the MSEG
    //   header. If software needs to access these data structures (e.g., to
    //   modify the contents of the MSR bitmaps), it can configure the paging
    //   structures to map them into the linear-address space. If it does so,
    //   it should establish mappings that use the memory type reported bits
    //   53:50 in this MSR.3
    //
    //   0 = uncacheable
    //   6 = writeback
    //

    auto physical_address_width = (vmx_basic_msr >> 48) & 0x1;
    auto memory_type = (vmx_basic_msr >> 50) & 0xF;

    if(physical_address_width != 0)
    {
        std::cout << "VMXON failed. " << "vmx capabilities MSR is reporting an unsupported physical address width: "
                  << std::hex << physical_address_width << std::dec << std::endl;
        return vmm_error::not_supported;
    }

    if(memory_type != 6)
    {
        std::cout << "VMXON failed. " << "vmx capabilities MSR is reporting an unsupported memory type: "
                  << std::hex << memory_type << std::dec << std::endl;
        return vmm_error::not_supported;
    }

    return vmm_error::success;
}

vmm_error::type
vmm_intel_x64::verify_v8086_disabled()
{
    auto rflags = m_intrinsics->read_rflags();

    if((rflags & RFLAGS_VM_VIRTUAL_8086_MODE) != 0)
    {
        std::cout << "VMXON failed. " << "v8086 is currently enabled" << std::endl;
        return vmm_error::not_supported;
    }

    return vmm_error::success;
}


// VMMs need to ensure that the processor is running in protected mode with
// paging before entering VMX operation. The following list describes the
// minimal steps required to enter VMX root operation with a VMM running at
// CPL = 0.
// • Check VMX support in processor using CPUID.
// • Determine the VMX capabilities supported by the processor through the VMX
//   capability MSRs. See Section 31.5.1 and Appendix A.
// • Create a VMXON region in non-pageable memory of a size specified by
//   IA32_VMX_BASIC MSR and aligned to a 4-KByte boundary. Software should read
//   the capability MSRs to determine width of the physical addresses that may
//   be used for the VMXON region and ensure the entire VMXON region can be
//   addressed by addresses with that width. Also, software must ensure that
//   the VMXON region is hosted in cache-coherent memory.
// • Initialize the version identifier in the VMXON region (the first 31 bits)
//   with the VMCS revision identifier reported by capability MSRs. Clear bit 31
//   of the first 4 bytes of the VMXON region.
// • Ensure the current processor operating mode meets the required CR0 fixed
//   bits (CR0.PE = 1, CR0.PG = 1). Other required CR0 fixed bits can be
//   detected through the IA32_VMX_CR0_FIXED0 and IA32_VMX_CR0_FIXED1 MSRs.
// • Enable VMX operation by setting CR4.VMXE = 1. Ensure the resultant CR4
//   value supports all the CR4 fixed bits reported in the IA32_VMX_CR4_FIXED0
//   and IA32_VMX_CR4_FIXED1 MSRs.
// • Ensure that the IA32_FEATURE_CONTROL MSR (MSR index 3AH) has been properly
//   programmed and that its lock bit is set (Bit 0 = 1). This MSR is generally
//   configured by the BIOS using WRMSR.
// • Execute VMXON with the physical address of the VMXON region as the operand.
//   Check successful execution of VMXON by checking if RFLAGS.CF = 0.
