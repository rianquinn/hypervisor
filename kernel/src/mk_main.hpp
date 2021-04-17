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

#ifndef MK_MAIN_HPP
#define MK_MAIN_HPP

#include <mk_interface.hpp>
#include <vmexit_loop_entry.hpp>

#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/exit_code.hpp>
#include <bsl/finally.hpp>
#include <bsl/touch.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// @class mk::mk_main
    ///
    /// <!-- description -->
    ///   @brief Provide the main entry point for the microkernel. The
    ///     microkernel actually starts in the _start function, and immediately
    ///     creates this class and calls its process() function to boot the
    ///     microkernel, start the extensions and eventually demote the CPU.
    ///     Like the other main classes, this class serves to encapsulate
    ///     the entry logic into something that can be easily tested with no
    ///     dependencies on global resources.
    ///
    /// <!-- template parameters -->
    ///   @tparam INTRINSIC_CONCEPT defines the type of intrinsics to use
    ///   @tparam PAGE_POOL_CONCEPT defines the type of page pool to use
    ///   @tparam HUGE_POOL_CONCEPT defines the type of huge pool to use
    ///   @tparam ROOT_PAGE_TABLE_CONCEPT defines the type of RPT pool to use
    ///   @tparam VPS_POOL_CONCEPT defines the type of VPS pool to use
    ///   @tparam VP_POOL_CONCEPT defines the type of VP pool to use
    ///   @tparam VM_POOL_CONCEPT defines the type of VM pool to use
    ///   @tparam EXT_POOL_CONCEPT defines the type of extension pool to use
    ///   @tparam PAGE_SIZE defines the size of a page
    ///   @tparam EXT_STACK_ADDR the address of the extension's stack
    ///   @tparam EXT_STACK_SIZE the size of the extension's stack
    ///   @tparam EXT_TLS_ADDR the address of the extension's TLS block
    ///   @tparam EXT_TLS_SIZE the size of the extension's TLS block
    ///
    template<
        typename INTRINSIC_CONCEPT,
        typename PAGE_POOL_CONCEPT,
        typename HUGE_POOL_CONCEPT,
        typename ROOT_PAGE_TABLE_CONCEPT,
        typename VPS_POOL_CONCEPT,
        typename VP_POOL_CONCEPT,
        typename VM_POOL_CONCEPT,
        typename EXT_POOL_CONCEPT,
        bsl::uintmax PAGE_SIZE,
        bsl::uintmax EXT_STACK_ADDR,
        bsl::uintmax EXT_STACK_SIZE,
        bsl::uintmax EXT_TLS_ADDR,
        bsl::uintmax EXT_TLS_SIZE>
    class mk_main final
    {
        /// @brief stores a reference to the intrinsics to use
        INTRINSIC_CONCEPT &m_intrinsic;
        /// @brief stores a reference to the page pool to use
        PAGE_POOL_CONCEPT &m_page_pool;
        /// @brief stores a reference to the huge pool to use
        HUGE_POOL_CONCEPT &m_huge_pool;
        /// @brief stores system RPT provided by the loader
        ROOT_PAGE_TABLE_CONCEPT &m_system_rpt;
        /// @brief stores a reference to the VPS pool to use
        VPS_POOL_CONCEPT &m_vps_pool;
        /// @brief stores a reference to the VP pool to use
        VP_POOL_CONCEPT &m_vp_pool;
        /// @brief stores a reference to the VM pool to use
        VM_POOL_CONCEPT &m_vm_pool;
        /// @brief stores a reference to the extension pool to use
        EXT_POOL_CONCEPT &m_ext_pool;

        /// @brief stores the extension pool's initialization status
        bool m_initialized;

        /// <!-- description -->
        ///   @brief Sets the extension stack pointer given a TLS block,
        ///     based on what PP we are currently executing on.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        set_extension_sp(TLS_CONCEPT &tls) noexcept
        {
            constexpr bsl::safe_uintmax stack_addr{EXT_STACK_ADDR};
            constexpr bsl::safe_uintmax stack_size{EXT_STACK_SIZE};

            auto const offs{(stack_size + PAGE_SIZE) * bsl::to_umax(tls.ppid)};
            tls.sp = (stack_addr + offs + stack_size).get();
        }

        /// <!-- description -->
        ///   @brief Sets the extension TLS pointer given a TLS block,
        ///     based on what PP we are currently executing on.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///
        template<typename TLS_CONCEPT>
        constexpr void
        set_extension_tp(TLS_CONCEPT &tls) noexcept
        {
            constexpr bsl::safe_uintmax tls_addr{EXT_TLS_ADDR};
            constexpr bsl::safe_uintmax tls_size{EXT_TLS_SIZE};

            auto const offs{(tls_size + PAGE_SIZE) * bsl::to_umax(tls.ppid)};
            tls.tp = (tls_addr + offs + PAGE_SIZE).get();

            m_intrinsic.set_tp(tls.tp);
        }

    public:
        /// @brief an alias for INTRINSIC_CONCEPT
        using intrinsic_type = INTRINSIC_CONCEPT;
        /// @brief an alias for PAGE_POOL_CONCEPT
        using page_pool_type = PAGE_POOL_CONCEPT;
        /// @brief an alias for HUGE_POOL_CONCEPT
        using huge_pool_type = HUGE_POOL_CONCEPT;
        /// @brief an alias for ROOT_PAGE_TABLE_CONCEPT
        using root_page_table_type = ROOT_PAGE_TABLE_CONCEPT;
        /// @brief an alias for VPS_POOL_CONCEPT
        using vps_pool_type = VPS_POOL_CONCEPT;
        /// @brief an alias for VP_POOL_CONCEPT
        using vp_pool_type = VP_POOL_CONCEPT;
        /// @brief an alias for VM_POOL_CONCEPT
        using vm_pool_type = VM_POOL_CONCEPT;
        /// @brief an alias for EXT_POOL_CONCEPT
        using ext_pool_type = EXT_POOL_CONCEPT;

        /// <!-- description -->
        ///   @brief Creates the microkernel's main class given the global
        ///     resources that the microkernel will rely on.
        ///
        /// <!-- inputs/outputs -->
        ///   @param intrinsic the intrinsics to use
        ///   @param page_pool the page pool to use
        ///   @param huge_pool the huge pool to use
        ///   @param system_rpt the system RPT provided by the loader
        ///   @param vps_pool the vps pool to use
        ///   @param vp_pool the vp pool to use
        ///   @param vm_pool the vm pool to use
        ///   @param ext_pool the extension pool to use
        ///
        constexpr mk_main(
            INTRINSIC_CONCEPT &intrinsic,
            PAGE_POOL_CONCEPT &page_pool,
            HUGE_POOL_CONCEPT &huge_pool,
            ROOT_PAGE_TABLE_CONCEPT &system_rpt,
            VPS_POOL_CONCEPT &vps_pool,
            VP_POOL_CONCEPT &vp_pool,
            VM_POOL_CONCEPT &vm_pool,
            EXT_POOL_CONCEPT &ext_pool) noexcept
            : m_intrinsic{intrinsic}
            , m_page_pool{page_pool}
            , m_huge_pool{huge_pool}
            , m_system_rpt{system_rpt}
            , m_vps_pool{vps_pool}
            , m_vp_pool{vp_pool}
            , m_vm_pool{vm_pool}
            , m_ext_pool{ext_pool}
            , m_initialized{}
        {}

        /// <!-- description -->
        ///   @brief Initialize all of the global resources the microkernel
        ///     depends on.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam MK_ARGS_CONCEPT the type of mk_args to use
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param args the loader provided arguments to the microkernel.
        ///   @param tls the current TLS block
        ///   @return If the user provided command succeeds, this function
        ///     will return bsl::exit_success, otherwise this function
        ///     will return bsl::exit_failure.
        ///
        template<typename MK_ARGS_CONCEPT, typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        initialize(MK_ARGS_CONCEPT *const args, TLS_CONCEPT &tls) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            if (m_initialized) {
                ret = m_system_rpt.activate();
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::errc_failure;
                }

                return bsl::errc_success;
            }

            bsl::print() << bsl::mag;
            bsl::print() << " ___                __ _           _         \n";
            bsl::print() << "| _ ) __ _ _ _ ___ / _| |__ _ _ _ | |__      \n";
            bsl::print() << "| _ \\/ _` | '_/ -_)  _| / _` | ' \\| / /    \n";
            bsl::print() << "|___/\\__,_|_| \\___|_| |_\\__,_|_||_|_\\_\\ \n";
            bsl::print() << "\n";
            bsl::print() << bsl::grn;
            bsl::print() << "Please give us a star on: ";
            bsl::print() << bsl::rst;
            bsl::print() << "https://github.com/Bareflank/hypervisor\n";
            bsl::print() << bsl::rst;
            bsl::print() << "=================================";
            bsl::print() << "=================================";
            bsl::print() << "\n";
            bsl::print() << "\n";

            ret = m_page_pool.initialize(args->page_pool);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_huge_pool.initialize(args->huge_pool);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_system_rpt.initialize(&m_intrinsic, &m_page_pool, &m_huge_pool);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_system_rpt.add_tables(args->rpt);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_system_rpt.activate();
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_vps_pool.initialize();
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_vp_pool.initialize();
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_vm_pool.initialize();
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_ext_pool.initialize(tls, args->ext_elf_files);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_ext_pool.start(tls);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_initialized = true;
            return bsl::errc_success;
        }

        /// <!-- description -->
        ///   @brief Process the mk_args_t provided by the loader.
        ///     If the user provided command succeeds, this function
        ///     will return bsl::exit_success, otherwise this function
        ///     will return bsl::exit_failure.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam MK_ARGS_CONCEPT the type of mk_args to use
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param args the loader provided arguments to the microkernel.
        ///   @param tls the current TLS block
        ///   @return If the user provided command succeeds, this function
        ///     will return bsl::exit_success, otherwise this function
        ///     will return bsl::exit_failure.
        ///
        template<typename MK_ARGS_CONCEPT, typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        process(MK_ARGS_CONCEPT *const args, TLS_CONCEPT &tls) &noexcept -> bsl::exit_code
        {
            set_extension_sp(tls);
            set_extension_tp(tls);

            /// TODO:
            /// - Verify the incomings args. Right now this is a non-issue as
            ///   we control the loader, but at some point we might want to
            ///   support third-party loaders, and this could be an issue
            ///

            if (bsl::unlikely(!this->initialize(args, tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::exit_failure;
            }

            if (bsl::unlikely(!m_ext_pool.bootstrap(tls))) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::exit_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == tls.active_vmid)) {
                bsl::error() << "bf_vps_op_run was never executed by an extension"    // --
                             << bsl::endl                                             // --
                             << bsl::here();                                          // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == tls.active_vpid)) {
                bsl::error() << "bf_vps_op_run was never executed by an extension"    // --
                             << bsl::endl                                             // --
                             << bsl::here();                                          // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == tls.active_vpsid)) {
                bsl::error() << "bf_vps_op_run was never executed by an extension"    // --
                             << bsl::endl                                             // --
                             << bsl::here();                                          // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely(nullptr == tls.ext_vmexit)) {
                bsl::error() << "a vmexit handler has not been registered"    // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely(nullptr == tls.ext_fail)) {
                bsl::error() << "a fast fail handler has not been registered"    // --
                             << bsl::endl                                        // --
                             << bsl::here();                                     // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely(vmexit_loop_entry() != bsl::exit_success)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::exit_failure;
            }

            return bsl::exit_success;

            // [ ] implement checks for which MSRs can be read/written
            // [ ] implement checks for VMCS fields can be read/written
            // [ ] implement contants for all of the asm logic
            // [ ] implement configuration validation
        }
    };
}

#endif
