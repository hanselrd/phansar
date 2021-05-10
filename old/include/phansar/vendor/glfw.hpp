#ifndef PHANSAR_VENDOR_GLFW_HPP
#define PHANSAR_VENDOR_GLFW_HPP

#include <phansar/vendor/bgfx.hpp>
#include <phansar/vendor/hedley.hpp>

#ifdef HEDLEY_MSVC_VERSION
    #pragma warning(push, 0)
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#ifdef PH_VENDOR_GLFW_PRIVATE
    #if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        #define GLFW_EXPOSE_NATIVE_X11
        #define GLFW_EXPOSE_NATIVE_GLX
    #elif BX_PLATFORM_OSX
        #define GLFW_EXPOSE_NATIVE_COCOA
        #define GLFW_EXPOSE_NATIVE_NSGL
    #elif BX_PLATFORM_WINDOWS
        #define GLFW_EXPOSE_NATIVE_WIN32
        #define GLFW_EXPOSE_NATIVE_WGL
    #endif
    #include <GLFW/glfw3native.h>
#endif

#ifdef HEDLEY_MSVC_VERSION
    #pragma warning(pop)
#endif

#endif
