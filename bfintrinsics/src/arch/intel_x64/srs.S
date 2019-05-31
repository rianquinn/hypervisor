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

    .globl  _read_es
    .type   _read_es, @function
_read_es:
    xor rax, rax
    mov ax, es
    ret

    .globl  _write_es
    .type   _write_es, @function
_write_es:
    xor rax, rax
    mov es, di
    ret

    .globl  _read_cs
    .type   _read_cs, @function
_read_cs:
    xor rax, rax
    mov ax, cs
    ret

    .globl  _write_cs
    .type   _write_cs, @function
_write_cs:
    pop rax
    push di
    push rax
    retf

    .globl  _read_ss
    .type   _read_ss, @function
_read_ss:
    xor rax, rax
    mov ax, ss
    ret

    .globl  _write_ss
    .type   _write_ss, @function
_write_ss:
    mov ss, di
    ret

    .globl  _read_ds
    .type   _read_ds, @function
_read_ds:
    xor rax, rax
    mov ax, ds
    ret

    .globl  _write_ds
    .type   _write_ds, @function
_write_ds:
    mov ds, di
    ret

    .globl  _read_fs
    .type   _read_fs, @function
_read_fs:
    xor rax, rax
    mov ax, fs
    ret

    .globl  _write_fs
    .type   _write_fs, @function
_write_fs:
    mov fs, di
    ret

    .globl  _read_gs
    .type   _read_gs, @function
_read_gs:
    xor rax, rax
    mov ax, gs
    ret

    .globl  _write_gs
    .type   _write_gs, @function
_write_gs:
    mov gs, di
    ret

    .globl  _read_ldtr
    .type   _read_ldtr, @function
_read_ldtr:
    xor rax, rax
    sldt ax
    ret

    .globl  _write_ldtr
    .type   _write_ldtr, @function
_write_ldtr:
    lldt di
    ret

    .globl  _read_tr
    .type   _read_tr, @function
_read_tr:
    xor rax, rax
    str ax
    ret

    .globl  _write_tr
    .type   _write_tr, @function
_write_tr:
    ltr di
    ret
