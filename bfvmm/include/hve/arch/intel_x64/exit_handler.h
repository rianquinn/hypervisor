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

#ifndef EXIT_HANDLER_INTEL_X64_H
#define EXIT_HANDLER_INTEL_X64_H

#include <bfdelegate.h>

#include <list>
#include <array>
#include <memory>

#include <intrinsics.h>

// -----------------------------------------------------------------------------
// Exports
// -----------------------------------------------------------------------------

#include <bfexports.h>

#ifndef STATIC_HVE
#ifdef SHARED_HVE
#define EXPORT_HVE EXPORT_SYM
#else
#define EXPORT_HVE IMPORT_SYM
#endif
#else
#define EXPORT_HVE
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

// -----------------------------------------------------------------------------
// Handler Types
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64
{
class vcpu;
}

using handler_t = bool(bfvmm::intel_x64::vcpu *);
using handler_delegate_t = delegate<handler_t>;

namespace bfvmm::intel_x64
{

class vcpu;

/// Exit handler
///
/// Processes all Intel based vmexits using an exit-specific delegator
///
class EXPORT_HVE exit_handler
{
public:

    /// Default Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu the vcpu object for this handler
    ///
    exit_handler(gsl::not_null<vcpu *> vcpu) = default;

    /// Destructor
    ///
    /// @expects none
    /// @ensures none
    ///
    ~exit_handler() = default;

    /// Init
    ///
    /// Initializes the exit handler's hardware state, if any.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu the vcpu object for this handler
    ///
    void init(gsl::not_null<vcpu *> vcpu);

    /// Fini
    ///
    /// Finalizes the exit handler's hardware state, if any.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu the vcpu object for this handler
    ///
    void fini(gsl::not_null<vcpu *> vcpu);

public:

    /// Add Handler Delegate
    ///
    /// Adds a handler to the handler function. When a VM exit occurs, the
    /// handler handler will call the delegate registered by this function as
    /// as needed. Note that the handlers are called in the reverse order they
    /// are registered (i.e. FIFO).
    ///
    /// @note If the delegate has serviced the VM exit, it should return true,
    ///     otherwise it should return false, and the next delegate registered
    ///     for this VM exit will execute, or an unimplemented exit reason
    ///     error will trigger
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param reason The exit reason for the handler being registered
    /// @param d The delegate being registered
    ///
    void add_handler(
        ::intel_x64::vmcs::value_type reason,
        const handler_delegate_t &d
    );

    /// Add Exit Delegate
    ///
    /// Adds an exit function to the exit list. Exit functions are executed
    /// right after a vCPU exits for any reason. Use this with care because
    /// this function will be executed a lot.
    ///
    /// Note the return value of the delegate is ignored
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param d The delegate being registered
    ///
    void add_exit_handler(
        const handler_delegate_t &d
    );

    /// Handle
    ///
    /// Handles a VM exit. This function should only be called by the exit
    /// handler entry function, which gets called when a VM exit occurs, and
    /// then calls this function to handler the VM exit to the proper
    /// handler.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param exit_handler the exit handler associated with this vcpu
    /// @param vcpu the vcpu this exit occurred on
    /// @return true if the vmexit was successfully handled, false otherwise
    ///
    bool handle(vcpu *vcpu, exit_handler *exit_handler);

private:

    std::list<handler_delegate_t> m_exit_handlers;
    std::array<std::list<handler_delegate_t>, 64> m_exit_handlers_array;

public:

    /// @cond

    exit_handler(exit_handler &&) noexcept = default;
    exit_handler &operator=(exit_handler &&) noexcept = default;

    exit_handler(const exit_handler &) = delete;
    exit_handler &operator=(const exit_handler &) = delete;

    /// @endcond
};

}

using exit_handler_t = bfvmm::intel_x64::exit_handler;

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
