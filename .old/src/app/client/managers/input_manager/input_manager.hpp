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

#ifndef APP_CLIENT_MANAGERS_INPUT_MANAGER_INPUT_MANAGER_HPP
#define APP_CLIENT_MANAGERS_INPUT_MANAGER_INPUT_MANAGER_HPP

#include <SDL2/SDL.h>
#include <common/components/vec2/vec2.hpp>
#include <cstdint>

namespace client {
namespace managers {
namespace input_manager {
void handle_event(const SDL_Event &event);
const SDL_Event &get_event();
const std::uint8_t *get_keyboard_state();
std::uint32_t get_mouse_state(common::components::vec2u &position);
} // namespace input_manager
} // namespace managers
} // namespace client

#endif
