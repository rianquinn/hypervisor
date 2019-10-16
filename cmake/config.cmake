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
# Build Type
# ------------------------------------------------------------------------------

if(NOT BAREFLANK_HOST_BUILD_TYPE)
    set(BAREFLANK_HOST_BUILD_TYPE ${CMAKE_BUILD_TYPE})
endif()

if(NOT BAREFLANK_TARGET_BUILD_TYPE)
    set(BAREFLANK_TARGET_BUILD_TYPE ${CMAKE_BUILD_TYPE})
endif()

# ------------------------------------------------------------------------------
# Processor Count
# ------------------------------------------------------------------------------

include(ProcessorCount)
ProcessorCount(BAREFLANK_HOST_NUMBER_CORES)

# ------------------------------------------------------------------------------
# Cache Directory
# ------------------------------------------------------------------------------

if(NOT BAREFLANK_CACHE_DIR)
    set(BAREFLANK_DEFAULT_CACHE_DIR ${CMAKE_BINARY_DIR}/../cache)

    if(EXISTS ${BAREFLANK_DEFAULT_CACHE_DIR})
        get_filename_component(BAREFLANK_CACHE_DIR "${BAREFLANK_DEFAULT_CACHE_DIR}" ABSOLUTE)
    else()
        set(BAREFLANK_CACHE_DIR ${CMAKE_BINARY_DIR}/cache)
    endif()
endif()

# ------------------------------------------------------------------------------
# Prefix Directory
# ------------------------------------------------------------------------------

if(NOT BAREFLANK_PREFIX_DIR)
    set(BAREFLANK_DEFAULT_PREFIX_DIR ${CMAKE_BINARY_DIR}/../prefix)

    if(EXISTS ${BAREFLANK_DEFAULT_PREFIX_DIR})
        get_filename_component(BAREFLANK_PREFIX_DIR "${BAREFLANK_DEFAULT_PREFIX_DIR}" ABSOLUTE)
    else()
        set(BAREFLANK_PREFIX_DIR ${CMAKE_BINARY_DIR}/prefix)
    endif()
endif()

# ------------------------------------------------------------------------------
# Build Directories
# ------------------------------------------------------------------------------

set(BAREFLANK_DEPENDS_DIR ${CMAKE_BINARY_DIR}/depends)
set(BAREFLANK_SUBPROJECT_DIR ${CMAKE_BINARY_DIR}/sub_projects)
set(BAREFLANK_EXAMPLE_DIR ${CMAKE_BINARY_DIR}/examples)

# ------------------------------------------------------------------------------
# Binaries
# ------------------------------------------------------------------------------

if(NOT BAREFLANK_CLANG_BIN)
    unset(BAREFLANK_CLANG_BIN)
    find_program(BAREFLANK_CLANG_BIN clang)
endif()

if(NOT BAREFLANK_LD_BIN)
    set(BAREFLANK_LD_BIN ${BAREFLANK_PREFIX_DIR}/host/bin/ld)
endif()

# ------------------------------------------------------------------------------
# CMake Switches
# ------------------------------------------------------------------------------

set(CMAKE_INSTALL_MESSAGE ALWAYS)
set(CMAKE_TARGET_MESSAGES ${CMAKE_VERBOSE_MAKEFILE})

# ------------------------------------------------------------------------------
# Target
# ------------------------------------------------------------------------------

set(BAREFLANK_TARGET x86_64-vmm-elf)

# ------------------------------------------------------------------------------
# Definitions
# ------------------------------------------------------------------------------

if(NOT BAREFLANK_DEBUGRING_SIZE)
    set(BAREFLANK_DEBUGRING_SIZE 32768)
endif()

string(CONCAT BAREFLANK_HOST_CXX_FLAGS
    "-DBAREFLANK_DEBUGRING_SIZE=${BAREFLANK_DEBUGRING_SIZE}"
)

string(CONCAT BAREFLANK_TARGET_CXX_FLAGS
    "-DBAREFLANK_DEBUGRING_SIZE=${BAREFLANK_DEBUGRING_SIZE}"
)

# ------------------------------------------------------------------------------
# Clang Tidy
# ------------------------------------------------------------------------------

if(NOT CMAKE_CXX_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
endif()

# ------------------------------------------------------------------------------
# Links
# ------------------------------------------------------------------------------

set(BAREFLANK_ARGAGG_URL "https://github.com/Bareflank/argagg/archive/v2.0.zip")
set(BAREFLANK_ARGAGG_URL_MD5 "aa737d49c8534dafece949539fe59f92")

set(BAREFLANK_GSL_URL "https://github.com/Bareflank/gsl/archive/v2.0.zip")
set(BAREFLANK_GSL_URL_MD5 "0cc95192658d10e43162ef7b2892e37a")

set(BAREFLANK_STANDALONE_URL "https://github.com/Bareflank/standalone_cxx/archive/v0.3.zip")
set(BAREFLANK_STANDALONE_URL_MD5 "463539784655a29ee1a6626c060a379a")

# ------------------------------------------------------------------------------
# Colors
# ------------------------------------------------------------------------------

string(ASCII 27 Esc)
set(ColorReset  "${Esc}[m")
set(ColorBold   "${Esc}[1m")
set(Red         "${Esc}[31m")
set(Green       "${Esc}[32m")
set(Yellow      "${Esc}[33m")
set(Blue        "${Esc}[34m")
set(Magenta     "${Esc}[35m")
set(Cyan        "${Esc}[36m")
set(White       "${Esc}[37m")
set(BoldRed     "${Esc}[1;31m")
set(BoldGreen   "${Esc}[1;32m")
set(BoldYellow  "${Esc}[1;33m")
set(BoldBlue    "${Esc}[1;34m")
set(BoldMagenta "${Esc}[1;35m")
set(BoldCyan    "${Esc}[1;36m")
set(BoldWhite   "${Esc}[1;37m")

# ------------------------------------------------------------------------------
# Build Command
# ------------------------------------------------------------------------------

if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    set(BAREFLANK_BUILD_COMMAND "make" CACHE INTERNAL "" FORCE)
elseif(CMAKE_GENERATOR STREQUAL "Ninja")
    set(BAREFLANK_BUILD_COMMAND "ninja" CACHE INTERNAL "" FORCE)
elseif(CMAKE_GENERATOR STREQUAL "NMake")
    set(BAREFLANK_BUILD_COMMAND "nmake" CACHE INTERNAL "" FORCE)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 15 2017 Win64")
    set(BAREFLANK_BUILD_COMMAND "msbuild hypervisor.sln" CACHE INTERNAL "" FORCE)
else()
    message(FATAL_ERROR "Unsupported cmake generator: ${CMAKE_GENERATOR}")
endif()
