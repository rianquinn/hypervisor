//
// Copyright (C) 2019 Assured Information Security, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// TIDY_EXCLUSION=-cppcoreguidelines-pro-type-reinterpret-cast
//
// Reason:
//     Although in general this is a good rule, for hypervisor level code that
//     interfaces with the kernel, and raw hardware, this rule is
//     impractical.
//

#include <bfgsl.h>
#include <bfweak.h>
#include <bfsupport.h>
#include <bfexception.h>

// #include <vcpu/vcpu_manager.h>
#include <uapis/memory_manager.h>
#include <implementation/debug_ring.h>

// #ifdef BF_INTEL_X64
// #include <hve/arch/intel_x64/vcpu.h>
// #endif

// static bfn::once_flag g_init_flag;

// void
// WEAK_SYM global_init()
// { }

// void
// WEAK_SYM vcpu_init_nonroot(vcpu_t *vcpu)
// { bfignored(vcpu); }

// void
// WEAK_SYM vcpu_fini_nonroot(vcpu_t *vcpu)
// { bfignored(vcpu); }

// void
// WEAK_SYM vcpu_init_nonroot_running(vcpu_t *vcpu)
// { bfignored(vcpu); }

// void
// WEAK_SYM vcpu_fini_nonroot_running(vcpu_t *vcpu)
// { bfignored(vcpu); }

extern "C" status_t
private_add_md(struct memory_descriptor *md) noexcept
{
    return guard_exceptions(BFFAILURE, [&] {
        memory_manager_n::add_md(
            static_cast<memory_manager_n::integer_pointer>(md->virt),
            static_cast<memory_manager_n::integer_pointer>(md->phys),
            static_cast<memory_manager_n::attr_type>(md->type)
        );
    });
}

extern "C" status_t
private_init_vmm(uint64_t arg) noexcept
{
    // return guard_exceptions(BFFAILURE, [&]() {

    //     bfn::call_once(g_init_flag, global_init);

    //     g_vcm->create(arg);

    //     auto vcpu = g_vcm->get<vcpu_t *>(arg);
    //     vcpu_init_nonroot(vcpu);

    //     vcpu->run();

    //     ::x64::cpuid::get(0x4BF00010, 0, 0, 0);
    //     ::x64::cpuid::get(0x4BF00011, 0, 0, 0);

    //     vcpu_init_nonroot_running(vcpu);
    //     return BFSUCCESS;
    // });

    bfignored(arg);
    return BFSUCCESS;
}

extern "C" status_t
private_fini_vmm(uint64_t arg) noexcept
{
    // return guard_exceptions(BFFAILURE, [&]() {

    //     auto vcpu = g_vcm->get<vcpu_t *>(arg);
    //     vcpu_fini_nonroot_running(vcpu);

    //     ::x64::cpuid::get(0x4BF00020, 0, 0, 0);
    //     ::x64::cpuid::get(0x4BF00021, 0, 0, 0);

    //     vcpu_fini_nonroot(vcpu);
    //     g_vcm->destroy(arg);

    //     return BFSUCCESS;
    // });

    bfignored(arg);
    return BFSUCCESS;
}

extern "C" status_t
bfmain(uint64_t request, uint64_t arg1, uint64_t arg2) noexcept
{
    bfignored(arg2);

    switch (request) {

        case BF_REQUEST_SET_MEM:
            return set_huge_pool(arg1, arg2);

        case BF_REQUEST_SET_MEM_NODE_TREE:
            return set_huge_pool_node_tree(arg1);

        // case BF_REQUEST_ADD_MDL:
        //     return private_add_md(reinterpret_cast<memory_descriptor *>(arg1));

        case BF_REQUEST_VMM_INIT:
            return private_init_vmm(arg1);

        case BF_REQUEST_VMM_FINI:
            return private_fini_vmm(arg1);

        // case BF_REQUEST_GET_DRR:
        //     return get_drr(reinterpret_cast<debug_ring_resources_t **>(arg1));

        default:
            break;
    }

    return BFSUCCESS;
}
