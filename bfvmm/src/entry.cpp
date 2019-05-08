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

#include <uapis/entry.h>
#include <uapis/vcpu_manager.h>
#include <implementation/debug_ring.h>
#include <implementation/memory_manager.h>

using namespace bfvmm;

// -----------------------------------------------------------------------------
// C-Style Entry Points
// -----------------------------------------------------------------------------

void
WEAK_SYM global_init()
{ }

void
WEAK_SYM vcpu_init_nonroot(vcpu_t *vcpu)
{ bfignored(vcpu); }

void
WEAK_SYM vcpu_fini_nonroot(vcpu_t *vcpu)
{ bfignored(vcpu); }

void
WEAK_SYM vcpu_init_nonroot_running(vcpu_t *vcpu)
{ bfignored(vcpu); }

void
WEAK_SYM vcpu_fini_nonroot_running(vcpu_t *vcpu)
{ bfignored(vcpu); }

// -----------------------------------------------------------------------------
// Entry Functions
// -----------------------------------------------------------------------------

class private_entry
{
public:

    static constexpr status_t
    request_add_md(uint64_t arg) noexcept
    {
        return guard_exceptions([arg] {
            auto md = reinterpret_cast<memory_descriptor *>(arg);
            g_mm->add_md(md->virt, md->phys, md->type);
        });
    }

    static constexpr status_t
    request_global_init() noexcept
    {
        return guard_exceptions([] {
            vcpu_t::global_init();
            global_init();
        });
    }

    static constexpr status_t
    request_init_vmm(uint64_t arg) noexcept
    {
        return guard_exceptions([arg]() {
            auto vcpu = g_vcm->create(arg);
            vcpu_init_nonroot(vcpu);
            vcpu->demote();
            vcpu_init_nonroot_running(vcpu);
        });
    }

    static constexpr status_t
    request_fini_vmm(uint64_t arg) noexcept
    {
        return guard_exceptions([arg]() {
            auto vcpu = g_vcm->destroy(arg);
            vcpu_fini_nonroot_running(vcpu.get());
            vcpu->promote();
            vcpu_fini_nonroot(vcpu.get());
        });
    }

    static constexpr status_t
    request_get_drr(uint64_t arg) noexcept
    {
        return guard_exceptions([arg]() {
            auto drr = reinterpret_cast<debug_ring_resources_t **>(arg);
            return get_drr(drr);
        });
    }
};

// -----------------------------------------------------------------------------
// BFMain
// -----------------------------------------------------------------------------

extern "C" status_t
bfmain(uint64_t request, uint64_t arg1, uint64_t arg2) noexcept
{
    bfignored(arg2);
    using namespace bfvmm::implementation;

    switch (request) {
        case BF_REQUEST_SET_MEM_LEAFS:
            return set_huge_pool_leafs(arg1, arg2);

        case BF_REQUEST_SET_MEM_NODES:
            return set_huge_pool_nodes(arg1, arg2);

        case BF_REQUEST_ADD_MD:
            return private_entry::request_add_md(arg1);

        case BF_REQUEST_GLOBAL_INIT:
            return private_entry::request_global_init();

        case BF_REQUEST_VMM_INIT:
            return private_entry::request_init_vmm(arg1);

        case BF_REQUEST_VMM_FINI:
            return private_entry::request_fini_vmm(arg1);

        case BF_REQUEST_GET_DRR:
            return private_entry::request_get_drr(arg1);

        default:
            break;
    }

    return BFSUCCESS;
}
