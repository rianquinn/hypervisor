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
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

///
/// @file bfstring.h
///

#ifndef BFSTRING_H
#define BFSTRING_H

#include <bftypes.h>

#include <array>
#include <string>

namespace bfn
{

/// Digits
///
/// Returns the number of digits in a number given the number and its
/// base. This can be used to figure out the size of the character
/// arracy that is needed to store a given number.
///
/// @expects none
/// @ensures none
///
/// @param val the value to convert to digits
/// @param base the base for conversion
/// @return the total number of digits in val given base
///
inline std::size_t
digits(std::size_t val, const int base = 10) noexcept
{
    std::array<char, 32> buf;

    switch (base) {
        case 16: {
            return static_cast<std::size_t>(
                snprintf(buf.data(), buf.size(), "%" PRIx64, val));
        }

        default: {
            return static_cast<std::size_t>(
                snprintf(buf.data(), buf.size(), "%" PRIu64, val));
        }
    }
}

/// Convert to String (with base)
///
/// Same thing as std::to_string, but adds the ability to state the base for
/// conversion.
///
/// @expects none
/// @ensures none
///
/// @param str the string to add the converted integer to
/// @param val the value to convert
/// @param base the base for conversion.
/// @param pad if padding should be used
/// @return the total number of digits of val given base
///
inline std::size_t
to_string(
    std::string &str, const std::size_t val, const int base = 10, bool pad = true) noexcept
{
    std::array<char, 32> buf;
    std::size_t len, digits = 0;

    switch (base) {
        case 16: {
            len = static_cast<std::size_t>(
                snprintf(buf.data(), buf.size(), "%" PRIx64, val));
            digits = len + 2;

            str += "0x";
            if (pad) {
                for (std::size_t i = 0; i < 16 - len; i++) {
                    str += '0';
                }
                digits += 16 - len;
            }

            break;
        }

        default: {
            len = static_cast<std::size_t>(
                snprintf(buf.data(), buf.size(), "%" PRIu64, val));
            digits = len;
            break;
        }
    }

    str.append(buf.data(), len);
    return digits;
}

/// Convert to String (with base)
///
/// Same thing as std::to_string, but adds the ability to state the base for
/// conversion.
///
/// @expects none
/// @ensures none
///
/// @param val the value to convert
/// @param base the base for conversion.
/// @param pad if padding should be used
/// @return string version of val converted to the provided base
///
template <
    typename T,
    typename = std::enable_if<std::is_integral<T>::value>
    >
inline std::string
to_string(const T val, const int base = 10, bool pad = false) noexcept
{
    std::string str;
    to_string(str, static_cast<std::size_t>(val), base, pad);

    return str;
}

}

#endif
