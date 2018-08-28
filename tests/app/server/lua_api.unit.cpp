#include <catch2/catch.hpp>
#include <common/common.hpp>

TEST_CASE("can use lua API", "[server]") {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::string);
    sol::table phansar = lua.create_named_table("phansar");
    common::lua_api::init(phansar);

    lua.script_file("scripts/lua_api/server.lua");
}
