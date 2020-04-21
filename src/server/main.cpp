#include <phansar/common.hpp>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

auto main(int argc, char * argv[]) -> int {
    phansar::common::system::init(argc, argv);

    LOGI("Binary Name: {}", phansar::common::config::get_binary_name());
    LOGI("Config File: {}", phansar::common::config::get_config_file());
    LOGI("Log File: {}", phansar::common::config::get_log_file());
    LOGI("Log Level: {}", phansar::common::config::get_log_level());
    LOGI("IP Address: {}", phansar::common::config::get_ip_address());
    LOGI("Port: {}", phansar::common::config::get_port());
    LOGI("Num Threads: {}", phansar::common::config::get_num_threads());

    auto lua = sol::state{};
    lua.open_libraries(sol::lib::base, sol::lib::package);
    lua.script(R"lua(
        print('test test test!')
    )lua");

    phansar::common::system::shutdown();

    return 0;
}
