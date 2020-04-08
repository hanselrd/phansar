#include "common_threading_thread_pool.hpp"
#include <atomic>
#include <catch2/catch.hpp>
#include <vector>

#define THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS (10000)

TEST_CASE("can use thread pool", "[libcommon][threading][thread_pool]") {
    auto tp = common::threading::thread_pool{};
    auto count = std::atomic_uint64_t{0};
    auto futs = std::vector<std::future<std::uint64_t>>{};
    auto futs_count = std::uint64_t{0};

    for (auto i = std::size_t{0}; i < THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS; ++i) {
        tp.push_work([&count] { count.fetch_add(1); });

        auto fut = tp.push_task([&count] {
            count.fetch_add(1);
            return std::uint64_t{1};
        });
        futs.push_back(std::move(fut));
    }

    for (auto &f : futs) {
        futs_count += f.get();
    }

    tp.wait_done();

    REQUIRE(count.load() == (2 * THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS));
    REQUIRE(futs_count == THREADING_THREAD_POOL_UNITTEST_MAX_ITERATIONS);
}
