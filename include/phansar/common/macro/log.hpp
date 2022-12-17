#ifndef PHANSAR_COMMON_MACRO_LOG_HPP
#define PHANSAR_COMMON_MACRO_LOG_HPP

#include <phansar/common/service/logger_service.hpp>
#include <phansar/common/service_container.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <hedley.h>

#ifdef __has_include
  #if __has_include(<source_location>) && defined(__cpp_lib_source_location)
    #define PH_LOG(_level, ...)                                                \
      do {                                                                     \
        using namespace ::phansar::common;                                     \
        if (HEDLEY_LIKELY(                                                     \
                g_service_container.contains<service::logger_service>())) {    \
          g_service_container.service<service::logger_service>().smart_log(    \
              spdlog::level::_level, fmt::format(__VA_ARGS__));                \
        }                                                                      \
      } while (false)
  #else
    #define PH_LOG(_level, ...)                                                \
      do {                                                                     \
        using namespace ::phansar::common;                                     \
        if (HEDLEY_LIKELY(                                                     \
                g_service_container.contains<service::logger_service>())) {    \
          g_service_container.service<service::logger_service>().log(          \
              spdlog::level::_level,                                           \
              fmt::format(__VA_ARGS__),                                        \
              spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION});        \
        }                                                                      \
      } while (false)
  #endif
#endif

#define PH_LOG_TRACE(...)    PH_LOG(trace, __VA_ARGS__)
#define PH_LOG_DEBUG(...)    PH_LOG(debug, __VA_ARGS__)
#define PH_LOG_INFO(...)     PH_LOG(info, __VA_ARGS__)
#define PH_LOG_WARNING(...)  PH_LOG(warn, __VA_ARGS__)
#define PH_LOG_ERROR(...)    PH_LOG(err, __VA_ARGS__)
#define PH_LOG_CRITICAL(...) PH_LOG(critical, __VA_ARGS__)

#define PH_LOG_IF(_level, _condition, ...)                                     \
  do {                                                                         \
    if (_condition) {                                                          \
      PH_LOG(_level, __VA_ARGS__);                                             \
    }                                                                          \
  } while (false)

#define PH_LOG_TRACE_IF(_condition, ...)                                       \
  PH_LOG_IF(trace, _condition, __VA_ARGS__)
#define PH_LOG_DEBUG_IF(_condition, ...)                                       \
  PH_LOG_IF(debug, _condition, __VA_ARGS__)
#define PH_LOG_INFO_IF(_condition, ...) PH_LOG_IF(info, _condition, __VA_ARGS__)
#define PH_LOG_WARNING_IF(_condition, ...)                                     \
  PH_LOG_IF(warn, _condition, __VA_ARGS__)
#define PH_LOG_ERROR_IF(_condition, ...) PH_LOG_IF(err, _condition, __VA_ARGS__)
#define PH_LOG_CRITICAL_IF(_condition, ...)                                    \
  PH_LOG_IF(critical, _condition, __VA_ARGS__)

#define PH_LOG_INDENTED(_level, _indent, ...)                                  \
  PH_LOG(_level,                                                               \
         "{:{}}" __VA_OPT__("{}"),                                             \
         "",                                                                   \
         _indent __VA_OPT__(, fmt::format(__VA_ARGS__)))

#define PH_LOG_INDENTED_TRACE(_indent, ...)                                    \
  PH_LOG_INDENTED(trace, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_DEBUG(_indent, ...)                                    \
  PH_LOG_INDENTED(debug, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_INFO(_indent, ...)                                     \
  PH_LOG_INDENTED(info, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_WARNING(_indent, ...)                                  \
  PH_LOG_INDENTED(warn, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_ERROR(_indent, ...)                                    \
  PH_LOG_INDENTED(err, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_CRITICAL(_indent, ...)                                 \
  PH_LOG_INDENTED(critical, _indent, __VA_ARGS__)

#define PH_LOG_INDENTED_IF(_level, _condition, _indent, ...)                   \
  do {                                                                         \
    if (_condition) {                                                          \
      PH_LOG_INDENTED(_level, _indent, __VA_ARGS__);                           \
    }                                                                          \
  } while (false)

#define PH_LOG_INDENTED_TRACE_IF(_condition, _indent, ...)                     \
  PH_LOG_INDENTED_IF(trace, _condition, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_DEBUG_IF(_condition, _indent, ...)                     \
  PH_LOG_INDENTED_IF(debug, _condition, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_INFO_IF(_condition, _indent, ...)                      \
  PH_LOG_INDENTED_IF(info, _condition, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_WARNING_IF(_condition, _indent, ...)                   \
  PH_LOG_INDENTED_IF(warn, _condition, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_ERROR_IF(_condition, _indent, ...)                     \
  PH_LOG_INDENTED_IF(err, _condition, _indent, __VA_ARGS__)
#define PH_LOG_INDENTED_CRITICAL_IF(_condition, _indent, ...)                  \
  PH_LOG_INDENTED_IF(critical, _condition, _indent, __VA_ARGS__)

#endif
