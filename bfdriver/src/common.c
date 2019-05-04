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

typedef struct thread_context_t tc_t;

/* -------------------------------------------------------------------------- */
/* Global                                                                     */
/* -------------------------------------------------------------------------- */

uint8_t *g_vmm = nullptr;
uint64_t g_vmm_size = 0;
uint8_t *g_vmm_mem = nullptr;
uint64_t g_vmm_mem_size = 0;
uint8_t *g_vmm_mem_node_tree = nullptr;
uint64_t g_vmm_mem_node_tree_size = 0;
_start_t g_vmm_start = nullptr;
status_t g_vmm_status = VMM_UNLOADED;

uint64_t g_num_cpus_started = 0;

uint64_t g_tls = 0;
uint64_t g_stack = 0;

uint64_t g_tls_size = 0;
uint64_t g_stack_size = 0;
uint64_t g_stack_top = 0;

/* -------------------------------------------------------------------------- */
/* Helpers                                                                    */
/* -------------------------------------------------------------------------- */

static inline status_t
private_is_power_of_2(uint64_t val)
{
    if (val == 0) {
        return BFFAILURE;
    }

    while (val > 1) {
        if (val % 2 != 0) {
            return BFFAILURE;
        }

        val >>= 1;
    }

    return BFSUCCESS;
}

static inline status_t
private_setup_stack(void)
{
    g_stack_size = STACK_SIZE * 2;

    g_stack = (uint64_t)platform_alloc_rw(g_stack_size);
    if (g_stack == 0) {
        return BFFAILURE;
    }

    g_stack_top = g_stack + g_stack_size;
    g_stack_top = (g_stack_top & ~(STACK_SIZE - 1)) - 1;

    platform_memset((void *)g_stack, 0, g_stack_size);
    return BFSUCCESS;
}

static inline status_t
private_setup_tls(void)
{
    g_tls_size = THREAD_LOCAL_STORAGE_SIZE * platform_num_cpus();

    g_tls = (uint64_t)platform_alloc_rw(g_tls_size);
    if (g_tls == 0) {
        return BFFAILURE;
    }

    platform_memset((void *)g_tls, 0, g_tls_size);
    return BFSUCCESS;
}

static inline status_t
private_add_md(uint64_t virt, uint64_t type)
{
    status_t ret = 0;
    struct memory_descriptor md = {0, 0, 0};

    md.virt = virt;
    md.phys = (uint64_t)platform_virt_to_phys((void *)md.virt);
    md.type = type;

    ret = platform_call_vmm_on_core(0, BF_REQUEST_ADD_MD, (uint64_t)&md, 0);
    if (ret != BFSUCCESS) {
        return ret;
    }

    return BFSUCCESS;
}

// static inline status_t
// private_add_md_to_memory_manager(struct bfelf_binary_t *module)
// {
//     // bfelf64_word s = 0;

//     // for (s = 0; s < bfelf_file_get_num_load_instrs(&module->ef); s++) {

//     //     int64_t ret = 0;

//     //     uint64_t exec_s = 0;
//     //     uint64_t exec_e = 0;
//     //     const struct bfelf_load_instr *instr = 0;

//     //     ret = bfelf_file_get_load_instr(&module->ef, s, &instr);
//     //     bfignored(ret);

//     //     exec_s = (uint64_t)module->exec + instr->mem_offset;
//     //     exec_e = (uint64_t)module->exec + instr->mem_offset + instr->memsz;
//     //     exec_s &= ~(BAREFLANK_PAGE_SIZE - 1);
//     //     exec_e &= ~(BAREFLANK_PAGE_SIZE - 1);

//     //     for (; exec_s <= exec_e; exec_s += BAREFLANK_PAGE_SIZE) {
//     //         if ((instr->perm & bfpf_x) != 0) {
//     //             ret = private_add_md(
//     //                       exec_s, MEMORY_TYPE_R | MEMORY_TYPE_E);
//     //         }
//     //         else {
//     //             ret = private_add_md(
//     //                       exec_s, MEMORY_TYPE_R | MEMORY_TYPE_W);
//     //         }

//     //         if (ret != BFSUCCESS) {
//     //             return ret;
//     //         }
//     //     }
//     // }

//     return BFSUCCESS;
// }

static inline status_t
private_add_tss_mds(void)
{
    uint64_t i = 0;
    status_t ret = 0;

    for (i = 0; i < g_tls_size; i += BAREFLANK_PAGE_SIZE) {
        ret = private_add_md(g_tls + i, MEMORY_TYPE_R | MEMORY_TYPE_W);
        if (ret != BFSUCCESS) {
            return ret;
        }
    }

    return ret;
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
    if (g_vmm != nullptr) {
        platform_free_rwe(g_vmm, g_vmm_size);
    }

    if (g_vmm_mem != nullptr) {
        platform_free_rw(g_vmm_mem, g_vmm_mem_size);
    }

    if (g_tls != 0) {
        platform_free_rw((void *)g_tls, g_tls_size);
    }

    if (g_stack != 0) {
        platform_free_rw((void *)g_stack, g_stack_size);
    }

    g_vmm = nullptr;
    g_vmm_size = 0;
    g_vmm_mem = nullptr;
    g_vmm_mem_size = 0;
    g_vmm_mem_node_tree = nullptr;
    g_vmm_mem_node_tree_size = 0;
    g_vmm_start = nullptr;
    g_vmm_status = VMM_UNLOADED;

    g_num_cpus_started = 0;

    g_tls = 0;
    g_stack = 0;

    g_tls_size = 0;
    g_stack_size = 0;
    g_stack_top = 0;
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

    ret = private_is_power_of_2(mem);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = private_setup_stack();
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = private_setup_tls();
    if (ret != BFSUCCESS) {
        goto failure;
    }

    ret = bfelf_file_init(file, size, &ef);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    g_vmm_size = ef.size;
    g_vmm_mem_size = mem;

    g_vmm = (uint8_t *)platform_alloc_rwe(g_vmm_size);
    if (g_vmm == nullptr) {
        goto failure;
    }
BFALERT("line: %d\n", __LINE__);

    platform_memset(g_vmm, 0, g_vmm_size);

    ret = bfelf_file_load(g_vmm, nullptr, &ef);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    g_vmm_start = (_start_t)ef.entry;

BFALERT("line: %d\n", __LINE__);
    g_vmm_mem = (uint8_t *)platform_alloc_rw(g_vmm_mem_size);
    if (g_vmm == nullptr) {
        goto failure;
    }

    platform_memset(g_vmm_mem, 0, g_vmm_mem_size);

BFALERT("g_vmm: %llx\n", (uint64_t)g_vmm);
BFALERT("g_vmm_mem: %llx\n", (uint64_t)g_vmm_mem);
    g_vmm_mem_node_tree_size = platform_call_vmm_on_core(
        0, BF_REQUEST_SET_MEM, (uint64_t)g_vmm_mem, g_vmm_mem_size);
    if (g_vmm_mem_node_tree_size == 0) {
        goto failure;
    }

BFALERT("line: %d\n", __LINE__);
    g_vmm_mem_node_tree = (uint8_t *)platform_alloc_rw(g_vmm_mem_node_tree_size);
    if (g_vmm_mem_node_tree == nullptr) {
        goto failure;
    }
BFALERT("line: %d\n", __LINE__);
    platform_memset(g_vmm_mem_node_tree, 0, g_vmm_mem_node_tree_size);

BFALERT("line: %d\n", __LINE__);
    ret = platform_call_vmm_on_core(
        0, BF_REQUEST_SET_MEM_NODE_TREE, (uint64_t)g_vmm_mem_node_tree, 0);
    if (ret != BFSUCCESS) {
        goto failure;
    }

BFALERT("line: %d\n", __LINE__);
    ret = platform_call_vmm_on_core(
        0, BF_REQUEST_INIT, ef.init_array_addr, ef.init_array_size);
BFALERT("ret: %llx\n", (uint64_t)ret);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    // ret = platform_call_vmm_on_core(
    //     0, BF_REQUEST_EH_FRAME, ef.eh_frame_addr, ef.eh_frame_size);
    // if (ret != BFSUCCESS) {
    //     goto failure;
    // }

    // ret = private_add_mds();
    // if (ret != BFSUCCESS) {
    //     goto failure;
    // }

    // ret = private_add_tss_mds();
    // if (ret != BFSUCCESS) {
    //     goto failure;
    // }

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

    for (cpuid = g_num_cpus_started - 1; cpuid >= 0 ; cpuid--) {
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
    struct _start_args_t args = {request, arg1, arg2};
    tc_t *tc = (tc_t *)(g_stack_top - sizeof(tc_t));

    tc->cpuid = cpuid;
    tc->tlsptr = (uint64_t *)(g_tls + (THREAD_LOCAL_STORAGE_SIZE * cpuid));

    return g_vmm_start(g_stack_top - sizeof(tc_t) - 1, &args);
}
