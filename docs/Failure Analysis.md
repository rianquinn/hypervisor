## Table of Contents <!-- omit in toc -->

# 1. Introduction

This document defines how failures are handled by the microkernel and what the expected results are.

# 2. Starting

TBD

# 3. Stopping

TBD

# 4. Syscalls

When a syscall is executed it is possible that the microkernel could generate a hardware exception and fail to execute the syscall. If this occurs, the microkernel is designed to return back to the extension with an error code stating that the call to the microkernel failed.

If a syscall returns BF_STATUS_FAILURE_UNKNOWN, it should be assumed that either an unexpected error has occurred, or a hardware exception has occurred. In either case, the following are the expectations that an extension can make about any given syscall:

# 4.1 Resource Creation

Any syscall that creates a resource like bf_vm_op_create_vm, bf_vm_op_create_vp and bf_vm_op_create_vps will leave the internal state of the microkernel the way it was prior to the error. This includes if a hardware exception occurs while attempting to execute the syscall (excluding exceptions like a Machine Check which are unrecoverable my design). It is up to the extension to determine how to proceed. For example, if the extension is implementing guest support and a creation function fails for whatever reason, the extension may choose to stop everything, or it may choose to continue the execution of any existing virtual machines and simply fail to create a new one.

# 4.2 Resource Destruction

Any syscall that destroys a resource like bf_vm_op_destroy_vm, bf_vm_op_destroy_vp and bf_vm_op_destroy_vps will leave the resource in an allocated state. Internally, the microkernel is allowed to leave its internal state however it wishes, so long as the resources is left as "allocated" from the extension's point of view (meaning it cannot recreate the resource later after a failed attempt to destroy the resource). What this means to the extension is the resource is leaked as it would have no ability to destroy the resource properly. As a result, if a destroy syscall fails, the extension is free to continue its execution with the expectation that the microkernel can continue other execution tasks but with some resources leaked and no longer accessible. Further attempts in the future to create new resources could fail as resources become starved.

It should also be noted that resource leakage could go beyond the resource in question. For example, if a VPS fails to be destroyed, the VP assigned to the VPS will also fail to be destroyed, which in turn means the VM assigned to the VP will also fail to be destroyed. In addition, all memory allocated to the VM, VP and VPS may also leak as is may remain in place.

In the event that destruction fails, the resource would be referred to as a Zombie resource, remaining inaccessible, but also indestructible. An extension can assume that any attempt to use a Zombie resource will fail, and that any attempt to further destroy a Zombie resource will be ignored.
