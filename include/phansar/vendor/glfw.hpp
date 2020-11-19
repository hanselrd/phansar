#ifndef PHANSAR_VENDOR_GLFW_HPP
#define PHANSAR_VENDOR_GLFW_HPP

#include <phansar/vendor/hedley.hpp>

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(push, 0)
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(pop)
#endif

#endif
