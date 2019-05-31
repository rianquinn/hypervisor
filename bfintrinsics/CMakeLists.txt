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
project(bfintrinsics CXX ASM)

# -----------------------------------------------------------------------------
# bfintrinsics
# -----------------------------------------------------------------------------

add_library(bfintrinsics
    src/null.cpp
    $<${INTEL_X64}:src/arch/x64/cache.S>
    $<${INTEL_X64}:src/arch/x64/cpuid.S>
    $<${INTEL_X64}:src/arch/x64/gdt.S>
    $<${INTEL_X64}:src/arch/x64/idt.S>
    $<${INTEL_X64}:src/arch/x64/msrs.S>
    $<${INTEL_X64}:src/arch/x64/pm.S>
    $<${INTEL_X64}:src/arch/x64/portio.S>
    $<${INTEL_X64}:src/arch/x64/rflags.S>
    $<${INTEL_X64}:src/arch/x64/srs.S>
    $<${INTEL_X64}:src/arch/intel_x64/crs.S>
    $<${INTEL_X64}:src/arch/intel_x64/drs.S>
    $<${INTEL_X64}:src/arch/intel_x64/vmx.S>
)

# -----------------------------------------------------------------------------
# installs
# -----------------------------------------------------------------------------

install(TARGETS bfintrinsics DESTINATION lib)
