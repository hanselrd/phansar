#include <catch2/catch.hpp>
#include <common/core/filesystem.hpp>

using namespace common::core::filesystem;

TEST_CASE("can open a file", "[libs][common][core][filesystem]") {
    file f("assets.psar");
    REQUIRE(f.exists());
}

TEST_CASE("can open a directory", "[libs][common][core][filesystem]") {
    directory dir("scripts");
    REQUIRE(dir.exists());
    REQUIRE(dir.get_path() == "scripts");
}

TEST_CASE("can see a directory_entry", "[libs][common][core][filesystem]") {
    directory dir("scripts");
    REQUIRE(dir.exists());
    REQUIRE(dir.get_path() == "scripts");

    auto entry = dir.next_entry();
    REQUIRE(
        (entry->get_name() == "." || entry->get_name() == ".." || entry->get_name() == "lua_api"));
    REQUIRE(entry->get_type() == directory_entry::type::DIRECTORY);
}
