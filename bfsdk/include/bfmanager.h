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

#ifndef BFMANAGER_H
#define BFMANAGER_H

#include <mutex>
#include <memory>
#include <unordered_map>

#include <bfgsl.h>

/// Manager
///
/// A generic class for creating and  destroying a type T. Note that this
/// is only meant for singleton style managers, so in general this class is
/// not needed for more users of Bareflank.
///
template<typename T>
class bfmanager
{
public:

    /// Destructor
    ///
    /// @expects none
    /// @ensures none
    ///
    ~bfmanager() = default;

    /// Get Singleton Instance
    ///
    /// @expects none
    /// @ensures ret != nullptr
    ///
    /// @return a singleton instance of bfmanager
    ///
    static bfmanager *instance() noexcept
    {
        static bfmanager self;
        return &self;
    }

    /// Create T
    ///
    /// Creates T. Note that the T is actually created by the
    /// T factory's make_t function.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param id the T to initialize
    ///
    gsl::not_null<T *>
    create(typename T::id_t id)
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        if (auto iter = m_store.find(id); iter != m_store.end()) {
            throw std::runtime_error("bfmanager: id already exists");
        }

        if (auto t = T::make(id)) {
            auto ptr = t.get();
            m_store[id] = std::move(t);
            return ptr;
        }

        throw std::runtime_error("bfmanager: factory returned a nullptr");
    }

    /// Destroy T
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param id the T to destroy
    ///
    std::unique_ptr<T>
    destroy(typename T::id_t id)
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        if (auto t = std::move(m_store[id])) {
            m_store.erase(id);
            return t;
        }

        throw std::runtime_error("bfmanager: invalid id");
    }

    /// For Each
    ///
    /// Loops through all of the Ts that are being managed and calls a
    /// provided callback for each T.
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param func the callback to call for each T
    ///
    constexpr void
    foreach(void(*func)(T *))
    {
        for (auto &t : m_store) {
            func(&t);
        }
    }

    /// Get
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param id the T to get
    /// @param err the error to display
    /// @return returns a pointer to the T associated with T::id_t
    ///
    gsl::not_null<T *>
    get(typename T::id_t id, const char *err = nullptr)
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        if (auto iter = m_store.find(id); iter != m_store.end()) {
            return iter->second.get();
        }

        if (err != nullptr) {
            throw std::runtime_error(err);
        }
        else {
            throw std::runtime_error("bfmanager: failed to get T");
        }
    }

    /// Get (Dynamic Cast)
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param id the T to get
    /// @param err the error to display
    /// @return returns a pointer to the T associated with T::id_t
    ///
    template<typename U> constexpr gsl::not_null<U>
    get(typename T::id_t id, const char *err = nullptr)
    { return dynamic_cast<U>(get(id, err).get()); }

private:

    bfmanager() noexcept = default;

private:

    mutable std::mutex m_mutex;
    std::unordered_map<typename T::id_t, std::unique_ptr<T>> m_store;

public:

    /// @cond

    bfmanager(bfmanager &&) noexcept = delete;
    bfmanager &operator=(bfmanager &&) noexcept = delete;

    bfmanager(const bfmanager &) = delete;
    bfmanager &operator=(const bfmanager &) = delete;

    /// @endcond
};

#endif
