#ifndef PHANSAR_COMMON_MACRO_UNIMPLEMENTED_HPP
#define PHANSAR_COMMON_MACRO_UNIMPLEMENTED_HPP

#include <phansar/common/macro/log.hpp>
#include <phansar/common/macro/overload.hpp>

#define PH_UNIMPLEMENTED_FREESTANDING_0()     return
#define PH_UNIMPLEMENTED_FREESTANDING_1(_arg) return (_arg)

#define PH_UNIMPLEMENTED_FREESTANDING(...) PH_OVERLOAD(PH_UNIMPLEMENTED_FREESTANDING, __VA_ARGS__)

#ifdef PH_BUILD_DEBUG
    #define PH_UNIMPLEMENTED_0()                                                                   \
        do {                                                                                       \
            PH_LOG_WARNING("Unimplemented `{}'", __FUNCTION__);                                    \
            return;                                                                                \
        } while (false)
    #define PH_UNIMPLEMENTED_1(_arg)                                                               \
        do {                                                                                       \
            PH_LOG_WARNING("Unimplemented `{}'", __FUNCTION__);                                    \
            return (_arg);                                                                         \
        } while (false)
#else
    #define PH_UNIMPLEMENTED_0()     return
    #define PH_UNIMPLEMENTED_1(_arg) return (_arg)
#endif

#define PH_UNIMPLEMENTED(...) PH_OVERLOAD(PH_UNIMPLEMENTED, __VA_ARGS__)

#endif
