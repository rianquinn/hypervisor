//
// Bareflank Hypervisor
// Copyright (C) 2015 Assured Information Security, Inc.
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

// TIDY_EXCLUSION=-cppcoreguidelines-pro-type-reinterpret-cast
//
// Reason:
//     Although in general this is a good rule, for hypervisor level code that
//     interfaces with the kernel, and raw hardware, this rule is
//     impractical.
//

#include <bfgsl.h>
#include <bfdebug.h>
#include <bfvcpuid.h>
#include <bfobject.h>
#include <bfexports.h>
#include <bfsupport.h>
#include <bfexception.h>
#include <bftypes.h>

#include <domain/domain_manager.h>
#include <vcpu/vcpu_manager.h>
#include <debug/debug_ring/debug_ring.h>
#include <memory_manager/memory_manager.h>

#include <intrinsics.h>

#include "entry/entry.h"

extern "C" int64_t
private_init(void)
{ return ENTRY_SUCCESS; }

extern "C" int64_t
private_fini(void)
{ return ENTRY_SUCCESS; }

extern "C" int64_t
private_add_md(struct memory_descriptor *md) noexcept
{
    return guard_exceptions(MEMORY_MANAGER_FAILURE, [&] {

        auto virt = static_cast<bfvmm::memory_manager::integer_pointer>(md->virt);
        auto phys = static_cast<bfvmm::memory_manager::integer_pointer>(md->phys);
        auto type = static_cast<bfvmm::memory_manager::attr_type>(md->type);

        g_mm->add_md(virt, phys, type);
    });
}

extern "C" int64_t
private_set_rsdp(uintptr_t rsdp) noexcept
{
    g_rsdp = rsdp;
    return ENTRY_SUCCESS;
}

bfobject *
WEAK_SYM pre_create_vcpu(vcpuid::type id)
{ (void) id; return nullptr; }

bfobject *
WEAK_SYM pre_run_vcpu(vcpuid::type id)
{ (void) id; return nullptr; }

bfobject *
WEAK_SYM pre_hlt_vcpu(vcpuid::type id)
{ (void) id; return nullptr; }

bfobject *
WEAK_SYM pre_destroy_vcpu(vcpuid::type id)
{ (void) id; return nullptr; }

bool
WEAK_SYM hypervisor_setup(domain_t domain)
{ bfignored(domain); return true; }

bool
WEAK_SYM hypervisor_main(vcpu_t vcpu)
{ bfignored(vcpu); return true; }

bool
WEAK_SYM hypervisor_teardown(vcpu_t vcpu)
{ bfignored(vcpu); return true; }

extern "C" int64_t
private_init_vmm(uint64_t arg) noexcept
{
    return guard_exceptions(ENTRY_ERROR_VMM_START_FAILED, [&]() {

        g_vcm->run(arg, pre_run_vcpu(arg));

        return ENTRY_SUCCESS;
    });
}

extern "C" int64_t
private_fini_vmm(uint64_t arg) noexcept
{
    return guard_exceptions(ENTRY_ERROR_VMM_STOP_FAILED, [&]() {
        g_vcm->hlt(arg, pre_hlt_vcpu(arg));
        g_vcm->destroy(arg, pre_destroy_vcpu(arg));

        return ENTRY_SUCCESS;
    });
}

extern "C" bool
private_hypervisor_setup(uint64_t arg) noexcept
{
    return guard_exceptions(ENTRY_ERROR_VMM_STOP_FAILED, [&]() {

        g_dm->create(0, 0);
        auto domain_0 = g_dm->get(0);

        for (uint64_t vcpuid = 0; vcpuid < arg; vcpuid++) {
            g_vcm->create(vcpuid, pre_create_vcpu(arg));

            auto vcpu = get_vcpu(vcpuid);
            domain_0->add_vcpu(vcpu);
        }

        auto ___ = gsl::on_failure([&] {
            for (uint64_t vcpuid = 0; vcpuid < arg; vcpuid++)
            {
                g_vcm->destroy(arg);
            }
        });

        return hypervisor_setup(get_domain(0));
    });
}

extern "C" int64_t
bfmain(uintptr_t request, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3)
{
    bfignored(arg2);
    bfignored(arg3);

    switch (request) {
        case BF_REQUEST_INIT:
            return private_init();

        case BF_REQUEST_FINI:
            return private_fini();

        case BF_REQUEST_ADD_MDL:
            return private_add_md(reinterpret_cast<memory_descriptor *>(arg1));

        case BF_REQUEST_SET_RSDP:
            return private_set_rsdp(arg1);

        case BF_REQUEST_GET_DRR:
            return get_drr(arg1, reinterpret_cast<debug_ring_resources_t **>(arg2));

        case BF_REQUEST_VMM_HYPERVISOR_SETUP:
            return private_hypervisor_setup(arg1);

        case BF_REQUEST_VMM_INIT:
            return private_init_vmm(arg1);

        case BF_REQUEST_VMM_FINI:
            return private_fini_vmm(arg1);

        default:
            break;
    }

    return ENTRY_ERROR_UNKNOWN;
}
