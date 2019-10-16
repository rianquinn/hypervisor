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

#include <file/details/file.h>
using namespace host;

TEST_CASE("empty filename")
{
    CHECK_THROWS(file<details::file>::read({}));
}

TEST_CASE("file doesn't exist")
{
    CHECK_THROWS(file<details::file>::read("not_a_real_file"));
}

TEST_CASE("Read succeeds")
{
    std::string msg = "The answer is: 42";
    if (auto strm = std::ofstream("test.txt")) {
        strm << msg;
    }

    auto res = file<details::file>::read("test.txt");
    for (size_t i = 0; i < res.size(); i++) {
        CHECK(res.at(i) == msg.at(i));
    }
}
