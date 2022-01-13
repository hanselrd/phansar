#include <phansar/common/rttr/debug_visitor.hpp>

#include <fmt/format.h>

namespace phansar::common::rttr {
template <class T, class... BaseClasses>
void debug_visitor::visit_type_begin(const ::rttr::visitor::type_info<T> & _info) {
    fmt::print("====================================================\n");
    fmt::print("T= {}\n", typeid(T).name());
    (fmt::print("BaseClass= {}\n", typeid(BaseClasses).name()), ...);

    using base_classes_t = typename ::rttr::visitor::type_info<T>::base_classes;
    fmt::print("base_classes_t= {}\n", typeid(base_classes_t).name());

    using declaring_type_t = typename ::rttr::visitor::type_info<T>::declaring_type;
    fmt::print("declaring_type_t= {}\n", typeid(declaring_type_t).name());

    fmt::print("len(base_classes)= {}\n", _info.type_item.get_base_classes().size());
    for (const auto & base_class : _info.type_item.get_base_classes()) {
        fmt::print("base_class= {}\n", base_class.get_name().to_string());
    }

    fmt::print("len(derived_classes)= {}\n", _info.type_item.get_derived_classes().size());
    for (const auto & derived_class : _info.type_item.get_derived_classes()) {
        fmt::print("derived_class= {}\n", derived_class.get_name().to_string());
    }

    fmt::print("id= {}\n", _info.type_item.get_id());
    fmt::print("name= {}\n", _info.type_item.get_name().to_string());
    fmt::print("len(constructors)= {}\n", _info.type_item.get_constructors().size());
    fmt::print("len(methods)= {}\n", _info.type_item.get_methods().size());
    fmt::print("len(properties)= {}\n", _info.type_item.get_properties().size());
    fmt::print("raw_type= {}\n", _info.type_item.get_raw_type().get_name().to_string());
    fmt::print("sizeof= {}\n", _info.type_item.get_sizeof());

    fmt::print("len(template_arguments)= {}\n", _info.type_item.get_template_arguments().size());
    for (const auto & template_argument : _info.type_item.get_template_arguments()) {
        fmt::print("template_argument= {}\n", template_argument.get_name().to_string());
    }

    fmt::print("wrapped_type= {}\n", _info.type_item.get_wrapped_type().get_name().to_string());
    fmt::print("is_arithmetic= {}\n", _info.type_item.is_arithmetic());
    fmt::print("is_array= {}\n", _info.type_item.is_array());
    fmt::print("is_associative_container= {}\n", _info.type_item.is_associative_container());
    fmt::print("is_class= {}\n", _info.type_item.is_class());
    fmt::print("is_enumeration= {}\n", _info.type_item.is_enumeration());
    fmt::print("is_function_pointer= {}\n", _info.type_item.is_function_pointer());
    fmt::print("is_member_function_pointer= {}\n", _info.type_item.is_member_function_pointer());
    fmt::print("is_member_object_pointer= {}\n", _info.type_item.is_member_object_pointer());
    fmt::print("is_pointer= {}\n", _info.type_item.is_pointer());
    fmt::print("is_sequential_container= {}\n", _info.type_item.is_sequential_container());
    fmt::print("is_template_instantiation= {}\n", _info.type_item.is_template_instantiation());
    fmt::print("is_valid= {}\n", _info.type_item.is_valid());
    fmt::print("is_wrapper= {}\n", _info.type_item.is_wrapper());
}

template <class T, class... BaseClasses>
void debug_visitor::visit_type_end(const ::rttr::visitor::type_info<T> & /*unused*/) {
    fmt::print("====================================================\n");
}

template <class T, class... CtorArgs>
void debug_visitor::visit_constructor(const ::rttr::visitor::constructor_info<T> & _info) {
    fmt::print("T= {}\n", typeid(T).name());
    (fmt::print("CtorArg= {}\n", typeid(CtorArgs).name()), ...);

    using declaring_type_t = typename ::rttr::visitor::constructor_info<T>::declaring_type;
    fmt::print("declaring_type_t= {}\n", typeid(declaring_type_t).name());

    using policy_t = typename ::rttr::visitor::constructor_info<T>::policy;
    fmt::print("policy_t= {}\n", typeid(policy_t).name());

    fmt::print("access_level= {}\n",
               static_cast<std::underlying_type_t<::rttr::access_levels>>(
                   _info.ctor_item.get_access_level()));
    fmt::print("declaring_type= {}\n", _info.ctor_item.get_declaring_type().get_name().to_string());
    fmt::print("instantiated_type= {}\n",
               _info.ctor_item.get_instantiated_type().get_name().to_string());

    fmt::print("len(parameter_infos)= {}\n", _info.ctor_item.get_parameter_infos().size());
    for (const auto & parameter_info : _info.ctor_item.get_parameter_infos()) {
        fmt::print("parameter_info= {} {}\n",
                   parameter_info.get_type().get_name().to_string(),
                   parameter_info.get_name().to_string());
    }

    fmt::print("signature= {}\n", _info.ctor_item.get_signature().to_string());
    fmt::print("is_valid= {}\n", _info.ctor_item.is_valid());
}

template <class T>
void debug_visitor::visit_constructor_function(
    const ::rttr::visitor::constructor_function_info<T> & _info) {
    fmt::print("T= {}\n", typeid(T).name());

    using declaring_type_t = typename ::rttr::visitor::constructor_function_info<T>::declaring_type;
    fmt::print("declaring_type_t= {}\n", typeid(declaring_type_t).name());

    using policy_t = typename ::rttr::visitor::constructor_function_info<T>::policy;
    fmt::print("policy_t= {}\n", typeid(policy_t).name());

    fmt::print("function_ptr= {} {}\n",
               typeid(decltype(_info.function_ptr)).name(),
               _info.function_ptr);

    fmt::print("access_level= {}\n",
               static_cast<std::underlying_type_t<::rttr::access_levels>>(
                   _info.ctor_item.get_access_level()));
    fmt::print("declaring_type= {}\n", _info.ctor_item.get_declaring_type().get_name().to_string());
    fmt::print("instantiated_type= {}\n",
               _info.ctor_item.get_instantiated_type().get_name().to_string());

    fmt::print("len(parameter_infos)= {}\n", _info.ctor_item.get_parameter_infos().size());
    for (const auto & parameter_info : _info.ctor_item.get_parameter_infos()) {
        fmt::print("parameter_info= {} {}\n",
                   parameter_info.get_type().get_name().to_string(),
                   parameter_info.get_name().to_string());
    }

    fmt::print("signature= {}\n", _info.ctor_item.get_signature().to_string());
    fmt::print("is_valid= {}\n", _info.ctor_item.is_valid());
}

template <class T>
void debug_visitor::visit_method(const ::rttr::visitor::method_info<T> & _info) {
    (void)_info; // TODO: remove
}

template <class T>
void debug_visitor::visit_global_method(const ::rttr::visitor::method_info<T> & _info) {
    (void)_info; // TODO: remove
}

template <class T>
void debug_visitor::visit_property(const ::rttr::visitor::property_info<T> & _info) {
    (void)_info; // TODO: remove
}

template <class T>
void debug_visitor::visit_getter_setter_property(
    const ::rttr::visitor::property_getter_setter_info<T> & _info) {
    (void)_info; // TODO: remove
}

template <class T>
void debug_visitor::visit_global_property(const ::rttr::visitor::property_info<T> & _info) {
    (void)_info; // TODO: remove
}

template <class T>
void debug_visitor::visit_global_getter_setter_property(
    const ::rttr::visitor::property_getter_setter_info<T> & _info) {
    (void)_info; // TODO: remove
}

template <class T>
void debug_visitor::visit_readonly_property(const ::rttr::visitor::property_info<T> & _info) {
    (void)_info; // TODO: remove
}

template <class T>
void debug_visitor::visit_global_readonly_property(
    const ::rttr::visitor::property_info<T> & _info) {
    (void)_info; // TODO: remove
}
} // namespace phansar::common::rttr

RTTR_REGISTER_VISITOR(phansar::common::rttr::debug_visitor);
