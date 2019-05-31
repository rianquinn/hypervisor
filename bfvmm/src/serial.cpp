//
// Copyright (C) 2019 Assured Information Security, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <uapis/arch/intel_x64/intrinsics/portio.h>

#include <bfconstants.h>
#include <implementation/serial.h>

constexpr uint16_t baud_rate_lo_reg = 0U;
constexpr uint16_t baud_rate_hi_reg = 1U;
constexpr uint16_t interrupt_en_reg = 1U;
constexpr uint16_t fifo_control_reg = 2U;
constexpr uint16_t line_control_reg = 3U;
constexpr uint16_t line__status_reg = 5U;

inline uint8_t inb(uint16_t addr) noexcept
{ return ::intel_x64::portio::inb(static_cast<uint16_t>(addr + DEFAULT_COM_PORT)); }

inline void outb(uint16_t addr, uint8_t data) noexcept
{ ::intel_x64::portio::outb(static_cast<uint16_t>(addr + DEFAULT_COM_PORT), data); }

inline bool is_transmit_empty() noexcept
{ return (inb(line__status_reg) & (1U << 5)) != 0; }

// -----------------------------------------------------------------------------
// Serial Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::implementation
{

serial::serial() noexcept
{
    constexpr uint8_t fifo_control_enable_fifos = 1U << 0;
    constexpr uint8_t fifo_control_clear_recieve_fifo = 1U << 1;
    constexpr uint8_t fifo_control_clear_transmit_fifo = 1U << 2;

    uint8_t bits = 0U;
    bits |= fifo_control_enable_fifos;
    bits |= fifo_control_clear_recieve_fifo;
    bits |= fifo_control_clear_transmit_fifo;

    outb(line_control_reg, 0x80);
    outb(baud_rate_lo_reg, 0x01);
    outb(baud_rate_hi_reg, 0x00);
    outb(line_control_reg, 0x03);
    outb(interrupt_en_reg, 0x00);
    outb(fifo_control_reg, bits);
}

gsl::not_null<serial *>
serial::instance() noexcept
{
    static serial s_serial;
    return &s_serial;
}

void
serial::write(const char c) const noexcept
{
    while(!is_transmit_empty());
    outb(0, static_cast<uint8_t>(c));
}

}
