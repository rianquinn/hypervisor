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
#include <hve/arch/intel_x64/implementation/vmx.h>

// -----------------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------------

namespace bfvmm::intel_x64::implementation
{

vmx::vmx() :
    m_vmx_region{make_page<uint32_t>()}
{
    this->check_cpuid_vmx_supported();
    this->check_vmx_capabilities_msr();
    this->check_ia32_vmx_cr0_fixed_msr();
    this->check_ia32_vmx_cr4_fixed_msr();

    this->enable_vmx();
    this->execute_vmxon();
}

vmx::~vmx()
{
    guard_exceptions([&]() {
        this->execute_vmxoff();
        this->disable_vmx();
    });
}

void
vmx::check_cpuid_vmx_supported()
{
    if (::intel_x64::cpuid::feature_information::ecx::vmx::is_disabled()) {
        throw std::runtime_error("VMX extensions not supported");
    }
}

void
vmx::check_vmx_capabilities_msr()
{
    using namespace ::intel_x64::msrs::ia32_vmx_basic;

    if (physical_address_width::is_enabled()) {
        throw std::runtime_error("invalid physical address width");
    }

    if (memory_type::get() != ::x64::memory_type::write_back) {
        throw std::runtime_error("invalid memory type");
    }

    if (true_based_controls::is_disabled()) {
        throw std::runtime_error("invalid vmx true based controls");
    }
}

void
vmx::check_ia32_vmx_cr0_fixed_msr()
{
    auto cr0 = ::intel_x64::cr0::get();
    auto ia32_vmx_cr0_fixed0 = ::intel_x64::msrs::ia32_vmx_cr0_fixed0::get();
    auto ia32_vmx_cr0_fixed1 = ::intel_x64::msrs::ia32_vmx_cr0_fixed1::get();

    if (0 != ((~cr0 & ia32_vmx_cr0_fixed0) | (cr0 & ~ia32_vmx_cr0_fixed1))) {
        throw std::runtime_error("invalid cr0");
    }
}

void
vmx::check_ia32_vmx_cr4_fixed_msr()
{
    auto cr4 = ::intel_x64::cr4::get();
    auto ia32_vmx_cr4_fixed0 = ::intel_x64::msrs::ia32_vmx_cr4_fixed0::get();
    auto ia32_vmx_cr4_fixed1 = ::intel_x64::msrs::ia32_vmx_cr4_fixed1::get();

    if (0 != ((~cr4 & ia32_vmx_cr4_fixed0) | (cr4 & ~ia32_vmx_cr4_fixed1))) {
        throw std::runtime_error("invalid cr4");
    }
}

void
vmx::enable_vmx()
{
    if (::intel_x64::msrs::ia32_feature_control::lock_bit::is_disabled()) {
        ::intel_x64::msrs::ia32_feature_control::enable_vmx_outside_smx::enable();
        ::intel_x64::msrs::ia32_feature_control::lock_bit::enable();
    }

    if (::intel_x64::cr4::vmx_enable_bit::is_enabled()) {
        bfalert_warning(0, "VMX was not properly disabled");
        this->execute_vmxoff();
    }

    ::intel_x64::cr4::vmx_enable_bit::enable();
}

void
vmx::disable_vmx()
{ ::intel_x64::cr4::vmx_enable_bit::disable(); }

void
vmx::execute_vmxon()
{
    using namespace ::intel_x64::msrs::ia32_vmx_basic;

    gsl::span<uint32_t> id{m_vmx_region.get(), 1024};
    id[0] = gsl::narrow<uint32_t>(revision_id::get());

    ::intel_x64::vmx::on(
        &g_mm->virtptr_to_physint(m_vmx_region.get())
    );
}

void
vmx::execute_vmxoff()
{ ::intel_x64::vmx::off(); }

}
