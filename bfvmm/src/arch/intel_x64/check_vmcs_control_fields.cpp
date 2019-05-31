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

#include <uapis/arch/intel_x64/intrinsics/vmcs/16bit_control_fields.h>
#include <uapis/arch/intel_x64/intrinsics/vmcs/32bit_control_fields.h>
#include <uapis/arch/intel_x64/intrinsics/vmcs/64bit_control_fields.h>
#include <uapis/arch/intel_x64/intrinsics/vmcs/natural_width_control_fields.h>
#include <uapis/arch/intel_x64/intrinsics/vmcs/natural_width_guest_state_fields.h>

namespace bfvmm::implementation::intel_x64::check
{

void
ctl_reserved_properly_set(
    ::intel_x64::msrs::field_type addr, ::intel_x64::msrs::value_type ctls, const char *name)
{
    using namespace ::intel_x64::vmcs::processor_based_vm_execution_ctls;

    auto allowed0 = ((::intel_x64::msrs::get(gsl::narrow_cast<uint32_t>(addr)) >> 0) & 0x00000000FFFFFFFFULL);
    auto allowed1 = ((::intel_x64::msrs::get(gsl::narrow_cast<uint32_t>(addr)) >> 32) & 0x00000000FFFFFFFFULL);
    auto allowed1_failed = false;

    ctls &= 0x00000000FFFFFFFFULL;

    if ((allowed0 & ctls) != allowed0) {
        bfdebug_transaction(0, [&](std::string * msg) {
            bferror_info(0, "failed: ctls_reserved_properly_set", msg);
            bferror_subnhex(0, "allowed0", allowed0, msg);
            bferror_subnhex(0, "bad ctls", ctls, msg);
        });

        throw std::logic_error("invalid " + std::string(name));
    }

    allowed1_failed = (ctls & ~allowed1) != 0ULL;

    if (::intel_x64::msrs::ia32_vmx_procbased_ctls2::addr == addr) {
        allowed1_failed = allowed1_failed && activate_secondary_ctls::is_enabled();
    }

    if (allowed1_failed) {
        bfdebug_transaction(0, [&](std::string * msg) {
            bferror_info(0, "failed: ctls_reserved_properly_set", msg);
            bferror_subnhex(0, "allowed1", allowed1, msg);
            bferror_subnhex(0, "bad ctls", ctls, msg);
        });

        throw std::logic_error("invalid " + std::string(name));
    }
}

void
ctl_pin_based_ctls_reserved_properly_set()
{
    auto addr = ::intel_x64::msrs::ia32_vmx_true_pinbased_ctls::addr;
    auto ctls = ::intel_x64::vmcs::pin_based_vm_execution_ctls::get();
    auto name = ::intel_x64::vmcs::pin_based_vm_execution_ctls::name;

    ctl_reserved_properly_set(addr, ctls, name);
}

void
ctl_proc_based_ctls_reserved_properly_set()
{
    auto addr = ::intel_x64::msrs::ia32_vmx_true_procbased_ctls::addr;
    auto ctls = ::intel_x64::vmcs::processor_based_vm_execution_ctls::get();
    auto name = ::intel_x64::vmcs::processor_based_vm_execution_ctls::name;

    ctl_reserved_properly_set(addr, ctls, name);
}

void
ctl_proc_based_ctls2_reserved_properly_set()
{
    if (!::intel_x64::vmcs::processor_based_vm_execution_ctls2::exists()) {
        throw std::logic_error("the secondary ctls field doesn't exist");
    }

    auto addr = ::intel_x64::msrs::ia32_vmx_procbased_ctls2::addr;
    auto ctls = ::intel_x64::vmcs::processor_based_vm_execution_ctls2::get();
    auto name = ::intel_x64::vmcs::processor_based_vm_execution_ctls2::name;

    ctl_reserved_properly_set(addr, ctls, name);
}

void
ctl_cr3_count_less_then_4()
{
    if (::intel_x64::vmcs::cr3_target_count::get() > 4) {
        throw std::logic_error("cr3 target count > 4");
    }
}

void
ctl_io_bitmap_addr_bits()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::use_io_bitmaps::is_disabled()) {
        return;
    }

    auto addr_a = ::intel_x64::vmcs::io_bitmap_a_addr::get();
    auto addr_b = ::intel_x64::vmcs::io_bitmap_b_addr::get();

    if ((addr_a & 0x0000000000000FFF) != 0) {
        throw std::logic_error("io bitmap a addr not page aligned");
    }

    if ((addr_b & 0x0000000000000FFF) != 0) {
        throw std::logic_error("io bitmap b addr not page aligned");
    }

    if (!::intel_x64::is_physical_addr_valid(addr_a)) {
        throw std::logic_error("io bitmap a addr too large");
    }

    if (!::intel_x64::is_physical_addr_valid(addr_b)) {
        throw std::logic_error("io bitmap b addr too large");
    }
}

void
ctl_msr_bitmaps_addr_bits()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::use_msr_bitmap::is_disabled()) {
        return;
    }

    auto addr = ::intel_x64::vmcs::msr_bitmaps_addr::get();

    if ((addr & 0x0000000000000FFF) != 0) {
        throw std::logic_error("msr bitmap addr not page aligned");
    }

    if (!::intel_x64::is_physical_addr_valid(addr)) {
        throw std::logic_error("msr bitmap addr too large");
    }
}

void
ctl_tpr_shadow_and_virtual_apic()
{
    using namespace ::intel_x64::vmcs::processor_based_vm_execution_ctls;
    using namespace ::intel_x64::vmcs::processor_based_vm_execution_ctls2;

    auto secondary_ctls_enabled = activate_secondary_ctls::is_enabled();

    if (use_tpr_shadow::is_enabled()) {

        auto phys_addr = ::intel_x64::vmcs::virtual_apic_addr::get();

        if (phys_addr == 0) {
            throw std::logic_error("virtual apic physical addr is NULL");
        }

        if ((phys_addr & 0x0000000000000FFFULL) != 0) {
            throw std::logic_error("virtual apic addr not 4k aligned");
        }

        if (!::intel_x64::is_physical_addr_valid(phys_addr)) {
            throw std::logic_error("virtual apic addr too large");
        }

        if (secondary_ctls_enabled && virtual_int_delivery::is_enabled_if_exists()) {
            throw std::logic_error("tpr_shadow is enabled, but virtual int delivery is enabled");
        }

        auto tpr_threshold = ::intel_x64::vmcs::tpr_threshold::get();

        if ((tpr_threshold & 0xFFFFFFF0ULL) != 0) {
            throw std::logic_error("bits 31:4 of the tpr threshold must be 0");
        }

        if (secondary_ctls_enabled && virtualize_apic_accesses::is_enabled_if_exists()) {
            throw std::logic_error("tpr_shadow is enabled, but virtual apic is enabled");
        }

        // TODO
        //
        // There are some additional checks that we are not performing here
        // that require a physical to virtual address translation.
        //
    }
    else {

        if (activate_secondary_ctls::is_disabled()) {
            return;
        }

        if (virtualize_x2apic_mode::is_enabled_if_exists()) {
            throw std::logic_error("virtualize_x2apic_mode must be disabled if tpr shadow is disabled");
        }

        if (apic_register_virtualization::is_enabled_if_exists()) {
            throw std::logic_error("apic_register_virtualization must be disabled if tpr shadow is disabled");
        }

        if (virtual_int_delivery::is_enabled_if_exists()) {
            throw std::logic_error("virtual_int_delivery must be disabled if tpr shadow is disabled");
        }
    }
}

void
ctl_nmi_exiting_and_virtual_nmi()
{
    if (::intel_x64::vmcs::pin_based_vm_execution_ctls::nmi_exiting::is_enabled()) {
        return;
    }

    if (::intel_x64::vmcs::pin_based_vm_execution_ctls::virtual_nmis::is_enabled()) {
        throw std::logic_error("virtual NMI must be 0 if NMI exiting is 0");
    }
}

void
ctl_virtual_nmi_and_nmi_window()
{
    if (::intel_x64::vmcs::pin_based_vm_execution_ctls::virtual_nmis::is_enabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::nmi_window_exiting::is_enabled()) {
        throw std::logic_error("NMI window exiting must be 0 if virtual NMI is 0");
    }
}

void
ctl_virtual_apic_addr_bits()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::virtualize_apic_accesses::is_disabled_if_exists()) {
        return;
    }

    auto phys_addr = ::intel_x64::vmcs::apic_access_addr::get_if_exists();

    if (phys_addr == 0) {
        throw std::logic_error("apic access physical addr is NULL");
    }

    if ((phys_addr & 0x0000000000000FFF) != 0) {
        throw std::logic_error("apic access addr not 4k aligned");
    }

    if (!::intel_x64::is_physical_addr_valid(phys_addr)) {
        throw std::logic_error("apic access addr too large");
    }
}

void
ctl_x2apic_mode_and_virtual_apic_access()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::virtualize_x2apic_mode::is_disabled_if_exists()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::virtualize_apic_accesses::is_enabled_if_exists()) {
        throw std::logic_error("apic accesses must be 0 if x2 apic mode is 1");
    }
}

void
ctl_virtual_int_and_external_int()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::virtual_int_delivery::is_disabled_if_exists()) {
        return;
    }

    if (::intel_x64::vmcs::pin_based_vm_execution_ctls::external_int_exiting::is_disabled()) {
        throw std::logic_error("external_int_exiting must be 1 "
                               "if virtual_int_delivery is 1");
    }
}

void
ctl_process_posted_int_checks()
{
    if (::intel_x64::vmcs::pin_based_vm_execution_ctls::process_posted_ints::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        throw std::logic_error("virtual int delivery must be 1 "
                               "if posted ints is 1");
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::virtual_int_delivery::is_disabled_if_exists()) {
        throw std::logic_error("virtual int delivery must be 1 "
                               "if posted ints is 1");
    }

    if (::intel_x64::vmcs::vmexit_ctls::acknowledge_int_on_exit::is_disabled()) {
        throw std::logic_error("ack int on exit must be 1 "
                               "if posted ints is 1");
    }

    auto vector = ::intel_x64::vmcs::posted_int_notification_vector::get();

    if ((vector & 0x000000000000FF00ULL) != 0) {
        throw std::logic_error("bits 15:8 of the notification vector must "
                               "be 0 if posted ints is 1");
    }

    auto addr = ::intel_x64::vmcs::posted_int_descriptor_addr::get();

    if ((addr & 0x000000000000003FULL) != 0) {
        throw std::logic_error("bits 5:0 of the int descriptor addr "
                               "must be 0 if posted ints is 1");
    }

    if (!::intel_x64::is_physical_addr_valid(addr)) {
        throw std::logic_error("int descriptor addr too large");
    }
}

void
ctl_vpid_checks()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::enable_vpid::is_disabled_if_exists()) {
        return;
    }

    if (::intel_x64::vmcs::virtual_processor_identifier::get_if_exists() == 0) {
        throw std::logic_error("vpid cannot equal 0");
    }
}

void
ctl_enable_ept_checks()
{
    using namespace ::intel_x64::msrs::ia32_vmx_ept_vpid_cap;
    using namespace ::intel_x64::vmcs::ept_ptr;

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::enable_ept::is_disabled_if_exists()) {
        return;
    }

    auto mem_type = ::intel_x64::vmcs::ept_ptr::memory_type::get_if_exists();

    if (mem_type == memory_type::uncacheable && memory_type_uncacheable_supported::is_disabled()) {
        throw std::logic_error("hardware does not support ept memory type: uncachable");
    }

    if (mem_type == memory_type::write_back && memory_type_write_back_supported::is_disabled()) {
        throw std::logic_error("hardware does not support ept memory type: write-back");
    }

    if (mem_type != memory_type::uncacheable && mem_type != memory_type::write_back) {
        throw std::logic_error("unknown eptp memory type");
    }

    if (page_walk_len_minus_one::get_if_exists() != 3) {
        throw std::logic_error("the ept walk-through len must be 1 less than 4, i.e. 3");
    }

    if (accessed_and_dirty_flags::is_enabled_if_exists() && accessed_dirty_support::is_disabled()) {
        throw std::logic_error("hardware does not support dirty / accessed flags for ept");
    }

    if (::intel_x64::vmcs::ept_ptr::reserved::get_if_exists() != 0) {
        throw std::logic_error("bits 11:7 and 63:48 of the eptp must be 0");
    }
}

void
ctl_enable_pml_checks()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::enable_pml::is_disabled_if_exists()) {
        return;
    }

    auto pml_addr = ::intel_x64::vmcs::pml_addr::get_if_exists();

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::enable_ept::is_disabled_if_exists()) {
        throw std::logic_error("ept must be enabled if pml is enabled");
    }

    if (!::intel_x64::is_physical_addr_valid(pml_addr)) {
        throw std::logic_error("pml addr must be a valid physical addr");
    }

    if ((pml_addr & 0x0000000000000FFF) != 0) {
        throw std::logic_error("bits 11:0 of the pml addr must be 0");
    }
}

void
ctl_unrestricted_guests()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::unrestricted_guest::is_disabled_if_exists()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::enable_ept::is_disabled_if_exists()) {
        throw std::logic_error("enable ept must be 1 if unrestricted guest is 1");
    }
}

void
ctl_enable_vm_functions()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::enable_vm_functions::is_disabled_if_exists()) {
        return;
    }

    if (!::intel_x64::vmcs::vm_function_ctls::exists()) {
        return;
    }

    if ((~::intel_x64::msrs::ia32_vmx_vmfunc::get() & ::intel_x64::vmcs::vm_function_ctls::get()) != 0) {
        throw std::logic_error("unsupported vm function ctl bit set");
    }

    if (::intel_x64::vmcs::vm_function_ctls::eptp_switching::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::enable_ept::is_disabled_if_exists()) {
        throw std::logic_error("enable ept must be 1 if eptp switching is 1");
    }

    auto eptp_list = ::intel_x64::vmcs::eptp_list_addr::get_if_exists();

    if ((eptp_list & 0x0000000000000FFFU) != 0) {
        throw std::logic_error("bits 11:0 must be 0 for eptp list addr");
    }

    if (!::intel_x64::is_physical_addr_valid(eptp_list)) {
        throw std::logic_error("eptp list addr addr too large");
    }
}

void
ctl_enable_vmcs_shadowing()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::vmcs_shadowing::is_disabled_if_exists()) {
        return;
    }

    auto vmcs_vmread_bitmap_addr = ::intel_x64::vmcs::vmread_bitmap_addr::get_if_exists();
    auto vmcs_vmwrite_bitmap_addr = ::intel_x64::vmcs::vmwrite_bitmap_addr::get_if_exists();

    if ((vmcs_vmread_bitmap_addr & 0x0000000000000FFF) != 0) {
        throw std::logic_error("bits 11:0 must be 0 for the vmcs read bitmap addr");
    }

    if ((vmcs_vmwrite_bitmap_addr & 0x0000000000000FFF) != 0) {
        throw std::logic_error("bits 11:0 must be 0 for the vmcs write bitmap addr");
    }

    if (!::intel_x64::is_physical_addr_valid(vmcs_vmread_bitmap_addr)) {
        throw std::logic_error("vmcs read bitmap addr addr too large");
    }

    if (!::intel_x64::is_physical_addr_valid(vmcs_vmwrite_bitmap_addr)) {
        throw std::logic_error("vmcs write bitmap addr addr too large");
    }
}

void
ctl_enable_ept_violation_checks()
{
    if (::intel_x64::vmcs::processor_based_vm_execution_ctls::activate_secondary_ctls::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::processor_based_vm_execution_ctls2::ept_violation_ve::is_disabled_if_exists()) {
        return;
    }

    auto vmcs_virt_except_info_addr =
        ::intel_x64::vmcs::virtualization_exception_info_addr::get_if_exists();

    if ((vmcs_virt_except_info_addr & 0x0000000000000FFF) != 0) {
        throw std::logic_error("bits 11:0 must be 0 for the vmcs virt except info addr");
    }

    if (!::intel_x64::is_physical_addr_valid(vmcs_virt_except_info_addr)) {
        throw std::logic_error("vmcs virt except info addr addr too large");
    }
}

void
ctl_vmexit_ctls_reserved_properly_set()
{
    auto addr = ::intel_x64::msrs::ia32_vmx_true_exit_ctls::addr;
    auto ctls = ::intel_x64::vmcs::vmexit_ctls::get();
    auto name = ::intel_x64::vmcs::vmexit_ctls::name;

    ctl_reserved_properly_set(addr, ctls, name);
}

void
ctl_activate_and_save_preemption_timer_must_be_0()
{
    if (::intel_x64::vmcs::pin_based_vm_execution_ctls::activate_preemption_timer::is_enabled()) {
        return;
    }

    if (::intel_x64::vmcs::vmexit_ctls::save_preemption_timer_value::is_enabled()) {
        throw std::logic_error("save vmx preemption timer must be 0 "
                               "if activate vmx preemption timer is 0");
    }
}

void
ctl_exit_msr_store_addr()
{
    auto msr_store_count = ::intel_x64::vmcs::vmexit_msr_store_count::get();

    if (msr_store_count == 0) {
        return;
    }

    auto msr_store_addr = ::intel_x64::vmcs::vmexit_msr_store_addr::get();

    if ((msr_store_addr & 0x000000000000000F) != 0) {
        throw std::logic_error("bits 3:0 must be 0 for the exit msr store addr");
    }

    if (!::intel_x64::is_physical_addr_valid(msr_store_addr)) {
        throw std::logic_error("exit msr store addr too large");
    }

    auto msr_store_addr_end = msr_store_addr + (msr_store_count * 16) - 1;

    if (!::intel_x64::is_physical_addr_valid(msr_store_addr_end)) {
        throw std::logic_error("end of exit msr store area too large");
    }
}

void
ctl_exit_msr_load_addr()
{
    auto msr_load_count = ::intel_x64::vmcs::vmexit_msr_load_count::get();

    if (msr_load_count == 0) {
        return;
    }

    auto msr_load_addr = ::intel_x64::vmcs::vmexit_msr_load_addr::get();

    if ((msr_load_addr & 0x000000000000000F) != 0) {
        throw std::logic_error("bits 3:0 must be 0 for the exit msr load addr");
    }

    if (!::intel_x64::is_physical_addr_valid(msr_load_addr)) {
        throw std::logic_error("exit msr load addr too large");
    }

    auto msr_load_addr_end = msr_load_addr + (msr_load_count * 16) - 1;

    if (!::intel_x64::is_physical_addr_valid(msr_load_addr_end)) {
        throw std::logic_error("end of exit msr load area too large");
    }
}

void
ctl_vmentry_ctls_reserved_properly_set()
{
    auto addr = ::intel_x64::msrs::ia32_vmx_true_entry_ctls::addr;
    auto ctls = ::intel_x64::vmcs::vmentry_ctls::get();
    auto name = ::intel_x64::vmcs::vmentry_ctls::name;

    ctl_reserved_properly_set(addr, ctls, name);
}

void
ctl_event_injection_type_vector_checks()
{
    using namespace ::intel_x64::vmcs::vmentry_interruption_info;
    using namespace ::intel_x64::msrs::ia32_vmx_true_procbased_ctls;

    if (::intel_x64::vmcs::vmentry_interruption_info::valid_bit::is_disabled()) {
        return;
    }

    auto vector = ::intel_x64::vmcs::vmentry_interruption_info::vector::get();
    auto type = ::intel_x64::vmcs::vmentry_interruption_info::interruption_type::get();

    if (type == interruption_type::reserved) {
        throw std::logic_error("int info field type of 1 is reserved");
    }

    if (!monitor_trap_flag::is_allowed1() && type == interruption_type::other_event) {
        throw std::logic_error("int info field type of 7 "
                               "is reserved on this hardware");
    }

    if (type == interruption_type::non_maskable_int && vector != 2) {
        throw std::logic_error("int info field vector must be "
                               "2 if the type field is 2 (NMI)");
    }

    if (type == interruption_type::hardware_exception && vector > 31) {
        throw std::logic_error("int info field vector must be "
                               "at most 31 if the type field is 3 (HE)");
    }

    if (type == interruption_type::other_event && vector != 0) {
        throw std::logic_error("int info field vector must be "
                               "0 if the type field is 7 (other)");
    }
}

void
ctl_event_injection_delivery_ec_checks()
{
    using namespace ::intel_x64::vmcs::vmentry_interruption_info;
    using namespace ::intel_x64::vmcs::processor_based_vm_execution_ctls;
    using namespace ::intel_x64::vmcs::processor_based_vm_execution_ctls2;

    if (::intel_x64::vmcs::vmentry_interruption_info::valid_bit::is_disabled()) {
        return;
    }

    auto type = ::intel_x64::vmcs::vmentry_interruption_info::interruption_type::get();
    auto vector = ::intel_x64::vmcs::vmentry_interruption_info::vector::get();

    if (unrestricted_guest::is_enabled() && activate_secondary_ctls::is_enabled()) {
        if (::intel_x64::vmcs::guest_cr0::protection_enable::is_disabled() && deliver_error_code_bit::is_enabled()) {
            throw std::logic_error("unrestricted guest must be 0 or PE must "
                                   "be enabled in cr0 if deliver_error_code_bit is set");
        }
    }

    if (type != interruption_type::hardware_exception && deliver_error_code_bit::is_enabled()) {
        throw std::logic_error("int info field type must be "
                               "3 if deliver_error_code_bit is set");
    }

    switch (vector) {
        case 8:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 17:
            if (deliver_error_code_bit::is_disabled()) {
                throw std::logic_error("deliver_error_code_bit must be 1");
            }
            break;

        default:
            if (deliver_error_code_bit::is_enabled()) {
                throw std::logic_error("vector must indicate exception that would normally "
                                       "deliver an error code if deliver_error_code_bit is set");
            }
            break;
    }
}

void
ctl_event_injection_reserved_bits_checks()
{
    if (::intel_x64::vmcs::vmentry_interruption_info::valid_bit::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::vmentry_interruption_info::reserved::get() != 0) {
        throw std::logic_error("reserved bits of the int info field must be 0");
    }
}

void
ctl_event_injection_ec_checks()
{
    if (::intel_x64::vmcs::vmentry_interruption_info::valid_bit::is_disabled()) {
        return;
    }

    if (::intel_x64::vmcs::vmentry_interruption_info::deliver_error_code_bit::is_disabled()) {
        return;
    }

    if ((::intel_x64::vmcs::vmentry_exception_error_code::get() & 0x00000000FFFF8000ULL) != 0) {
        throw std::logic_error("bits 31:15 of the exception error code field must be 0 "
                               "if deliver error code bit is set in the int info field");
    }
}

void
ctl_event_injection_instr_len_checks()
{
    using namespace ::intel_x64::vmcs::vmentry_interruption_info;

    if (::intel_x64::vmcs::vmentry_interruption_info::valid_bit::is_disabled()) {
        return;
    }

    auto type = ::intel_x64::vmcs::vmentry_interruption_info::interruption_type::get();
    auto instr_len = ::intel_x64::vmcs::vmentry_instr_len::get();

    switch (type) {
        case interruption_type::software_int:
        case interruption_type::privileged_software_exception:
        case interruption_type::software_exception:
            break;

        default:
            return;
    }

    if (instr_len == 0 &&
        ::intel_x64::msrs::ia32_vmx_misc::injection_with_instr_len_of_zero::is_disabled()) {
        throw std::logic_error("instr len must be greater than zero");
    }

    if (instr_len > 15) {
        throw std::logic_error("instr len must be in the range of 0-15 if type is 4, 5, 6");
    }
}

void
ctl_entry_msr_load_addr()
{
    auto msr_load_count = ::intel_x64::vmcs::vmentry_msr_load_count::get();

    if (msr_load_count == 0) {
        return;
    }

    auto msr_load_addr = ::intel_x64::vmcs::vmentry_msr_load_addr::get();

    if ((msr_load_addr & 0x000000000000000F) != 0) {
        throw std::logic_error("bits 3:0 must be 0 for the entry msr load addr");
    }

    if (!::intel_x64::is_physical_addr_valid(msr_load_addr)) {
        throw std::logic_error("entry msr load addr too large");
    }

    auto msr_load_addr_end = msr_load_addr + (msr_load_count * 16) - 1;

    if (!::intel_x64::is_physical_addr_valid(msr_load_addr_end)) {
        throw std::logic_error("end of entry msr load area too large");
    }
}

}
