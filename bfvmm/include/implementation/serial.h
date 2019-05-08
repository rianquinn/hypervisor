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

#ifndef IMPLEMENTATION_SERIAL_H
#define IMPLEMENTATION_SERIAL_H

#include "macros.h"

// -----------------------------------------------------------------------------
// Definition
// -----------------------------------------------------------------------------

namespace bfvmm::implementation
{

class serial
{
    serial() noexcept;

PUBLIC:
    static gsl::not_null<serial *> instance() noexcept;
    void write(const char c) const noexcept;

PRIVATE:
    enum baud_rate_t {
        baud_rate_50 = 0x0900,
        baud_rate_75 = 0x0600,
        baud_rate_110 = 0x0417,
        baud_rate_150 = 0x0300,
        baud_rate_300 = 0x0180,
        baud_rate_600 = 0x00C0,
        baud_rate_1200 = 0x0060,
        baud_rate_1800 = 0x0040,
        baud_rate_2000 = 0x003A,
        baud_rate_2400 = 0x0030,
        baud_rate_3600 = 0x0020,
        baud_rate_4800 = 0x0018,
        baud_rate_7200 = 0x0010,
        baud_rate_9600 = 0x000C,
        baud_rate_19200 = 0x0006,
        baud_rate_38400 = 0x0003,
        baud_rate_57600 = 0x0002,
        baud_rate_115200 = 0x0001
    };

    enum data_bits_t {
        char_length_5 = 0x00,
        char_length_6 = 0x01,
        char_length_7 = 0x02,
        char_length_8 = 0x03
    };

    enum stop_bits_t {
        stop_bits_1 = 0x00,
        stop_bits_2 = 0x04
    };

    enum parity_bits_t {
        parity_none = 0x00,
        parity_odd = 0x08,
        parity_even = 0x18,
        parity_mark = 0x28,
        parity_space = 0x38
    };

    void set_baud_rate(baud_rate_t rate) noexcept;
    void set_data_bits(data_bits_t bits) noexcept;
    void set_stop_bits(stop_bits_t bits) noexcept;
    void set_parity_bits(parity_bits_t bits) noexcept;

    void enable_dlab() const noexcept;
    void disable_dlab() const noexcept;
    bool is_transmit_empty() const noexcept;

    uint8_t inb(uint16_t addr) const noexcept;
    void outb(uint16_t addr, uint8_t data) const noexcept;

PRIVATE:
    uint16_t m_port;

PRIVATE:
    COPY_MOVE_SEMANTICS(serial)
};

}

#endif
