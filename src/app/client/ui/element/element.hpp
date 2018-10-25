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

#ifndef CLIENT_UI_ELEMENT_HPP
#define CLIENT_UI_ELEMENT_HPP

#include <SDL2/SDL.h>
#include <common/components/vec2/vec2.hpp>
#include <memory>
#include <vector>

namespace client {
namespace ui {
class element {
public:
    element();
    explicit element(const common::components::vec2f &position,
                     const common::components::vec2u &size,
                     const SDL_Color &color);
    virtual ~element() = default;

    virtual void update() = 0;
    virtual void render() = 0;
    const common::components::vec2f &get_position() const;
    void set_position(const common::components::vec2f &position);
    const common::components::vec2u &get_size() const;
    void set_size(const common::components::vec2u &size);
    const SDL_Color &get_color() const;
    void set_color(const SDL_Color &color);
    void add_element(const std::shared_ptr<element> &el);

protected:
    void _set_render_draw_color();
    SDL_Rect *_get_rect();

private:
    std::vector<std::shared_ptr<element>> _elements;
    common::components::vec2f _position;
    common::components::vec2u _size;
    SDL_Color _color;
    SDL_Rect _rect;
};
} // namespace ui
} // namespace client

#endif
