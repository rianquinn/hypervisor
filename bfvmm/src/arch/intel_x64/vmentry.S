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

/*
 * VMCS Launch
 *
 * This function launches a vCPU using the VMLaunch instruction. There are
 * two different ways that you can launch a vCPU.
 * - host vCPU: on a host vCPU, when performing a VMLaunch, we are acutally
 *   performing a demotion. This means that the host OS is being placed in a VM
 *   in its current running state. The only thing we need to do in this case
 *   is execute the instruction and return. The problem is, we need to know
 *   what to set RIP to so that execution can continue. To do this, we use
 *   the call instruction which pushes a return address to the stack, which
 *   is what we set RIP to.
 * - guest vCPU: a guest vCPU starts a vCPU from a given state which is set
 *   by the software executing the VMLaunch. In this case, we need to set the
 *   state as directed and then VMLaunch will execute the guest vCPU as told.
 *   This is the typical use for this instruction, but be aware that this will
 *   only be called if an extension uses it. The base hypervisor doesn't create
 *   guest vCPUs. It only creates host vCPUs.
 */
    .code64
    .intel_syntax noprefix

    .globl  _vmlaunch
    .type   _vmlaunch, @function
_vmlaunch:
    mov rax, rdi

    push rbx
    push rbp
    push r12
    push r13
    push r14
    push r15

    mov rdi, [rax + 0x0A0]
    and rdi, 0xFFFFFFFFFFFF0000

    jz _vmlaunch_host
    jnz _vmlaunch_guest

done:

    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx

    ret

/*
 * VMLaunch Host vCPU.
 *
 * This function performs a VMLaunch on a host vCPU which executes the
 * VMLaunch instruction by setting the RIP to an address that we get from the
 * call instruction. What this does is it pushes a return address to the stack.
 * We cannot simply store "done" or any other label in RIP because the compiler
 * doesn't know where we are located in memory, so even if the compiler let
 * you do this, you would be storing an offset, not an actual address. The best
 * way to overcome this is to execute a call instruction which pushes a return
 * address to the stack. This return address contains the absolute address in
 * memory of the next instruction after the call instruction. We can then pop
 * this off of the stack which will give us an RIP that we can use. If the
 * VMLaunch function works, it will jump to RIP which is the instruction right
 * after the call instruction, which in this case will set rax to 1 (true) and
 * then calls done which will return with our custom epilog. If the VMLaunch
 * fails, we will return false as the VMLaunch function will fall through to
 * the instruction after that.
 */
_vmlaunch_host:
    call _vmlaunch_host_trick

    mov rax, 0x1
    jmp done

_vmlaunch_host_trick:
    pop rsi

    mov rdi, 0x0000681E
    vmwrite rdi, rsi
    mov rdi, 0x0000681C
    vmwrite rdi, rsp

    vmlaunch

    mov rax, 0x0
    jmp done

/*
 * VMLaunch Guest vCPU
 *
 * This function launches a guest vCPU. All vCPUs created by a user must be
 * a guest vCPU. The goal with this function is to set the state of the
 * registers that are not set by the VMCS when the VMLaunch occurs. Note that
 * a VMLaunch does not always occur when first launching a guest vCPU. If the
 * user clears the guest vCPU, a VMLaunch could occur again, on a valid VMExit
 * of an already running guest vCPU, so this code needs to resemble a VMResume
 * almost identically. Also note that this function does not return on success.
 * It will only return on failure.
 *
 * TODO:
 * Right now we only support fxsave/fxrstor, which means that guest vCPUs
 * do not support AVX+. If we want to support AVX+ we will need to add support
 * for XSAVE/XRSTOR in the future as we will need to preserve the guest state
 * properly on world switches.
 */
_vmlaunch_guest:

    mov rdi, [rax + 0x080]
    fxrstor [rdi]

    mov r15, [rax + 0x070]
    mov r14, [rax + 0x068]
    mov r13, [rax + 0x060]
    mov r12, [rax + 0x058]
    mov r11, [rax + 0x050]
    mov r10, [rax + 0x048]
    mov r9,  [rax + 0x040]
    mov r8,  [rax + 0x038]
    mov rdi, [rax + 0x030]
    mov rsi, [rax + 0x028]
    mov rbp, [rax + 0x020]
    mov rdx, [rax + 0x018]
    mov rcx, [rax + 0x010]
    mov rbx, [rax + 0x008]
    mov rax, [rax + 0x000]

    vmlaunch

    mov rax, 0x0
    jmp done

/*
 * VMResume
 *
 * This function performs a VMResume. A VMResume and a VMLaunch are
 * identical for a guest vCPU. They do exactly the same thing, with the only
 * difference being that one executes vmlaunch while the other executes a
 * vmresume (which is required by Intel). For a host vCPU, the execution of a
 * VMLaunch is different, but from that point on, the VMM will use a VMResume
 * (as a VMClear is not allowed on a host vCPU), and this code is used. It
 * should be noted that this code is the opposite of the VMExit logic. Think
 * of this as the epilog for the VMM and the VMExit logic is the prolog.
 */

    .globl  _vmresume
    .type   _vmresume, @function
_vmresume:
    mov rax, rdi

    push rbx
    push rbp
    push r12
    push r13
    push r14
    push r15

    mov rdi, [rax + 0x080]
    fxrstor [rdi]

    mov r15, [rax + 0x070]
    mov r14, [rax + 0x068]
    mov r13, [rax + 0x060]
    mov r12, [rax + 0x058]
    mov r11, [rax + 0x050]
    mov r10, [rax + 0x048]
    mov r9,  [rax + 0x040]
    mov r8,  [rax + 0x038]
    mov rdi, [rax + 0x030]
    mov rsi, [rax + 0x028]
    mov rbp, [rax + 0x020]
    mov rdx, [rax + 0x018]
    mov rcx, [rax + 0x010]
    mov rbx, [rax + 0x008]
    mov rax, [rax + 0x000]

    vmresume

    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx

    mov rax, 0x0
    ret

/*
 * VMPromote
 *
 * This function promotes the guest state to ring-1. This is a really complex
 * function that has to continue the execution of the guest, but in ring-1,
 * leaving the host state behind. Once the guest is in ring-1, VMX will be
 * turned off, resulting in the guest executing in ring0 again.
 *
 * This cannot be stressed enough..., this code has been a work-of-art over the
 * years, testing various different operating systems, nested hypervisors and
 * handling different bugs. Every line of code below has a purpose, including
 * where it is located. For example, RFLAGS has to be preserved, but it cannot
 * be the last thing executed, so the instructions after it is restored are
 * known not to change RFLAGS. If you need to modify this code, please reach
 * out to the community and ask first.
 */

    .globl  _vmprmote
    .type   _vmprmote, @function
_vmprmote:
    push rdi

    /*
     * Restore Control Registers
     */

    mov rsi, 0x00006800
    vmread rdi, rsi
    call _write_cr0

    mov rsi, 0x00006802
    vmread rdi, rsi
    push rdi

    and rdi, 0xFFFFFFFFFFFFF000
    call _write_cr3

    mov rsi, 0x00006804
    vmread rdi, rsi
    call _write_cr4

    pop rdi
    call _write_cr3

    mov rsi, 0x0000681A
    vmread rdi, rsi
    call _write_dr7

    /*
     * Restore GDT
     */

    mov rsi, 0x00006816
    vmread rdi, rsi
    push rdi

    mov rsi, 0x00004810
    vmread rdi, rsi
    push di

    mov rdi, rsp
    call _write_gdt

    /*
     * Restore IDT
     */

    mov rsi, 0x00006818
    vmread rdi, rsi
    push rdi

    mov rsi, 0x00004812
    vmread rdi, rsi
    push di

    mov rdi, rsp
    call _write_idt

    /*
     * Clear TSS Busy
     */

    mov rsi, 0x00006816
    vmread rdi, rsi
    mov rsi, 0x0000080E
    vmread rsi, rsi

    add rdi, rsi

    mov rax, 0xFFFFFDFFFFFFFFFF
    and [rdi], rax

    /*
     * Restore Selectors
     */

    mov rsi, 0x00000800
    vmread rdi, rsi
    call _write_es

    mov rsi, 0x00000802
    vmread rdi, rsi
    call _write_cs

    mov rsi, 0x00000804
    vmread rdi, rsi
    call _write_ss

    mov rsi, 0x00000806
    vmread rdi, rsi
    call _write_ds

    mov rsi, 0x00000808
    vmread rdi, rsi
    call _write_fs

    mov rsi, 0x0000080A
    vmread rdi, rsi
    call _write_gs

    mov rsi, 0x0000080C
    vmread rdi, rsi
    call _write_ldtr

    mov rsi, 0x0000080E
    vmread rdi, rsi
    call _write_tr

    /*
     * Restore MSRs
     */

    mov rdi, 0x000001D9
    mov rsi, 0x00002802
    vmread rsi, rsi
    call _write_msr

    mov rdi, 0x00000277
    mov rsi, 0x00002804
    vmread rsi, rsi
    call _write_msr

    mov rdi, 0xC0000080
    mov rsi, 0x00002806
    vmread rsi, rsi
    call _write_msr

    mov edi, 0x0000000A
    call _cpuid_eax
    cmp al, 0x00000002
    jl .perf_not_supported

    mov rdi, 0x0000038F
    mov rsi, 0x00002808
    vmread rsi, rsi
    call _write_msr

.perf_not_supported:

    mov rdi, 0x00000174
    mov rsi, 0x0000482A
    vmread rsi, rsi
    call _write_msr

    mov rdi, 0x00000175
    mov rsi, 0x00006824
    vmread rsi, rsi
    call _write_msr

    mov rdi, 0x00000176
    mov rsi, 0x00006826
    vmread rsi, rsi
    call _write_msr

    mov rdi, 0xC0000100
    mov rsi, 0x0000680E
    vmread rsi, rsi
    call _write_msr

    mov rdi, 0xC0000101
    mov rsi, 0x00006810
    vmread rsi, rsi
    call _write_msr

    /*
     * Final State Restoration
     */

    pop rax

    /*
     * Restore RSP
     */

    mov rsi, 0x0000681C
    vmread rdi, rsi
    mov rsp, rdi

    /*
     * Restore RIP
     */

    mov rsi, 0x0000681E
    vmread rdi, rsi
    push rdi

    /*
     * Restore RFLAGS
     */

    mov rsi, 0x00006820
    vmread rdi, rsi
    and rdi, 0xFFFFFFFFFFFFFDFF
    push rdi
    popf

    /*
     * Restore General Purpose Registers
     */

    mov rdi, [rax + 0x080]
    fxrstor [rdi]

    mov r15, [rax + 0x070]
    mov r14, [rax + 0x068]
    mov r13, [rax + 0x060]
    mov r12, [rax + 0x058]
    mov r11, [rax + 0x050]
    mov r10, [rax + 0x048]
    mov r9,  [rax + 0x040]
    mov r8,  [rax + 0x038]
    mov rdi, [rax + 0x030]
    mov rsi, [rax + 0x028]
    mov rbp, [rax + 0x020]
    mov rdx, [rax + 0x018]
    mov rcx, [rax + 0x010]
    mov rbx, [rax + 0x008]
    mov rax, [rax + 0x000]

    sti
    ret
