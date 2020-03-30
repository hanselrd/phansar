#include "common_allocators_default.hpp"
#include <catch2/catch.hpp>

TEST_CASE("can use default allocator", "[libcommon][allocators][default]") {
    auto a = common::allocators::default_allocator<int>{};
    auto ptr = a.allocate(10);
    REQUIRE(ptr != nullptr);
    a.deallocate(ptr, 10);
}
