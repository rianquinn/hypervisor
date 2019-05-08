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

#include <bfgsl.h>

#include <implementation/serial.h>
#include <implementation/debug_ring.h>

using namespace bfvmm::implementation;

#include <mutex>
std::mutex g_write_mutex;

extern "C" void
unlock_write(void) noexcept
{ g_write_mutex.unlock(); }

extern "C" int
write_str(const std::string &str) noexcept
{
    try {
        std::lock_guard<std::mutex> guard(g_write_mutex);

        for (const auto &c : str) {
            serial::instance()->write(c);
            debug_ring::instance()->write(c);
        }
    }
    catch (...) {
        return 0;
    }

    return gsl::narrow_cast<int>(str.length());
}

extern "C" void
unsafe_write_cstr(const char *cstr, size_t len) noexcept
{
    try {
        auto str = gsl::span(cstr, gsl::index_cast(len));

        for (const auto &c : str) {
            serial::instance()->write(c);
            debug_ring::instance()->write(c);
        }
    }
    catch (...)
    { }
}

extern "C" int
write(int __fd, const void *__buf, size_t __nbyte)
{
    if (__buf == nullptr || __nbyte == 0) {
        return 0;
    }

    if (__fd != 1 && __fd != 2) {
        return 0;
    }

    return write_str({static_cast<const char *>(__buf), __nbyte});
}
