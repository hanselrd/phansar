#ifndef PHANSAR_VENDOR_SPDLOG_PRIVATE_HPP
#define PHANSAR_VENDOR_SPDLOG_PRIVATE_HPP

#include <phansar/vendor/hedley.hpp>
#include <phansar/vendor/spdlog.hpp>

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(push, 0)
#endif

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(pop)
#endif

#endif
