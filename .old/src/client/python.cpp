#include <phansar/common/bindings.hpp>
#include <phansar/common/histogram.hpp>

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
PYBIND11_EMBEDDED_MODULE(phansar, m) {
    /* phansar::common::python::embed(m); */
    auto visitor = phansar::common::bindings::rttr_visitor{m};
    visitor.visit(rttr::type::get<phansar::common::histogram<double>::bin>());
    visitor.visit(rttr::type::get<phansar::common::histogram<double>::sample>());
    visitor.visit(rttr::type::get<phansar::common::histogram<double>>());
}
