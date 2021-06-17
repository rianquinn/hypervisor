/// @copyright
/// Copyright (C) 2020 Assured Information Security, Inc.
///
/// @copyright
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// @copyright
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// @copyright
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

#ifndef VMEXIT_T_HPP
#define VMEXIT_T_HPP

#include <bf_debug_ops.hpp>
#include <bf_syscall_t.hpp>
#include <cpuid_commands.hpp>
#include <gs_t.hpp>
#include <intrinsic_t.hpp>
#include <tls_t.hpp>
#include <vp_pool_t.hpp>
#include <vps_pool_t.hpp>

#include <bsl/debug.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely_assert.hpp>

namespace example
{
    /// @class example::vmexit_t
    ///
    /// <!-- description -->
    ///   @brief Defines the extension's VMExit handler
    ///
    class vmexit_t final
    {
    public:
        /// <!-- description -->
        ///   @brief Initializes this vmexit_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vp_pool the vp_pool_t to use
        ///   @param vps_pool the vps_pool_t to use
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] static constexpr auto
        initialize(
            gs_t &gs,
            tls_t &tls,
            syscall::bf_syscall_t &sys,
            intrinsic_t &intrinsic,
            vp_pool_t &vp_pool,
            vps_pool_t &vps_pool) noexcept -> bsl::errc_type
        {
            bsl::discard(gs);
            bsl::discard(tls);
            bsl::discard(sys);
            bsl::discard(intrinsic);
            bsl::discard(vp_pool);
            bsl::discard(vps_pool);

            /// NOTE:
            /// - Add initialization code here if needed. Otherwise, this
            ///   function can be removed if it is not needed.
            ///

            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Release the vmexit_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vp_pool the vp_pool_t to use
        ///   @param vps_pool the vps_pool_t to use
        ///
        static constexpr void
        release(
            gs_t &gs,
            tls_t &tls,
            syscall::bf_syscall_t &sys,
            intrinsic_t &intrinsic,
            vp_pool_t &vp_pool,
            vps_pool_t &vps_pool) noexcept
        {
            bsl::discard(gs);
            bsl::discard(tls);
            bsl::discard(sys);
            bsl::discard(intrinsic);
            bsl::discard(vp_pool);
            bsl::discard(vps_pool);

            /// NOTE:
            /// - Release functions are usually only needed in the event of
            ///   an error, or during unit testing.
            ///
        }

        /// <!-- description -->
        ///   @brief Handle NMIs. This is required by Intel.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vp_pool the vp_pool_t to use
        ///   @param vps_pool the vps_pool_t to use
        ///   @param vpsid the ID of the VPS that generated the VMExit
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] static constexpr auto
        handle_nmi(
            gs_t &gs,
            tls_t &tls,
            syscall::bf_syscall_t &sys,
            intrinsic_t &intrinsic,
            vp_pool_t &vp_pool,
            vps_pool_t &vps_pool,
            bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
        {
            bsl::discard(gs);
            bsl::discard(tls);
            bsl::discard(intrinsic);
            bsl::discard(vp_pool);
            bsl::discard(vps_pool);

            /// NOTE:
            /// - If we caught an NMI, we need to inject it into the VM. To do
            ///   this, all we do is enable the NMI window, which will tell us
            ///   when we can safely inject the NMI.
            /// - Note that the microkernel will do the same thing. If an NMI
            ///   fires while the hypevisor is running, it will enable the NMI
            ///   window, which the extension will see as a VMExit, and must
            ///   from there, inject the NMI into the appropriate VPS.
            ///

            constexpr auto vmcs_procbased_ctls_idx{bsl::to_umax(0x4002U)};
            constexpr auto vmcs_set_nmi_window_exiting{bsl::to_u32(0x400000U)};

            bsl::safe_uint32 val{};
            bsl::errc_type ret{};

            val = sys.bf_vps_op_read32(vpsid, vmcs_procbased_ctls_idx);
            if (bsl::unlikely_assert(!val)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            val |= vmcs_set_nmi_window_exiting;

            ret = sys.bf_vps_op_write32(vpsid, vmcs_procbased_ctls_idx, val);
            if (bsl::unlikely_assert(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            return sys.bf_vps_op_run_current();
        }

        /// <!-- description -->
        ///   @brief Handle NMIs Windows
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vp_pool the vp_pool_t to use
        ///   @param vps_pool the vps_pool_t to use
        ///   @param vpsid the ID of the VPS that generated the VMExit
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] static constexpr auto
        handle_nmi_window(
            gs_t &gs,
            tls_t &tls,
            syscall::bf_syscall_t &sys,
            intrinsic_t &intrinsic,
            vp_pool_t &vp_pool,
            vps_pool_t &vps_pool,
            bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
        {
            bsl::discard(gs);
            bsl::discard(tls);
            bsl::discard(intrinsic);
            bsl::discard(vp_pool);
            bsl::discard(vps_pool);

            /// NOTE:
            /// - If we see this exit, it is because an NMI fired. There are two
            ///   situations where this could occur, either while the hypervisor
            ///   is running, or the VPS is running. In either case, we need to
            ///   clear the NMI window and inject the NMI into the appropriate
            ///   VPS so that it can be handled. Note that Intel requires that
            ///   we handle NMIs, and they actually happen a lot with Linux based
            ///   on what hardware you are using (e.g., a laptop).
            ///

            constexpr auto vmcs_procbased_ctls_idx{bsl::to_umax(0x4002U)};
            constexpr auto vmcs_clear_nmi_window_exiting{bsl::to_u32(0xFFBFFFFFU)};

            bsl::safe_uint32 val{};
            bsl::errc_type ret{};

            val = sys.bf_vps_op_read32(vpsid, vmcs_procbased_ctls_idx);
            if (bsl::unlikely_assert(!val)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            val &= vmcs_clear_nmi_window_exiting;

            ret = sys.bf_vps_op_write32(vpsid, vmcs_procbased_ctls_idx, val);
            if (bsl::unlikely_assert(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            /// NOTE:
            /// - Inject an NMI. If the NMI window was enabled, it is because we
            ///   need to inject a NMI. Note that the NMI window can be enabled
            ///   both by this extension, as well as by the microkernel itself,
            ///   so we are required to implement it on Intel.
            ///

            constexpr auto vmcs_entry_interrupt_info_idx{bsl::to_umax(0x4016U)};
            constexpr auto vmcs_entry_interrupt_info_val{bsl::to_u32(0x80000202U)};

            ret = sys.bf_vps_op_write32(
                vpsid, vmcs_entry_interrupt_info_idx, vmcs_entry_interrupt_info_val);
            if (bsl::unlikely_assert(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return ret;
            }

            return sys.bf_vps_op_run_current();
        }

        /// <!-- description -->
        ///   @brief Handles the CPUID VMexit
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vp_pool the vp_pool_t to use
        ///   @param vps_pool the vps_pool_t to use
        ///   @param vpsid the ID of the VPS that generated the VMExit
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] static constexpr auto
        handle_cpuid(
            gs_t &gs,
            tls_t &tls,
            syscall::bf_syscall_t &sys,
            intrinsic_t &intrinsic,
            vp_pool_t &vp_pool,
            vps_pool_t &vps_pool,
            bsl::safe_uint16 const &vpsid) noexcept -> bsl::errc_type
        {
            bsl::discard(gs);
            bsl::discard(tls);
            bsl::discard(vp_pool);
            bsl::discard(vps_pool);

            bsl::errc_type ret{};

            /// NOTE:
            /// - The first thing that we need to do is get the current values
            ///   of RAX, RBX, RCX and RDX. We use the full 64bit versions to
            ///   ensure that we leave the upper half of these values intact,
            ///   otherwise we would not be emulating the execution of CPUID
            ///   correctly.
            ///

            auto rax{sys.bf_tls_rax()};
            auto rbx{sys.bf_tls_rbx()};
            auto rcx{sys.bf_tls_rcx()};
            auto rdx{sys.bf_tls_rdx()};

            /// NOTE:
            /// - Before we execute CPUID, we need to check to see if we have
            ///   received a CPUID command. If we have, we need to handle this
            ///   CPUID differently.
            ///

            if (loader::CPUID_COMMAND_EAX == bsl::to_u32_unsafe(rax)) {
                switch (bsl::to_u32_unsafe(rcx).get()) {
                    case loader::CPUID_COMMAND_ECX_STOP.get(): {

                        /// NOTE:
                        /// - If this is the first PP to stop (which is the
                        ///   last PP in the list as we stop in reverse order),
                        ///   print out how much memory was used by the
                        ///   hypervisor. This is a debugging feature that can
                        ///   be disabled, but it helps to track if memory is
                        ///   being over used.
                        ///

                        if (sys.bf_tls_ppid() == (sys.bf_tls_online_pps() - bsl::ONE_U16)) {
                            bsl::print() << bsl::endl;
                            syscall::bf_debug_op_dump_page_pool();
                            bsl::print() << bsl::endl;
                        }
                        else {
                            bsl::touch();
                        }

                        /// NOTE:
                        /// - If the debug level is set to something higher
                        ///   than bsl::V, we can print out a VMExit log. How
                        ///   many entries we print is configurable, and you
                        ///   can control which PP you want to output if you
                        ///   only care about a specific PP. Note that this log
                        ///   will show VMExits for the whole PP, meaning you
                        ///   will see the order in which different VM's are
                        ///   making VMExits. The VMExit log doesn't attempt
                        ///   to decode anything, so that is up to you.
                        ///

                        if constexpr (BSL_DEBUG_LEVEL > bsl::V) {
                            bsl::print() << bsl::endl;
                            syscall::bf_debug_op_dump_vmexit_log(sys.bf_tls_ppid());
                        }

                        /// NOTE:
                        /// - Report that the root OS is no longer in a VM for
                        ///   this specific PP. Note that you can do whatever
                        ///   you want here, this is just the default behavior.
                        ///   To report success on promotion after promotion
                        ///   takes place would require that the loader reports
                        ///   success, which we do not do as we are not sure
                        ///   what the extension wants, so the message here
                        ///   should state that we are "about to", and not that
                        ///   it is "done", because it might fail.
                        ///

                        bsl::debug() << bsl::rst << "about to"                     // --
                                     << bsl::red << " promote "                    // --
                                     << bsl::rst << "root OS on pp "               // --
                                     << bsl::cyn << bsl::hex(sys.bf_tls_ppid())    // --
                                     << bsl::rst << bsl::endl;                     // --

                        /// NOTE:
                        /// - Report success
                        ///

                        sys.bf_tls_set_rax(loader::CPUID_COMMAND_RAX_SUCCESS);

                        /// NOTE:
                        /// - Before we can stop, we need to advance RIP.
                        ///   Normally, all of the other commands will advance
                        ///   and return to the VM at the end of this switch
                        ///   statement, but in this case, promote will not
                        ///   exit before then so we need to advance now.
                        ///

                        ret = sys.bf_vps_op_advance_ip(vpsid);
                        if (bsl::unlikely_assert(!ret)) {
                            bsl::print<bsl::V>() << bsl::here();
                            return ret;
                        }

                        /// NOTE:
                        /// - The promote ABI will load the microkernel by
                        ///   replacing the CPU's state withthe VP state
                        ///   associated with the provided VPSID. If all
                        ///   goes well, bf_vps_op_promote will not return,
                        ///   and the system will continue executing with the
                        ///   hypervisor turned off.
                        ///

                        return sys.bf_vps_op_promote(vpsid);
                    }

                    case loader::CPUID_COMMAND_ECX_REPORT_ON.get(): {

                        /// NOTE:
                        /// - Report that the root OS is now in a VM for this
                        ///   specific PP. Note that you can do whatever you
                        ///   want here, this is just the default behavior.
                        ///

                        bsl::debug() << bsl::rst << "root OS had been"             // --
                                     << bsl::grn << " demoted "                    // --
                                     << bsl::rst << "to vm "                       // --
                                     << bsl::cyn << bsl::hex(sys.bf_tls_vmid())    // --
                                     << bsl::rst << " on pp "                      // --
                                     << bsl::cyn << bsl::hex(sys.bf_tls_ppid())    // --
                                     << bsl::rst << bsl::endl;                     // --

                        break;
                    }

                    case loader::CPUID_COMMAND_ECX_REPORT_OFF.get(): {

                        /// NOTE:
                        /// - There is nothing to do here as we report off
                        ///   right before promotion takes place. Extensions
                        ///   can use this as a means to perform actions if
                        ///   needed right before the loader sends the stop
                        ///   command. Just note that this command does not
                        ///   report success/failure.
                        ///

                        break;
                    }

                    default: {
                        bsl::error() << "unsupported cpuid command "    // --
                                     << bsl::hex(rcx)                   // --
                                     << bsl::endl                       // --
                                     << bsl::here();                    // --

                        break;
                    }
                }

                /// NOTE:
                /// - Complete this command by advancing RIP and running
                ///   the currently loaded VM, VP and VPS.
                ///

                return sys.bf_vps_op_advance_ip_and_run_current();
            }

            /// NOTE:
            /// - If we got this far, this is a normal CPUID, which means we
            ///   simply need to emulate its execution by calling CPUID and
            ///   returning the results.
            ///

            intrinsic.cpuid(rax, rbx, rcx, rdx);

            /// NOTE:
            /// - Write the results of CPUID to the VP's registers. Note that
            ///   the above CPUID intrinsic takes in the full 64bit registers
            ///   but only touches the lower half of each register, which makes
            ///   sure that we are emulating CPUID properly.
            ///

            sys.bf_tls_set_rax(rax);
            sys.bf_tls_set_rbx(rbx);
            sys.bf_tls_set_rcx(rcx);
            sys.bf_tls_set_rdx(rdx);

            /// NOTE:
            /// - Complete the emulation of CPUID by advancing RIP and running
            ///   the currently loaded VM, VP and VPS.
            ///

            return sys.bf_vps_op_advance_ip_and_run_current();
        }

        /// <!-- description -->
        ///   @brief Dispatches the VMExit.
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vp_pool the vp_pool_t to use
        ///   @param vps_pool the vps_pool_t to use
        ///   @param vpsid the ID of the VPS that generated the VMExit
        ///   @param exit_reason the exit reason associated with the VMExit
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        [[nodiscard]] static constexpr auto
        dispatch(
            gs_t &gs,
            tls_t &tls,
            syscall::bf_syscall_t &sys,
            intrinsic_t &intrinsic,
            vp_pool_t &vp_pool,
            vps_pool_t &vps_pool,
            bsl::safe_uint16 const &vpsid,
            bsl::safe_uint64 const &exit_reason) noexcept -> bsl::errc_type
        {
            /// NOTE:
            /// - Define the different VMExits that this dispatcher will
            ///   support. At a minimum, we need to handle CPUID, and NMIs
            ///   on Intel (as there is no way to disable NMIs on Intel).
            ///

            constexpr auto exit_reason_nmi{bsl::to_umax(0x0)};
            constexpr auto exit_reason_nmi_window{bsl::to_umax(0x8)};
            constexpr auto exit_reason_cpuid{bsl::to_umax(0xA)};

            /// NOTE:
            /// - Dispatch and handle each VMExit.
            ///

            switch (exit_reason.get()) {
                case exit_reason_nmi.get(): {
                    return handle_nmi(gs, tls, sys, intrinsic, vp_pool, vps_pool, vpsid);
                }

                case exit_reason_nmi_window.get(): {
                    return handle_nmi_window(gs, tls, sys, intrinsic, vp_pool, vps_pool, vpsid);
                }

                case exit_reason_cpuid.get(): {
                    return handle_cpuid(gs, tls, sys, intrinsic, vp_pool, vps_pool, vpsid);
                }

                default: {
                    break;
                }
            }

            /// NOTE:
            /// - If we got this far, it means that we were given a VMExit
            ///   that we do not handle.
            ///

            bsl::error() << "unsupported vmexit "    // --
                         << bsl::hex(exit_reason)    // --
                         << bsl::endl                // --
                         << bsl::here();             // --

            return bsl::errc_failure;
        }
    };
}

#endif
