#include <common.hpp>

auto main(int argc, char * argv[]) -> int {
    common::system::init(argc, argv);

    LOGI("Binary Name: {}", common::config::get_binary_name());
    LOGI("Config File: {}", common::config::get_config_file());
    LOGI("Log File: {}", common::config::get_log_file());
    LOGI("Log Level: {}", common::config::get_log_level());
    LOGI("IP Address: {}", common::config::get_ip_address());
    LOGI("Port: {}", common::config::get_port());
    LOGI("Num Threads: {}", common::config::get_num_threads());

    common::system::shutdown();

    return 0;
}
