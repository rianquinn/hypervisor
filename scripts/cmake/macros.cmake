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

if(ENABLE_BUILD_TEST)
    include(CTest)
    enable_testing(true)
endif()

# ------------------------------------------------------------------------------
# include_external_config
# ------------------------------------------------------------------------------

macro(include_external_config)
    if(CONFIG)
        foreach(c ${CONFIG})
            if(EXISTS "${SOURCE_CONFIG_DIR}/${c}.cmake")
                message(STATUS "Config: ${SOURCE_CONFIG_DIR}/${c}.cmake")
                include(${SOURCE_CONFIG_DIR}/${c}.cmake)
                continue()
            endif()
            if(NOT IS_ABSOLUTE "${c}")
                get_filename_component(c "${CMAKE_BINARY_DIR}/${c}" ABSOLUTE)
            endif()
            if(EXISTS "${c}")
                message(STATUS "Config: ${c}")
                include(${c})
                continue()
            endif()

            message(FATAL_ERROR "File not found: ${c}")
        endforeach(c)
    elseif(EXISTS "${CMAKE_SOURCE_DIR}/../config.cmake")
        get_filename_component(CONFIG "${CMAKE_SOURCE_DIR}/../config.cmake" ABSOLUTE)
        message(STATUS "Config: ${CONFIG}")
        include(${CONFIG})
    endif()

    set_vmm(vmm DEFAULT)
    message(STATUS "Type: ${CMAKE_BUILD_TYPE}")

endmacro(include_external_config)

# ------------------------------------------------------------------------------
# include_external_extensions
# ------------------------------------------------------------------------------

macro(include_external_extensions)
    foreach(e ${EXTENSION})
        if(NOT IS_ABSOLUTE "${e}")
            get_filename_component(e "${CMAKE_BINARY_DIR}/${e}" ABSOLUTE)
        endif()
        if(EXISTS "${e}/CMakeLists.txt")
            message(STATUS "Extension: ${e}")
            include(${e}/CMakeLists.txt)
        else()
            message(FATAL_ERROR "Extension not found: ${e}")
        endif()
    endforeach(e)
endmacro(include_external_extensions)

# ------------------------------------------------------------------------------
# setup_flags
# ------------------------------------------------------------------------------

# Sets up CMAKE_C_FLAGS and CMAKE_CXX_FLAGS based on the provided flags and
# prefix value. Each time this is executed, CMAKE_XXX_FLAGS are overwritten
# and globally set. The add_subproject function performs this action on your
# behalf, and this function generally should not be used unless you are
# compiling a dependency, in which case, you will need to run this manually.
#
# @param PREFIX (macro arg) Defines which prefix the flags belong too. Valid
#     values are: vmm, userspace, and test
# @param NOWARNINGS Disable warnings
# @param C_FLAGS Additional C flags to add to CMAKE_C_FLAGS
# @param CXX_FLAGS Additional CXX flags to add to CMAKE_CXX_FLAGS
#
macro(setup_flags PREFIX)
    set(options NOWARNINGS)
    set(multiVal C_FLAGS CXX_FLAGS)
    cmake_parse_arguments(ARG "${options}" "" "${multiVal}" ${ARGN})

    unset(CMAKE_C_FLAGS)
    unset(CMAKE_CXX_FLAGS)
    unset(CMAKE_C_LINK_FLAGS)
    unset(CMAKE_CXX_LINK_FLAGS)

    list(APPEND CMAKE_C_FLAGS ${ARG_C_FLAGS})
    list(APPEND CMAKE_CXX_FLAGS ${ARG_CXX_FLAGS})

    if(${PREFIX} STREQUAL "vmm")
        set(CMAKE_C_LINK_FLAGS ${BFFLAGS_VMM_LINK})
        set(CMAKE_CXX_LINK_FLAGS ${BFFLAGS_VMM_LINK})
        list(APPEND CMAKE_C_FLAGS ${BFFLAGS_VMM_C} ${C_FLAGS_VMM})
        list(APPEND CMAKE_CXX_FLAGS ${BFFLAGS_VMM_CXX} ${CXX_FLAGS_VMM})
    elseif(${PREFIX} STREQUAL "userspace")
        list(APPEND CMAKE_C_FLAGS ${BFFLAGS_USERSPACE_C} ${C_FLAGS_USERSPACE})
        list(APPEND CMAKE_CXX_FLAGS ${BFFLAGS_USERSPACE_CXX} ${CXX_FLAGS_USERSPACE})
    elseif(${PREFIX} STREQUAL "test")
        list(APPEND CMAKE_C_FLAGS ${BFFLAGS_TEST_C} ${C_FLAGS_TEST})
        list(APPEND CMAKE_CXX_FLAGS ${BFFLAGS_TEST_CXX} ${CXX_FLAGS_TEST})
    elseif(${PREFIX} STREQUAL "efi")
        list(APPEND CMAKE_C_FLAGS ${BFFLAGS_EFI_C} ${C_FLAGS_EFI})
        list(APPEND CMAKE_CXX_FLAGS ${BFFLAGS_EFI_CXX} ${CXX_FLAGS_EFI})
    else()
        message(FATAL_ERROR "Invalid prefix: ${PREFIX}")
    endif()

    if(ENABLE_COMPILER_WARNINGS AND NOT ARG_NOWARNINGS)
        list(APPEND CMAKE_C_FLAGS ${BFFLAGS_WARNING_C})
        list(APPEND CMAKE_CXX_FLAGS ${BFFLAGS_WARNING_CXX})
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            if(UNIX)
                list(APPEND CMAKE_C_FLAGS -Werror)
                list(APPEND CMAKE_CXX_FLAGS -Werror)
            else()
                list(APPEND CMAKE_C_FLAGS /WX)
                list(APPEND CMAKE_CXX_FLAGS /WX)
            endif()
        endif()
    else()
        if(UNIX)
            list(APPEND CMAKE_C_FLAGS -w)
            list(APPEND CMAKE_CXX_FLAGS -w)
        else()
            list(APPEND CMAKE_C_FLAGS /w)
            list(APPEND CMAKE_CXX_FLAGS /w)
        endif()
    endif()

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        if(UNIX)
            list(APPEND CMAKE_C_FLAGS -O3 -DNDEBUG)
            list(APPEND CMAKE_CXX_FLAGS -O3 -DNDEBUG)
        else()
            list(APPEND CMAKE_C_FLAGS /O2 -DNDEBUG)
            list(APPEND CMAKE_CXX_FLAGS /O2 -DNDEBUG)
        endif()
    else()
        if(UNIX)
            list(APPEND CMAKE_C_FLAGS -g)
            list(APPEND CMAKE_CXX_FLAGS -g)
        else()
            list(APPEND CMAKE_C_FLAGS /Od)
            list(APPEND CMAKE_CXX_FLAGS /Od)
        endif()
    endif()

    string(REPLACE ";" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endmacro(setup_flags)

# ------------------------------------------------------------------------------
# setup_generator_expression_shorthands
# ------------------------------------------------------------------------------

# Sets up some generator expression shorthands which can be used by a
# subproject to keep their CMakeLists.txt files simpilar.
#
macro(setup_generator_expression_shorthands)
    set(INTEL_X64 $<STREQUAL:${CMAKE_HOST_SYSTEM_PROCESSOR},x86_64>)

    set(C $<COMPILE_LANGUAGE:C>)
    set(CXX $<COMPILE_LANGUAGE:CXX>)

    set(LINUX $<STREQUAL:${HOST_SYSTEM_NAME},Linux>)
    set(WINDOWS $<STREQUAL:${HOST_SYSTEM_NAME},Windows>)
endmacro(setup_generator_expression_shorthands)

# ------------------------------------------------------------------------------
# include_dependency
# ------------------------------------------------------------------------------

macro(include_dependency DIR NAME)
    include(${${DIR}}/${NAME}.cmake)
endmacro(include_dependency)

# ------------------------------------------------------------------------------
# download_dependency
# ------------------------------------------------------------------------------

# Downloads a dependency from a URL. Dependencies can either be
# a tarball or a zip file. These downloaded files are placeed in the CACHE_DIR.
# If the provided MD5 hash does not match, the cached download is redownloaded.
#
# @param NAME the name of the dependency
# @param URL The URL for the dependency
# @param URL_MD5 The MD5 of the file being downloaded
# @param PREFIX An optional prefix. This is only needed if downloading the
#     dependency is the only required step, in which case this function will
#     create the custom target for dependency tracking.
#
function(download_dependency NAME)
    set(oneVal URL URL_MD5 GIT_REPOSITORY GIT_TAG PREFIX)
    cmake_parse_arguments(ARG "" "${oneVal}" "" ${ARGN})

    set(SRC ${CACHE_DIR}/${NAME})

    if(ARG_URL)
        if(NOT ARG_URL_MD5)
            message(FATAL_ERROR "Invalid URL MD5: ${ARG_URL_MD5}")
        endif()

        string(REGEX REPLACE "\\.[^.]*$" "" FILENAME ${ARG_URL})
        string(REPLACE "${FILENAME}" "" EXT ${ARG_URL})
        get_filename_component(LONG_EXT ${ARG_URL} EXT)
        if(NOT LONG_EXT MATCHES "(\\.|=)(7z|tar\\.bz2|tar\\.gz|tar\\.xz|tbz2|tgz|txz|zip)$")
            message(FATAL_ERROR "Unsupported file format: ${ARG_URL}")
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

        set(TMP ${CACHE_DIR}/${NAME}_tmp)
        set(TAR ${CACHE_DIR}/${NAME}${EXT})

        # TODO
        #
        # If a dependency needs to be downloaded, currently, we remove the
        # source directory which forces a recompile. We need to verify that
        # when this happens, all of the targets that rely on this dependency
        # are also recompiled / relinked.
        #

        foreach(ATTEMPT RANGE 1 5 1)
            if(EXISTS "${TAR}")
                message(STATUS "    checking hash: ${ARG_URL_MD5}")
                file(MD5 ${TAR} MD5)
                if(NOT "${MD5}" STREQUAL "${ARG_URL_MD5}")
                    message(STATUS "    ${Red}md5 mismatch: expecting ${ARG_URL_MD5}, got ${MD5}${ColorReset}")
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

            message(STATUS "    download file: ${ARG_URL} -> ${TAR}")
            file(DOWNLOAD ${ARG_URL} ${TAR} STATUS DOWNLOAD_STATUS)
            if(NOT DOWNLOAD_STATUS MATCHES "0;")
                message(STATUS "    ${Red}failed to download ${ARG_URL}${ColorReset}")
                file(REMOVE_RECURSE ${TAR})
                continue()
            endif()
            message(STATUS "    download file: ${Green}complete${ColorReset}")
        endforeach()

        if(EXISTS ${TAR})
            file(MD5 ${TAR} MD5)
            if(NOT "${MD5}" STREQUAL "${ARG_URL_MD5}")
                message(FATAL_ERROR "Failed to download ${ARG_URL} with md5 hash of ${ARG_URL_MD5}")
            endif()
        else()
            message(FATAL_ERROR "Failed to download ${ARG_URL} with md5 hash of ${ARG_URL_MD5}")
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
                message(FATAL_ERROR "Invalid tarball: ${ARG_URL}")
            endif()

            get_filename_component(CONTENTS ${CONTENTS} ABSOLUTE)
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E rename ${CONTENTS} ${SRC}
            )

            file(REMOVE_RECURSE ${TMP})
        endif()
    endif()

    if(ARG_GIT_REPOSITORY)
        if(ARG_GIT_TAG)
            set(ARG_GIT_TAG -b ${ARG_GIT_TAG})
        endif()
        if(NOT EXISTS "${SRC}")
            execute_process(COMMAND git clone ${ARG_GIT_REPOSITORY} ${ARG_GIT_TAG} ${SRC})
        endif()
    endif()

    if(ARG_PREFIX)
        if(ARG_PREFIX STREQUAL "vmm")
            add_custom_target(${NAME}_${VMM_PREFIX})
        elseif(ARG_PREFIX STREQUAL "userspace")
            add_custom_target(${NAME}_${USERSPACE_PREFIX})
        elseif(ARG_PREFIX STREQUAL "test")
            add_custom_target(${NAME}_${TEST_PREFIX})
        else()
            message(FATAL_ERROR "Invalid prefix: ${PREFIX}")
        endif()
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
# @param PREFIX the prefix this dependency belongs too. Valid values are:
#     vmm, userspace and test.
#
function(add_dependency NAME PREFIX)
    if(PREFIX STREQUAL "vmm")
        set(PREFIX ${VMM_PREFIX})
    elseif(PREFIX STREQUAL "userspace")
        set(PREFIX ${USERSPACE_PREFIX})
    elseif(PREFIX STREQUAL "test")
        set(PREFIX ${TEST_PREFIX})
    elseif(PREFIX STREQUAL "efi")
        set(PREFIX ${EFI_PREFIX})
    else()
        message(FATAL_ERROR "Invalid prefix: ${PREFIX}")
    endif()

    if(EXISTS "${CACHE_DIR}/${NAME}/CMakeLists.txt")
        list(APPEND ARGN
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${PREFIXES_DIR}/${PREFIX}
            CMAKE_ARGS -DCMAKE_INSTALL_MESSAGE=${CMAKE_INSTALL_MESSAGE}
            CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}
        )
        if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
            list(APPEND ARGN
                CMAKE_ARGS -DCMAKE_TARGET_MESSAGES=${CMAKE_TARGET_MESSAGES}
            )
        endif()
    elseif(NOT CMAKE_VERBOSE_MAKEFILE)
        list(APPEND ARGN
            LOG_CONFIGURE 1
            LOG_BUILD 1
            LOG_INSTALL 1
        )
    endif()

    add_custom_command(
        TARGET clean-all
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${DEPENDS_DIR}/${NAME}
    )

    add_custom_command(
        TARGET clean-depends
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${DEPENDS_DIR}/${NAME}
    )

    ExternalProject_Add(
        ${NAME}_${PREFIX}
        ${ARGN}
        PREFIX              ${DEPENDS_DIR}/${NAME}/${PREFIX}
        STAMP_DIR           ${DEPENDS_DIR}/${NAME}/${PREFIX}/stamp
        TMP_DIR             ${DEPENDS_DIR}/${NAME}/${PREFIX}/tmp
        BINARY_DIR          ${DEPENDS_DIR}/${NAME}/${PREFIX}/build
        LOG_DIR             ${DEPENDS_DIR}/${NAME}/${PREFIX}/logs
        SOURCE_DIR          ${CACHE_DIR}/${NAME}
    )

    ExternalProject_Add_Step(
        ${NAME}_${PREFIX}
        ${NAME}_${PREFIX}_cleanup
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${DEPENDS_DIR}/${NAME}/${PREFIX}/src
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
# @param PREFIX the prefix this dependency belongs too. Valid values are:
#     vmm, userspace and test.
#
function(add_dependency_step NAME PREFIX)
    if(PREFIX STREQUAL "vmm")
        set(PREFIX ${VMM_PREFIX})
    elseif(PREFIX STREQUAL "userspace")
        set(PREFIX ${USERSPACE_PREFIX})
    elseif(PREFIX STREQUAL "test")
        set(PREFIX ${TEST_PREFIX})
    elseif(PREFIX STREQUAL "efi")
        set(PREFIX ${EFI_PREFIX})
    else()
        message(FATAL_ERROR "Invalid prefix: ${PREFIX}")
    endif()

    ExternalProject_Add_Step(
        ${NAME}_${PREFIX}
        step_${NAME}_${PREFIX}
        ${ARGN}
        DEPENDEES install
    )
endfunction(add_dependency_step)

# ------------------------------------------------------------------------------
# add_targets
# ------------------------------------------------------------------------------

function(add_tidy_targets PREFIX NAME SOURCE_DIR)
    if(PREFIX STREQUAL "vmm")
        set(PREFIX ${VMM_PREFIX})
    elseif(PREFIX STREQUAL "userspace")
        set(PREFIX ${USERSPACE_PREFIX})
    elseif(PREFIX STREQUAL "test")
        set(PREFIX ${TEST_PREFIX})
    endif()

    if(NOT EXISTS "${SOURCE_DIR}")
        return()
    endif()

    add_custom_command(
        TARGET tidy
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/build
            ${TIDY_SCRIPT} diff ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET tidy-all
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/build
            ${TIDY_SCRIPT} all ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET tidy-upstream
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/build
            ${TIDY_SCRIPT} upstream ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET tidy-${NAME}_${PREFIX}
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/build
            ${TIDY_SCRIPT} diff ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET tidy-${NAME}_${PREFIX}-all
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/build
            ${TIDY_SCRIPT} all ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET tidy-${NAME}_${PREFIX}-upstream
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/build
            ${TIDY_SCRIPT} upstream ${SOURCE_DIR}
    )
endfunction(add_tidy_targets)

function(add_format_targets PREFIX NAME SOURCE_DIR)
    if(PREFIX STREQUAL "vmm")
        set(PREFIX ${VMM_PREFIX})
    elseif(PREFIX STREQUAL "userspace")
        set(PREFIX ${USERSPACE_PREFIX})
    elseif(PREFIX STREQUAL "test")
        set(PREFIX ${TEST_PREFIX})
    endif()

    if(NOT EXISTS "${SOURCE_DIR}")
        return()
    endif()

    add_custom_command(
        TARGET format
        COMMAND ${ASTYLE_SCRIPT} ${USERSPACE_PREFIX_PATH}/bin/astyle diff ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET format-all
        COMMAND ${ASTYLE_SCRIPT} ${USERSPACE_PREFIX_PATH}/bin/astyle all ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET format-upstream
        COMMAND ${ASTYLE_SCRIPT} ${USERSPACE_PREFIX_PATH}/bin/astyle upstream ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET format-${NAME}_${PREFIX}
        COMMAND ${ASTYLE_SCRIPT} ${USERSPACE_PREFIX_PATH}/bin/astyle diff ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET format-${NAME}_${PREFIX}-all
        COMMAND ${ASTYLE_SCRIPT} ${USERSPACE_PREFIX_PATH}/bin/astyle all ${SOURCE_DIR}
    )

    add_custom_command(
        TARGET format-${NAME}_${PREFIX}-upstream
        COMMAND ${ASTYLE_SCRIPT} ${USERSPACE_PREFIX_PATH}/bin/astyle upstream ${SOURCE_DIR}
    )
endfunction(add_format_targets)

function(add_targets PREFIX NAME SOURCE_DIR)
    if(PREFIX STREQUAL "vmm")
        set(FULLPREFIX ${VMM_PREFIX})
    elseif(PREFIX STREQUAL "userspace")
        set(FULLPREFIX ${USERSPACE_PREFIX})
    elseif(PREFIX STREQUAL "test")
        set(FULLPREFIX ${TEST_PREFIX})
    elseif(PREFIX STREQUAL "none")
        set(FULLPREFIX ${PREFIX})
    endif()

    if(NOT PREFIX STREQUAL "none")
        add_custom_target(
            clean-${NAME}_${FULLPREFIX}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/${NAME}/${FULLPREFIX}
        )

        add_custom_command(
            TARGET clean-all
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/${NAME}/${FULLPREFIX}
        )

        add_custom_command(
            TARGET clean-subprojects
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/${NAME}/${FULLPREFIX}
        )

        add_custom_target(
            rebuild-${NAME}_${FULLPREFIX}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/${NAME}/${FULLPREFIX}
            COMMAND ${CMAKE_COMMAND} --build . --target ${NAME}_${FULLPREFIX}
        )

        if(ENABLE_TIDY)
            add_custom_target(tidy-${NAME}_${FULLPREFIX})
            add_custom_target(tidy-${NAME}_${FULLPREFIX}-all)
            add_custom_target(tidy-${NAME}_${FULLPREFIX}-upstream)
            add_tidy_targets(${PREFIX} ${NAME} ${SOURCE_DIR})
        endif()

        if(ENABLE_FORMAT)
            add_custom_target(format-${NAME}_${FULLPREFIX})
            add_custom_target(format-${NAME}_${FULLPREFIX}-all)
            add_custom_target(format-${NAME}_${FULLPREFIX}-upstream)
            add_format_targets(${PREFIX} ${NAME} ${SOURCE_DIR})
            add_format_targets(${PREFIX} ${NAME} ${SOURCE_DIR}/../include)
        endif()
    endif()

    if(PREFIX STREQUAL "test")
        add_custom_command(
            TARGET unittest
            COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${NAME}/${FULLPREFIX}/build
            ctest -C Debug --output-on-failure
        )

        add_custom_target(
            unittest-${NAME}_${FULLPREFIX}
            COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${NAME}/${FULLPREFIX}/build
            ctest -C Debug --output-on-failure
        )
    endif()
endfunction(add_targets)

# ------------------------------------------------------------------------------
# add_subproject
# ------------------------------------------------------------------------------

# Adds a Bareflank specific project to the build. Unlike dependencies,
# sub projects are checked for changes. This function is not only used
# internally by the main build system, but can also be used by extensions
# for adding additional logic to the hypervisor.
#
# @param NOINSTALL skip the install step
# @param PRIVATE only for internal uses
# @param SOURCE_DIR the path to the project's CMakeLists.txt.
# @param DEPENDS superbuild-level dependencies of the project.
#
function(add_subproject NAME PREFIX)
    set(options NOINSTALL PRIVATE)
    set(oneVal SOURCE_DIR)
    set(multiVal DEPENDS)
    cmake_parse_arguments(ARG "${options}" "${oneVal}" "${multiVal}" ${ARGN})

    if(PREFIX STREQUAL "vmm" AND NOT ENABLE_BUILD_VMM)
        return()
    elseif(PREFIX STREQUAL "userspace" AND NOT ENABLE_BUILD_USERSPACE)
        return()
    elseif(PREFIX STREQUAL "test" AND NOT ENABLE_BUILD_TEST)
        return()
    elseif(PREFIX STREQUAL "efi"  AND NOT ENABLE_BUILD_EFI)
        return()
    endif()

    if(ARG_SOURCE_DIR)
        set(SOURCE_DIR ${ARG_SOURCE_DIR})
    else()
        set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/${NAME})
    endif()

    if(PREFIX STREQUAL "vmm")
        set(TOOLCHAIN ${VMM_TOOLCHAIN_PATH})
    elseif(PREFIX STREQUAL "userspace")
        set(TOOLCHAIN ${USERSPACE_TOOLCHAIN_PATH})
    elseif(PREFIX STREQUAL "test")
        set(TOOLCHAIN ${TEST_TOOLCHAIN_PATH})
    elseif(PREFIX STREQUAL "efi")
        set(TOOLCHAIN ${EFI_TOOLCHAIN_PATH})
    endif()

    setup_flags(${PREFIX})
    add_targets(${PREFIX} ${NAME} ${SOURCE_DIR})

    if(PREFIX STREQUAL "vmm")
        set(PREFIX ${VMM_PREFIX})
    elseif(PREFIX STREQUAL "userspace")
        set(PREFIX ${USERSPACE_PREFIX})
    elseif(PREFIX STREQUAL "test")
        set(PREFIX ${TEST_PREFIX})
    elseif(PREFIX STREQUAL "efi")
        set(PREFIX ${EFI_PREFIX})
    endif()

    foreach(d ${ARG_DEPENDS})
        if(d MATCHES ${VMM_PREFIX})
            list(APPEND DEPENDS "${d}")
        elseif(d MATCHES ${USERSPACE_PREFIX})
            list(APPEND DEPENDS "${d}")
        elseif(d MATCHES ${TEST_PREFIX})
            list(APPEND DEPENDS "${d}")
        elseif(d MATCHES ${EFI_PREFIX})
            list(APPEND DEPENDS "${d}")
        else()
            list(APPEND DEPENDS "${d}_${PREFIX}")
        endif()
    endforeach(d)

    if(PREFIX MATCHES "vmm" AND NOT ARG_PRIVATE)
        list(APPEND DEPENDS "bfvmm_${PREFIX}")
    endif()

    list(APPEND CMAKE_ARGS
        -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN}
        -DCMAKE_INSTALL_PREFIX=${PREFIXES_DIR}/${PREFIX}
        -DCMAKE_PROJECT_${NAME}_INCLUDE=${SOURCE_CMAKE_DIR}/project.cmake
        -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}
        -DCMAKE_TARGET_MESSAGES=${CMAKE_TARGET_MESSAGES}
        -DCMAKE_INSTALL_MESSAGE=${CMAKE_INSTALL_MESSAGE}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        -DCMAKE_CXX_LINK_FLAGS=${CMAKE_CXX_LINK_FLAGS}
    )

    list(APPEND CMAKE_ARGS
        -DENABLE_BUILD_VMM=${ENABLE_BUILD_VMM}
        -DENABLE_BUILD_USERSPACE=${ENABLE_BUILD_USERSPACE}
        -DENABLE_BUILD_TEST=${ENABLE_BUILD_TEST}
        -DENABLE_BUILD_EFI=${ENABLE_BUILD_EFI}
        -DENABLE_BUILD_EXAMPLES=${ENABLE_BUILD_EXAMPLES}
        -DHOST_SYSTEM_NAME=${HOST_SYSTEM_NAME}
        -DHOST_FORMAT_TYPE=${HOST_FORMAT_TYPE}
        -DHOST_OSTYPE=${HOST_OSTYPE}
        -DHOST_ABITYPE=${HOST_ABITYPE}
        -DSOURCE_ROOT_DIR=${SOURCE_ROOT_DIR}
    )

    if(ARG_NOINSTALL)
        ExternalProject_Add(
            ${NAME}_${PREFIX}
            PREFIX          ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}
            STAMP_DIR       ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/stamp
            TMP_DIR         ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/tmp
            BINARY_DIR      ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/build
            LOG_DIR         ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/logs
            SOURCE_DIR      ${SOURCE_DIR}
            CMAKE_ARGS      ${CMAKE_ARGS}
            DEPENDS         ${DEPENDS}
            UPDATE_COMMAND  ${CMAKE_COMMAND} -E echo "-- checking for updates"
            INSTALL_COMMAND  ${CMAKE_COMMAND} -E echo "-- skipping install"
        )
    else()
        ExternalProject_Add(
            ${NAME}_${PREFIX}
            PREFIX          ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}
            STAMP_DIR       ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/stamp
            TMP_DIR         ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/tmp
            BINARY_DIR      ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/build
            LOG_DIR         ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/logs
            SOURCE_DIR      ${SOURCE_DIR}
            CMAKE_ARGS      ${CMAKE_ARGS}
            DEPENDS         ${DEPENDS}
            UPDATE_COMMAND  ${CMAKE_COMMAND} -E echo "-- checking for updates"
        )
    endif()

    ExternalProject_Add_Step(
        ${NAME}_${PREFIX}
        ${NAME}_${PREFIX}_cleanup
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/${NAME}/${PREFIX}/src
        DEPENDEES configure
    )
endfunction(add_subproject)

# ------------------------------------------------------------------------------
# setup_interfaces
# ------------------------------------------------------------------------------

function(setup_interfaces)
    if(ENABLE_BUILD_VMM)
        add_library(bareflank_internal INTERFACE)
        add_library(bareflank_vmm INTERFACE)

        target_link_libraries(bareflank_internal INTERFACE
            --whole-archive
            ${VMM_PREFIX_PATH}/lib/libbfcrt.a
            ${VMM_PREFIX_PATH}/lib/libbfdso.a
            --no-whole-archive
            ${VMM_PREFIX_PATH}/lib/libbfintrinsics.a
            ${VMM_PREFIX_PATH}/lib/libc++.a
            ${VMM_PREFIX_PATH}/lib/libc++abi.a
            ${VMM_PREFIX_PATH}/lib/libbfpthread.a
            ${VMM_PREFIX_PATH}/lib/libbfunwind.a
            ${VMM_PREFIX_PATH}/lib/libm.a
            ${VMM_PREFIX_PATH}/lib/libc.a
            ${VMM_PREFIX_PATH}/lib/libbfsyscall.a
        )

        target_link_libraries(bareflank_vmm INTERFACE
            --whole-archive
            ${VMM_PREFIX_PATH}/lib/libbfcrt.a
            ${VMM_PREFIX_PATH}/lib/libbfdso.a
            --no-whole-archive
            ${VMM_PREFIX_PATH}/lib/libbfvmm.a
            ${VMM_PREFIX_PATH}/lib/libbfintrinsics.a
            ${VMM_PREFIX_PATH}/lib/libc++.a
            ${VMM_PREFIX_PATH}/lib/libc++abi.a
            ${VMM_PREFIX_PATH}/lib/libbfpthread.a
            ${VMM_PREFIX_PATH}/lib/libbfunwind.a
            ${VMM_PREFIX_PATH}/lib/libm.a
            ${VMM_PREFIX_PATH}/lib/libc.a
            ${VMM_PREFIX_PATH}/lib/libbfsyscall.a
            ${VMM_PREFIX_PATH}/lib/libbfvmm.a
        )

        export(TARGETS bareflank_internal FILE bareflank_vmmConfig.cmake APPEND)
        export(TARGETS bareflank_vmm FILE bareflank_vmmConfig.cmake APPEND)
        export(PACKAGE bareflank_vmm)
    endif()

    if(ENABLE_BUILD_USERSPACE)
        add_library(bareflank_userspace INTERFACE)

        target_link_libraries(bareflank_userspace INTERFACE
            ${USERSPACE_PREFIX_PATH}/lib/libbfintrinsics.a
            $<$<OR:$<BOOL:${CYGWIN}>,$<BOOL:${WIN32}>>:setupapi>
        )

        export(TARGETS bareflank_userspace FILE bareflank_userspaceConfig.cmake APPEND)
        export(PACKAGE bareflank_userspace)
    endif()

    if(ENABLE_BUILD_TEST)
        add_library(bareflank_test INTERFACE)

        target_link_libraries(bareflank_test INTERFACE
            ${TEST_PREFIX_PATH}/lib/libCatchMain.a
            $<$<OR:$<BOOL:${CYGWIN}>,$<BOOL:${WIN32}>>:setupapi>
        )

        export(TARGETS bareflank_test FILE bareflank_testConfig.cmake APPEND)
        export(PACKAGE bareflank_test)
    endif()
endfunction(setup_interfaces)

# ------------------------------------------------------------------------------
# set_vmm
# ------------------------------------------------------------------------------

# Sets the VMM that will be used when running "make load" or "make quick".
# Note that this is only used by the make targets and does not extend to BFM
# itself which must be used manually.
#
# @param NAME The name of the VMM to load
# @param DEFAULT If the VMM has not yet been set, this default value will be
#     used instead. This should not be used by extensions
#
macro(set_vmm NAME)
    set(options DEFAULT)
    cmake_parse_arguments(ARG "${options}" "" "" ${ARGN})

    if(NOT ARG_DEFAULT OR (ARG_DEFAULT AND NOT VMM))
        set(VMM "${NAME}")
        message(STATUS "VMM: ${VMM}")
    endif()
endmacro(set_vmm)

# ------------------------------------------------------------------------------
# validate_build / invalid_config
# ------------------------------------------------------------------------------

function(validate_build)
    if(BUILD_VALIDATOR_ERROR)
        message(FATAL_ERROR "Build validation failed")
    endif()
endfunction(validate_build)

# Use this function to invalidate the configuration of the build. Unlike
# message(FATAL_ERROR), this function will queue up errors, and exit when
# the build is validated ensuring all errors are reported at once.
#
# @param MSG the message to report on error
#
macro(invalid_config MSG)
    message(SEND_ERROR "${MSG}")
    set(BUILD_VALIDATOR_ERROR ON)
endmacro(invalid_config)

# ------------------------------------------------------------------------------
# do_test
# ------------------------------------------------------------------------------

# Adds a unit test.
#
# @param FILEPATH the file name of the test.
# @param DEFINES Additional definitions for the test
# @param DEPENDS Additional dependencies for the test.
# @param SOURCES The source files to use for the test. If this is not defined,
#     the file used is ${FILEPATH}.cpp. This is only needed if the test file
#     is not in the same directory, allowing you to pass a source file with
#     a directory. Nomrally FILEPATH should still match the filename being
#     used.
#
function(do_test FILEPATH)
    set(multiVal DEPENDS SOURCES)
    cmake_parse_arguments(ARG "" "" "${multiVal}" ${ARGN})

    if(NOT CMAKE_INSTALL_PREFIX MATCHES "test")
        return()
    endif()

    if(NOT ARG_SOURCES)
        set(ARG_SOURCES "${FILEPATH}")
    endif()

    get_filename_component(TEST_NAME "${FILEPATH}" NAME_WE)
    string(REPLACE "test_" "" NAME "${TEST_NAME}")

    add_executable(test_${NAME})
    target_sources(test_${NAME} PRIVATE ${ARG_SOURCES})
    target_link_libraries(test_${NAME} PRIVATE ${ARG_DEPENDS} bareflank_test)
    add_test(NAME test_${NAME} COMMAND test_${NAME})
endfunction(do_test)

# ------------------------------------------------------------------------------
# add_custom_target_category
# ------------------------------------------------------------------------------

function(add_custom_target_category TEXT)
    add_custom_command(
        TARGET info
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color " "
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "${TEXT}:"
    )
endfunction(add_custom_target_category)

# ------------------------------------------------------------------------------
# add_custom_target_info
# ------------------------------------------------------------------------------

function(right_justify text width output)
    set(str "")
    string(LENGTH "${text}" text_len)
    foreach(i RANGE ${text_len} ${width})
        set(str " ${str}")
    endforeach(i)
    set(${output} ${str} PARENT_SCOPE)
endfunction(right_justify)

function(add_custom_target_info)
    set(oneVal TARGET COMMENT)
    cmake_parse_arguments(ARG "" "${oneVal}" "" ${ARGN})

    if(NOT_ARG_TARGET)
        right_justify("${BUILD_COMMAND}" 20 JUSTIFY_STR)
        add_custom_command(
            TARGET info
            COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --yellow --no-newline "    ${BUILD_COMMAND}"
            COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --no-newline "${JUSTIFY_STR}- "
            COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --white "${ARG_COMMENT}"
        )
    else()
        right_justify("${BUILD_COMMAND} ${ARG_TARGET}" 20 JUSTIFY_STR)
        add_custom_command(
            TARGET info
            COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --yellow --no-newline "    ${BUILD_COMMAND} ${ARG_TARGET}"
            COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --no-newline "${JUSTIFY_STR}- "
            COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --white "${ARG_COMMENT}"
        )
    endif()
endfunction(add_custom_target_info)

# ------------------------------------------------------------------------------
# force_rebuild_if_needed
# ------------------------------------------------------------------------------

function(force_rebuild_if_needed)
    get_property(FORCE_REBUILD GLOBAL PROPERTY "FORCE_REBUILD")

    if(FORCE_REBUILD STREQUAL "ON")
        set_property(GLOBAL PROPERTY "FORCE_REBUILD" "OFF")
        file(REMOVE_RECURSE ${DEPENDS_DIR})
        file(REMOVE_RECURSE ${PREFIXES_DIR})
        message(FATAL_ERROR "${Yellow}dependencies updated, rebuild is required. Rerun cmake${ColorReset}")
    endif()
endfunction()

# ------------------------------------------------------------------------------
# print_xxx
# ------------------------------------------------------------------------------

function(print_banner)
    message(STATUS "${BoldMagenta}  ___                __ _           _   ${ColorReset}")
    message(STATUS "${BoldMagenta} | _ ) __ _ _ _ ___ / _| |__ _ _ _ | |__${ColorReset}")
    message(STATUS "${BoldMagenta} | _ \\/ _` | '_/ -_)  _| / _` | ' \\| / /${ColorReset}")
    message(STATUS "${BoldMagenta} |___/\\__,_|_| \\___|_| |_\\__,_|_||_|_\\_\\${ColorReset}")
    message(STATUS "")
    message(STATUS "${Green} Please give us a star on: ${White}https://github.com/Bareflank/hypervisor${ColorReset}")
    message(STATUS "")
endfunction(print_banner)

function(print_usage)
    message(STATUS "${Green} Bareflank is ready to build, usage:${ColorReset}")
    message(STATUS "${Yellow}    ${BUILD_COMMAND}${ColorReset}")
    message(STATUS "")
    if(UNIX)
        message(STATUS "${Green} For more build options:${ColorReset}")
        message(STATUS "${Yellow}    ${BUILD_COMMAND} info${ColorReset}")
    else()
        message(STATUS "${Green} Additional build options:${ColorReset}")
        message(STATUS "${Yellow}    cmake --build . --target unittest${ColorReset}")
        message(STATUS "${Yellow}    cmake --build . --target clean-all${ColorReset}")
    endif()
    message(STATUS "")
endfunction(print_usage)
