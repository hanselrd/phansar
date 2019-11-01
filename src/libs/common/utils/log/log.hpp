/**
 * This file is part of Phansar.
 *
 * Copyright (C) 2018  Hansel De La Cruz
 *
 * Phansar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phansar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_UTILS_LOG_HPP
#define COMMON_UTILS_LOG_HPP

#ifdef NDEBUG
#    define SPDLOG_ACTIVE_LEVEL SDPLOG_LEVEL_INFO
#else
#    define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif
#include <spdlog/spdlog.h>
#include <string>
#include <string_view>

#if defined(__FILE__) && defined(__SOURCE_PATH_SIZE__)
#    define __FILENAME__ (__FILE__ + __SOURCE_PATH_SIZE__)
#else
#    define __FILENAME__ "unknown"
#endif

#define LOG_LOGGER_CALL(logger, level, ...)                                                        \
    do {                                                                                           \
        if (logger->should_log(level) || logger->should_backtrace()) {                             \
            logger->log(                                                                           \
                spdlog::source_loc{__FILENAME__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__);  \
        }                                                                                          \
    } while (0)

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#    define LOG_LOGGER_TRACE(logger, ...) LOG_LOGGER_CALL(logger, spdlog::level::trace, __VA_ARGS__)
#    define LOG_TRACE(...) LOG_LOGGER_TRACE(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define LOG_LOGGER_TRACE(logger, ...) (void)0
#    define LOG_TRACE(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#    define LOG_LOGGER_DEBUG(logger, ...) LOG_LOGGER_CALL(logger, spdlog::level::debug, __VA_ARGS__)
#    define LOG_DEBUG(...) LOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define LOG_LOGGER_DEBUG(logger, ...) (void)0
#    define LOG_DEBUG(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#    define LOG_LOGGER_INFO(logger, ...) LOG_LOGGER_CALL(logger, spdlog::level::info, __VA_ARGS__)
#    define LOG_INFO(...) LOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define LOG_LOGGER_INFO(logger, ...) (void)0
#    define LOG_INFO(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#    define LOG_LOGGER_WARN(logger, ...) LOG_LOGGER_CALL(logger, spdlog::level::warn, __VA_ARGS__)
#    define LOG_WARN(...) LOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define LOG_LOGGER_WARN(logger, ...) (void)0
#    define LOG_WARN(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#    define LOG_LOGGER_ERROR(logger, ...) LOG_LOGGER_CALL(logger, spdlog::level::err, __VA_ARGS__)
#    define LOG_ERROR(...) LOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define LOG_LOGGER_ERROR(logger, ...) (void)0
#    define LOG_ERROR(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#    define LOG_LOGGER_CRITICAL(logger, ...)                                                       \
        LOG_LOGGER_CALL(logger, spdlog::level::critical, __VA_ARGS__)
#    define LOG_CRITICAL(...) LOG_LOGGER_CRITICAL(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#    define LOG_LOGGER_CRITICAL(logger, ...) (void)0
#    define LOG_CRITICAL(...) (void)0
#endif

#define LOGT LOG_TRACE
#define LOGD LOG_DEBUG
#define LOGI LOG_INFO
#define LOGW LOG_WARN
#define LOGE LOG_ERROR
#define LOGC LOG_CRITICAL

#define LOG_LOGGER_IF_CALL(logger, condition, level, ...)                                          \
    do {                                                                                           \
        if (condition) {                                                                           \
            LOG_LOGGER_CALL(logger, level, __VA_ARGS__);                                           \
        }                                                                                          \
    } while (0)

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#    define LOG_LOGGER_TRACE_IF(logger, condition, ...)                                            \
        LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::trace, __VA_ARGS__)
#    define LOG_TRACE_IF(condition, ...)                                                           \
        LOG_LOGGER_TRACE_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define LOG_LOGGER_TRACE_IF(logger, condition, ...) (void)0
#    define LOG_TRACE_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#    define LOG_LOGGER_DEBUG_IF(logger, condition, ...)                                            \
        LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::debug, __VA_ARGS__)
#    define LOG_DEBUG_IF(condition, ...)                                                           \
        LOG_LOGGER_DEBUG_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define LOG_LOGGER_DEBUG_IF(logger, condition, ...) (void)0
#    define LOG_DEBUG_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#    define LOG_LOGGER_INFO_IF(logger, condition, ...)                                             \
        LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::info, __VA_ARGS__)
#    define LOG_INFO_IF(condition, ...)                                                            \
        LOG_LOGGER_INFO_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define LOG_LOGGER_INFO_IF(logger, condition, ...) (void)0
#    define LOG_INFO_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#    define LOG_LOGGER_WARN_IF(logger, condition, ...)                                             \
        LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::warn, __VA_ARGS__)
#    define LOG_WARN_IF(condition, ...)                                                            \
        LOG_LOGGER_WARN_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define LOG_LOGGER_WARN_IF(logger, condition, ...) (void)0
#    define LOG_WARN_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#    define LOG_LOGGER_ERROR_IF(logger, condition, ...)                                            \
        LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::err, __VA_ARGS__)
#    define LOG_ERROR_IF(condition, ...)                                                           \
        LOG_LOGGER_ERROR_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define LOG_LOGGER_ERROR_IF(logger, condition, ...) (void)0
#    define LOG_ERROR_IF(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#    define LOG_LOGGER_CRITICAL_IF(logger, condition, ...)                                         \
        LOG_LOGGER_IF_CALL(logger, condition, spdlog::level::critical, __VA_ARGS__)
#    define LOG_CRITICAL_IF(condition, ...)                                                        \
        LOG_LOGGER_CRITICAL_IF(spdlog::default_logger_raw(), condition, __VA_ARGS__)
#else
#    define LOG_LOGGER_CRITICAL_IF(logger, condition, ...) (void)0
#    define LOG_CRITICAL_IF(...) (void)0
#endif

#define LOGT_IF LOG_TRACE_IF
#define LOGD_IF LOG_DEBUG_IF
#define LOGI_IF LOG_INFO_IF
#define LOGW_IF LOG_WARN_IF
#define LOGE_IF LOG_ERROR_IF
#define LOGC_IF LOG_CRITICAL_IF

namespace common {
namespace utils {
namespace log {
void init(std::string_view filename);
} // namespace log
} // namespace utils
} // namespace common

#endif
