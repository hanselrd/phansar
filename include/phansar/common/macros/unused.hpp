#ifndef PHANSAR_COMMON_MACROS_UNUSED_HPP
#define PHANSAR_COMMON_MACROS_UNUSED_HPP

#include <phansar/common/log.hpp>

#ifndef NDEBUG
#    define UNUSED_ARG(arg)                                                                        \
        [&] {                                                                                      \
            LOGT("Unused argument `" #arg "'");                                                    \
            (void)(arg);                                                                           \
        }()
#else
#    define UNUSED_ARG(arg) ((void)(arg))
#endif

#endif
