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

#ifndef IMPLEMENTATION_EXIT_HANDLER_INTEL_X64_H
#define IMPLEMENTATION_EXIT_HANDLER_INTEL_X64_H

#include "../uapis/exit_handler.h"

// -----------------------------------------------------------------------------
// Defintion
// -----------------------------------------------------------------------------

///@cond

namespace bfvmm::intel_x64::implementation
{

class exit_handler
{
public:

    explicit exit_handler(gsl::not_null<vcpu *> vcpu);
    VIRTUAL ~exit_handler() = default;

    VIRTUAL void add(const handler_delegate_t &d);
    VIRTUAL void add_for_reason(
        exit_handler_n::exit_reason_t reason, const handler_delegate_t &d);

    VIRTUAL const exit_handlers_t &exit_handlers() const noexcept;
    VIRTUAL const exit_handlers_t &exit_handlers_for_reason(
        exit_handler_n::exit_reason_t reason) const noexcept;

private:

    exit_handlers_t m_exit_handlers;
    std::array<exit_handlers_t, 128> m_exit_handlers_for_reason;

public:
    MOCK_PROTOTYPE(exit_handler);
    COPY_MOVE_SEMANTICS(exit_handler);
};

}

///@endcond

#endif
