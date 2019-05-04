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

unset(BFFLAGS_VMM)
unset(BFFLAGS_VMM_C)
unset(BFFLAGS_VMM_CXX)
unset(BFFLAGS_VMM_LINK)

list(APPEND BFFLAGS_VMM
    -isystem ${VMM_PREFIX_PATH}/include/c++/v1
    -isystem ${VMM_PREFIX_PATH}/include
)

list(APPEND BFFLAGS_VMM
    --target=${CMAKE_HOST_SYSTEM_PROCESSOR}-vmm-elf
    --sysroot=${VMM_PREFIX_PATH}
    -fpic
    -fpie
    # -fdata-sections
    # -ffunction-sections
    -fstack-protector-strong
    -mno-red-zone
    -march=core2
    -mstackrealign
    -D${HOST_OSTYPE}
    -DSYSV
    -DENABLE_BUILD_VMM
    -DGSL_THROW_ON_CONTRACT_VIOLATION
    -DMALLOC_PROVIDED
    -DCLOCK_MONOTONIC
    -D_HAVE_LONG_DOUBLE
    -D_LDBL_EQ_DBL
    -D_POSIX_TIMERS
    -D_POSIX_THREADS
    -D_POSIX_PRIORITY_SCHEDULING
    -D_UNIX98_THREAD_MUTEX_ATTRIBUTES
    -U__STRICT_ANSI__
    -D__SINGLE_THREAD__
    -U__USER_LABEL_PREFIX__
    -D__USER_LABEL_PREFIX__=
    -D__ELF__
)

list(APPEND BFFLAGS_VMM_C
    ${BFFLAGS_VMM}
    -std=c11
)

list(APPEND BFFLAGS_VMM_CXX
    ${BFFLAGS_VMM}
    -x c++
    -std=c++17
)

string(CONCAT BFFLAGS_VMM_LINK
    "--sysroot=${CMAKE_INSTALL_PREFIX} "
    "--no-dynamic-linker "
    # "--gc-sections "
    # "--strip-all "
    "-nostdlib "
    "-pie "
    "-static "
    "-z noexecstack "
    "-z defs "
)
