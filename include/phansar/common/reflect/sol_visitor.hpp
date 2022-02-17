#ifndef PHANSAR_COMMON_REFLECT_SOL_VISITOR_HPP
#define PHANSAR_COMMON_REFLECT_SOL_VISITOR_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <rttr/type>
#include <rttr/visitor.h>
#include <sol/sol.hpp>

namespace phansar::common::reflect {
class sol_visitor : public rttr::visitor {
public:
    explicit sol_visitor(sol::state & _state);
    sol_visitor(const sol_visitor & _other);
    auto operator=(const sol_visitor & _other) -> sol_visitor &;
    sol_visitor(sol_visitor && _other) noexcept;
    auto operator=(sol_visitor && _other) noexcept -> sol_visitor &;
    ~sol_visitor() override;

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
    void visit(const rttr::type & _type = rttr::type::get<T>());

private:
    [[nodiscard]] auto _state_internal() const -> sol::state &;
    void               _constructor_counter_reset_internal();
    auto               _constructor_counter_next_internal() -> std::size_t;

    struct impl;
    utility::pimpl<impl> m_impl;

    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    RTTR_ENABLE(rttr::visitor)
};
} // namespace phansar::common::reflect

#include <phansar/common/reflect/sol_visitor.inl>

#endif
