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

    .globl  _read_cr0
    .type   _read_cr0, @function
_read_cr0:
    mov rax, cr0
    ret

    .globl  _write_cr0
    .type   _write_cr0, @function
_write_cr0:
    mov cr0, rdi
    ret

    .globl  _read_cr2
    .type   _read_cr2, @function
_read_cr2:
    mov rax, cr2
    ret

    .globl  _write_cr2
    .type   _write_cr2, @function
_write_cr2:
    mov cr2, rdi
    ret

    .globl  _read_cr3
    .type   _read_cr3, @function
_read_cr3:
    mov rax, cr3
    ret

    .globl  _write_cr3
    .type   _write_cr3, @function
_write_cr3:
    mov cr3, rdi
    ret

    .globl  _read_cr4
    .type   _read_cr4, @function
_read_cr4:
    mov rax, cr4
    ret

    .globl  _write_cr4
    .type   _write_cr4, @function
_write_cr4:
    mov cr4, rdi
    ret

    .globl  _read_cr8
    .type   _read_cr8, @function
_read_cr8:
    mov rax, cr8
    ret

    .globl  _write_cr8
    .type   _write_cr8, @function
_write_cr8:
    mov cr8, rdi
    ret

    .globl  _write_xcr0
    .type   _write_xcr0, @function
_write_xcr0:
    mov rax, rdi
    mov rdx, rdi
    shr rdx, 32
    mov rcx, 0
    xsetbv

    ret
