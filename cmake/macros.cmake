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

include(ExternalProject)

# ------------------------------------------------------------------------------
# include_dependency
# ------------------------------------------------------------------------------

macro(include_dependency NAME)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/depends/${NAME}.cmake)
endmacro(include_dependency)

# ------------------------------------------------------------------------------
# download_dependency
# ------------------------------------------------------------------------------

# Downloads a dependency from a URL. Dependencies can either be
# a tarball or a zip file. These downloaded files are placed in the BAREFLANK_CACHE_DIR.
# If the provided MD5 hash does not match, the cached download is redownloaded.
#
# @param NAME the name of the dependency
# @param URL The URL for the dependency
# @param URL_MD5 The MD5 of the file being downloaded
#
function(download_dependency NAME URL URL_MD5)
    set(SRC ${BAREFLANK_CACHE_DIR}/${NAME})

    string(REGEX REPLACE "\\.[^.]*$" "" FILENAME ${URL})
    string(REPLACE "${FILENAME}" "" EXT ${URL})
    get_filename_component(LONG_EXT ${URL} EXT)
    if(NOT LONG_EXT MATCHES "(\\.|=)(7z|tar\\.bz2|tar\\.gz|tar\\.xz|tbz2|tgz|txz|zip)$")
        message(FATAL_ERROR "Unsupported file format: ${URL}")
    endif()

    if(LONG_EXT MATCHES ".tar.gz$")
        set(EXT ".tar.gz")
    endif()

    if(LONG_EXT MATCHES ".tar.xz$")
        set(EXT ".tar.xz")
    endif()

    if(LONG_EXT MATCHES ".tar.bz2$")
        set(EXT ".tar.bz2")
    endif()

    set(TMP ${BAREFLANK_CACHE_DIR}/${NAME}_tmp)
    set(TAR ${BAREFLANK_CACHE_DIR}/${NAME}${EXT})

    message(STATUS "    file location: ${TAR}")

    # TODO
    #
    # If a dependency needs to be downloaded, currently, we remove the
    # source directory which forces a recompile. We need to verify that
    # when this happens, all of the targets that rely on this dependency
    # are also recompiled / relinked.
    #

    foreach(ATTEMPT RANGE 1 5 1)
        if(EXISTS "${TAR}")
            message(STATUS "    checking hash: ${URL_MD5}")
            file(MD5 ${TAR} MD5)
            if(NOT "${MD5}" STREQUAL "${URL_MD5}")
                message(STATUS "    ${Red}md5 mismatch: expecting ${URL_MD5}, got ${MD5}${ColorReset}")
                set_property(GLOBAL PROPERTY "FORCE_REBUILD" "ON")
                file(REMOVE_RECURSE ${SRC})
                file(REMOVE_RECURSE ${TMP})
                file(REMOVE_RECURSE ${TAR})
                message(STATUS "    checking hash: ${Yellow}complete, redownload required${ColorReset}")
            else()
                message(STATUS "    checking hash: ${Green}complete${ColorReset}")
                break()
            endif()
        endif()

        if(ATTEMPT GREATER 1)
            message(STATUS "    attempt: ${ATTEMPT}")
        endif()

        message(STATUS "    download file: ${URL} -> ${TAR}")
        file(DOWNLOAD ${URL} ${TAR} STATUS DOWNLOAD_STATUS)
        if(NOT DOWNLOAD_STATUS MATCHES "0;")
            message(STATUS "    ${Red}failed to download ${URL}${ColorReset}")
            file(REMOVE_RECURSE ${TAR})
            continue()
        endif()
        message(STATUS "    download file: ${Green}complete${ColorReset}")
    endforeach()

    if(EXISTS ${TAR})
        file(MD5 ${TAR} MD5)
        if(NOT "${MD5}" STREQUAL "${URL_MD5}")
            message(FATAL_ERROR "Failed to download ${URL} with md5 hash of ${URL_MD5}")
        endif()
    else()
        message(FATAL_ERROR "Failed to download ${URL} with md5 hash of ${URL_MD5}")
    endif()

    if(NOT EXISTS "${SRC}")
        file(REMOVE_RECURSE ${TMP})
        file(REMOVE_RECURSE ${SRC})
        file(MAKE_DIRECTORY ${TMP})

        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xfz ${TAR}
            WORKING_DIRECTORY ${TMP}
        )

        file(GLOB CONTENTS "${TMP}/*")

        list(LENGTH CONTENTS LEN)
        if(NOT LEN EQUAL 1 OR NOT IS_DIRECTORY ${CONTENTS})
            message(FATAL_ERROR "Invalid tarball: ${URL}")
        endif()

        get_filename_component(CONTENTS ${CONTENTS} ABSOLUTE)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E rename ${CONTENTS} ${SRC}
        )

        file(REMOVE_RECURSE ${TMP})
    endif()
endfunction(download_dependency)

# ------------------------------------------------------------------------------
# add_dependency
# ------------------------------------------------------------------------------

# Uses ExternalProject_Add to add the dependency to the build. All of the
# optional arguments are passed directly to ExternalProject_Add, so most of
# ExternalProject_Add's options are supported by this function.
#
# @param NAME the name of the dependency
# @param PREFIX the prefix to install the dependency
#
function(add_dependency NAME PREFIX)
    if(PREFIX MATCHES "target")
        list(APPEND ARGN CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET})
    elseif(PREFIX MATCHES "host")
        list(APPEND ARGN CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${BAREFLANK_PREFIX_DIR}/host)
    else()
        list(APPEND ARGN CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${BAREFLANK_PREFIX_DIR})
    endif()

    if(PREFIX MATCHES "target")
        list(APPEND ARGN CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${BAREFLANK_TOOLCHAIN_FILE})
    elseif(PREFIX MATCHES "host")
        list(APPEND ARGN
            CMAKE_ARGS -DCMAKE_INSTALL_MESSAGE=${CMAKE_INSTALL_MESSAGE}
            CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}
            CMAKE_ARGS -DCMAKE_BUILD_TYPE=${BAREFLANK_HOST_BUILD_TYPE}
        )

        if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
            list(APPEND ARGN
                CMAKE_ARGS -DCMAKE_TARGET_MESSAGES=${CMAKE_TARGET_MESSAGES}
            )
        endif()
    endif()

    if(PREFIX MATCHES "target" OR PREFIX MATCHES "host")
        set(FULLNAME ${NAME}_${PREFIX})
    else()
        set(FULLNAME ${NAME})
    endif()

    ExternalProject_Add(
        ${FULLNAME}
        ${ARGN}
        PREFIX              ${BAREFLANK_DEPENDS_DIR}/${FULLNAME}
        STAMP_DIR           ${BAREFLANK_DEPENDS_DIR}/${FULLNAME}/stamp
        TMP_DIR             ${BAREFLANK_DEPENDS_DIR}/${FULLNAME}/tmp
        BINARY_DIR          ${BAREFLANK_DEPENDS_DIR}/${FULLNAME}/build
        LOG_DIR             ${BAREFLANK_DEPENDS_DIR}/${FULLNAME}/logs
        SOURCE_DIR          ${BAREFLANK_CACHE_DIR}/${NAME}
        DEPENDS             ${DEPENDS}
    )

    ExternalProject_Add_Step(
        ${FULLNAME}
        ${FULLNAME}_cleanup
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${BAREFLANK_DEPENDS_DIR}/${FULLNAME}/src
        DEPENDEES configure
    )
endfunction(add_dependency)

# Uses ExternalProject_Add_Step to add an additional step to external project
# add after "install" is executed by ExternalProject_Add. Only one additional
# step is supported. Like add_dependency, add_dependency_step passes all
# optional parameters to ExternalProject_Add_Step, so most options are
# supported.
#
# @param NAME the name of the dependency
# @param PREFIX the prefix to install the dependency
#
function(add_dependency_step NAME PREFIX)
    ExternalProject_Add_Step(
        ${NAME}_${PREFIX}
        step_${NAME}_${PREFIX}
        ${ARGN}
        DEPENDEES install
    )
endfunction(add_dependency_step)

# ------------------------------------------------------------------------------
# add_subproject
# ------------------------------------------------------------------------------

# Uses ExternalProject_Add to add a subproject to the build. All of the
# optional arguments are passed directly to ExternalProject_Add, so most of
# ExternalProject_Add's options are supported by this function.
#
# @param NAME the name of the subproject
# @param PREFIX the prefix to install the subproject
#
function(add_subproject NAME PREFIX)
    if(PREFIX MATCHES "target")
        list(APPEND ARGN
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}
        )
    else()
        list(APPEND ARGN
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${BAREFLANK_PREFIX_DIR}/host
        )
    endif()

    if(PREFIX MATCHES "target")
        if(NOT NAME MATCHES "uefi")
            list(APPEND ARGN
                CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${BAREFLANK_TOOLCHAIN_FILE}
            )
        endif()
    else()
        list(APPEND ARGN
            CMAKE_ARGS -DCMAKE_INSTALL_MESSAGE=${CMAKE_INSTALL_MESSAGE}
            CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}
            CMAKE_ARGS -DCMAKE_BUILD_TYPE=${BAREFLANK_HOST_BUILD_TYPE}
        )

        if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
            list(APPEND ARGN
                CMAKE_ARGS -DCMAKE_TARGET_MESSAGES=${CMAKE_TARGET_MESSAGES}
            )
        endif()
    endif()

    if(PREFIX MATCHES "target")
        if(BAREFLANK_TARGET_BUILD_TYPE MATCHES "Debug")
            list(APPEND ARGN
                CMAKE_ARGS -DCMAKE_CXX_CLANG_TIDY=${CMAKE_CXX_CLANG_TIDY}
            )
        endif()
    else()
        if(BAREFLANK_HOST_BUILD_TYPE MATCHES "Debug")
            list(APPEND ARGN
                CMAKE_ARGS -DCMAKE_CXX_CLANG_TIDY=${CMAKE_CXX_CLANG_TIDY}
            )
        endif()
    endif()

    ExternalProject_Add(
        ${NAME}_${PREFIX}
        ${ARGN}
        PREFIX              ${BAREFLANK_SUBPROJECT_DIR}/${NAME}_${PREFIX}
        STAMP_DIR           ${BAREFLANK_SUBPROJECT_DIR}/${NAME}_${PREFIX}/stamp
        TMP_DIR             ${BAREFLANK_SUBPROJECT_DIR}/${NAME}_${PREFIX}/tmp
        BINARY_DIR          ${BAREFLANK_SUBPROJECT_DIR}/${NAME}_${PREFIX}/build
        LOG_DIR             ${BAREFLANK_SUBPROJECT_DIR}/${NAME}_${PREFIX}/logs
        UPDATE_COMMAND      cmake -E echo -- Checking for changes
        DEPENDS             ${DEPENDS}
    )

    ExternalProject_Add_Step(
        ${NAME}_${PREFIX}
        ${NAME}_${PREFIX}_cleanup
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${BAREFLANK_SUBPROJECT_DIR}/${NAME}_${PREFIX}/src
        DEPENDEES configure
    )
endfunction(add_subproject)

# ------------------------------------------------------------------------------
# setup_interfaces
# ------------------------------------------------------------------------------

# Creates the public libraries interfaces so that other projects can leverage
# the bareflank sdk libraries without any issues using CMake. All of the
# compiler options, flags and libraries are defined here so that users of our
# libraries do not need to understand how to compile
#
function(setup_interfaces)
    add_library(bareflank_host INTERFACE)
    add_library(bareflank_target INTERFACE)

    # target_link_libraries(bareflank_target INTERFACE
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libc++.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libc++abi.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libbfunwind.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libc.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libm.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libbfruntime.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libc++.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libc++abi.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libbfunwind.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libc.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libm.a
    #     ${BAREFLANK_PREFIX_DIR}/${BAREFLANK_TARGET}/lib/libbfruntime.a
    # )

    target_include_directories(bareflank_host INTERFACE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
    )

    target_include_directories(bareflank_target INTERFACE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
    )

    export(TARGETS bareflank_host FILE bareflank_hostConfig.cmake APPEND)
    export(PACKAGE bareflank_host)

    export(TARGETS bareflank_target FILE bareflank_targetConfig.cmake APPEND)
    export(PACKAGE bareflank_target)
endfunction(setup_interfaces)

# ------------------------------------------------------------------------------
# add_subproject
# ------------------------------------------------------------------------------

function(print_init_banner)
    message(STATUS "${BoldMagenta}  ___                __ _           _   ${ColorReset}")
    message(STATUS "${BoldMagenta} | _ ) __ _ _ _ ___ / _| |__ _ _ _ | |__${ColorReset}")
    message(STATUS "${BoldMagenta} | _ \\/ _` | '_/ -_)  _| / _` | ' \\| / /${ColorReset}")
    message(STATUS "${BoldMagenta} |___/\\__,_|_| \\___|_| |_\\__,_|_||_|_\\_\\${ColorReset}")
    message(STATUS "")
    message(STATUS "${Green} Please give us a star on: ${White}https://github.com/Bareflank/hypervisor${ColorReset}")
    message(STATUS "")
endfunction(print_init_banner)

function(print_fini_banner)
    message(STATUS "")
    if(UNIX)
        message(STATUS "${Green} For more build options:${ColorReset}")
        message(STATUS "${Yellow}    ${BAREFLANK_BUILD_COMMAND} info${ColorReset}")
    else()
        message(STATUS "${Green} Additional build options include:${ColorReset}")
        message(STATUS "${Yellow}    cmake --build . --target unittest${ColorReset}")
        message(STATUS "${Yellow}    cmake --build . --target clean-all${ColorReset}")
    endif()
    message(STATUS "")
endfunction(print_fini_banner)


