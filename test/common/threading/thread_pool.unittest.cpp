#include <phansar/common/threading/thread_pool.hpp>

#include <phansar/vendor/catch2.hpp>

#include <atomic>
#include <vector>

#define THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS (10000)

TEST_CASE("common_threading_thread_pool", "[common][threading][thread_pool]") {
    auto tp    = phansar::common::threading::thread_pool{};
    auto count = std::atomic_uint64_t{0};

    SECTION("can push_work") {
        for (auto i = std::size_t{0}; i < THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS; ++i) {
            tp.push_work([&count] { count.fetch_add(1); });
        }

        tp.wait_done();

        REQUIRE(count.load() == THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS);
    }

    SECTION("can push_task") {
        auto futs       = std::vector<std::future<std::uint64_t>>{};
        auto futs_count = std::uint64_t{0};

        for (auto i = std::size_t{0}; i < THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS; ++i) {
            auto fut = tp.push_task([&count] {
                count.fetch_add(1);
                return std::uint64_t{1};
            });
            futs.push_back(std::move(fut));
        }

        for (auto & f : futs) {
            futs_count += f.get();
        }

        tp.wait_done();

        REQUIRE(count.load() == THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS);
        REQUIRE(futs_count == THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS);
    }
}
