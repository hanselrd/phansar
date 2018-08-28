#include "window.hpp"

namespace client {
namespace gui {
window::window(const SDL_Rect &rect) : widget(rect) {
}

void window::update(double delta) {
    int x, y;

    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if ((x > _rect.x) && (x < _rect.x + _rect.w) && (y > _rect.y) && (y < _rect.y + _rect.h)) {
            _rect.x = x;
            _rect.y = y;
        }
    }
}

void window::draw(const std::shared_ptr<SDL_Renderer> &renderer) const {
    SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(renderer.get(), &_rect);
}
} // namespace gui
} // namespace client
