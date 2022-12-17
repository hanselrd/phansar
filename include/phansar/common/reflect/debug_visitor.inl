#include <phansar/common/macro.hpp>
#include <phansar/common/reflect/debug_visitor.hpp>
#include <type_traits>

namespace phansar::common::reflect {
template <class T, class... BaseClasses>
void debug_visitor::visit_type_begin(
    const rttr::visitor::type_info<T> & _info) {
  PH_LOG_DEBUG("====================================================");

  PH_LOG_DEBUG("T= {}", typeid(T).name());

  auto log_base_class = [](auto _base_class) {
    PH_LOG_DEBUG("BaseClass= {}",
                 typeid(std::remove_pointer_t<decltype(_base_class)>).name());
  };
  PH_UNUSED(log_base_class);
  (log_base_class(static_cast<BaseClasses *>(nullptr)), ...);

  using base_classes_t = typename rttr::visitor::type_info<T>::base_classes;
  PH_LOG_DEBUG("base_classes_t= {}", typeid(base_classes_t).name());

  using declaring_type_t = typename rttr::visitor::type_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  PH_LOG_DEBUG("len(base_classes)= {}",
               _info.type_item.get_base_classes().size());
  for (const auto & base_class : _info.type_item.get_base_classes()) {
    PH_LOG_DEBUG("base_class= {}", base_class.get_name().to_string());
  }

  PH_LOG_DEBUG("len(derived_classes)= {}",
               _info.type_item.get_derived_classes().size());
  for (const auto & derived_class : _info.type_item.get_derived_classes()) {
    PH_LOG_DEBUG("derived_class= {}", derived_class.get_name().to_string());
  }

  PH_LOG_DEBUG("id= {}", _info.type_item.get_id());

  PH_LOG_DEBUG("name= {}", _info.type_item.get_name().to_string());

  PH_LOG_DEBUG("len(constructors)= {}",
               _info.type_item.get_constructors().size());

  PH_LOG_DEBUG("len(methods)= {}", _info.type_item.get_methods().size());

  PH_LOG_DEBUG("len(properties)= {}", _info.type_item.get_properties().size());

  PH_LOG_DEBUG("raw_type= {}",
               _info.type_item.get_raw_type().get_name().to_string());

  PH_LOG_DEBUG("sizeof= {}", _info.type_item.get_sizeof());

  PH_LOG_DEBUG("len(template_arguments)= {}",
               _info.type_item.get_template_arguments().size());
  for (const auto & template_argument :
       _info.type_item.get_template_arguments()) {
    PH_LOG_DEBUG("template_argument= {}",
                 template_argument.get_name().to_string());
  }

  PH_LOG_DEBUG("wrapped_type= {}",
               _info.type_item.get_wrapped_type().get_name().to_string());

  PH_LOG_DEBUG("is_arithmetic= {}", _info.type_item.is_arithmetic());

  PH_LOG_DEBUG("is_array= {}", _info.type_item.is_array());

  PH_LOG_DEBUG("is_associative_container= {}",
               _info.type_item.is_associative_container());

  PH_LOG_DEBUG("is_class= {}", _info.type_item.is_class());

  PH_LOG_DEBUG("is_enumeration= {}", _info.type_item.is_enumeration());

  PH_LOG_DEBUG("is_function_pointer= {}",
               _info.type_item.is_function_pointer());

  PH_LOG_DEBUG("is_member_function_pointer= {}",
               _info.type_item.is_member_function_pointer());

  PH_LOG_DEBUG("is_member_object_pointer= {}",
               _info.type_item.is_member_object_pointer());

  PH_LOG_DEBUG("is_pointer= {}", _info.type_item.is_pointer());

  PH_LOG_DEBUG("is_sequential_container= {}",
               _info.type_item.is_sequential_container());

  PH_LOG_DEBUG("is_template_instantiation= {}",
               _info.type_item.is_template_instantiation());

  PH_LOG_DEBUG("is_valid= {}", _info.type_item.is_valid());

  PH_LOG_DEBUG("is_wrapper= {}", _info.type_item.is_wrapper());
}

template <class T, class... BaseClasses>
void debug_visitor::visit_type_end(
    const rttr::visitor::type_info<T> & /*unused*/) {
  PH_LOG_DEBUG("====================================================");
}

template <class T, class... CtorArgs>
void debug_visitor::visit_constructor(
    const rttr::visitor::constructor_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  auto log_ctor_arg = [](auto _ctor_arg) {
    PH_LOG_DEBUG("CtorArg= {}",
                 typeid(std::remove_pointer_t<decltype(_ctor_arg)>).name());
  };
  PH_UNUSED(log_ctor_arg);
  (log_ctor_arg(static_cast<CtorArgs *>(nullptr)), ...);

  using declaring_type_t =
      typename rttr::visitor::constructor_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t = typename rttr::visitor::constructor_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.ctor_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.ctor_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("instantiated_type= {}",
               _info.ctor_item.get_instantiated_type().get_name().to_string());

  PH_LOG_DEBUG("len(parameter_infos)= {}",
               _info.ctor_item.get_parameter_infos().size());
  for (const auto & parameter_info : _info.ctor_item.get_parameter_infos()) {
    PH_LOG_DEBUG("parameter_info= {} {}",
                 parameter_info.get_type().get_name().to_string(),
                 parameter_info.get_name().to_string());
  }

  PH_LOG_DEBUG("signature= {}", _info.ctor_item.get_signature().to_string());

  PH_LOG_DEBUG("is_valid= {}", _info.ctor_item.is_valid());
}

template <class T>
void debug_visitor::visit_constructor_function(
    const rttr::visitor::constructor_function_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  using declaring_type_t =
      typename rttr::visitor::constructor_function_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t = typename rttr::visitor::constructor_function_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("function_ptr= {}", typeid(decltype(_info.function_ptr)).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.ctor_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.ctor_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("instantiated_type= {}",
               _info.ctor_item.get_instantiated_type().get_name().to_string());

  PH_LOG_DEBUG("len(parameter_infos)= {}",
               _info.ctor_item.get_parameter_infos().size());
  for (const auto & parameter_info : _info.ctor_item.get_parameter_infos()) {
    PH_LOG_DEBUG("parameter_info= {} {}",
                 parameter_info.get_type().get_name().to_string(),
                 parameter_info.get_name().to_string());
  }

  PH_LOG_DEBUG("signature= {}", _info.ctor_item.get_signature().to_string());

  PH_LOG_DEBUG("is_valid= {}", _info.ctor_item.is_valid());
}

template <class T>
void debug_visitor::visit_method(const rttr::visitor::method_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  using declaring_type_t =
      typename rttr::visitor::method_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t = typename rttr::visitor::method_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("function_ptr= {}", typeid(decltype(_info.function_ptr)).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.method_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.method_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("name= {}", _info.method_item.get_name().to_string());

  PH_LOG_DEBUG("len(parameter_infos)= {}",
               _info.method_item.get_parameter_infos().size());
  for (const auto & parameter_info : _info.method_item.get_parameter_infos()) {
    PH_LOG_DEBUG("parameter_info= {} {}",
                 parameter_info.get_type().get_name().to_string(),
                 parameter_info.get_name().to_string());
  }

  PH_LOG_DEBUG("return_type= {}",
               _info.method_item.get_return_type().get_name().to_string());

  PH_LOG_DEBUG("signature= {}", _info.method_item.get_signature().to_string());

  PH_LOG_DEBUG("is_static= {}", _info.method_item.is_static());

  PH_LOG_DEBUG("is_valid= {}", _info.method_item.is_valid());
}

template <class T>
void debug_visitor::visit_global_method(
    const rttr::visitor::method_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  using declaring_type_t =
      typename rttr::visitor::method_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t = typename rttr::visitor::method_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("function_ptr= {}", typeid(decltype(_info.function_ptr)).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.method_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.method_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("name= {}", _info.method_item.get_name().to_string());

  PH_LOG_DEBUG("len(parameter_infos)= {}",
               _info.method_item.get_parameter_infos().size());
  for (const auto & parameter_info : _info.method_item.get_parameter_infos()) {
    PH_LOG_DEBUG("parameter_info= {} {}",
                 parameter_info.get_type().get_name().to_string(),
                 parameter_info.get_name().to_string());
  }

  PH_LOG_DEBUG("return_type= {}",
               _info.method_item.get_return_type().get_name().to_string());

  PH_LOG_DEBUG("signature= {}", _info.method_item.get_signature().to_string());

  PH_LOG_DEBUG("is_static= {}", _info.method_item.is_static());

  PH_LOG_DEBUG("is_valid= {}", _info.method_item.is_valid());
}

template <class T>
void debug_visitor::visit_property(
    const rttr::visitor::property_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  using declaring_type_t =
      typename rttr::visitor::property_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t = typename rttr::visitor::property_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("property_accessor= {}",
               typeid(decltype(_info.property_accessor)).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.property_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.property_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("name= {}", _info.property_item.get_name().to_string());

  PH_LOG_DEBUG("type= {}",
               _info.property_item.get_type().get_name().to_string());

  PH_LOG_DEBUG("is_enumeration= {}", _info.property_item.is_enumeration());

  PH_LOG_DEBUG("is_readonly= {}", _info.property_item.is_readonly());

  PH_LOG_DEBUG("is_static= {}", _info.property_item.is_static());

  PH_LOG_DEBUG("is_valid= {}", _info.property_item.is_valid());
}

template <class T>
void debug_visitor::visit_getter_setter_property(
    const rttr::visitor::property_getter_setter_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  using declaring_type_t =
      typename rttr::visitor::property_getter_setter_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t =
      typename rttr::visitor::property_getter_setter_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("property_getter= {}",
               typeid(decltype(_info.property_getter)).name());

  PH_LOG_DEBUG("property_setter= {}",
               typeid(decltype(_info.property_setter)).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.property_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.property_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("name= {}", _info.property_item.get_name().to_string());

  PH_LOG_DEBUG("type= {}",
               _info.property_item.get_type().get_name().to_string());

  PH_LOG_DEBUG("is_enumeration= {}", _info.property_item.is_enumeration());

  PH_LOG_DEBUG("is_readonly= {}", _info.property_item.is_readonly());

  PH_LOG_DEBUG("is_static= {}", _info.property_item.is_static());

  PH_LOG_DEBUG("is_valid= {}", _info.property_item.is_valid());
}

template <class T>
void debug_visitor::visit_global_property(
    const rttr::visitor::property_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  using declaring_type_t =
      typename rttr::visitor::property_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t = typename rttr::visitor::property_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("property_accessor= {}",
               typeid(decltype(_info.property_accessor)).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.property_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.property_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("name= {}", _info.property_item.get_name().to_string());

  PH_LOG_DEBUG("type= {}",
               _info.property_item.get_type().get_name().to_string());

  PH_LOG_DEBUG("is_enumeration= {}", _info.property_item.is_enumeration());

  PH_LOG_DEBUG("is_readonly= {}", _info.property_item.is_readonly());

  PH_LOG_DEBUG("is_static= {}", _info.property_item.is_static());

  PH_LOG_DEBUG("is_valid= {}", _info.property_item.is_valid());
}

template <class T>
void debug_visitor::visit_global_getter_setter_property(
    const rttr::visitor::property_getter_setter_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  using declaring_type_t =
      typename rttr::visitor::property_getter_setter_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t =
      typename rttr::visitor::property_getter_setter_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("property_getter= {}",
               typeid(decltype(_info.property_getter)).name());

  PH_LOG_DEBUG("property_setter= {}",
               typeid(decltype(_info.property_setter)).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.property_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.property_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("name= {}", _info.property_item.get_name().to_string());

  PH_LOG_DEBUG("type= {}",
               _info.property_item.get_type().get_name().to_string());

  PH_LOG_DEBUG("is_enumeration= {}", _info.property_item.is_enumeration());

  PH_LOG_DEBUG("is_readonly= {}", _info.property_item.is_readonly());

  PH_LOG_DEBUG("is_static= {}", _info.property_item.is_static());

  PH_LOG_DEBUG("is_valid= {}", _info.property_item.is_valid());
}

template <class T>
void debug_visitor::visit_readonly_property(
    const rttr::visitor::property_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  using declaring_type_t =
      typename rttr::visitor::property_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t = typename rttr::visitor::property_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("property_accessor= {}",
               typeid(decltype(_info.property_accessor)).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.property_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.property_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("name= {}", _info.property_item.get_name().to_string());

  PH_LOG_DEBUG("type= {}",
               _info.property_item.get_type().get_name().to_string());

  PH_LOG_DEBUG("is_enumeration= {}", _info.property_item.is_enumeration());

  PH_LOG_DEBUG("is_readonly= {}", _info.property_item.is_readonly());

  PH_LOG_DEBUG("is_static= {}", _info.property_item.is_static());

  PH_LOG_DEBUG("is_valid= {}", _info.property_item.is_valid());
}

template <class T>
void debug_visitor::visit_global_readonly_property(
    const rttr::visitor::property_info<T> & _info) {
  PH_LOG_DEBUG("T= {}", typeid(T).name());

  using declaring_type_t =
      typename rttr::visitor::property_info<T>::declaring_type;
  PH_LOG_DEBUG("declaring_type_t= {}", typeid(declaring_type_t).name());

  using policy_t = typename rttr::visitor::property_info<T>::policy;
  PH_LOG_DEBUG("policy_t= {}", typeid(policy_t).name());

  PH_LOG_DEBUG("property_accessor= {}",
               typeid(decltype(_info.property_accessor)).name());

  PH_LOG_DEBUG("access_level= {}",
               static_cast<std::underlying_type_t<rttr::access_levels>>(
                   _info.property_item.get_access_level()));

  PH_LOG_DEBUG("declaring_type= {}",
               _info.property_item.get_declaring_type().get_name().to_string());

  PH_LOG_DEBUG("name= {}", _info.property_item.get_name().to_string());

  PH_LOG_DEBUG("type= {}",
               _info.property_item.get_type().get_name().to_string());

  PH_LOG_DEBUG("is_enumeration= {}", _info.property_item.is_enumeration());

  PH_LOG_DEBUG("is_readonly= {}", _info.property_item.is_readonly());

  PH_LOG_DEBUG("is_static= {}", _info.property_item.is_static());

  PH_LOG_DEBUG("is_valid= {}", _info.property_item.is_valid());
}
} // namespace phansar::common::reflect

RTTR_REGISTER_VISITOR(phansar::common::reflect::debug_visitor);
