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

	.global esr
	.align 12
esr:

    mov x19, x0
    mov x20, x1
    mov x21, x2
    mov x22, x3

    mov x0, #0xA
    bl serial_write_c

    mov x0, #0xA
    bl serial_write_c

    mov x0, #0xA
    bl serial_write_c

    /**
     * NOTE:
     * - output: "exception:"
     */

    mov x0, #0x65
    bl serial_write_c

    mov x0, #0x78
    bl serial_write_c

    mov x0, #0x63
    bl serial_write_c

    mov x0, #0x65
    bl serial_write_c

    mov x0, #0x70
    bl serial_write_c

    mov x0, #0x74
    bl serial_write_c

    mov x0, #0x69
    bl serial_write_c

    mov x0, #0x6F
    bl serial_write_c

    mov x0, #0x6E
    bl serial_write_c

    mov x0, #0x3A
    bl serial_write_c

    mov x0, #0xA
    bl serial_write_c

    /**
     * NOTE:
     * - output: " - vec: <vector #>"
     */

    mov x0, #0x20
    bl serial_write_c

    mov x0, #0x2D
    bl serial_write_c

    mov x0, #0x20
    bl serial_write_c

    mov x0, #0x76
    bl serial_write_c

    mov x0, #0x65
    bl serial_write_c

    mov x0, #0x63
    bl serial_write_c

    mov x0, #0x3A
    bl serial_write_c

    mov x0, #0x20
    bl serial_write_c

    mov x0, x19
    bl serial_write_hex

    mov x0, #0xA
    bl serial_write_c

    /**
     * NOTE:
     * - output: " - esr: <esr_el2>"
     */

    mov x0, #0x20
    bl serial_write_c

    mov x0, #0x2D
    bl serial_write_c

    mov x0, #0x20
    bl serial_write_c

    mov x0, #0x65
    bl serial_write_c

    mov x0, #0x73
    bl serial_write_c

    mov x0, #0x72
    bl serial_write_c

    mov x0, #0x3A
    bl serial_write_c

    mov x0, #0x20
    bl serial_write_c

    mov x0, x20
    bl serial_write_hex

    mov x0, #0xA
    bl serial_write_c

    /**
     * NOTE:
     * - output: " - far: <far_el2>"
     */

    mov x0, #0x20
    bl serial_write_c

    mov x0, #0x2D
    bl serial_write_c

    mov x0, #0x20
    bl serial_write_c

    mov x0, #0x66
    bl serial_write_c

    mov x0, #0x61
    bl serial_write_c

    mov x0, #0x72
    bl serial_write_c

    mov x0, #0x3A
    bl serial_write_c

    mov x0, #0x20
    bl serial_write_c

    mov x0, x21
    bl serial_write_hex

    mov x0, #0xA
    bl serial_write_c

    /**
     * NOTE:
     * - output: " - spsr: <spsr_el2>"
     */

    mov x0, #0x20
    bl serial_write_c

    mov x0, #0x2D
    bl serial_write_c

    mov x0, #0x20
    bl serial_write_c

    mov x0, #0x73
    bl serial_write_c

    mov x0, #0x70
    bl serial_write_c

    mov x0, #0x73
    bl serial_write_c

    mov x0, #0x72
    bl serial_write_c

    mov x0, #0x3A
    bl serial_write_c

    mov x0, #0x20
    bl serial_write_c

    mov x0, x22
    bl serial_write_hex

    mov x0, #0xA
    bl serial_write_c

loop_forever:
    b loop_forever
