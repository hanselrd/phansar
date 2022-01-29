#include <phansar/common/logger.hpp>
#include <catch2/catch.hpp>
#include <thread>

TEST_CASE("common::logger", "[common][logger]") {
    auto logger = phansar::common::logger{"unittest",
                                          "logs/unittest.log",
                                          static_cast<std::size_t>(1024 * 1024 * 5),
                                          3};

#ifdef __has_include
    #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
    logger.smart_log(spdlog::level::trace, "trace");
    logger.smart_log(spdlog::level::debug, "debug");
    logger.smart_log(spdlog::level::info, "info");
    logger.smart_log(spdlog::level::warn, "warning");
    logger.smart_log(spdlog::level::err, "error");
    logger.smart_log(spdlog::level::critical, "critical");
    #endif
#endif

    logger.log(spdlog::level::trace, "trace", spdlog::source_loc{"<none>", 1, ""});
    logger.log(spdlog::level::debug, "debug", spdlog::source_loc{"<none>", 1, ""});
    logger.log(spdlog::level::info, "info", spdlog::source_loc{"<none>", 1, ""});
    logger.log(spdlog::level::warn, "warning", spdlog::source_loc{"<none>", 1, ""});
    logger.log(spdlog::level::err, "error", spdlog::source_loc{"<none>", 1, ""});
    logger.log(spdlog::level::critical, "critical", spdlog::source_loc{"<none>", 1, ""});

    auto threads = std::vector<std::jthread>{};
    for (auto i = std::size_t{0}; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&logger]() {
#ifdef __has_include
    #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
            logger.smart_log(spdlog::level::trace, "trace");
            logger.smart_log(spdlog::level::debug, "debug");
            logger.smart_log(spdlog::level::info, "info");
            logger.smart_log(spdlog::level::warn, "warning");
            logger.smart_log(spdlog::level::err, "error");
            logger.smart_log(spdlog::level::critical, "critical");
    #endif
#endif

            logger.log(spdlog::level::trace, "trace", spdlog::source_loc{"<none>", 1, ""});
            logger.log(spdlog::level::debug, "debug", spdlog::source_loc{"<none>", 1, ""});
            logger.log(spdlog::level::info, "info", spdlog::source_loc{"<none>", 1, ""});
            logger.log(spdlog::level::warn, "warning", spdlog::source_loc{"<none>", 1, ""});
            logger.log(spdlog::level::err, "error", spdlog::source_loc{"<none>", 1, ""});
            logger.log(spdlog::level::critical, "critical", spdlog::source_loc{"<none>", 1, ""});
        });
    }
}
