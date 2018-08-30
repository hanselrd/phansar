#include "window.hpp"

namespace client {
namespace ui {
window::window(const common::core::types::vector2f &position,
               const common::core::types::vector2u &size,
               const SDL_Color &color)
    : _titlebar(position, size, color), _body(position, size, SDL_Color{0xAA, 0xAA, 0xAA, 0xDD}) {
    _titlebar.set_size(common::core::types::vector2u{size.x, 20});
    _body.set_position(common::core::types::vector2f{position.x, position.y + 20});
}

void window::update() {
}

void window::render() {
    _titlebar.render();
    _body.render();
}
} // namespace ui
} // namespace client
