#include <phansar/common/threading/synchronized.hpp>

#include <phansar/vendor/catch2.hpp>
#include <phansar/vendor/trompeloeil.hpp>

struct mutex_mock {
    struct adapter {
        // NOLINTNEXTLINE(modernize-use-trailing-return-type)
        MAKE_MOCK0(lock, void());
        // NOLINTNEXTLINE(modernize-use-trailing-return-type)
        MAKE_MOCK0(try_lock, bool());
        // NOLINTNEXTLINE(modernize-use-trailing-return-type)
        MAKE_MOCK0(unlock, void());
    };

    static void lock() {
        return s_mock.lock();
    }

    static auto try_lock() -> bool {
        return s_mock.try_lock();
    }

    static void unlock() {
        return s_mock.unlock();
    }

    static adapter s_mock;
};

mutex_mock::adapter mutex_mock::s_mock = mutex_mock::adapter{};

SCENARIO("common::threading::synchronized", "[common][threading][synchronized]") {
    auto & mock = mutex_mock::s_mock;
    auto   sync = phansar::common::threading::synchronized<int, mutex_mock>{50};

    GIVEN("a new synchronized value") {
        WHEN("it is locked") {
            auto x1    = NAMED_REQUIRE_CALL(mock, lock());
            auto proxy = sync.lock();

            THEN("the value is locked") {
                x1.reset();

                AND_THEN("a proxy is returned") {
                    REQUIRE(*proxy == 50);

                    AND_WHEN("it goes out of scope") {
                        auto x2 = NAMED_REQUIRE_CALL(mock, unlock());
                        { auto dummy = std::move(proxy); }

                        THEN("the synchronized value is unlocked") {
                            x2.reset();
                        }
                    }
                }
            }
        }
        WHEN("it is try locked") {
            AND_WHEN("it is successful") {
                auto x1    = NAMED_REQUIRE_CALL(mock, try_lock()).RETURN(true);
                auto proxy = sync.try_lock();

                THEN("the value is locked") {
                    x1.reset();

                    AND_THEN("a proxy is returned") {
                        REQUIRE(proxy.has_value());
                        REQUIRE(*proxy.value() == 50);

                        AND_WHEN("it goes out of scope") {
                            auto x2 = NAMED_REQUIRE_CALL(mock, unlock());
                            { auto dummy = std::move(proxy); }

                            THEN("the synchronized value is unlocked") {
                                x2.reset();
                            }
                        }
                    }
                }
            }
            AND_WHEN("it fails") {
                auto x1    = NAMED_REQUIRE_CALL(mock, try_lock()).RETURN(false);
                auto proxy = sync.try_lock();

                THEN("the value is not locked") {
                    x1.reset();

                    AND_THEN("nothing is returned") {
                        REQUIRE(! proxy.has_value());
                    }
                }
            }
        }
    }
}
