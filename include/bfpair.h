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

#ifndef BFPAIR_H
#define BFPAIR_H

#include <bfgsl.h>
#include <bftypes.h>

/// Pair
///
/// Creates a concrete type by pairing an interface with the details that
/// implements the interface. This is used to implement the static interface
/// pattern which is used heavily in this project to ensure the code adheres
/// to the S.O.L.I.D principles.
///
/// For more information, please see:
/// https://github.com/Bareflank/static_interface_pattern
///
template<
    template<typename> typename INTERFACE,
    typename DETAILS
    >
class bfpair :
    public INTERFACE<bfpair<INTERFACE, DETAILS>>
{
    using details_type = DETAILS;
    using interface_type = INTERFACE<bfpair<INTERFACE, DETAILS>>;

private:
    constexpr static auto details(interface_type *i)
    -> DETAILS &
    { return static_cast<bfpair<INTERFACE, DETAILS> *>(i)->d; }

    constexpr static auto details(const interface_type *i)
    -> const DETAILS &
    { return static_cast<const bfpair<INTERFACE, DETAILS> *>(i)->d; }

private:
    DETAILS d;
    friend class INTERFACE<bfpair<INTERFACE, DETAILS>>;
};

#endif
