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

#ifndef VP_T_MIGRATE_FAILURE_HPP
#define VP_T_MIGRATE_FAILURE_HPP

#include "vp_t_base.hpp"

#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>

namespace mk
{
    /// @class mk::vp_t_migrate_failure
    ///
    /// <!-- description -->
    ///   @brief Returns failure on initialization
    ///
    class vp_t_migrate_failure final    // --
        : public vp_t_base<vp_t_migrate_failure>
    {
    public:
        /// <!-- description -->
        ///   @brief Migrates this vp_t from one PP to another. If this calls
        ///     completes successfully, the VPS's assigned PP will not
        ///     match the VP's assigned PP. Future calls to the run ABI
        ///     will be able to detect this an migrate mismatched VPSs to
        ///     the proper PP as needed. Note that since the VP doesn't control
        ///     any hardware state, all we have to do here is set which PP
        ///     this VP is allowed to execute on. The VPS is what actually
        ///     needs to be migrated, and that will not happen until a call
        ///     to the run ABIs made. Once the run ABI detects a mismatch with
        ///     the VPS and it's assigned VP, it will be migrated then.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam TLS_CONCEPT defines the type of TLS block to use
        ///   @param tls the current TLS block
        ///   @param ppid the ID of the PP to migrate to
        ///   @return Returns bsl::errc_success on success, bsl::errc_failure
        ///     and friends otherwise
        ///
        template<typename TLS_CONCEPT>
        [[nodiscard]] constexpr auto
        migrate(TLS_CONCEPT &tls, bsl::safe_uint16 const &ppid) &noexcept -> bsl::errc_type
        {
            bsl::discard(tls);
            bsl::discard(ppid);

            return bsl::errc_failure;
        }
    };
}

#endif
