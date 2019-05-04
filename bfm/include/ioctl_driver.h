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

#ifndef IOCTL_DRIVER_H
#define IOCTL_DRIVER_H

#include <ioctl.h>

/// IOCTL Driver
///
/// The IOCTL driver is the main work horse of the Bareflank Manager. The
/// IOCTL driver takes the command line, and tells the bfdriver what to do
/// using the IOCTL interface.
///
class ioctl_driver
{
public:

    /// Default Constructor
    ///
    /// @expects
    /// @ensures
    ///
    ioctl_driver() = default;

    /// Process
    ///
    /// @expects
    /// @ensures
    ///
    int process(int argc, char *argv[]);

private:

    void load_vmm(const std::string &filename, uint64_t mem);
    void unload_vmm();
    void start_vmm();
    void stop_vmm();
    void dump_vmm();

    status_t get_status() const;

private:

    ioctl m_ioctl;
};

#endif
