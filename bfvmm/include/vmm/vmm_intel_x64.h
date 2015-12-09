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

#ifndef VMM_X86_64_H
#define VMM_X86_64_H

#include <vmm/vmm_base.h>
#include <intrinsics/intrinsics_intel_x64.h>

class vmm_intel_x64 : public vmm_base
{
public:

    /// Get Singleton Instance
    ///
    /// @return an instance to this singleton class
    ///
    static vmm_intel_x64 &instance();

    /// Intel x64 VMM Destructor
    ///
    ~vmm_intel_x64() {}

    /// Init VMM
    ///
    /// Initializes the VMM. One of the goals of this function is to decouple
    /// the intrinsics from the VMM so that the VMM can be tested.
    ///
    /// @param intrinsics the intrinsics class that this VMM will use
    /// @return success on success, failure otherwise
    vmm_error::type init(intrinsics_base *intrinsics,
                         memory_manager_base *memory_manager) override;

    /// Start VMM
    ///
    /// Starts the VMM. In the process of starting the VMM, several
    /// compatibility tests will be run to ensure that the VMM can in fact
    /// be used.
    ///
    /// @return not_supported if the compability tests fail, success on success
    ///         and failure otherwise
    vmm_error::type start() override;

    /// Stop VMM
    ///
    /// Stops the VMM.
    ///
    /// @return success on success, failure otherwise
    vmm_error::type stop() override;

private:

    /// Private Intel x64 VMM Constructor
    ///
    /// Since this is a singleton class, the constructor should not be used
    /// directly. Instead, use instance()
    ///
    vmm_intel_x64() {}

public:

    /// Explicitly prevent the ability to copy this class since it is
    /// a singleton class
    ///

    vmm_intel_x64(vmm_intel_x64 const &) = delete;
    void operator=(vmm_intel_x64 const &) = delete;

private:

    vmm_error::type verify_cpuid_vmx_supported();
    vmm_error::type verify_vmx_capabilities_msr();
    vmm_error::type verify_ia32_vmx_cr0_fixed0_msr();
    vmm_error::type verify_ia32_vmx_cr0_fixed1_msr();
    vmm_error::type verify_ia32_vmx_cr4_fixed0_msr();
    vmm_error::type verify_ia32_vmx_cr4_fixed1_msr();
    vmm_error::type verify_ia32_feature_control_msr();
    vmm_error::type verify_v8086_disabled();

    vmm_error::type create_vmxon_region();
    vmm_error::type enable_vmx_operation();

    vmm_error::type execute_vmxon();
    vmm_error::type execute_vmxoff();

    uint64_t vmxon_vmcs_region_size();

private:

    page m_vmxon_page;
    memory_manager_base *m_mm;
    intrinsics_intel_x64 *m_intrinsics;
};

#endif
