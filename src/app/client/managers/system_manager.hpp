#ifndef CLIENT_MANAGERS_SYSTEM_MANAGER_HPP
#define CLIENT_MANAGERS_SYSTEM_MANAGER_HPP

#include <SDL2/SDL.h>
#include <memory>

namespace client {
namespace managers {
namespace system_manager {
void init();
std::shared_ptr<SDL_Window> get_window();
std::shared_ptr<SDL_Renderer> get_renderer();
} // namespace system_manager
} // namespace managers
} // namespace client

#endif
