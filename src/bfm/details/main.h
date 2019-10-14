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

#ifndef BFM_DETAILS_PARSE_H
#define BFM_DETAILS_PARSE_H

#include <file/file.h>
#include <ioctl/ioctl_controller.h>
#include <ioctl/ioctl_debug.h>

#include <argparse/argparse.hpp>

namespace host::details
{

template<
    typename FILE,
    typename IOCTL_CONTROLLER,
    typename IOCTL_DEBUG
    >
class main
{
    interface::ioctl_controller<IOCTL_CONTROLLER> m_ioctl_controller{};
    interface::ioctl_debug<IOCTL_DEBUG> m_ioctl_debug{};

    argparse::ArgumentParser m_bfm{};

public:
    auto execute(
        int argc, const char *argv[])
    -> int
    {
        this->parse_args(argc, argv);
        this->dispatch();

        return EXIT_SUCCESS;
    }

private:
    auto parse_args(
        int argc, const char *argv[])
    -> void
    {
        m_bfm = {"bfm"};

        m_bfm.add_argument("-l","--load")
            .help("load a VMM into the kernel");

        m_bfm.add_argument("-u", "--unload")
            .default_value(false)
            .implicit_value(true)
            .help("unload a previously loaded VMM");

        m_bfm.add_argument("-x", "--start")
            .default_value(false)
            .implicit_value(true)
            .help("start a previously loaded VMM");

        m_bfm.add_argument("-s", "--stop")
            .default_value(false)
            .implicit_value(true)
            .help("stop a previously started VMM");

        m_bfm.add_argument("-d", "--dump")
            .default_value(false)
            .implicit_value(true)
            .help("output the contents of the VMM's debug buffer");

        m_bfm.add_argument("-m", "--mem")
            .default_value(64ULL)
            .action([](const std::string& val) { return std::stoull(val); })
            .help("memory in MB to give the VMM when loading");

        m_bfm.parse_args(argc, const_cast<char**>(argv));
    }

    auto dispatch()
    -> void
    {
        if (!m_bfm.get<std::string>("--load").empty()) {
            m_ioctl_controller.load_vmm(
                FILE::read(m_bfm.get<std::string>("--load")),
                m_bfm.get<unsigned long long>("--mem")
            );

            return;
        }

        if (m_bfm.get<bool>("--unload")) {
            m_ioctl_controller.unload_vmm();
            return;
        }

        if (m_bfm.get<bool>("--start")) {
            m_ioctl_controller.start_vmm();
            return;
        }

        if (m_bfm.get<bool>("--stop")) {
            m_ioctl_controller.stop_vmm();
            return;
        }

        if (m_bfm.get<bool>("--dump")) {
            std::cout << m_ioctl_debug.dump_vmm() << '\n';
            return;
        }
    }
};

}

#endif
