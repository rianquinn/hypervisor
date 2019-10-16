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
# setup
# -----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
find_package(standalone_cxx_sdk)

# -----------------------------------------------------------------------------
# compile
# -----------------------------------------------------------------------------

add_executable(bfm
    src/main.cpp
)

target_include_directories(bfm PRIVATE
    ../../include
    ../../src
)

target_link_libraries(bfm PRIVATE
    standalone_cxx_sdk
    stdc++fs
)

# -----------------------------------------------------------------------------
# installs
# -----------------------------------------------------------------------------

install(TARGETS bfm DESTINATION bin)
