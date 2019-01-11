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

#include <vcpu/vcpu.h>
#include <domain/domain.h>

#include "sdk/arch/intel_x64/cpuid.h"

namespace bfvmm::intel_x64::cpuid
{

void emulate(vcpu_t vcpu, leaf_t leaf, delegate_t handler)
{
    vcpu->cpuid_delegator()->add_handler(leaf, handler);
}

void emulate(domain_t domain, leaf_t leaf, delegate_t handler)
{
    for (auto vcpu : domain->vcpus()) {
        emulate(vcpu, leaf, handler);
    }
}

}
