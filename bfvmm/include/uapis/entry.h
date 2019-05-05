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

#ifndef UAPIS_ENTRY_H
#define UAPIS_ENTRY_H

#include <uapis/vcpu_manager.h>

/// Global Init
///
/// Global constructors are a terrible way to construct global objects as
/// their order is not defined. In addition, some resources are not available
/// during global construction such as hva->hpa / hpa->hva conversions as
/// the memory descriptors are added to the memory manager after global
/// construction. This function provides the user with a way to construct their
/// code after the C++ environment was been fully established, while also being
/// able to dictate order.
///
void global_init();

/// vCPU Init Nonroot
///
/// This function is called after a vCPU has been fully constructed, but before
/// the vCPU has been started. This code executes in nonroot (i.e. in the
/// host OS's kernel).
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being initialized
///
void vcpu_init_nonroot(vcpu_t *vcpu);

/// vCPU Fini Nonroot
///
/// This function is called after a vCPU has been stopped, but just prior to
/// it being destroyed. This code executes in nonroot (i.e. in the host OS's
/// kernel).
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being finalized
///
void vcpu_fini_nonroot(vcpu_t *vcpu);

/// vCPU Init Nonroot (Running)
///
/// This function is called after a vCPU has been fully constructed, right
/// after the vCPU has been started (i.e. it is now running). This function is
/// also called after the vcpu_init_root() function, and unlike that function,
/// this code executes in nonroot (i.e. in the host OS's kernel).
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being initialized
///
void vcpu_ini_nonroot_running(vcpu_t *vcpu);

/// vCPU Fini Nonroot (Running)
///
/// This function is called just before the vCPU is stopped and the host OS
/// is promoted. This code executes in nonroot (i.e. in the host OS's kernel).
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being initialized
///
void vcpu_fini_nonroot_running(vcpu_t *vcpu);

#endif
