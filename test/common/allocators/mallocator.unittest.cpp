#include <phansar/common/allocators/mallocator.hpp>

#include <phansar/vendor/catch2.hpp>

#include <string>
#include <tuple>
#include <vector>

using types = std::tuple<int, std::string, std::vector<int>, std::vector<std::string>>;

TEMPLATE_LIST_TEST_CASE("common_allocators_mallocator", "[common][allocators][mallocator]", types) {
    auto a = phansar::common::allocators::mallocator<TestType>{};

    SECTION("can allocate and deallocate") {
        auto * ptr = a.allocate(2);
        a.deallocate(ptr, 2);

        REQUIRE(ptr != nullptr);
    }
}
