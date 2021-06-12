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
    /// @brief stores the answer to all things
    constexpr bf_uint64_t g_answer{bsl::to_u64(42)};

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
                bf_uint16_t arg0{};
                bsl::ut_then{} = [&arg0]() {
                    bootstrap_entry(arg0.get());
                };
            };
        };

        bsl::ut_scenario{"quiet vmexit_entry"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t arg0{};
                bf_uint64_t arg1{};
                bsl::ut_then{} = [&arg0, &arg1]() {
                    vmexit_entry(arg0.get(), arg1.get());
                };
            };
        };

        bsl::ut_scenario{"quiet fail_entry"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                bf_uint16_t arg0{};
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
                    bsl::ut_check(!sys.initialize(bf_uint32_t::zero(true), &bootstrap_entry, &vmexit_entry, &fail_entry));
                };
            };
        };

        bsl::ut_scenario{"initialize invalid version #2"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(!sys.initialize({}, &bootstrap_entry, &vmexit_entry, &fail_entry));
                };
            };
        };

        bsl::ut_scenario{"initialize invalid bootstrap_handler"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(!sys.initialize(BF_ALL_SPECS_SUPPORTED_VAL, {}, &vmexit_entry, &fail_entry));
                };
            };
        };

        bsl::ut_scenario{"initialize invalid bootstrap_handler"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(!sys.initialize(BF_ALL_SPECS_SUPPORTED_VAL, &bootstrap_entry, {}, &fail_entry));
                };
            };
        };

        bsl::ut_scenario{"initialize invalid bootstrap_handler"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(!sys.initialize(BF_ALL_SPECS_SUPPORTED_VAL, &bootstrap_entry, &vmexit_entry, {}));
                };
            };
        };

        bsl::ut_scenario{"initialize returns alert"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_when{} = [&sys]() {
                    sys.set_initialize(bsl::errc_failure);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(!sys.initialize(BF_ALL_SPECS_SUPPORTED_VAL, &bootstrap_entry, &vmexit_entry, &fail_entry));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize success"} = []() {
            bsl::ut_given{} = []() {
                bf_syscall_t sys{};
                bsl::ut_then{} = [&sys]() {
                    bsl::ut_check(sys.initialize(BF_ALL_SPECS_SUPPORTED_VAL, &bootstrap_entry, &vmexit_entry, &fail_entry));
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
                    sys.bf_tls_set_rax(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rax());
                        bsl::ut_check(sys.bf_tls_rax() == g_answer);
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
                    sys.bf_tls_set_rbx(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rbx());
                        bsl::ut_check(sys.bf_tls_rbx() == g_answer);
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
                    sys.bf_tls_set_rcx(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rcx());
                        bsl::ut_check(sys.bf_tls_rcx() == g_answer);
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
                    sys.bf_tls_set_rdx(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rdx());
                        bsl::ut_check(sys.bf_tls_rdx() == g_answer);
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
                    sys.bf_tls_set_rbp(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rbp());
                        bsl::ut_check(sys.bf_tls_rbp() == g_answer);
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
                    sys.bf_tls_set_rsi(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rsi());
                        bsl::ut_check(sys.bf_tls_rsi() == g_answer);
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
                    sys.bf_tls_set_rdi(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_rdi());
                        bsl::ut_check(sys.bf_tls_rdi() == g_answer);
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
                    sys.bf_tls_set_r8(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r8());
                        bsl::ut_check(sys.bf_tls_r8() == g_answer);
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
                    sys.bf_tls_set_r9(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r9());
                        bsl::ut_check(sys.bf_tls_r9() == g_answer);
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
                    sys.bf_tls_set_r10(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r10());
                        bsl::ut_check(sys.bf_tls_r10() == g_answer);
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
                    sys.bf_tls_set_r11(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r11());
                        bsl::ut_check(sys.bf_tls_r11() == g_answer);
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
                    sys.bf_tls_set_r12(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r12());
                        bsl::ut_check(sys.bf_tls_r12() == g_answer);
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
                    sys.bf_tls_set_r13(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r13());
                        bsl::ut_check(sys.bf_tls_r13() == g_answer);
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
                    sys.bf_tls_set_r14(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r14());
                        bsl::ut_check(sys.bf_tls_r14() == g_answer);
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
                    sys.bf_tls_set_r15(g_answer);
                    bsl::ut_then{} = [&sys]() {
                        bsl::ut_check(sys.bf_tls_r15());
                        bsl::ut_check(sys.bf_tls_r15() == g_answer);
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
