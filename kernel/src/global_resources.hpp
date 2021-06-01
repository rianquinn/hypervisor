/// @copyright
/// Copyright (C) 2020 Assured Information Security, Inc.
///
/// @copyright
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// @copyright
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// @copyright
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

#ifndef GLOBAL_RESOURCES_HPP
#define GLOBAL_RESOURCES_HPP

#include <ext_pool_t.hpp>
#include <ext_t.hpp>
#include <huge_pool_t.hpp>
#include <intrinsic_t.hpp>
#include <mk_main.hpp>
#include <page_pool_t.hpp>
#include <root_page_table_t.hpp>
#include <tls_t.hpp>
#include <vm_pool_t.hpp>
#include <vm_t.hpp>
#include <vmexit_log_t.hpp>
#include <vp_pool_t.hpp>
#include <vp_t.hpp>
#include <vps_pool_t.hpp>
#include <vps_t.hpp>

/// NOTE:
/// - Do not include this file. The only files that should include this
///   one are main entry points (like _start, a trampoline, etc...).
///   Instead, define a template and get these types through a template
///   type. This ensures testing is simple.
///

extern "C"
{
    /// @brief stores the TLS blocks used by the microkernel.
    // These are buggy as this is an extern
    // NOLINTNEXTLINE(bsl-non-pod-static, bsl-var-braced-init)
    extern bsl::array<mk::tls_t, bsl::to_umax(HYPERVISOR_MAX_PPS).get()> g_tls_blocks;
}

// bsl::to_umax(HYPERVISOR_VMEXIT_LOG_SIZE).get()

namespace mk
{
    /// @brief defines the TLS pool type to use
    using mk_vmexit_log_type = vmexit_log_t<               // --
        bsl::to_umax(HYPERVISOR_VMEXIT_LOG_SIZE).get(),    // --
        bsl::to_umax(HYPERVISOR_MAX_PPS).get()>;           // --

    /// @brief defines the intrinsic type
    using mk_intrinsic_type = intrinsic_t;

    /// @brief defines the page pool type
    using mk_page_pool_type = page_pool_t<                    // --
        bsl::to_umax(HYPERVISOR_PAGE_SIZE).get(),             // --
        bsl::to_umax(HYPERVISOR_MK_PAGE_POOL_ADDR).get()>;    // --

    /// @brief defines the huge pool type
    using mk_huge_pool_type = huge_pool_t<                    // --
        bsl::to_umax(HYPERVISOR_PAGE_SIZE).get(),             // --
        bsl::to_umax(HYPERVISOR_MK_HUGE_POOL_ADDR).get()>;    // --

    /// @brief defines the VPS type to use
    using mk_vps_type = vps_t;    // --

    /// @brief defines the VPS pool type to use
    using mk_vps_pool_type = vps_pool_t<             // --
        mk_vps_type,                                 // --
        bsl::to_umax(HYPERVISOR_MAX_VPSS).get()>;    // --

    /// @brief defines the VP type to use
    using mk_vp_type = vp_t;    // --

    /// @brief defines the VP pool type to use
    using mk_vp_pool_type = vp_pool_t<              // --
        mk_vp_type,                                 // --
        bsl::to_umax(HYPERVISOR_MAX_VPS).get()>;    // --

    /// @brief defines the VM type to use
    using mk_vm_type = vm_t<                        // --
        bsl::to_umax(HYPERVISOR_MAX_PPS).get()>;    // --

    /// @brief defines the VM pool type to use
    using mk_vm_pool_type = vm_pool_t<              // --
        mk_vm_type,                                 // --
        bsl::to_umax(HYPERVISOR_MAX_VMS).get()>;    // --

    /// @brief defines the root page table type
    using mk_root_page_table_type = root_page_table_t<    // --
        mk_intrinsic_type,                                // --
        mk_page_pool_type,                                // --
        mk_huge_pool_type,                                // --
        bsl::to_umax(HYPERVISOR_PAGE_SIZE).get(),         // --
        bsl::to_umax(HYPERVISOR_PAGE_SHIFT).get()>;       // --

    /// @brief defines the extension type to use
    using mk_ext_type = ext_t<                                 // --
        mk_intrinsic_type,                                     // --
        mk_page_pool_type,                                     // --
        mk_huge_pool_type,                                     // --
        mk_root_page_table_type,                               // --
        bsl::to_umax(HYPERVISOR_PAGE_SIZE).get(),              // --
        bsl::to_umax(HYPERVISOR_MAX_PPS).get(),                // --
        bsl::to_umax(HYPERVISOR_MAX_VMS).get(),                // --
        bsl::to_umax(HYPERVISOR_EXT_DIRECT_MAP_ADDR).get(),    // --
        bsl::to_umax(HYPERVISOR_EXT_DIRECT_MAP_SIZE).get(),    // --
        bsl::to_umax(HYPERVISOR_EXT_STACK_ADDR).get(),         // --
        bsl::to_umax(HYPERVISOR_EXT_STACK_SIZE).get(),         // --
        bsl::to_umax(HYPERVISOR_EXT_CODE_ADDR).get(),          // --
        bsl::to_umax(HYPERVISOR_EXT_CODE_SIZE).get(),          // --
        bsl::to_umax(HYPERVISOR_EXT_TLS_ADDR).get(),           // --
        bsl::to_umax(HYPERVISOR_EXT_TLS_SIZE).get(),           // --
        bsl::to_umax(HYPERVISOR_EXT_PAGE_POOL_ADDR).get(),     // --
        bsl::to_umax(HYPERVISOR_EXT_PAGE_POOL_SIZE).get(),     // --
        bsl::to_umax(HYPERVISOR_EXT_HUGE_POOL_ADDR).get(),     // --
        bsl::to_umax(HYPERVISOR_EXT_HUGE_POOL_SIZE).get(),     // --
        bsl::to_umax(HYPERVISOR_EXT_HEAP_POOL_ADDR).get(),     // --
        bsl::to_umax(HYPERVISOR_EXT_HEAP_POOL_SIZE).get()>;    // --

    /// @brief defines the extension pool type to use
    using mk_ext_pool_type = ext_pool_t<                   // --
        mk_ext_type,                                       // --
        mk_intrinsic_type,                                 // --
        mk_page_pool_type,                                 // --
        mk_huge_pool_type,                                 // --
        mk_root_page_table_type,                           // --
        bsl::to_umax(HYPERVISOR_MAX_EXTENSIONS).get()>;    // --

    /// @brief defines the extension pool type to use
    using mk_main_type = mk_main<                         // --
        mk_intrinsic_type,                                // --
        mk_page_pool_type,                                // --
        mk_huge_pool_type,                                // --
        mk_root_page_table_type,                          // --
        mk_vps_pool_type,                                 // --
        mk_vp_pool_type,                                  // --
        mk_vm_pool_type,                                  // --
        mk_ext_pool_type,                                 // --
        bsl::to_umax(HYPERVISOR_PAGE_SIZE).get(),         // --
        bsl::to_umax(HYPERVISOR_MAX_PPS).get(),           // --
        bsl::to_umax(HYPERVISOR_MK_CODE_SIZE).get(),      // --
        bsl::to_umax(HYPERVISOR_EXT_CODE_SIZE).get(),     // --
        bsl::to_umax(HYPERVISOR_EXT_STACK_ADDR).get(),    // --
        bsl::to_umax(HYPERVISOR_EXT_STACK_SIZE).get(),    // --
        bsl::to_umax(HYPERVISOR_EXT_TLS_ADDR).get(),      // --
        bsl::to_umax(HYPERVISOR_EXT_TLS_SIZE).get()>;     // --

    /// @brief stores the vmexit log used by the microkernel
    constinit inline mk_vmexit_log_type g_vmexit_log{};

    /// @brief stores the intrinsics used by the microkernel
    constinit inline mk_intrinsic_type g_intrinsic{};

    /// @brief stores the page pool used by the microkernel
    constinit inline mk_page_pool_type g_page_pool{};

    /// @brief stores the huge pool used by the microkernel
    constinit inline mk_huge_pool_type g_huge_pool{};

    /// @brief stores the vps_t pool used by the microkernel
    constinit inline mk_vps_pool_type g_vps_pool{};

    /// @brief stores the vp_t pool used by the microkernel
    constinit inline mk_vp_pool_type g_vp_pool{};

    /// @brief stores the vm_t pool used by the microkernel
    constinit inline mk_vm_pool_type g_vm_pool{};

    /// @brief stores the system RPT provided by the loader
    constinit inline mk_root_page_table_type g_system_rpt{};

    /// @brief stores the ext_t pool used by the microkernel
    constinit inline mk_ext_pool_type g_ext_pool{
        g_intrinsic, g_page_pool, g_huge_pool, g_system_rpt};

    /// @brief stores the microkernel's main class
    constinit inline mk_main_type g_mk_main{
        g_intrinsic,
        g_page_pool,
        g_huge_pool,
        g_system_rpt,
        g_vps_pool,
        g_vp_pool,
        g_vm_pool,
        g_ext_pool};
}

#endif
