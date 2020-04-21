#include <phansar/common.hpp>

auto main(int argc, char * argv[]) -> int {
    phansar::common::system::init(argc, argv);

    LOGI("Binary Name: {}", phansar::common::config::get_binary_name());
    LOGI("Config File: {}", phansar::common::config::get_config_file());
    LOGI("Log File: {}", phansar::common::config::get_log_file());
    LOGI("Log Level: {}", phansar::common::config::get_log_level());
    LOGI("IP Address: {}", phansar::common::config::get_ip_address());
    LOGI("Port: {}", phansar::common::config::get_port());
    LOGI("Num Threads: {}", phansar::common::config::get_num_threads());

    phansar::common::system::shutdown();

    return 0;
}
