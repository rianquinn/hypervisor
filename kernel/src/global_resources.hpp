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
#include <huge_pool_t.hpp>
#include <intrinsic_t.hpp>
#include <mk_main_t.hpp>
#include <page_pool_t.hpp>
#include <root_page_table_t.hpp>
#include <tls_t.hpp>
#include <vm_pool_t.hpp>
#include <vmexit_log_t.hpp>
#include <vp_pool_t.hpp>
#include <vps_pool_t.hpp>

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
    /// @brief stores the vmexit log used by the microkernel
    constinit inline vmexit_log_t g_vmexit_log{};

    /// @brief stores the intrinsics used by the microkernel
    constinit inline intrinsic_t g_intrinsic{};

    /// @brief stores the page pool used by the microkernel
    constinit inline page_pool_t g_page_pool{};

    /// @brief stores the huge pool used by the microkernel
    constinit inline huge_pool_t g_huge_pool{};

    /// @brief stores the vps pool used by the microkernel
    constinit inline vps_pool_t g_vps_pool{};

    /// @brief stores the vp pool used by the microkernel
    constinit inline vp_pool_t g_vp_pool{};

    /// @brief stores the vm pool used by the microkernel
    constinit inline vm_pool_t g_vm_pool{};

    /// @brief stores the system RPT provided by the loader
    constinit inline root_page_table_t g_system_rpt{};

    /// @brief stores the ext pool used by the microkernel
    constinit inline ext_pool_t g_ext_pool{
        g_intrinsic, g_page_pool, g_huge_pool, g_system_rpt};

    /// @brief stores the microkernel's main class
    constinit inline mk_main_t g_mk_main{
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
