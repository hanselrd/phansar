#include "common_allocators_default_allocator.hpp"
#include <catch2/catch.hpp>
#include <string>
#include <tuple>
#include <vector>

using types = std::tuple<int, std::string, std::vector<int>, std::vector<std::string>>;

TEMPLATE_LIST_TEST_CASE("common_allocators_default_allocator",
                        "[common][allocators][default_allocator]",
                        types) {
    auto a = common::allocators::default_allocator<TestType>{};

    SECTION("can allocate and deallocate") {
        auto ptr = a.allocate(2);
        a.deallocate(ptr, 2);

        REQUIRE(ptr != nullptr);
    }
}
