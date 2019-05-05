/*
 * Copyright (C) 2019 Assured Information Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <common.h>

#include <bftypes.h>
#include <bfdebug.h>
#include <bfmemory.h>
#include <bfsupport.h>
#include <bfplatform.h>
#include <bfconstants.h>
#include <bfelf_loader.h>
#include <bfthreadcontext.h>

/* -------------------------------------------------------------------------- */
/* Global                                                                     */
/* -------------------------------------------------------------------------- */

uint8_t *g_vmm = nullptr;
uint64_t g_vmm_size = 0;
uint8_t *g_mem_leafs = nullptr;
uint64_t g_mem_leafs_size = 0;
uint8_t *g_mem_nodes = nullptr;
uint64_t g_mem_nodes_size = 0;
_start_t g_vmm_start = nullptr;
status_t g_vmm_status = VMM_UNLOADED;

uint8_t *g_tls = nullptr;
uint64_t g_tls_size = 0;

uint8_t *g_stack = nullptr;
uint64_t g_stack_size = 0;

uint64_t g_num_cpus_started = 0;

/* -------------------------------------------------------------------------- */
/* Helpers                                                                    */
/* -------------------------------------------------------------------------- */

static inline status_t
private_setup_vmm_memory(uint64_t vmm_size, uint64_t vmm_mem_size)
{
    uint32_t k = log2n(vmm_mem_size) - log2n(BFPAGE_SIZE);

    g_vmm_size = vmm_size;
    g_mem_leafs_size = num_leafs(k) * BFPAGE_SIZE;
    g_mem_nodes_size = num_nodes(k) * BFNODE_SIZE;
    g_stack_size = BFSTACK_SIZE * 2;
    g_tls_size = BFTLS_SIZE * platform_num_cpus();

    g_vmm = (uint8_t *)platform_alloc_rwe(g_vmm_size);
    if (g_vmm == 0) {
        return BFFAILURE;
    }

    g_mem_leafs = (uint8_t *)platform_alloc_rw(g_mem_leafs_size);
    if (g_mem_leafs == 0) {
        return BFFAILURE;
    }

    g_mem_nodes = (uint8_t *)platform_alloc_rw(g_mem_nodes_size);
    if (g_mem_nodes == 0) {
        return BFFAILURE;
    }

    g_stack = (uint8_t *)platform_alloc_rw(g_stack_size);
    if (g_stack == 0) {
        return BFFAILURE;
    }

    g_tls = (uint8_t *)platform_alloc_rw(g_tls_size);
    if (g_tls == 0) {
        return BFFAILURE;
    }

    /**
     * Notes:
     *
     * We need to memset the VMM memory because of the BSS section and any
     * other portions of the VMM that are not initialized by the ELF loader.
     * We also need to zero out the nodes memory because this will be used
     * for bookkeeping and we want to make sure that nothing in there will
     * affect that. We do not want to memset the VMM's leaf memory which is
     * the memory that is actually given out for malloc/free. This will be
     * cleared as needed by the VMM itself. We also don't want to zero out
     * the stack memory as this is a waste of time. We do want to zero out
     * the TLS memory as this is expected.
     */

    platform_memset(g_vmm, 0, g_vmm_size);
    platform_memset(g_mem_nodes, 0, g_mem_nodes_size);
    platform_memset(g_tls, 0, g_tls_size);

    BFDEBUG("vmm addr: %llx\n", (uint64_t)g_vmm);
    BFDEBUG("vmm size: %llx\n", (uint64_t)g_vmm_size);
    BFDEBUG("mem addr: %llx\n", (uint64_t)g_mem_leafs);
    BFDEBUG("mem size: %llx\n", (uint64_t)g_mem_leafs_size);

    return BFSUCCESS;
}

static inline status_t
private_add_mds(uint8_t *addr, uint64_t size, uint64_t type)
{
    uint64_t i;
    status_t ret;
    struct memory_descriptor md;

    for (i = 0; i < size; i += BFPAGE_SIZE) {
        md.virt = (uint64_t)addr + i;
        md.phys = (uint64_t)platform_virt_to_phys(addr + i);
        md.type = type;

        ret = platform_call_vmm_on_core(0, BF_REQUEST_ADD_MD, (uint64_t)&md, 0);
        if (ret != BFSUCCESS) {
            return ret;
        }
    }

    return BFSUCCESS;
}

/* -------------------------------------------------------------------------- */
/* Implementation                                                             */
/* -------------------------------------------------------------------------- */

status_t
common_vmm_status(void)
{ return g_vmm_status; }

void
common_reset(void)
{
    platform_free_rwe(g_vmm, g_vmm_size);
    platform_free_rw(g_mem_leafs, g_mem_leafs_size);
    platform_free_rw(g_mem_nodes, g_mem_nodes_size);
    platform_free_rw(g_tls, g_tls_size);
    platform_free_rw(g_stack, g_stack_size);

    g_vmm = nullptr;
    g_vmm_size = 0;
    g_mem_leafs = nullptr;
    g_mem_leafs_size = 0;
    g_mem_nodes = nullptr;
    g_mem_nodes_size = 0;
    g_vmm_start = nullptr;
    g_vmm_status = VMM_UNLOADED;

    g_tls = nullptr;
    g_tls_size = 0;

    g_stack = nullptr;
    g_stack_size = 0;

    g_num_cpus_started = 0;
}

status_t
common_init(void)
{
    status_t ret = platform_init();
    if (ret != BFSUCCESS) {
        return ret;
    }

    common_reset();
    return BFSUCCESS;
}

status_t
common_fini(void)
{
    if (common_vmm_status() == VMM_RUNNING) {
        if (common_stop_vmm() != BFSUCCESS) {
            BFALERT("common_fini: failed to stop vmm\n");
        }
    }

    if (common_vmm_status() == VMM_LOADED) {
        if (common_unload_vmm() != BFSUCCESS) {
            BFALERT("common_fini: failed to unload vmm\n");
        }
    }

    if (common_vmm_status() == VMM_CORRUPT) {
        return BFFAILURE;
    }

    common_reset();
    return BFSUCCESS;
}

status_t
common_load_vmm(const void *file, uint64_t size, uint64_t mem)
{
    status_t ret = 0;
    struct bfelf_file_t ef;

    switch (common_vmm_status()) {
        case VMM_UNLOADED:
            break;
        default:
            return BFFAILURE;
    };

    ret = is_power_of_2(mem);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = bfelf_file_init(file, size, &ef);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = private_setup_vmm_memory(ef.size, mem);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = bfelf_file_load(g_vmm, nullptr, &ef);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    g_vmm_start = (_start_t)ef.entry;

    ret = platform_call_vmm_on_core(
        0, BF_REQUEST_SET_MEM_LEAFS, (uint64_t)g_mem_leafs, g_mem_leafs_size);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = platform_call_vmm_on_core(
        0, BF_REQUEST_SET_MEM_NODES, (uint64_t)g_mem_nodes, g_mem_nodes_size);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = platform_call_vmm_on_core(
        0, BF_REQUEST_INIT, ef.init_array_addr, ef.init_array_size);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = platform_call_vmm_on_core(
        0, BF_REQUEST_EH_FRAME, ef.eh_frame_addr, ef.eh_frame_size);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = private_add_mds(ef.rx_addr, ef.rx_size, MEMORY_TYPE_RX);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = private_add_mds(ef.rw_addr, ef.rw_size, MEMORY_TYPE_RW);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = private_add_mds(g_mem_leafs, g_mem_leafs_size, MEMORY_TYPE_RW);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = private_add_mds(g_mem_nodes, g_mem_nodes_size, MEMORY_TYPE_RW);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = private_add_mds(g_tls, g_tls_size, MEMORY_TYPE_RW);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = platform_call_vmm_on_core(
        0, BF_REQUEST_GLOBAL_INIT, 0, 0);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    g_vmm_status = VMM_LOADED;
    return BFSUCCESS;

failure:

    (void) common_unload_vmm();
    return ret;
}

status_t
common_unload_vmm(void)
{
    switch (common_vmm_status()) {
        case VMM_LOADED:
        case VMM_UNLOADED:
            break;
        default:
            return BFFAILURE;
    };

    common_reset();

    g_vmm_status = VMM_UNLOADED;
    return BFSUCCESS;
}

status_t
common_start_vmm(void)
{
    status_t ret = 0;
    uint64_t cpuid = 0;

    switch (common_vmm_status()) {
        case VMM_LOADED:
            break;
        default:
            return BFFAILURE;
    };

    for (cpuid = 0; cpuid < platform_num_cpus(); cpuid++) {
        ret = platform_call_vmm_on_core(cpuid, BF_REQUEST_VMM_INIT, cpuid, 0);
        if (ret != BFSUCCESS) {
            goto failure;
        }

        g_num_cpus_started++;
    }

    g_vmm_status = VMM_RUNNING;
    return BFSUCCESS;

failure:

    (void) common_stop_vmm();
    return ret;
}

status_t
common_stop_vmm(void)
{
    status_t ret = 0;
    uint64_t cpuid = 0;

    switch (common_vmm_status()) {
        case VMM_RUNNING:
            break;
        default:
            return BFFAILURE;
    };

    for (cpuid = g_num_cpus_started - 1; g_num_cpus_started > 0 ; cpuid--) {
        ret = platform_call_vmm_on_core(cpuid, BF_REQUEST_VMM_FINI, cpuid, 0);
        if (ret != BFSUCCESS) {
            goto corrupted;
        }

        g_num_cpus_started--;
    }

    g_vmm_status = VMM_LOADED;
    return BFSUCCESS;

corrupted:

    g_vmm_status = VMM_CORRUPT;
    return ret;
}

status_t
common_dump_vmm(struct debug_ring_resources_t **drr)
{
    status_t ret = 0;

    switch (common_vmm_status()) {
        case VMM_UNLOADED:
            return BFFAILURE;
        default:
            break;
    };

    ret = platform_call_vmm_on_core(0, BF_REQUEST_GET_DRR, (uint64_t)drr, 0);
    if (ret != BFSUCCESS) {
        return ret;
    }

    return BFSUCCESS;
}

status_t
common_call_vmm(
    uint64_t cpuid, uint64_t request, uint64_t arg1, uint64_t arg2)
{
    uint64_t stack = setup_stack(g_stack, cpuid, g_tls + (BFTLS_SIZE * cpuid));
    struct _start_args_t args = {request, arg1, arg2};

    return g_vmm_start(stack, &args);
}
