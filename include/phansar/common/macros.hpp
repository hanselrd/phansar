#ifndef PHANSAR_COMMON_MACROS_HPP
#define PHANSAR_COMMON_MACROS_HPP

#include <phansar/common/log.hpp>

#include <phansar/vendor/fmt.hpp>

#include <cstdlib>
#include <stdexcept>

#define LOG(_level, ...)                                                                           \
    do {                                                                                           \
        if (phansar::common::log::instance() != nullptr) {                                         \
            phansar::common::log::instance()->print(phansar::common::log::level::_level,           \
                                                    __FILE__,                                      \
                                                    __LINE__,                                      \
                                                    __VA_ARGS__);                                  \
        }                                                                                          \
    } while (false)

#define LOG_TRACE(...)    LOG(trace, __VA_ARGS__)
#define LOG_DEBUG(...)    LOG(debug, __VA_ARGS__)
#define LOG_INFO(...)     LOG(info, __VA_ARGS__)
#define LOG_WARNING(...)  LOG(warning, __VA_ARGS__)
#define LOG_ERROR(...)    LOG(error, __VA_ARGS__)
#define LOG_CRITICAL(...) LOG(critical, __VA_ARGS__)

#define LOG_IF(_level, _condition, ...)                                                            \
    do {                                                                                           \
        if (_condition) {                                                                          \
            LOG(_level, __VA_ARGS__);                                                              \
        }                                                                                          \
    } while (false)

#define LOG_TRACE_IF(_condition, ...)    LOG_IF(trace, _condition, __VA_ARGS__)
#define LOG_DEBUG_IF(_condition, ...)    LOG_IF(debug, _condition, __VA_ARGS__)
#define LOG_INFO_IF(_condition, ...)     LOG_IF(info, _condition, __VA_ARGS__)
#define LOG_WARNING_IF(_condition, ...)  LOG_IF(warning, _condition, __VA_ARGS__)
#define LOG_ERROR_IF(_condition, ...)    LOG_IF(error, _condition, __VA_ARGS__)
#define LOG_CRITICAL_IF(_condition, ...) LOG_IF(critical, _condition, __VA_ARGS__)

#ifndef NDEBUG
#    define TERMINATE(_message) std::terminate()
#else
#    define TERMINATE(_message) throw std::runtime_error(_message)
#endif

#define ASSERT_ALWAYS(_condition, ...)                                                             \
    do {                                                                                           \
        if (! (_condition)) {                                                                      \
            LOG_CRITICAL("Assertion `" #_condition "' failed: {}", fmt::format(__VA_ARGS__));      \
            TERMINATE(fmt::format(__VA_ARGS__));                                                   \
        }                                                                                          \
    } while (false)

#define ASSERT_ALWAYS_IF(_enable, _condition, ...)                                                 \
    do {                                                                                           \
        if (_enable) {                                                                             \
            ASSERT_ALWAYS(_condition, __VA_ARGS__);                                                \
        }                                                                                          \
    } while (false)

#ifndef NDEBUG
#    define ASSERT(_condition, ...)             ASSERT_ALWAYS(_condition, __VA_ARGS__)
#    define ASSERT_IF(_enable, _condition, ...) ASSERT_ALWAYS_IF(_enable, _condition, __VA_ARGS__)
#else
#    define ASSERT(...)    (void)0
#    define ASSERT_IF(...) (void)0
#endif

#ifndef NDEBUG
#    define UNUSED_ARG(_arg)                                                                       \
        do {                                                                                       \
            LOG_TRACE("Unused argument `" #_arg "'");                                              \
            (void)(_arg);                                                                          \
        } while (false)
#else
#    define UNUSED_ARG(_arg) (void)_arg
#endif

#endif
