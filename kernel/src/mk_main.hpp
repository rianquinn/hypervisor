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
#include <bsl/finally_assert.hpp>
#include <bsl/touch.hpp>
#include <bsl/unlikely.hpp>
#include <bsl/unlikely_assert.hpp>

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
    ///   @tparam MAX_PPS the max number of PPs supported
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
        bsl::uintmax MAX_PPS,
        bsl::uintmax MK_CODE_SIZE,
        bsl::uintmax EXT_CODE_SIZE,
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

        /// @brief stores the root VMID
        bsl::safe_uint16 m_root_vmid;
        /// @brief stores the registered VMExit handler
        void *m_ext_vmexit{};
        /// @brief stores the registered fast fail handler
        void *m_ext_fail{};

        /// <!-- description -->
        ///   @brief Verifies that the args and the resulting TLS block
        ///     make sense. The trampoline code has to fill in a lot of
        ///     the TLS block to bootstrap, so this provides some simple
        ///     sanity checks where possible.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam MK_ARGS_CONCEPT the type of mk_args to use
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param args the loader provided arguments to the microkernel.
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename MK_ARGS_CONCEPT, typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        verify_args(MK_ARGS_CONCEPT *const args, TLS_CONCEPT const &tls) noexcept -> bsl::errc_type
        {
            if (args->ppid == syscall::BF_BS_PPID) {
                if (bsl::unlikely_assert(syscall::BF_INVALID_ID != tls.active_vmid)) {
                    bsl::error() << "cannot initialize the BSP more than once"    // --
                                 << bsl::endl                                     // --
                                 << bsl::here();                                  // --

                    return bsl::errc_failure;
                }

                bsl::touch();
            }
            else {
                if (bsl::unlikely_assert(syscall::BF_INVALID_ID != tls.active_vmid)) {
                    bsl::error() << "cannot initialize the AP more than once"    // --
                                 << bsl::endl                                    // --
                                 << bsl::here();                                 // --

                    return bsl::errc_failure;
                }

                if (bsl::unlikely_assert(!m_root_vmid)) {
                    bsl::error() << "cannot initialize an AP due to previous failure"    // --
                                 << bsl::endl                                            // --
                                 << bsl::here();                                         // --

                    return bsl::errc_failure;
                }

                bsl::touch();
            }

            if (bsl::unlikely_assert(tls.ppid != args->ppid)) {
                bsl::error() << "tls.ppid ["                          // --
                             << bsl::hex(tls.ppid)                    // --
                             << "] doesn't match the args->ppid ["    // --
                             << bsl::hex(args->ppid)                  // --
                             << "]"                                   // --
                             << bsl::endl                             // --
                             << bsl::here();                          // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(syscall::BF_INVALID_ID == tls.ppid)) {
                bsl::error() << "tls.ppid ["                          // --
                             << bsl::hex(tls.ppid)                    // --
                             << "] doesn't match the args->ppid ["    // --
                             << bsl::hex(args->ppid)                  // --
                             << "]"                                   // --
                             << bsl::endl                             // --
                             << bsl::here();                          // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(tls.online_pps != args->online_pps)) {
                bsl::error() << "tls.online_pps ["                          // --
                             << bsl::hex(tls.online_pps)                    // --
                             << "] doesn't match the args->online_pps ["    // --
                             << bsl::hex(args->online_pps)                  // --
                             << "]"                                         // --
                             << bsl::endl                                   // --
                             << bsl::here();                                // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(tls.online_pps > MAX_PPS)) {
                bsl::error() << "tls.online_pps ["                            // --
                             << bsl::hex(tls.online_pps)                      // --
                             << "] is not less or equal to than the max ["    // --
                             << bsl::hex(MAX_PPS)                             // --
                             << "]"                                           // --
                             << bsl::endl                                     // --
                             << bsl::here();                                  // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(!(args->ppid < args->online_pps))) {
                bsl::error() << "the args->ppid ["                         // --
                             << bsl::hex(args->ppid)                       // --
                             << "] is not less than args->online_pps ["    // --
                             << bsl::hex(args->online_pps)                 // --
                             << "]"                                        // --
                             << bsl::endl                                  // --
                             << bsl::here();                               // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(nullptr == args->mk_state)) {
                bsl::error() << "args->mk_state is null"    // --
                             << bsl::endl                   // --
                             << bsl::here();                // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(nullptr == args->root_vp_state)) {
                bsl::error() << "args->root_vp_state is null"    // --
                             << bsl::endl                        // --
                             << bsl::here();                     // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(nullptr == args->debug_ring)) {
                bsl::error() << "args->debug_ring is null"    // --
                             << bsl::endl                     // --
                             << bsl::here();                  // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->mk_elf_file.empty())) {
                bsl::error() << "args->mk_elf_file is empty"    // --
                             << bsl::endl                       // --
                             << bsl::here();                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->mk_elf_file.size().is_zero())) {
                bsl::error() << "args->mk_elf_file's size is zero"    // --
                             << bsl::endl                             // --
                             << bsl::here();                          // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(!(args->mk_elf_file.size() < MK_CODE_SIZE))) {
                bsl::error() << "args->mk_elf_file's size is too big"    // --
                             << bsl::endl                                // --
                             << bsl::here();                             // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->ext_elf_files.front().empty())) {
                bsl::error() << "args->ext_elf_files.front() is empty"    // --
                             << bsl::endl                                 // --
                             << bsl::here();                              // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->ext_elf_files.front().size().is_zero())) {
                bsl::error() << "args->ext_elf_files.front()'s size is zero"    // --
                             << bsl::endl                                       // --
                             << bsl::here();                                    // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(!(args->ext_elf_files.front().size() < MK_CODE_SIZE))) {
                bsl::error() << "args->ext_elf_files.front()'s size is too big"    // --
                             << bsl::endl                                          // --
                             << bsl::here();                                       // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(nullptr == args->rpt)) {
                bsl::error() << "args->rpt is null"    // --
                             << bsl::endl              // --
                             << bsl::here();           // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(bsl::ZERO_UMAX == args->rpt_phys)) {
                bsl::error() << "args->rpt_phys is 0"    // --
                             << bsl::endl                // --
                             << bsl::here();             // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->page_pool.empty())) {
                bsl::error() << "args->page_pool is empty"    // --
                             << bsl::endl                     // --
                             << bsl::here();                  // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->page_pool.size().is_zero())) {
                bsl::error() << "args->page_pool's size is zero"    // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->page_pool.size() < PAGE_SIZE)) {
                bsl::error() << "args->page_pool's size is too small"    // --
                             << bsl::endl                                // --
                             << bsl::here();                             // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->huge_pool.empty())) {
                bsl::error() << "args->huge_pool is empty"    // --
                             << bsl::endl                     // --
                             << bsl::here();                  // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->huge_pool.size().is_zero())) {
                bsl::error() << "args->huge_pool's size is zero"    // --
                             << bsl::endl                           // --
                             << bsl::here();                        // --

                return bsl::errc_failure;
            }

            if (bsl::unlikely_assert(args->huge_pool.size() < PAGE_SIZE)) {
                bsl::error() << "args->huge_pool's size is too small"    // --
                             << bsl::endl                                // --
                             << bsl::here();                             // --

                return bsl::errc_failure;
            }

            return bsl::errc_success;
        }

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

        /// <!-- description -->
        ///   @brief Initialize all of the global resources the microkernel
        ///     depends on.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam MK_ARGS_CONCEPT the type of mk_args to use
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param args the loader provided arguments to the microkernel.
        ///   @param tls the current TLS block
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename MK_ARGS_CONCEPT, typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        initialize(MK_ARGS_CONCEPT *const args, TLS_CONCEPT &tls) noexcept -> bsl::errc_type
        {
            bsl::errc_type ret{};

            bsl::print() << bsl::mag << " ___                __ _           _        " << bsl::endl;
            bsl::print() << bsl::mag << "| _ ) __ _ _ _ ___ / _| |__ _ _ _ | |__     " << bsl::endl;
            bsl::print() << bsl::mag << "| _ \\/ _` | '_/ -_)  _| / _` | ' \\| / /   " << bsl::endl;
            bsl::print() << bsl::mag << "|___/\\__,_|_| \\___|_| |_\\__,_|_||_|_\\_\\" << bsl::endl;
            bsl::print() << bsl::rst << bsl::endl;
            bsl::print() << bsl::grn << "Please give us a star on: ";
            bsl::print() << bsl::rst << "https://github.com/Bareflank/hypervisor";
            bsl::print() << bsl::rst << bsl::endl;
            bsl::print() << bsl::ylw << "=================================";
            bsl::print() << bsl::ylw << "=================================";
            bsl::print() << bsl::rst << bsl::endl;
            bsl::print() << bsl::rst << bsl::endl;

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

            ret = m_system_rpt.initialize(tls, &m_intrinsic, &m_page_pool, &m_huge_pool);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_system_rpt.add_tables(tls, args->rpt);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_vps_pool.initialize(tls, m_page_pool);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_vp_pool.initialize(tls, m_vps_pool);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_ext_pool.initialize(tls, args->ext_elf_files);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_vm_pool.initialize(tls, m_ext_pool, m_vp_pool);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            m_root_vmid = m_vm_pool.allocate(tls, m_ext_pool);
            if (bsl::unlikely(!m_root_vmid)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_vm_pool.set_active(tls, m_root_vmid);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            ret = m_ext_pool.start(tls);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::errc_failure;
            }

            return bsl::errc_success;
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
            , m_root_vmid{bsl::safe_uint16::zero(true)}
            , m_ext_vmexit{}
            , m_ext_fail{}
        {}

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
            bsl::errc_type ret{};

            bsl::finally_assert reset_root_vmid_on_error{[this]() noexcept -> void {
                m_root_vmid = bsl::safe_uint16::zero(true);
            }};

            ret = this->verify_args(args, tls);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::exit_failure;
            }

            this->set_extension_sp(tls);
            this->set_extension_tp(tls);

            if (args->ppid == syscall::BF_BS_PPID) {
                ret = this->initialize(args, tls);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                m_ext_vmexit = tls.ext_vmexit;
                if (bsl::unlikely(nullptr == m_ext_vmexit)) {
                    bsl::error() << "a vmexit handler has not been registered"    // --
                                 << bsl::endl                                     // --
                                 << bsl::here();                                  // --

                    return bsl::exit_failure;
                }

                m_ext_fail = tls.ext_fail;
                if (bsl::unlikely(nullptr == m_ext_fail)) {
                    bsl::error() << "a fast fail handler has not been registered"    // --
                                 << bsl::endl                                        // --
                                 << bsl::here();                                     // --

                    return bsl::exit_failure;
                }

                bsl::touch();
            }
            else {
                ret = m_vm_pool.set_active(tls, m_root_vmid);
                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return bsl::exit_failure;
                }

                tls.ext_vmexit = m_ext_vmexit;
                tls.ext_fail = m_ext_fail;
            }

            ret = m_ext_pool.bootstrap(tls);
            if (bsl::unlikely(!ret)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::exit_failure;
            }

            if (bsl::unlikely(syscall::BF_INVALID_ID == tls.active_extid)) {
                bsl::error() << "bf_vps_op_run was never executed by an extension"    // --
                             << bsl::endl                                             // --
                             << bsl::here();                                          // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely_assert(syscall::BF_INVALID_ID == tls.active_vmid)) {
                bsl::error() << "bf_vps_op_run was never executed by an extension"    // --
                             << bsl::endl                                             // --
                             << bsl::here();                                          // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely_assert(syscall::BF_INVALID_ID == tls.active_vpid)) {
                bsl::error() << "bf_vps_op_run was never executed by an extension"    // --
                             << bsl::endl                                             // --
                             << bsl::here();                                          // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely_assert(syscall::BF_INVALID_ID == tls.active_vpsid)) {
                bsl::error() << "bf_vps_op_run was never executed by an extension"    // --
                             << bsl::endl                                             // --
                             << bsl::here();                                          // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely_assert(nullptr == tls.active_rpt)) {
                bsl::error() << "bf_vps_op_run was never executed by an extension"    // --
                             << bsl::endl                                             // --
                             << bsl::here();                                          // --

                return bsl::exit_failure;
            }

            if (bsl::unlikely(vmexit_loop_entry() != bsl::exit_success)) {
                bsl::print<bsl::V>() << bsl::here();
                return bsl::exit_failure;
            }

            // Unreachable. Only used for unit testing

            reset_root_vmid_on_error.ignore();
            return bsl::exit_success;

            /// Need to finish porting the VP and VPS and possibly any other
            /// object that supports release().
            /// Need to reimplement the run function. No idea what that is
            /// going to look like, so good luck.
            /// Need to finish the migration stuff so that it makes sense.

            // [ ] what happens if a failure handler throws an exception?
            // [ ] need fast fail integration tests
            // [ ] fast fail is not working right. Once the handler is
            //     installed by the extension, any error should call this
            //     and then we return based on what the extension tells us
            //     to do. Right now, it is never called.
            // [ ] add a pointer to the TLS block to the top of the stack
            //     so that you can use the stack to get to the TLS block in
            //     addition to GS. This way, the SX handler has a way to
            //     change TLS data without needing GS, which is a problem.
            //     Will also need a way to get to the size of the stack from
            //     constants.h inside of assembly logic.
            // [ ] Most of the syscalls need to verify that the ext has started that it registered for VMExits.
            // [ ] VP and VPS calls should only occur on the PP the VP/VPS was assigned to?
            //     what about the migration case? You need to update a VPS. The VP has
            //     been migrated, but the VPS has not. Why do we care?
            // [x] What happens if you try to delete a VM that has VPs assigned to it?
            // [ ] What happens if you try to delete a VP that has VPSs assigned to it?
            // [ ] Provide syscall handlers with real error codes?
            // [ ] lock protect the initialize main function in case initialization happens in parallel. mimic call_once init?
            // [ ] What do I do if an exception fires for each syscall.
            //     - Will I end up in deadlock?
            //     = What about the state. Is it corrupt?
            // [ ] What do I do if an exception fires for non-syscalls
            //     - Will I end up in deadlock?
            //     = What about the state. Is it corrupt?
            // [ ] detect if the microkernel attempt to map in physical memory and generates a page fault.
            //     only userspace should be allowed to map to the direct map
            // [ ] The intrinsic run function should be a function in the class and not a global?
            // [ ] Simplify the Intel VPS destriptor stuff by using a template?
            // [ ] Grep for bsl::errc_failure and use other error codes where
            //     it makes sense
            // [ ] Remove pool and intrinsic points from remaining classes
            // [ ] Finish migration stuff
            // [ ] The syscalls should not be doing all of the checks. This
            //     should be done by the APIs themselves for safety.
            // [ ] We need assigned ABIs
            // [ ] We need an umap routines. One routine should unmap a
            //     single address, and another should unmap over an array
            //     that is provided by the extension so that any attempt
            //     to do a TLB flush only occurs after everything is complete.
            // [ ] We need a memset ABI so that extensions do not have
            //     to map in large amounts of memory to set it if needed.
            // [ ] We need a memcpy ABI so that extensions do not have
            //     to map in large amounts of memory to copy it if needed.
            // [ ] Resource cleanup.
            //     - cannot destroy VM until all VPs are destroyed
            //     - cannot destroy VP until all VPSs are destroyed
            //     - cannot load a VPS that is already loaded on another PP
            // [ ] If you destroy a VPS, it should be cleared before it is
            //     destroyed.
            // [ ] make sure the VPS has a migrate function, and make sure
            //     we check that the PP has the same revision ID. Make a
            //     note about the revision issue for AMD.
            // [ ] What about optimizations for read/write MSRs so that the
            //     APIC is fast for an extension.
            // [ ] Make sure all function inputs are checked.
            // [ ] Make sure all rule of 5 crap is moved to the top or removed
            // [ ] What about assignment and active ABIs
            // [ ] Validate upper limit of VM, VP and VPS in config and test with 1 and max
            // [ ] What about IO operations. Need to make sure that an extension can execute port IO
            // [ ] What about an IPI ABI
            // [ ] What about a WBINVLD ABI
            // [ ] implement migration APIs
            // [ ] implement checks for which MSRs can be read/written
            // [ ] implement checks for VMCS fields can be read/written
            // [ ] implement contants for all of the asm logic
            // [ ] implement version of likely/unlikely that always returns true/false in release/minsizerel mode
            //     Anything that is not part of the userspace ABI path should have
            //     these checks removed in release/minsizerel mode
        }
    };
}

#endif
