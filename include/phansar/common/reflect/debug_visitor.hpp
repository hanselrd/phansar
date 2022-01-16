#ifndef PHANSAR_COMMON_REFLECT_DEBUG_VISITOR_HPP
#define PHANSAR_COMMON_REFLECT_DEBUG_VISITOR_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <phansar/common/utility/rule_of_n.hpp>
#include <rttr/type>
#include <rttr/visitor.h>

namespace phansar::common::reflect {
class debug_visitor : public rttr::visitor {
public:
    PH_RULE_OF_6(debug_visitor);

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
    struct impl;
    utility::pimpl<impl> m_impl;

    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    RTTR_ENABLE(rttr::visitor)
};
} // namespace phansar::common::reflect

#include <phansar/common/reflect/debug_visitor.inl>

#endif
