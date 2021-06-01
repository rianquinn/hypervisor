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

#ifndef VP_POOL_T_FAILURE_HPP
#define VP_POOL_T_FAILURE_HPP

#include "vp_pool_t_base.hpp"

namespace mk
{
    /// @class mk::vp_pool_t_failure
    ///
    /// <!-- description -->
    ///   @brief Returns success on initialization
    ///
    class vp_pool_t_failure final    // --
        : public vp_pool_t_base<vp_pool_t_failure>
    {
    public:
        /// <!-- description -->
        ///   @brief If a vp_t is assigned to the requested VM, the ID of
        ///     the vp_t is returned. Otherwise, this function will return
        ///     bsl::safe_uint16::zero(true)
        ///
        /// <!-- inputs/outputs -->
        ///   @param vmid the ID fo the VM to query
        ///   @return If a vp_t is assigned to the requested VM, the ID of
        ///     the vp_t is returned. Otherwise, this function will return
        ///     bsl::safe_uint16::zero(true)
        ///
        [[nodiscard]] static constexpr auto
        is_assigned_to_vm(bsl::safe_uint16 const &vmid) noexcept -> bsl::safe_uint16
        {
            bsl::discard(vmid);
            return syscall::BF_ROOT_VMID;
        }
    };
}

#endif
