#include <phansar/common.hpp>

#include <phansar/vendor/pybind11.hpp>

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
PYBIND11_EMBEDDED_MODULE(py_phansar, m) {
    auto fast_calc = m.def_submodule("fast_calc");
    fast_calc.def("add", [](int i, int j) { return i + j; });
}

auto main(int argc, char * argv[]) -> int {
    phansar::common::system::init(argc, argv);

    LOGI("Binary Name: {}", phansar::common::config::get_binary_name());
    LOGI("Config File: {}", phansar::common::config::get_config_file());
    LOGI("Log File: {}", phansar::common::config::get_log_file());
    LOGI("Log Level: {}", phansar::common::config::get_log_level());
    LOGI("IP Address: {}", phansar::common::config::get_ip_address());
    LOGI("Port: {}", phansar::common::config::get_port());
    LOGI("Num Threads: {}", phansar::common::config::get_num_threads());

    auto guard = py::scoped_interpreter{};
    py::print("Hello world!");
    py::exec(R"python(
        from py_phansar import fast_calc

        print("Hello, {name}! The answer is {number}".format(name="Bob", number=42))
        print("{} + {} = {}".format(3, 4, fast_calc.add(3, 4)))
    )python");
    py::exec(R"python(
        from inspect import currentframe, getframeinfo

        frameinfo = getframeinfo(currentframe())
        print(frameinfo)
        print(frameinfo.filename, frameinfo.lineno)
    )python");

    phansar::common::system::shutdown();

    return 0;
}
