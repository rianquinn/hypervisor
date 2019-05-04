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
# General
# ------------------------------------------------------------------------------

if(BUILD_SHARED_LIBS)
    invalid_config("BUILD_SHARED_LIBS not supported")
endif()

if(NOT ENABLE_BUILD_VMM AND NOT ENABLE_BUILD_USERSPACE AND NOT ENABLE_BUILD_TEST)
    invalid_config("VMM, USERSAPCE and TEST disabled. You must enable one.")
endif()

# ------------------------------------------------------------------------------
# VMM
# ------------------------------------------------------------------------------

if(ENABLE_BUILD_VMM)
    if(WIN32)
        invalid_config("ENABLE_BUILD_VMM is only supported on Linux and Cygwin")
    endif()
endif()

# ------------------------------------------------------------------------------
# Userspace
# ------------------------------------------------------------------------------

if(ENABLE_BUILD_USERSPACE)
endif()

# ------------------------------------------------------------------------------
# Test
# ------------------------------------------------------------------------------

if(ENABLE_BUILD_TEST)
    if(WIN32 OR CYGWIN)
        invalid_config("ENABLE_BUILD_TEST is only supported on Linux")
    endif()
    if(NOT ENABLE_BUILD_VMM)
        invalid_config("ENABLE_BUILD_VMM must be enabled if ENABLE_BUILD_TEST is enabled")
    endif()
endif()

# ------------------------------------------------------------------------------
# EFI
# ------------------------------------------------------------------------------

if(ENABLE_BUILD_EFI)
    if(WIN32 OR CYGWIN)
        invalid_config("ENABLE_BUILD_EFI is only supported on Linux")
    endif()

    if(NOT ENABLE_BUILD_VMM)
        invalid_config("ENABLE_BUILD_VMM must be enabled if ENABLE_BUILD_EFI is enabled")
    endif()
endif()

# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------

if(ENABLE_BUILD_EXAMPLES)
    if(NOT ENABLE_BUILD_VMM)
        invalid_config("ENABLE_BUILD_VMM must be enabled if ENABLE_BUILD_EXAMPLES is enabled")
    endif()
endif()

# ------------------------------------------------------------------------------
# Developer Features
# ------------------------------------------------------------------------------

if(ENABLE_ASAN)
    if(ENABLE_USAN)
        invalid_config("ENABLE_USAN cannot be enabled if ENABLE_ASAN is enabled")
    endif()
    if(WIN32 OR CYGWIN)
        invalid_config("ENABLE_ASAN is only supported on Linux")
    endif()
endif()

if(ENABLE_USAN)
    if(ENABLE_ASAN)
        invalid_config("ENABLE_ASAN cannot be enabled if ENABLE_USAN is enabled")
    endif()
    if(WIN32 OR CYGWIN)
        invalid_config("ENABLE_USAN is only supported on Linux")
    endif()
endif()

if(ENABLE_CODECOV)
    if(NOT ENABLE_BUILD_TEST)
        invalid_config("ENABLE_BUILD_TEST must be enabled if ENABLE_CODECOV is enabled")
    endif()
    if(WIN32 OR CYGWIN)
        invalid_config("ENABLE_CODECOV is only supported on Linux")
    endif()
endif()

if(ENABLE_TIDY)
    if(WIN32 OR CYGWIN)
        invalid_config("ENABLE_TIDY is only supported on Linux")
    endif()
endif()

if(ENABLE_FORMAT)
    if(WIN32)
        invalid_config("ENABLE_TIDY is only supported on Linux and Cygwin")
    endif()
endif()
