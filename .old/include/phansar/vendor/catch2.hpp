#ifndef PHANSAR_VENDOR_CATCH2_HPP
#define PHANSAR_VENDOR_CATCH2_HPP

#include <phansar/vendor/hedley.hpp>

#ifdef HEDLEY_MSVC_VERSION
    #pragma warning(push, 0)
#endif

#ifdef PH_VENDOR_CATCH2_PRIVATE
    #define CATCH_CONFIG_RUNNER
#endif
#include <catch2/catch.hpp>

#ifdef HEDLEY_MSVC_VERSION
    #pragma warning(pop)
#endif

#endif
