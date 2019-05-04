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
#include <ioctl_driver.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include <argparse/argparse.hpp>

int
ioctl_driver::process(int argc, char *argv[])
{
    argparse::ArgumentParser bfm("bfm");

    bfm.add_argument("-l","--load")
        .help("load a VMM into the kernel");

    bfm.add_argument("-x", "--start")
        .default_value(false)
        .implicit_value(true)
        .help("start a previously loaded VMM");

    bfm.add_argument("-d", "--dump")
        .default_value(false)
        .implicit_value(true)
        .help("output the contents of the VMM's debug buffer");

    bfm.add_argument("-s", "--stop")
        .default_value(false)
        .implicit_value(true)
        .help("stop a previously started VMM");

    bfm.add_argument("-u", "--unload")
        .default_value(false)
        .implicit_value(true)
        .help("unload a previously loaded VMM");

    bfm.add_argument("-m", "--mem")
        .default_value(64ULL)
        .action([](const std::string& val) { return std::stoull(val); })
        .help("memory in MB to give the VMM when loading");

    bfm.parse_args(argc, argv);

    if (!bfm.get<std::string>("--load").empty()) {
        this->load_vmm(
            bfm.get<std::string>("--load"),
            bfm.get<unsigned long long>("--mem")
        );
    }

    if (bfm.get<bool>("--start")) {
        this->start_vmm();
    }

    if (bfm.get<bool>("--dump")) {
        this->dump_vmm();
    }

    if (bfm.get<bool>("--stop")) {
        this->stop_vmm();
    }

    if (bfm.get<bool>("--unload")) {
        this->unload_vmm();
    }

    return EXIT_SUCCESS;
}

std::string
read_file(const std::string &filename)
{
    if (auto in = std::ifstream(filename, std::ios::binary)) {
        std::stringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }

    throw std::runtime_error("file not found: " + filename);
}

void
ioctl_driver::load_vmm(const std::string &filename, uint64_t mem)
{
    auto contents = read_file(filename);

    ioctl_load_args_t args = {
        reinterpret_cast<uint64_t>(contents.data()), contents.size(), (mem << 20)
    };

    switch (this->get_status()) {
        case VMM_RUNNING: this->stop_vmm(); [[fallthrough]];
        case VMM_LOADED: this->unload_vmm(); [[fallthrough]];
        case VMM_UNLOADED: break;
        case VMM_CORRUPT: throw std::runtime_error("vmm corrupt");
        default: throw std::runtime_error("unknown status");
    }

    try {
        m_ioctl.call_ioctl_load_vmm(&args);
    }
    catch (...) {
        this->unload_vmm();
        throw;
    }
}

void
ioctl_driver::unload_vmm()
{
    switch (this->get_status()) {
        case VMM_RUNNING: this->stop_vmm();
        case VMM_LOADED: break;
        case VMM_UNLOADED: return;
        case VMM_CORRUPT: throw std::runtime_error("vmm corrupt");
        default: throw std::runtime_error("unknown status");
    }

    m_ioctl.call_ioctl_unload_vmm();
}

void
ioctl_driver::start_vmm()
{
    switch (this->get_status()) {
        case VMM_RUNNING: this->stop_vmm();
        case VMM_LOADED: break;
        case VMM_UNLOADED: throw std::runtime_error("vmm must be loaded first");
        case VMM_CORRUPT: throw std::runtime_error("vmm corrupt");
        default: throw std::runtime_error("unknown status");
    }

    m_ioctl.call_ioctl_start_vmm();
}

void
ioctl_driver::stop_vmm()
{
    switch (this->get_status()) {
        case VMM_RUNNING: break;
        case VMM_LOADED: return;
        case VMM_UNLOADED: return;
        case VMM_CORRUPT: throw std::runtime_error("vmm corrupt");
        default: throw std::runtime_error("unknown status");
    }

    m_ioctl.call_ioctl_stop_vmm();
}

void
ioctl_driver::dump_vmm()
{
    debug_ring_resources_t args;
    auto buffer = std::make_unique<char[]>(DEBUG_RING_SIZE);

    switch (this->get_status()) {
        case VMM_RUNNING: break;
        case VMM_LOADED: break;
        case VMM_UNLOADED: throw std::runtime_error("vmm must be loaded first");
        case VMM_CORRUPT: throw std::runtime_error("vmm corrupt");
        default: throw std::runtime_error("unknown status");
    }

    m_ioctl.call_ioctl_dump_vmm(&args);

    if (debug_ring_read(&args, buffer.get(), DEBUG_RING_SIZE) > 0) {
        std::cout << buffer.get();
    }

    std::cout << '\n';
}

status_t
ioctl_driver::get_status() const
{
    status_t status;
    m_ioctl.call_ioctl_vmm_status(&status);

    return status;
}
