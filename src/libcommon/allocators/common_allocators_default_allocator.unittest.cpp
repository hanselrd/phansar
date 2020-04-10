#include "common_allocators_default_allocator.hpp"
#include <catch2/catch.hpp>

TEST_CASE("can use default allocator", "[libcommon][allocators][default_allocator]") {
    auto a   = common::allocators::default_allocator<int>{};
    auto ptr = a.allocate(2);
    REQUIRE(ptr != nullptr);
    a.deallocate(ptr, 2);
}
