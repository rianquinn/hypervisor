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

#include <hve/arch/intel_x64/vcpu.h>
#include <hve/arch/intel_x64/implementation/cpuid.h>

namespace bfvmm::intel_x64::implementation
{

exit_handler::exit_handler(
    gsl::not_null<vcpu *> vcpu)
{ bfignored(vcpu); }

void
exit_handler::add(const handler_delegate_t &d)
{ m_exit_handlers.push_front(d); }

void
exit_handler::add_for_reason(
    exit_handler_n::exit_reason_t reason, const handler_delegate_t &d)
{ m_exit_handlers_for_reason.at(reason).push_front(d); }

const exit_handlers_t &
exit_handler::exit_handlers() const noexcept
{ return m_exit_handlers; }

const exit_handlers_t &
exit_handler::exit_handlers_for_reason(
    exit_handler_n::exit_reason_t reason) const noexcept
{ return m_exit_handlers_for_reason.at(reason); }

MOCK_FUNCTION(exit_handler, {
    mocks.OnCall(vcpu->exit_handler_impl().get(), exit_handler::add);
    mocks.OnCall(vcpu->exit_handler_impl().get(), exit_handler::add_for_reason);
    mocks.OnCall(vcpu->exit_handler_impl().get(), exit_handler::exit_handlers).Return(exit_handlers_t{});
    mocks.OnCall(vcpu->exit_handler_impl().get(), exit_handler::exit_handlers_for_reason).Return(exit_handlers_t{});
})

}

// -----------------------------------------------------------------------------
// VMExit Entry Point
// -----------------------------------------------------------------------------

// Notes:
//
// - When a VMExit occurs, the exit_handler_entry function is called inside the
//   exit_handler_entry.asm file. This is the initial entry point. This code
//   saves the vCPU's state into the state structure which is in the
//   implementation/state.h. Once that is done, it calls the handle_exit()
//   function below.
//
// - The handle_exit() has to process two different handler lists. The first
//   list is processed for every VMExit while the second list is processed for
//   a specific VMExit reason. The base hypervisor doesn't use the the first
//   list internally. The first list is for extensions like Boxy that need to
//   do things on every exit (like save/restore vCPU state on world switches)
//
// - We guard the VMExit so that any exceptions that might fire get caught. If
//   this happens the vCPU has to halt(). In this base, this results in the
//   system freezing. If you experience this, the hypervisor will output the
//   reason, you just need to debug the system with a second, external machine
//   with something like serial to get the output. If this is a guest vCPU
//   (for example if you are using Boxy), the guest vCPU will crash and hand
//   control back to the host and a normal "bfm dump" can be used to get the
//   debug output.
//
// - Finally, at least one of the handlers in either list must return true
//   and advance the instruction pointer (when applicable). If all of the
//   handlers return false vcpu->halt() will be called as that means that none
//   of the handlers completely handled the exit. Ideally, the first list always
//   returns false, and the extension's handlers are executed which also return
//   false until finally code from the base hypervisor executes and returns
//   true. All of the base handlers that return true are in the vmexit folder.
//   There are a lot of handlers that still have to be implemented with some
//   sort of general set of APIs, so if you end up with an exit that we are
//   currently not handling, draft and RFC on what you think the general API
//   should look like and lets add the missing handler.
//

inline void
handle(vcpu_t *vcpu, const exit_handlers_t &handlers)
{
    for (const auto &d : handlers) {
        if (d(vcpu)) {
            vcpu->run();
        }
    }
}

extern "C"  void
handle_exit(vcpu_t *vcpu)
{
    guard_exceptions([vcpu]() {
        handle(vcpu, vcpu->exit_handlers());
        handle(vcpu, vcpu->exit_handlers_for_reason(vcpu->exit_reason()));
    });

    vcpu->halt("unhandled vm exit");
}
