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
#include <cstdlib>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>

namespace common {
namespace utils {
namespace log {
void init(std::string_view filename) {
    if (filename.empty()) {
        return;
    }

    static auto color_console_appender = plog::ColorConsoleAppender<plog::TxtFormatter>{};
    static auto file_appender =
        plog::RollingFileAppender<plog::TxtFormatter>{std::string{filename}.c_str(), 8000, 3};

    plog::init(
#ifdef NDEBUG
        plog::info,
#else
        plog::debug,
#endif
        &color_console_appender);

    plog::get()->addAppender(&file_appender);

    LOGI << "";
    LOGD << "Logger initialized";
    LOGD << "  log file: " << filename;
    LOGI << "CPU count: " << SDL_GetCPUCount();
    LOGI << "CPU cache line size: " << SDL_GetCPUCacheLineSize();
    LOGI_IF(SDL_BYTEORDER) << "CPU endianness: "
                           << ((SDL_BYTEORDER == SDL_LIL_ENDIAN) ? "little" : "big");
    LOGI << "Platform: " << SDL_GetPlatform();
    LOGI << "System RAM: " << SDL_GetSystemRAM() << " B";
    LOGI << "Build type: "
         <<
#ifdef NDEBUG
        "release";
#else
        "debug";
#endif

    std::atexit([] {
        LOGD << "Logger shutdown";
        LOGI << "";
    });
}
} // namespace log
} // namespace utils
} // namespace common
