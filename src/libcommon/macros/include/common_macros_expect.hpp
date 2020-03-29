#ifndef LIBCOMMON_MACROS_INCLUDE_COMMON_MACROS_EXPECT_HPP
#define LIBCOMMON_MACROS_INCLUDE_COMMON_MACROS_EXPECT_HPP

#include "common_log.hpp"
#include <plibsys.h>

#ifndef NDEBUG
#    define EXPECT_TRUE(condition)                                                                 \
        [&] {                                                                                      \
            if (!(condition)) {                                                                    \
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
#    define EXPECT_TRUE(condition) P_LIKELY(condition)
#    define EXPECT_FALSE(condition) P_UNLIKELY(condition)
#endif

#endif
