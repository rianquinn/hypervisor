#
# Copyright (C) 2019 Assured Information Security, Inc.
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

cmake_minimum_required(VERSION 3.13)
project(hypervisor NONE)

# ------------------------------------------------------------------------------
# Initial Setup
# ------------------------------------------------------------------------------

include(${CMAKE_CURRENT_LIST_DIR}/scripts/cmake/config/default.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/scripts/cmake/macros.cmake)

include_external_config()

# ------------------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------------------

include(${CMAKE_CURRENT_LIST_DIR}/scripts/cmake/targets.cmake)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------

include_dependency(SOURCE_DEPENDS_DIR gsl)
include_dependency(SOURCE_DEPENDS_DIR json)
include_dependency(SOURCE_DEPENDS_DIR argparse)
include_dependency(SOURCE_DEPENDS_DIR binutils)
include_dependency(SOURCE_DEPENDS_DIR newlib)
include_dependency(SOURCE_DEPENDS_DIR llvm)
include_dependency(SOURCE_DEPENDS_DIR libcxxabi)
include_dependency(SOURCE_DEPENDS_DIR libcxx)
include_dependency(SOURCE_DEPENDS_DIR astyle)
include_dependency(SOURCE_DEPENDS_DIR clang_tidy)
include_dependency(SOURCE_DEPENDS_DIR catch)
include_dependency(SOURCE_DEPENDS_DIR hippomocks)

# ------------------------------------------------------------------------------
# Interface
# ------------------------------------------------------------------------------

setup_interfaces()

# ------------------------------------------------------------------------------
# VMM Components
# ------------------------------------------------------------------------------

add_subproject(bfsdk vmm DEPENDS gsl json libcxx PRIVATE NOINSTALL)
add_subproject(bfintrinsics vmm DEPENDS bfsdk PRIVATE)
add_subproject(bfruntime vmm DEPENDS bfsdk PRIVATE)
add_subproject(bfunwind vmm DEPENDS bfsdk PRIVATE)
add_subproject(bfvmm vmm DEPENDS bfruntime bfunwind bfintrinsics PRIVATE)

# ------------------------------------------------------------------------------
# Userspace Components
# ------------------------------------------------------------------------------

add_subproject(bfsdk userspace DEPENDS gsl json argparse PRIVATE NOINSTALL)
add_subproject(bfm userspace DEPENDS bfintrinsics PRIVATE)
# add_subproject(bfack userspace DEPENDS bfintrinsics PRIVATE)

# ------------------------------------------------------------------------------
# Unit Tests
# ------------------------------------------------------------------------------

add_subproject(bfsdk test DEPENDS gsl json catch hippomocks PRIVATE NOINSTALL)
add_subproject(bfm test DEPENDS bfsdk PRIVATE NOINSTALL)

# ------------------------------------------------------------------------------
# Integration Tests
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------

if(NOT EXTENSION)
    list(APPEND EXTENSION ${CMAKE_CURRENT_LIST_DIR}/examples/dummy)
    list(APPEND EXTENSION ${CMAKE_CURRENT_LIST_DIR}/examples/default)
endif()

if(ENABLE_BUILD_EXAMPLES)
    list(APPEND EXTENSION ${SOURCE_EXAMPLES_DIR}/cpuidcount)
    list(APPEND EXTENSION ${SOURCE_EXAMPLES_DIR}/hook)
    list(APPEND EXTENSION ${SOURCE_EXAMPLES_DIR}/rdtsc)
    list(APPEND EXTENSION ${SOURCE_EXAMPLES_DIR}/vpid)
endif()

# ------------------------------------------------------------------------------
# External Extensions
# ------------------------------------------------------------------------------

include_external_extensions()

# ------------------------------------------------------------------------------
# EFI Components
# ------------------------------------------------------------------------------

if(ENABLE_BUILD_EFI)
    add_subproject(bfdriver efi DEPENDS ${BUILDSYSTEM_TARGETS})
endif()

# ------------------------------------------------------------------------------
# Validate Build
# ------------------------------------------------------------------------------

include(scripts/cmake/validate.cmake)
validate_build()

# ------------------------------------------------------------------------------
# Force Rebuild
# ------------------------------------------------------------------------------

force_rebuild_if_needed()

# ------------------------------------------------------------------------------
# Banners
# ------------------------------------------------------------------------------

print_banner()
print_usage()

# ------------------------------------------------------------------------------
# Info
# ------------------------------------------------------------------------------

add_custom_command(TARGET info COMMAND ${CMAKE_COMMAND} -E cmake_echo_color " ")
