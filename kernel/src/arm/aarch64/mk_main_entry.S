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

    .text

    .globl  mk_main_entry
    .type   mk_main_entry, @function
mk_main_entry:

    .size mk_main_entry, .-mk_main_entry

    /**************************************************************************/
    /* Fast Fail Routine                                                      */
    /**************************************************************************/

    .globl  mk_main_fast_fail_entry
    .type   mk_main_fast_fail_entry, @function
mk_main_fast_fail_entry:

    .size mk_main_fast_fail_entry, .-mk_main_fast_fail_entry



    /**************************************************************************/
    /* Runtime Helpers                                                        */
    /**************************************************************************/

    .rodata

    .globl  __stack_chk_guard
__stack_chk_guard:
    .quad 0xDEADBEEFDEADBEEF
