#ifndef PHANSAR_COMMON_BINDINGS_HPP
#define PHANSAR_COMMON_BINDINGS_HPP

#include <phansar/vendor/json.hpp>
#include <phansar/vendor/pybind11.hpp>
#include <phansar/vendor/rttr.hpp>

namespace phansar::common::bindings {
class rttr_visitor : public rttr::visitor {
public:
    explicit rttr_visitor(py::module & _module);

    template <class T, class... BaseClasses>
    void visit_type_begin(const rttr::visitor::type_info<T> & _info);
    template <class T, class... BaseClasses>
    void visit_type_end(const rttr::visitor::type_info<T> & _info);
    template <class T, class... CtorArgs>
    void visit_constructor(const rttr::visitor::constructor_info<T> & _info);
    template <class T>
    void visit_constructor_function(const rttr::visitor::constructor_function_info<T> & _info);
    template <class T>
    void visit_method(const rttr::visitor::method_info<T> & _info);
    template <class T>
    void visit_global_method(const rttr::visitor::method_info<T> & _info);
    template <class T>
    void visit_property(const rttr::visitor::property_info<T> & _info);
    template <class T>
    void visit_getter_setter_property(const rttr::visitor::property_getter_setter_info<T> & _info);
    template <class T>
    void visit_global_property(const rttr::visitor::property_info<T> & _info);
    template <class T>
    void visit_global_getter_setter_property(
        const rttr::visitor::property_getter_setter_info<T> & _info);
    template <class T>
    void visit_readonly_property(const rttr::visitor::property_info<T> & _info);
    template <class T>
    void visit_global_readonly_property(const rttr::visitor::property_info<T> & _info);

private:
    py::module & m_module;

    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    RTTR_ENABLE(visitor)
};
} // namespace phansar::common::bindings

namespace rttr {
void to_json(nlohmann::ordered_json & _json, const instance & _obj);
}

#include <phansar/common/bindings.inl>

#endif
