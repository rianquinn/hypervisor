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

#ifndef IMPLEMENTATION_VCPU_H
#define IMPLEMENTATION_VCPU_H

#include "../papis/macros.h"

namespace bfvmm::implementation
{

class vcpu
{
public:

    using id_t = uint64_t;

public:

    explicit vcpu(id_t id);
    VIRTUAL ~vcpu() = default;

    VIRTUAL id_t id() const noexcept;
    VIRTUAL static id_t generate_guest_id() noexcept;

    VIRTUAL bool is_bootstrap_vcpu() const noexcept;
    VIRTUAL bool is_host_vcpu() const noexcept;
    VIRTUAL bool is_guest_vcpu() const noexcept;

    template<typename T>
    T data()
    { return std::any_cast<T>(m_data); }

    template<typename T>
    void set_data(T &&t)
    { m_data = std::any(t); }

private:

    id_t m_id;
    std::any m_data{};

public:
    MOCK_PROTOTYPE(vcpu)
    COPY_MOVE_SEMANTICS(vcpu)
};

}

#endif
