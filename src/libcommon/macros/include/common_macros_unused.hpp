#ifndef LIBCOMMON_MACROS_INCLUDE_COMMON_MACROS_UNUSED_HPP
#define LIBCOMMON_MACROS_INCLUDE_COMMON_MACROS_UNUSED_HPP

#include "common_log.hpp"

#ifndef NDEBUG
#    define UNUSED_ARG(arg)                                                                        \
        [&] {                                                                                      \
            LOGT("Unused argument `" #arg "'");                                                    \
            (void)(arg);                                                                           \
        }()
#else
#    define UNUSED_ARG(arg) ((void)arg)
#endif

#endif
