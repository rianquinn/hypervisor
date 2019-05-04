#
# Bareflank Hypervisor
# Copyright (C) 2019 Assured Information Security, Inc.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

cmake_minimum_required(VERSION 3.13)
project(bfm CXX)

# -----------------------------------------------------------------------------
# bfm
# -----------------------------------------------------------------------------

list(APPEND SOURCES
    src/ioctl_driver.cpp
    $<${LINUX}:src/platform/linux/ioctl.cpp>
    $<${WINDOWS}:src/platform/windows/ioctl.cpp>
)

if(CMAKE_INSTALL_PREFIX MATCHES "userspace")
    add_executable(bfm ${SOURCES} src/main.cpp)
else()
    add_library(bfm ${SOURCES})
endif()

target_include_directories(bfm PRIVATE
    $<${LINUX}:${CMAKE_CURRENT_LIST_DIR}/src/platform/linux>
    $<${WINDOWS}:${CMAKE_CURRENT_LIST_DIR}/src/platform/windows>
)

# do_test(tests/test_ioctl_driver.cpp DEPENDS bfm)

# -----------------------------------------------------------------------------
# installs
# -----------------------------------------------------------------------------

install(TARGETS bfm DESTINATION bin)
