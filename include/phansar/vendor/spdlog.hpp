#ifndef PHANSAR_VENDOR_SPDLOG_HPP
#define PHANSAR_VENDOR_SPDLOG_HPP

#include <phansar/vendor/hedley.hpp>

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(push, 0)
#endif

#include <spdlog/common.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#ifdef HEDLEY_MSVC_VERSION
#    pragma warning(pop)
#endif

#endif
