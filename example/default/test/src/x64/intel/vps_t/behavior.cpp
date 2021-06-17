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

#include "../../../../../src/x64/intel/vps_t.hpp"

#include <bsl/ut.hpp>

namespace example
{
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
        bsl::ut_scenario{"initialize twice fails"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.initialize(gs, tls, sys, intrinsic, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"initialize invalid id #1"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_check(
                        !vps.initialize(gs, tls, sys, intrinsic, bsl::safe_uint16::zero(true)));
                };
            };
        };

        bsl::ut_scenario{"initialize invalid id #2"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_check(!vps.initialize(gs, tls, sys, intrinsic, syscall::BF_INVALID_ID));
                };
            };
        };

        bsl::ut_scenario{"initialize bf_mem_op_alloc_page fails"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    sys.set_bf_mem_op_alloc_page(bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.initialize(gs, tls, sys, intrinsic, {}));
                    };
                };
            };
        };

        bsl::ut_scenario{"initialize success"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(vps.initialize(gs, tls, sys, intrinsic, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"release executes without initialize"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"release executes with initialize"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        vps.release(gs, tls, sys, intrinsic);
                    };
                };
            };
        };

        bsl::ut_scenario{"allocate not initialized"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                };
            };
        };

        bsl::ut_scenario{"allocate already allocated"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    bsl::ut_required_step(vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate invalid vpid #1"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(
                            gs, tls, sys, intrinsic, bsl::safe_uint16::zero(true), {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate invalid vpid #2"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(
                            !vps.allocate(gs, tls, sys, intrinsic, syscall::BF_INVALID_ID, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate invalid ppid #1"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(
                            gs, tls, sys, intrinsic, {}, bsl::safe_uint16::zero(true)));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate invalid ppid #2"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(
                            !vps.allocate(gs, tls, sys, intrinsic, {}, syscall::BF_INVALID_ID));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vps_op_init_as_root fails"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_vps_op_init_as_root({}, bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate when ppid does not match vpsid"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto ppid{bsl::to_u16(42)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &ppid]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic, &ppid]() {
                        bsl::ut_check(vps.allocate(gs, tls, sys, intrinsic, {}, ppid));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vps_op_write16 fails for vpid"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto idx{bsl::to_u64(0x0000U)};
                constexpr auto val{bsl::to_u16(0x1)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &idx, &val]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_vps_op_write16({}, idx, val, bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vps_op_write64 fails for link ptr"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto idx{bsl::to_u64(0x2800U)};
                constexpr auto val{bsl::to_u64(0xFFFFFFFFFFFFFFFFU)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &idx, &val]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_vps_op_write64({}, idx, val, bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_intrinsic_op_rdmsr fails for pin ctls"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto msr{bsl::to_u32(0x48DU)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, bsl::safe_uint64::zero(true));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vps_op_write32 fails for pin ctls"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto idx{bsl::to_u64(0x4000U)};
                constexpr auto val{bsl::to_u32(0x0)};
                constexpr auto msr{bsl::to_u32(0x48DU)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &idx, &val, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, {});
                    sys.set_bf_vps_op_write32({}, idx, val, bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_intrinsic_op_rdmsr fails for proc ctls"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto msr{bsl::to_u32(0x48EU)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, bsl::safe_uint64::zero(true));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vps_op_write32 fails for proc ctls"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto idx{bsl::to_u64(0x4002U)};
                constexpr auto val{bsl::to_u32(0x0)};
                constexpr auto msr{bsl::to_u32(0x48EU)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &idx, &val, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, {});
                    sys.set_bf_vps_op_write32({}, idx, val, bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_intrinsic_op_rdmsr fails for exit ctls"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto msr{bsl::to_u32(0x48FU)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, bsl::safe_uint64::zero(true));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vps_op_write32 fails for exit ctls"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto idx{bsl::to_u64(0x400CU)};
                constexpr auto val{bsl::to_u32(0x0)};
                constexpr auto msr{bsl::to_u32(0x48FU)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &idx, &val, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, {});
                    sys.set_bf_vps_op_write32({}, idx, val, bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_intrinsic_op_rdmsr fails for entry ctls"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto msr{bsl::to_u32(0x490U)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, bsl::safe_uint64::zero(true));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vps_op_write32 fails for entry ctls"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto idx{bsl::to_u64(0x4012U)};
                constexpr auto val{bsl::to_u32(0x0)};
                constexpr auto msr{bsl::to_u32(0x490U)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &idx, &val, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, {});
                    sys.set_bf_vps_op_write32({}, idx, val, bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_intrinsic_op_rdmsr fails for proc ctls2"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto msr{bsl::to_u32(0x48BU)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, bsl::safe_uint64::zero(true));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vps_op_write32 fails for proc ctls2"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto idx{bsl::to_u64(0x401EU)};
                constexpr auto val{bsl::to_u32(0x0)};
                constexpr auto msr{bsl::to_u32(0x48BU)};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &idx, &val, &msr]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_intrinsic_op_rdmsr(msr, {});
                    sys.set_bf_vps_op_write32({}, idx, val, bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate bf_vps_op_write64 fails for msr bitmap"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                constexpr auto idx{bsl::to_u64(0x2004U)};
                constexpr auto val{bsl::to_u64(0x1000)};

                /// NOTE:
                /// - The val above is the physical address of the msr bitmaps.
                ///   The mocked syscall library will always return a physical
                ///   address that is 0x1000 * the allocation number. Since we
                ///   only allocated one thing which is the msr_bitmap, the
                ///   physical address of the msr_bitmap must be 0x1000.
                ///

                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic, &idx, &val]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    sys.set_bf_vps_op_write64({}, idx, val, bsl::errc_failure);
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(!vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
                };
            };
        };

        bsl::ut_scenario{"allocate success"} = []() {
            bsl::ut_given{} = []() {
                vps_t vps{};
                gs_t gs{};
                tls_t tls{};
                syscall::bf_syscall_t sys{};
                intrinsic_t intrinsic{};
                bsl::ut_when{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                    bsl::ut_required_step(vps.initialize(gs, tls, sys, intrinsic, {}));
                    bsl::ut_then{} = [&vps, &gs, &tls, &sys, &intrinsic]() {
                        bsl::ut_check(vps.allocate(gs, tls, sys, intrinsic, {}, {}));
                    };
                    vps.release(gs, tls, sys, intrinsic);
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

    static_assert(example::tests() == bsl::ut_success());
    return example::tests();
}
