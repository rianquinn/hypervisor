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

#include "../../macros.h"

#include "../../../uapis/unique_page.h"
#include "../../../uapis/arch/intel_x64/state.h"

// -----------------------------------------------------------------------------
// Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::implementation::intel_x64
{

class state :
    public uapis::intel_x64::state<state>
{
PUBLIC:
    explicit state();
    VIRTUAL ~state() = default;

PRIVATE:
    reg_t __rax() const noexcept;
    void __set_rax(reg_t val) noexcept;
    reg_t __rbx() const noexcept;
    void __set_rbx(reg_t val) noexcept;
    reg_t __rcx() const noexcept;
    void __set_rcx(reg_t val) noexcept;
    reg_t __rdx() const noexcept;
    void __set_rdx(reg_t val) noexcept;
    reg_t __rbp() const noexcept;
    void __set_rbp(reg_t val) noexcept;
    reg_t __rsi() const noexcept;
    void __set_rsi(reg_t val) noexcept;
    reg_t __rdi() const noexcept;
    void __set_rdi(reg_t val) noexcept;
    reg_t __r08() const noexcept;
    void __set_r08(reg_t val) noexcept;
    reg_t __r09() const noexcept;
    void __set_r09(reg_t val) noexcept;
    reg_t __r10() const noexcept;
    void __set_r10(reg_t val) noexcept;
    reg_t __r11() const noexcept;
    void __set_r11(reg_t val) noexcept;
    reg_t __r12() const noexcept;
    void __set_r12(reg_t val) noexcept;
    reg_t __r13() const noexcept;
    void __set_r13(reg_t val) noexcept;
    reg_t __r14() const noexcept;
    void __set_r14(reg_t val) noexcept;
    reg_t __r15() const noexcept;
    void __set_r15(reg_t val) noexcept;
    reg_t __rip() const noexcept;
    void __set_rip(reg_t val) noexcept;
    reg_t __rsp() const noexcept;
    void __set_rsp(reg_t val) noexcept;
    reg_t __exit_reason() const noexcept;
    reg_t __ia32_vmx_cr0_fixed0() const noexcept;
    void __set_ia32_vmx_cr0_fixed0(reg_t val) noexcept;
    reg_t __ia32_vmx_cr4_fixed0() const noexcept;
    void __set_ia32_vmx_cr4_fixed0(reg_t val) noexcept;

PRIVATE:
    VIRTUAL const state_t *state() const noexcept;

PRIVATE:
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
        void *fxsave_region;            // 0x098
    };

    reg_t m_ia32_vmx_cr0_fixed0{};
    reg_t m_ia32_vmx_cr4_fixed0{};

    unique_page<state_t> m_state;
    unique_page<uint8_t> m_fxsave_region;

PRIVATE:
    MOCK_PROTOTYPE(state)
    COPY_MOVE_SEMANTICS(state)

PRIVATE:
    template<typename T>
    friend struct uapis::intel_x64::state;
};

}

#endif
