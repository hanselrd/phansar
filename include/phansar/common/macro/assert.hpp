#ifndef PHANSAR_COMMON_MACRO_ASSERT_HPP
#define PHANSAR_COMMON_MACRO_ASSERT_HPP

#include <phansar/common/macro/log.hpp>
#include <hedley.h>
#include <exception>

#define PH_ASSERT_ALWAYS_FREESTANDING(_condition)                              \
  do {                                                                         \
    if (HEDLEY_UNLIKELY(! (_condition))) {                                     \
      std::terminate();                                                        \
    }                                                                          \
  } while (false)

#define PH_ASSERT_ALWAYS_IF_FREESTANDING(_enable, _condition)                  \
  do {                                                                         \
    if (_enable) {                                                             \
      PH_ASSERT_ALWAYS_FREESTANDING(_condition);                               \
    }                                                                          \
  } while (false)

#ifdef PH_BUILD_DEBUG
  #define PH_ASSERT_FREESTANDING(_condition)                                   \
    PH_ASSERT_ALWAYS_FREESTANDING(_condition)
  #define PH_ASSERT_IF_FREESTANDING(_enable, _condition)                       \
    PH_ASSERT_ALWAYS_IF_FREESTANDING(_enable, _condition)
#else
  #define PH_ASSERT_FREESTANDING(_condition)             (void)0
  #define PH_ASSERT_IF_FREESTANDING(_enable, _condition) (void)0
#endif

#define PH_ASSERT_ALWAYS(_condition)                                           \
  do {                                                                         \
    if (HEDLEY_UNLIKELY(! (_condition))) {                                     \
      PH_LOG_CRITICAL("Assertion `" #_condition "' failed");                   \
      std::terminate();                                                        \
    }                                                                          \
  } while (false)

#define PH_ASSERT_ALWAYS_IF(_enable, _condition)                               \
  do {                                                                         \
    if (_enable) {                                                             \
      PH_ASSERT_ALWAYS(_condition);                                            \
    }                                                                          \
  } while (false)

#ifdef PH_BUILD_DEBUG
  #define PH_ASSERT(_condition) PH_ASSERT_ALWAYS(_condition)
  #define PH_ASSERT_IF(_enable, _condition)                                    \
    PH_ASSERT_ALWAYS_IF(_enable, _condition)
#else
  #define PH_ASSERT(_condition)             (void)0
  #define PH_ASSERT_IF(_enable, _condition) (void)0
#endif

#endif
