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

#include "input_manager.hpp"

namespace client {
namespace managers {
namespace input_manager {
namespace {
SDL_Event e;
} // namespace

void handle_event(const SDL_Event &event) {
    e = event;
}

const SDL_Event &get_event() {
    return e;
}

const std::uint8_t *get_keyboard_state() {
    return SDL_GetKeyboardState(nullptr);
}

std::uint32_t get_mouse_state(common::core::types::vector2u &position) {
    int x, y;
    auto state = SDL_GetMouseState(&x, &y);
    position.x = x;
    position.y = y;
    return state;
}
} // namespace input_manager
} // namespace managers
} // namespace client
