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

add_executable(example_default)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------

if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD" OR HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
    target_include_directories(example_default PRIVATE
        x64
    )

    if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD")
        target_include_directories(example_default PRIVATE
            x64/amd
        )
    endif()

    if(HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
        target_include_directories(example_default PRIVATE
            x64/intel
        )
    endif()
endif()

if(HYPERVISOR_TARGET_ARCH STREQUAL "aarch64")
    target_include_directories(example_default PRIVATE
        arm
    )

    if(HYPERVISOR_TARGET_ARCH STREQUAL "aarch64")
        target_include_directories(example_default PRIVATE
            arm/aarch64
        )
    endif()
endif()

# ------------------------------------------------------------------------------
# Headers
# ------------------------------------------------------------------------------

if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD" OR HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
    list(APPEND HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/x64/common_arch_support.hpp
    )

    if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD")
        list(APPEND HEADERS
            ${CMAKE_CURRENT_LIST_DIR}/x64/amd/arch_support.hpp
        )
    endif()

    if(HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
        list(APPEND HEADERS
            ${CMAKE_CURRENT_LIST_DIR}/x64/intel/arch_support.hpp
        )
    endif()
endif()

if(HYPERVISOR_TARGET_ARCH STREQUAL "aarch64")
    list(APPEND HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/arm/common_arch_support.hpp
    )

    if(HYPERVISOR_TARGET_ARCH STREQUAL "aarch64")
        list(APPEND HEADERS
            ${CMAKE_CURRENT_LIST_DIR}/arm/aarch64/arch_support.hpp
        )
    endif()
endif()

# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------

target_sources(example_default PRIVATE
    main.cpp
)

set_property(SOURCE main.cpp APPEND PROPERTY OBJECT_DEPENDS ${HEADERS})

if(HYPERVISOR_TARGET_ARCH STREQUAL "AuthenticAMD" OR HYPERVISOR_TARGET_ARCH STREQUAL "GenuineIntel")
    target_sources(example_default PRIVATE
        x64/intrinsic_cpuid.S
        x64/intrinsic_rdtsc.S
        x64/intrinsic_rdtscp.S
    )

    set_property(SOURCE x64/intrinsic_cpuid.S APPEND PROPERTY OBJECT_DEPENDS ${HEADERS})
    set_property(SOURCE x64/intrinsic_rdtsc.S APPEND PROPERTY OBJECT_DEPENDS ${HEADERS})
    set_property(SOURCE x64/intrinsic_rdtscp.S APPEND PROPERTY OBJECT_DEPENDS ${HEADERS})
endif()


# ------------------------------------------------------------------------------
# Libraries
# ------------------------------------------------------------------------------

target_link_libraries(example_default PRIVATE
    runtime
    bsl
    loader
    syscall
)

# ------------------------------------------------------------------------------
# Install
# ------------------------------------------------------------------------------

if(CMAKE_BUILD_TYPE STREQUAL RELEASE OR CMAKE_BUILD_TYPE STREQUAL MINSIZEREL)
    add_custom_command(TARGET example_default POST_BUILD COMMAND ${CMAKE_STRIP} example_default)
endif()

install(TARGETS example_default DESTINATION bin)
