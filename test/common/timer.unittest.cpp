#include <phansar/common/timer.hpp>

#include <phansar/vendor/catch2.hpp>
#include <phansar/vendor/trompeloeil.hpp>

struct clock_mock {
    using duration = std::chrono::duration<int>;

    struct adapter {
        // NOLINTNEXTLINE(modernize-use-trailing-return-type)
        MAKE_MOCK0(now, std::chrono::time_point<clock_mock>());
    };

    static auto now() -> std::chrono::time_point<clock_mock> {
        return s_mock.now();
    }

    static adapter s_mock;
};

clock_mock::adapter clock_mock::s_mock = clock_mock::adapter{};

SCENARIO("common::timer", "[common][timer]") {
    auto & mock  = clock_mock::s_mock;
    auto   timer = phansar::common::timer<clock_mock>{};

    GIVEN("a new timer") {
        WHEN("it is started") {
            auto x1 = NAMED_REQUIRE_CALL(mock, now())
                          .RETURN(std::invoke_result_t<decltype(&clock_mock::now)>{
                              std::chrono::seconds{10}});
            timer.start();

            THEN("it remembers the start time") {
                x1.reset();
            }
        }
        WHEN("it is stopped") {
            timer.stop();

            THEN("nothing happens") {}
        }
        WHEN("it is queried for elapsed time") {
            THEN("the elapsed time is 0") {
                REQUIRE(timer.get_elapsed_time<int, std::chrono::seconds>() == 0);
            }
        }
    }
    GIVEN("a started timer") {
        {
            REQUIRE_CALL(mock, now())
                .RETURN(std::invoke_result_t<decltype(&clock_mock::now)>{std::chrono::seconds{10}});
            timer.start();
        }

        WHEN("it is started") {
            timer.start();

            THEN("nothing happens") {}
        }
        WHEN("it is stopped") {
            auto x1 = NAMED_REQUIRE_CALL(mock, now())
                          .RETURN(std::invoke_result_t<decltype(&clock_mock::now)>{
                              std::chrono::seconds{15}});
            timer.stop();

            THEN("it remembers the stop time") {
                x1.reset();
            }
        }
        WHEN("it is queried for elapsed time") {
            auto x1 = NAMED_REQUIRE_CALL(mock, now())
                          .RETURN(std::invoke_result_t<decltype(&clock_mock::now)>{
                              std::chrono::seconds{15}});

            THEN("the elapsed time is the difference between the current and start time") {
                REQUIRE(timer.get_elapsed_time<int, std::chrono::seconds>() == 5);
                x1.reset();
            }
        }
    }
    GIVEN("a stopped timer") {
        timer.stop();

        WHEN("it is started") {
            auto x1 = NAMED_REQUIRE_CALL(mock, now())
                          .RETURN(std::invoke_result_t<decltype(&clock_mock::now)>{
                              std::chrono::seconds{10}});
            timer.start();

            THEN("it remembers the start time") {
                x1.reset();
            }
        }
        WHEN("it is stopped") {
            timer.stop();

            THEN("nothing happens") {}
        }
        WHEN("it is queried for elapsed time") {
            THEN("the elapsed time is the difference between the stop and start time") {
                REQUIRE(timer.get_elapsed_time<int, std::chrono::seconds>() == 0);
            }
        }
    }
}
