#ifndef PHANSAR_COMMON_MACRO_UNUSED_HPP
#define PHANSAR_COMMON_MACRO_UNUSED_HPP

#include <phansar/common/macro/log.hpp>

#define PH_UNUSED_FREESTANDING(_arg) (void)(_arg)

#ifdef PH_BUILD_DEBUG
  #define PH_UNUSED(_arg)                                                      \
    do {                                                                       \
      PH_LOG_WARNING("Unused argument `" #_arg "'");                           \
      (void)(_arg);                                                            \
    } while (false)
#else
  #define PH_UNUSED(_arg) (void)(_arg)
#endif

#endif
