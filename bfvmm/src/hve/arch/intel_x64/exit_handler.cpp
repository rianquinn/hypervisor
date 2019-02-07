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

// TIDY_EXCLUSION=-cppcoreguidelines-pro-type-reinterpret-cast
//
// Reason:
//     Although in general this is a good rule, for hypervisor level code that
//     interfaces with the kernel, and raw hardware, this rule is
//     impractical.
//

#include <bfgsl.h>
#include <bfexception.h>

#include <hve/arch/intel_x64/exit_handler.h>

namespace bfvmm::intel_x64
{

exit_handler::exit_handler(vcpu *vcpu)
{ bfignored(vcpu); }

exit_handler::init(vcpu *vcpu)
{ bfignored(vcpu); }

void
exit_handler::add_handler(
    ::intel_x64::vmcs::value_type reason,
    const handler_delegate_t &d)
{ m_exit_handlers_array.at(reason).push_front(d); }

void
exit_handler::add_exit_handler(
    const handler_delegate_t &d)
{ m_exit_handlers.push_front(d); }

bool
exit_handler::handle(
    vcpu *vcpu, exit_handler *exit_handler)
{
    using namespace ::intel_x64::vmcs;

    guard_exceptions([&]() {

        for (const auto &d : exit_handler->m_exit_handlers) {
            d(vcpu);
        }

        const auto &handlers =
            exit_handler->m_exit_handlers_array.at(
                exit_reason::basic_exit_reason::get()
            );

        for (const auto &d : handlers) {
            if (d(vcpu)) {
                vcpu->run();
            }
        }

        bfdebug_transaction(0, [&](std::string * msg) {
            bferror_lnbr(0, msg);
            bferror_info(0, "unhandled exit reason", msg);
            bferror_brk1(0, msg);

            bferror_subtext(
                0, "exit_reason",
                exit_reason::basic_exit_reason::description(), msg
            );
        });

        if (exit_reason::vm_entry_failure::is_enabled()) {
            debug::dump();
            check::all();
        }
    });

    vcpu->halt();
}

}
