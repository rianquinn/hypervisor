//
// Bareflank Hypervisor
// Copyright (C) 2018 Assured Information Security, Inc.
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

#include <hypervisor.h>

using namespace bfvmm::intel_x64;

bool my_cpuid_handler(vcpu_t vcpu, cpuid::info_t &info)
{
    bfignored(vcpu);
    bfignored(info);

    bfdebug_info(0, "This handler gets called when a guest runs CPUID 0xF00D");
    bfdebug_info(0, "The guest will observe the result 0xBEEF in register rax");
    vcpu->set_rax(0xBEEF);

    return true;
}

bool my_cpuid_handler_2(vcpu_t vcpu, cpuid::info_t &info)
{
    bfignored(vcpu);
    bfignored(info);

    bfdebug_info(0, "An extra handler for special-purpose CPUID leaf 0xBF21");
    bfdebug_info(0, "This handler is only registered to vcpu 0");

    return false;
}

bool hypervisor_setup(domain_t domain)
{
    bfdebug_info(0, "Initializing 2 CPUID handlers...");

    auto handler = cpuid::handler(my_cpuid_handler);
    cpuid::emulate(domain, 0xF00D, handler);

    auto vcpu_0 = get_vcpu(0);
    auto handler_2 = cpuid::handler(my_cpuid_handler_2);
    cpuid::emulate(vcpu_0, 0x4BF00020, handler_2);

    bfdebug_info(0, "CPUID example vmm setup complete!");

    return true;
}
