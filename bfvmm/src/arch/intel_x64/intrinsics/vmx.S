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

_vmx_failure:
    mov rax, 0x0
    ret

_vmx_success:
    mov rax, 0x1
    ret

    .globl  _vmxon
    .type   _vmxon, @function
_vmxon:
    vmxon [rdi]
    jbe _vmx_failure
    jmp _vmx_success

    .globl  _vmxoff
    .type   _vmxoff, @function
_vmxoff:
    vmxoff
    jbe _vmx_failure
    jmp _vmx_success

    .globl  _vmclear
    .type   _vmclear, @function
_vmclear:
    vmclear [rdi]
    jbe _vmx_failure
    jmp _vmx_success

    .globl  _vmptrld
    .type   _vmptrld, @function
_vmptrld:
    vmptrld [rdi]
    jbe _vmx_failure
    jmp _vmx_success

    .globl  _vmptrst
    .type   _vmptrst, @function
_vmptrst:
    vmptrst [rdi]
    jbe _vmx_failure
    jmp _vmx_success

    .globl  _vmread
    .type   _vmread, @function
_vmread:
    vmread [rsi], rdi
    jbe _vmx_failure
    jmp _vmx_success

    .globl  _vmwrite
    .type   _vmwrite, @function
_vmwrite:
    vmwrite rdi, rsi
    jbe _vmx_failure
    jmp _vmx_success

    .globl  _invept
    .type   _invept, @function
_invept:
    invept rdi, [rsi]
    jbe _vmx_failure
    jmp _vmx_success

    .globl  _invvpid
    .type   _invvpid, @function
_invvpid:
    invvpid rdi, [rsi]
    jbe _vmx_failure
    jmp _vmx_success
