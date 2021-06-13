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

#include "../../../../mocks/cpp/bf_syscall_t.hpp"

#include <bsl/discard.hpp>
#include <bsl/ut.hpp>

namespace syscall
{
    /// @brief stores the answer to all things (in 8 bits)
    constexpr bf_uint8_t g_answer8{bsl::to_u8(42)};
    /// @brief stores the answer to all things (in 16 bits)
    constexpr bf_uint16_t g_answer16{bsl::to_u16(42)};
    /// @brief stores the answer to all things (in 32 bits)
    constexpr bf_uint32_t g_answer32{bsl::to_u32(42)};
    /// @brief stores the answer to all things (in 64 bits)
    constexpr bf_uint64_t g_answer64{bsl::to_u64(42)};

    // -------------------------------------------------------------------------
    // dummy callbacks
    // -------------------------------------------------------------------------

    /// <!-- description -->
    ///   @brief Implements a dummy bootstrap entry function.
    ///
    /// <!-- inputs/outputs -->
    ///   @param ppid the physical process to bootstrap
    ///
    extern "C" void
    bootstrap_entry(syscall::bf_uint16_t::value_type const ppid) noexcept
    {
        bsl::discard(ppid);
    }

    /// <!-- description -->
    ///   @brief Implements a dummy VMExit entry function.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vpsid the ID of the VPS that generated the VMExit
    ///   @param exit_reason the exit reason associated with the VMExit
    ///
    extern "C" void
    vmexit_entry(
        syscall::bf_uint16_t::value_type const vpsid,
        syscall::bf_uint64_t::value_type const exit_reason) noexcept
    {
        bsl::discard(vpsid);
        bsl::discard(exit_reason);
    }

    /// <!-- description -->
    ///   @brief Implements a dummy fast fail entry function.
    ///
    /// <!-- inputs/outputs -->
    ///   @param vpsid the ID of the VPS that generated the fail
    ///   @param fail_reason the exit reason associated with the fail
    ///
    extern "C" void
    fail_entry(
        syscall::bf_uint16_t::value_type const vpsid,
        syscall::bf_status_t::value_type const fail_reason) noexcept
    {
        bsl::discard(vpsid);
        bsl::discard(fail_reason);
    }

    /// <!-- description -->
    ///   @brief Used to execute the actual checks. We put the checks in this
    ///     function so that we can validate the tests both at compile-time
    ///     and at run-time. If a bsl::ut_check fails, the tests will either
    ///     fail fast at run-time, or will produce a compile-time error.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Always returns bsl::exit_success.
    ///
    [[nodiscard]] constexpr auto
    tests() noexcept -> bsl::exit_code
    {
        bsl::ut_scenario{"quiet bootstrap_entry"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t arg0{g_answer16};
                bsl::ut_then{} = [&arg0]() {
                    bootstrap_entry(arg0.get());
                };
            };
        };

        bsl::ut_scenario{"quiet vmexit_entry"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{};
                bsl::ut_then{} = [&arg0, &arg1]() {
                    vmexit_entry(arg0.get(), arg1.get());
                };
            };
        };

        bsl::ut_scenario{"quiet fail_entry"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{};
                bsl::ut_then{} = [&arg0, &arg1]() {
                    fail_entry(arg0.get(), arg1.get());
                };
            };
        };

        bsl::ut_scenario{"initialize invalid version #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(!sys.initialize(
                        bf_uint32_t::zero(true), &bootstrap_entry, &vmexit_entry, &fail_entry));
                };
            };
        };

        bsl::ut_scenario{"initialize invalid version #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(
                        !sys.initialize({}, &bootstrap_entry, &vmexit_entry, &fail_entry));
                };
            };
        };

        bsl::ut_scenario{"initialize invalid bootstrap_handler"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(!sys.initialize(
                        BF_ALL_SPECS_SUPPORTED_VAL, {}, &vmexit_entry, &fail_entry));
                };
            };
        };

        bsl::ut_scenario{"initialize invalid bootstrap_handler"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(!sys.initialize(
                        BF_ALL_SPECS_SUPPORTED_VAL, &bootstrap_entry, {}, &fail_entry));
                };
            };
        };

        bsl::ut_scenario{"initialize invalid bootstrap_handler"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(!sys.initialize(
                        BF_ALL_SPECS_SUPPORTED_VAL, &bootstrap_entry, &vmexit_entry, {}));
                };
            };
        };

        bsl::ut_scenario{"initialize returns alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.set_initialize(bsl::errc_failure);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.initialize(
                            BF_ALL_SPECS_SUPPORTED_VAL,
                            &bootstrap_entry,
                            &vmexit_entry,
                            &fail_entry));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(sys.initialize(
                        BF_ALL_SPECS_SUPPORTED_VAL, &bootstrap_entry, &vmexit_entry, &fail_entry));
                };
            };
        };

        bsl::ut_scenario{"release executes"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    sys.release();
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rax/bf_tls_set_rax alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rax(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rax/bf_tls_set_rax success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rax(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rax());
                        bsl::ut_check(sys.bf_tls_rax() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbx/bf_tls_set_rbx alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rbx(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbx/bf_tls_set_rbx success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rbx(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rbx());
                        bsl::ut_check(sys.bf_tls_rbx() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rcx/bf_tls_set_rcx alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rcx(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rcx/bf_tls_set_rcx success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rcx(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rcx());
                        bsl::ut_check(sys.bf_tls_rcx() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdx/bf_tls_set_rdx alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rdx(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdx/bf_tls_set_rdx success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rdx(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rdx());
                        bsl::ut_check(sys.bf_tls_rdx() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbp/bf_tls_set_rbp alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rbp(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbp/bf_tls_set_rbp success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rbp(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rbp());
                        bsl::ut_check(sys.bf_tls_rbp() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rsi/bf_tls_set_rsi alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rsi(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rsi/bf_tls_set_rsi success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rsi(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rsi());
                        bsl::ut_check(sys.bf_tls_rsi() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdi/bf_tls_set_rdi alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rdi(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdi/bf_tls_set_rdi success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_rdi(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rdi());
                        bsl::ut_check(sys.bf_tls_rdi() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r8/bf_tls_set_r8 alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r8(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r8/bf_tls_set_r8 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r8(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r8());
                        bsl::ut_check(sys.bf_tls_r8() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r9/bf_tls_set_r9 alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r9(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r9/bf_tls_set_r9 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r9(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r9());
                        bsl::ut_check(sys.bf_tls_r9() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r10/bf_tls_set_r10 alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r10(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r10/bf_tls_set_r10 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r10(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r10());
                        bsl::ut_check(sys.bf_tls_r10() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r11/bf_tls_set_r11 alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r11(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r11/bf_tls_set_r11 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r11(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r11());
                        bsl::ut_check(sys.bf_tls_r11() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r12/bf_tls_set_r12 alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r12(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r12/bf_tls_set_r12 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r12(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r12());
                        bsl::ut_check(sys.bf_tls_r12() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r13/bf_tls_set_r13 alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r13(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r13/bf_tls_set_r13 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r13(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r13());
                        bsl::ut_check(sys.bf_tls_r13() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r14/bf_tls_set_r14 alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r14(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r14/bf_tls_set_r14 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r14(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r14());
                        bsl::ut_check(sys.bf_tls_r14() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r15/bf_tls_set_r15 alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r15(bf_uint64_t::zero(true));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r15/bf_tls_set_r15 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_r15(g_answer64);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r15());
                        bsl::ut_check(sys.bf_tls_r15() == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_extid/bf_tls_set_extid success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_extid(g_answer16);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_extid());
                        bsl::ut_check(sys.bf_tls_extid() == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vmid/bf_tls_set_vmid success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_vmid(g_answer16);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_vmid());
                        bsl::ut_check(sys.bf_tls_vmid() == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpid/bf_tls_set_vpid success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_vpid(g_answer16);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_vpid());
                        bsl::ut_check(sys.bf_tls_vpid() == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpsid/bf_tls_set_vpsid success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_vpsid(g_answer16);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_vpsid());
                        bsl::ut_check(sys.bf_tls_vpsid() == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_ppid/bf_tls_set_ppid success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_ppid(g_answer16);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_ppid());
                        bsl::ut_check(sys.bf_tls_ppid() == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_online_pps/bf_tls_set_online_pps success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.bf_tls_set_online_pps(g_answer16);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_online_pps());
                        bsl::ut_check(sys.bf_tls_online_pps() == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_create_vm failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.set_bf_vm_op_create_vm(bf_uint16_t::zero(true));
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.bf_vm_op_create_vm());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_create_vm success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.set_bf_vm_op_create_vm(g_answer16);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_vm_op_create_vm() == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_destroy_vm invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(!sys.bf_vm_op_destroy_vm(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_destroy_vm failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_when{} = [&sys, &arg0]() {
                    sys.set_bf_vm_op_destroy_vm(arg0, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vm_op_destroy_vm(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vm_op_destroy_vm success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(sys.bf_vm_op_destroy_vm(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint16_t arg1{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vp_op_create_vp(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vp_op_create_vp(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{g_answer16};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vp_op_create_vp(arg0, arg1, bf_uint16_t::zero(true));
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vp_op_create_vp(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_create_vp success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{g_answer16};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vp_op_create_vp(arg0, arg1, g_answer16);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vp_op_create_vp(arg0, arg1) == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_destroy_vp invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(!sys.bf_vp_op_destroy_vp(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_destroy_vp failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_when{} = [&sys, &arg0]() {
                    sys.set_bf_vp_op_destroy_vp(arg0, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vp_op_destroy_vp(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_destroy_vp success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(sys.bf_vp_op_destroy_vp(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint16_t arg1{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vp_op_migrate(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vp_op_migrate(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{g_answer16};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vp_op_migrate(arg0, arg1, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vp_op_migrate(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vp_op_migrate success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(sys.bf_vp_op_migrate(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint16_t arg1{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_create_vps(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_create_vps(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{g_answer16};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_create_vps(arg0, arg1, bf_uint16_t::zero(true));
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_create_vps(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_create_vps success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{g_answer16};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_create_vps(arg0, arg1, g_answer16);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_create_vps(arg0, arg1) == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_destroy_vps invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(!sys.bf_vps_op_destroy_vps(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_destroy_vps failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_when{} = [&sys, &arg0]() {
                    sys.set_bf_vps_op_destroy_vps(arg0, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_destroy_vps(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_destroy_vps success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(sys.bf_vps_op_destroy_vps(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_init_as_root invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(!sys.bf_vps_op_init_as_root(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_init_as_root failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_when{} = [&sys, &arg0]() {
                    sys.set_bf_vps_op_init_as_root(arg0, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_init_as_root(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_init_as_root success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(sys.bf_vps_op_init_as_root(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8 invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_read8(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8 invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_read8(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8 failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read8(arg0, arg1, bf_uint8_t::zero(true));
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read8(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read8 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read8(arg0, arg1, g_answer8);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read8(arg0, arg1) == g_answer8);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16 invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_read16(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16 invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_read16(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16 failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read16(arg0, arg1, bf_uint16_t::zero(true));
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read16(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read16 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read16(arg0, arg1, g_answer16);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read16(arg0, arg1) == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32 invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_read32(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32 invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_read32(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32 failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read32(arg0, arg1, bf_uint32_t::zero(true));
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read32(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read32 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read32(arg0, arg1, g_answer32);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read32(arg0, arg1) == g_answer32);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64 invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_read64(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64 invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_read64(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64 failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read64(arg0, arg1, bf_uint64_t::zero(true));
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read64(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read64 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read64(arg0, arg1, g_answer64);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read64(arg0, arg1) == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bf_uint8_t arg2{g_answer8};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write8(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bf_uint8_t arg2{g_answer8};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write8(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 invalid arg2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint8_t arg2{bf_uint8_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write8(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint8_t arg2{g_answer8};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    sys.set_bf_vps_op_write8(arg0, arg1, arg2, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write8(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write8 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint8_t arg2{g_answer8};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(sys.bf_vps_op_write8(arg0, arg1, arg2));
                    bsl::ut_check(sys.bf_vps_op_read8(arg0, arg1) == arg2);
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bf_uint16_t arg2{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write16(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bf_uint16_t arg2{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write16(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 invalid arg2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint16_t arg2{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write16(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint16_t arg2{g_answer16};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    sys.set_bf_vps_op_write16(arg0, arg1, arg2, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write16(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write16 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint16_t arg2{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(sys.bf_vps_op_write16(arg0, arg1, arg2));
                    bsl::ut_check(sys.bf_vps_op_read16(arg0, arg1) == arg2);
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bf_uint32_t arg2{g_answer32};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write32(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bf_uint32_t arg2{g_answer32};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write32(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 invalid arg2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint32_t arg2{bf_uint32_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write32(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint32_t arg2{g_answer32};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    sys.set_bf_vps_op_write32(arg0, arg1, arg2, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write32(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write32 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint32_t arg2{g_answer32};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(sys.bf_vps_op_write32(arg0, arg1, arg2));
                    bsl::ut_check(sys.bf_vps_op_read32(arg0, arg1) == arg2);
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write64(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write64(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 invalid arg2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint64_t arg2{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write64(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    sys.set_bf_vps_op_write64(arg0, arg1, arg2, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write64(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write64 success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint64_t arg1{g_answer64};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(sys.bf_vps_op_write64(arg0, arg1, arg2));
                    bsl::ut_check(sys.bf_vps_op_read64(arg0, arg1) == arg2);
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_reg_t arg1{};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_vps_op_read_reg(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_reg_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read_reg(arg0, arg1, bf_uint64_t::zero(true));
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_vps_op_read_reg(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_read_reg success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_reg_t arg1{};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_vps_op_read_reg(arg0, arg1, g_answer64);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(sys.bf_vps_op_read_reg(arg0, arg1) == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_reg_t arg1{};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write_reg(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg invalid arg2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_reg_t arg1{};
                bf_uint64_t arg2{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_write_reg(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_reg_t arg1{};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    sys.set_bf_vps_op_write_reg(arg0, arg1, arg2, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_write_reg(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_write_reg success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_reg_t arg1{};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(sys.bf_vps_op_write_reg(arg0, arg1, arg2));
                    bsl::ut_check(sys.bf_vps_op_read_reg(arg0, arg1) == arg2);
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bf_uint16_t arg1{g_answer16};
                bf_uint16_t arg2{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_run(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bf_uint16_t arg2{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_run(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run invalid arg2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{g_answer16};
                bf_uint16_t arg2{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_vps_op_run(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{g_answer16};
                bf_uint16_t arg2{g_answer16};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    sys.set_bf_vps_op_run(arg0, arg1, arg2, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_vps_op_run(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bf_uint16_t arg1{g_answer16};
                bf_uint16_t arg2{g_answer16};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(sys.bf_vps_op_run(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_current failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.set_bf_vps_op_run_current(bsl::errc_failure);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.bf_vps_op_run_current());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_run_current success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(sys.bf_vps_op_run_current());
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(!sys.bf_vps_op_advance_ip(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_when{} = [&sys, &arg0]() {
                    sys.set_bf_vps_op_advance_ip(arg0, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_advance_ip(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(sys.bf_vps_op_advance_ip(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_and_run_current failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.set_bf_vps_op_advance_ip_and_run_current(bsl::errc_failure);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.bf_vps_op_advance_ip_and_run_current());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_advance_ip_and_run_current success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(sys.bf_vps_op_advance_ip_and_run_current());
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_promote invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(!sys.bf_vps_op_promote(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_promote failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_when{} = [&sys, &arg0]() {
                    sys.set_bf_vps_op_promote(arg0, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_promote(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_promote success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(sys.bf_vps_op_promote(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_clear_vps invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(!sys.bf_vps_op_clear_vps(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_clear_vps failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_when{} = [&sys, &arg0]() {
                    sys.set_bf_vps_op_clear_vps(arg0, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_vps_op_clear_vps(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_vps_op_clear_vps success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint16_t arg0{g_answer16};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(sys.bf_vps_op_clear_vps(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{bf_uint32_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_rdmsr(arg0));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{g_answer32};
                bsl::ut_when{} = [&sys, &arg0]() {
                    sys.set_bf_intrinsic_op_rdmsr(arg0, bf_uint64_t::zero(true));
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_rdmsr(arg0));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_rdmsr success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{g_answer32};
                bsl::ut_when{} = [&sys, &arg0]() {
                    sys.set_bf_intrinsic_op_rdmsr(arg0, g_answer64);
                    bsl::ut_then{} = [&sys, &arg0]() {
                        bsl::ut_check(sys.bf_intrinsic_op_rdmsr(arg0) == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{bf_uint32_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_wrmsr(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{g_answer32};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_wrmsr(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{g_answer32};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_intrinsic_op_wrmsr(arg0, arg1, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_wrmsr(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_wrmsr success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint32_t arg0{g_answer32};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(sys.bf_intrinsic_op_wrmsr(arg0, arg1));
                    bsl::ut_check(sys.bf_intrinsic_op_rdmsr(arg0) == arg1);
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_invlpga(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_invlpga(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_intrinsic_op_invlpga(arg0, arg1, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invlpga(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invlpga success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(sys.bf_intrinsic_op_invlpga(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_invept(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint64_t arg1{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_invept(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1]() {
                    sys.set_bf_intrinsic_op_invept(arg0, arg1, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invept(arg0, arg1));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invept success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint64_t arg1{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1]() {
                    bsl::ut_check(sys.bf_intrinsic_op_invept(arg0, arg1));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid invalid arg0"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{bf_uint64_t::zero(true)};
                bf_uint16_t arg1{g_answer16};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid invalid arg1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint16_t arg1{bf_uint16_t::zero(true)};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid invalid arg2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint16_t arg1{g_answer16};
                bf_uint64_t arg2{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(!sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint16_t arg1{g_answer16};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_when{} = [&sys, &arg0, &arg1, &arg2]() {
                    sys.set_bf_intrinsic_op_invvpid(arg0, arg1, arg2, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                        bsl::ut_check(!sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_intrinsic_op_invvpid success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t arg0{g_answer64};
                bf_uint16_t arg1{g_answer16};
                bf_uint64_t arg2{g_answer64};
                bsl::ut_then{} = [&sys, &arg0, &arg1, &arg2]() {
                    bsl::ut_check(sys.bf_intrinsic_op_invvpid(arg0, arg1, arg2));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page invalid phys"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(!sys.bf_mem_op_alloc_page(phys));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bsl::ut_when{} = [&sys, &phys]() {
                    sys.set_bf_mem_op_alloc_page(bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &phys]() {
                        bsl::ut_check(!sys.bf_mem_op_alloc_page(phys));
                        bsl::ut_check(!sys.bf_mem_op_alloc_page());
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_page success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                void *ptr{};
                bsl::ut_when{} = [&sys, &phys, &ptr]() {
                    ptr = sys.bf_mem_op_alloc_page(phys);
                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(ptr != nullptr);
                        bsl::ut_check(sys.bf_mem_op_free_page(ptr));
                    };
                };

                bsl::ut_when{} = [&sys, &ptr]() {
                    ptr = sys.bf_mem_op_alloc_page();
                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(ptr != nullptr);
                        bsl::ut_check(sys.bf_mem_op_free_page(ptr));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_page invalid ptr"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                void *ptr{};
                bsl::ut_then{} = [&sys, &ptr]() {
                    bsl::ut_check(!sys.bf_mem_op_free_page(ptr));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_page failure/success/failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                void *ptr{};
                bsl::ut_when{} = [&sys, &ptr]() {
                    ptr = sys.bf_mem_op_alloc_page();
                    sys.set_bf_mem_op_free_page(bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(!sys.bf_mem_op_free_page(ptr));
                    };

                    sys.set_bf_mem_op_free_page(bsl::errc_success);
                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(sys.bf_mem_op_free_page(ptr));
                    };

                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(!sys.bf_mem_op_free_page(ptr));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge invalid size"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t size{bf_uint64_t::zero(true)};
                bf_uint64_t phys{};
                bsl::ut_then{} = [&sys, &size, &phys]() {
                    bsl::ut_check(!sys.bf_mem_op_alloc_huge(size, phys));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge invalid phys"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t size{g_answer64};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &size, &phys]() {
                    bsl::ut_check(!sys.bf_mem_op_alloc_huge(size, phys));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t size{g_answer64};
                bf_uint64_t phys{};
                bsl::ut_when{} = [&sys, &size, &phys]() {
                    sys.set_bf_mem_op_alloc_huge(bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &size, &phys]() {
                        bsl::ut_check(!sys.bf_mem_op_alloc_huge(size, phys));
                        bsl::ut_check(!sys.bf_mem_op_alloc_huge(size));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_alloc_huge success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t size{g_answer64};
                bf_uint64_t phys{};
                void *ptr{};
                bsl::ut_when{} = [&sys, &size, &phys, &ptr]() {
                    ptr = sys.bf_mem_op_alloc_huge(size, phys);
                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(ptr != nullptr);
                        bsl::ut_check(sys.bf_mem_op_free_huge(ptr));
                    };
                };

                bsl::ut_when{} = [&sys, &size, &ptr]() {
                    ptr = sys.bf_mem_op_alloc_huge(size);
                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(ptr != nullptr);
                        bsl::ut_check(sys.bf_mem_op_free_huge(ptr));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_huge invalid ptr"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                void *ptr{};
                bsl::ut_then{} = [&sys, &ptr]() {
                    bsl::ut_check(!sys.bf_mem_op_free_huge(ptr));
                };
            };
        };

        bsl::ut_scenario{"bf_mem_op_free_huge failure/success/failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t size{g_answer64};
                void *ptr{};
                bsl::ut_when{} = [&sys, &size, &ptr]() {
                    ptr = sys.bf_mem_op_alloc_huge(size);
                    sys.set_bf_mem_op_free_huge(bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(!sys.bf_mem_op_free_huge(ptr));
                    };

                    sys.set_bf_mem_op_free_huge(bsl::errc_success);
                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(sys.bf_mem_op_free_huge(ptr));
                    };

                    bsl::ut_then{} = [&sys, &ptr]() {
                        bsl::ut_check(!sys.bf_mem_op_free_huge(ptr));
                    };
                };
            };
        };

        bsl::ut_scenario{"quiet bf_mem_op_alloc_heap"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(sys.bf_mem_op_alloc_heap(g_answer64) == nullptr);
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys invalid phys #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(!sys.bf_read_phys<bsl::uint8>(phys));
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys invalid phys #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(!sys.bf_read_phys<bsl::uint8>(phys));
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bsl::ut_when{} = [&sys, &phys]() {
                    sys.set_bf_read_phys(phys, bf_uint8_t::zero(true));
                    bsl::ut_then{} = [&sys, &phys]() {
                        bsl::ut_check(!sys.bf_read_phys<bsl::uint8>(phys));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bsl::ut_when{} = [&sys, &phys]() {
                    sys.set_bf_read_phys(phys, g_answer8);
                    bsl::ut_then{} = [&sys, &phys]() {
                        bsl::ut_check(sys.bf_read_phys<bsl::uint8>(phys) == g_answer8);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys invalid phys #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(!sys.bf_read_phys<bsl::uint16>(phys));
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys invalid phys #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(!sys.bf_read_phys<bsl::uint16>(phys));
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bsl::ut_when{} = [&sys, &phys]() {
                    sys.set_bf_read_phys(phys, bf_uint16_t::zero(true));
                    bsl::ut_then{} = [&sys, &phys]() {
                        bsl::ut_check(!sys.bf_read_phys<bsl::uint16>(phys));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bsl::ut_when{} = [&sys, &phys]() {
                    sys.set_bf_read_phys(phys, g_answer16);
                    bsl::ut_then{} = [&sys, &phys]() {
                        bsl::ut_check(sys.bf_read_phys<bsl::uint16>(phys) == g_answer16);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys invalid phys #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(!sys.bf_read_phys<bsl::uint32>(phys));
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys invalid phys #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(!sys.bf_read_phys<bsl::uint32>(phys));
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bsl::ut_when{} = [&sys, &phys]() {
                    sys.set_bf_read_phys(phys, bf_uint32_t::zero(true));
                    bsl::ut_then{} = [&sys, &phys]() {
                        bsl::ut_check(!sys.bf_read_phys<bsl::uint32>(phys));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bsl::ut_when{} = [&sys, &phys]() {
                    sys.set_bf_read_phys(phys, g_answer32);
                    bsl::ut_then{} = [&sys, &phys]() {
                        bsl::ut_check(sys.bf_read_phys<bsl::uint32>(phys) == g_answer32);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys invalid phys #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(!sys.bf_read_phys<bsl::uint64>(phys));
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys invalid phys #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(!sys.bf_read_phys<bsl::uint64>(phys));
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bsl::ut_when{} = [&sys, &phys]() {
                    sys.set_bf_read_phys(phys, bf_uint64_t::zero(true));
                    bsl::ut_then{} = [&sys, &phys]() {
                        bsl::ut_check(!sys.bf_read_phys<bsl::uint64>(phys));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_read_phys success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bsl::ut_when{} = [&sys, &phys]() {
                    sys.set_bf_read_phys(phys, g_answer64);
                    bsl::ut_then{} = [&sys, &phys]() {
                        bsl::ut_check(sys.bf_read_phys<bsl::uint64>(phys) == g_answer64);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid phys #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bf_uint8_t val{g_answer8};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid phys #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bf_uint8_t val{g_answer8};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid val"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint8_t val{bf_uint8_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint8_t val{g_answer8};
                bsl::ut_when{} = [&sys, &phys, &val]() {
                    sys.set_bf_write_phys(phys, val, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &phys, &val]() {
                        bsl::ut_check(!sys.bf_write_phys(phys, val));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint8_t val{g_answer8};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(sys.bf_write_phys(phys, val));
                    bsl::ut_check(sys.bf_read_phys<bsl::uint8>(phys) == g_answer8);
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid phys #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bf_uint16_t val{g_answer16};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid phys #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bf_uint16_t val{g_answer16};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid val"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint16_t val{bf_uint16_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint16_t val{g_answer16};
                bsl::ut_when{} = [&sys, &phys, &val]() {
                    sys.set_bf_write_phys(phys, val, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &phys, &val]() {
                        bsl::ut_check(!sys.bf_write_phys(phys, val));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint16_t val{g_answer16};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(sys.bf_write_phys(phys, val));
                    bsl::ut_check(sys.bf_read_phys<bsl::uint16>(phys) == g_answer16);
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid phys #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bf_uint32_t val{g_answer32};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid phys #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bf_uint32_t val{g_answer32};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid val"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint32_t val{bf_uint32_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint32_t val{g_answer32};
                bsl::ut_when{} = [&sys, &phys, &val]() {
                    sys.set_bf_write_phys(phys, val, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &phys, &val]() {
                        bsl::ut_check(!sys.bf_write_phys(phys, val));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint32_t val{g_answer32};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(sys.bf_write_phys(phys, val));
                    bsl::ut_check(sys.bf_read_phys<bsl::uint32>(phys) == g_answer32);
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid phys #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bf_uint64_t val{g_answer64};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid phys #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bf_uint64_t val{g_answer64};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys invalid val"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint64_t val{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(!sys.bf_write_phys(phys, val));
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys failure"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint64_t val{g_answer64};
                bsl::ut_when{} = [&sys, &phys, &val]() {
                    sys.set_bf_write_phys(phys, val, bsl::errc_failure);
                    bsl::ut_then{} = [&sys, &phys, &val]() {
                        bsl::ut_check(!sys.bf_write_phys(phys, val));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_write_phys success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{g_answer64};
                bf_uint64_t val{g_answer64};
                bsl::ut_then{} = [&sys, &phys, &val]() {
                    bsl::ut_check(sys.bf_write_phys(phys, val));
                    bsl::ut_check(sys.bf_read_phys<bsl::uint64>(phys) == g_answer64);
                };
            };
        };

        bsl::ut_scenario{"bf_virt_to_phys invalid virt"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                void *virt{};
                bsl::ut_then{} = [&sys, &virt]() {
                    bsl::ut_check(!sys.bf_virt_to_phys(virt));
                };
            };
        };

        bsl::ut_scenario{"bf_virt_to_phys success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                void *virt{};
                bsl::ut_when{} = [&sys, &virt]() {
                    virt = sys.bf_mem_op_alloc_page();
                    bsl::ut_then{} = [&sys, &virt]() {
                        bsl::ut_check(sys.bf_virt_to_phys(virt));
                        bsl::ut_check(sys.bf_mem_op_free_page(virt));
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_phys_to_virt invalid phys #1"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{bf_uint64_t::zero(true)};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(sys.bf_phys_to_virt(phys) == nullptr);
                };
            };
        };

        bsl::ut_scenario{"bf_phys_to_virt invalid phys #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bf_uint64_t phys{};
                bsl::ut_then{} = [&sys, &phys]() {
                    bsl::ut_check(sys.bf_phys_to_virt(phys) == nullptr);
                };
            };
        };

        bsl::ut_scenario{"bf_phys_to_virt success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                void *virt{};
                bf_uint64_t phys{};
                bsl::ut_when{} = [&sys, &virt, &phys]() {
                    virt = sys.bf_mem_op_alloc_page(phys);
                    bsl::ut_then{} = [&sys, &virt, &phys]() {
                        bsl::ut_check(sys.bf_phys_to_virt(phys) == virt);
                        bsl::ut_check(sys.bf_mem_op_free_page(virt));
                    };
                };
            };
        };

        return bsl::ut_success();
    }
}

/// <!-- description -->
///   @brief Main function for this unit test. If a call to bsl::ut_check() fails
///     the application will fast fail. If all calls to bsl::ut_check() pass, this
///     function will successfully return with bsl::exit_success.
///
/// <!-- inputs/outputs -->
///   @return Always returns bsl::exit_success.
///
[[nodiscard]] auto
main() noexcept -> bsl::exit_code
{
    bsl::enable_color();

    static_assert(syscall::tests() == bsl::ut_success());
    return syscall::tests();
}
