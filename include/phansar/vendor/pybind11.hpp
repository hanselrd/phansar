#ifndef PHANSAR_VENDOR_PYBIND11_HPP
#define PHANSAR_VENDOR_PYBIND11_HPP

#include <phansar/vendor/hedley.hpp>

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(push, 0)
#endif

#include <pybind11/embed.h>
namespace py = pybind11;

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(pop)
#endif

#endif
