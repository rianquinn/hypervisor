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

#include <implementation/vcpu_base.h>

/// WARNING:
///
/// If you change the host/guest ID mask, you must also change this mask in
/// the VMCS launch code as this is hardcoded in that file as well.
///

namespace bfvmm::implementation
{

vcpu_base::vcpu_base(id_t id) :
    m_id{id}
{ }

vcpu_base::id_t
vcpu_base::__id() const noexcept
{ return m_id; }

vcpu_base::id_t
vcpu_base::__generate_guest_id() noexcept
{
    static id_t s_id = 10000;
    return s_id++;
}

bool
vcpu_base::__is_bootstrap_vcpu() const noexcept
{ return m_id == 0; }

bool
vcpu_base::__is_host_vcpu() const noexcept
{ return (m_id & 0xFFFFFFFFFFFF0000UL) == 0; }

bool
vcpu_base::__is_guest_vcpu() const noexcept
{ return !this->__is_host_vcpu(); }

MOCK_FUNCTION(vcpu, {
    mocks.OnCall(vcpu, vcpu_base::id).Return(0);
    mocks.OnCallFunc(vcpu_base::generate_guest_id).Return(10000);
    mocks.OnCall(vcpu, vcpu_base::is_bootstrap_vcpu).Return(true);
    mocks.OnCall(vcpu, vcpu_base::is_host_vcpu).Return(true);
    mocks.OnCall(vcpu, vcpu_base::is_guest_vcpu).Return(false);
})

}
