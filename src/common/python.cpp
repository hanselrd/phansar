#include <phansar/common/log.hpp>
#include <phansar/common/python.hpp>

#include <phansar/vendor/pybind11.hpp>

#include <string>
#include <string_view>

namespace phansar::common::python {
void embed(py::module & m) {
    auto common = m.def_submodule("common");

    auto log = common.def_submodule("log");
    log.def("trace", [](std::string_view message) {
        auto inspect   = py::module::import("inspect");
        auto frameinfo = inspect.attr("getframeinfo")(inspect.attr("currentframe")());
        log::print(frameinfo.attr("filename").cast<std::string>(),
                   frameinfo.attr("lineno").cast<int>(),
                   log::level::trace,
                   message);
    });
    log.def("debug", [](std::string_view message) {
        auto inspect   = py::module::import("inspect");
        auto frameinfo = inspect.attr("getframeinfo")(inspect.attr("currentframe")());
        log::print(frameinfo.attr("filename").cast<std::string>(),
                   frameinfo.attr("lineno").cast<int>(),
                   log::level::debug,
                   message);
    });
    log.def("info", [](std::string_view message) {
        auto inspect   = py::module::import("inspect");
        auto frameinfo = inspect.attr("getframeinfo")(inspect.attr("currentframe")());
        log::print(frameinfo.attr("filename").cast<std::string>(),
                   frameinfo.attr("lineno").cast<int>(),
                   log::level::info,
                   message);
    });
    log.def("warning", [](std::string_view message) {
        auto inspect   = py::module::import("inspect");
        auto frameinfo = inspect.attr("getframeinfo")(inspect.attr("currentframe")());
        log::print(frameinfo.attr("filename").cast<std::string>(),
                   frameinfo.attr("lineno").cast<int>(),
                   log::level::warning,
                   message);
    });
    log.def("error", [](std::string_view message) {
        auto inspect   = py::module::import("inspect");
        auto frameinfo = inspect.attr("getframeinfo")(inspect.attr("currentframe")());
        log::print(frameinfo.attr("filename").cast<std::string>(),
                   frameinfo.attr("lineno").cast<int>(),
                   log::level::error,
                   message);
    });
    log.def("critical", [](std::string_view message) {
        auto inspect   = py::module::import("inspect");
        auto frameinfo = inspect.attr("getframeinfo")(inspect.attr("currentframe")());
        log::print(frameinfo.attr("filename").cast<std::string>(),
                   frameinfo.attr("lineno").cast<int>(),
                   log::level::critical,
                   message);
    });
}
} // namespace phansar::common::python
