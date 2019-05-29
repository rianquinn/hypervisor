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
        .code64
        .intel_syntax noprefix

        .globl  _vmexit
        .type   _vmexit, @function
_vmexit:

    mov gs:[0x000], rax
    mov gs:[0x008], rbx
    mov gs:[0x010], rcx
    mov gs:[0x018], rdx
    mov gs:[0x020], rbp
    mov gs:[0x028], rsi
    mov gs:[0x030], rdi
    mov gs:[0x038], r8
    mov gs:[0x040], r9
    mov gs:[0x048], r10
    mov gs:[0x050], r11
    mov gs:[0x058], r12
    mov gs:[0x060], r13
    mov gs:[0x068], r14
    mov gs:[0x070], r15

    mov rdi, 0x00004402
    vmread gs:[0x078], rdi

    mov rdi, gs:[0x080]
    fxsave [rdi]

    mov rdi, gs:[0x088]
    call handle_vmexit

    /*
     * Generate an exception.
     *
     * This should never execute, so if it doesn, something horrible has
     * occured, like the unwinder not working right, or forgetting to resume.
     */
    int3
