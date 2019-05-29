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

#include <bfgsl.h>
#include <bftypes.h>

#include "../../impl.h"

// -----------------------------------------------------------------------------
// Interface Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::uapis::intel_x64
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
struct state
{
    using reg_t = uint64_t;     ///< pCPU register type

    /// Get RAX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rax register
    ///
    CONSTEXPR reg_t rax() const noexcept
    { return impl<const IMPL>(this)->__rax(); }

    /// Set RAX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rax register to
    ///
    CONSTEXPR void set_rax(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_rax(val); }

    /// Get RBX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rbx register
    ///
    CONSTEXPR reg_t rbx() const noexcept
    { return impl<const IMPL>(this)->__rbx(); }

    /// Set RBX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rbx register to
    ///
    CONSTEXPR void set_rbx(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_rbx(val); }

    /// Get RCX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rcx register
    ///
    CONSTEXPR reg_t rcx() const noexcept
    { return impl<const IMPL>(this)->__rcx(); }

    /// Set RCX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rcx register to
    ///
    CONSTEXPR void set_rcx(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_rcx(val); }

    /// Get RDX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rdx register
    ///
    CONSTEXPR reg_t rdx() const noexcept
    { return impl<const IMPL>(this)->__rdx(); }

    /// Set RDX
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rdx register to
    ///
    CONSTEXPR void set_rdx(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_rdx(val); }

    /// Get RBP
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rbp register
    ///
    CONSTEXPR reg_t rbp() const noexcept
    { return impl<const IMPL>(this)->__rbp(); }

    /// Set RBP
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rbp register to
    ///
    CONSTEXPR void set_rbp(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_rbp(val); }

    /// Get RSI
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rsi register
    ///
    CONSTEXPR reg_t rsi() const noexcept
    { return impl<const IMPL>(this)->__rsi(); }

    /// Set RSI
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rsi register to
    ///
    CONSTEXPR void set_rsi(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_rsi(val); }

    /// Get RDI
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's rdi register
    ///
    CONSTEXPR reg_t rdi() const noexcept
    { return impl<const IMPL>(this)->__rdi(); }

    /// Set RDI
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's rdi register to
    ///
    CONSTEXPR void set_rdi(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_rdi(val); }

    /// Get R08
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r08 register
    ///
    CONSTEXPR reg_t r08() const noexcept
    { return impl<const IMPL>(this)->__r08(); }

    /// Set R08
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r08 register to
    ///
    CONSTEXPR void set_r08(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_r08(val); }

    /// Get R09
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r09 register
    ///
    CONSTEXPR reg_t r09() const noexcept
    { return impl<const IMPL>(this)->__r09(); }

    /// Set R09
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r09 register to
    ///
    CONSTEXPR void set_r09(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_r09(val); }

    /// Get R10
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r10 register
    ///
    CONSTEXPR reg_t r10() const noexcept
    { return impl<const IMPL>(this)->__r10(); }

    /// Set R10
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r10 register to
    ///
    CONSTEXPR void set_r10(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_r10(val); }

    /// Get R11
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r11 register
    ///
    CONSTEXPR reg_t r11() const noexcept
    { return impl<const IMPL>(this)->__r11(); }

    /// Set R11
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r11 register to
    ///
    CONSTEXPR void set_r11(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_r11(val); }

    /// Get R12
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r12 register
    ///
    CONSTEXPR reg_t r12() const noexcept
    { return impl<const IMPL>(this)->__r12(); }

    /// Set R12
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r12 register to
    ///
    CONSTEXPR void set_r12(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_r12(val); }

    /// Get R13
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r13 register
    ///
    CONSTEXPR reg_t r13() const noexcept
    { return impl<const IMPL>(this)->__r13(); }

    /// Set R13
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r13 register to
    ///
    CONSTEXPR void set_r13(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_r13(val); }

    /// Get R14
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r14 register
    ///
    CONSTEXPR reg_t r14() const noexcept
    { return impl<const IMPL>(this)->__r14(); }

    /// Set R14
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r14 register to
    ///
    CONSTEXPR void set_r14(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_r14(val); }

    /// Get R15
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's r15 register
    ///
    CONSTEXPR reg_t r15() const noexcept
    { return impl<const IMPL>(this)->__r15(); }

    /// Set R15
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's r15 register to
    ///
    CONSTEXPR void set_r15(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_r15(val); }

    /// Exit Reason
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the exit reason for the current VMExit
    ///
    CONSTEXPR reg_t exit_reason() const noexcept
    { return impl<const IMPL>(this)->__exit_reason(); }

    /// Set Exit Reason
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's exit_reason register to
    ///
    CONSTEXPR void set_exit_reason(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_exit_reason(val); }

    /// Get CR0 Fixed 0 (MSR)
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's ia32_vmx_cr0_fixed0 MSR
    ///
    CONSTEXPR reg_t ia32_vmx_cr0_fixed0() const noexcept
    { return impl<const IMPL>(this)->__ia32_vmx_cr0_fixed0(); }

    /// Set CR4 Fixed 0 (MSR)
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's ia32_vmx_cr4_fixed0 MSR to
    ///
    CONSTEXPR void set_ia32_vmx_cr0_fixed0(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_ia32_vmx_cr0_fixed0(val); }

    /// Get CR4 Fixed 0 (MSR)
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @return returns the guest's ia32_vmx_cr4_fixed0 MSR
    ///
    CONSTEXPR reg_t ia32_vmx_cr4_fixed0() const noexcept
    { return impl<const IMPL>(this)->__ia32_vmx_cr4_fixed0(); }

    /// Set CR4 Fixed 0 (MSR)
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param val the value to set the guest's ia32_vmx_cr4_fixed0 MSR to
    ///
    CONSTEXPR void set_ia32_vmx_cr4_fixed0(reg_t val) noexcept
    { impl<const IMPL>(this)->__set_ia32_vmx_cr4_fixed0(val); }
};

}

// -----------------------------------------------------------------------------
// Wrappers
// -----------------------------------------------------------------------------

/// @cond

namespace bfvmm::intel_x64::state
{

template<typename IMPL>
constexpr auto rax(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->rax(); }

template<typename IMPL, typename... Args>
constexpr void set_rax(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_rax(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto rbx(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->rbx(); }

template<typename IMPL, typename... Args>
constexpr void set_rbx(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_rbx(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto rcx(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->rcx(); }

template<typename IMPL, typename... Args>
constexpr void set_rcx(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_rcx(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto rdx(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->rdx(); }

template<typename IMPL, typename... Args>
constexpr void set_rdx(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_rdx(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto rbp(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->rbp(); }

template<typename IMPL, typename... Args>
constexpr void set_rbp(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_rbp(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto rsi(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->rsi(); }

template<typename IMPL, typename... Args>
constexpr void set_rsi(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_rsi(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto rdi(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->rdi(); }

template<typename IMPL, typename... Args>
constexpr void set_rdi(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_rdi(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto r08(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->r08(); }

template<typename IMPL, typename... Args>
constexpr void set_r08(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_r08(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto r09(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->r09(); }

template<typename IMPL, typename... Args>
constexpr void set_r09(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_r09(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto r10(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->r10(); }

template<typename IMPL, typename... Args>
constexpr void set_r10(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_r10(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto r11(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->r11(); }

template<typename IMPL, typename... Args>
constexpr void set_r11(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_r11(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto r12(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->r12(); }

template<typename IMPL, typename... Args>
constexpr void set_r12(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_r12(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto r13(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->r13(); }

template<typename IMPL, typename... Args>
constexpr void set_r13(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_r13(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto r14(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->r14(); }

template<typename IMPL, typename... Args>
constexpr void set_r14(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_r14(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto r15(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->r15(); }

template<typename IMPL, typename... Args>
constexpr void set_r15(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_r15(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto exit_reason(gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->exit_reason(); }

template<typename IMPL, typename... Args>
constexpr void set_exit_reason(gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_exit_reason(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ia32_vmx_cr0_fixed0(
    gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->ia32_vmx_cr0_fixed0(); }

template<typename IMPL, typename... Args>
constexpr void set_ia32_vmx_cr0_fixed0(
    gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_ia32_vmx_cr0_fixed0(std::forward<Args>(args)...); }

template<typename IMPL>
constexpr auto ia32_vmx_cr4_fixed0(
    gsl::not_null<const IMPL *> vcpu) noexcept
{ return vcpu->ia32_vmx_cr4_fixed0(); }

template<typename IMPL, typename... Args>
constexpr void set_ia32_vmx_cr4_fixed0(
    gsl::not_null<IMPL *> vcpu, Args &&...args) noexcept
{ vcpu->set_ia32_vmx_cr4_fixed0(std::forward<Args>(args)...); }

}

/// @endcond

#endif
