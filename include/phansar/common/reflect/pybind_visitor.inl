#include <phansar/common/macro.hpp>
#include <phansar/common/reflect/pybind_visitor.hpp>
#include <fmt/format.h>

namespace phansar::common::reflect {
template <class T, class... BaseClasses>
void pybind_visitor::visit_type_begin(const rttr::visitor::type_info<T> & _info) {
    PH_UNUSED(_info);

    using declaring_type_t = typename rttr::visitor::type_info<T>::declaring_type;
    py::class_<declaring_type_t, BaseClasses...>(
        _module_internal(),
        rttr::type::get<declaring_type_t>().get_name().to_string().c_str());
}

template <class T, class... BaseClasses>
void pybind_visitor::visit_type_end(const rttr::visitor::type_info<T> & _info) {
    PH_UNUSED(_info);

    using declaring_type_t = typename rttr::visitor::type_info<T>::declaring_type;
    py::class_<declaring_type_t>{
        _module_internal().attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
        .def("__repr__", [](const declaring_type_t & _obj) {
            return fmt::format("<{} object at {} with {} byte(s)>",
                               rttr::type::get<declaring_type_t>().get_name().to_string(),
                               static_cast<const void *>(&_obj),
                               sizeof(_obj));
        });
}

template <class T, class... CtorArgs>
void pybind_visitor::visit_constructor(const rttr::visitor::constructor_info<T> & _info) {
    PH_UNUSED(_info);

    using declaring_type_t = typename rttr::visitor::constructor_info<T>::declaring_type;
    py::class_<declaring_type_t>{
        _module_internal().attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
        .def(py::init<CtorArgs...>());
}

template <class T>
void pybind_visitor::visit_constructor_function(
    const rttr::visitor::constructor_function_info<T> & _info) {
    using declaring_type_t = typename rttr::visitor::constructor_function_info<T>::declaring_type;
    py::class_<declaring_type_t>{
        _module_internal().attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
        .def(py::init(_info.function_ptr));
}

template <class T>
void pybind_visitor::visit_method(const rttr::visitor::method_info<T> & _info) {
    using declaring_type_t = typename rttr::visitor::method_info<T>::declaring_type;
    py::class_<declaring_type_t>{
        _module_internal().attr(rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
        .def(_info.method_item.get_name().to_string().c_str(), _info.function_ptr);
}

template <class T>
void pybind_visitor::visit_global_method(const rttr::visitor::method_info<T> & _info) {
    _module_internal().def(_info.method_item.get_name().to_string().c_str(), _info.function_ptr);
}

template <class T>
void pybind_visitor::visit_property(const rttr::visitor::property_info<T> & _info) {
    using declaring_type_t = typename rttr::visitor::property_info<T>::declaring_type;
    if constexpr (! std::is_member_pointer_v<decltype(_info.property_accessor)>) {
        py::class_<declaring_type_t>{
            _module_internal().attr(
                rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
            .def_readwrite_static(_info.property_item.get_name().to_string().c_str(),
                                  _info.property_accessor);
    } else {
        py::class_<declaring_type_t>{
            _module_internal().attr(
                rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
            .def_readwrite(_info.property_item.get_name().to_string().c_str(),
                           _info.property_accessor);
    }
}

template <class T>
void pybind_visitor::visit_getter_setter_property(
    const rttr::visitor::property_getter_setter_info<T> & _info) {
    using declaring_type_t = typename rttr::visitor::property_getter_setter_info<T>::declaring_type;
    if constexpr (! std::is_member_pointer_v<decltype(_info.property_getter)> &&
                  ! std::is_member_pointer_v<decltype(_info.property_setter)>) {
        py::class_<declaring_type_t>{
            _module_internal().attr(
                rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
            .def_property_static(_info.property_item.get_name().to_string().c_str(),
                                 _info.property_getter,
                                 _info.property_setter);
    } else {
        py::class_<declaring_type_t>{
            _module_internal().attr(
                rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
            .def_property(_info.property_item.get_name().to_string().c_str(),
                          _info.property_getter,
                          _info.property_setter);
    }
}

template <class T>
void pybind_visitor::visit_global_property(const rttr::visitor::property_info<T> & _info) {
    _module_internal().attr(_info.property_item.get_name().to_string().c_str()) =
        _info.property_accessor;
}

template <class T>
void pybind_visitor::visit_global_getter_setter_property(
    const rttr::visitor::property_getter_setter_info<T> & _info) {
    _module_internal().def(_info.property_item.get_name().to_string().c_str(),
                           _info.property_getter);
}

template <class T>
void pybind_visitor::visit_readonly_property(const rttr::visitor::property_info<T> & _info) {
    using declaring_type_t = typename rttr::visitor::property_info<T>::declaring_type;
    if constexpr (std::is_member_object_pointer_v<decltype(_info.property_accessor)>) {
        if constexpr (! std::is_member_pointer_v<decltype(_info.property_accessor)>) {
            py::class_<declaring_type_t>{
                _module_internal().attr(
                    rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
                .def_readonly_static(_info.property_item.get_name().to_string().c_str(),
                                     _info.property_accessor);
        } else {
            py::class_<declaring_type_t>{
                _module_internal().attr(
                    rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
                .def_readonly(_info.property_item.get_name().to_string().c_str(),
                              _info.property_accessor);
        }
    } else {
        if constexpr (! std::is_member_pointer_v<decltype(_info.property_accessor)>) {
            py::class_<declaring_type_t>{
                _module_internal().attr(
                    rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
                .def_property_readonly_static(_info.property_item.get_name().to_string().c_str(),
                                              _info.property_accessor);
        } else {
            py::class_<declaring_type_t>{
                _module_internal().attr(
                    rttr::type::get<declaring_type_t>().get_name().to_string().c_str())}
                .def_property_readonly(_info.property_item.get_name().to_string().c_str(),
                                       _info.property_accessor);
        }
    }
}

template <class T>
void pybind_visitor::visit_global_readonly_property(const rttr::visitor::property_info<T> & _info) {
    _module_internal().attr(_info.property_item.get_name().to_string().c_str()) =
        _info.property_accessor;
}
} // namespace phansar::common::reflect

RTTR_REGISTER_VISITOR(phansar::common::reflect::pybind_visitor);
