#include <phansar/common/logger.hpp>

#include <catch2/catch.hpp>

#include <thread>

SCENARIO("common::logger", "[common][logger]") {
    auto logger = phansar::common::logger{"unittest", "logs/unittest.log", 1024 * 1024 * 5, 3};

    SPDLOG_LOGGER_TRACE(logger.log(), "trace");
    SPDLOG_LOGGER_DEBUG(logger.log(), "debug");
    SPDLOG_LOGGER_INFO(logger.log(), "info");
    SPDLOG_LOGGER_WARN(logger.log(), "warn");
    SPDLOG_LOGGER_ERROR(logger.log(), "error");
    SPDLOG_LOGGER_CRITICAL(logger.log(), "critical");

    auto threads = std::vector<std::jthread>{};
    for (auto i = std::size_t{0}; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&logger]() {
            SPDLOG_LOGGER_TRACE(logger.log(), "trace");
            SPDLOG_LOGGER_DEBUG(logger.log(), "debug");
            SPDLOG_LOGGER_INFO(logger.log(), "info");
            SPDLOG_LOGGER_WARN(logger.log(), "warn");
            SPDLOG_LOGGER_ERROR(logger.log(), "error");
            SPDLOG_LOGGER_CRITICAL(logger.log(), "critical");
        });
    }
}
