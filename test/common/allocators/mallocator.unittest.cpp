#include <phansar/common/allocators/mallocator.hpp>

#include <phansar/vendor/catch2.hpp>

SCENARIO("common::allocators::mallocator", "[common][allocators][mallocator]") {
    auto alloc = phansar::common::allocators::mallocator<int>{};

    GIVEN("a new mallocator") {
        WHEN("it allocates") {
            auto * ptr = alloc.allocate(5);

            THEN("a pointer is returned") {
                REQUIRE(ptr != nullptr);

                AND_WHEN("it deallocates") {
                    alloc.deallocate(ptr, 5);

                    THEN("the pointer is freed") {}
                }
            }
        }
    }
}
