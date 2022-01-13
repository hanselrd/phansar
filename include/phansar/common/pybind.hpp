#ifndef PHANSAR_COMMON_PYBIND_HPP
#define PHANSAR_COMMON_PYBIND_HPP

#include <phansar/common/logger.hpp>

#include <fmt/format.h>
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/embed.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace phansar::common {
/* [[[cog
import codegen
codegen.class_(
    "logger",
    "common::logger",
    [
        ["std::string_view", "std::string_view", "std::size_t", "std::size_t"],
    ],
    [
        codegen.ClassMethod(name="handle", args=[], const=True),
        codegen.ClassMethod(name="trace", args=["std::string_view"]),
        codegen.ClassMethod(name="debug", args=["std::string_view"]),
        codegen.ClassMethod(name="info", args=["std::string_view"]),
        codegen.ClassMethod(name="warn", args=["std::string_view"]),
        codegen.ClassMethod(name="error", args=["std::string_view"]),
        codegen.ClassMethod(name="critical", args=["std::string_view"]),
    ],
    pybind=True,
)
]]] */
namespace pybind {
inline void pybind_logger(pybind11::module & _m) {
    py::class_<common::logger>(_m, "logger")
        .def(py::init<std::string_view, std::string_view, std::size_t, std::size_t>())
        .def("handle", py::overload_cast<>(&common::logger::handle, py::const_))
        .def("trace", py::overload_cast<std::string_view>(&common::logger::trace))
        .def("debug", py::overload_cast<std::string_view>(&common::logger::debug))
        .def("info", py::overload_cast<std::string_view>(&common::logger::info))
        .def("warn", py::overload_cast<std::string_view>(&common::logger::warn))
        .def("error", py::overload_cast<std::string_view>(&common::logger::error))
        .def("critical", py::overload_cast<std::string_view>(&common::logger::critical))
        .def("__repr__", [](const common::logger & _o) {
            return fmt::format("<logger object at {} with {} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        });
}
} // namespace pybind
/* [[[end]]] */
} // namespace phansar::common

#endif
