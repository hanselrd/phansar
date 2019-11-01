/**
 * This file is part of Phansar.
 *
 * Copyright (C) 2018  Hansel De La Cruz
 *
 * Phansar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phansar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "log.hpp"
#include <SDL2/SDL_cpuinfo.h>
#include <SDL2/SDL_endian.h>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace common {
namespace utils {
namespace log {
namespace detail {
std::string obfuscate(std::string_view str, std::string_view delims) {
    auto tmp = std::string{""};

    auto beg = std::size_t{0};
    auto pos = std::size_t{0};
    while ((beg = str.find_first_not_of(delims, pos)) != std::string_view::npos) {
        pos = str.find_first_of(delims, beg + 1);
        tmp += str.substr(beg, pos - beg)[0];
    }

    std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](auto c) {
        return std::toupper(static_cast<unsigned char>(c));
    });

    return tmp;
}
} // namespace detail

void init(std::string_view filename) {
    if (filename.empty()) {
        return;
    }

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e %z] [%t] [%^%l%$] [%s.%!.%#] %v");
    console_sink->set_level(
#ifdef NDEBUG
        spdlog::level::info
#else
        spdlog::level::debug
#endif
    );

    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        std::string{filename}, 1048576 * 5, 3);
    rotating_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e %z] [%t] [%^%l%$] [%s.%!.%#] %v");
    rotating_sink->set_level(
#ifdef NDEBUG
        spdlog::level::info
#else
        spdlog::level::debug
#endif
    );

    auto logger = std::make_shared<spdlog::logger>(
        spdlog::logger{"multi_sink", {console_sink, rotating_sink}});
    logger->set_level(spdlog::level::trace);
    spdlog::set_default_logger(logger);

    LOGI("");
    LOGD("Logger initialized");
    LOGD("  log file: {}", filename);
    LOGI("CPU count: {}", SDL_GetCPUCount());
    LOGI("CPU cache line size: {}", SDL_GetCPUCacheLineSize());
    LOGI_IF(
        SDL_BYTEORDER, "CPU endianness: {}", (SDL_BYTEORDER == SDL_LIL_ENDIAN) ? "little" : "big");
    LOGI("Platform: {}", SDL_GetPlatform());
    LOGI("System RAM: {} B", SDL_GetSystemRAM());
    LOGI("Build type: {}",
#ifdef NDEBUG
         "release"
#else
         "debug"
#endif
    );

    std::atexit([] {
        LOGD("Logger shutdown");
        LOGI("");
    });
}
} // namespace log
} // namespace utils
} // namespace common
