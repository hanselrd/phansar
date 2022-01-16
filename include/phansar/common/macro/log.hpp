#ifndef PHANSAR_COMMON_MACRO_LOG_HPP
#define PHANSAR_COMMON_MACRO_LOG_HPP

#include <phansar/common/logger.hpp>
#include <phansar/common/service_container.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

#ifdef __has_include
    #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
        #define PH_LOG(_level, ...)                                                                \
            do {                                                                                   \
                using namespace ::phansar::common;                                                 \
                if (g_service_container.contains<logger_service>()) {                              \
                    g_service_container.service<logger_service>()._level(                          \
                        fmt::format(__VA_ARGS__));                                                 \
                }                                                                                  \
            } while (false)
    #else
        #define PH_LOG(_level, ...)                                                                \
            do {                                                                                   \
                using namespace ::phansar::common;                                                 \
                if (g_service_container.contains<logger_service>()) {                              \
                    g_service_container.service<logger_service>()._level(                          \
                        fmt::format(__VA_ARGS__),                                                  \
                        spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION});                  \
                }                                                                                  \
            } while (false)
    #endif
#endif

#define PH_LOG_TRACE(...)    PH_LOG(trace, __VA_ARGS__)
#define PH_LOG_DEBUG(...)    PH_LOG(debug, __VA_ARGS__)
#define PH_LOG_INFO(...)     PH_LOG(info, __VA_ARGS__)
#define PH_LOG_WARNING(...)  PH_LOG(warning, __VA_ARGS__)
#define PH_LOG_ERROR(...)    PH_LOG(error, __VA_ARGS__)
#define PH_LOG_CRITICAL(...) PH_LOG(critical, __VA_ARGS__)

#define PH_LOG_IF(_level, _condition, ...)                                                         \
    do {                                                                                           \
        if (_condition) {                                                                          \
            PH_LOG(_level, __VA_ARGS__);                                                           \
        }                                                                                          \
    } while (false)

#define PH_LOG_TRACE_IF(_condition, ...)    PH_LOG_IF(trace, _condition, __VA_ARGS__)
#define PH_LOG_DEBUG_IF(_condition, ...)    PH_LOG_IF(debug, _condition, __VA_ARGS__)
#define PH_LOG_INFO_IF(_condition, ...)     PH_LOG_IF(info, _condition, __VA_ARGS__)
#define PH_LOG_WARNING_IF(_condition, ...)  PH_LOG_IF(warning, _condition, __VA_ARGS__)
#define PH_LOG_ERROR_IF(_condition, ...)    PH_LOG_IF(error, _condition, __VA_ARGS__)
#define PH_LOG_CRITICAL_IF(_condition, ...) PH_LOG_IF(critical, _condition, __VA_ARGS__)

#endif
