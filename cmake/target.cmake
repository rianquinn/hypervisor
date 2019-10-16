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

# ------------------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------------------

add_custom_target(
    clean-all
    COMMAND ${CMAKE_COMMAND} --build . --target clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BAREFLANK_DEPENDS_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BAREFLANK_SUBPROJECT_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory src
    COMMAND ${CMAKE_COMMAND} -E remove_directory tests
    COMMAND ${CMAKE_COMMAND} -E remove bareflank_hostConfig.cmake
    COMMAND ${CMAKE_COMMAND} -E remove bareflank_targetConfig.cmake
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BAREFLANK_PREFIX_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BAREFLANK_PREFIX_DIR}
)

# ------------------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------------------

add_custom_target(
    format
    COMMAND find ${CMAKE_SOURCE_DIR} -iname *.h -o -iname *.cpp | xargs clang-format -i
)

add_custom_target(
    unittest
    COMMAND ${CMAKE_COMMAND} -E chdir ${BAREFLANK_SUBPROJECT_DIR}/unit_host/build ctest --output-on-failure
)
