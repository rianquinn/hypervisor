//
// Bareflank Hypervisor
//
// Copyright (C) 2015 Assured Information Security, Inc.
// Author: Rian Quinn        <quinnr@ainfosec.com>
// Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include <test.h>
#include <maskmanip.h>

void
misc_ut::test_maskmanip_get_mask()
{
    this->expect_true(get_mask(0xFFFFFFFFU, 0x11111111U) == 0x11111111U);
    this->expect_true(get_mask(0x00000000U, 0x11111111U) == 0x00000000U);
    this->expect_true(get_mask(0x88888888U, 0x11111111U) == 0x00000000U);
    this->expect_true(get_mask(0xF0F0F0F0U, 0x11111111U) == 0x10101010U);
}

void
misc_ut::test_maskmanip_clear_mask()
{
    this->expect_true(clear_mask(0xFFFFFFFFU, 0x11111111U) == 0xEEEEEEEEU);
    this->expect_true(clear_mask(0x00000000U, 0x11111111U) == 0x00000000U);
    this->expect_true(clear_mask(0x88888888U, 0x11111111U) == 0x88888888U);
    this->expect_true(clear_mask(0xF0F0F0F0U, 0x11111111U) == 0xE0E0E0E0U);
}

void
misc_ut::test_maskmanip_set_mask()
{
    this->expect_true(set_mask(0xFFFFFFFFU, 0x11111111U) == 0xFFFFFFFFU);
    this->expect_true(set_mask(0x00000000U, 0x11111111U) == 0x11111111U);
    this->expect_true(set_mask(0x88888888U, 0x11111111U) == 0x99999999U);
    this->expect_true(set_mask(0xF0F0F0F0U, 0x11111111U) == 0xF1F1F1F1U);

    this->expect_true(set_mask(0xFFFFFFFFU, 0x00111100U, 0x00000000U) == 0xFFEEEEFFU);
    this->expect_true(set_mask(0x00000000U, 0x00111100U, 0xFFFFFFFFU) == 0x00111100U);
    this->expect_true(set_mask(0x88888888U, 0x00111100U, 0x00111100U) == 0x88999988U);
    this->expect_true(set_mask(0xF0F0F0F0U, 0x00111100U, 0x00111100U) == 0xF0F1F1F0U);
}
