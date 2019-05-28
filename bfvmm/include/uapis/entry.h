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

#include "../implementation/vcpu_t.h"

// -----------------------------------------------------------------------------
// Notes
// -----------------------------------------------------------------------------

/// This file provides the functions that can be used to hook into the VMM to
/// add your own functionality. All of the APIs in the "uapis" can be used by
/// an extension and are supported and these APIs can be broken up into two
/// different views:
/// - the vcpu functions
/// - the entry functions
///
/// The vCPU functions provide various different APIs that are vCPU specific,
/// and provide extensions with the ability to configure the vCPU to do
/// whatever it is you need them to do. Also note that you need to configure
/// each vCPU one at a time.
///
/// The entry functions provide an extension with the needed hooks or "seems"
/// to add your custom vCPU operations. The entry functions are called at
/// various stages of a vCPU's lifecycle and give you a place to setup and
/// teardown whatever custom logic your extension is providing.
///
/// To understand what a vCPU is we will need to define some types. Although
/// Bareflank is designed to work with multiple CPU archiectures, the names
/// mostly come from Intel with some mods to make things easier to understand.
/// These definitions should make it easier to understand what the apis in the
/// uapis folder do.
///
/// - host: the host is the thing that is executed in ring-1. From an Intel
///   point of view, the host is the collection of exit handlers. It is not
///   all of the code in the "bfvmm" folder as some of that code is run
///   outside of the host. It is simply the code running on the CPU with the
///   highest privileges. It also has its own state including its own page
///   tables, memory etc... When running in the host, DO NOT ASSUME you can
///   access any resource (e.g. memory, kernel function calls, etc...) outside
///   the host. The host is its own isolated entity that does not have access
///   to anything outside of itself unless you explicitly grant it access to
///   other resources. The most important thing to remember is that if the
///   execution of code doesn't start from an exit handler, you are not in the
///   host. You are only in the host if execution starts from a VMExit.
///
/// - guest: the guest is any code that is not executed from an exit handler.
///   Note that if the VMM is not running, "host" and "guest" have no meaning
///   which is why we do not use them in this context. You can only be in the
///   "host" or the "guest", not both at the same time, and you are in neither
///   if the VMM is not running. If the VMM is not running, you are simply
///   running in the "host OS" which is described below. From an Intel point
///   of view, the VMCS maintains a "host" and "guest" state and we use the
///   same scheme here for all architectures. Another way to look at this is
///   software that executes in the host executes with ring-1 privileges while
///   software that executes in the guest executes with ring0-3 privileges.
///   Also note that "guest", "guest VM" and "guest vCPU" all mean different
///   things and should not be confused. The "guest" simply refers to any code
///   not running with ring-1 privileges, which includes code in the bfvmm
///   folder (the parts that do not originate from a VMExit).
///
/// - pCPU: A physical CPU. On systems with hyperthreading this is actually
///   a thread, but on systems without hyperthraeding, or hyperthreading
///   disabled, the pCPU is a real-life core. The important thing to remember
///   here is that a pCPU is a real CPU and it is the thing that actually
///   executes software.
///
/// - vCPU: a virtual CPU is a virtual representation of a pCPU. Another way
///   of looking at it is, a vCPU stores all of the state for a pCPU and allows
///   a hypervisor to swap states on the pCPU from one state to another. This
///   provides the hypervisor with a means to execute multiple operating
///   systems on the same pCPU at the same time. In the VMM we only really talk
///   about vCPUs as everything we do in the hypervisor is manipulate vCPUs.
///   In reality, at some point, a vCPU needs to be loaded onto a pCPU and its
///   the pCPU that is actually executing code. That is what the run()
///   function does.
///
/// - host OS: the host OS is the OS responsible for managing the system.
///   Another way of looking at it is, the host OS is the thing that starts
///   the VMM. When this occurs, all of the physical CPUs are given virtual
///   CPUs by demoting the host OS (i.e. running the host OS in a VM). Once
///   the VMM is running, the host OS is free to do what it wants, including
///   starting other operating systems (e.g. UEFI starting Linux or Windows).
///   Although there is no requirement for the host OS to execute, the host
///   vCPUs must always be present as they are the "root" vCPUs, and the host
///   OS has to at least start the VMM.
///
/// - guest VM: A "guest VM", not to be confused with "guest", is any
///   operating system that is executing on the system that is not the host OS.
///   A VMM is needed to execute a guest VM (as you cannot have more than one
///   OS running at the sametime on the same hardware without a VMM), and
///   support for a guest VM must come from an extension as Bareflank natively
///   doesn't provide this support (it simply provides the APIs needed to
///   provide this support). Although a guest vCPU can be used for both the
///   host OS and a guest VM, a guest VM can only be created using guest vCPUs.
///
/// - host vCPU: A host vCPU is a vCPU that stores the state for the host OS.
///   It is a vCPU that executes the host OS. There is one host vCPU for every
///   pCPU on the system (no more, no less) and host vCPUs should not be
///   created by the user. These are managed by Bareflank. It should be noted
///   that host vCPUs do not need to execute but they do need to exist as they
///   are the "root" vCPUs. Once again, extensions should not attempt to create
///   or destroy these vCPUs are they control promotion/demotion of the host OS.
///   It should also be noted that guest vCPU can be created and left intact
///   well after all of the host vCPUs have been destroyed. In fact, the host
///   vCPUs can be created and destroyed many times without affecting the
///   lifetime of a guest vCPU at all.
///
/// - guest vCPU: A guest vCPU is any vCPU that is not a host vCPU. Guest
///   vCPUs can be used to create guest VMs, containerization, etc... There
///   is no limit. Another way of looking at a guest vCPU is a guest vCPU is
///   any vCPU that the user of these APIs creates themselves. If you do not
///   create a vCPU yourself, you are only using host vCPUs in your project,
///   and you likely are working with a host-only configuration. With that said
///   guest vCPUs can execute software in the host OS (meaning they are not
///   limited to guest VMs). For example, if you are implementing
///   containerization, you would still create guest vCPUs to do this, even
///   though the guest vCPUs are being used to execute the host OS. A host
///   vCPU is nothing more than a vCPU that is created by Bareflank and used
///   to demote/promote the host OS. All other vCPUs, for any reason are guest
///   vCPUs, and should use guest vCPU ids.
///
/// - bootstrap vCPU: The bootstrap vCPU is the fist host vCPU to be created,
///   and it is the last host vCPU to be destroyed. It will always have a vCPU
///   id of 0. It is also the vCPU that is used when setting up global resources
///   in the VMM. Like the BSP on Intel, this is the vCPU that is used to
///   bootstrap the VMM. Once the VMM is running on all cores, it has no
///   additional meaning except that it will be the last host vCPU to be
///   destroyed. Since the VMM is symmetric, the bootstrap vCPU has no special
///   meaning while everything is running.
///
/// - host-only: a host-only VMM (sometimes referred to as a host-only
///   hypervisor) is a VMM that never creates guest VMs (not to be confused
///   with guest vCPUs). Remember that one of the biggest differences with
///   Bareflank is that the host OS runs in a VM at all times. Most other
///   hypervisors only run guest VMs. The reason is most hypervisors provide
///   the ability to run more than one operating system simultaneously (with the
///   most familiar being running Windows on a Mac using VMWare Fusion). But
///   in general hypervisors like Xen, KVM, VirtualBox, VMWare, etc... they all
///   focus on running more than one guest VM. Although Bareflank can be
///   used to create a hypervisor that does the same thing, it is designed to
///   also support "host-only" configurations where no guest VMs are ever
///   executed and the hypervisor is only used to virtualize the host OS. This
///   can be done to support reverse engineering, introspection, security
///   products, research, and even containerization. In fact, it is possible
///   for a host-only VMM to still create guest vCPUs designed to execute the
///   host OS (e.g. containerization). A host-only hypervisor only means that
///   guest VMs are not created. It doesn't mean that guest vCPUs are never
///   created. Bareflank provides out-of-box support for host-only
///   configurations. If you need guest VM support, you will need to leverage
///   an extension that provides such support, or write one using Bareflank.
///
/// - early-boot: we do not like the terms type 1 or type 2 as they do not
///   describe the design principles of a hypervisor accurately. Sometimes
///   when we think of a type 1 hypervisor like Xen, what we are likely
///   referring to is an early-boot hypervisor. An early-boot hypervisor
///   executes from BIOS or UEFI and then executes the primary OS inside a VM
///   (in the Xen case, this is called dom0). The benefit to an early-boot
///   hypervisor is the hypervisor is capable of controlling the security of
///   itself and the platform better than a late-launch hypervisor. It is also
///   capable of better deprivilege and disaggregation. One big disadvantage
///   to an early-boot hypervisor is they are a pain to develop as you typically
///   have to restart the computer each time you recompile the hypervisor.
///   Bareflank supports early-boot for UEFI and is capable of booting Linux or
///   Windows from there.
///
/// - late-launch: a late-launch hypervisor is the more common hypervisor
///   including KVM, VirtualBox, VMWare Workstation/Fusion, etc... All of these
///   hypervisors (also called hosted hypervisors) execute after the host OS
///   starts. These hypervisors generally require the facilities of the host
///   OS to work (although early-boot could also require this, and relying on
///   a host OS does not immediately reduce the security posture of the
///   hypervisor). Late-launch hypervisors are easier to develop as you can
///   start/stop them at will which means typically no reboot is required. In
///   most cases these types of hypervisors are implemented as host OS kernel
///   drivers, and they are typically used to provide support for guest VMs.
///   Bareflank is unique in that it is one of the first hypervisors capable of
///   supporting late-launch while also being able to execute the host OS in a
///   VM like an early-boot hypervisor. Late-launch hypervisors however should
///   not be used for security critical software as the host OS executes first,
///   and therefore is capable of breaking down the isolation the hypervisor
///   attempts to put in place. Some of this risk can be reduced or even
///   eliminated if the hypervisor is launched as part of a trusted boot, but
///   in this case, you are really dealing with an early-boot hypervisor. The
///   difference is pedantic assuming the hypervisor executes the host OS in a
///   VM. If it doesn't, like KVM, VirtualBox and VMWare, early-boot vs
///   late-launch is not the biggest issue if security is your focus.
///
/// - host physical address (HPA): A physical address (PA) is the actual address
///   that is used to talk to RAM. It is the 1:1 mapping between the address
///   and actual memory. A host physical address (HPA) and physical address (PA)
///   are the same thing. The only reason we add the extra "H" is so that we
///   are explicit about the type of memory we are accessing.
///
/// - host virtual address (HVA): like any other modern operating system, the
///   VMM has its own virtual memory. On Intel, the Host CR3 is used to store
///   the root address of the pages used by the host. Since virtual memory is
///   used in the host, the host cannot directly address physical memory, but
///   instead must make an entry in the host's page tables to make an HVA to
///   and HPA. In addition, since the host has its own virtual memory, it
///   cannot directly access guest memory. If you want to access guest memory
///   you must first figure out what the physical address of the guest memory
///   is and then map this memory in the host's page tables to get an HVA that
///   can be used to access the memory.
///
/// - guest physical address (GPA): a guest physical address is not the same
///   thing as a host physical address or a physical address. If something like
///   EPT is used, the hypervisor is capable of using a set of page tables to
///   remap guest physical memory. Think of this as a second level of page
///   tables. If EPT is disabled, the GPA == HPA == PA, meaning they are all
///   the same thing. If EPT is enabled however, you must use EPT to convert a
///   guest physical address to an actual physical address (i.e. HPA). Note
///   that when we say guest, as described above, we mean any ring0-3 code,
///   which could include the host OS.
///
/// - guest virtual address (GVA): A guest virtual address is the address that
///   guest software (both in userspace and in the kernel) uses to access
///   memory. Similar to the HVA, the guest maintains a set of pages tables for
///   each process that executes, and the process uses the GVA to access memory
///   when paging is turned on. If you allocate a block of memory in the kernrel
///   or in a userspace application, you get a GVA. If you want to access this
///   GVA in the VMM, you must first convert the GVA to a GPA and then, using
///   something like EPT you must convert the GPA to a PA (i.e. HPA). Once you
///   have an HPA, you must map the HPA into the VMM which will give you an
///   HVA that you can use from within the VMM to access the memory.
///   Bareflank provides a set of APIs to perform these conversions, but as you
///   can imagine, they are slow so only use these if needed. Also note that
///   the guest has a lot of page tables, and the page tables between userspace
///   and the kernel may not be shared (especially since Meltdown was released)
///   so care should be taken to ensure any conversions of a GVA are handled
///   properly.
///
/// - deprivilege: When a VMM is not running, the host OS has complete control
///   of the system. When the VMM is running, it has control of the host OS and
///   any additional guest VMs that are created. The act of deprivilege is
///   nothing more than restricting a VMs actions (either the host OS or a
///   guest VM). Typically, a deprivileged VM cannot see or manipulate the
///   resources of another VM which provides "isolation". On a system like Xen
///   this usually does not include dom0 (i.e. the host OS). Using Bareflank,
///   it is possible to not only deprivilege a guest VM, but also the host OS.
///   This provides the ability to protect a guest VM from the host OS which is
///   the opposite from what we are used too with other hypervisors.
///
/// - disaggregation: Since most hypervisors cannot provide a deprivileged
///   host OS, we usually attempt to disaggregate the host OS to reduce the
///   risk of malware breaking into the host OS from completely owning the
///   system. Disaggregation refers moving resources that the host OS would
///   usually manage into guest VMs that can be deprivileged. Using Bareflank,
///   we can deprivilege the host OS, so disaggregation is a "nice to have",
///   "defense-in-depth" technique, and not a requirement. On other hypervisors
///   disaggregation is the only mechanism we have to increase the security
///   posture of the system by reducing the amount of software that is running
///   with "privilege" (i.e. the ability to see another VM's resources).
///

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

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

/// vCPU Init
///
/// This function is called after a vCPU has been fully constructed, but before
/// the vCPU has been started. Since the VMM is not running, we do not
/// have a host or a guest, so this function is executed in the context of the
/// host OS (on Intel this is ring0).
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being initialized
///
void vcpu_init(vcpu_t *vcpu);

/// vCPU Fini
///
/// This function is called before a vCPU has been fully destroyed, but after
/// the vCPU has been stopped. Since the VMM is not running, we do not
/// have a host or a guest, so this function is executed in the context of the
/// host OS (on Intel this is ring0).
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being finailized
///
void vcpu_fini(vcpu_t *vcpu);

/// vCPU Init Guest
///
/// This function is called after a vCPU has been fully constructed, right
/// after the vCPU has been started (i.e. it is now running). There are two
/// versions of this function: host/guest. The guest function is executed
/// from the guest point of view, which means that it executes from the host
/// OS (on Intel this is ring0). Remember that there is a difference between
/// the guest, a guest vCPU and a guest VM. The "guest" is nothing more than
/// any code not running in the "host". On Intel, the guest is any code running
/// in ring0-3, even for host vCPUs. A guest vCPU is any vCPU that is not a
/// host vCPU. This function never executes for a guest vCPU. A guest VM is
/// any operating system that is not the host OS. This function is never called
/// for a guest VM since guest VMs can only be executed by guest vCPUs, and
/// this function is never executed for guest vCPUs. This function is only
/// executed for host vCPUs on the host OS from the guest POV.
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being initialized
///
void vcpu_init_guest(vcpu_t *vcpu);

/// vCPU Fini Guest
///
/// This function is called before a vCPU has been fully destroyed, right
/// before the vCPU has been stopped (i.e. it is still running). There are two
/// versions of this function: host/guest. The guest function is executed
/// from the guest point of view, which means that it executes from the host
/// OS (on Intel this is ring0). Remember that there is a difference between
/// the guest, a guest vCPU and a guest VM. The "guest" is nothing more than
/// any code not running in the "host". On Intel, the guest is any code running
/// in ring0-3, even for host vCPUs. A guest vCPU is any vCPU that is not a
/// host vCPU. This function never executes for a guest vCPU. A guest VM is
/// any operating system that is not the host OS. This function is never called
/// for a guest VM since guest VMs can only be executed by guest vCPUs, and
/// this function is never executed for guest vCPUs. This function is only
/// executed for host vCPUs on the host OS from the guest POV.
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being finailized
///
void vcpu_fini_guest(vcpu_t *vcpu);

/// vCPU Init Guest
///
/// This function is called after a vCPU has been fully constructed, right
/// after the vCPU has been started (i.e. it is now running). There are two
/// versions of this function: host/guest. The host function is executed
/// from the host point of view, which means that it executes from an exit
/// handler. To do this, we generate a VMExit right after the VMM is stated
/// on this vCPU.
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being initialized
///
void vcpu_init_host(vcpu_t *vcpu);

/// vCPU Fini Guest
///
/// This function is called before a vCPU has been fully destroyed, right
/// before the vCPU has been stopped (i.e. it is still running). There are two
/// versions of this function: host/guest. The host function is executed
/// from the host point of view, which means that it executes from an exit
/// handler. To do this, we generate a VMExit right before the VMM is stopped
/// on this vCPU.
///
/// Note:
/// This is only called for host vCPUs
///
/// @param vcpu the vCPU being finailized
///
void vcpu_fini_host(vcpu_t *vcpu);

#endif
