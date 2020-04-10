#include "common_allocators_default_allocator.hpp"
#include <catch2/catch.hpp>
#include <string>
#include <vector>

TEMPLATE_TEST_CASE("common_allocators_default_allocator",
                   "[common][allocators][default_allocator]",
                   int,
                   std::string,
                   std::vector<int>,
                   std::vector<std::string>) {
    auto a = common::allocators::default_allocator<TestType>{};

    SECTION("can allocate and deallocate") {
        auto ptr = a.allocate(2);
        a.deallocate(ptr, 2);

        REQUIRE(ptr != nullptr);
    }
}
