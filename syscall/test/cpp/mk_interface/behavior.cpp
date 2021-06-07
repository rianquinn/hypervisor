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

#include <mk_interface.hpp>

#include <bsl/ut.hpp>

namespace mk
{
    /// @brief stores the expected 16bit return value
    constexpr bsl::safe_uint16 EXPECTED_16BIT_RET{bsl::to_u16(42)};
    /// @brief stores the expected 64bit return value
    constexpr bsl::safe_uint64 EXPECTED_64BIT_RET{bsl::to_umax(42)};
    /// @brief stores the resulting 64bit return value
    bsl::safe_uint64 g_resulting_64bit_ret{};

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_rax.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rax_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_rax.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_rax_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_rbx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rbx_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_rbx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_rbx_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_rcx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rcx_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_rcx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_rcx_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_rdx.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rdx_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_rdx.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_rdx_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_rbp.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rbp_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_rbp.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_rbp_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_rsi.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rsi_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_rsi.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_rsi_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_rdi.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_rdi_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_rdi.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_rdi_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_r8.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r8_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_r8.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_r8_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_r9.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r9_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_r9.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_r9_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_r10.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r10_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_r10.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_r10_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_r11.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r11_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_r11.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_r11_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_r12.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r12_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_r12.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_r12_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_r13.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r13_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_r13.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_r13_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_r14.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r14_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_r14.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_r14_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_r15.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_64BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_r15_impl() noexcept -> syscall::bf_uint64_t
    {
        return EXPECTED_64BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_set_r15.
    ///
    /// <!-- inputs/outputs -->
    ///   @param val The value to set g_resulting_64bit_ret to
    ///
    extern "C" void
    bf_tls_set_r15_impl(syscall::bf_uint64_t const val) noexcept
    {
        g_resulting_64bit_ret = val;
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_extid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_16BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_extid_impl() noexcept -> syscall::bf_uint16_t
    {
        return EXPECTED_16BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_vmid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_16BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_vmid_impl() noexcept -> syscall::bf_uint16_t
    {
        return EXPECTED_16BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_vpid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_16BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_vpid_impl() noexcept -> syscall::bf_uint16_t
    {
        return EXPECTED_16BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_vpsid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_16BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_vpsid_impl() noexcept -> syscall::bf_uint16_t
    {
        return EXPECTED_16BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_ppid.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_16BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_ppid_impl() noexcept -> syscall::bf_uint16_t
    {
        return EXPECTED_16BIT_RET.get();
    }

    /// <!-- description -->
    ///   @brief Implements the test ABI for bf_tls_online_pps.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Returns EXPECTED_16BIT_RET
    ///
    extern "C" [[nodiscard]] auto
    bf_tls_online_pps_impl() noexcept -> syscall::bf_uint16_t
    {
        return EXPECTED_16BIT_RET.get();
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
        bsl::ut_scenario{"bf_syscall_sig"} = []() {
            bsl::ut_given{} = []() {
                constexpr bsl::safe_uint64 syscall_val{bsl::to_u64(0x4242424242424242)};
                constexpr bsl::safe_uint64 expected_syscall_sig{bsl::to_u64(0x4242000000000000)};
                bsl::ut_then{} = [&syscall_val, &expected_syscall_sig]() {
                    bsl::ut_check(syscall::bf_syscall_sig(syscall_val) == expected_syscall_sig);
                };
            };
        };

        bsl::ut_scenario{"bf_syscall_flags"} = []() {
            bsl::ut_given{} = []() {
                constexpr bsl::safe_uint64 syscall_val{bsl::to_u64(0x4242424242424242)};
                constexpr bsl::safe_uint64 expected_syscall_sig{bsl::to_u64(0x0000424200000000)};
                bsl::ut_then{} = [&syscall_val, &expected_syscall_sig]() {
                    bsl::ut_check(syscall::bf_syscall_flags(syscall_val) == expected_syscall_sig);
                };
            };
        };

        bsl::ut_scenario{"bf_syscall_opcode"} = []() {
            bsl::ut_given{} = []() {
                constexpr bsl::safe_uint64 syscall_val{bsl::to_u64(0x4242424242424242)};
                constexpr bsl::safe_uint64 expected_syscall_sig{bsl::to_u64(0x4242000042420000)};
                bsl::ut_then{} = [&syscall_val, &expected_syscall_sig]() {
                    bsl::ut_check(syscall::bf_syscall_opcode(syscall_val) == expected_syscall_sig);
                };
            };
        };

        bsl::ut_scenario{"bf_syscall_opcode_nosig"} = []() {
            bsl::ut_given{} = []() {
                constexpr bsl::safe_uint64 syscall_val{bsl::to_u64(0x4242424242424242)};
                constexpr bsl::safe_uint64 expected_syscall_sig{bsl::to_u64(0x0000000042420000)};
                bsl::ut_then{} = [&syscall_val, &expected_syscall_sig]() {
                    bsl::ut_check(
                        syscall::bf_syscall_opcode_nosig(syscall_val) == expected_syscall_sig);
                };
            };
        };

        bsl::ut_scenario{"bf_syscall_index"} = []() {
            bsl::ut_given{} = []() {
                constexpr bsl::safe_uint64 syscall_val{bsl::to_u64(0x4242424242424242)};
                constexpr bsl::safe_uint64 expected_syscall_sig{bsl::to_u64(0x0000000000004242)};
                bsl::ut_then{} = [&syscall_val, &expected_syscall_sig]() {
                    bsl::ut_check(syscall::bf_syscall_index(syscall_val) == expected_syscall_sig);
                };
            };
        };

        bsl::ut_scenario{"bf_is_spec1_supported failure"} = []() {
            bsl::ut_given{} = []() {
                constexpr bsl::safe_uint32 version{~bsl::to_u32(syscall::BF_SPEC_ID1_MASK)};
                bsl::ut_then{} = [&version]() {
                    bsl::ut_check(!syscall::bf_is_spec1_supported(version));
                };
            };
        };

        bsl::ut_scenario{"bf_is_spec1_supported success"} = []() {
            bsl::ut_given{} = []() {
                constexpr bsl::safe_uint32 version{bsl::to_u32(syscall::BF_SPEC_ID1_MASK)};
                bsl::ut_then{} = [&version]() {
                    bsl::ut_check(syscall::bf_is_spec1_supported(version));
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rax"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_rax(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_rax"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_rax(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbx"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_rbx(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_rbx"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_rbx(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rcx"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_rcx(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_rcx"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_rcx(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdx"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_rdx(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_rdx"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_rdx(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rbp"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_rbp(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_rbp"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_rbp(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rsi"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_rsi(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_rsi"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_rsi(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_rdi"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_rdi(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_rdi"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_rdi(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r8"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_r8(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_r8"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_r8(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r9"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_r9(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_r9"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_r9(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r10"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_r10(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_r10"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_r10(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r11"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_r11(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_r11"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_r11(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r12"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_r12(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_r12"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_r12(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r13"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_r13(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_r13"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_r13(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r14"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_r14(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_r14"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_r14(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_r15"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_r15(hndl) == EXPECTED_64BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_set_r15"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_when{} = [&hndl]() {
                    g_resulting_64bit_ret = {};
                    syscall::bf_tls_set_r15(hndl, EXPECTED_64BIT_RET.get());
                    bsl::ut_then{} = []() {
                        bsl::ut_check(EXPECTED_64BIT_RET == g_resulting_64bit_ret);
                    };
                };
            };
        };

        bsl::ut_scenario{"bf_tls_extid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_extid(hndl) == EXPECTED_16BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vmid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_vmid(hndl) == EXPECTED_16BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_vpid(hndl) == EXPECTED_16BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_vpsid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_vpsid(hndl) == EXPECTED_16BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_ppid"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_ppid(hndl) == EXPECTED_16BIT_RET);
                };
            };
        };

        bsl::ut_scenario{"bf_tls_online_pps"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                syscall::bf_handle_t hndl{};
                bsl::ut_then{} = [&hndl]() {
                    bsl::ut_check(syscall::bf_tls_online_pps(hndl) == EXPECTED_16BIT_RET);
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

    static_assert(mk::tests() == bsl::ut_success());
    return mk::tests();
}
