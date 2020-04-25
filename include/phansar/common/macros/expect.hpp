#ifndef PHANSAR_COMMON_MACROS_EXPECT_HPP
#define PHANSAR_COMMON_MACROS_EXPECT_HPP

#include <phansar/common/log.hpp>

#include <phansar/vendor/hedley.hpp>

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
