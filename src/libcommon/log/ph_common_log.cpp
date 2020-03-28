#include "ph_common_log.hpp"
#include <cstdlib>
#include <plibsys.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace ph::common::log {
void init(std::string_view filename) {
    if (filename.empty()) {
        return;
    }

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e %z] [%t] [%^%l%$] [%s:%#] %v");
    console_sink->set_level(
#ifdef NDEBUG
        spdlog::level::info
#else
        spdlog::level::debug
#endif
    );

    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        std::string{filename}, 1048576 * 5, 3);
    rotating_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e %z] [%t] [%^%l%$] [%s:%#] %v");
    rotating_sink->set_level(
#ifdef NDEBUG
        spdlog::level::info
#else
        spdlog::level::debug
#endif
    );

    auto logger = std::make_shared<spdlog::logger>(
        spdlog::logger{"multi_sink", {console_sink, rotating_sink}});
    logger->set_level(spdlog::level::trace);
    spdlog::set_default_logger(logger);

    PH_LOGI("");
    PH_LOGD("Logger initialized");
    PH_LOGD("  log file: {}", filename);
    PH_LOGI("CPU count: {}", 0);
    PH_LOGI("CPU cache line size: {}", 0);
    PH_LOGI("CPU endianness: {}", "unknown");
    PH_LOGI("Platform: {}", "unknown");
    PH_LOGI("System RAM: {}", "unknown");
    auto build_type =
#ifdef NDEBUG
        "release"
#else
        "debug"
#endif
        ;
    PH_LOGI("Build type: {}", build_type);

    std::atexit([] {
        PH_LOGD("Logger shutdown");
        PH_LOGI("");
    });
}
} // namespace ph::common::log
