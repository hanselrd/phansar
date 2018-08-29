#ifndef CLIENT_MANAGERS_INPUT_MANAGER_HPP
#define CLIENT_MANAGERS_INPUT_MANAGER_HPP

#include <SDL2/SDL.h>
#include <common/core/types.hpp>
#include <cstdint>

namespace client {
namespace managers {
namespace input_manager {
void handle_event(const SDL_Event &event);
const SDL_Event &get_event();
const std::uint8_t *get_keyboard_state();
std::uint32_t get_mouse_state(common::core::types::vector2u &position);
} // namespace input_manager
} // namespace managers
} // namespace client

#endif
