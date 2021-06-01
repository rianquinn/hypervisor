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

#ifndef EXT_POOL_T_SIGNAL_VM_CREATED_FAILURE_HPP
#define EXT_POOL_T_SIGNAL_VM_CREATED_FAILURE_HPP

#include "ext_pool_t_base.hpp"

namespace mk
{
    /// @class mk::ext_pool_t_signal_vm_created_failure
    ///
    /// <!-- description -->
    ///   @brief Returns success on initialization
    ///
    class ext_pool_t_signal_vm_created_failure final    // --
        : public ext_pool_t_base<ext_pool_t_signal_vm_created_failure>
    {
    public:
        /// <!-- description -->
        ///   @brief Tells each extension that a VM was created so that it
        ///     can initialize it's VM specific resources.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param vmid the VMID of the VM that was created.
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] static constexpr auto
        signal_vm_created(TLS_CONCEPT &tls, bsl::safe_uint16 const &vmid) noexcept
            -> bsl::errc_type
        {
            bsl::discard(tls);
            bsl::discard(vmid);

            return bsl::errc_failure;
        }
    };
}

#endif
