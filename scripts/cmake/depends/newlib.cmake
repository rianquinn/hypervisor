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

if(ENABLE_BUILD_VMM)
    message(STATUS "Including dependency: newlib")

    download_dependency(
        newlib
        URL         ${NEWLIB_URL}
        URL_MD5     ${NEWLIB_URL_MD5}
    )

    if(NOT DEFINED ENV{CLANG_BIN})
        find_program(CLANG_BIN clang)
    else()
        set(CLANG_BIN $ENV{CLANG_BIN})
    endif()

    if(CLANG_BIN)
        set(CMAKE_C_COMPILER ${CLANG_BIN})
        set(CMAKE_CXX_COMPILER ${CLANG_BIN})
    else()
        message(FATAL_ERROR "Unable to find clang")
    endif()

    set(AR_FOR_TARGET ar)
    set(AS_FOR_TARGET as)
    set(NM_FOR_TARGET nm)
    set(OBJCOPY_FOR_TARGET objcopy)
    set(OBJDUMP_FOR_TARGET objdump)
    set(RANLIB_FOR_TARGET ranlib)
    set(READELF_FOR_TARGET readelf)
    set(STRIP_FOR_TARGET strip)

    setup_flags(
        vmm
        NOWARNINGS
    )

    list(APPEND NEWLIB_CONFIGURE_FLAGS
        --disable-libgloss
        --disable-multilib
        --disable-newlib-supplied-syscalls
        --enable-newlib-multithread
        --enable-newlib-iconv
        --enable-lite-exit
        CFLAGS_FOR_TARGET=${CMAKE_C_FLAGS}
        CXXFLAGS_FOR_TARGET=${CMAKE_CXX_FLAGS}
        CC_FOR_TARGET=${CLANG_BIN}
        CXX_FOR_TARGET=${CLANG_BIN}
        AR_FOR_TARGET=${AR_FOR_TARGET}
        AS_FOR_TARGET=${AS_FOR_TARGET}
        NM_FOR_TARGET=${NM_FOR_TARGET}
        OBJCOPY_FOR_TARGET=${OBJCOPY_FOR_TARGET}
        OBJDUMP_FOR_TARGET=${OBJDUMP_FOR_TARGET}
        RANLIB_FOR_TARGET=${RANLIB_FOR_TARGET}
        READELF_FOR_TARGET=${READELF_FOR_TARGET}
        STRIP_FOR_TARGET=${STRIP_FOR_TARGET}
        --prefix=${PREFIXES_DIR}
        --target=${VMM_PREFIX}
    )

    add_dependency(
        newlib vmm
        CONFIGURE_COMMAND   ${CACHE_DIR}/newlib/configure ${NEWLIB_CONFIGURE_FLAGS}
        BUILD_COMMAND       make -j${HOST_NUMBER_CORES}
        INSTALL_COMMAND     make install
        DEPENDS             binutils_${VMM_PREFIX}
    )

    add_dependency_step(
        newlib vmm
        COMMAND eval "${CMAKE_COMMAND} -E remove_directory ${PREFIXES_DIR}/share"
    )
endif()
