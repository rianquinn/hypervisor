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

include(${SOURCE_ROOT_DIR}/scripts/cmake/macros.cmake)

enable_asm()
setup_generator_expression_shorthands()

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${SOURCE_ROOT_DIR}/bfack/include
    ${SOURCE_ROOT_DIR}/bfdriver/include
    ${SOURCE_ROOT_DIR}/bfdummy/include
    ${SOURCE_ROOT_DIR}/bfelf_loader/include
    ${SOURCE_ROOT_DIR}/bfintrinsics/include
    ${SOURCE_ROOT_DIR}/bfm/include
    ${SOURCE_ROOT_DIR}/bfruntime/include
    ${SOURCE_ROOT_DIR}/bfsdk/include
    ${SOURCE_ROOT_DIR}/bfunwind/include
    ${SOURCE_ROOT_DIR}/bfvmm/include
)

set(CMAKE_C_COMPILER "")
set(CMAKE_C_COMPILER_WORKS 0)

if(CMAKE_INSTALL_PREFIX MATCHES "test")
    find_package(bareflank_test)
endif()

get_cmake_property(_vars CACHE_VARIABLES)
foreach (_var ${_vars})
    set(${_var} ${${_var}})
endforeach()
