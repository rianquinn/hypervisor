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

    .globl  _cpuid_eax
    .type   _cpuid_eax, @function
_cpuid_eax:
    push rbx

    mov eax, edi
    cpuid

    pop rbx
    ret

    .globl  _cpuid_ebx
    .type   _cpuid_ebx, @function
_cpuid_ebx:
    push rbx

    mov eax, edi
    cpuid
    mov eax, ebx

    pop rbx
    ret

    .globl  _cpuid_ecx
    .type   _cpuid_ecx, @function
_cpuid_ecx:
    push rbx

    mov eax, edi
    cpuid
    mov eax, ecx

    pop rbx
    ret

    .globl  _cpuid_edx
    .type   _cpuid_edx, @function
_cpuid_edx:
    push rbx

    mov eax, edi
    cpuid
    mov eax, edx

    pop rbx
    ret

    .globl  _cpuid_subeax
    .type   _cpuid_subeax, @function
_cpuid_subeax:
    push rbx

    mov eax, edi
    mov ecx, esi
    cpuid

    pop rbx
    ret

    .globl  _cpuid_subebx
    .type   _cpuid_subebx, @function
_cpuid_subebx:
    push rbx

    mov eax, edi
    mov ecx, esi
    cpuid
    mov eax, ebx

    pop rbx
    ret

    .globl  _cpuid_subecx
    .type   _cpuid_subecx, @function
_cpuid_subecx:
    push rbx

    mov eax, edi
    mov ecx, esi
    cpuid
    mov eax, ecx

    pop rbx
    ret

    .globl  _cpuid_subedx
    .type   _cpuid_subedx, @function
_cpuid_subedx:
    push rbx

    mov eax, edi
    mov ecx, esi
    cpuid
    mov eax, edx

    pop rbx
    ret

    .globl  _cpuid
    .type   _cpuid, @function
_cpuid:
    push rbx

    mov r8, rdi
    mov r9, rsi
    mov r10, rdx
    mov r11, rcx

    mov eax, [r8]
    mov ebx, [r9]
    mov ecx, [r10]
    mov edx, [r11]

    cpuid

    mov [r8], eax
    mov [r9], ebx
    mov [r10], ecx
    mov [r11], edx

    mov rax, 0

    pop rbx
    ret
