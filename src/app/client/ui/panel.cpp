#include "panel.hpp"
#include "../managers/system_manager.hpp"

namespace client {
namespace ui {
panel::panel(const common::core::types::vector2f &position,
             const common::core::types::vector2u &size,
             const SDL_Color &color)
    : element(position, size, color) {
}

void panel::update() {
}

void panel::render() {
    _set_render_draw_color();
    SDL_RenderFillRect(managers::system_manager::get_renderer().get(), _get_rect());
}
} // namespace ui
} // namespace client
