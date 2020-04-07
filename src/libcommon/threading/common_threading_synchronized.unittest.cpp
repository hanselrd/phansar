#include "common_threading_synchronized.hpp"
#include <catch2/catch.hpp>
#include <thread>
#include <vector>

TEST_CASE("can use synchronized vector", "[libcommon][threading][synchronized]") {
    auto s = common::threading::synchronized<std::vector<int>>{};
    auto threads = std::vector<std::thread>{};

    REQUIRE(std::thread::hardware_concurrency() > 0);

    for (auto i = std::size_t{0}; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&s]() {
            for (auto j = int{0}; j < 10000; ++j) {
                s.lock()->push_back(j);
            }
        });
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    REQUIRE(s.lock()->size() == (10000 * std::thread::hardware_concurrency()));
}

TEST_CASE("can use synchronized struct", "[libcommon][threading][synchronized]") {
    struct point {
        int x;
        int y;
    };

    auto s = common::threading::synchronized<point>{};
    auto threads = std::vector<std::thread>{};

    REQUIRE(std::thread::hardware_concurrency() > 0);

    for (auto i = std::size_t{0}; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&s]() {
            for (auto j = int{0}; j < 10000; ++j) {
                auto l = s.lock();
                ++l->x;
                --l->y;
            }
        });
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    REQUIRE(s.lock()->x == (10000 * static_cast<int>(std::thread::hardware_concurrency())));
    REQUIRE(s.lock()->y == (-10000 * static_cast<int>(std::thread::hardware_concurrency())));
}

TEST_CASE("can use synchronized primitive", "[libcommon][threading][synchronized]") {
    auto s = common::threading::synchronized<int>{};
    auto threads = std::vector<std::thread>{};

    REQUIRE(std::thread::hardware_concurrency() > 0);

    for (auto i = std::size_t{0}; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&s]() {
            for (auto j = int{0}; j < 10000; ++j) {
                /* ++(*s.lock()); */
                while (true) {
                    if (auto l = s.try_lock(); l.has_value()) {
                        ++l->get();
                        break;
                    }
                }
            }
        });
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    REQUIRE(*s.lock() == (10000 * static_cast<int>(std::thread::hardware_concurrency())));
}
