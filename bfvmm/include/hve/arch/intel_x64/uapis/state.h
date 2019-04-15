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

#ifndef UAPIS_STATE_INTEL_X64_H
#define UAPIS_STATE_INTEL_X64_H

#include "../private.h"

// -----------------------------------------------------------------------------
// Interface Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64::uapis
{

/// State
///
/// Defines the register state of the vCPU as well as other register types
/// that are not managed by the VMCS architecturally (examples include the
/// vCPU's ids, exit reason info, etc...). More specifically, the registers
/// in this interface are mostly used by the VMCS for performing things like
/// entries, exits, etc...
///
template<typename IMPL>
class state
{
public:

    /// Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu the vCPU that is associated with this interface
    ///
    explicit state(gsl::not_null<vcpu *> vcpu) :
        m_impl{vcpu}
    { }

public:

    /// Get RAX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rax register
    ///
    inline reg_t rax() const noexcept
    { return m_impl.rax(); }

    /// Set RAX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rax register to
    ///
    inline void set_rax(reg_t val) noexcept
    { m_impl.set_rax(val); }

    /// Get RBX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rbx register
    ///
    inline reg_t rbx() const noexcept
    { return m_impl.rbx(); }

    /// Set RBX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rbx register to
    ///
    inline void set_rbx(reg_t val) noexcept
    { m_impl.set_rbx(val); }

    /// Get RCX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rcx register
    ///
    inline reg_t rcx() const noexcept
    { return m_impl.rcx(); }

    /// Set RCX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rcx register to
    ///
    inline void set_rcx(reg_t val) noexcept
    { m_impl.set_rcx(val); }

    /// Get RDX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rdx register
    ///
    inline reg_t rdx() const noexcept
    { return m_impl.rdx(); }

    /// Set RDX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rdx register to
    ///
    inline void set_rdx(reg_t val) noexcept
    { m_impl.set_rdx(val); }

    /// Get RBP
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rbp register
    ///
    inline reg_t rbp() const noexcept
    { return m_impl.rbp(); }

    /// Set RBP
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rbp register to
    ///
    inline void set_rbp(reg_t val) noexcept
    { m_impl.set_rbp(val); }

    /// Get RSI
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rsi register
    ///
    inline reg_t rsi() const noexcept
    { return m_impl.rsi(); }

    /// Set RSI
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rsi register to
    ///
    inline void set_rsi(reg_t val) noexcept
    { m_impl.set_rsi(val); }

    /// Get RDI
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rdi register
    ///
    inline reg_t rdi() const noexcept
    { return m_impl.rdi(); }

    /// Set RDI
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rdi register to
    ///
    inline void set_rdi(reg_t val) noexcept
    { m_impl.set_rdi(val); }

    /// Get R08
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r08 register
    ///
    inline reg_t r08() const noexcept
    { return m_impl.r08(); }

    /// Set R08
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r08 register to
    ///
    inline void set_r08(reg_t val) noexcept
    { m_impl.set_r08(val); }

    /// Get R09
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r09 register
    ///
    inline reg_t r09() const noexcept
    { return m_impl.r09(); }

    /// Set R09
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r09 register to
    ///
    inline void set_r09(reg_t val) noexcept
    { m_impl.set_r09(val); }

    /// Get R10
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r10 register
    ///
    inline reg_t r10() const noexcept
    { return m_impl.r10(); }

    /// Set R10
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r10 register to
    ///
    inline void set_r10(reg_t val) noexcept
    { m_impl.set_r10(val); }

    /// Get R11
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r11 register
    ///
    inline reg_t r11() const noexcept
    { return m_impl.r11(); }

    /// Set R11
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r11 register to
    ///
    inline void set_r11(reg_t val) noexcept
    { m_impl.set_r11(val); }

    /// Get R12
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r12 register
    ///
    inline reg_t r12() const noexcept
    { return m_impl.r12(); }

    /// Set R12
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r12 register to
    ///
    inline void set_r12(reg_t val) noexcept
    { m_impl.set_r12(val); }

    /// Get R13
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r13 register
    ///
    inline reg_t r13() const noexcept
    { return m_impl.r13(); }

    /// Set R13
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r13 register to
    ///
    inline void set_r13(reg_t val) noexcept
    { m_impl.set_r13(val); }

    /// Get R14
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r14 register
    ///
    inline reg_t r14() const noexcept
    { return m_impl.r14(); }

    /// Set R14
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r14 register to
    ///
    inline void set_r14(reg_t val) noexcept
    { m_impl.set_r14(val); }

    /// Get R15
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r15 register
    ///
    inline reg_t r15() const noexcept
    { return m_impl.r15(); }

    /// Set R15
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r15 register to
    ///
    inline void set_r15(reg_t val) noexcept
    { m_impl.set_r15(val); }

    /// Get RIP
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rip register
    ///
    inline reg_t rip() const noexcept
    { return m_impl.rip(); }

    /// Set RIP
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rip register to
    ///
    inline void set_rip(reg_t val) noexcept
    { m_impl.set_rip(val); }

    /// Get RSP
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rsp register
    ///
    inline reg_t rsp() const noexcept
    { return m_impl.rsp(); }

    /// Set RSP
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rsp register to
    ///
    inline void set_rsp(reg_t val) noexcept
    { m_impl.set_rsp(val); }

    /// Exit Reason
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the exit reason for the current VMExit
    ///
    inline reg_t exit_reason() const noexcept
    { return m_impl.exit_reason(); }

    /// Get CR0 Fixed 0 (MSR)
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's ia32_vmx_cr0_fixed0 MSR
    ///
    inline reg_t ia32_vmx_cr0_fixed0() const noexcept
    { return m_impl.ia32_vmx_cr0_fixed0(); }

    /// Set CR4 Fixed 0 (MSR)
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's ia32_vmx_cr4_fixed0 MSR to
    ///
    inline void set_ia32_vmx_cr0_fixed0(reg_t val) noexcept
    { m_impl.set_ia32_vmx_cr0_fixed0(val); }

    /// Get CR4 Fixed 0 (MSR)
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's ia32_vmx_cr4_fixed0 MSR
    ///
    inline reg_t ia32_vmx_cr4_fixed0() const noexcept
    { return m_impl.ia32_vmx_cr4_fixed0(); }

    /// Set CR4 Fixed 0 (MSR)
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's ia32_vmx_cr4_fixed0 MSR to
    ///
    inline void set_ia32_vmx_cr4_fixed0(reg_t val) noexcept
    { m_impl.set_ia32_vmx_cr4_fixed0(val); }

private:
    PRIVATE_INTERFACES(state);
};

}

// -----------------------------------------------------------------------------
// Wrappers
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64::state
{

}

// -----------------------------------------------------------------------------
// Wrapper Overloads
// -----------------------------------------------------------------------------

/// @cond

namespace bfvmm::intel_x64::state
{

}

/// @endcond

#endif
