#ifndef PHANSAR_COMMON_REFLECT_PYBIND_VISITOR_HPP
#define PHANSAR_COMMON_REFLECT_PYBIND_VISITOR_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <pybind11/embed.h>
#include <rttr/type>
#include <rttr/visitor.h>

namespace py = pybind11;

namespace phansar::common::reflect {
class pybind_visitor : public rttr::visitor {
public:
    explicit pybind_visitor(py::module & _module);
    pybind_visitor(const pybind_visitor & _other);
    auto operator=(const pybind_visitor & _other) -> pybind_visitor &;
    pybind_visitor(pybind_visitor && _other) noexcept;
    auto operator=(pybind_visitor && _other) noexcept -> pybind_visitor &;
    ~pybind_visitor() override;

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
    template <class T>
    void visit_enumeration(const rttr::type & _type = rttr::type::get<T>());

private:
    [[nodiscard]] auto _module_internal() const -> py::module &;

    struct impl;
    utility::pimpl<impl> m_impl;

    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    RTTR_ENABLE(rttr::visitor)
};
} // namespace phansar::common::reflect

#include <phansar/common/reflect/pybind_visitor.inl>

#endif
