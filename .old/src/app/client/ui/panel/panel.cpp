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

#include "panel.hpp"
#include "../../managers/system_manager/system_manager.hpp"

namespace client {
namespace ui {
panel::panel(const common::components::vec2f &position,
             const common::components::vec2u &size,
             const SDL_Color &color)
    : element{position, size, color} {
}

void panel::update() {
}

void panel::render() {
    _set_render_draw_color();
    SDL_RenderFillRect(managers::system_manager::get_renderer().get(), _get_rect());
}
} // namespace ui
} // namespace client
