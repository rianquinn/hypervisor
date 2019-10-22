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

#ifndef BFM_DETAILS_PARSE_H
#define BFM_DETAILS_PARSE_H

#include <file/file.h>
#include <vmmctl/vmm_controller.h>
#include <vmmctl/debug.h>

#include <memory>
#include <iostream>
#include <argagg/argagg.hpp>

namespace vmmctl::details
{
    constexpr auto default_heap_size = 64ULL;

    template<typename FILE, typename VMM_CONTROLLER, typename DEBUG>
    class main
    {
        adheres_to(FILE, interface::file);
        adheres_to(VMM_CONTROLLER, interface::vmm_controller);
        adheres_to(DEBUG, interface::debug);

        argagg::parser m_parser{{
            {"help", {"-h", "--help"}, "shows this help message", 0},
            {"heap", {"-m", "--heap"}, "MB of heap memory to give the VMM", 1},
        }};

    public:
        auto
        execute(int argc, char **argv) -> int
        {
            this->dispatch(m_parser.parse(argc, argv));
            return EXIT_SUCCESS;
        }

        auto
        execute(int argc, const char **argv) -> int
        {
            return this->execute(argc, const_cast<char **>(argv));    // NOLINT
        }

    private:
        auto
        dispatch(const argagg::parser_results &args) -> void
        {
            if (args["help"]) {
                return this->help();
            }

            if (args.pos.empty()) {
                throw std::runtime_error("missing argument \"command\"");
            }

            auto cmd = args.as<std::string>(0);

            if (cmd == "load") {
                if (args.pos.size() != 2) {
                    throw std::runtime_error("invalid arguments for \"load\"");
                }

                auto file = FILE::read(args.as<std::string>(1));
                auto heap = args["heap"].as<uint64_t>(default_heap_size);

                std::make_unique<VMM_CONTROLLER>()->load_vmm(file, heap);
                return;
            }

            if (cmd == "unload") {
                std::make_unique<VMM_CONTROLLER>()->unload_vmm();
                return;
            }

            if (cmd == "start") {
                std::make_unique<VMM_CONTROLLER>()->start_vmm();
                return;
            }

            if (cmd == "stop") {
                std::make_unique<VMM_CONTROLLER>()->stop_vmm();
                return;
            }

            if (cmd == "dump") {
                std::cout << std::make_unique<DEBUG>()->dump_vmm();
                std::cout << '\n';

                return;
            }

            throw std::runtime_error("unknown command \"" + cmd + "\"");
        }

        auto
        help() -> void
        {
            std::cout << "Usage: bfm [OPTION]... load <filename>" << '\n';
            std::cout << "  or:  bfm unload" << '\n';
            std::cout << "  or:  bfm start" << '\n';
            std::cout << "  or:  bfm stop" << '\n';
            std::cout << "  or:  bfm dump" << '\n';
            std::cout << "Controls/Debugs the Bareflank(TM) Hypervisor" << '\n';
            std::cout << '\n';
            std::cout << "Options:" << '\n';
            std::cout << m_parser;
        }
    };

}

#endif
