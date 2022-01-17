#ifndef PHANSAR_VENDOR_RTTR_HPP
#define PHANSAR_VENDOR_RTTR_HPP

#include <phansar/vendor/hedley.hpp>

#ifdef HEDLEY_MSVC_VERSION
    #pragma warning(push, 0)
#endif

#include <rttr/type>
#include <rttr/visitor.h>
#ifdef PH_VENDOR_RTTR_PRIVATE
    #include <rttr/registration>
#endif

#ifdef HEDLEY_MSVC_VERSION
    #pragma warning(pop)
#endif

#endif
