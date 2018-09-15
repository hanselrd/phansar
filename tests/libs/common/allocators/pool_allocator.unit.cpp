#include <catch2/catch.hpp>
#include <common/allocators/pool_allocator.hpp>

using namespace common::allocators;

TEST_CASE("can create pool allocator", "[libs][common][allocators][pool_allocator]") {
    pool_allocator pa(512);
}

TEST_CASE("pool allocator can allocate", "[libs][common][allocators][pool_allocator]") {
    pool_allocator pa(sizeof(int) * 2);

    auto p_int1 = new (pa) int(1337);
    REQUIRE(p_int1 != nullptr);
    REQUIRE(*p_int1 == 1337);

    auto p_int2 = new (pa) int(9001);
    REQUIRE(p_int2 != nullptr);
    REQUIRE((p_int2 - p_int1) == 1);
    REQUIRE(*p_int2 == 9001);
}

TEST_CASE("pool allocator can deallocate", "[libs][common][allocators][pool_allocator]") {
    pool_allocator pa(sizeof(int));

    auto p_int1 = new (pa) int(1337);
    REQUIRE(p_int1 != nullptr);
    REQUIRE(*p_int1 == 1337);

    pa.deallocate(p_int1);

    auto p_int2 = new (pa) int(9001);
    REQUIRE(p_int2 != nullptr);
    REQUIRE(p_int1 == p_int2);
    REQUIRE(*p_int2 == 9001);
}
