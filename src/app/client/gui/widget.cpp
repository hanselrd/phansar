#include "widget.hpp"

namespace client {
namespace gui {
widget::widget(const SDL_Rect &rect) : _rect(rect) {
}

const SDL_Rect &widget::get_rect() const {
    return _rect;
}

void widget::set_rect(const SDL_Rect &rect) {
    _rect = rect;
}
} // namespace gui
} // namespace client
