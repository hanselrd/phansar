#include <phansar/common/threading/thread_pool.hpp>

#include <phansar/vendor/catch2.hpp>

SCENARIO("common::threading::thread_pool", "[common][threading][thread_pool]") {
    auto pool = phansar::common::threading::thread_pool{};

    GIVEN("a new thread pool") {
        WHEN("it receives work") {
            pool.push_work([] {});

            THEN("the work is scheduled") {
                AND_THEN("it is completed") {}
            }
        }
        WHEN("it receives a task") {
            auto fut = pool.push_task([] { return 50; });

            THEN("the task is scheduled") {
                AND_THEN("a future is returned") {
                    fut.wait();

                    AND_WHEN("the task is completed") {
                        THEN("the future will resolve") {
                            REQUIRE(fut.get() == 50);
                        }
                    }
                }
            }
        }
    }
}
