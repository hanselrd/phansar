#ifndef LIBCOMMON_MACROS_INCLUDE_COMMON_MACROS_ASSERT_HPP
#define LIBCOMMON_MACROS_INCLUDE_COMMON_MACROS_ASSERT_HPP

#include "common_log.hpp"
#include <cstdlib>
#include <stdexcept>

#ifndef NDEBUG
#    define TERMINATE(message) std::terminate()
#else
#    define TERMINATE(message) throw std::runtime_error(message)
#endif

#define MASSERT_ALWAYS(condition, message)                                                         \
    [&] {                                                                                          \
        if (! (condition)) {                                                                       \
            LOGC("Assertion `" #condition "' failed [{}]", message);                               \
            TERMINATE(message);                                                                    \
        }                                                                                          \
    }()

#define MASSERT_ALWAYS_IF(enable, condition, message)                                              \
    [&] {                                                                                          \
        if (enable) {                                                                              \
            MASSERT_ALWAYS(condition, message);                                                    \
        }                                                                                          \
    }()

#define ASSERT_ALWAYS(condition)                                                                   \
    [&] {                                                                                          \
        if (! (condition)) {                                                                       \
            LOGC("Assertion `" #condition "' failed");                                             \
            TERMINATE("");                                                                         \
        }                                                                                          \
    }()

#define ASSERT_ALWAYS_IF(enable, condition)                                                        \
    [&] {                                                                                          \
        if (enable) {                                                                              \
            ASSERT_ALWAYS(condition);                                                              \
        }                                                                                          \
    }()

#ifndef NDEBUG
#    define MASSERT(condition, message)            MASSERT_ALWAYS(condition, message)
#    define MASSERT_IF(enable, condition, message) MASSERT_ALWAYS_IF(enable, condition, message)
#    define ASSERT(condition)                      ASSERT_ALWAYS(condition)
#    define ASSERT_IF(enable, condition)           ASSERT_ALWAYS_IF(enable, condition)
#else
#    define MASSERT(ignore1, ignore2)             ((void)0)
#    define MASSERT_IF(ignore1, ignore2, ignore3) ((void)0)
#    define ASSERT(ignore1)                       ((void)0)
#    define ASSERT_IF(ignore1, ignore2)           ((void)0)
#endif

#endif
