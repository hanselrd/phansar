#include <catch2/catch.hpp>
#include <common/core/filesystem.hpp>

using namespace common::core::filesystem;

TEST_CASE("can open a file", "[common]") {
    file f("assets.psar");
    REQUIRE(f.exists());
}

TEST_CASE("can open a directory", "[common]") {
    directory dir("scripts");
    REQUIRE(dir.exists());
    REQUIRE(dir.get_path() == "scripts");
}
