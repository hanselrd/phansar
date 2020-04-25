#ifndef PHANSAR_VENDOR_RAYGUI_HPP
#define PHANSAR_VENDOR_RAYGUI_HPP

#include <phansar/vendor/hedley.hpp>

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(push, 0)
#endif

#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>
#include <ricons.h>

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(pop)
#endif

#endif
