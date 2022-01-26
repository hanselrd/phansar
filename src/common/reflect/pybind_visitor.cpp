#include <phansar/common/reflect/pybind_visitor.hpp>

namespace phansar::common::reflect {
struct pybind_visitor::impl {
    py::module * module{};
};

pybind_visitor::pybind_visitor(py::module & _module) : m_impl{&_module} {}

pybind_visitor::pybind_visitor(const pybind_visitor & _other) = default;

auto pybind_visitor::operator=(const pybind_visitor & _other) -> pybind_visitor & = default;

pybind_visitor::pybind_visitor(pybind_visitor && _other) noexcept = default;

auto pybind_visitor::operator=(pybind_visitor && _other) noexcept -> pybind_visitor & = default;

pybind_visitor::~pybind_visitor() = default;

auto pybind_visitor::_module_internal() const -> py::module & {
    return *m_impl->module;
}
} // namespace phansar::common::reflect
