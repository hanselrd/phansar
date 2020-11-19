#include <phansar/common/log.hpp>
#include <phansar/common/python.hpp>

namespace phansar::common::python {
void embed(py::module & _module) {
    auto common = _module.def_submodule("common");

    auto logger = [](log::level _level) {
        return [_level](std::string_view _message) {
            if (log::instance() != nullptr) {
                auto inspect   = py::module::import("inspect");
                auto frameinfo = inspect.attr("getframeinfo")(inspect.attr("currentframe")());
                log::instance()->print(_level,
                                       frameinfo.attr("filename").cast<std::string>(),
                                       frameinfo.attr("lineno").cast<int>(),
                                       _message);
            }
        };
    };
    auto log = common.def_submodule("log");
    log.def("trace", logger(log::level::trace));
    log.def("debug", logger(log::level::debug));
    log.def("info", logger(log::level::info));
    log.def("warning", logger(log::level::warning));
    log.def("error", logger(log::level::error));
    log.def("critical", logger(log::level::critical));
}
} // namespace phansar::common::python
