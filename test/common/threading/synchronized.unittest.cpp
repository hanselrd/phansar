#include <phansar/common/threading/synchronized.hpp>
#include <phansar/vendor/catch2.hpp>

SCENARIO("common::threading::synchronized", "[common][threading][synchronized]") {
    auto sync = phansar::common::threading::synchronized<int>{50};

    GIVEN("a new synchronized value") {
        WHEN("it is locked") {
            /* auto x1    = NAMED_REQUIRE_CALL(mock, lock()); */
            auto proxy = sync.lock();

            THEN("the value is locked") {
                /* x1.reset(); */

                AND_THEN("a proxy is returned") {
                    REQUIRE(*proxy == 50);

                    AND_WHEN("it goes out of scope") {
                        /* auto x2 = NAMED_REQUIRE_CALL(mock, unlock()); */
                        { auto dummy = std::move(proxy); }

                        THEN("the synchronized value is unlocked") {
                            /* x2.reset(); */
                        }
                    }
                }
            }
        }
        WHEN("it is try locked") {
            AND_WHEN("it is successful") {
                /* auto x1    = NAMED_REQUIRE_CALL(mock, try_lock()).RETURN(true); */
                auto proxy = sync.try_lock();

                THEN("the value is locked") {
                    /* x1.reset(); */

                    AND_THEN("a proxy is returned") {
                        REQUIRE(proxy.has_value());
                        REQUIRE(*proxy.value() == 50);

                        AND_WHEN("it goes out of scope") {
                            /* auto x2 = NAMED_REQUIRE_CALL(mock, unlock()); */
                            { auto dummy = std::move(proxy); }

                            THEN("the synchronized value is unlocked") {
                                /* x2.reset(); */
                            }
                        }
                    }
                }
            }
            /* AND_WHEN("it fails") { */
            /*     /1* auto x1    = NAMED_REQUIRE_CALL(mock, try_lock()).RETURN(false); *1/ */
            /*     auto proxy = sync.try_lock(); */

            /*     THEN("the value is not locked") { */
            /*         /1* x1.reset(); *1/ */

            /*         AND_THEN("nothing is returned") { */
            /*             REQUIRE(! proxy.has_value()); */
            /*         } */
            /*     } */
            /* } */
        }
    }
}
