/**
 * This file is part of Phansar.
 *
 * Copyright (C) 2018  Hansel De La Cruz
 *
 * Phansar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phansar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SDL2/SDL.h>
#include <catch2/catch.hpp>
#include <common/core/event_queue.hpp>
#include <cstdint>

using namespace common::core;

TEST_CASE("can create event queue", "[libs][common][core][event_queue]") {
    event_queue<SDL_Event, std::uint32_t> eq;
}

TEST_CASE("can subscribe to all events", "[libs][common][core][event_queue]") {
    event_queue<SDL_Event, std::uint32_t> eq;
    std::uint8_t count = 0;

    eq.subscribe([&](const SDL_Event &e) { ++count; });
    eq.event(SDL_Event{}, SDL_QUIT);
    eq.event(SDL_Event{}, SDL_KEYDOWN);
    eq.event(SDL_Event{}, SDL_KEYUP);
    eq.update();

    REQUIRE(count == 3);
}

TEST_CASE("can subscribe to filtered events", "[libs][common][core][event_queue]") {
    event_queue<SDL_Event, std::uint32_t> eq{SDL_QUIT, SDL_KEYDOWN};
    std::uint8_t count = 0;

    eq.subscribe([&](const SDL_Event &e) { ++count; });
    eq.event(SDL_Event{}, SDL_QUIT);
    eq.event(SDL_Event{}, SDL_KEYDOWN);
    eq.event(SDL_Event{}, SDL_KEYUP);
    eq.update();

    REQUIRE(count == 2);
}
