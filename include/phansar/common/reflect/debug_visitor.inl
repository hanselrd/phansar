#include <phansar/common/macro.hpp>
#include <phansar/common/reflect/debug_visitor.hpp>

namespace phansar::common::reflect {
template <class T, class... BaseClasses>
void debug_visitor::visit_type_begin(const rttr::visitor::type_info<T> & _info) {
    PH_LOG_DEBUG("====================================================\n");

    PH_LOG_DEBUG("T= {}\n", typeid(T).name());
    // (PH_LOG_DEBUG("BaseClass= {}\n", typeid(BaseClasses).name()), ...);

    using base_classes_t = typename rttr::visitor::type_info<T>::base_classes;
    PH_LOG_DEBUG("base_classes_t= {}\n", typeid(base_classes_t).name());

    using declaring_type_t = typename rttr::visitor::type_info<T>::declaring_type;
    PH_LOG_DEBUG("declaring_type_t= {}\n", typeid(declaring_type_t).name());

    PH_LOG_DEBUG("len(base_classes)= {}\n", _info.type_item.get_base_classes().size());
    for (const auto & base_class : _info.type_item.get_base_classes()) {
        PH_LOG_DEBUG("base_class= {}\n", base_class.get_name().to_string());
    }

    PH_LOG_DEBUG("len(derived_classes)= {}\n", _info.type_item.get_derived_classes().size());
    for (const auto & derived_class : _info.type_item.get_derived_classes()) {
        PH_LOG_DEBUG("derived_class= {}\n", derived_class.get_name().to_string());
    }

    PH_LOG_DEBUG("id= {}\n", _info.type_item.get_id());
    PH_LOG_DEBUG("name= {}\n", _info.type_item.get_name().to_string());
    PH_LOG_DEBUG("len(constructors)= {}\n", _info.type_item.get_constructors().size());
    PH_LOG_DEBUG("len(methods)= {}\n", _info.type_item.get_methods().size());
    PH_LOG_DEBUG("len(properties)= {}\n", _info.type_item.get_properties().size());
    PH_LOG_DEBUG("raw_type= {}\n", _info.type_item.get_raw_type().get_name().to_string());
    PH_LOG_DEBUG("sizeof= {}\n", _info.type_item.get_sizeof());

    PH_LOG_DEBUG("len(template_arguments)= {}\n", _info.type_item.get_template_arguments().size());
    for (const auto & template_argument : _info.type_item.get_template_arguments()) {
        PH_LOG_DEBUG("template_argument= {}\n", template_argument.get_name().to_string());
    }

    PH_LOG_DEBUG("wrapped_type= {}\n", _info.type_item.get_wrapped_type().get_name().to_string());
    PH_LOG_DEBUG("is_arithmetic= {}\n", _info.type_item.is_arithmetic());
    PH_LOG_DEBUG("is_array= {}\n", _info.type_item.is_array());
    PH_LOG_DEBUG("is_associative_container= {}\n", _info.type_item.is_associative_container());
    PH_LOG_DEBUG("is_class= {}\n", _info.type_item.is_class());
    PH_LOG_DEBUG("is_enumeration= {}\n", _info.type_item.is_enumeration());
    PH_LOG_DEBUG("is_function_pointer= {}\n", _info.type_item.is_function_pointer());
    PH_LOG_DEBUG("is_member_function_pointer= {}\n", _info.type_item.is_member_function_pointer());
    PH_LOG_DEBUG("is_member_object_pointer= {}\n", _info.type_item.is_member_object_pointer());
    PH_LOG_DEBUG("is_pointer= {}\n", _info.type_item.is_pointer());
    PH_LOG_DEBUG("is_sequential_container= {}\n", _info.type_item.is_sequential_container());
    PH_LOG_DEBUG("is_template_instantiation= {}\n", _info.type_item.is_template_instantiation());
    PH_LOG_DEBUG("is_valid= {}\n", _info.type_item.is_valid());
    PH_LOG_DEBUG("is_wrapper= {}\n", _info.type_item.is_wrapper());
}

template <class T, class... BaseClasses>
void debug_visitor::visit_type_end(const rttr::visitor::type_info<T> & /*unused*/) {
    PH_LOG_DEBUG("====================================================\n");
}

template <class T, class... CtorArgs>
void debug_visitor::visit_constructor(const rttr::visitor::constructor_info<T> & _info) {
    PH_LOG_DEBUG("T= {}\n", typeid(T).name());
    // (PH_LOG_DEBUG("CtorArg= {}\n", typeid(CtorArgs).name()), ...);

    using declaring_type_t = typename rttr::visitor::constructor_info<T>::declaring_type;
    PH_LOG_DEBUG("declaring_type_t= {}\n", typeid(declaring_type_t).name());

    using policy_t = typename rttr::visitor::constructor_info<T>::policy;
    PH_LOG_DEBUG("policy_t= {}\n", typeid(policy_t).name());

    PH_LOG_DEBUG("access_level= {}\n",
                 static_cast<std::underlying_type_t<rttr::access_levels>>(
                     _info.ctor_item.get_access_level()));
    PH_LOG_DEBUG("declaring_type= {}\n",
                 _info.ctor_item.get_declaring_type().get_name().to_string());
    PH_LOG_DEBUG("instantiated_type= {}\n",
                 _info.ctor_item.get_instantiated_type().get_name().to_string());

    PH_LOG_DEBUG("len(parameter_infos)= {}\n", _info.ctor_item.get_parameter_infos().size());
    for (const auto & parameter_info : _info.ctor_item.get_parameter_infos()) {
        PH_LOG_DEBUG("parameter_info= {} {}\n",
                     parameter_info.get_type().get_name().to_string(),
                     parameter_info.get_name().to_string());
    }

    PH_LOG_DEBUG("signature= {}\n", _info.ctor_item.get_signature().to_string());
    PH_LOG_DEBUG("is_valid= {}\n", _info.ctor_item.is_valid());
}

template <class T>
void debug_visitor::visit_constructor_function(
    const rttr::visitor::constructor_function_info<T> & _info) {
    PH_LOG_DEBUG("T= {}\n", typeid(T).name());

    using declaring_type_t = typename rttr::visitor::constructor_function_info<T>::declaring_type;
    PH_LOG_DEBUG("declaring_type_t= {}\n", typeid(declaring_type_t).name());

    using policy_t = typename rttr::visitor::constructor_function_info<T>::policy;
    PH_LOG_DEBUG("policy_t= {}\n", typeid(policy_t).name());

    PH_LOG_DEBUG("function_ptr= {} {}\n",
                 typeid(decltype(_info.function_ptr)).name(),
                 _info.function_ptr);

    PH_LOG_DEBUG("access_level= {}\n",
                 static_cast<std::underlying_type_t<rttr::access_levels>>(
                     _info.ctor_item.get_access_level()));
    PH_LOG_DEBUG("declaring_type= {}\n",
                 _info.ctor_item.get_declaring_type().get_name().to_string());
    PH_LOG_DEBUG("instantiated_type= {}\n",
                 _info.ctor_item.get_instantiated_type().get_name().to_string());

    PH_LOG_DEBUG("len(parameter_infos)= {}\n", _info.ctor_item.get_parameter_infos().size());
    for (const auto & parameter_info : _info.ctor_item.get_parameter_infos()) {
        PH_LOG_DEBUG("parameter_info= {} {}\n",
                     parameter_info.get_type().get_name().to_string(),
                     parameter_info.get_name().to_string());
    }

    PH_LOG_DEBUG("signature= {}\n", _info.ctor_item.get_signature().to_string());
    PH_LOG_DEBUG("is_valid= {}\n", _info.ctor_item.is_valid());
}

template <class T>
void debug_visitor::visit_method(const rttr::visitor::method_info<T> & _info) {
    PH_UNUSED(_info);
}

template <class T>
void debug_visitor::visit_global_method(const rttr::visitor::method_info<T> & _info) {
    PH_UNUSED(_info);
}

template <class T>
void debug_visitor::visit_property(const rttr::visitor::property_info<T> & _info) {
    PH_UNUSED(_info);
}

template <class T>
void debug_visitor::visit_getter_setter_property(
    const rttr::visitor::property_getter_setter_info<T> & _info) {
    PH_UNUSED(_info);
}

template <class T>
void debug_visitor::visit_global_property(const rttr::visitor::property_info<T> & _info) {
    PH_UNUSED(_info);
}

template <class T>
void debug_visitor::visit_global_getter_setter_property(
    const rttr::visitor::property_getter_setter_info<T> & _info) {
    PH_UNUSED(_info);
}

template <class T>
void debug_visitor::visit_readonly_property(const rttr::visitor::property_info<T> & _info) {
    PH_UNUSED(_info);
}

template <class T>
void debug_visitor::visit_global_readonly_property(const rttr::visitor::property_info<T> & _info) {
    PH_UNUSED(_info);
}
} // namespace phansar::common::reflect

RTTR_REGISTER_VISITOR(phansar::common::reflect::debug_visitor);
