#include "common_strings_stdlib.hpp"
#include <catch2/catch.hpp>
#include <tuple>
#include <type_traits>

using types = std::tuple<char, wchar_t /*, char8_t, char16_t, char32_t*/>;

TEMPLATE_LIST_TEST_CASE("common_strings_stdlib", "[common][strings][stdlib]", types) {
    SECTION("can use basic_string") {
        auto bs = common::strings::stdlib::basic_string<TestType>{};

        if constexpr (std::is_same_v<TestType, char>) {
            bs.push_back('T');
        } else if constexpr (std::is_same_v<TestType, wchar_t>) {
            bs.push_back(L'T');
            /* } else if constexpr (std::is_same_v<TestType, char8_t>) { */
            /*     bs.push_back(u8'T'); */
            /* } else if constexpr (std::is_same_v<TestType, char16_t>) { */
            /*     bs.push_back(u'T'); */
            /* } else if constexpr (std::is_same_v<TestType, char32_t>) { */
            /*     bs.push_back(U'T'); */
        }

        REQUIRE(bs.length() == 1);

        if constexpr (std::is_same_v<TestType, char>) {
            bs += "est";
        } else if constexpr (std::is_same_v<TestType, wchar_t>) {
            bs += L"est";
            /* } else if constexpr (std::is_same_v<TestType, char8_t>) { */
            /*     bs += u8"est"; */
            /* } else if constexpr (std::is_same_v<TestType, char16_t>) { */
            /*     bs += u"est"; */
            /* } else if constexpr (std::is_same_v<TestType, char32_t>) { */
            /*     bs += U"est"; */
        }

        REQUIRE(bs.length() == 4);
    }

    SECTION("can use basic_stringstream") {
        auto bss = common::strings::stdlib::basic_stringstream<TestType>{};

        if constexpr (std::is_same_v<TestType, char>) {
            bss << 'T';
        } else if constexpr (std::is_same_v<TestType, wchar_t>) {
            bss << L'T';
            /* } else if constexpr (std::is_same_v<TestType, char8_t>) { */
            /*     bss << u8'T'; */
            /* } else if constexpr (std::is_same_v<TestType, char16_t>) { */
            /*     bss << u'T'; */
            /* } else if constexpr (std::is_same_v<TestType, char32_t>) { */
            /*     bss << U'T'; */
        }

        REQUIRE(bss.str().length() == 1);

        if constexpr (std::is_same_v<TestType, char>) {
            bss << "est";
        } else if constexpr (std::is_same_v<TestType, wchar_t>) {
            bss << L"est";
            /* } else if constexpr (std::is_same_v<TestType, char8_t>) { */
            /*     bss << u8"est"; */
            /* } else if constexpr (std::is_same_v<TestType, char16_t>) { */
            /*     bss << u"est"; */
            /* } else if constexpr (std::is_same_v<TestType, char32_t>) { */
            /*     bss << U"est"; */
        }

        REQUIRE(bss.str().length() == 4);
    }
}
