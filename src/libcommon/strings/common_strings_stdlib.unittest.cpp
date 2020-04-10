#include "common_strings_stdlib.hpp"
#include <catch2/catch.hpp>

TEST_CASE("common_strings_stdlib", "[common][strings][stdlib]") {
    SECTION("can use string") {
        auto s = common::strings::stdlib::string{};
    }

    SECTION("can use u8string") {
        auto u8s = common::strings::stdlib::u8string{};
    }

    SECTION("can use u16string") {
        auto u16s = common::strings::stdlib::u16string{};
    }

    SECTION("can use u32string") {
        auto u32s = common::strings::stdlib::u32string{};
    }

    SECTION("can use stringstream") {
        auto ss = common::strings::stdlib::stringstream{};
    }

    SECTION("can use u8stringstream") {
        auto u8ss = common::strings::stdlib::u8stringstream{};
    }

    SECTION("can use u16stringstream") {
        auto u16ss = common::strings::stdlib::u16stringstream{};
    }

    SECTION("can use u32stringstream") {
        auto u32ss = common::strings::stdlib::u32stringstream{};
    }
}
