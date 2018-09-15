#include <catch2/catch.hpp>
#include <common/core/dispatch_queue.hpp>
#include <future>

using namespace common::core;

TEST_CASE("can create dispatch queue", "[libs][common][core][dispatch_queue]") {
    dispatch_queue dq;
}

TEST_CASE("can dispatch a job", "[libs][common][core][dispatch_queue]") {
    dispatch_queue dq;

    std::promise<bool> p;
    auto f = p.get_future();
    dq.dispatch([&p] { p.set_value(true); });
    f.wait();
    REQUIRE(f.get() == true);
}
