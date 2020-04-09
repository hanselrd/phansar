#include "common_containers_event_queue.hpp"
#include <catch2/catch.hpp>
#include <cstdint>
#include <string>

enum class event_type { on, off, dead };

TEST_CASE("can use event queue", "[libcommon][containers][event_queue]") {
    auto eq = common::containers::event_queue<event_type, std::string>{};
}

TEST_CASE("can use event queue all", "[libcommon][containers][event_queue]") {

    auto eq    = common::containers::event_queue<event_type, std::string>{};
    auto count = std::uint8_t{0};

    eq.subscribe([&count](const event_type & event, const std::string & data) {
        switch (event) {
        case event_type::on:
            REQUIRE(data == "on");
            break;
        case event_type::off:
            REQUIRE(data == "off");
            break;
        case event_type::dead:
            REQUIRE(data == "dead");
            break;
        }

        ++count;
    });

    eq.push(event_type::on, "on");
    eq.push(event_type::off, "off");
    eq.push(event_type::dead, "dead");

    eq.update();

    REQUIRE(count == 3);
}

TEST_CASE("can use event queue filtered", "[libcommon][containers][event_queue]") {
    auto eq =
        common::containers::event_queue<event_type, std::string>{event_type::on, event_type::off};
    auto count = std::uint8_t{0};

    eq.subscribe([&count](const event_type & event, const std::string & data) {
        switch (event) {
        case event_type::on:
            REQUIRE(data == "on");
            break;
        case event_type::off:
            REQUIRE(data == "off");
            break;
        case event_type::dead:
            REQUIRE(false);
            break;
        }

        ++count;
    });

    eq.push(event_type::on, "on");
    eq.push(event_type::off, "off");
    eq.push(event_type::dead, "dead");

    eq.update();

    REQUIRE(count == 2);
}
