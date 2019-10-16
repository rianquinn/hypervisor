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

#include <file/file.h>
#include <ioctl/ioctl_controller.h>
#include <ioctl/ioctl_debug.h>

#include <bfm/details/main.h>
using namespace host;

// -------------------------------------------------------------------------
// Mocks
// -------------------------------------------------------------------------

#include <vector>
#include <fstream>

std::vector<std::string> g_calls;
auto heap_arg = std::to_string(details::default_heap_size);    // NOLINT

auto
called(size_t i, const std::string &str) -> bool
{
    return g_calls.at(i).find(str) != std::string::npos;
}

class file_mock
{
public:
    static auto
    read(const std::string &filename) -> std::vector<char>
    {
        if (filename != "vmm.bin") {
            g_calls.emplace_back("file::read failure");
            return {};
        }

        g_calls.emplace_back("file::read success");
        return {'4', '2'};
    }
};

class ioctl_controller_mock
{
public:
    auto
    load_vmm(const std::vector<char> &file, size_t heap_size) -> void
    {
        std::vector<char> control{'4', '2'};

        if (file == control && heap_size == details::default_heap_size) {
            g_calls.emplace_back("ioctl_controller::load_vmm success");
            return;
        }

        g_calls.emplace_back("ioctl_controller::load_vmm failure");
    }

    auto
    unload_vmm() -> void
    {
        g_calls.emplace_back("ioctl_controller::unload_vmm success");
    }

    auto
    start_vmm() -> void
    {
        g_calls.emplace_back("ioctl_controller::start_vmm success");
    }

    auto
    stop_vmm() -> void
    {
        g_calls.emplace_back("ioctl_controller::stop_vmm success");
    }
};

class ioctl_debug_mock
{
public:
    auto
    dump_vmm() -> std::string
    {
        g_calls.emplace_back("ioctl_debug::dump_vmm success");
        return "The answer is: 42";
    }
};

using main_t = details::main<
    file<file_mock>,
    ioctl_controller<ioctl_controller_mock>,
    ioctl_debug<ioctl_debug_mock>>;

// -------------------------------------------------------------------------
// Setup
// -------------------------------------------------------------------------

auto
setup_test() -> void
{
    g_calls.clear();

    if (auto strm = std::ofstream("vmm.bin")) {
        strm << "The answer is: 42";
    }
}

// -------------------------------------------------------------------------
// Tests
// -------------------------------------------------------------------------

TEST_CASE("no args")
{
    setup_test();

    main_t m;
    std::array args{"bfm"};

    CHECK_THROWS(m.execute(args.size(), args.data()));
    CHECK(g_calls.empty());
}

TEST_CASE("--help success")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "--help"};

    CHECK(m.execute(args.size(), args.data()) == EXIT_SUCCESS);
    CHECK(g_calls.empty());
}

TEST_CASE("-h success")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "-h"};

    CHECK(m.execute(args.size(), args.data()) == EXIT_SUCCESS);
    CHECK(g_calls.empty());
}

TEST_CASE("--heap without load and no args")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "--heap"};

    CHECK_THROWS(m.execute(args.size(), args.data()));
    CHECK(g_calls.empty());
}

TEST_CASE("-m without load and no args")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "-m"};

    CHECK_THROWS(m.execute(args.size(), args.data()));
    CHECK(g_calls.empty());
}

TEST_CASE("--heap without load")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "--heap", heap_arg.c_str()};

    CHECK_THROWS(m.execute(args.size(), args.data()));
    CHECK(g_calls.empty());
}

TEST_CASE("-m without load")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "-m", heap_arg.c_str()};

    CHECK_THROWS(m.execute(args.size(), args.data()));
    CHECK(g_calls.empty());
}

TEST_CASE("load without filename")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "load"};

    CHECK_THROWS(m.execute(args.size(), args.data()));
    CHECK(g_calls.empty());
}

TEST_CASE("load success")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "load", "vmm.bin"};

    CHECK(m.execute(args.size(), args.data()) == EXIT_SUCCESS);
    CHECK(called(0, "file::read success"));
    CHECK(called(1, "ioctl_controller::load_vmm success"));
}

TEST_CASE("load with --heap and no args")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "load", "vmm.bin", "--heap"};

    CHECK_THROWS(m.execute(args.size(), args.data()));
    CHECK(g_calls.empty());
}

TEST_CASE("load with --heap success")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "load", "vmm.bin", "--heap", heap_arg.c_str()};

    CHECK(m.execute(args.size(), args.data()) == EXIT_SUCCESS);
    CHECK(called(0, "file::read success"));
    CHECK(called(1, "ioctl_controller::load_vmm success"));
}

TEST_CASE("unload success")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "unload"};

    CHECK(m.execute(args.size(), args.data()) == EXIT_SUCCESS);
    CHECK(called(0, "ioctl_controller::unload_vmm success"));
}

TEST_CASE("start success")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "start"};

    CHECK(m.execute(args.size(), args.data()) == EXIT_SUCCESS);
    CHECK(called(0, "ioctl_controller::start_vmm success"));
}

TEST_CASE("stop success")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "stop"};

    CHECK(m.execute(args.size(), args.data()) == EXIT_SUCCESS);
    CHECK(called(0, "ioctl_controller::stop_vmm success"));
}

TEST_CASE("dump success")
{
    setup_test();

    main_t m;
    std::array args{"bfm", "dump"};

    CHECK(m.execute(args.size(), args.data()) == EXIT_SUCCESS);
    CHECK(called(0, "ioctl_debug::dump_vmm success"));
}
