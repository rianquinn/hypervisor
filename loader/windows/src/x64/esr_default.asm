; @copyright
; Copyright (C) 2020 Assured Information Security, Inc.
;
; @copyright
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; @copyright
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
;
; @copyright
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
; SOFTWARE.

include constants_masm.h

    esr_default_text SEGMENT ALIGN(1000h) 'CODE'
    esr_default PROC

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 'e'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 's'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 'r'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, '_'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 'd'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 'e'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 'f'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 'a'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 'u'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 'l'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, 't'
    out dx, al

    mov rdx, HYPERVISOR_SERIAL_PORT
    mov rax, '\n'
    out dx, al

    cli
    hlt

    esr_default ENDP
    esr_default_text ENDS
    end
