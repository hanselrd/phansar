#include "input_manager.hpp"

namespace client {
namespace managers {
namespace input_manager {
namespace {
SDL_Event e;
} // namespace

void handle_event(const SDL_Event &event) {
    e = event;
}

const SDL_Event &get_event() {
    return e;
}

const std::uint8_t *get_keyboard_state() {
    return SDL_GetKeyboardState(nullptr);
}

std::uint32_t get_mouse_state(common::core::types::vector2u &position) {
    int x, y;
    auto state = SDL_GetMouseState(&x, &y);
    position.x = x;
    position.y = y;
    return state;
}
} // namespace input_manager
} // namespace managers
} // namespace client
