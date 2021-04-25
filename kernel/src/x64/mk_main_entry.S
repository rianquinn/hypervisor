/**
 * @copyright
 * Copyright (C) 2020 Assured Information Security, Inc.
 *
 * @copyright
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @copyright
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * @copyright
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

    .code64
    .intel_syntax noprefix

    .globl  mk_main_entry
    .type   mk_main_entry, @function
mk_main_entry:

    /**
     * NOTE:
     * - The first thing we need to do is save off RDI for the fast fail
     *   handler. If it is called, it will need the args that this function
     *   was provided, so we leave this on the stack for it. Since the state
     *   save has the correct stack pointer, we can leave it in this state
     *   as a safe return that uses the Root VP state will use the correct
     *   stack pointer, while a failure will use the current stack pointer
     *   with this return address on it.
     */

    push rdi

    /**
     * NOTE:
     * - The next thing to do is get the TLS block for this PP. Each PP has
     *   it's own TLS block (both in the microkernel, and in each extension)
     *   which means that our definition of a thread is similar to that of
     *   Intel's and AMD's, meaning each logical core is a thread.
     * - The loader will tell us in the args that it provided what the PPID
     *   is. Remember that this entry point will be called for each PP, so it
     *   is called more than once. Once we have the PPID, we can calculate
     *   which TLS block to grab based on the size of each TLS block.
     */

    xor rbx, rbx
    mov bx, [rdi]

    mov rax, rbx
    mov rdx, 0x300
    mul rdx
    lea rsi, [rip + g_tls_blocks]
    add rsi, rax

    /**
     * NOTE:
     * - Next we program GS with the location of the TLS block so that we
     *   can index into the TLS block using GS.
     */

    mov ecx, 0xC0000101
    mov rax, rsi
    mov rdx, rsi
    shr rdx, 32
    wrmsr

    /**
     * NOTE:
     * - From here we need to set the "self" pointer in the TLS block as
     *   well as the PPID to the TLS block so that we always know what the
     *   PPID is no matter where we are.
     */

    mov gs:[0x200], rsi
    mov gs:[0x208], bx

    /**
     * NOTE:
     * - To start, there are no active extensions, VMs, VPs or VPSs.
     */

    mov rax, 0xFFFFFFFFFFFFFFFF
    mov gs:[0x238], rax

    /**
     * NOTE:
     * - Next we set some of the fast fail entry points in the TLS block.
     *   These will be used when an error or exception occurs so that
     *   we can gracefully handle issues.
     */

    lea rax, [rip + mk_main_fast_fail_entry]
    mov gs:[0x190], rax
    lea rax, [rip + call_ext_fast_fail_entry]
    mov gs:[0x1A0], rax
    lea rax, [rip + dispatch_syscall_fast_fail_entry]
    mov gs:[0x1B0], rax

    /**
     * NOTE:
     * - Next we need to set the number of online PPs on the system.
     *   The microkernel will need to know this so that it can properly set
     *   up it's internal resources.
     */

    mov ax, [rdi + 0x002]
    mov gs:[0x20A], ax

    /**
     * NOTE:
     * - Next we need to invalidate the loaded VPSID. This is only used on
     *   Intel CPUs and is used to determine which VMCS is currently loaded.
     *   We cannot use the active VPSID here because an extension can read
     *   and write to any VPS it wants, even if it is not active.
     */

    mov ax, 0xFFFF
    mov gs:[0x20C], ax

    /**
     * NOTE:
     * - Next we store the location of the MK and Root VP state save areas
     *   that the loader created for us. For the most part, we only really
     *   need the Root VP state as we will use this to return back to the
     *   Root VP once we start the hypervisor on this PP, but just in case,
     *   we also provide the MK state as well. In general, the microkernel
     *   is really unware of the state that the loader gives it.
     */

    mov rax, [rdi + 0x008]
    mov gs:[0x228], rax
    mov rax, [rdi + 0x010]
    mov gs:[0x230], rax

    /**
     * NOTE:
     * - Next we store the pointer to the debug ring that the loader has
     *   set up for us. This is needed so that we have somewhere to put
     *   debug information.
     */

    lea rax, [rip + g_debug_ring]
    mov rdx, [rdi + 0x018]
    mov [rax], rdx

    /**
     * NOTE:
     * - Before we can continue, we need to save off the arguments for
     *   the mk_main_trampoline function. These will be poped right before
     *   calling this function.
     */

    push rsi
    push rdi

    /**
     * NOTE:
     * - Set up the IDT with the actual ESRs. Before we can do this, we need
     *   to lock NMIs. Any NMIs that come in can only set the pending bit
     *   in the TLS until a run occurs. Once a run occurs, we can handle
     *   the NMI from there (or the promote logic will handle it in the
     *   event that an error occurs).
     * - Once we install the new ESRs, we can transfer the NMI bit from the
     *   root state to the TLS.
     */

    mov rax, 0x1
    mov gs:[0x258], rax

    mov rdi, 0
    lea rsi, [rip + dispatch_esr_entry_0]
    call set_esr

    mov rdi, 1
    lea rsi, [rip + dispatch_esr_entry_1]
    call set_esr

    mov rdi, 2
    lea rsi, [rip + dispatch_esr_entry_2]
    call set_esr

    mov rdi, 3
    lea rsi, [rip + dispatch_esr_entry_3]
    call set_esr

    mov rdi, 4
    lea rsi, [rip + dispatch_esr_entry_4]
    call set_esr

    mov rdi, 5
    lea rsi, [rip + dispatch_esr_entry_5]
    call set_esr

    mov rdi, 6
    lea rsi, [rip + dispatch_esr_entry_6]
    call set_esr

    mov rdi, 7
    lea rsi, [rip + dispatch_esr_entry_7]
    call set_esr

    mov rdi, 8
    lea rsi, [rip + dispatch_esr_entry_8]
    call set_esr

    mov rdi, 10
    lea rsi, [rip + dispatch_esr_entry_10]
    call set_esr

    mov rdi, 11
    lea rsi, [rip + dispatch_esr_entry_11]
    call set_esr

    mov rdi, 12
    lea rsi, [rip + dispatch_esr_entry_12]
    call set_esr

    mov rdi, 13
    lea rsi, [rip + dispatch_esr_entry_13]
    call set_esr

    mov rdi, 14
    lea rsi, [rip + dispatch_esr_entry_14]
    call set_esr

    mov rdi, 16
    lea rsi, [rip + dispatch_esr_entry_16]
    call set_esr

    mov rdi, 17
    lea rsi, [rip + dispatch_esr_entry_17]
    call set_esr

    mov rdi, 18
    lea rsi, [rip + dispatch_esr_entry_18]
    call set_esr

    mov rdi, 19
    lea rsi, [rip + dispatch_esr_entry_19]
    call set_esr

    /**
     * NOTE:
     * - Next, we need to store the syscall handler location. This will be
     *   used by extensions to make syscalls.
     */

    mov ecx, 0xC0000082
    lea rax, [rip + dispatch_syscall_entry]
    mov rdx, rax
    shr rdx, 32
    wrmsr

    /**
     * NOTE:
     * - Next we transfer the NMI pending bit. If this is set, we need to hand
     *   it to the extension so that it can handle the NMI appropriately as
     *   the microkernel has no way of handling NMIs, so basically any NMI
     *   that might fire at any point during the loading process has to be
     *   recorded and transfered all the way to the extension so that it can
     *   handle it properly.
     */

    pop rdi

    mov rdx, [rdi + 0x010]
    mov rax, [rdx + 0x318]
    mov gs:[0x260], rax

    xor rax, rax
    mov [rdx + 0x318], rax

    pop rsi

    /**
     * NOTE:
     * - This next block of assembly is seen throughout the assembly code.
     *   Basically, it stores the information needed for fast failing. Each
     *   time we enter a new context like calling into an extension, handling
     *   a syscall, etc, we need to swap around the fast fail handler and RSP
     *   so that we know where to return to in the event of an error.
     */

    mov gs:[0x198], rsp
    mov rax, gs:[0x190]
    mov gs:[0x180], rax
    mov rax, gs:[0x198]
    mov gs:[0x188], rax

    call mk_main_trampoline
    jmp return_to_current_fast_fail

    .size mk_main_entry, .-mk_main_entry

    /**************************************************************************/
    /* Fast Fail Routine                                                      */
    /**************************************************************************/

    .globl  mk_main_fast_fail_entry
    .type   mk_main_fast_fail_entry, @function
mk_main_fast_fail_entry:

    pop rdi

    mov rdi, [rdi + 0x010]
    mov rsi, 1
    jmp promote

    .size mk_main_fast_fail_entry, .-mk_main_fast_fail_entry



    .globl  memcpy
    .type   memcpy, @function
memcpy:

    mov     rax, rdi
    mov     rcx, rdx
    rep     movsb

    ret
    int 3

    .size memcpy, .-memcpy



    .globl  memset
    .type   memset, @function
memset:

    mov     r10, rdi
    mov     rax, rsi
    mov     rcx, rdx
    rep     stosb
    mov     rax, r10

    ret
    int 3

    .size memset, .-memset
