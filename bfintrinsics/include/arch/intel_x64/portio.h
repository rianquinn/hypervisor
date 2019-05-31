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

#ifndef PORTIO_INTEL_X64_H
#define PORTIO_INTEL_X64_H

#include <bftypes.h>
#include <bfbitmanip.h>

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

extern "C" uint8_t _inb(uint16_t port) noexcept;
extern "C" uint16_t _inw(uint16_t port) noexcept;
extern "C" uint32_t _ind(uint16_t port) noexcept;

extern "C" void _outb(uint16_t port, uint8_t val) noexcept;
extern "C" void _outw(uint16_t port, uint16_t val) noexcept;
extern "C" void _outd(uint16_t port, uint32_t val) noexcept;

// *INDENT-OFF*

namespace intel_x64::portio
{

using port_addr_type = uint16_t;
using port_8bit_type = uint8_t;
using port_16bit_type = uint16_t;
using port_32bit_type = uint32_t;

inline auto inb(port_addr_type port) noexcept
{ return _inb(port); }

inline auto inw(port_addr_type port) noexcept
{ return _inw(port); }

inline auto ind(port_addr_type port) noexcept
{ return _ind(port); }

inline void outb(port_addr_type port, port_8bit_type val) noexcept
{ _outb(port, val); }

inline void outw(port_addr_type port, port_16bit_type val) noexcept
{ _outw(port, val); }

inline void outd(port_addr_type port, port_32bit_type val) noexcept
{ _outd(port, val); }

}

// *INDENT-ON*

#endif
