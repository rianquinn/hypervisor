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

#ifndef IMPLEMENTATION_STATE_INTEL_X64_H
#define IMPLEMENTATION_STATE_INTEL_X64_H

#include "../uapis/state.h"
#include "../../../../memory_manager/memory_manager.h"

// -----------------------------------------------------------------------------
// Defintion
// -----------------------------------------------------------------------------

///@cond

namespace bfvmm::intel_x64::implementation
{

class state
{
public:

    explicit state(gsl::not_null<vcpu *> vcpu);
    VIRTUAL ~state() = default;

    VIRTUAL reg_t rax() const noexcept;
    VIRTUAL void set_rax(reg_t val) noexcept;
    VIRTUAL reg_t rbx() const noexcept;
    VIRTUAL void set_rbx(reg_t val) noexcept;
    VIRTUAL reg_t rcx() const noexcept;
    VIRTUAL void set_rcx(reg_t val) noexcept;
    VIRTUAL reg_t rdx() const noexcept;
    VIRTUAL void set_rdx(reg_t val) noexcept;
    VIRTUAL reg_t rbp() const noexcept;
    VIRTUAL void set_rbp(reg_t val) noexcept;
    VIRTUAL reg_t rsi() const noexcept;
    VIRTUAL void set_rsi(reg_t val) noexcept;
    VIRTUAL reg_t rdi() const noexcept;
    VIRTUAL void set_rdi(reg_t val) noexcept;
    VIRTUAL reg_t r08() const noexcept;
    VIRTUAL void set_r08(reg_t val) noexcept;
    VIRTUAL reg_t r09() const noexcept;
    VIRTUAL void set_r09(reg_t val) noexcept;
    VIRTUAL reg_t r10() const noexcept;
    VIRTUAL void set_r10(reg_t val) noexcept;
    VIRTUAL reg_t r11() const noexcept;
    VIRTUAL void set_r11(reg_t val) noexcept;
    VIRTUAL reg_t r12() const noexcept;
    VIRTUAL void set_r12(reg_t val) noexcept;
    VIRTUAL reg_t r13() const noexcept;
    VIRTUAL void set_r13(reg_t val) noexcept;
    VIRTUAL reg_t r14() const noexcept;
    VIRTUAL void set_r14(reg_t val) noexcept;
    VIRTUAL reg_t r15() const noexcept;
    VIRTUAL void set_r15(reg_t val) noexcept;
    VIRTUAL reg_t rip() const noexcept;
    VIRTUAL void set_rip(reg_t val) noexcept;
    VIRTUAL reg_t rsp() const noexcept;
    VIRTUAL void set_rsp(reg_t val) noexcept;

    VIRTUAL reg_t exit_reason() const noexcept;

    VIRTUAL reg_t ia32_vmx_cr0_fixed0() const noexcept;
    VIRTUAL void set_ia32_vmx_cr0_fixed0(reg_t val) noexcept;
    VIRTUAL reg_t ia32_vmx_cr4_fixed0() const noexcept;
    VIRTUAL void set_ia32_vmx_cr4_fixed0(reg_t val) noexcept;

private:

    struct state_t {
        reg_t rax;                      // 0x000
        reg_t rbx;                      // 0x008
        reg_t rcx;                      // 0x010
        reg_t rdx;                      // 0x018
        reg_t rbp;                      // 0x020
        reg_t rsi;                      // 0x028
        reg_t rdi;                      // 0x030
        reg_t r08;                      // 0x038
        reg_t r09;                      // 0x040
        reg_t r10;                      // 0x048
        reg_t r11;                      // 0x050
        reg_t r12;                      // 0x058
        reg_t r13;                      // 0x060
        reg_t r14;                      // 0x068
        reg_t r15;                      // 0x070
        reg_t rip;                      // 0x078
        reg_t rsp;                      // 0x080

        reg_t exit_reason;              // 0x088
        void *vcpu_ptr;                 // 0x090
        reg_t ia32_vmx_cr0_fixed0;      // 0x098
        reg_t ia32_vmx_cr4_fixed0;      // 0x0A0
    };

    page_ptr<state_t> m_state;

public:
    MOCK_PROTOTYPE(state);
    COPY_MOVE_SEMANTICS(state);
};

}

///@endcond

#endif
