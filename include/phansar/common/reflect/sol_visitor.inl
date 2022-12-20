#include <phansar/common/macro.hpp>
#include <phansar/common/reflect/sol_visitor.hpp>
#include <fmt/format.h>
#include <hedley.h>

namespace phansar::common::reflect {
template <class T, class... BaseClasses>
void sol_visitor::visit_type_begin(rttr::visitor::type_info<T> const & _info) {
  using declaring_type_t =
      typename std::remove_cvref_t<decltype(_info)>::declaring_type;
  _state_internal().new_usertype<declaring_type_t>(
      rttr::type::get<declaring_type_t>().get_name().to_string(),
      sol::no_constructor,
      sol::base_classes,
      sol::bases<BaseClasses...>());

  _constructor_counter_reset_internal();
}

template <class T, class... BaseClasses>
void sol_visitor::visit_type_end(rttr::visitor::type_info<T> const & _info) {
  using declaring_type_t =
      typename std::remove_cvref_t<decltype(_info)>::declaring_type;
  auto usertype =
      _state_internal()
          [rttr::type::get<declaring_type_t>().get_name().to_string()]
              .template get<sol::usertype<declaring_type_t>>();
  HEDLEY_DIAGNOSTIC_PUSH
#ifdef HEDLEY_GCC_VERSION
  HEDLEY_PRAGMA(GCC diagnostic ignored "-Wnonnull")
#endif
  usertype["__tostring"] = [](declaring_type_t const & _obj) {
    return fmt::format(
        "<{} object at {} with {} byte(s)>",
        rttr::type::get<declaring_type_t>().get_name().to_string(),
        static_cast<const void *>(&_obj),
        sizeof(_obj));
  };
  HEDLEY_DIAGNOSTIC_POP
}

template <class T, class... CtorArgs>
void sol_visitor::visit_constructor(
    rttr::visitor::constructor_info<T> const & _info) {
  using declaring_type_t =
      typename std::remove_cvref_t<decltype(_info)>::declaring_type;
  auto usertype =
      _state_internal()
          [rttr::type::get<declaring_type_t>().get_name().to_string()]
              .template get<sol::usertype<declaring_type_t>>();
  HEDLEY_DIAGNOSTIC_PUSH
#ifdef HEDLEY_GCC_VERSION
  HEDLEY_PRAGMA(GCC diagnostic ignored "-Wnonnull")
#endif
  usertype[fmt::format("new{}", _constructor_counter_next_internal())] =
      [](CtorArgs const &... _args) {
        return std::make_unique<declaring_type_t>(_args...);
      };
  HEDLEY_DIAGNOSTIC_POP
}

template <class T>
void sol_visitor::visit_constructor_function(
    rttr::visitor::constructor_function_info<T> const & _info) {
  using declaring_type_t =
      typename std::remove_cvref_t<decltype(_info)>::declaring_type;
  auto usertype =
      _state_internal()
          [rttr::type::get<declaring_type_t>().get_name().to_string()]
              .template get<sol::usertype<declaring_type_t>>();
  usertype[fmt::format("new{}", _constructor_counter_next_internal())] =
      _info.function_ptr;
}

template <class T>
void sol_visitor::visit_method(rttr::visitor::method_info<T> const & _info) {
  using declaring_type_t =
      typename std::remove_cvref_t<decltype(_info)>::declaring_type;
  auto usertype =
      _state_internal()
          [rttr::type::get<declaring_type_t>().get_name().to_string()]
              .template get<sol::usertype<declaring_type_t>>();
  usertype[_info.method_item.get_name().to_string()] = _info.function_ptr;
}

template <class T>
void sol_visitor::visit_global_method(
    rttr::visitor::method_info<T> const & _info) {
  visit_method(_info);
}

template <class T>
void sol_visitor::visit_property(
    rttr::visitor::property_info<T> const & _info) {
  using declaring_type_t =
      typename std::remove_cvref_t<decltype(_info)>::declaring_type;
  auto usertype =
      _state_internal()
          [rttr::type::get<declaring_type_t>().get_name().to_string()]
              .template get<sol::usertype<declaring_type_t>>();
  if constexpr (std::is_member_object_pointer_v<
                    decltype(_info.property_accessor)>) {
    usertype[_info.property_item.get_name().to_string()] =
        _info.property_accessor;
  } else {
    usertype[_info.property_item.get_name().to_string()] =
        sol::var(std::ref(*_info.property_accessor));
  }
}

template <class T>
void sol_visitor::visit_getter_setter_property(
    rttr::visitor::property_getter_setter_info<T> const & _info) {
  using declaring_type_t =
      typename std::remove_cvref_t<decltype(_info)>::declaring_type;
  auto usertype =
      _state_internal()
          [rttr::type::get<declaring_type_t>().get_name().to_string()]
              .template get<sol::usertype<declaring_type_t>>();
  usertype[_info.property_item.get_name().to_string()] =
      sol::property(_info.property_getter, _info.property_setter);
}

template <class T>
void sol_visitor::visit_global_property(
    rttr::visitor::property_info<T> const & _info) {
  visit_property(_info);
}

template <class T>
void sol_visitor::visit_global_getter_setter_property(
    rttr::visitor::property_getter_setter_info<T> const & _info) {
  visit_getter_setter_property(_info);
}

template <class T>
void sol_visitor::visit_readonly_property(
    rttr::visitor::property_info<T> const & _info) {
  using declaring_type_t =
      typename std::remove_cvref_t<decltype(_info)>::declaring_type;
  auto usertype =
      _state_internal()
          [rttr::type::get<declaring_type_t>().get_name().to_string()]
              .template get<sol::usertype<declaring_type_t>>();
  if constexpr (std::is_member_object_pointer_v<
                    decltype(_info.property_accessor)>) {
    usertype[_info.property_item.get_name().to_string()] =
        sol::readonly(_info.property_accessor);
  } else if constexpr (std::is_member_function_pointer_v<
                           decltype(_info.property_accessor)>) {
    usertype[_info.property_item.get_name().to_string()] =
        sol::property(_info.property_accessor);
  } else {
    usertype[_info.property_item.get_name().to_string()] =
        sol::var(*_info.property_accessor);
  }
}

template <class T>
void sol_visitor::visit_global_readonly_property(
    rttr::visitor::property_info<T> const & _info) {
  visit_readonly_property(_info);
}

template <class T>
void sol_visitor::visit(rttr::type const & _type) {
  if constexpr (std::is_enum_v<T>) {
    PH_ASSERT(_type.is_enumeration());

    auto usertype = _state_internal().new_usertype<T>(
        rttr::type::get<T>().get_name().to_string(), sol::no_constructor);

    auto enumeration = _type.get_enumeration();
    for (auto const & name : enumeration.get_names()) {
      bool ok                    = false;
      usertype[name.to_string()] = sol::var(
          static_cast<T>(enumeration.name_to_value(name).to_int64(&ok)));
      PH_ASSERT(ok);
    }
  } else {
    rttr::visitor::visit(_type);
  }
}
} // namespace phansar::common::reflect

RTTR_REGISTER_VISITOR(phansar::common::reflect::sol_visitor);
