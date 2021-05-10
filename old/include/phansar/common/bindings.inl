#include <phansar/common/bindings.hpp>
#include <phansar/common/macros.hpp>
#include <phansar/vendor/fmt.hpp>
#include <phansar/vendor/json.hpp>
#include <phansar/vendor/pybind11.hpp>

namespace phansar::common::bindings {
template <class T, class... BaseClasses>
void rttr_visitor::visit_type_begin(const rttr::visitor::type_info<T> & _info) {
    PH_UNUSED(_info);
    using declaring_type_t = typename type_info<T>::declaring_type;
    py::class_<declaring_type_t, BaseClasses...>(
        m_module,
        rttr::type::get<declaring_type_t>().get_name().to_string().c_str());
}

template <class T, class... BaseClasses>
void rttr_visitor::visit_type_end(const rttr::visitor::type_info<T> & _info) {
    PH_UNUSED(_info);
    using declaring_type_t = typename type_info<T>::declaring_type;
    py::class_<declaring_type_t>{
        m_module.attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
        .def("__str__",
             [](const declaring_type_t & _obj) {
                 return fmt::format("{}", nlohmann::ordered_json{rttr::instance{_obj}});
             })
        .def("__repr__", [](const declaring_type_t & _obj) {
            return fmt::format("{}", nlohmann::ordered_json{rttr::instance{_obj}});
        });
}

template <class T, class... CtorArgs>
void rttr_visitor::visit_constructor(const rttr::visitor::constructor_info<T> & _info) {
    PH_UNUSED(_info);
    using declaring_type_t = typename constructor_info<T>::declaring_type;
    py::class_<declaring_type_t>{
        m_module.attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
        .def(py::init<CtorArgs...>());
}

template <class T>
void rttr_visitor::visit_constructor_function(
    const rttr::visitor::constructor_function_info<T> & _info) {
    PH_UNUSED(_info);
}

template <class T>
void rttr_visitor::visit_method(const rttr::visitor::method_info<T> & _info) {
    using declaring_type_t = typename method_info<T>::declaring_type;
    py::class_<declaring_type_t>{
        m_module.attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
        .def(_info.method_item.get_name().to_string().c_str(), _info.function_ptr);
}

template <class T>
void rttr_visitor::visit_global_method(const rttr::visitor::method_info<T> & _info) {
    m_module.def(_info.method_item.get_name().to_string().c_str(), _info.function_ptr);
}

template <class T>
void rttr_visitor::visit_property(const rttr::visitor::property_info<T> & _info) {
    using declaring_type_t = typename property_info<T>::declaring_type;
    py::class_<declaring_type_t>{
        m_module.attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
        .def_readwrite(_info.property_item.get_name().to_string().c_str(), _info.property_accessor);
}

template <class T>
void rttr_visitor::visit_getter_setter_property(
    const rttr::visitor::property_getter_setter_info<T> & _info) {
    using declaring_type_t = typename property_getter_setter_info<T>::declaring_type;
    py::class_<declaring_type_t>{
        m_module.attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
        .def_property(_info.property_item.get_name().to_string().c_str(),
                      _info.property_getter,
                      _info.property_setter);
}

template <class T>
void rttr_visitor::visit_global_property(const rttr::visitor::property_info<T> & _info) {
    m_module.attr(_info.property_item.get_name().to_string().c_str()) = _info.property_accessor;
}

template <class T>
void rttr_visitor::visit_global_getter_setter_property(
    const rttr::visitor::property_getter_setter_info<T> & _info) {
    m_module.def(_info.method_item.get_name().to_string().c_str(), _info.property_getter);
}

template <class T>
void rttr_visitor::visit_readonly_property(const rttr::visitor::property_info<T> & _info) {
    using declaring_type_t = typename property_info<T>::declaring_type;
    if constexpr (std::is_member_object_pointer_v<decltype(_info.property_accessor)>) {
        py::class_<declaring_type_t>{
            m_module.attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
            .def_readonly(_info.property_item.get_name().to_string().c_str(),
                          _info.property_accessor);
    } else {
        py::class_<declaring_type_t>{
            m_module.attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
            .def_property_readonly(_info.property_item.get_name().to_string().c_str(),
                                   _info.property_accessor);
    }
}

template <class T>
void rttr_visitor::visit_global_readonly_property(const rttr::visitor::property_info<T> & _info) {
    m_module.attr(_info.property_item.get_name().to_string().c_str()) = _info.property_accessor;
}
} // namespace phansar::common::bindings

RTTR_REGISTER_VISITOR(phansar::common::bindings::rttr_visitor);
