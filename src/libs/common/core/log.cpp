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
namespace core {
namespace log {
namespace {
void _log_generic(sol::this_state s, plog::Severity severity, const std::string &message) {
    if (!plog::get<PLOG_DEFAULT_INSTANCE>() ||
        !plog::get<PLOG_DEFAULT_INSTANCE>()->checkSeverity(severity)) {
        return;
    }

    lua_State *L = s;
    lua_Debug ar;
    lua_getstack(L, 1, &ar);
    lua_getinfo(L, "nSl", &ar);

    (*plog::get<PLOG_DEFAULT_INSTANCE>()) +=
        plog::Record(severity, ar.source + 1, ar.currentline, "", PLOG_GET_THIS()).ref() << message;
}
} // namespace

void init(const std::string &filename) {
    if (filename.empty()) {
        return;
    }

    static plog::ColorConsoleAppender<plog::TxtFormatter> color_console_appender;
    static plog::RollingFileAppender<plog::TxtFormatter> file_appender(filename.c_str(), 8000, 3);

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

namespace lua_api {
void init(sol::table &t) {
    sol::table log = t.create_named("log");

    log.set_function("verbose", [](sol::this_state s, const std::string &message) {
        _log_generic(s, plog::verbose, message);
    });
    log.set_function("debug", [](sol::this_state s, const std::string &message) {
        _log_generic(s, plog::debug, message);
    });
    log.set_function("info", [](sol::this_state s, const std::string &message) {
        _log_generic(s, plog::info, message);
    });
    log.set_function("warning", [](sol::this_state s, const std::string &message) {
        _log_generic(s, plog::warning, message);
    });
    log.set_function("error", [](sol::this_state s, const std::string &message) {
        _log_generic(s, plog::error, message);
    });
    log.set_function("fatal", [](sol::this_state s, const std::string &message) {
        _log_generic(s, plog::fatal, message);
    });
    log.set_function("none", [](sol::this_state s, const std::string &message) {
        _log_generic(s, plog::none, message);
    });
}
} // namespace lua_api
} // namespace log
} // namespace core
} // namespace common
