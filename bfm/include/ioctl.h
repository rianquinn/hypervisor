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

#ifndef IOCTL_H
#define IOCTL_H

#include <bfgsl.h>
#include <bftypes.h>
#include <bfdriverinterface.h>

/// IOCTL
///
/// Calls into the bareflank driver entry to perform a desired action. Note
/// that for this class to function, the driver entry must be loaded, and
/// bfm must be executed with the proper permissions.
///
class ioctl
{
public:

    /// Default Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    ioctl();

    /// Destructor
    ///
    /// @expects none
    /// @ensures none
    ///
    ~ioctl();

    /// Load VMM
    ///
    /// Loads the VMM
    ///
    /// @expects none
    /// @ensures none
    ///
    void call_ioctl_load_vmm(
        gsl::not_null<const ioctl_load_args_t *> args) const;

    /// Unload VMM
    ///
    /// Unloads the VMM
    ///
    /// @expects none
    /// @ensures none
    ///
    void call_ioctl_unload_vmm() const;

    /// Start VMM
    ///
    /// Starts the VMM
    ///
    /// @expects none
    /// @ensures none
    ///
    void call_ioctl_start_vmm() const;

    /// Stop VMM
    ///
    /// Stops the VMM
    ///
    /// @expects none
    /// @ensures none
    ///
    void call_ioctl_stop_vmm() const;

    /// Dump VMM
    ///
    /// Dumps the contents of the VMM's debug ring
    ///
    /// @expects drr != null;
    /// @ensures none
    ///
    /// @param drr pointer a debug_ring_resources_t
    ///
    void call_ioctl_dump_vmm(
        gsl::not_null<debug_ring_resources_t *> args) const;

    /// VMM Status
    ///
    /// Get the status of the VMM
    ///
    /// @expects status != nullptr
    /// @ensures none
    ///
    /// @param status pointer to status variable to store the results
    ///
    void call_ioctl_vmm_status(
        gsl::not_null<status_t *> args) const;
};

#endif
