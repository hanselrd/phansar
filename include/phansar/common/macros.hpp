#ifndef PHANSAR_COMMON_MACROS_HPP
#define PHANSAR_COMMON_MACROS_HPP

#include <phansar/common/log.hpp>
#include <phansar/vendor/hedley.hpp>

#if HEDLEY_HAS_ATTRIBUTE(annotate)
#    define PH_ANNOTATE(...) __attribute__((annotate(#    __VA_ARGS__)))
#else
#    define PH_ANNOTATE(...)
#endif

#define PH_METADATA(...) PH_ANNOTATE(phansar, metadata, __VA_ARGS__)

#define PH_LOG(_level, ...)                                                                        \
    do {                                                                                           \
        if (::phansar::common::log::instance() != nullptr) {                                       \
            ::phansar::common::log::instance()->print(::phansar::common::log::level::_level,       \
                                                      __FILE__,                                    \
                                                      __LINE__,                                    \
                                                      __VA_ARGS__);                                \
        }                                                                                          \
    } while (false)

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

#ifndef HEDLEY_MSVC_VERSION
#    define PH_ASSERT_ALWAYS(_condition, ...)                                                      \
        do {                                                                                       \
            if (HEDLEY_UNLIKELY(! (_condition))) {                                                 \
                PH_LOG_CRITICAL("Assertion `" #_condition                                          \
                                "' failed" __VA_OPT__(": {}", fmt::format(__VA_ARGS__)));          \
                std::terminate();                                                                  \
            }                                                                                      \
        } while (false)
#else
#    define PH_ASSERT_ALWAYS(_condition, ...)                                                      \
        do {                                                                                       \
            if (HEDLEY_UNLIKELY(! (_condition))) {                                                 \
                PH_LOG_CRITICAL("Assertion `" #_condition "' failed");                             \
                std::terminate();                                                                  \
            }                                                                                      \
        } while (false)
#endif

#define PH_ASSERT_ALWAYS_IF(_enable, _condition, ...)                                              \
    do {                                                                                           \
        if (_enable) {                                                                             \
            PH_ASSERT_ALWAYS(_condition, __VA_ARGS__);                                             \
        }                                                                                          \
    } while (false)

#ifdef PH_BUILD_DEBUG
#    define PH_ASSERT(_condition, ...) PH_ASSERT_ALWAYS(_condition, __VA_ARGS__)
#    define PH_ASSERT_IF(_enable, _condition, ...)                                                 \
        PH_ASSERT_ALWAYS_IF(_enable, _condition, __VA_ARGS__)
#else
#    define PH_ASSERT(...)    (void)0
#    define PH_ASSERT_IF(...) (void)0
#endif

#ifdef PH_BUILD_DEBUG
#    define PH_UNUSED(_arg)                                                                        \
        do {                                                                                       \
            PH_LOG_TRACE("Unused argument `" #_arg "'");                                           \
            (void)(_arg);                                                                          \
        } while (false)
#else
#    define PH_UNUSED(_arg) (void)_arg
#endif

#endif
