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

    /** @brief defines the offset of state_save_t.x0 */
    #define SS_X0_OFFSET 0x000
    /** @brief defines the offset of state_save_t.x1 */
    #define SS_X1_OFFSET 0x008
    /** @brief defines the offset of state_save_t.x2 */
    #define SS_X2_OFFSET 0x010
    /** @brief defines the offset of state_save_t.x3 */
    #define SS_X3_OFFSET 0x018
    /** @brief defines the offset of state_save_t.x4 */
    #define SS_X4_OFFSET 0x020
    /** @brief defines the offset of state_save_t.x5 */
    #define SS_X5_OFFSET 0x028
    /** @brief defines the offset of state_save_t.x6 */
    #define SS_X6_OFFSET 0x030
    /** @brief defines the offset of state_save_t.x7 */
    #define SS_X7_OFFSET 0x038
    /** @brief defines the offset of state_save_t.x8 */
    #define SS_X8_OFFSET 0x040
    /** @brief defines the offset of state_save_t.x9 */
    #define SS_X9_OFFSET 0x048
    /** @brief defines the offset of state_save_t.x10 */
    #define SS_X10_OFFSET 0x050
    /** @brief defines the offset of state_save_t.x11 */
    #define SS_X11_OFFSET 0x058
    /** @brief defines the offset of state_save_t.x12 */
    #define SS_X12_OFFSET 0x060
    /** @brief defines the offset of state_save_t.x13 */
    #define SS_X13_OFFSET 0x068
    /** @brief defines the offset of state_save_t.x14 */
    #define SS_X14_OFFSET 0x070
    /** @brief defines the offset of state_save_t.x15 */
    #define SS_X15_OFFSET 0x078
    /** @brief defines the offset of state_save_t.x16 */
    #define SS_X16_OFFSET 0x080
    /** @brief defines the offset of state_save_t.x17 */
    #define SS_X17_OFFSET 0x088
    /** @brief defines the offset of state_save_t.x18 */
    #define SS_X18_OFFSET 0x090
    /** @brief defines the offset of state_save_t.x19 */
    #define SS_X19_OFFSET 0x098
    /** @brief defines the offset of state_save_t.x20 */
    #define SS_X20_OFFSET 0x0A0
    /** @brief defines the offset of state_save_t.x21 */
    #define SS_X21_OFFSET 0x0A8
    /** @brief defines the offset of state_save_t.x22 */
    #define SS_X22_OFFSET 0x0B0
    /** @brief defines the offset of state_save_t.x23 */
    #define SS_X23_OFFSET 0x0B8
    /** @brief defines the offset of state_save_t.x24 */
    #define SS_X24_OFFSET 0x0C0
    /** @brief defines the offset of state_save_t.x25 */
    #define SS_X25_OFFSET 0x0C8
    /** @brief defines the offset of state_save_t.x26 */
    #define SS_X26_OFFSET 0x0D0
    /** @brief defines the offset of state_save_t.x27 */
    #define SS_X27_OFFSET 0x0D8
    /** @brief defines the offset of state_save_t.x28 */
    #define SS_X28_OFFSET 0x0E0
    /** @brief defines the offset of state_save_t.x29 */
    #define SS_X29_OFFSET 0x0E8
    /** @brief defines the offset of state_save_t.x30 */
    #define SS_X30_OFFSET 0x0F0
    /** @brief defines the offset of state_save_t.sp_el2 */
    #define SS_SP_EL2_OFFSET 0x0F8
    /** @brief defines the offset of state_save_t.pc_el2 */
    #define SS_PC_EL2_OFFSET 0x100

    /** @brief defines the offset of state_save_t.daif */
    #define SS_DAIF_OFFSET 0x108
    /** @brief defines the offset of state_save_t.spsel */
    #define SS_SPSEL_OFFSET 0x110

    /** @brief defines the offset of state_save_t.vbar_el2 */
    #define SS_VBAR_EL2_OFFSET 0x188

    /** @brief defines the offset of state_save_t.hcr_el2 */
    #define SS_HCR_EL2_OFFSET 0x190
    /** @brief defines the offset of state_save_t.mair_el2 */
    #define SS_MAIR_EL2_OFFSET 0x198
    /** @brief defines the offset of state_save_t.sctlr_el2 */
    #define SS_SCTLR_EL2_OFFSET 0x1A0
    /** @brief defines the offset of state_save_t.tcr_el2 */
    #define SS_TCR_EL2_OFFSET 0x1A8
    /** @brief defines the offset of state_save_t.ttbr0_el2 */
    #define SS_TTBR0_EL2_OFFSET 0x1B0

    /**************************************************************************/
    /* demote                                                                 */
    /**************************************************************************/

    /**
    * <!-- description -->
    *   @brief This function executes the microkernel, demoting the current
    *     OS into a virtual machine.
    *
    * <!-- inputs/outputs -->
    *   @param mk_args_t the arguments to pass to the microkernel
    *   @param mk_state the microkernel's state save
    *   @param root_vp_state the root vp's state save
    *   @return 0 on success, LOADER_FAILURE on failure.
    */

	.global demote
	.align 12
demote:

    /**************************************************************************/
    /* Report Success On Completion                                           */
    /**************************************************************************/

    add  x11, x2, #SS_X0_OFFSET
    str  xzr, [x11]

    /**************************************************************************/
    /* General Purpose Registers (non-volatile)                               */
    /**************************************************************************/

    add  x12, x2, #SS_X19_OFFSET
    str  x19, [x12]
    add  x12, x2, #SS_X20_OFFSET
    str  x20, [x12]
    add  x12, x2, #SS_X21_OFFSET
    str  x21, [x12]
    add  x12, x2, #SS_X22_OFFSET
    str  x22, [x12]
    add  x12, x2, #SS_X23_OFFSET
    str  x23, [x12]
    add  x12, x2, #SS_X24_OFFSET
    str  x24, [x12]
    add  x12, x2, #SS_X25_OFFSET
    str  x25, [x12]
    add  x12, x2, #SS_X26_OFFSET
    str  x26, [x12]
    add  x12, x2, #SS_X27_OFFSET
    str  x27, [x12]
    add  x12, x2, #SS_X28_OFFSET
    str  x28, [x12]
    add  x12, x2, #SS_X29_OFFSET
    str  x29, [x12]
    add  x12, x2, #SS_X30_OFFSET
    str  x30, [x12]

    mov  x10, sp
    add  x12, x2, #SS_SP_EL2_OFFSET
    str  x10, [x12]

    adr  x10, demotion_return
    add  x12, x2, #SS_PC_EL2_OFFSET
    str  x10, [x12]

    /**************************************************************************/
    /* Setup                                                                  */
    /**************************************************************************/

    mov  x20, x0       /* args */
    mov  x21, x1       /* mk_state */
    mov  x22, x2       /* root_vp_state */

    /**************************************************************************/
    /* Saved Program Status Registers (SPSR)                                  */
    /**************************************************************************/

    /**
     * TODO:
     * - We probably need to store more of these as we support more ARM
     *   archiectures. Just depends on whether or not we use the feature
     *   in the microkernel. For now, this is all we need.
     */

    mrs  x10, daif
    add  x12, x22, #SS_DAIF_OFFSET
    str  x10, [x12]
    add  x11, x21, #SS_DAIF_OFFSET
    ldr  x10, [x11]
    msr  daif, x10

    mrs  x10, spsel
    add  x12, x22, #SS_SPSEL_OFFSET
    str  x10, [x12]
    add  x11, x21, #SS_SPSEL_OFFSET
    ldr  x10, [x11]
    msr  spsel, x10

    /**************************************************************************/
    /* Exceptions                                                             */
    /**************************************************************************/

    mrs  x10, vbar_el2
    add  x12, x22, #SS_VBAR_EL2_OFFSET
    str  x10, [x12]
    add  x11, x21, #SS_VBAR_EL2_OFFSET
    ldr  x10, [x11]
    msr  vbar_el2, x10

    /**************************************************************************/
    /* System Registers                                                       */
    /**************************************************************************/

    mrs  x10, hcr_el2
    add  x12, x22, #SS_HCR_EL2_OFFSET
    str  x10, [x12]
    add  x11, x21, #SS_HCR_EL2_OFFSET
    ldr  x10, [x11]
    msr  hcr_el2, x10

    mrs  x10, mair_el2
    add  x12, x22, #SS_MAIR_EL2_OFFSET
    str  x10, [x12]
    add  x11, x21, #SS_MAIR_EL2_OFFSET
    ldr  x10, [x11]
    msr  mair_el2, x10

    mrs  x10, sctlr_el2
    add  x12, x22, #SS_SCTLR_EL2_OFFSET
    str  x10, [x12]
    add  x11, x21, #SS_SCTLR_EL2_OFFSET
    ldr  x10, [x11]
    msr  sctlr_el2, x10

    mrs  x10, tcr_el2
    add  x12, x22, #SS_TCR_EL2_OFFSET
    str  x10, [x12]
    add  x11, x21, #SS_TCR_EL2_OFFSET
    ldr  x10, [x11]
    msr  tcr_el2, x10

    mrs  x10, ttbr0_el2
    add  x12, x22, #SS_TTBR0_EL2_OFFSET
    str  x10, [x12]
    add  x11, x21, #SS_TTBR0_EL2_OFFSET
    ldr  x10, [x11]
    msr  ttbr0_el2, x10

    tlbi alle2
    isb  sy
    dsb  sy

    /**************************************************************************/
    /* Stack                                                                  */
    /**************************************************************************/

    add  x11, x21, #SS_SP_EL2_OFFSET
    ldr  x10, [x11]
    mov  sp, x10

    /**************************************************************************/
    /* Call Microkernel                                                       */
    /**************************************************************************/

    add  x11, x21, #SS_PC_EL2_OFFSET
    ldr  x10, [x11]

    mov  x0, x20
    ret  x10

demotion_return:

    /**
     * NOTE:
     * - If demotion is successful, before we return back to the loader, we
     *   ensure that at least one exit occurs. This is done to properly handle
     *   errors with the first VMExit. Specifically, if the first VMExit
     *   generates a failure, it needs to return to loader. The state in
     *   the root VP, which is what it will use to return is still the same
     *   at this point, so a return is safe.
     */

    ret
