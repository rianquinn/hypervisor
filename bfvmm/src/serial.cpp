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

#include <implementation/serial.h>

// -----------------------------------------------------------------------------
// Serial Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::implementation
{

serial::serial() noexcept :
    m_port{DEFAULT_COM_PORT}
{
    constexpr uint16_t interrupt_en_reg = 1U;
    constexpr uint16_t fifo_control_reg = 2U;

    constexpr uint8_t fifo_control_enable_fifos = 1U << 0;
    constexpr uint8_t fifo_control_clear_recieve_fifo = 1U << 1;
    constexpr uint8_t fifo_control_clear_transmit_fifo = 1U << 2;

    this->disable_dlab();

    uint8_t bits = 0U;
    bits |= fifo_control_enable_fifos;
    bits |= fifo_control_clear_recieve_fifo;
    bits |= fifo_control_clear_transmit_fifo;

    outb(interrupt_en_reg, 0x00);
    outb(fifo_control_reg, bits);

    this->set_baud_rate(DEFAULT_BAUD_RATE);
    this->set_data_bits(DEFAULT_DATA_BITS);
    this->set_stop_bits(DEFAULT_STOP_BITS);
    this->set_parity_bits(DEFAULT_PARITY_BITS);
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
    while (!is_transmit_empty())
    { }

    outb(0, static_cast<uint8_t>(c));
}

constexpr uint16_t baud_rate_lo_reg = 0U;
constexpr uint16_t baud_rate_hi_reg = 1U;

void
serial::set_baud_rate(baud_rate_t rate) noexcept
{
    auto lsb = gsl::narrow_cast<uint8_t>((rate & 0x000000FF) >> 0);
    auto msb = gsl::narrow_cast<uint8_t>((rate & 0x0000FF00) >> 8);

    this->enable_dlab();

    outb(baud_rate_lo_reg, lsb);
    outb(baud_rate_hi_reg, msb);

    this->disable_dlab();
}

constexpr uint16_t line_control_reg = 3U;
constexpr const uint8_t line_control_data_mask = 0x03;
constexpr const uint8_t line_control_stop_mask = 0x04;
constexpr const uint8_t line_control_parity_mask = 0x38;

void
serial::set_data_bits(data_bits_t bits) noexcept
{
    auto reg = inb(line_control_reg);

    reg = reg & static_cast<decltype(reg)>(~line_control_data_mask);
    reg = reg | static_cast<decltype(reg)>(bits & line_control_data_mask);

    outb(line_control_reg, reg);
}

void
serial::set_stop_bits(stop_bits_t bits) noexcept
{
    auto reg = inb(line_control_reg);

    reg = reg & static_cast<decltype(reg)>(~line_control_stop_mask);
    reg = reg | static_cast<decltype(reg)>(bits & line_control_stop_mask);

    outb(line_control_reg, reg);
}

void
serial::set_parity_bits(parity_bits_t bits) noexcept
{
    auto reg = inb(line_control_reg);

    reg = reg & static_cast<decltype(reg)>(~line_control_parity_mask);
    reg = reg | static_cast<decltype(reg)>(bits & line_control_parity_mask);

    outb(line_control_reg, reg);
}

bool
serial::is_transmit_empty() const noexcept
{
    constexpr uint16_t line_status_reg = 5U;
    constexpr uint8_t line_status_empty_transmitter = 1U << 5;

    return (inb(line_status_reg) & line_status_empty_transmitter) != 0;
}

constexpr const uint8_t dlab = 1U << 7;

void
serial::enable_dlab() const noexcept
{
    auto reg = inb(line_control_reg);
    reg = reg | static_cast<decltype(reg)>(dlab);
    outb(line_control_reg, reg);
}

void
serial::disable_dlab() const noexcept
{
    auto reg = inb(line_control_reg);
    reg = reg & static_cast<decltype(reg)>(~(dlab));
    outb(line_control_reg, reg);
}

uint8_t
serial::inb(uint16_t addr) const noexcept
{ return ::x64::portio::inb(static_cast<uint16_t>(addr + m_port)); }

void
serial::outb(uint16_t addr, uint8_t data) const noexcept
{ ::x64::portio::outb(static_cast<uint16_t>(addr + m_port), data); }

}
