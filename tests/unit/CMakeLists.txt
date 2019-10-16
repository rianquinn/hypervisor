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
project(unit CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
find_package(standalone_cxx_sdk)

# ------------------------------------------------------------------------------
# Test Macro
# ------------------------------------------------------------------------------

macro(add_unittest NAME)
    add_executable(${NAME} ${NAME}.cpp)
    target_link_libraries(${NAME} PRIVATE standalone_cxx_sdk catch2_main)
    target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include)
    target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../src)
    target_compile_definitions(${NAME} PRIVATE GSL_THROW_ON_CONTRACT_VIOLATION)
    add_test(${NAME} ${NAME})
endmacro(add_unittest)

# ------------------------------------------------------------------------------
# Directories
# ------------------------------------------------------------------------------

add_subdirectory(bfm)
add_subdirectory(common)
add_subdirectory(file)

# ------------------------------------------------------------------------------
# Quiet Install Command
# ------------------------------------------------------------------------------

set(IGNOREME "${CMAKE_INSTALL_MESSAGE}")
install(CODE "MESSAGE(\"Nothing to install\")")
