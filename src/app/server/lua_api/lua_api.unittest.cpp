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

#include "lua_api.hpp"
#include <catch2/catch.hpp>
#include <common/lua_api/lua_api.hpp>

TEST_CASE("can use lua API", "[app][server][lua_api]") {
    auto lua = sol::state{};
    lua.open_libraries(sol::lib::base, sol::lib::string);

    auto phansar = lua.create_named_table("phansar");
    lua_api::init_common(phansar);
    lua_api::init_server(phansar);

    lua.script_file("scripts/lua_api/server.lua");
}