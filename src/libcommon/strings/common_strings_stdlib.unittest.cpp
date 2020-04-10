#include "common_strings_stdlib.hpp"
#include <catch2/catch.hpp>

TEST_CASE("can use string", "[libcommon][strings][stdlib]") {
    auto s = common::strings::stdlib::string{};
}

TEST_CASE("can use u8string", "[libcommon][strings][stdlib]") {
    auto u8s = common::strings::stdlib::u8string{};
}

TEST_CASE("can use u16string", "[libcommon][strings][stdlib]") {
    auto u16s = common::strings::stdlib::u16string{};
}

TEST_CASE("can use u32string", "[libcommon][strings][stdlib]") {
    auto u32s = common::strings::stdlib::u32string{};
}

TEST_CASE("can use stringstream", "[libcommon][strings][stdlib]") {
    auto ss = common::strings::stdlib::stringstream{};
}

TEST_CASE("can use u8stringstream", "[libcommon][strings][stdlib]") {
    auto u8ss = common::strings::stdlib::u8stringstream{};
}

TEST_CASE("can use u16stringstream", "[libcommon][strings][stdlib]") {
    auto u16ss = common::strings::stdlib::u16stringstream{};
}

TEST_CASE("can use u32stringstream", "[libcommon][strings][stdlib]") {
    auto u32ss = common::strings::stdlib::u32stringstream{};
}
