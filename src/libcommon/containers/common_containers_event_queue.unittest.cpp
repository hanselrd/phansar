#include "common_containers_event_queue.hpp"
#include <catch2/catch.hpp>
#include <cstdint>
#include <string>

enum class event_type { on, off, dead };

TEST_CASE("common_containers_event_queue", "[common][containers][event_queue]") {
    auto count = std::uint8_t{0};

    SECTION("can process all events") {
        auto eq = common::containers::event_queue<event_type, std::string>{};

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

    SECTION("can process filtered events") {
        auto eq = common::containers::event_queue<event_type, std::string>{event_type::on,
                                                                           event_type::off};

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
}
