#include "element.hpp"
#include "../managers/system_manager.hpp"

namespace client {
namespace ui {
element::element()
    : element(common::core::types::vector2f{0.f, 0.f},
              common::core::types::vector2u{0, 0},
              SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}) {
}

element::element(const common::core::types::vector2f &position,
                 const common::core::types::vector2u &size,
                 const SDL_Color &color)
    : _position(position), _size(size), _color(color) {
}

const common::core::types::vector2f &element::get_position() const {
    return _position;
}

void element::set_position(const common::core::types::vector2f &position) {
    _position = position;
}

const common::core::types::vector2u &element::get_size() const {
    return _size;
}

void element::set_size(const common::core::types::vector2u &size) {
    _size = size;
}

const SDL_Color &element::get_color() const {
    return _color;
}

void element::set_color(const SDL_Color &color) {
    _color = color;
}

void element::add_element(const std::shared_ptr<element> &el) {
    _elements.push_back(el);
}

void element::_set_render_draw_color() {
    SDL_SetRenderDrawColor(
        managers::system_manager::get_renderer().get(), _color.r, _color.g, _color.b, _color.a);
}

SDL_Rect *element::_get_rect() {
    _rect.x = _position.x;
    _rect.y = _position.y;
    _rect.w = _size.x;
    _rect.h = _size.y;
    return &_rect;
}
} // namespace ui
} // namespace client
