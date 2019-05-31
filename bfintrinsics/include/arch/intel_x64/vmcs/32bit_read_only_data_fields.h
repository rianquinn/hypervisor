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

#ifndef VMCS_INTEL_X64_32BIT_READ_ONLY_DATA_FIELDS_H
#define VMCS_INTEL_X64_32BIT_READ_ONLY_DATA_FIELDS_H

#include "helpers.h"

// *INDENT-OFF*

namespace intel_x64::vmcs
{

namespace vm_instr_error
{
    constexpr const auto addr = 0x0000000000004400ULL;
    constexpr const auto name = "vm_instr_error";

    inline auto exists()
    { return true; }

    inline auto get()
    { return get_vmcs_field(addr, name, exists()); }

    inline auto vm_instr_error_description(value_type error)
    {
        switch (error) {
            case 1U:
                return "VMCALL executed in VMX root operation";

            case 2U:
                return "VMCLEAR with invalid physical addr";

            case 3U:
                return "VMCLEAR with VMXON ptr";

            case 4U:
                return "VMLAUNCH with non-clear VMCS";

            case 5U:
                return "VMRESUME with non-launched VMCS";

            case 6U:
                return "VMRESUME after VMXOFF (VMXOFF AND VMXON between VMLAUNCH and VMRESUME)";

            case 7U:
                return "VM entry with invalid ctl field(s)";

            case 8U:
                return "VM entry with invalid host-state field(s)";

            case 9U:
                return "VMPTRLD with invalid physical addr";

            case 10U:
                return "VMPTRLD with VMXON ptr";

            case 11U:
                return "VMPTRLD with incorrect VMCS revision identifier";

            case 12U:
                return "VMREAD/VMWRITE from/to unsupported VMCS component";

            case 13U:
                return "VMWRITE to read-only VMCS component";

            case 15U:
                return "VMXON executed in VMX root operation";

            case 16U:
                return "VM entry with invalid executive-VMCS ptr";

            case 17U:
                return "VM entry with non-launched executive VMCS";

            case 18U:
                return "VM entry with executive-VMCS ptr not VMXON ptr "
                       "(when attempting to deactivate the dual-monitor treatment of SMIs and SMM)";

            case 19U:
                return "VMCALL with non-clear VMCS (when attempting to activate"
                       " the dual-monitor treatment of SMIs and SMM)";

            case 20U:
                return "VMCALL with invalid VM-exit ctl fields";

            case 22U:
                return "VMCALL with incorrect MSEG revision identifier (when attempting "
                       "to activate the dual-monitor treatment of SMIs and SMM)";

            case 23U:
                return "VMXOFF under dual-monitor treatment of SMIs and SMM";

            case 24U:
                return "VMCALL with invalid SMM-monitor features (when attempting to "
                       "activate the dual-monitor treatment of SMIs and SMM)";

            case 25U:
                return "VM entry with invalid VM-execution ctl fields in executive"
                       " VMCS (when attempting to return from SMM)";

            case 26U:
                return "VM entry with events blocked by MOV SS";

            case 28U:
                return "Invalid operand to INVEPT/INVVPID";

            default:
                return "Unknown VM-instr error";
        }
    }

    inline auto description()
    { return vm_instr_error_description(get_vmcs_field(addr, name, exists())); }
}

namespace exit_reason
{
    constexpr const auto addr = 0x0000000000004402ULL;
    constexpr const auto name = "exit_reason";

    inline auto exists()
    { return true; }

    inline auto get()
    { return get_vmcs_field(addr, name, exists()); }

    namespace basic_exit_reason
    {
        constexpr const auto mask = 0x000000000000FFFFULL;
        constexpr const auto from = 0ULL;
        constexpr const auto name = "basic_exit_reason";                        // Short Name

        constexpr const auto exception_or_nmi = 0U;
        constexpr const auto external_int = 1U;
        constexpr const auto triple_fault = 2U;
        constexpr const auto init_signal = 3U;
        constexpr const auto sipi = 4U;
        constexpr const auto smi = 5U;
        constexpr const auto other_smi = 6U;
        constexpr const auto int_window = 7U;
        constexpr const auto nmi_window = 8U;
        constexpr const auto task_switch = 9U;
        constexpr const auto cpuid = 10U;
        constexpr const auto getsec = 11U;
        constexpr const auto hlt = 12U;
        constexpr const auto invd = 13U;
        constexpr const auto invlpg = 14U;
        constexpr const auto rdpmc = 15U;
        constexpr const auto rdtsc = 16U;
        constexpr const auto rsm = 17U;
        constexpr const auto vmcall = 18U;
        constexpr const auto vmclear = 19U;
        constexpr const auto vmlaunch = 20U;
        constexpr const auto vmptrld = 21U;
        constexpr const auto vmptrst = 22U;
        constexpr const auto vmread = 23U;
        constexpr const auto vmresume = 24U;
        constexpr const auto vmwrite = 25U;
        constexpr const auto vmxoff = 26U;
        constexpr const auto vmxon = 27U;
        constexpr const auto ctl_register_accesses = 28U;
        constexpr const auto mov_dr = 29U;
        constexpr const auto io_instr = 30U;
        constexpr const auto rdmsr = 31U;
        constexpr const auto wrmsr = 32U;
        constexpr const auto vmentry_failure_invalid_guest_state = 33U;
        constexpr const auto vmentry_failure_msr_loading = 34U;
        constexpr const auto mwait = 36U;
        constexpr const auto monitor_trap_flag = 37U;
        constexpr const auto monitor = 39U;
        constexpr const auto pause = 40U;
        constexpr const auto vmentry_failure_machine_check_event = 41U;
        constexpr const auto tpr_below_threshold = 43U;
        constexpr const auto apic_access = 44U;
        constexpr const auto virtualized_eoi = 45U;
        constexpr const auto access_to_gdtr_or_idtr = 46U;
        constexpr const auto access_to_ldtr_or_tr = 47U;
        constexpr const auto ept_violation = 48U;
        constexpr const auto ept_misconfiguration = 49U;
        constexpr const auto invept = 50U;
        constexpr const auto rdtscp = 51U;
        constexpr const auto preemption_timer = 52U;
        constexpr const auto invvpid = 53U;
        constexpr const auto wbinvd = 54U;
        constexpr const auto xsetbv = 55U;
        constexpr const auto apic_write = 56U;
        constexpr const auto rdrand = 57U;
        constexpr const auto invpcid = 58U;
        constexpr const auto vmfunc = 59U;
        constexpr const auto rdseed = 61U;
        constexpr const auto xsaves = 63U;
        constexpr const auto xrstors = 64U;

        inline auto get()
        { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

        inline auto basic_exit_reason_description(value_type reason)
        {
            switch (reason) {
                case exception_or_nmi:
                    return "exception_or_nmi";

                case external_int:
                    return "external_int";

                case triple_fault:
                    return "triple_fault";

                case init_signal:
                    return "init_signal";

                case sipi:
                    return "sipi";

                case smi:
                    return "smi";

                case other_smi:
                    return "other_smi";

                case int_window:
                    return "int_window";

                case nmi_window:
                    return "nmi_window";

                case task_switch:
                    return "task_switch";

                case cpuid:
                    return "cpuid";

                case getsec:
                    return "getsec";

                case hlt:
                    return "hlt";

                case invd:
                    return "invd";

                case invlpg:
                    return "invlpg";

                case rdpmc:
                    return "rdpmc";

                case rdtsc:
                    return "rdtsc";

                case rsm:
                    return "rsm";

                case vmcall:
                    return "vmcall";

                case vmclear:
                    return "vmclear";

                case vmlaunch:
                    return "vmlaunch";

                case vmptrld:
                    return "vmptrld";

                case vmptrst:
                    return "vmptrst";

                case vmread:
                    return "vmread";

                case vmresume:
                    return "vmresume";

                case vmwrite:
                    return "vmwrite";

                case vmxoff:
                    return "vmxoff";

                case vmxon:
                    return "vmxon";

                case ctl_register_accesses:
                    return "ctl_register_accesses";

                case mov_dr:
                    return "mov_dr";

                case io_instr:
                    return "io_instr";

                case rdmsr:
                    return "rdmsr";

                case wrmsr:
                    return "wrmsr";

                case vmentry_failure_invalid_guest_state:
                    return "vmentry_failure_invalid_guest_state";

                case vmentry_failure_msr_loading:
                    return "vmentry_failure_msr_loading";

                case mwait:
                    return "mwait";

                case monitor_trap_flag:
                    return "monitor_trap_flag";

                case monitor:
                    return "monitor";

                case pause:
                    return "pause";

                case vmentry_failure_machine_check_event:
                    return "vmentry_failure_machine_check_event";

                case tpr_below_threshold:
                    return "tpr_below_threshold";

                case apic_access:
                    return "apic_access";

                case virtualized_eoi:
                    return "virtualized_eoi";

                case access_to_gdtr_or_idtr:
                    return "access_to_gdtr_or_idtr";

                case access_to_ldtr_or_tr:
                    return "access_to_ldtr_or_tr";

                case ept_violation:
                    return "ept_violation";

                case ept_misconfiguration:
                    return "ept_misconfiguration";

                case invept:
                    return "invept";

                case rdtscp:
                    return "rdtscp";

                case preemption_timer:
                    return "preemption_timer";

                case invvpid:
                    return "invvpid";

                case wbinvd:
                    return "wbinvd";

                case xsetbv:
                    return "xsetbv";

                case apic_write:
                    return "apic_write";

                case rdrand:
                    return "rdrand";

                case invpcid:
                    return "invpcid";

                case vmfunc:
                    return "vmfunc";

                case rdseed:
                    return "rdseed";

                case xsaves:
                    return "xsaves";

                case xrstors:
                    return "xrstors";

                default:
                    return "unknown";
            }
        }

        inline auto description()
        {
            auto field = get_bits(get_vmcs_field(addr, name, exists()), mask) >> from;
            return basic_exit_reason_description(field);
        }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_text(level, msg); }
    }

    namespace reserved
    {
        constexpr const auto mask = 0x0000000047FF0000ULL;
        constexpr const auto from = 0ULL;
        constexpr const auto name = "reserved";

        inline auto get()
        { return get_bits(get_vmcs_field(addr, name, true), mask) >> from; }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subnhex(level, msg); }
    }

    namespace vmexit_incident_to_enclave_mode
    {
        constexpr const auto mask = 0x0000000008000000ULL;
        constexpr const auto from = 27ULL;
        constexpr const auto name = "vmexit_incident_to_enclave_mode";

        inline auto is_enabled()
        { return is_bit_set(get_vmcs_field(addr, name, true), from); }

        inline auto is_enabled(value_type field)
        { return is_bit_set(field, from); }

        inline auto is_enabled_if_exists(bool verbose = false)
        { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, true), from); }

        inline auto is_disabled()
        { return is_bit_cleared(get_vmcs_field(addr, name, true), from); }

        inline auto is_disabled(value_type field)
        { return is_bit_cleared(field, from); }

        inline auto is_disabled_if_exists(bool verbose = false)
        { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, true), from); }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subbool(level, msg); }
    }

    namespace pending_mtf_vmexit
    {
        constexpr const auto mask = 0x0000000010000000ULL;
        constexpr const auto from = 28ULL;
        constexpr const auto name = "pending_mtf_vmexit";

        inline auto is_enabled()
        { return is_bit_set(get_vmcs_field(addr, name, true), from); }

        inline auto is_enabled(value_type field)
        { return is_bit_set(field, from); }

        inline auto is_enabled_if_exists(bool verbose = false)
        { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, true), from); }

        inline auto is_disabled()
        { return is_bit_cleared(get_vmcs_field(addr, name, true), from); }

        inline auto is_disabled(value_type field)
        { return is_bit_cleared(field, from); }

        inline auto is_disabled_if_exists(bool verbose = false)
        { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, true), from); }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subbool(level, msg); }
    }

    namespace vmexit_from_vmx_root_operation
    {
        constexpr const auto mask = 0x0000000020000000ULL;
        constexpr const auto from = 29ULL;
        constexpr const auto name = "vmexit_from_vmx_root_operation";

        inline auto is_enabled()
        { return is_bit_set(get_vmcs_field(addr, name, true), from); }

        inline auto is_enabled(value_type field)
        { return is_bit_set(field, from); }

        inline auto is_enabled_if_exists(bool verbose = false)
        { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, true), from); }

        inline auto is_disabled()
        { return is_bit_cleared(get_vmcs_field(addr, name, true), from); }

        inline auto is_disabled(value_type field)
        { return is_bit_cleared(field, from); }

        inline auto is_disabled_if_exists(bool verbose = false)
        { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, true), from); }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subbool(level, msg); }
    }

    namespace vmentry_failure
    {
        constexpr const auto mask = 0x0000000080000000ULL;
        constexpr const auto from = 31ULL;
        constexpr const auto name = "vmentry_failure";

        inline auto is_enabled()
        { return is_bit_set(get_vmcs_field(addr, name, true), from); }

        inline auto is_enabled(value_type field)
        { return is_bit_set(field, from); }

        inline auto is_enabled_if_exists(bool verbose = false)
        { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, true), from); }

        inline auto is_disabled()
        { return is_bit_cleared(get_vmcs_field(addr, name, true), from); }

        inline auto is_disabled(value_type field)
        { return is_bit_cleared(field, from); }

        inline auto is_disabled_if_exists(bool verbose = false)
        { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, true), from); }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subbool(level, msg); }
    }

    inline void dump(int level, std::string *msg = nullptr)
    {
        dump_vmcs_nhex(level, msg);
        basic_exit_reason::dump(level, msg);
        reserved::dump(level, msg);
        vmexit_incident_to_enclave_mode::dump(level, msg);
        pending_mtf_vmexit::dump(level, msg);
        vmexit_from_vmx_root_operation::dump(level, msg);
        vmentry_failure::dump(level, msg);
    }
}

namespace vmexit_interruption_info
{
    constexpr const auto addr = 0x0000000000004404ULL;
    constexpr const auto name = "vmexit_interruption_info";

    inline auto exists()
    { return true; }

    inline auto get()
    { return get_vmcs_field(addr, name, exists()); }

    inline auto get_if_exists(bool verbose = false)
    { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

    namespace vector
    {
        constexpr const auto mask = 0x000000FFULL;
        constexpr const auto from = 0ULL;
        constexpr const auto name = "vector";

        inline auto get()
        { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

        inline auto get(value_type field)
        { return get_bits(field, mask) >> from; }

        inline auto get_if_exists(bool verbose = false)
        { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subnhex(level, msg); }
    }

    namespace interruption_type
    {
        constexpr const auto mask = 0x00000700ULL;
        constexpr const auto from = 8ULL;
        constexpr const auto name = "interruption_type";

        constexpr const auto external_int = 0ULL;
        constexpr const auto non_maskable_int = 2ULL;
        constexpr const auto hardware_exception = 3ULL;
        constexpr const auto software_exception = 6ULL;

        inline auto get()
        { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

        inline auto get(value_type field)
        { return get_bits(field, mask) >> from; }

        inline auto get_if_exists(bool verbose = false)
        { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subnhex(level, msg); }
    }

    namespace error_code_valid
    {
        constexpr const auto mask = 0x00000800ULL;
        constexpr const auto from = 11ULL;
        constexpr const auto name = "deliver_error_code_bit";

        inline auto is_enabled()
        { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_enabled(value_type field)
        { return is_bit_set(field, from); }

        inline auto is_enabled_if_exists(bool verbose = false)
        { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline auto is_disabled()
        { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_disabled(value_type field)
        { return is_bit_cleared(field, from); }

        inline auto is_disabled_if_exists(bool verbose = false)
        { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subbool(level, msg); }
    }

    namespace nmi_unblocking_due_to_iret
    {
        constexpr const auto mask = 0x00001000ULL;
        constexpr const auto from = 12ULL;
        constexpr const auto name = "nmi_unblocking_due_to_iret";

        inline auto is_enabled()
        { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_enabled(value_type field)
        { return is_bit_set(field, from); }

        inline auto is_enabled_if_exists(bool verbose = false)
        { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline auto is_disabled()
        { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_disabled(value_type field)
        { return is_bit_cleared(field, from); }

        inline auto is_disabled_if_exists(bool verbose = false)
        { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subbool(level, msg); }
    }

    namespace reserved
    {
        constexpr const auto mask = 0x7FFFE000ULL;
        constexpr const auto from = 0ULL;
        constexpr const auto name = "reserved";

        inline auto get()
        { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

        inline auto get(value_type field)
        { return get_bits(field, mask) >> from; }

        inline auto get_if_exists(bool verbose = false)
        { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subnhex(level, msg); }
    }

    namespace valid_bit
    {
        constexpr const auto mask = 0x80000000ULL;
        constexpr const auto from = 31ULL;
        constexpr const auto name = "valid_bit";

        inline auto is_enabled()
        { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_enabled(value_type field)
        { return is_bit_set(field, from); }

        inline auto is_enabled_if_exists(bool verbose = false)
        { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline auto is_disabled()
        { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_disabled(value_type field)
        { return is_bit_cleared(field, from); }

        inline auto is_disabled_if_exists(bool verbose = false)
        { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subbool(level, msg); }
    }

    inline void dump(int level, std::string *msg = nullptr)
    {
        dump_vmcs_nhex(level, msg);
        vector::dump(level, msg);
        interruption_type::dump(level, msg);
        error_code_valid::dump(level, msg);
        nmi_unblocking_due_to_iret::dump(level, msg);
        reserved::dump(level, msg);
        valid_bit::dump(level, msg);
    }
}

namespace vmexit_interruption_error_code
{
    constexpr const auto addr = 0x0000000000004406ULL;
    constexpr const auto name = "vmexit_interruption_error_code";

    inline auto exists()
    { return true; }

    inline auto get()
    { return get_vmcs_field(addr, name, exists()); }

    inline auto get_if_exists(bool verbose = false)
    { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

    inline void dump(int level, std::string *msg = nullptr)
    { dump_vmcs_nhex(level, msg); }
}

namespace idt_vectoring_info
{
    constexpr const auto addr = 0x0000000000004408ULL;
    constexpr const auto name = "idt_vectoring_info_field";

    inline auto exists()
    { return true; }

    inline auto get()
    { return get_vmcs_field(addr, name, exists()); }

    inline auto get_if_exists(bool verbose = false)
    { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

    namespace vector
    {
        constexpr const auto mask = 0x000000FFULL;
        constexpr const auto from = 0ULL;
        constexpr const auto name = "vector";

        inline auto get()
        { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

        inline auto get(value_type field)
        { return get_bits(field, mask) >> from; }

        inline auto get_if_exists(bool verbose = false)
        { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subnhex(level, msg); }
    }

    namespace interruption_type
    {
        constexpr const auto mask = 0x00000700ULL;
        constexpr const auto from = 8ULL;
        constexpr const auto name = "interruption_type";

        constexpr const auto external_int = 0ULL;
        constexpr const auto non_maskable_int = 2ULL;
        constexpr const auto hardware_exception = 3ULL;
        constexpr const auto software_int = 4ULL;
        constexpr const auto privileged_software_exception = 5ULL;
        constexpr const auto software_exception = 6ULL;

        inline auto get()
        { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

        inline auto get(value_type field)
        { return get_bits(field, mask) >> from; }

        inline auto get_if_exists(bool verbose = false)
        { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subnhex(level, msg); }
    }

    namespace error_code_valid
    {
        constexpr const auto mask = 0x00000800ULL;
        constexpr const auto from = 11ULL;
        constexpr const auto name = "deliver_error_code_bit";

        inline auto is_enabled()
        { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_enabled(value_type field)
        { return is_bit_set(field, from); }

        inline auto is_enabled_if_exists(bool verbose = false)
        { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline auto is_disabled()
        { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_disabled(value_type field)
        { return is_bit_cleared(field, from); }

        inline auto is_disabled_if_exists(bool verbose = false)
        { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subbool(level, msg); }
    }

    namespace reserved
    {
        constexpr const auto mask = 0x7FFFE000ULL;
        constexpr const auto from = 0ULL;
        constexpr const auto name = "reserved";

        inline auto get()
        { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

        inline auto get(value_type field)
        { return get_bits(field, mask) >> from; }

        inline auto get_if_exists(bool verbose = false)
        { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subnhex(level, msg); }
    }

    namespace valid_bit
    {
        constexpr const auto mask = 0x80000000ULL;
        constexpr const auto from = 31ULL;
        constexpr const auto name = "valid_bit";

        inline auto is_enabled()
        { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_enabled(value_type field)
        { return is_bit_set(field, from); }

        inline auto is_enabled_if_exists(bool verbose = false)
        { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline auto is_disabled()
        { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

        inline auto is_disabled(value_type field)
        { return is_bit_cleared(field, from); }

        inline auto is_disabled_if_exists(bool verbose = false)
        { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

        inline void dump(int level, std::string *msg = nullptr)
        { dump_vmcs_subbool(level, msg); }
    }

    inline void dump(int level, std::string *msg = nullptr)
    {
        dump_vmcs_nhex(level, msg);
        vector::dump(level, msg);
        interruption_type::dump(level, msg);
        error_code_valid::dump(level, msg);
        reserved::dump(level, msg);
        valid_bit::dump(level, msg);
    }
}

namespace idt_vectoring_error_code
{
    constexpr const auto addr = 0x000000000000440AULL;
    constexpr const auto name = "idt_vectoring_error_code";

    inline auto exists()
    { return true; }

    inline auto get()
    { return get_vmcs_field(addr, name, exists()); }

    inline auto get_if_exists(bool verbose = false)
    { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

    inline void dump(int level, std::string *msg = nullptr)
    { dump_vmcs_nhex(level, msg); }
}

namespace vmexit_instr_len
{
    constexpr const auto addr = 0x000000000000440CULL;
    constexpr const auto name = "vmexit_instr_len";

    inline auto exists()
    { return true; }

    inline auto get()
    { return get_vmcs_field(addr, name, exists()); }

    inline auto get_if_exists(bool verbose = false)
    { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

    inline void dump(int level, std::string *msg = nullptr)
    { dump_vmcs_nhex(level, msg); }
}

namespace vmexit_instr_info
{
    constexpr const auto addr = 0x000000000000440EULL;
    constexpr const auto name = "vmexit_instr_info";

    inline auto exists()
    { return true; }

    inline auto get()
    { return get_vmcs_field(addr, name, exists()); }

    inline auto get_if_exists(bool verbose = false)
    { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

    inline void dump(int level, std::string *msg = nullptr)
    { dump_vmcs_nhex(level, msg); }

    namespace ins
    {
        constexpr const auto name = "ins";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            addr_size::dump(level, msg);
        }
    }

    namespace outs
    {
        constexpr const auto name = "outs";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
        }
    }

    namespace invept
    {
        constexpr const auto name = "invept";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace reg2
        {
            constexpr const auto mask = 0x00000000F0000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "reg2";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            reg2::dump(level, msg);
        }
    }

    namespace invpcid
    {
        constexpr const auto name = "invpcid";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace reg2
        {
            constexpr const auto mask = 0x00000000F0000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "reg2";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            reg2::dump(level, msg);
        }
    }

    namespace invvpid
    {
        constexpr const auto name = "invvpid";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace reg2
        {
            constexpr const auto mask = 0x00000000F0000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "reg2";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            reg2::dump(level, msg);
        }
    }

    namespace lidt
    {
        constexpr const auto name = "lidt";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace operand_size
        {
            constexpr const auto mask = 0x0000000000000800ULL;
            constexpr const auto from = 11ULL;
            constexpr const auto name = "operand_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace instr_identity
        {
            constexpr const auto mask = 0x0000000030000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "instr_identity";

            constexpr const auto sgdt = 0UL;
            constexpr const auto sidt = 1UL;
            constexpr const auto lgdt = 2UL;
            constexpr const auto lidt = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            operand_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            instr_identity::dump(level, msg);
        }
    }

    namespace lgdt
    {
        constexpr const auto name = "lgdt";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace operand_size
        {
            constexpr const auto mask = 0x0000000000000800ULL;
            constexpr const auto from = 11ULL;
            constexpr const auto name = "operand_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace instr_identity
        {
            constexpr const auto mask = 0x0000000030000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "instr_identity";

            constexpr const auto sgdt = 0UL;
            constexpr const auto sidt = 1UL;
            constexpr const auto lgdt = 2UL;
            constexpr const auto lidt = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            operand_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            instr_identity::dump(level, msg);
        }
    }

    namespace sidt
    {
        constexpr const auto name = "sidt";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace operand_size
        {
            constexpr const auto mask = 0x0000000000000800ULL;
            constexpr const auto from = 11ULL;
            constexpr const auto name = "operand_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace instr_identity
        {
            constexpr const auto mask = 0x0000000030000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "instr_identity";

            constexpr const auto sgdt = 0UL;
            constexpr const auto sidt = 1UL;
            constexpr const auto lgdt = 2UL;
            constexpr const auto lidt = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            operand_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            instr_identity::dump(level, msg);
        }
    }

    namespace sgdt
    {
        constexpr const auto name = "sgdt";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace operand_size
        {
            constexpr const auto mask = 0x0000000000000800ULL;
            constexpr const auto from = 11ULL;
            constexpr const auto name = "operand_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace instr_identity
        {
            constexpr const auto mask = 0x0000000030000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "instr_identity";

            constexpr const auto sgdt = 0UL;
            constexpr const auto sidt = 1UL;
            constexpr const auto lgdt = 2UL;
            constexpr const auto lidt = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            operand_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            instr_identity::dump(level, msg);
        }
    }

    namespace lldt
    {
        constexpr const auto name = "lldt";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace reg1
        {
            constexpr const auto mask = 0x0000000000000078ULL;
            constexpr const auto from = 3ULL;
            constexpr const auto name = "reg1";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace mem_reg
        {
            constexpr const auto mask = 0x0000000000000400ULL;
            constexpr const auto from = 10ULL;
            constexpr const auto name = "mem/reg";

            constexpr const auto mem = 0UL;
            constexpr const auto reg = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace instr_identity
        {
            constexpr const auto mask = 0x0000000030000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "instr_identity";

            constexpr const auto sldt = 0UL;
            constexpr const auto str = 1UL;
            constexpr const auto lldt = 2UL;
            constexpr const auto ltr = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            reg1::dump(level, msg);
            addr_size::dump(level, msg);
            mem_reg::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            instr_identity::dump(level, msg);
        }
    }

    namespace ltr
    {
        constexpr const auto name = "ltr";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace reg1
        {
            constexpr const auto mask = 0x0000000000000078ULL;
            constexpr const auto from = 3ULL;
            constexpr const auto name = "reg1";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace mem_reg
        {
            constexpr const auto mask = 0x0000000000000400ULL;
            constexpr const auto from = 10ULL;
            constexpr const auto name = "mem/reg";

            constexpr const auto mem = 0UL;
            constexpr const auto reg = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace instr_identity
        {
            constexpr const auto mask = 0x0000000030000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "instr_identity";

            constexpr const auto sldt = 0UL;
            constexpr const auto str = 1UL;
            constexpr const auto lldt = 2UL;
            constexpr const auto ltr = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            reg1::dump(level, msg);
            addr_size::dump(level, msg);
            mem_reg::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            instr_identity::dump(level, msg);
        }
    }

    namespace sldt
    {
        constexpr const auto name = "sldt";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace reg1
        {
            constexpr const auto mask = 0x0000000000000078ULL;
            constexpr const auto from = 3ULL;
            constexpr const auto name = "reg1";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace mem_reg
        {
            constexpr const auto mask = 0x0000000000000400ULL;
            constexpr const auto from = 10ULL;
            constexpr const auto name = "mem/reg";

            constexpr const auto mem = 0UL;
            constexpr const auto reg = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace instr_identity
        {
            constexpr const auto mask = 0x0000000030000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "instr_identity";

            constexpr const auto sldt = 0UL;
            constexpr const auto str = 1UL;
            constexpr const auto lldt = 2UL;
            constexpr const auto ltr = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            reg1::dump(level, msg);
            addr_size::dump(level, msg);
            mem_reg::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            instr_identity::dump(level, msg);
        }
    }

    namespace str
    {
        constexpr const auto name = "str";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace reg1
        {
            constexpr const auto mask = 0x0000000000000078ULL;
            constexpr const auto from = 3ULL;
            constexpr const auto name = "reg1";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace mem_reg
        {
            constexpr const auto mask = 0x0000000000000400ULL;
            constexpr const auto from = 10ULL;
            constexpr const auto name = "mem/reg";

            constexpr const auto mem = 0UL;
            constexpr const auto reg = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace instr_identity
        {
            constexpr const auto mask = 0x0000000030000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "instr_identity";

            constexpr const auto sldt = 0UL;
            constexpr const auto str = 1UL;
            constexpr const auto lldt = 2UL;
            constexpr const auto ltr = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            reg1::dump(level, msg);
            addr_size::dump(level, msg);
            mem_reg::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            instr_identity::dump(level, msg);
        }
    }

    namespace rdrand
    {
        constexpr const auto name = "rdrand";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace destination_register
        {
            constexpr const auto mask = 0x0000000000000078ULL;
            constexpr const auto from = 3ULL;
            constexpr const auto name = "destination_register";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace operand_size
        {
            constexpr const auto mask = 0x0000000000001800ULL;
            constexpr const auto from = 11ULL;
            constexpr const auto name = "operand_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            destination_register::dump(level, msg);
            operand_size::dump(level, msg);
        }
    }

    namespace rdseed
    {
        constexpr const auto name = "rdseed";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace destination_register
        {
            constexpr const auto mask = 0x0000000000000078ULL;
            constexpr const auto from = 3ULL;
            constexpr const auto name = "destination_register";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace operand_size
        {
            constexpr const auto mask = 0x0000000000001800ULL;
            constexpr const auto from = 11ULL;
            constexpr const auto name = "operand_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            destination_register::dump(level, msg);
            operand_size::dump(level, msg);
        }
    }

    namespace vmclear
    {
        constexpr const auto name = "vmclear";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
        }
    }

    namespace vmptrld
    {
        constexpr const auto name = "vmptrld";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
        }
    }

    namespace vmptrst
    {
        constexpr const auto name = "vmptrst";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
        }
    }

    namespace vmxon
    {
        constexpr const auto name = "vmxon";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
        }
    }

    namespace xrstors
    {
        constexpr const auto name = "xrstors";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
        }
    }

    namespace xsaves
    {
        constexpr const auto name = "xsaves";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            addr_size::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
        }
    }

    namespace vmread
    {
        constexpr const auto name = "vmread";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace reg1
        {
            constexpr const auto mask = 0x0000000000000078ULL;
            constexpr const auto from = 3ULL;
            constexpr const auto name = "reg1";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace mem_reg
        {
            constexpr const auto mask = 0x0000000000000400ULL;
            constexpr const auto from = 10ULL;
            constexpr const auto name = "mem/reg";

            constexpr const auto mem = 0UL;
            constexpr const auto reg = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace reg2
        {
            constexpr const auto mask = 0x00000000F0000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "reg2";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            reg1::dump(level, msg);
            addr_size::dump(level, msg);
            mem_reg::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            reg2::dump(level, msg);
        }
    }

    namespace vmwrite
    {
        constexpr const auto name = "vmwrite";

        inline auto get()
        { return get_vmcs_field(addr, name, exists()); }

        inline auto get_if_exists(bool verbose = false)
        { return get_vmcs_field_if_exists(addr, name, verbose, exists()); }

        namespace scaling
        {
            constexpr const auto mask = 0x0000000000000003ULL;
            constexpr const auto from = 0ULL;
            constexpr const auto name = "scaling";

            constexpr const auto no_scaling = 0UL;
            constexpr const auto scale_by_2 = 1UL;
            constexpr const auto scale_by_4 = 2UL;
            constexpr const auto scale_by_8 = 3UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace reg1
        {
            constexpr const auto mask = 0x0000000000000078ULL;
            constexpr const auto from = 3ULL;
            constexpr const auto name = "reg1";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace addr_size
        {
            constexpr const auto mask = 0x0000000000000380ULL;
            constexpr const auto from = 7ULL;
            constexpr const auto name = "addr_size";

            constexpr const auto _16bit = 0UL;
            constexpr const auto _32bit = 1UL;
            constexpr const auto _64bit = 2UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace mem_reg
        {
            constexpr const auto mask = 0x0000000000000400ULL;
            constexpr const auto from = 10ULL;
            constexpr const auto name = "mem/reg";

            constexpr const auto mem = 0UL;
            constexpr const auto reg = 1UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace segment_register
        {
            constexpr const auto mask = 0x0000000000038000ULL;
            constexpr const auto from = 15ULL;
            constexpr const auto name = "segment_register";

            constexpr const auto es = 0UL;
            constexpr const auto cs = 1UL;
            constexpr const auto ss = 2UL;
            constexpr const auto ds = 3UL;
            constexpr const auto fs = 4UL;
            constexpr const auto gs = 5UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg
        {
            constexpr const auto mask = 0x00000000003C0000ULL;
            constexpr const auto from = 18ULL;
            constexpr const auto name = "index_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace index_reg_invalid
        {
            constexpr const auto mask = 0x0000000000400000ULL;
            constexpr const auto from = 22ULL;
            constexpr const auto name = "index_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace base_reg
        {
            constexpr const auto mask = 0x0000000007800000ULL;
            constexpr const auto from = 23ULL;
            constexpr const auto name = "base_reg";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        namespace base_reg_invalid
        {
            constexpr const auto mask = 0x0000000008000000ULL;
            constexpr const auto from = 27ULL;
            constexpr const auto name = "base_reg_invalid";

            inline auto is_enabled()
            { return is_bit_set(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_enabled(value_type field)
            { return is_bit_set(field, from); }

            inline auto is_enabled_if_exists(bool verbose = false)
            { return is_bit_set(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline auto is_disabled()
            { return is_bit_cleared(get_vmcs_field(addr, name, exists()), from); }

            inline auto is_disabled(value_type field)
            { return is_bit_cleared(field, from); }

            inline auto is_disabled_if_exists(bool verbose = false)
            { return is_bit_cleared(get_vmcs_field_if_exists(addr, name, verbose, exists()), from); }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subbool(level, msg); }
        }

        namespace reg2
        {
            constexpr const auto mask = 0x00000000F0000000ULL;
            constexpr const auto from = 28ULL;
            constexpr const auto name = "reg2";

            constexpr const auto rax = 0UL;
            constexpr const auto rcx = 1UL;
            constexpr const auto rdx = 2UL;
            constexpr const auto rbx = 3UL;
            constexpr const auto rsp = 4UL;
            constexpr const auto rbp = 5UL;
            constexpr const auto rsi = 6UL;
            constexpr const auto rdi = 7UL;
            constexpr const auto r8 = 8UL;
            constexpr const auto r9 = 9UL;
            constexpr const auto r10 = 10UL;
            constexpr const auto r11 = 11UL;
            constexpr const auto r12 = 12UL;
            constexpr const auto r13 = 13UL;
            constexpr const auto r14 = 14UL;
            constexpr const auto r15 = 15UL;

            inline auto get()
            { return get_bits(get_vmcs_field(addr, name, exists()), mask) >> from; }

            inline auto get(value_type field)
            { return get_bits(field, mask) >> from; }

            inline auto get_if_exists(bool verbose = false)
            { return get_bits(get_vmcs_field_if_exists(addr, name, verbose, exists()), mask) >> from; }

            inline void dump(int level, std::string *msg = nullptr)
            { dump_vmcs_subnhex(level, msg); }
        }

        inline void dump(int level, std::string *msg = nullptr)
        {
            dump_vmcs_nhex(level, msg);
            scaling::dump(level, msg);
            reg1::dump(level, msg);
            addr_size::dump(level, msg);
            mem_reg::dump(level, msg);
            segment_register::dump(level, msg);
            index_reg::dump(level, msg);
            index_reg_invalid::dump(level, msg);
            base_reg::dump(level, msg);
            base_reg_invalid::dump(level, msg);
            reg2::dump(level, msg);
        }
    }
}

}

// *INDENT-ON*

#endif
