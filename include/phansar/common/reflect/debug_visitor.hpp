#ifndef PHANSAR_COMMON_REFLECT_DEBUG_VISITOR_HPP
#define PHANSAR_COMMON_REFLECT_DEBUG_VISITOR_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <rttr/type>
#include <rttr/visitor.h>

namespace phansar::common::reflect {
class debug_visitor : public rttr::visitor {
public:
  debug_visitor();
  debug_visitor(debug_visitor const & _other);
  auto operator=(debug_visitor const & _other) -> debug_visitor &;
  debug_visitor(debug_visitor && _other) noexcept;
  auto operator=(debug_visitor && _other) noexcept -> debug_visitor &;
  ~debug_visitor() override;

  template <class T, class... BaseClasses>
  void visit_type_begin(rttr::visitor::type_info<T> const & _info);
  template <class T, class... BaseClasses>
  void visit_type_end(rttr::visitor::type_info<T> const & _info);
  template <class T, class... CtorArgs>
  void visit_constructor(rttr::visitor::constructor_info<T> const & _info);
  template <class T>
  void visit_constructor_function(
      rttr::visitor::constructor_function_info<T> const & _info);
  template <class T>
  void visit_method(rttr::visitor::method_info<T> const & _info);
  template <class T>
  void visit_global_method(rttr::visitor::method_info<T> const & _info);
  template <class T>
  void visit_property(rttr::visitor::property_info<T> const & _info);
  template <class T>
  void visit_getter_setter_property(
      rttr::visitor::property_getter_setter_info<T> const & _info);
  template <class T>
  void visit_global_property(rttr::visitor::property_info<T> const & _info);
  template <class T>
  void visit_global_getter_setter_property(
      rttr::visitor::property_getter_setter_info<T> const & _info);
  template <class T>
  void visit_readonly_property(rttr::visitor::property_info<T> const & _info);
  template <class T>
  void
  visit_global_readonly_property(rttr::visitor::property_info<T> const & _info);

private:
  struct impl;
  utility::pimpl<impl> m_impl;

  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  RTTR_ENABLE(rttr::visitor)
};
} // namespace phansar::common::reflect

#include <phansar/common/reflect/debug_visitor.inl>

#endif
