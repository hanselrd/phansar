#ifndef LIBCOMMON_CONFIG_INCLUDE_COMMON_CONFIG_HPP
#define LIBCOMMON_CONFIG_INCLUDE_COMMON_CONFIG_HPP

#include <cstddef>
#include <cstdint>
#include <spdlog/common.h>
#include <string>

namespace common::config {
void init(int argc, const char * const * argv);
auto get_binary_name() -> std::string;
auto get_config_file() -> std::string;
auto get_log_file() -> std::string;
auto get_log_level() -> spdlog::level::level_enum;
auto get_ip_address() -> std::string;
auto get_port() -> std::uint16_t;
auto get_num_threads() -> std::size_t;
} // namespace common::config

#endif
