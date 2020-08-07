#ifndef PHANSAR_COMMON_LOG_HPP
#define PHANSAR_COMMON_LOG_HPP

#include <phansar/vendor/fmt.hpp>

#include <string_view>

#define __FILENAME__ (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOGT(...)                                                                                  \
    phansar::common::log::detail::print(__FILENAME__,                                              \
                                        __LINE__,                                                  \
                                        phansar::common::log::level::trace,                        \
                                        __VA_ARGS__)
#define LOGD(...)                                                                                  \
    phansar::common::log::detail::print(__FILENAME__,                                              \
                                        __LINE__,                                                  \
                                        phansar::common::log::level::debug,                        \
                                        __VA_ARGS__)
#define LOGI(...)                                                                                  \
    phansar::common::log::detail::print(__FILENAME__,                                              \
                                        __LINE__,                                                  \
                                        phansar::common::log::level::info,                         \
                                        __VA_ARGS__)
#define LOGW(...)                                                                                  \
    phansar::common::log::detail::print(__FILENAME__,                                              \
                                        __LINE__,                                                  \
                                        phansar::common::log::level::warning,                      \
                                        __VA_ARGS__)
#define LOGE(...)                                                                                  \
    phansar::common::log::detail::print(__FILENAME__,                                              \
                                        __LINE__,                                                  \
                                        phansar::common::log::level::error,                        \
                                        __VA_ARGS__)
#define LOGC(...)                                                                                  \
    phansar::common::log::detail::print(__FILENAME__,                                              \
                                        __LINE__,                                                  \
                                        phansar::common::log::level::critical,                     \
                                        __VA_ARGS__)
#define LOGT_IF(condition, ...)                                                                    \
    do {                                                                                           \
        if (condition) {                                                                           \
            LOGT(__VA_ARGS__);                                                                     \
        }                                                                                          \
    } while (0)
#define LOGD_IF(condition, ...)                                                                    \
    do {                                                                                           \
        if (condition) {                                                                           \
            LOGD(__VA_ARGS__);                                                                     \
        }                                                                                          \
    } while (0)
#define LOGI_IF(condition, ...)                                                                    \
    do {                                                                                           \
        if (condition) {                                                                           \
            LOGI(__VA_ARGS__);                                                                     \
        }                                                                                          \
    } while (0)
#define LOGW_IF(condition, ...)                                                                    \
    do {                                                                                           \
        if (condition) {                                                                           \
            LOGW(__VA_ARGS__);                                                                     \
        }                                                                                          \
    } while (0)
#define LOGE_IF(condition, ...)                                                                    \
    do {                                                                                           \
        if (condition) {                                                                           \
            LOGE(__VA_ARGS__);                                                                     \
        }                                                                                          \
    } while (0)
#define LOGC_IF(condition, ...)                                                                    \
    do {                                                                                           \
        if (condition) {                                                                           \
            LOGC(__VA_ARGS__);                                                                     \
        }                                                                                          \
    } while (0)

namespace phansar::common::log {
enum class level { trace, debug, info, warning, error, critical, off };

namespace detail {
void vprint(std::string_view file,
            int              line,
            level            level,
            std::string_view format,
            fmt::format_args args);
template <class... Args>
void print(std::string_view file, int line, level level, std::string_view format, Args &&... args);
} // namespace detail

void init(std::string_view file_name, level level, std::string_view binary_name);
void set_thread_name(std::string_view name);
} // namespace phansar::common::log

#include <phansar/common/detail/log.tpp>

#endif
