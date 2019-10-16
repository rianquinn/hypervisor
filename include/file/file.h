//
// Copyright (C) 2019 Assured Information Security, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef FILE_FILE_H
#define FILE_FILE_H

#include "../bfpair.h"

#include <vector>
#include <string>

namespace host::interface
{
    /// File
    ///
    /// This class provides APIs for common file operations including:
    /// - reading a file into a std::vector<char>
    ///
    template<typename T>
    struct file
    {
        /// Read
        ///
        /// Reads the contents of a file given a "filename" and outputs the
        /// contents to a std::vector<char>.
        ///
        /// @param filename the name of the file to read
        /// @return a std::vector<char> containing the contents of the file read
        ///
        static auto
        read(const std::string &filename) -> std::vector<char>
        {
            expects(!filename.empty());
            return T::details_type::read(filename);
        }
    };

}    // namespace host::interface

namespace host
{
    template<typename D>
    using file = bfpair<interface::file, D>;
}

#endif
