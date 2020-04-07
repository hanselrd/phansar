#include "common_threading_thread_pool.hpp"
#include <atomic>
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("can use thread pool", "[libcommon][threading][thread_pool]") {
    auto tp = common::threading::thread_pool{};
    auto count = std::atomic_uint64_t{0};
    auto futs = std::vector<std::future<std::uint64_t>>{};
    auto futs_count = std::uint64_t{0};

    for (auto i = std::size_t{0}; i < 10000; ++i) {
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

    REQUIRE(count.load() == 20000);
    REQUIRE(futs_count == 10000);
}
