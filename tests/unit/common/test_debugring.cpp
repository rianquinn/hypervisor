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
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <catch2/catch.hpp>
#include <common/details/debugring.h>

TEST_CASE("empty debugring")
{
    debug_ring_t dr{};
    CHECK(debugring_to_string(dr).empty());
}

TEST_CASE("single string without changing size")
{
    debug_ring_t dr{};
    auto view = gsl::span(dr.buf);

    view[0] = '4';
    view[1] = '2';

    CHECK(debugring_to_string(dr).empty());
}

TEST_CASE("single string")
{
    debug_ring_t dr{};
    auto view = gsl::span(dr.buf);

    view[0] = '4';
    view[1] = '2';
    dr.epos = 2;    // NOLINT

    CHECK(debugring_to_string(dr) == "42");
}

TEST_CASE("multiple strings")
{
    debug_ring_t dr{};
    auto view = gsl::span(dr.buf);

    view[0] = '4';
    view[1] = '2';
    view[2] = '\n';
    view[3] = '4';
    view[4] = '2';
    dr.epos = 5;    // NOLINT

    CHECK(debugring_to_string(dr) == "42\n42");
}

TEST_CASE("wrapping string v1")
{
    debug_ring_t dr{};
    auto view = gsl::span(dr.buf);

    view[BAREFLANK_DEBUGRING_SIZE - 1] = '4';
    view[0] = '2';
    dr.spos = BAREFLANK_DEBUGRING_SIZE - 1;    // NOLINT
    dr.epos = 1;                               // NOLINT

    CHECK(debugring_to_string(dr) == "42");
}

TEST_CASE("wrapping string v2")
{
    debug_ring_t dr{};
    auto view = gsl::span(dr.buf);

    view[BAREFLANK_DEBUGRING_SIZE - 2] = '4';
    view[BAREFLANK_DEBUGRING_SIZE - 1] = '2';
    dr.spos = BAREFLANK_DEBUGRING_SIZE - 2;    // NOLINT
    dr.epos = 0;                               // NOLINT

    CHECK(debugring_to_string(dr) == "42");
}
