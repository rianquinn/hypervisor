## Table of Contents <!-- omit in toc -->

# 1. Introduction

This document describes some of the reasoning behind certain optimization, or the lack there of.

# 2. VM, VP and VPS Pools

The VM, VP and VPS pools used to use a combination of an array and a linked list. THe ID given to each resource is the resource's position in the array. This allows any API to access the resource using it's ID, which is fast and simple. Allocations, however, used a linked list. Basically, each resource stored a "next" pointer which the pools could use to turn the array into a linked list. This provided a means to allocate using O(1). In otherwords, all operations for each resource, including accesses, allocations and deallocations were all O(1) which is fast.

This was changed to remove the linked list portion for a couple of reasons. To start, the next pointer adds memory usage. This memory usage is small, so by itself is not enough to remove the linked list. The main reason for removing the linked list is stability. Even if Bareflank is configured to have access to the max of 32767 resources for a VM, VP and VPS, O(N) in this case is not unreasonable. There are other operations that must take place other than just allocations that are O(N). For example, the microkernel must ensure that when a VM is destroyed, it is not active on any PPs, and that no VPs are assigned to it. All of these operations are all O(N), or we would need additional linked lists to reduce the overall time required to perform these checks. Each linked list not only adds additional memory requirements, but most importantly, it adds additional complexity to the microkernel.

For example, suppose in the process of performing a deallocation, a null dereference occurs in the microkernel. If this happens, the microkernel needs to mark the resource as a zombie as it was not properly deallocated. Now lets say the microkernel needs to allocate a new resource. If the zombie resource is the head (which it will eventually become), the microkernel would fail as it would have allocated a zombie resource. This means that in addition to the added complexity of the linked lists, the microkernel needs added logic for handling when it attempts to allocate a resource that is a zombie. It also needs added logic for handling when the linked list is not properly linked. There are many more examples of these types of issues. Each linked list adds a lot of extra logic that must be compiled into the code (which also adds to the size of the microkernel), unit tested, etc.

For these reasons, we simply loop through the arrays when attempting to do allocations. The move from O(1) to O(N) does mean that as N increases, allocations will take longer, but in the grand scheme of things, the reduction in overall complexity is worth it, as there are far fewer edge cases that must be considered, and a lot less state that must be properly handled in the event of unexpected errors.
