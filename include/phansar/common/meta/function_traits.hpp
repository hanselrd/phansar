#ifndef PHANSAR_COMMON_META_FUNCTION_TRAITS_HPP
#define PHANSAR_COMMON_META_FUNCTION_TRAITS_HPP

#include <tuple>
#include <type_traits>

namespace phansar::common::meta {
template <class T>
struct function_traits;

template <class R, class... Args>
struct function_traits<R (*)(Args...)> : function_traits<R(Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...)> : function_traits<R(C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const>
    : function_traits<R(const C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) volatile>
    : function_traits<R(volatile C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const volatile>
    : function_traits<R(const volatile C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) noexcept>
    : function_traits<R(C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const noexcept>
    : function_traits<R(const C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) volatile noexcept>
    : function_traits<R(volatile C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const volatile noexcept>
    : function_traits<R(const volatile C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) &>
    : function_traits<R(C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const &>
    : function_traits<R(const C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) volatile &>
    : function_traits<R(volatile C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const volatile &>
    : function_traits<R(const volatile C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) & noexcept>
    : function_traits<R(C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const & noexcept>
    : function_traits<R(const C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) volatile & noexcept>
    : function_traits<R(volatile C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const volatile & noexcept>
    : function_traits<R(const volatile C &, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) &&>
    : function_traits<R(C &&, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const &&>
    : function_traits<R(const C &&, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) volatile &&>
    : function_traits<R(volatile C &&, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const volatile &&>
    : function_traits<R(const volatile C &&, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) && noexcept>
    : function_traits<R(C &&, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const && noexcept>
    : function_traits<R(const C &&, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) volatile && noexcept>
    : function_traits<R(volatile C &&, Args...)> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const volatile && noexcept>
    : function_traits<R(const volatile C &&, Args...)> {};

template <class R, class... Args>
struct function_traits<R(Args...)> {
  // NOLINTNEXTLINE(readability-identifier-naming)
  static constexpr std::size_t arity = sizeof...(Args);

  using result_type                  = R;
  using args                         = std::tuple<Args...>;
  template <std::size_t N>
  using arg_type = std::tuple_element_t<N, args>;
};
} // namespace phansar::common::meta

#endif
