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

#ifndef UAPIS_exit_handler_INTEL_X64_H
#define UAPIS_exit_handler_INTEL_X64_H

#include "../private.h"

// -----------------------------------------------------------------------------
// Types/Namespaces
// -----------------------------------------------------------------------------

// *INDENT-OFF*

namespace bfvmm::intel_x64::exit_handler
{
    /// Exit Reason Type
    ///
    /// This defines the exit reason type that is used in this interface
    ///
    using exit_reason_t = uint64_t;

    /// Exit Handlers Type
    ///
    /// This defines the exit handlers type that is used in this interface
    ///
    using exit_handlers_t = std::list<handler_delegate_t>;

    /// Exit Reasons
    ///
    /// The following are imported version of the exit reasons in the
    /// intrinsics to match the type that is defined here.
    ///
    /// @cond
    ///

    constexpr auto exception_or_nmi = vmcs_n::exit_reason::basic_exit_reason::exception_or_nmi;
    constexpr auto external_interrupt = vmcs_n::exit_reason::basic_exit_reason::external_interrupt;
    constexpr auto triple_fault = vmcs_n::exit_reason::basic_exit_reason::triple_fault;
    constexpr auto init_signal = vmcs_n::exit_reason::basic_exit_reason::init_signal;
    constexpr auto sipi = vmcs_n::exit_reason::basic_exit_reason::sipi;
    constexpr auto smi = vmcs_n::exit_reason::basic_exit_reason::smi;
    constexpr auto other_smi = vmcs_n::exit_reason::basic_exit_reason::other_smi;
    constexpr auto interrupt_window = vmcs_n::exit_reason::basic_exit_reason::interrupt_window;
    constexpr auto nmi_window = vmcs_n::exit_reason::basic_exit_reason::nmi_window;
    constexpr auto task_switch = vmcs_n::exit_reason::basic_exit_reason::task_switch;
    constexpr auto cpuid = vmcs_n::exit_reason::basic_exit_reason::cpuid;
    constexpr auto getsec = vmcs_n::exit_reason::basic_exit_reason::getsec;
    constexpr auto hlt = vmcs_n::exit_reason::basic_exit_reason::hlt;
    constexpr auto invd = vmcs_n::exit_reason::basic_exit_reason::invd;
    constexpr auto invlpg = vmcs_n::exit_reason::basic_exit_reason::invlpg;
    constexpr auto rdpmc = vmcs_n::exit_reason::basic_exit_reason::rdpmc;
    constexpr auto rdtsc = vmcs_n::exit_reason::basic_exit_reason::rdtsc;
    constexpr auto rsm = vmcs_n::exit_reason::basic_exit_reason::rsm;
    constexpr auto vmcall = vmcs_n::exit_reason::basic_exit_reason::vmcall;
    constexpr auto vmclear = vmcs_n::exit_reason::basic_exit_reason::vmclear;
    constexpr auto vmlaunch = vmcs_n::exit_reason::basic_exit_reason::vmlaunch;
    constexpr auto vmptrld = vmcs_n::exit_reason::basic_exit_reason::vmptrld;
    constexpr auto vmptrst = vmcs_n::exit_reason::basic_exit_reason::vmptrst;
    constexpr auto vmread = vmcs_n::exit_reason::basic_exit_reason::vmread;
    constexpr auto vmresume = vmcs_n::exit_reason::basic_exit_reason::vmresume;
    constexpr auto vmwrite = vmcs_n::exit_reason::basic_exit_reason::vmwrite;
    constexpr auto vmxoff = vmcs_n::exit_reason::basic_exit_reason::vmxoff;
    constexpr auto vmxon = vmcs_n::exit_reason::basic_exit_reason::vmxon;
    constexpr auto control_register_accesses = vmcs_n::exit_reason::basic_exit_reason::control_register_accesses;
    constexpr auto mov_dr = vmcs_n::exit_reason::basic_exit_reason::mov_dr;
    constexpr auto io_instruction = vmcs_n::exit_reason::basic_exit_reason::io_instruction;
    constexpr auto rdmsr = vmcs_n::exit_reason::basic_exit_reason::rdmsr;
    constexpr auto wrmsr = vmcs_n::exit_reason::basic_exit_reason::wrmsr;
    constexpr auto vm_entry_failure_invalid_guest_state = vmcs_n::exit_reason::basic_exit_reason::vm_entry_failure_invalid_guest_state;
    constexpr auto vm_entry_failure_msr_loading = vmcs_n::exit_reason::basic_exit_reason::vm_entry_failure_msr_loading;
    constexpr auto mwait = vmcs_n::exit_reason::basic_exit_reason::mwait;
    constexpr auto monitor_trap_flag = vmcs_n::exit_reason::basic_exit_reason::monitor_trap_flag;
    constexpr auto monitor = vmcs_n::exit_reason::basic_exit_reason::monitor;
    constexpr auto pause = vmcs_n::exit_reason::basic_exit_reason::pause;
    constexpr auto vm_entry_failure_machine_check_event = vmcs_n::exit_reason::basic_exit_reason::vm_entry_failure_machine_check_event;
    constexpr auto tpr_below_threshold = vmcs_n::exit_reason::basic_exit_reason::tpr_below_threshold;
    constexpr auto apic_access = vmcs_n::exit_reason::basic_exit_reason::apic_access;
    constexpr auto virtualized_eoi = vmcs_n::exit_reason::basic_exit_reason::virtualized_eoi;
    constexpr auto access_to_gdtr_or_idtr = vmcs_n::exit_reason::basic_exit_reason::access_to_gdtr_or_idtr;
    constexpr auto access_to_ldtr_or_tr = vmcs_n::exit_reason::basic_exit_reason::access_to_ldtr_or_tr;
    constexpr auto ept_violation = vmcs_n::exit_reason::basic_exit_reason::ept_violation;
    constexpr auto ept_misconfiguration = vmcs_n::exit_reason::basic_exit_reason::ept_misconfiguration;
    constexpr auto invept = vmcs_n::exit_reason::basic_exit_reason::invept;
    constexpr auto rdtscp = vmcs_n::exit_reason::basic_exit_reason::rdtscp;
    constexpr auto preemption_timer = vmcs_n::exit_reason::basic_exit_reason::preemption_timer;
    constexpr auto invvpid = vmcs_n::exit_reason::basic_exit_reason::invvpid;
    constexpr auto wbinvd = vmcs_n::exit_reason::basic_exit_reason::wbinvd;
    constexpr auto xsetbv = vmcs_n::exit_reason::basic_exit_reason::xsetbv;
    constexpr auto apic_write = vmcs_n::exit_reason::basic_exit_reason::apic_write;
    constexpr auto rdrand = vmcs_n::exit_reason::basic_exit_reason::rdrand;
    constexpr auto invpcid = vmcs_n::exit_reason::basic_exit_reason::invpcid;
    constexpr auto vmfunc = vmcs_n::exit_reason::basic_exit_reason::vmfunc;
    constexpr auto rdseed = vmcs_n::exit_reason::basic_exit_reason::rdseed;
    constexpr auto xsaves = vmcs_n::exit_reason::basic_exit_reason::xsaves;
    constexpr auto xrstors = vmcs_n::exit_reason::basic_exit_reason::xrstors;

    /// @endcond
}

/// Exit Handler Namespace
///
namespace exit_handler_n = bfvmm::intel_x64::exit_handler;

// *INDENT-ON*

// -----------------------------------------------------------------------------
// Interface Defintion
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64::uapis
{

/// Exit Handler
///
/// Defines the Exit Handler interfaces provided by the vCPU.
///
template<typename IMPL>
class exit_handler
{
public:

    /// Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu the vCPU that is associated with this interface
    ///
    explicit exit_handler(gsl::not_null<vcpu *> vcpu) :
        m_impl{vcpu}
    { }

public:

    /// Exit Handler Add
    ///
    /// Adds a delegate to the exit handler list. Exit delegates are executed
    /// right after a VMExit for any reason. Note that this should only be used
    /// if you are 100% sure you need a delegate to execute on every VMExit.
    /// If delegates are added to this list, ensure they execute as fast as
    /// possible.
    ///
    /// Also note that if a registered delegate returns true, the vCPU will
    /// perform a VMResume. All registered delegates should return false unless
    /// the delegate intends to be the last delegate to execute. Also note that
    /// at least one delegate has to return true, but in most cases, the base
    /// APIs will take of this for you. Returning true should only be done if
    /// you fully understand what the base implementation is doing.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param d The delegate being registered
    ///
    inline void exit_handler_add(const handler_delegate_t &d)
    { m_impl.add(d); }

    /// Exit Handler Add (For Reason)
    ///
    /// Adds a delegate to the exit handler list for a specific VMExit reason.
    /// Exit delegates are executed right after a VMExit. Note that in most
    /// cases you should register with the associated APIs. The only time you
    /// would use this function directly is if the base hypervisor doesn't
    /// provide APIs for the exit you are attempting to handle. If this ends up
    /// being the case, consider working with the Bareflank community to more
    /// officially add the missing APIs.
    ///
    /// Also note that if a registered delegate returns true, the vCPU will
    /// perform a VMResume. All registered delegates should return false unless
    /// the delegate intends to be the last delegate to execute. Also note that
    /// at least one delegate has to return true, but in most cases, the base
    /// APIs will take of this for you. Returning true should only be done if
    /// you fully understand what the base implementation is doing.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param reason the VMExit reason the delegate is being registered for
    /// @param d The delegate being registered
    ///
    inline void exit_handler_add_for_reason(
        exit_handler_n::exit_reason_t reason, const handler_delegate_t &d)
    { m_impl.add_for_reason(reason, d); }

public:

    /// Private
    ///
    /// The following APIs are private and should not be used by an end user.
    /// These are made public for internal use only, and these APIs are subject
    /// to change. You have been warned.
    ///
    /// @cond
    ///

    inline const exit_handlers_t &exit_handlers() const noexcept
    { return m_impl.exit_handlers(); }

    inline const exit_handlers_t &exit_handlers_for_reason(
        exit_handler_n::exit_reason_t reason) const noexcept
    { return m_impl.exit_handlers_for_reason(); }

    /// @endcond

private:
    PRIVATE_INTERFACES(exit_handler);
};

}

// -----------------------------------------------------------------------------
// Wrappers
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64::exit_handler
{

}

// -----------------------------------------------------------------------------
// Wrapper Overloads
// -----------------------------------------------------------------------------

/// @cond

namespace bfvmm::intel_x64::exit_handler
{

}

/// @endcond

#endif
