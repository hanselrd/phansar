#ifndef LIBCOMMON_LOG_INCLUDE_PH_COMMON_LOG_HPP
#define LIBCOMMON_LOG_INCLUDE_PH_COMMON_LOG_HPP

#ifdef NDEBUG
#    define SPDLOG_ACTIVE_LEVEL SDPLOG_LEVEL_INFO
#else
#    define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <string>
#include <string_view>

/* #if defined(__FILE__) && defined(PH_SOURCE_PATH_SIZE) */
/* #    define __FILENAME__ (__FILE__ + PH_SOURCE_PATH_SIZE) */
/* #else */
/* #    define __FILENAME__ "unknown" */
/* #endif */

#define PH_LOG_LOGGER_CALL(logger, level, ...)                                                     \
    do {                                                                                           \
        if (logger->should_log(level) || logger->should_backtrace()) {                             \
            logger->log(                                                                           \
                spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__);      \
        }                                                                                          \
    } while (0)

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#    define PH_LOG_LOGGER_TRACE(logger, ...)                                                       \
        PH_LOG_LOGGER_CALL(logger, spdlog::level::trace, __VA_ARGS__)
#    define PH_LOG_TRACE(...) PH_LOG_LOGGER_TRACE(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_TRACE(logger, ...) (void)0
#    define PH_LOG_TRACE(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#    define PH_LOG_LOGGER_DEBUG(logger, ...)                                                       \
        PH_LOG_LOGGER_CALL(logger, spdlog::level::debug, __VA_ARGS__)
#    define PH_LOG_DEBUG(...) PH_LOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_DEBUG(logger, ...) (void)0
#    define PH_LOG_DEBUG(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#    define PH_LOG_LOGGER_INFO(logger, ...)                                                        \
        PH_LOG_LOGGER_CALL(logger, spdlog::level::info, __VA_ARGS__)
#    define PH_LOG_INFO(...) PH_LOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_INFO(logger, ...) (void)0
#    define PH_LOG_INFO(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#    define PH_LOG_LOGGER_WARN(logger, ...)                                                        \
        PH_LOG_LOGGER_CALL(logger, spdlog::level::warn, __VA_ARGS__)
#    define PH_LOG_WARN(...) PH_LOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_WARN(logger, ...) (void)0
#    define PH_LOG_WARN(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#    define PH_LOG_LOGGER_ERROR(logger, ...)                                                       \
        PH_LOG_LOGGER_CALL(logger, spdlog::level::err, __VA_ARGS__)
#    define PH_LOG_ERROR(...) PH_LOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_ERROR(logger, ...) (void)0
#    define PH_LOG_ERROR(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#    define PH_LOG_LOGGER_CRITICAL(logger, ...)                                                    \
        PH_LOG_LOGGER_CALL(logger, spdlog::level::critical, __VA_ARGS__)
#    define PH_LOG_CRITICAL(...) PH_LOG_LOGGER_CRITICAL(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_CRITICAL(logger, ...) (void)0
#    define PH_LOG_CRITICAL(...) (void)0
#endif

#define PH_LOGT PH_LOG_TRACE
#define PH_LOGD PH_LOG_DEBUG
#define PH_LOGI PH_LOG_INFO
#define PH_LOGW PH_LOG_WARN
#define PH_LOGE PH_LOG_ERROR
#define PH_LOGC PH_LOG_CRITICAL

#define PH_LOG_LOGGER_IF_CALL(logger, condition, level, ...)                                       \
    do {                                                                                           \
        if (condition) {                                                                           \
            PH_LOG_LOGGER_CALL(logger, level, __VA_ARGS__);                                        \
        }                                                                                          \
    } while (0)

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#    define PH_LOG_LOGGER_TRACE_IF(logger, condition, ...)                                         \
        PH_LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::trace, __VA_ARGS__)
#    define PH_LOG_TRACE_IF(condition, ...)                                                        \
        PH_LOG_LOGGER_TRACE_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_TRACE_IF(logger, condition, ...) (void)0
#    define PH_LOG_TRACE_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#    define PH_LOG_LOGGER_DEBUG_IF(logger, condition, ...)                                         \
        PH_LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::debug, __VA_ARGS__)
#    define PH_LOG_DEBUG_IF(condition, ...)                                                        \
        PH_LOG_LOGGER_DEBUG_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_DEBUG_IF(logger, condition, ...) (void)0
#    define PH_LOG_DEBUG_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#    define PH_LOG_LOGGER_INFO_IF(logger, condition, ...)                                          \
        PH_LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::info, __VA_ARGS__)
#    define PH_LOG_INFO_IF(condition, ...)                                                         \
        PH_LOG_LOGGER_INFO_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_INFO_IF(logger, condition, ...) (void)0
#    define PH_LOG_INFO_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#    define PH_LOG_LOGGER_WARN_IF(logger, condition, ...)                                          \
        PH_LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::warn, __VA_ARGS__)
#    define PH_LOG_WARN_IF(condition, ...)                                                         \
        PH_LOG_LOGGER_WARN_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_WARN_IF(logger, condition, ...) (void)0
#    define PH_LOG_WARN_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#    define PH_LOG_LOGGER_ERROR_IF(logger, condition, ...)                                         \
        PH_LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::err, __VA_ARGS__)
#    define PH_LOG_ERROR_IF(condition, ...)                                                        \
        PH_LOG_LOGGER_ERROR_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_ERROR_IF(logger, condition, ...) (void)0
#    define PH_LOG_ERROR_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#    define PH_LOG_LOGGER_CRITICAL_IF(logger, condition, ...)                                      \
        PH_LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::critical, __VA_ARGS__)
#    define PH_LOG_CRITICAL_IF(condition, ...)                                                     \
        PH_LOG_LOGGER_CRITICAL_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define PH_LOG_LOGGER_CRITICAL_IF(logger, condition, ...) (void)0
#    define PH_LOG_CRITICAL_IF(...) (void)0
#endif

#define PH_LOGT_IF PH_LOG_TRACE_IF
#define PH_LOGD_IF PH_LOG_DEBUG_IF
#define PH_LOGI_IF PH_LOG_INFO_IF
#define PH_LOGW_IF PH_LOG_WARN_IF
#define PH_LOGE_IF PH_LOG_ERROR_IF
#define PH_LOGC_IF PH_LOG_CRITICAL_IF

namespace ph::common::log {
void init(std::string_view filename);
}

#endif
