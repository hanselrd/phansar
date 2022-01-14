#include <phansar/common/rttr/pybind_visitor.hpp>

namespace phansar::common::rttr {
struct pybind_visitor::impl {
    py::module & module;
};

pybind_visitor::pybind_visitor(py::module & _module) : m_impl{_module} {}

PH_RULE_OF_5_DEFAULT(pybind_visitor);

auto pybind_visitor::_module_internal() const -> py::module & {
    return m_impl->module;
}
} // namespace phansar::common::rttr
