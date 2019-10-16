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

message(STATUS "Including dependency: standalone_cxx")

download_dependency(
    standalone_cxx
    ${BAREFLANK_STANDALONE_URL}
    ${BAREFLANK_STANDALONE_URL_MD5}
)

list(APPEND BAREFLANK_STANDALONE_CXX_CONFIGURE_FLAGS
    -DBAREFLANK_NOBFCOMPILE=ON
    -DBAREFLANK_NOEXAMPLES=ON
    -DBAREFLANK_CACHE_DIR=${BAREFLANK_CACHE_DIR}
    -DBAREFLANK_PREFIX_DIR=${BAREFLANK_PREFIX_DIR}
    -DBAREFLANK_HOST_BUILD_TYPE=${BAREFLANK_HOST_BUILD_TYPE}
    -DBAREFLANK_TARGET_BUILD_TYPE=${BAREFLANK_TARGET_BUILD_TYPE}
    -DBAREFLANK_CLANG_BIN=${BAREFLANK_CLANG_BIN}
    -DBAREFLANK_LD_BIN=${BAREFLANK_LD_BIN}
    -DBAREFLANK_TARGET=${BAREFLANK_TARGET}
    -DBAREFLANK_HOST_CXX_FLAGS=${BAREFLANK_HOST_CXX_FLAGS}
    -DBAREFLANK_TARGET_CXX_FLAGS=${BAREFLANK_TARGET_CXX_FLAGS}
)

add_dependency(
    standalone_cxx  ""
    CMAKE_ARGS      ${BAREFLANK_STANDALONE_CXX_CONFIGURE_FLAGS}
)
