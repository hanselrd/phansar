#ifndef PHANSAR_CODEGEN_MACROS_HPP
#define PHANSAR_CODEGEN_MACROS_HPP

#include <hedley.h>

#if HEDLEY_HAS_ATTRIBUTE(annotate)
    #define PH_ANNOTATE(...) __attribute__((annotate(#__VA_ARGS__)))
#else
    #define PH_ANNOTATE(...)
#endif

#endif
