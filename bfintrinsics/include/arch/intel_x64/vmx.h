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

#ifndef VMX_INTEL_X64_H
#define VMX_INTEL_X64_H

#include <bftypes.h>
#include <bfbitmanip.h>

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

extern "C" bool _vmxon(void *ptr) noexcept;
extern "C" bool _vmxoff(void) noexcept;
extern "C" bool _vmclear(void *ptr) noexcept;
extern "C" bool _vmptrld(void *ptr) noexcept;
extern "C" bool _vmptrst(void *ptr) noexcept;
extern "C" bool _vmread(uint64_t field, uint64_t *value) noexcept;
extern "C" bool _vmwrite(uint64_t field, uint64_t value) noexcept;
extern "C" bool _invept(uint64_t type, void *ptr) noexcept;
extern "C" bool _invvpid(uint64_t type, void *ptr) noexcept;

// *INDENT-OFF*

namespace intel_x64::vmx
{

using field_type = uint64_t;
using value_type = uint64_t;
using integer_pointer = uint64_t;

inline void on(integer_pointer ptr)
{
    if (!_vmxon(&ptr)) {
        throw std::runtime_error("vmx::on failed");
    }
}

inline void off()
{
    if (!_vmxoff()) {
        throw std::runtime_error("vmx::off failed");
    }
}

inline void invept_single_context(value_type eptp)
{
    value_type descriptor[2] = { eptp, 0 };
    if (!_invept(1, static_cast<void *>(descriptor))) {
        throw std::runtime_error("vmx::invept_singal_context failed");
    }
}

inline void invept_global()
{
    value_type descriptor[2] = { 0, 0 };
    if (!_invept(2, static_cast<void *>(descriptor))) {
        throw std::runtime_error("vmx::invept_global failed");
    }
}

inline void invvpid_individual_addr(value_type vpid, integer_pointer addr)
{
    value_type descriptor[2] = { vpid, addr };
    if (!_invvpid(0, static_cast<void *>(descriptor))) {
        throw std::runtime_error("vmx::invvpid_individual_addr failed");
    }
}

inline void invvpid_single_context(value_type vpid)
{
    value_type descriptor[2] = { vpid, 0 };
    if (!_invvpid(1, static_cast<void *>(descriptor))) {
        throw std::runtime_error("vmx::invvpid_single_context failed");
    }
}

inline void invvpid_all_contexts()
{
    value_type descriptor[2] = { 0, 0 };
    if (!_invvpid(2, static_cast<void *>(descriptor))) {
        throw std::runtime_error("vmx::invvpid_all_contexts failed");
    }
}

inline void invvpid_single_context_global(value_type vpid)
{
    value_type descriptor[2] = { vpid, 0 };
    if (!_invvpid(3, static_cast<void *>(descriptor))) {
        throw std::runtime_error("vmx::invvpid_single_context_global failed");
    }
}

inline void clear(integer_pointer ptr)
{
    if (!_vmclear(&ptr)) {
        throw std::runtime_error("vmx::clear failed");
    }
}

inline void load(integer_pointer ptr)
{
    if (!_vmptrld(&ptr)) {
        throw std::runtime_error("vmx::load failed");
    }
}

inline void reset(integer_pointer ptr)
{
    if (!_vmptrst(&ptr)) {
        throw std::runtime_error("vmx::reset failed");
    }
}

inline auto read(field_type field)
{
    value_type value = {};

    if (!_vmread(field, &value)) {
        throw std::runtime_error("vmx::read failed");
    }

    return value;
}

inline void write(field_type field, value_type value)
{
    if (!_vmwrite(field, value)) {
        throw std::runtime_error("vmx::write failed");
    }
}

}

// *INDENT-ON*

#endif
