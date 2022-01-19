#ifndef PHANSAR_COMMON_META_IS_CONST_METHOD_HPP
#define PHANSAR_COMMON_META_IS_CONST_METHOD_HPP

#include <type_traits>

namespace phansar::common::meta {
template <class T>
struct is_const_method : std::false_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args...) const> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args...) const &> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args...) const &&> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args..., ...) const> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args..., ...) const &> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args..., ...) const &&> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args...) const volatile> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args...) const volatile &> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args...) const volatile &&> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args..., ...) const volatile> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args..., ...) const volatile &> : std::true_type {};

template <class ReturnType, class Class, class... Args>
struct is_const_method<ReturnType (Class::*)(Args..., ...) const volatile &&> : std::true_type {};

template <class T>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr bool is_const_method_v = is_const_method<T>::value;
} // namespace phansar::common::meta

#endif
