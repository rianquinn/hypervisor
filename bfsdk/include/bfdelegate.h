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
/// @file bfdelegate.h
///

#ifndef BFDELEGATE_H
#define BFDELEGATE_H

#include <bftypes.h>
#include <array>
#include <functional>

// Note:
//
// These functions are lifted from Ben Diamand's implementation at
// https://github.com/bdiamand/Delegate/blob/master/delegate.h
//

/// @cond

template<size_t size = 24, size_t align = 32>
struct state
{
    alignas(align) std::array<uint8_t, size> m_buf{};
};

using state_t = state<>;

template<typename Ret, typename... Args>
using call_t = Ret(*)(const state_t &, Args && ...);

template<typename F>
constexpr bool can_emplace()
{
    return (sizeof(F) <= sizeof(state_t)) &&
           (alignof(state_t) % alignof(F) == 0);
}

template<typename F>
constexpr F &get_state(const state_t &state)
{ return reinterpret_cast<F &>(const_cast<state_t &>(state)); }

template<typename F>
constexpr void copy_state(state_t &state, const F &fn)
{
    static_assert(can_emplace<F>());
    new (&get_state<F>(state)) F(fn);
}

template<typename F>
constexpr void move_state(state_t &state, F &&fn)
{
    static_assert(can_emplace<F>());
    new (&get_state<F>(state)) F(fn);
}

template<typename F, typename Ret, typename... Args>
constexpr Ret call(const state_t &state, Args &&... args)
{
    static_assert(std::is_invocable_r_v<Ret, F, Args...>);
    return get_state<F>(state)(std::forward<Args>(args)...);
}

class vtable
{
public:
    void (&copy)(state_t &lhs, const state_t &rhs);
    void (&move)(state_t &lhs, state_t &&rhs);
    void (&destroy)(state_t &state);

    template<typename F>
    static const vtable &init() noexcept
    {
        static const vtable self = {
            s_copy<F>, s_move<F>, s_destroy<F>
        };

        return self;
    }

private:

    template <
        typename F,
        std::enable_if_t<std::is_copy_constructible_v<F>, int> = 0
        >
    static constexpr void s_copy(state_t &lhs, const state_t &rhs) noexcept
    { copy_state<F>(lhs, get_state<F>(rhs)); }

    template <
        typename F,
        std::enable_if_t<std::is_move_constructible_v<F>, int> = 0
        >
    static constexpr void s_move(state_t &lhs, state_t &&rhs) noexcept
    { move_state<F>(lhs, std::move(get_state<F>(rhs))); }

    template <
        typename F,
        std::enable_if_t<std::is_destructible_v<F>, int> = 0
        >
    static constexpr void s_destroy(state_t &state) noexcept
    { get_state<F>(state).~F(); }
};

template< typename> class delegate;

/// @endcond

/// Delegate
///
/// Wraps either a raw function pointer or a pointer-to-member-function
/// and pointer-to-object into an invocable type with a common signature.
///
/// The constructor arguments provide the internal state needed to later
/// invoke the function with the Args... arguments. Only normal function
/// pointers and member function pointers are supported, but lambdas could
/// also be used provided their capture list is at most 16 bytes.
///
template<typename Ret, typename... Args>
class delegate<Ret(Args...)>
{
    call_t<Ret, Args...> m_call{nullptr};
    const vtable *m_vtbl{nullptr};
    state_t m_state;

public:

    /// Return type
    using result_type = Ret;

    /// Null delegate
    ///
    delegate() = default;

    /// Delegate from function pointer
    ///
    /// Create a delegate from the provided function pointer.
    /// Passing a lambda with an empty capture list prefixed with '+'
    /// will match this overload as well.
    ///
    /// Example:
    /// @code
    /// int foo() { return 42; }
    //
    /// int main()
    /// {
    ///     delegate x(+[](const char *s){ printf("%s\n", s); });
    ///     delegate y(foo);
    ///
    ///     x("42");
    ///     return y();
    /// }
    /// @endcode
    ///
    /// @param fn the function to create the delegate for
    ///
    delegate(Ret(*fn)(Args...))
    {
        expects(fn);

        m_call = &call<decltype(fn), Ret, Args...>;
        m_vtbl = &vtable::init<decltype(fn)>();
        copy_state(m_state, fn);
    }

    /// Delegate from functor
    ///
    /// Create a delegate from the provided functor. Note
    /// that there isn't a deduction guide for this overload,
    /// so the Ret, Args... types must be given in the call
    ///
    /// Example:
    /// @code
    /// int main()
    /// {
    ///     auto foo = [](){ return 42; };
    ///     auto d = delegate<int>(foo);
    ///
    ///     return d();
    /// }
    /// @endcode
    ///
    /// @param fn the function to create the delegate for
    ///
    template <
        typename F,
        typename = std::enable_if <
            std::is_invocable_r_v<Ret, F, Args...> &&
            std::is_object_v<F >>
        >
    delegate(F fn)
    {
        expects(fn);

        m_call = &call<decltype(fn), Ret, Args...>;
        m_vtbl = &vtable::init<decltype(fn)>();
        copy_state(m_state, fn);
    }

    /// Delegate from non-const memfn, non-const object
    ///
    /// Create a delegate from the provided member function pointer
    /// and object address.
    ///
    /// Example:
    /// @code
    /// struct S {
    ///     bool even() { return (m_val & 1) == 0; }
    ///     int m_val;
    /// }
    ///
    /// int main()
    /// {
    ///     struct S s;
    ///     delegate d(&S::even, &s);
    ///
    ///     d();
    /// }
    /// @endcode
    ///
    /// @param memfn the member function to create the delegate for
    /// @param obj the object to create the delegate for
    ///
    template <
        typename C,
        typename = std::enable_if<std::is_class_v<C>>
        >
    delegate(Ret(C::*memfn)(Args...), C *obj)
    {
        expects(obj);

        auto fn = [memfn, obj](Args && ... args) -> decltype(auto)
        { return std::invoke(memfn, obj, args...); };

        m_call = &call<decltype(fn), Ret, Args...>;
        m_vtbl = &vtable::init<decltype(fn)>();
        copy_state(m_state, fn);
    }

    /// Delegate from const memfn, non-const object
    ///
    /// Create a delegate from the provided member function pointer
    /// and object address.
    ///
    /// Example:
    /// @code
    /// struct S {
    ///     bool even() const { return (m_val & 1) == 0; }
    ///     int m_val;
    /// }
    ///
    /// int main()
    /// {
    ///     struct S s;
    ///     delegate d(&S::even, &s);
    ///
    ///     d();
    /// }
    /// @endcode
    ///
    /// @param memfn the member function to create the delegate for
    /// @param obj the object to create the delegate for
    ///
    template <
        typename C,
        typename = std::enable_if<std::is_class_v<C>>
        >
    delegate(Ret(C::*memfn)(Args...) const, C *obj)
    {
        expects(obj);

        auto fn = [memfn, obj](Args && ... args) -> decltype(auto)
        { return std::invoke(memfn, obj, args...); };

        m_call = &call<decltype(fn), Ret, Args...>;
        m_vtbl = &vtable::init<decltype(fn)>();
        copy_state(m_state, fn);
    }

    /// Delegate from const memfn, const object
    ///
    /// Create a delegate from the provided member function pointer
    /// and object address.
    ///
    /// Example:
    /// @code
    /// struct S {
    ///     bool even() const { return (m_val & 1) == 0; }
    ///     int m_val;
    /// }
    ///
    /// int main()
    /// {
    ///     const struct S s;
    ///     delegate d(&S::even, &s);
    ///
    ///     d();
    /// }
    /// @endcode
    ///
    /// @param memfn the member function to create the delegate for
    /// @param obj the object to create the delegate for
    ///
    template<
        typename C,
        typename = std::enable_if<std::is_class_v<C>>
        >
    delegate(Ret(C::*memfn)(Args...) const, const C *obj)
    {
        expects(obj);

        auto fn = [memfn, obj](Args && ... args) -> decltype(auto)
        { return std::invoke(memfn, obj, args...); };

        m_call = &call<decltype(fn), Ret, Args...>;
        m_vtbl = &vtable::init<decltype(fn)>();
        copy_state(m_state, fn);
    }

    /// Copy constructor
    ///
    /// @param other the delegate to copy
    ///
    delegate(const delegate &other) :
        m_call{other.m_call},
        m_vtbl{other.m_vtbl}
    { m_vtbl->copy(m_state, other.m_state); }

    /// Move constructor
    ///
    /// @param other the delegate to move
    ///
    delegate(delegate &&other) :
        m_call{other.m_call},
        m_vtbl{other.m_vtbl}
    {
        m_vtbl->move(m_state, std::move(other.m_state));
        other.m_call = nullptr;
    }

    /// Copy assignment
    ///
    /// @param other the delegate to copy
    /// @return the resulting copy
    ///
    delegate &operator=(const delegate &other)
    {
        m_call = other.m_call;
        m_vtbl = other.m_vtbl;

        m_vtbl->copy(m_state, other.m_state);
        return *this;
    }

    /// Move assignment
    ///
    /// @param other the delegate to move
    /// @return the resulting move
    ///
    delegate &operator=(delegate &&other)
    {
        m_call = other.m_call;
        m_vtbl = other.m_vtbl;

        m_vtbl->move(m_state, std::move(other.m_state));
        other.m_call = nullptr;
        return *this;
    }

    /// Destructor
    ///
    ~delegate()
    {
        if (m_vtbl) {
            m_vtbl->destroy(m_state);
        }
    }

    /// operator()
    ///
    /// @param args the arguments to pass to the delegate
    /// @return the result of calling the delegate
    ///
    Ret operator()(Args... args) const
    { return m_call(m_state, std::forward<Args>(args)...); }

    /// operator bool
    ///
    /// @return true iff the delegate is callable
    ///
    operator bool() const
    { return m_call != nullptr; }
};

/// @cond

template<typename Ret, typename... Args>
constexpr std::ostream &operator<<(std::ostream &os, const delegate<Ret(Args...)> &)
{ return os; }

template<typename R, typename... A>
delegate(R(A...)) -> delegate<R(A...)>;

template<typename C, typename R, typename... A>
delegate(R(C::*)(A...), C *) -> delegate<R(A...)>;

template<typename C, typename R, typename... A>
delegate(R(C::*)(A...) const, C *) -> delegate<R(A...)>;

template<typename C, typename R, typename... A>
delegate(R(C::*)(A...) const, const C *) -> delegate<R(A...)>;

/// @endcond

#endif
