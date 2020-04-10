#include "common_threading_synchronized.hpp"
#include <catch2/catch.hpp>
#include <thread>
#include <tuple>
#include <type_traits>
#include <vector>

#define THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS (10000)

struct point {
    int x;
    int y;
};

using types = std::tuple<std::vector<int>, point, int>;

TEMPLATE_LIST_TEST_CASE("common_threading_synchronized",
                        "[common][threading][synchronized]",
                        types) {
    auto s       = common::threading::synchronized<TestType>{};
    auto threads = std::vector<std::thread>{};

    REQUIRE(std::thread::hardware_concurrency() > 0);

    SECTION("can lock") {
        for (auto i = std::size_t{0}; i < std::thread::hardware_concurrency(); ++i) {
            threads.emplace_back([&s] {
                for (auto j = std::size_t{0}; j < THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS;
                     ++j) {
                    auto l = s.lock();

                    if constexpr (std::is_same_v<TestType, std::tuple_element_t<0, types>>) {
                        l->push_back(1);
                    } else if constexpr (std::is_same_v<TestType, std::tuple_element_t<1, types>>) {
                        ++l->x;
                        --l->y;
                    } else if constexpr (std::is_same_v<TestType, std::tuple_element_t<2, types>>) {
                        ++(*l);
                    }
                }
            });
        }

        for (auto & t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }

        auto l = s.lock();

        if constexpr (std::is_same_v<TestType, std::tuple_element_t<0, types>>) {
            REQUIRE(l->size() == (THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS *
                                  std::thread::hardware_concurrency()));
        } else if constexpr (std::is_same_v<TestType, std::tuple_element_t<1, types>>) {
            REQUIRE(l->x == (THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS *
                             static_cast<decltype(l->x)>(std::thread::hardware_concurrency())));
            REQUIRE(l->y == -(THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS *
                              static_cast<decltype(l->y)>(std::thread::hardware_concurrency())));
        } else if constexpr (std::is_same_v<TestType, std::tuple_element_t<2, types>>) {
            REQUIRE(*l == (THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS *
                           static_cast<std::remove_reference_t<decltype(*l)>>(
                               std::thread::hardware_concurrency())));
        }
    }

    SECTION("can try_lock") {
        for (auto i = std::size_t{0}; i < std::thread::hardware_concurrency(); ++i) {
            threads.emplace_back([&s] {
                for (auto j = std::size_t{0}; j < THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS;
                     ++j) {
                    while (true) {
                        if (auto l = s.try_lock(); l.has_value()) {
                            if constexpr (std::is_same_v<TestType,
                                                         std::tuple_element_t<0, types>>) {
                                l.value()->push_back(1);
                            } else if constexpr (std::is_same_v<TestType,
                                                                std::tuple_element_t<1, types>>) {
                                ++l.value()->x;
                                --l.value()->y;
                            } else if constexpr (std::is_same_v<TestType,
                                                                std::tuple_element_t<2, types>>) {
                                ++(*l.value());
                            }

                            break;
                        }
                    }
                }
            });
        }

        for (auto & t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }

        while (true) {
            if (auto l = s.try_lock(); l.has_value()) {
                if constexpr (std::is_same_v<TestType, std::tuple_element_t<0, types>>) {
                    REQUIRE(l.value()->size() == (THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS *
                                                  std::thread::hardware_concurrency()));
                } else if constexpr (std::is_same_v<TestType, std::tuple_element_t<1, types>>) {
                    REQUIRE(l.value()->x == (THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS *
                                             static_cast<decltype(l.value()->x)>(
                                                 std::thread::hardware_concurrency())));
                    REQUIRE(l.value()->y == -(THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS *
                                              static_cast<decltype(l.value()->y)>(
                                                  std::thread::hardware_concurrency())));
                } else if constexpr (std::is_same_v<TestType, std::tuple_element_t<2, types>>) {
                    REQUIRE(*l.value() ==
                            (THREADING_SYNCHRONIZED_UNITTEST_MAX_ITERATIONS *
                             static_cast<std::remove_reference_t<decltype(*l.value())>>(
                                 std::thread::hardware_concurrency())));
                }

                break;
            }
        }
    }
}
