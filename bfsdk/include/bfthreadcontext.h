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

#ifndef BFTHREADCONTEXT
#define BFTHREADCONTEXT

#include <bftypes.h>
#include <bfconstants.h>

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

uint64_t _thread_context_get_sp(void);

/**
 * @struct thread_context_t
 *
 * Thread Context
 *
 * On the top of every stack pointer sits one of these structures, which is
 * used to identify thread specific information. For more information on
 * how this works, please see the following post:
 *
 * https://github.com/Bareflank/hypervisor/issues/213
 *
 * Note: If this struct changes, assembly code in the misc module will
 * likely have to change as well since we don't have a clean way to bridge
 * between C and NASM
 *
 * @var thread_context_t::unused
 *      unusd to ensure no overruns
 * @var thread_context_t::cpuid
 *      the cpuid of the thread
 * @var thread_context_t::tlsptr
 *      the TLS pointer of the thread
 * @var thread_context_t::canary
 *      ensure an overflow has not occured
 */
struct thread_context_t {
    uint64_t canary;
    uint8_t *tlsptr;
    uint64_t cpuid;
    uint64_t unused;
};

static inline uint64_t 
thread_context_cpuid(void)
{
    struct thread_context_t *tc;
    uint64_t stack = _thread_context_get_sp();

    /**
     * Notes:
     * 
     * We use the same math to get the top of the stack that we used
     * to align the stack. This makes sure that no matter where the 
     * stack is (unless something really bad happens), we can always 
     * find the top of the stack. 
     */
    stack = (stack & ~(STACK_SIZE - 1)) + STACK_SIZE;

    /**
     * Notes
     * 
     * Finally we just need to get the field that we care about and 
     * return it. 
     */ 
    tc = bfrcast(struct thread_context_t *, stack - sizeof(struct thread_context_t));
    return tc->cpuid;
}

static inline uint64_t *
thread_context_tlsptr(void)
{
    struct thread_context_t *tc;
    uint64_t stack = _thread_context_get_sp();

    /**
     * Notes:
     * 
     * We use the same math to get the top of the stack that we used
     * to align the stack. This makes sure that no matter where the 
     * stack is (unless something really bad happens), we can always 
     * find the top of the stack. 
     */
    stack = (stack & ~(STACK_SIZE - 1)) + STACK_SIZE;

    /**
     * Notes
     * 
     * Finally we just need to get the field that we care about and 
     * return it. 
     */ 
    tc = bfrcast(struct thread_context_t *, stack - sizeof(struct thread_context_t));
    return bfrcast(uint64_t *, tc->tlsptr);
}

static inline uint64_t 
thread_context_canary(void)
{
    struct thread_context_t *tc;
    uint64_t stack = _thread_context_get_sp();

    /**
     * Notes:
     * 
     * We use the same math to get the top of the stack that we used
     * to align the stack. This makes sure that no matter where the 
     * stack is (unless something really bad happens), we can always 
     * find the top of the stack. 
     */
    stack = (stack & ~(STACK_SIZE - 1)) + STACK_SIZE;

    /**
     * Notes
     * 
     * Finally we just need to get the field that we care about and 
     * return it. 
     */ 
    tc = bfrcast(struct thread_context_t *, stack - sizeof(struct thread_context_t));
    return tc->canary;
}

/**
 * Setup Stack
 *
 * The following function sets up the stack to match the algorithm defined
 * in the following issue (with some mods to cleanup math errors):
 *
 * https://github.com/Bareflank/hypervisor/issues/213
 *
 * ------------ 0x9050 <-- top of stack (0x1050 + STACK_SIZE * 2)
 * |          |
 * |   ---    | 0x8000 <-- actual top stack = top of stack & ~(STACK_SIZE - 1)
 * |   ---    | 0x7FF8 <-- unused
 * |   ---    | 0x7FF0 <-- cpuid
 * |   ---    | 0x7FE8 <-- TLS pointer
 * |   ---    | 0x7FE0 <-- canary
 * |   ---    | 0x7FDF <-- RSP = actual top stack - 0x20 - 1
 * |          |            
 * |          |
 * |          |
 * |   ---    | 0x4000 <-- bottom of stack
 * |          |
 * |          | Extra space can be used on overrun
 * |          |
 * ------------ 0x1050 <-- returned by platform_alloc_rw(STACK_SIZE * 2)
 * 
 * @param stack the stack pointer
 * @param cpuid the cpu ID for this thread
 * @param tlsptr the pointer to the TLS block for this thread
 * @return the stack pointer (in interger form)
 */
static inline uint64_t
setup_stack(uint8_t *stack, uint64_t cpuid, uint8_t *tlsptr)
{
    struct thread_context_t *tc;

    uint64_t btm = bfrcast(uint64_t, stack);
    uint64_t top = btm + (STACK_SIZE * 2);

    /**
     * Notes:
     * 
     * We need to align the actual stack pointer which is why we always
     * allocate x2 the memory that we actually need. This is a common 
     * trick when aligning memory that we do not have control of. 
     */
    top &= ~(STACK_SIZE - 1);

    /**
     * Notes
     * 
     * Now that we have the top of the stack, we can fill in our thread 
     * context structure. This way we can always use this same math to 
     * get back to this structure without the possibility of 
     * overrunning memory. 
     */ 
    tc = bfrcast(struct thread_context_t *, top - sizeof(struct thread_context_t));
    tc->cpuid = cpuid;
    tc->tlsptr = tlsptr;
    tc->canary = 0xBF42BF42BF42BF42; 

    /**
     * Finally we will return the location of the stack without the 
     * thread context added so that the code knows where the actual stack 
     * is
     */
    return top - sizeof(struct thread_context_t) - 1;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif
