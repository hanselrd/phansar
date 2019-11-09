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

#ifndef APP_CLIENT_UI_WINDOW_WINDOW_HPP
#define APP_CLIENT_UI_WINDOW_WINDOW_HPP

#include "../element/element.hpp"
#include "../panel/panel.hpp"

namespace client {
namespace ui {
class window : public element {
public:
    explicit window(const common::components::vec2f &position,
                    const common::components::vec2u &size,
                    const SDL_Color &color);

    void update() override;
    void render() override;

private:
    panel _titlebar;
    panel _body;
};
} // namespace ui
} // namespace client

#endif
