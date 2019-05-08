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

#include <implementation/arch/intel_x64/state.h>

namespace bfvmm::intel_x64::implementation
{

state::state(
    gsl::not_null<vcpu *> vcpu
) :
    m_ia32_vmx_cr0_fixed0{::intel_x64::msrs::ia32_vmx_cr0_fixed0::get()},
    m_ia32_vmx_cr4_fixed0{::intel_x64::msrs::ia32_vmx_cr4_fixed0::get()}
{
    m_state->vcpu_ptr = vcpu.get();
    m_state->fxsave_region = m_fxsave_region.hva();

    vcpu->set_host_gs_base(m_state.hva()));
}

reg_t
state::rax() const noexcept
{ return m_state->rax; }

void
state::set_rax(reg_t val) noexcept
{ m_state->rax = val; }

reg_t
state::rbx() const noexcept
{ return m_state->rbx; }

void
state::set_rbx(reg_t val) noexcept
{ m_state->rbx = val; }

reg_t
state::rcx() const noexcept
{ return m_state->rcx; }

void
state::set_rcx(reg_t val) noexcept
{ m_state->rcx = val; }

reg_t
state::rdx() const noexcept
{ return m_state->rdx; }

void
state::set_rdx(reg_t val) noexcept
{ m_state->rdx = val; }

reg_t
state::rbp() const noexcept
{ return m_state->rbp; }

void
state::set_rbp(reg_t val) noexcept
{ m_state->rbp = val; }

reg_t
state::rsi() const noexcept
{ return m_state->rsi; }

void
state::set_rsi(reg_t val) noexcept
{ m_state->rsi = val; }

reg_t
state::rdi() const noexcept
{ return m_state->rdi; }

void
state::set_rdi(reg_t val) noexcept
{ m_state->rdi = val; }

reg_t
state::r08() const noexcept
{ return m_state->r08; }

void
state::set_r08(reg_t val) noexcept
{ m_state->r08 = val; }

reg_t
state::r09() const noexcept
{ return m_state->r09; }

void
state::set_r09(reg_t val) noexcept
{ m_state->r09 = val; }

reg_t
state::r10() const noexcept
{ return m_state->r10; }

void
state::set_r10(reg_t val) noexcept
{ m_state->r10 = val; }

reg_t
state::r11() const noexcept
{ return m_state->r11; }

void
state::set_r11(reg_t val) noexcept
{ m_state->r11 = val; }

reg_t
state::r12() const noexcept
{ return m_state->r12; }

void
state::set_r12(reg_t val) noexcept
{ m_state->r12 = val; }

reg_t
state::r13() const noexcept
{ return m_state->r13; }

void
state::set_r13(reg_t val) noexcept
{ m_state->r13 = val; }

reg_t
state::r14() const noexcept
{ return m_state->r14; }

void
state::set_r14(reg_t val) noexcept
{ m_state->r14 = val; }

reg_t
state::r15() const noexcept
{ return m_state->r15; }

void
state::set_r15(reg_t val) noexcept
{ m_state->r15 = val; }

reg_t
state::rip() const noexcept
{ return m_state->rip; }

void
state::set_rip(reg_t val) noexcept
{ m_state->rip = val; }

reg_t
state::rsp() const noexcept
{ return m_state->rsp; }

void
state::set_rsp(reg_t val) noexcept
{ m_state->rsp = val; }

reg_t
state::exit_reason() const noexcept
{ return m_state->exit_reason; }

reg_t
state::ia32_vmx_cr0_fixed0() const noexcept
{ return m_state->ia32_vmx_cr0_fixed0; }

void
state::set_ia32_vmx_cr0_fixed0(reg_t val) noexcept
{ m_state->ia32_vmx_cr0_fixed0 = val; }

reg_t
state::ia32_vmx_cr4_fixed0() const noexcept
{ return m_state->ia32_vmx_cr4_fixed0; }

void
state::set_ia32_vmx_cr4_fixed0(reg_t val) noexcept
{ m_state->ia32_vmx_cr4_fixed0 = val; }

}
