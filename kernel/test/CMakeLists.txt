#
# Copyright (C) 2020 Assured Information Security, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

include(${bsl_SOURCE_DIR}/cmake/function/bf_add_test.cmake)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------

list(APPEND INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/../../syscall/include/cpp
)

list(APPEND SYSTEM_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/../../loader/include/interface/cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../loader/include/interface/cpp/bfelf
)

if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD" OR HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
    list(APPEND INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../include/x64)
    list(APPEND SYSTEM_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../../loader/include/interface/cpp/x64)

    if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD")
        list(APPEND INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../include/x64/amd)
        list(APPEND SYSTEM_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../../loader/include/interface/cpp/x64/amd)
    endif()

    if(HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
        list(APPEND INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../include/x64/intel)
        list(APPEND SYSTEM_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../../loader/include/interface/cpp/x64/intel)
    endif()
endif()

if(HYPERVISOR_TARGET_ARCH STREQUAL "aarch64")
    list(APPEND INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../include/arm)
    list(APPEND SYSTEM_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../../loader/include/interface/cpp/arm)

    if(HYPERVISOR_TARGET_ARCH STREQUAL "aarch64")
        list(APPEND INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../include/arm/aarch64)
        list(APPEND SYSTEM_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/../../loader/include/interface/cpp/arm/aarch64)
    endif()
endif()

# ------------------------------------------------------------------------------
# Default Definitions
# ------------------------------------------------------------------------------

list(APPEND DEFINES
    HYPERVISOR_DEBUG_RING_SIZE=0x7FF0
)

if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD")
    list(APPEND DEFINES
        HYPERVISOR_X64=true
        HYPERVISOR_AMD=true
        HYPERVISOR_INTEL=false
        HYPERVISOR_ARM=false
        HYPERVISOR_AARCH64=false
    )
endif()

if(HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
    list(APPEND DEFINES
        HYPERVISOR_X64=true
        HYPERVISOR_AMD=false
        HYPERVISOR_INTEL=true
        HYPERVISOR_ARM=false
        HYPERVISOR_AARCH64=false
    )
endif()

if(HYPERVISOR_TARGET_ARCH STREQUAL "aarch64")
    list(APPEND DEFINES
        HYPERVISOR_X64=false
        HYPERVISOR_AMD=false
        HYPERVISOR_INTEL=false
        HYPERVISOR_ARM=true
        HYPERVISOR_AARCH64=true
    )
endif()

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

add_subdirectory(call_ext)
add_subdirectory(debug_ring_write)
add_subdirectory(dispatch_esr_page_fault)
add_subdirectory(dispatch_syscall)
add_subdirectory(dispatch_syscall_callback_op)
add_subdirectory(dispatch_syscall_control_op)
add_subdirectory(dispatch_syscall_debug_op)
add_subdirectory(dispatch_syscall_handle_op)
add_subdirectory(dispatch_syscall_mem_op)
add_subdirectory(dispatch_syscall_vm_op)
add_subdirectory(dispatch_syscall_vp_op)
add_subdirectory(dispatch_syscall_vps_op)
add_subdirectory(ext_pool_t)
add_subdirectory(ext_t)
add_subdirectory(fast_fail)
add_subdirectory(get_current_tls)
add_subdirectory(huge_pool_t)
add_subdirectory(huge_t)
add_subdirectory(map_page_flags)
add_subdirectory(mk_main)
add_subdirectory(page_pool_t)
add_subdirectory(page_t)
add_subdirectory(promote)
add_subdirectory(return_to_mk)
add_subdirectory(return_to_vmexit_loop)
add_subdirectory(vm_pool_t)
add_subdirectory(vm_t)
add_subdirectory(vmexit_loop)
add_subdirectory(vmexit_loop_entry)
add_subdirectory(vp_pool_t)
add_subdirectory(vp_t)
add_subdirectory(vps_pool_t)

if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD" OR HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
    add_subdirectory(x64/dispatch_esr)
    add_subdirectory(x64/root_page_table_t)

    if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD")
        add_subdirectory(x64/amd/dispatch_esr_nmi)
        add_subdirectory(x64/amd/dispatch_syscall_intrinsic_op)
        add_subdirectory(x64/amd/intrinsic_t)
        add_subdirectory(x64/amd/vps_t)
    endif()

    if(HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
        add_subdirectory(x64/intel/dispatch_esr_nmi)
        add_subdirectory(x64/intel/dispatch_syscall_intrinsic_op)
        add_subdirectory(x64/intel/intrinsic_t)
        add_subdirectory(x64/intel/vps_t)
    endif()
endif()

if(HYPERVISOR_TARGET_ARCH STREQUAL "aarch64")
    add_subdirectory(arm/aarch64/dispatch_esr)
    add_subdirectory(arm/aarch64/dispatch_syscall_intrinsic_op)
    add_subdirectory(arm/aarch64/intrinsic_t)
    add_subdirectory(arm/aarch64/root_page_table_t)
    add_subdirectory(arm/aarch64/vps_t)
endif()












    file(GLOB SUBDIRS RELATIVE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/*)
    foreach(DIR ${SUBDIRS})
        file(GLOB_RECURSE FILES RELATIVE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/${DIR}/*.profraw)
        if(NOT FILES STREQUAL "")
            set(LLVM_PROFDATA_FILES "${LLVM_PROFDATA_FILES} ${FILES}")
        endif()
    endforeach()

    string(REPLACE ";" " " LLVM_PROFDATA_FILES "${LLVM_PROFDATA_FILES}")
    string(REPLACE " \\ " "" LLVM_PROFDATA_FILES "${LLVM_PROFDATA_FILES}")

    

    add_custom_target(yourmom
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} llvm-profdata merge -sparse ${LLVM_PROFDATA_FILES} -o info.profdata
    )
