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
project(bfdummy CXX)

find_package(bareflank_vmm)

add_executable(dummy_main src/main.cpp)
add_executable(dummy_main_init_fails src/main.cpp)
add_executable(dummy_main_fini_fails src/main.cpp)
add_executable(dummy_main_add_mdl_fails src/main.cpp)
add_executable(dummy_main_get_drr_fails src/main.cpp)
add_executable(dummy_main_set_rsdp_fails src/main.cpp)
add_executable(dummy_main_vmm_init_fails src/main.cpp)
add_executable(dummy_main_vmm_fini_fails src/main.cpp)

target_link_libraries(dummy_main PRIVATE bareflank_internal)
target_link_libraries(dummy_main_init_fails PRIVATE bareflank_internal)
target_link_libraries(dummy_main_fini_fails PRIVATE bareflank_internal)
target_link_libraries(dummy_main_add_mdl_fails PRIVATE bareflank_internal)
target_link_libraries(dummy_main_get_drr_fails PRIVATE bareflank_internal)
target_link_libraries(dummy_main_set_rsdp_fails PRIVATE bareflank_internal)
target_link_libraries(dummy_main_vmm_init_fails PRIVATE bareflank_internal)
target_link_libraries(dummy_main_vmm_fini_fails PRIVATE bareflank_internal)

target_compile_definitions(dummy_main_init_fails PRIVATE REQUEST_INIT_FAILS)
target_compile_definitions(dummy_main_fini_fails PRIVATE REQUEST_FINI_FAILS)
target_compile_definitions(dummy_main_add_mdl_fails PRIVATE REQUEST_ADD_MDL_FAILS)
target_compile_definitions(dummy_main_get_drr_fails PRIVATE REQUEST_GET_DRR_FAILS)
target_compile_definitions(dummy_main_set_rsdp_fails PRIVATE REQUEST_SET_RSDP_FAILS)
target_compile_definitions(dummy_main_vmm_init_fails PRIVATE REQUEST_VMM_INIT_FAILS)
target_compile_definitions(dummy_main_vmm_fini_fails PRIVATE REQUEST_VMM_FINI_FAILS)

install(TARGETS dummy_main DESTINATION bin)
install(TARGETS dummy_main_init_fails DESTINATION bin)
install(TARGETS dummy_main_fini_fails DESTINATION bin)
install(TARGETS dummy_main_add_mdl_fails DESTINATION bin)
install(TARGETS dummy_main_get_drr_fails DESTINATION bin)
install(TARGETS dummy_main_set_rsdp_fails DESTINATION bin)
install(TARGETS dummy_main_vmm_init_fails DESTINATION bin)
install(TARGETS dummy_main_vmm_fini_fails DESTINATION bin)
