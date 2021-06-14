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

#include <bsl/array.hpp>
#include <bsl/as_const.hpp>
#include <bsl/convert.hpp>
#include <bsl/cstdint.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/span.hpp>
#include <bsl/ut.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Provides the prototype for memcpy
    ///
    /// <!-- inputs/outputs -->
    ///   @param dst pointer to the destination array where the content is to
    ///     be copied, type-casted to a pointer of type void*.
    ///   @param src pointer to the source of data to be copied, type-casted to
    ///     a pointer of type const void*.
    ///   @param num number of bytes to copy.
    ///   @return Returns dst
    ///
    extern "C" void *
    ut_memcpy(void *const dst, void const *const src, bsl::uintmax const num) noexcept;

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
        bsl::ut_scenario{"copy an array of size 1"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                constexpr bsl::safe_uintmax size{bsl::to_umax(1)};
                bsl::array<bsl::uint8, size.get()> data_dst{};
                bsl::array<bsl::uint8, size.get()> data_src{};
                bsl::ut_when{} = [&data_dst, &data_src]() {
                    constexpr bsl::safe_uint8 val{bsl::to_u8(42)};
                    for (auto const elem : data_src) {
                        *elem.data = val.get();
                    }
                    ut_memcpy(data_dst.data(), data_src.data(), data_src.size_bytes().get());
                    bsl::ut_then{} = [&data_dst, &val]() {
                        for (auto const elem : bsl::as_const(data_dst)) {
                            bsl::ut_check(*elem.data == val.get());
                        }
                    };
                };
            };
        };

        bsl::ut_scenario{"copy an array of size 15 (unaligned)"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                constexpr bsl::safe_uintmax size{bsl::to_umax(15)};
                bsl::array<bsl::uint8, size.get()> data_dst{};
                bsl::array<bsl::uint8, size.get()> data_src{};
                bsl::ut_when{} = [&data_dst, &data_src]() {
                    constexpr bsl::safe_uint8 val{bsl::to_u8(42)};
                    for (auto const elem : data_src) {
                        *elem.data = val.get();
                    }
                    ut_memcpy(data_dst.data(), data_src.data(), data_src.size_bytes().get());
                    bsl::ut_then{} = [&data_dst, &val]() {
                        for (auto const elem : bsl::as_const(data_dst)) {
                            bsl::ut_check(*elem.data == val.get());
                        }
                    };
                };
            };
        };

        bsl::ut_scenario{"copy an array of size 16 (aligned)"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                constexpr bsl::safe_uintmax size{bsl::to_umax(16)};
                bsl::array<bsl::uint8, size.get()> data_dst{};
                bsl::array<bsl::uint8, size.get()> data_src{};
                bsl::ut_when{} = [&data_dst, &data_src]() {
                    constexpr bsl::safe_uint8 val{bsl::to_u8(42)};
                    for (auto const elem : data_src) {
                        *elem.data = val.get();
                    }
                    ut_memcpy(data_dst.data(), data_src.data(), data_src.size_bytes().get());
                    bsl::ut_then{} = [&data_dst, &val]() {
                        for (auto const elem : bsl::as_const(data_dst)) {
                            bsl::ut_check(*elem.data == val.get());
                        }
                    };
                };
            };
        };

        bsl::ut_scenario{"copy an array of size 31 (unaligned)"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                constexpr bsl::safe_uintmax size{bsl::to_umax(31)};
                bsl::array<bsl::uint8, size.get()> data_dst{};
                bsl::array<bsl::uint8, size.get()> data_src{};
                bsl::ut_when{} = [&data_dst, &data_src]() {
                    constexpr bsl::safe_uint8 val{bsl::to_u8(42)};
                    for (auto const elem : data_src) {
                        *elem.data = val.get();
                    }
                    ut_memcpy(data_dst.data(), data_src.data(), data_src.size_bytes().get());
                    bsl::ut_then{} = [&data_dst, &val]() {
                        for (auto const elem : bsl::as_const(data_dst)) {
                            bsl::ut_check(*elem.data == val.get());
                        }
                    };
                };
            };
        };

        bsl::ut_scenario{"copy an array of size 32 (aligned)"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                constexpr bsl::safe_uintmax size{bsl::to_umax(32)};
                bsl::array<bsl::uint8, size.get()> data_dst{};
                bsl::array<bsl::uint8, size.get()> data_src{};
                bsl::ut_when{} = [&data_dst, &data_src]() {
                    constexpr bsl::safe_uint8 val{bsl::to_u8(42)};
                    for (auto const elem : data_src) {
                        *elem.data = val.get();
                    }
                    ut_memcpy(data_dst.data(), data_src.data(), data_src.size_bytes().get());
                    bsl::ut_then{} = [&data_dst, &val]() {
                        for (auto const elem : bsl::as_const(data_dst)) {
                            bsl::ut_check(*elem.data == val.get());
                        }
                    };
                };
            };
        };

        bsl::ut_scenario{"copy an array of size 127 (unaligned)"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                constexpr bsl::safe_uintmax size{bsl::to_umax(127)};
                bsl::array<bsl::uint8, size.get()> data_dst{};
                bsl::array<bsl::uint8, size.get()> data_src{};
                bsl::ut_when{} = [&data_dst, &data_src]() {
                    constexpr bsl::safe_uint8 val{bsl::to_u8(42)};
                    for (auto const elem : data_src) {
                        *elem.data = val.get();
                    }
                    ut_memcpy(data_dst.data(), data_src.data(), data_src.size_bytes().get());
                    bsl::ut_then{} = [&data_dst, &val]() {
                        for (auto const elem : bsl::as_const(data_dst)) {
                            bsl::ut_check(*elem.data == val.get());
                        }
                    };
                };
            };
        };

        bsl::ut_scenario{"copy an array of size 128 (aligned)"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                constexpr bsl::safe_uintmax size{bsl::to_umax(128)};
                bsl::array<bsl::uint8, size.get()> data_dst{};
                bsl::array<bsl::uint8, size.get()> data_src{};
                bsl::ut_when{} = [&data_dst, &data_src]() {
                    constexpr bsl::safe_uint8 val{bsl::to_u8(42)};
                    for (auto const elem : data_src) {
                        *elem.data = val.get();
                    }
                    ut_memcpy(data_dst.data(), data_src.data(), data_src.size_bytes().get());
                    bsl::ut_then{} = [&data_dst, &val]() {
                        for (auto const elem : bsl::as_const(data_dst)) {
                            bsl::ut_check(*elem.data == val.get());
                        }
                    };
                };
            };
        };

        bsl::ut_scenario{"copy an array of size 0xFFFFF (unaligned)"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                constexpr bsl::safe_uintmax size{bsl::to_umax(0xFFFFF)};
                bsl::array<bsl::uint8, size.get()> data_dst{};
                bsl::array<bsl::uint8, size.get()> data_src{};
                bsl::ut_when{} = [&data_dst, &data_src]() {
                    constexpr bsl::safe_uint8 val{bsl::to_u8(42)};
                    for (auto const elem : data_src) {
                        *elem.data = val.get();
                    }
                    ut_memcpy(data_dst.data(), data_src.data(), data_src.size_bytes().get());
                    bsl::ut_then{} = [&data_dst, &val]() {
                        for (auto const elem : bsl::as_const(data_dst)) {
                            bsl::ut_check(*elem.data == val.get());
                        }
                    };
                };
            };
        };

        bsl::ut_scenario{"copy an array of size 0x100000 (aligned)"} = []() {
            bsl::ut_given_at_runtime{} = []() {
                constexpr bsl::safe_uintmax size{bsl::to_umax(0x100000)};
                bsl::array<bsl::uint8, size.get()> data_dst{};
                bsl::array<bsl::uint8, size.get()> data_src{};
                bsl::ut_when{} = [&data_dst, &data_src]() {
                    constexpr bsl::safe_uint8 val{bsl::to_u8(42)};
                    for (auto const elem : data_src) {
                        *elem.data = val.get();
                    }
                    ut_memcpy(data_dst.data(), data_src.data(), data_src.size_bytes().get());
                    bsl::ut_then{} = [&data_dst, &val]() {
                        for (auto const elem : bsl::as_const(data_dst)) {
                            bsl::ut_check(*elem.data == val.get());
                        }
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

    static_assert(mk::tests() == bsl::ut_success());
    return mk::tests();
}
