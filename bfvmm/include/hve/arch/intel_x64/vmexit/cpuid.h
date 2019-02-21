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

#ifndef VMEXIT_CPUID_INTEL_X64_H
#define VMEXIT_CPUID_INTEL_X64_H

#include <unordered_map>

#include <bfgsl.h>
#include <bfdelegate.h>

#include "../exit_handler.h"

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

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64
{

class vcpu;

/// CPUID
///
/// Provides an interface for registering handlers for cpuid exits
/// at a given (leaf, subleaf).
///
class EXPORT_HVE cpuid_handler
{
public:

    /// Leaf type
    ///
    ///
    using leaf_t = uint64_t;

    /// Constructor
    ///
    /// @expects
    /// @ensures
    ///
    /// @param vcpu the vcpu object for this handler
    ///
    cpuid_handler(
        gsl::not_null<vcpu *> vcpu);

    /// Destructor
    ///
    /// @expects
    /// @ensures
    ///
    ~cpuid_handler() = default;

    /// Init
    ///
    /// Initializes the handler's hardware state, if any.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu the vcpu object for this handler
    ///
    void init(gsl::not_null<vcpu *> vcpu);

    /// Fini
    ///
    /// Finalizes the handler's hardware state, if any.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param vcpu the vcpu object for this handler
    ///
    void fini(gsl::not_null<vcpu *> vcpu) noexcept;

public:

    /// Add Emulation Handler
    ///
    /// Emulate the VM exit instead of passing it through. If an emulation
    /// handler is registered, at least one handler must return true, otherwise
    /// the base exit handler will be returned false which will result in
    /// a halt(). Emulation handlers should be used by guest vCPUs, or for
    /// hardware that doesn't actually exist. All registers affected by the
    /// VM exit are set to 0 or F (depending on the exit type) prior to the
    /// handlers being executed.
    ///
    /// Note: Handlers must also execute advance() manually
    /// by executing "return vcpu->advance()". This does two things:
    /// - it ensures that the instruction pointer is advanced, but gives the
    ///   handler control if advancement should not be done (for example
    ///   in the case of throwing a hardware exception)
    /// - the advance() function always returns true, which tells the APIs to
    ///   stop executing additional handlers. Calling advance() should always
    ///   be done using a return to ensure that an advance doesn't
    ///   occur twice. Calling advance() and returning tells the APIs that
    ///   the exit is done, and no further processing is needed as true
    ///   is returned.
    ///
    /// @expects
    /// @ensures
    ///
    /// @param leaf the address to emulate
    /// @param d the handler to call when an exit occurs
    ///
    void add_emulation_handler(leaf_t leaf, const handler_delegate_t &d);

    /// Add Pass-Through Handler
    ///
    /// Prior to a pass-through handler being called, the registers
    /// are filled in with information from the actual hardware. Once this
    /// is done, the pass-through handlers are executed until at least one
    /// handler returns true. If no handler returns true, the data in the
    /// registers will be written to hardware if applicable. This
    /// allows the user to register a pass-through handler, without having
    /// to completely handle the exit, allowing the base implementation to
    /// do this.
    ///
    /// Note: Unlike emulation handlers, advance() doesn't need to be called
    /// manually. Instead, the handler can return false, allowing other
    /// handlers to also execute, or allow the base implementation to complete
    /// the exit for you, and advance the instruction pointer. Returning
    /// false should be the default approach unless you explicitly wish to
    /// prevent additional handlers from executing, in which case you can
    /// execute "return vcpu->advance()" which will complete the VM exit.
    /// If you return true and don't execute advance(), the instruction will
    /// not be advanced.
    ///
    /// @expects
    /// @ensures
    ///
    /// @param leaf the cpuid leaf to call d
    /// @param d the handler to call when an exit occurs
    ///
    void add_pass_through_handler(leaf_t leaf, const handler_delegate_t &d);

public:

    /// @cond

    bool handle(vcpu *vcpu);

    /// @endcond

private:

    std::unordered_map<leaf_t, std::list<handler_delegate_t>> m_emulation_handlers;
    std::unordered_map<leaf_t, std::list<handler_delegate_t>> m_pass_through_handlers;

public:

    /// @cond

    cpuid_handler(cpuid_handler &&) = default;
    cpuid_handler &operator=(cpuid_handler &&) = default;

    cpuid_handler(const cpuid_handler &) = delete;
    cpuid_handler &operator=(const cpuid_handler &) = delete;

    /// @endcond
};

}

#endif
