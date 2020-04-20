#ifndef LIBCOMMON_MACROS_INCLUDE_COMMON_MACROS_EXPECT_HPP
#define LIBCOMMON_MACROS_INCLUDE_COMMON_MACROS_EXPECT_HPP

#include "common_log.hpp"
#include <hedley.h>

#ifndef NDEBUG
#    define EXPECT_TRUE(condition)                                                                 \
        [&] {                                                                                      \
            if (! (condition)) {                                                                   \
                LOGW("Expected `" #condition "' to be true");                                      \
            }                                                                                      \
            return condition;                                                                      \
        }()

#    define EXPECT_FALSE(condition)                                                                \
        [&] {                                                                                      \
            if (condition) {                                                                       \
                LOGW("Expected `" #condition "' to be false");                                     \
            }                                                                                      \
            return condition;                                                                      \
        }()
#else
#    define EXPECT_TRUE(condition)  HEDLEY_LIKELY(condition)
#    define EXPECT_FALSE(condition) HEDLEY_UNLIKELY(condition)
#endif

#endif
