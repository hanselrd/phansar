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

#include "log.lua_api.hpp"
#include "log.hpp"

using namespace common::utils;

namespace lua_api {
namespace common {
namespace utils {
void init_log(sol::table &t) {
    auto log_generic =
        [](sol::this_state s, spdlog::level::level_enum level, std::string_view message) {
            auto logger = spdlog::default_logger_raw();

            if (logger->should_log(level) || logger->should_backtrace()) {
                lua_State *L = s;
                lua_Debug ar;
                lua_getstack(L, 1, &ar);
                lua_getinfo(L, "nSl", &ar);

                logger->log(spdlog::source_loc{ar.source + 1, ar.currentline, ""}, level, message);
            }
        };

    auto log = t.create_named("log");

    log.set_function("trace", [&](sol::this_state s, std::string_view message) {
        log_generic(s, spdlog::level::trace, message);
    });
    log.set_function("debug", [&](sol::this_state s, std::string_view message) {
        log_generic(s, spdlog::level::debug, message);
    });
    log.set_function("info", [&](sol::this_state s, std::string_view message) {
        log_generic(s, spdlog::level::info, message);
    });
    log.set_function("warn", [&](sol::this_state s, std::string_view message) {
        log_generic(s, spdlog::level::warn, message);
    });
    log.set_function("error", [&](sol::this_state s, std::string_view message) {
        log_generic(s, spdlog::level::err, message);
    });
    log.set_function("critical", [&](sol::this_state s, std::string_view message) {
        log_generic(s, spdlog::level::critical, message);
    });
}
} // namespace utils
} // namespace common
} // namespace lua_api
