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

#include <vmm_entry.h>

#include <iostream>
#include <entry/entry_factory.h>

#ifndef INIT_IOSTREAM
#define INIT_IOSTREAM()
#endif

debug_ring_error::type
debug_ring_init_local(struct debug_ring_resources *drr)
{
    drr->epos = 0;
    drr->spos = 0;

    // std::cout << "-------------------------------------------- start" << std::endl;

    // std::cout << "drr: " << drr << std::endl;
    // std::cout << "buf: " << (void *)drr->buf << std::endl;
    // std::cout << "len: " << drr->len << std::endl;

    for (auto i = 0; i < drr->len; i++)
        drr->buf[i] = '\0';

    // std::cout << "-------------------------------------------- start" << std::endl;

    return debug_ring_error::success;
}

// =============================================================================
// Internal C++ Entry Functions
// =============================================================================

void *
start_vmm_trampoline(void *arg)
{
    auto *vmmr = (vmm_resources_t *)arg;

    if (arg == 0)
        return VMM_ERROR_INVALID_ARG;

    // #########################################################################
    // Testing Code
    // #########################################################################

    INIT_IOSTREAM();

    // The following code is the same as what is in common.c for the driver
    // entry. Bascially, both are clearing memory, and printing out the address
    // of the memory and it's length.
    //
    // The address and length never change. In all the tests below, pritning
    // out the address of buf causes the code to be more reliable, but it
    // will still crash if you try like a million times. When it does crash
    // you get a "buf: ", meaning it crashed trying to access drr->buf. This
    // tells me that the drr memory itself is somehow no longer addressable,
    // even though nothing has happened, and the address is the same.

    std::cout << "============================================ start" << std::endl;

    std::cout << "drr: " << vmmr->drr << std::endl;
    std::cout << "buf: " << (void *)vmmr->drr->buf << std::endl;
    std::cout << "len: " << vmmr->drr->len << std::endl;

    // TEST #1: This test was designed to see if allocating the debug ring in
    // the vcpu is the problem. So I create the debug ring on the stack here,
    // and it's still a problem.
    debug_ring m_debug_ring;
    m_debug_ring.init(vmmr->drr);
    m_debug_ring.init(vmmr->drr);
    m_debug_ring.init(vmmr->drr);
    m_debug_ring.init(vmmr->drr);
    m_debug_ring.init(vmmr->drr);

    // TEST #2: This test was to try and figure out if the C++ code was the
    // issue. The idea here was that maybe removing the C++ component would
    // make it work. But that as was not the case, as it still crashes.
    // debug_ring_init(vmmr->drr);
    // debug_ring_init(vmmr->drr);
    // debug_ring_init(vmmr->drr);
    // debug_ring_init(vmmr->drr);
    // debug_ring_init(vmmr->drr);

    // TEST #3: This test was to see if the ELF loader was the issue, as this
    // function is in the same module. This code still crashes.
    // debug_ring_init_local(vmmr->drr);
    // debug_ring_init_local(vmmr->drr);
    // debug_ring_init_local(vmmr->drr);
    // debug_ring_init_local(vmmr->drr);
    // debug_ring_init_local(vmmr->drr);

    // TEST #4: This test test if we run this code from in the this function.
    // In this case, it still crashes, but it takes longer to do so.
    // {
    //     vmmr->drr->epos = 0;
    //     vmmr->drr->spos = 0;

    //     for (auto i = 0; i < vmmr->drr->len; i++)
    //         vmmr->drr->buf[i] = '\0';

    //     vmmr->drr->epos = 0;
    //     vmmr->drr->spos = 0;

    //     for (auto i = 0; i < vmmr->drr->len; i++)
    //         vmmr->drr->buf[i] = '\0';

    //     vmmr->drr->epos = 0;
    //     vmmr->drr->spos = 0;

    //     for (auto i = 0; i < vmmr->drr->len; i++)
    //         vmmr->drr->buf[i] = '\0';

    //     vmmr->drr->epos = 0;
    //     vmmr->drr->spos = 0;

    //     for (auto i = 0; i < vmmr->drr->len; i++)
    //         vmmr->drr->buf[i] = '\0';

    //     vmmr->drr->epos = 0;
    //     vmmr->drr->spos = 0;

    //     for (auto i = 0; i < vmmr->drr->len; i++)
    //         vmmr->drr->buf[i] = '\0';
    // }

    // TEST #5: This test case runs the actual code that we are supposed to
    // run. I do it many times (just like above), as this causes the crash to
    // happen faster.
    //
    // if (vcpu == 0 || memory_manager == 0)
    //     return VMM_ERROR_INVALID_ENTRY_FACTORY;

    // auto vcpu = ef()->get_vcpu_factory()->get_vcpu(0);
    // auto memory_manager = ef()->get_memory_manager();

    // if (vcpu->get_debug_ring()->init(vmmr->drr) != debug_ring_error::success)
    //     return VMM_ERROR_INVALID_DRR;

    // if (vcpu->get_debug_ring()->init(vmmr->drr) != debug_ring_error::success)
    //     return VMM_ERROR_INVALID_DRR;

    // if (vcpu->get_debug_ring()->init(vmmr->drr) != debug_ring_error::success)
    //     return VMM_ERROR_INVALID_DRR;

    // if (vcpu->get_debug_ring()->init(vmmr->drr) != debug_ring_error::success)
    //     return VMM_ERROR_INVALID_DRR;

    // if (vcpu->get_debug_ring()->init(vmmr->drr) != debug_ring_error::success)
    //     return VMM_ERROR_INVALID_DRR;

    std::cout << "============================================ stop" << std::endl;

    // #########################################################################
    // Testing Code
    // #########################################################################

    // -------------------------------------------------------------------------
    // Initialize Debugging

    // TODO: At some point, we are going to have to be told what CPU we are
    // starting on, and then get the VCPU for that CPU and initialize it.
    // Since we only support single core for now, we use 0.

    // TODO: There are a lot of train wrecks in the code here that need to be
    //       removed.

    // auto vcpu = ef()->get_vcpu_factory()->get_vcpu(0);
    // auto memory_manager = ef()->get_memory_manager();

    // if (vcpu == 0 || memory_manager == 0)
    //     return VMM_ERROR_INVALID_ENTRY_FACTORY;

    // if (vcpu->get_debug_ring()->init(vmmr->drr) != debug_ring_error::success)
    //     return VMM_ERROR_INVALID_DRR;

    // INIT_IOSTREAM();

    // // -------------------------------------------------------------------------
    // // Memory Managment

    // for (auto i = 0; i < MAX_PAGES; i++)
    // {
    //     auto pg = page(vmmr->pages[i]);

    //     if (memory_manager->add_page(pg) != memory_manager_error::success)
    //         return VMM_ERROR_INVALID_PAGES;
    // }

    // // -------------------------------------------------------------------------
    // // Initialize and Start the VMM

    // auto vmm = vcpu->get_vmm();
    // auto intrinsics = vcpu->get_intrinsics();

    // if (vmm->init(intrinsics, memory_manager) != vmm_error::success)
    //     return VMM_ERROR_VMM_INIT_FAILED;

    // if (vmm->start() != vmm_error::success)
    //     return VMM_ERROR_VMM_START_FAILED;

    // // -------------------------------------------------------------------------
    // // Initialize and Luanch the VMCS

    // auto vmcs = vcpu->get_vmcs();

    // if (vmcs->init(intrinsics, memory_manager) != vmcs_error::success)
    //     return VMM_ERROR_VMM_INIT_FAILED;

    // if (vmcs->launch() != vmcs_error::success)
    //     return VMM_ERROR_VMM_START_FAILED;

    return 0;
}

void *
stop_vmm_trampoline(void *arg)
{
    if (arg != 0)
        return VMM_ERROR_INVALID_ARG;

    // auto vcpu = ef()->get_vcpu_factory()->get_vcpu(0);
    // auto memory_manager = ef()->get_memory_manager();

    // if (vcpu == 0 || memory_manager == 0)
    //     return VMM_ERROR_INVALID_ENTRY_FACTORY;

    // // -------------------------------------------------------------------------
    // // Stop the VMM

    // auto vmm = vcpu->get_vmm();

    // if (vmm->stop() != vmm_error::success)
    //     return VMM_ERROR_VMM_STOP_FAILED;

    return 0;
}

// =============================================================================
// C Entry Functions
// =============================================================================

extern "C" void *
start_vmm(void *arg)
{
    return start_vmm_trampoline(arg);
}

extern "C" void *
stop_vmm(void *arg)
{
    return stop_vmm_trampoline(arg);
}
