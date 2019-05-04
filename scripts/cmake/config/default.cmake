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

# ------------------------------------------------------------------------------
# Build Switches (these are exposed to extensions)
# ------------------------------------------------------------------------------

option(ENABLE_BUILD_VMM "Build VMM components" ON)
option(ENABLE_BUILD_USERSPACE "Build userspace components" ON)
option(ENABLE_BUILD_TEST "Build test components" OFF)
option(ENABLE_BUILD_EFI "Build efi boot-time components" OFF)
option(ENABLE_BUILD_EXAMPLES "Build examples" OFF)

# ------------------------------------------------------------------------------
# Developer Switches (not exposed to extensions)
# ------------------------------------------------------------------------------

option(ENABLE_COMPILER_WARNINGS "Enable compiler warnings" ON)
option(ENABLE_ASAN "Enable clang AddressSanitizer" OFF)
option(ENABLE_USAN "Enable clang UndefinedBehaviorSanitizer" OFF)
option(ENABLE_CODECOV "Enable code coverage from codecov.io" OFF)
option(ENABLE_TIDY "Enable clang-tidy" OFF)
option(ENABLE_FORMAT "Enable astyle formatting" OFF)

# ------------------------------------------------------------------------------
# Read-Only (do not modify, these are exposed to extensions)
# ------------------------------------------------------------------------------

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(HOST_FORMAT_TYPE "elf" CACHE INTERNAL "" FORCE)
    set(HOST_SYSTEM_NAME "Linux" CACHE INTERNAL "" FORCE)
    set(HOST_OSTYPE "UNIX" CACHE INTERNAL "" FORCE)
    set(HOST_ABITYPE "SYSV" CACHE INTERNAL "" FORCE)
else()
    set(HOST_FORMAT_TYPE "pe" CACHE INTERNAL "" FORCE)
    set(HOST_SYSTEM_NAME "Windows" CACHE INTERNAL "" FORCE)
    set(HOST_OSTYPE "WIN64" CACHE INTERNAL "" FORCE)
    set(HOST_ABITYPE "MS64" CACHE INTERNAL "" FORCE)
endif()

set(SOURCE_ROOT_DIR ${CMAKE_SOURCE_DIR} CACHE INTERNAL "" FORCE)

# ==============================================================================
# PRIVATE *** DO NOT MODIFY ***
# ==============================================================================

# The remaining configuration items are for internal use only. These are
# subject to change and should not be used by an extension, nor should these
# be modified by the command line for any reason. You have been warned.

# ------------------------------------------------------------------------------
# Build Type
# ------------------------------------------------------------------------------

if (NOT CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# ------------------------------------------------------------------------------
# Processor Count
# ------------------------------------------------------------------------------

include(ProcessorCount)
ProcessorCount(HOST_NUMBER_CORES)

# ------------------------------------------------------------------------------
# Colors
# ------------------------------------------------------------------------------

string(ASCII 27 Esc)
set(ColorReset  "${Esc}[m" CACHE INTERNAL "" FORCE)
set(ColorBold   "${Esc}[1m" CACHE INTERNAL "" FORCE)
set(Red         "${Esc}[31m" CACHE INTERNAL "" FORCE)
set(Green       "${Esc}[32m" CACHE INTERNAL "" FORCE)
set(Yellow      "${Esc}[33m" CACHE INTERNAL "" FORCE)
set(Blue        "${Esc}[34m" CACHE INTERNAL "" FORCE)
set(Magenta     "${Esc}[35m" CACHE INTERNAL "" FORCE)
set(Cyan        "${Esc}[36m" CACHE INTERNAL "" FORCE)
set(White       "${Esc}[37m" CACHE INTERNAL "" FORCE)
set(BoldRed     "${Esc}[1;31m" CACHE INTERNAL "" FORCE)
set(BoldGreen   "${Esc}[1;32m" CACHE INTERNAL "" FORCE)
set(BoldYellow  "${Esc}[1;33m" CACHE INTERNAL "" FORCE)
set(BoldBlue    "${Esc}[1;34m" CACHE INTERNAL "" FORCE)
set(BoldMagenta "${Esc}[1;35m" CACHE INTERNAL "" FORCE)
set(BoldCyan    "${Esc}[1;36m" CACHE INTERNAL "" FORCE)
set(BoldWhite   "${Esc}[1;37m" CACHE INTERNAL "" FORCE)

# ------------------------------------------------------------------------------
# Build Command
# ------------------------------------------------------------------------------

if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    set(BUILD_COMMAND "make" CACHE INTERNAL "" FORCE)
elseif(CMAKE_GENERATOR STREQUAL "Ninja")
    set(BUILD_COMMAND "ninja" CACHE INTERNAL "" FORCE)
elseif(CMAKE_GENERATOR STREQUAL "NMake")
    set(BUILD_COMMAND "nmake" CACHE INTERNAL "" FORCE)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 15 2017 Win64")
    set(BUILD_COMMAND "msbuild hypervisor.sln" CACHE INTERNAL "" FORCE)
else()
    message(FATAL_ERROR "Unsupported cmake generator: ${CMAKE_GENERATOR}")
endif()

# ------------------------------------------------------------------------------
# Source Tree
# ------------------------------------------------------------------------------

set(SOURCE_CMAKE_DIR ${CMAKE_SOURCE_DIR}/scripts/cmake CACHE INTERNAL "" FORCE)
set(SOURCE_CONFIG_DIR ${CMAKE_SOURCE_DIR}/scripts/cmake/config CACHE INTERNAL "" FORCE)
set(SOURCE_DEPENDS_DIR ${CMAKE_SOURCE_DIR}/scripts/cmake/depends CACHE INTERNAL "" FORCE)
set(SOURCE_FLAGS_DIR ${CMAKE_SOURCE_DIR}/scripts/cmake/flags CACHE INTERNAL "" FORCE)
set(SOURCE_TOOLCHAIN_DIR ${CMAKE_SOURCE_DIR}/scripts/cmake/toolchain CACHE INTERNAL "" FORCE)
set(SOURCE_UTIL_DIR ${CMAKE_SOURCE_DIR}/scripts/util CACHE INTERNAL "" FORCE)

# ------------------------------------------------------------------------------
# Cache Directory
# ------------------------------------------------------------------------------

set(CACHE_DIR ${CMAKE_SOURCE_DIR}/../cache CACHE INTERNAL "" FORCE)

if(EXISTS ${CACHE_DIR})
    get_filename_component(CACHE_DIR "${CACHE_DIR}" ABSOLUTE)
else()
    set(CACHE_DIR ${CMAKE_BINARY_DIR}/cache CACHE INTERNAL "" FORCE)
endif()

# ------------------------------------------------------------------------------
# Non-configurable directories
# ------------------------------------------------------------------------------

set(DEPENDS_DIR ${CMAKE_BINARY_DIR}/depends CACHE INTERNAL "" FORCE)
set(PREFIXES_DIR ${CMAKE_BINARY_DIR}/prefixes CACHE INTERNAL "" FORCE)

# ------------------------------------------------------------------------------
# CMake Switches
# ------------------------------------------------------------------------------

set(CMAKE_TARGET_MESSAGES ${CMAKE_VERBOSE_MAKEFILE} CACHE INTERNAL "" FORCE)
set(CMAKE_INSTALL_MESSAGE ALWAYS CACHE INTERNAL "" FORCE)

# ------------------------------------------------------------------------------
# Prefixes
# ------------------------------------------------------------------------------

set(VMM_PREFIX ${CMAKE_HOST_SYSTEM_PROCESSOR}-vmm-elf CACHE INTERNAL "" FORCE)
set(USERSPACE_PREFIX ${CMAKE_HOST_SYSTEM_PROCESSOR}-userspace-${HOST_FORMAT_TYPE} CACHE INTERNAL "" FORCE)
set(TEST_PREFIX ${CMAKE_HOST_SYSTEM_PROCESSOR}-test-${HOST_FORMAT_TYPE} CACHE INTERNAL "" FORCE)
set(EFI_PREFIX ${CMAKE_HOST_SYSTEM_PROCESSOR}-efi-pe CACHE INTERNAL "" FORCE)

set(VMM_PREFIX_PATH ${PREFIXES_DIR}/${VMM_PREFIX} CACHE INTERNAL "" FORCE)
set(USERSPACE_PREFIX_PATH ${PREFIXES_DIR}/${USERSPACE_PREFIX} CACHE INTERNAL "" FORCE)
set(TEST_PREFIX_PATH ${PREFIXES_DIR}/${TEST_PREFIX} CACHE INTERNAL "" FORCE)
set(EFI_PREFIX_PATH ${PREFIXES_DIR}/${EFI_PREFIX} CACHE INTERNAL "" FORCE)

# ------------------------------------------------------------------------------
# Scripts
# ------------------------------------------------------------------------------

set(TIDY_SCRIPT ${SOURCE_UTIL_DIR}/check_clang_tidy.sh CACHE INTERNAL "" FORCE)
set(ASTYLE_SCRIPT ${SOURCE_UTIL_DIR}/check_astyle_format.sh CACHE INTERNAL "" FORCE)

# ------------------------------------------------------------------------------
# Toolchains
# ------------------------------------------------------------------------------

set(VMM_TOOLCHAIN_PATH ${SOURCE_TOOLCHAIN_DIR}/clang_${CMAKE_HOST_SYSTEM_PROCESSOR}_vmm.cmake CACHE INTERNAL "" FORCE)
set(USERSPACE_TOOLCHAIN_PATH "" CACHE INTERNAL "" FORCE)
set(TEST_TOOLCHAIN_PATH "" CACHE INTERNAL "" FORCE)
set(EFI_TOOLCHAIN_PATH ${SOURCE_TOOLCHAIN_DIR}/clang_${CMAKE_HOST_SYSTEM_PROCESSOR}_efi.cmake CACHE INTERNAL "" FORCE)

# ------------------------------------------------------------------------------
# Links
# ------------------------------------------------------------------------------

set(ARGPARSE_URL "https://github.com/Bareflank/argparse/archive/v1.1.zip" CACHE INTERNAL "" FORCE)
set(ARGPARSE_URL_MD5 "cf9f7cd53e10f78f798d8eba7b25dbcc" CACHE INTERNAL "" FORCE)

set(ASTYLE_URL "https://github.com/Bareflank/astyle/archive/v2.0.zip" CACHE INTERNAL "" FORCE)
set(ASTYLE_URL_MD5 "4315484ed9b4fbe4dfd534c5db5499a0" CACHE INTERNAL "" FORCE)

set(BINUTILS_URL "https://ftp.gnu.org/gnu/binutils/binutils-2.32.tar.gz" CACHE INTERNAL "" FORCE)
set(BINUTILS_URL_MD5 "d1119c93fc0ed3007be4a84dd186af55" CACHE INTERNAL "" FORCE)

set(CATCH_URL "https://github.com/Bareflank/Catch/archive/v2.0.zip" CACHE INTERNAL "" FORCE)
set(CATCH_URL_MD5 "c60970ceed825b00af11930acc86b2d8" CACHE INTERNAL "" FORCE)

set(GNUEFI_URL "https://github.com/Bareflank/gnu-efi/archive/v2.0.zip" CACHE INTERNAL "" FORCE)
set(GNUEFI_URL_MD5 "3cd10dc9c14f4a3891f8537fd78ed04f" CACHE INTERNAL "" FORCE)

set(GSL_URL "https://github.com/Bareflank/gsl/archive/v2.0.zip" CACHE INTERNAL "" FORCE)
set(GSL_URL_MD5 "0cc95192658d10e43162ef7b2892e37a" CACHE INTERNAL "" FORCE)

set(HIPPOMOCKS_URL "https://github.com/Bareflank/hippomocks/archive/v1.2.zip" CACHE INTERNAL "" FORCE)
set(HIPPOMOCKS_URL_MD5 "6a0928dfee03fbf4c12c36219c696bae" CACHE INTERNAL "" FORCE)

set(JSON_URL "https://github.com/nlohmann/json/archive/v3.1.2.zip" CACHE INTERNAL "" FORCE)
set(JSON_URL_MD5 "a5690d84678f50860550633363a44a89" CACHE INTERNAL "" FORCE)

set(LIBCXX_URL "https://github.com/Bareflank/libcxx/archive/v2.0.zip" CACHE INTERNAL "" FORCE)
set(LIBCXX_URL_MD5 "564e6377485bf8527cab085075a626e1" CACHE INTERNAL "" FORCE)

set(LIBCXXABI_URL "https://github.com/Bareflank/libcxxabi/archive/v2.0.1.zip" CACHE INTERNAL "" FORCE)
set(LIBCXXABI_URL_MD5 "f5da5c086bf79ae88b46ee44cbeca2e9" CACHE INTERNAL "" FORCE)

set(LLVM_URL "https://github.com/Bareflank/llvm/archive/v2.0.zip" CACHE INTERNAL "" FORCE)
set(LLVM_URL_MD5 "7a088762b40665815e47e49dc97ac59f" CACHE INTERNAL "" FORCE)

set(NEWLIB_URL "https://github.com/Bareflank/newlib/archive/v2.0.zip" CACHE INTERNAL "" FORCE)
set(NEWLIB_URL_MD5 "91588a1a925c953453b2f04acecbcb88" CACHE INTERNAL "" FORCE)

# ------------------------------------------------------------------------------
# Default Flags
# ------------------------------------------------------------------------------

include(${SOURCE_FLAGS_DIR}/efi_flags.cmake)
include(${SOURCE_FLAGS_DIR}/test_flags.cmake)
include(${SOURCE_FLAGS_DIR}/userspace_flags.cmake)
include(${SOURCE_FLAGS_DIR}/vmm_flags.cmake)
include(${SOURCE_FLAGS_DIR}/warning_flags.cmake)
