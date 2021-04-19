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

#include <constants.h>
#include <debug.h>
#include <efi/efi_status.h>
#include <efi/efi_system_table.h>
#include <global_descriptor_table_register_t.h>
#include <intrinsic_lgdt.h>
#include <intrinsic_ltr.h>
#include <intrinsic_sgdt.h>
#include <intrinsic_str.h>
#include <platform.h>
#include <set_gdt_descriptor.h>
#include <tss_t.h>
#include <types.h>

/** @brief defines our custom TR attributes */
#define UEFI_TR_ATTRIB ((uint16_t)0x00000089)
/** @brief defines our custom TR limit */
#define UEFI_TR_LIMIT ((uint32_t)(sizeof(struct tss_t) - ((uint64_t)1)))

/**
 * <!-- description -->
 *   @brief Ensures that the TSS is set up properly.
 *
 * <!-- inputs/outputs -->
 *   @return returns EFI_SUCCESS on success, and a non-EFI_SUCCESS value on
 *     failure.
 */
EFI_STATUS
setup_tss(void)
{
    int64_t ret;

    /**
     * NOTE:
     * - UEFI doesn't seem to set the TR segment. This causes a number of
     *   issues with our code so we create a new GDT that is the same as
     *   the current GDT, but with TR added.
     * - This seems to be an issue on both AMD and Intel, and also seems to
     *   be an issue on multiple systems from different vendors.
     * - One issue is the on Intel, you cannot start a VM with TR set to 0.
     *   Any attempt to do so will cause a VM entry failure.
     * - Another issue is that when you attempt to return (i.e. promote) from
     *   the microkernel, the promote logic doesn't have a TR to flip the
     *   TSS busy bit for. As a result, it has to leave the TR set to the
     *   microkernel's TR which leaks it's resources.
     * - Looking at the GDT for
     */

    struct tss_t *tss;
    struct global_descriptor_table_register_t old_gdtr;
    struct global_descriptor_table_register_t new_gdtr;

    if (intrinsic_str() != ((uint16_t)0)) {

        /**
         * NOTE:
         * - Based on testing, I don't think this specific branch will
         *   actually be taken, but just in case there is a TR set, we don't
         *   need to actually execute this code.
         */

        return EFI_SUCCESS;
    }

    intrinsic_sgdt(&old_gdtr);
    old_gdtr.limit += ((uint16_t)1);

    if (old_gdtr.limit > ((uint16_t)0xFFF0)) {
        bferror("system unsupported. existing GDT is too large");
        return EFI_LOAD_ERROR;
    }

    /**
     * NOTE:
     * - Allocate the new GDT and the new TSS. The TR will be set to the
     *   current GDT's limit. This ensures that the TR uses the first
     *   available entry in the old GDT.
     */

    new_gdtr.base = (uint64_t *)platform_alloc(HYPERVISOR_PAGE_SIZE);
    if (((void *)0) == new_gdtr.base) {
        bferror("platform_alloc failed");
        goto platform_alloc_gdt_failed;
    }

    new_gdtr.limit = (uint16_t)(HYPERVISOR_PAGE_SIZE - ((uint64_t)1));

    /**
     * TODO:
     * - There is an issue here. If an interrupt or exception fires, we might
     *   have a problem if UEFI's IDT is set up to use the IST when an
     *   interrupt first. Since the TR is not set, it is likely that the IDT
     *   is set up to use the stack, in which case the IST is never used,
     *   and this TSS configuration is fine. We should veryify this on
     *   different systems to prove that this will work. Otherwise, using
     *   other UEFI functions that need interrupts might fail if UEFI tries
     *   to add a TR to their GDT but ours is loaded and the TSS's do not
     *   match.
     */

    tss = (struct tss_t *)platform_alloc(HYPERVISOR_PAGE_SIZE);
    if (((void *)0) == tss) {
        bferror("platform_alloc failed");
        goto platform_alloc_tss_failed;
    }

    tss->tss->iomap = ((uint16_t)sizeof(struct tss_t));

    /**
     * NOTE:
     * - Set up the new GDT. To do this, all we need to do is copy over the
     *   old GDT and then add the TSS.
     */

    g_st->BootServices->CopyMem(new_gdtr.base, old_gdtr.base, old_gdtr.limit);

    ret = set_gdt_descriptor(    // --
        &new_gdtr,               // --
        old_gdtr.limit,          // --
        (uint64_t)tss,           // --
        UEFI_TR_LIMIT,           // --
        UEFI_TR_ATTRIB);

    if (ret) {
        bferror("set_gdt_descriptor failed");
        goto set_descriptor_failed;
    }

    /**
     * NOTE:
     * - Now that the new GDT is set up, we can load it as well as the TR
     *   segment which should fixes the above identified issues. Note that
     *   we do not need to load any other segment registers are they are
     *   all identical.
     */

    intrinsic_lgdt(&new_gdtr);
    intrinsic_ltr(old_gdtr.limit);

    return EFI_SUCCESS;

set_descriptor_failed:
    platform_free(tss, HYPERVISOR_PAGE_SIZE);
platform_alloc_tss_failed:
    platform_free(new_gdtr.base, HYPERVISOR_PAGE_SIZE);
platform_alloc_gdt_failed:

    return EFI_LOAD_ERROR;
}
