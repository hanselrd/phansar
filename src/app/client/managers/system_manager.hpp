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

#ifndef CLIENT_MANAGERS_SYSTEM_MANAGER_HPP
#define CLIENT_MANAGERS_SYSTEM_MANAGER_HPP

#include <SDL2/SDL.h>
#include <common/core/dispatch_queue.hpp>
#include <memory>

namespace client {
namespace managers {
namespace system_manager {
void init();
void update();
std::shared_ptr<common::core::dispatch_queue> get_dispatch_queue();
std::shared_ptr<SDL_Window> get_window();
std::shared_ptr<SDL_Renderer> get_renderer();
float get_delta_time();
float get_fps();
} // namespace system_manager
} // namespace managers
} // namespace client

#endif
