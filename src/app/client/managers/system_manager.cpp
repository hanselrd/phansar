#include "system_manager.hpp"
#include <common/core/assert.hpp>
#include <common/core/log.hpp>
#include <common/scopes/scopes.hpp>
#include <cstdlib>

namespace client {
namespace managers {
namespace system_manager {
namespace {
std::unique_ptr<common::scopes::plibsys> plibsys_guard;
std::unique_ptr<common::scopes::sdl> sdl_guard;
std::unique_ptr<common::scopes::sdl_image> sdl_image_guard;
std::unique_ptr<common::scopes::sdl_ttf> sdl_ttf_guard;
std::unique_ptr<common::scopes::enet> enet_guard;

std::shared_ptr<SDL_Window> window;
std::shared_ptr<SDL_Renderer> renderer;
} // namespace

void init() {
    common::core::log::init("phansar.log");

    plibsys_guard = std::make_unique<common::scopes::plibsys>();
    sdl_guard = std::make_unique<common::scopes::sdl>(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    sdl_image_guard = std::make_unique<common::scopes::sdl_image>(IMG_INIT_PNG);
    sdl_ttf_guard = std::make_unique<common::scopes::sdl_ttf>();
    enet_guard = std::make_unique<common::scopes::enet>();

    window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Phansar [SDL]",
                                                          SDL_WINDOWPOS_CENTERED,
                                                          SDL_WINDOWPOS_CENTERED,
                                                          800,
                                                          600,
                                                          SDL_WINDOW_SHOWN),
                                         &SDL_DestroyWindow);
    MASSERT_ALWAYS(window, SDL_GetError());

    renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
        &SDL_DestroyRenderer);
    MASSERT_ALWAYS(renderer, SDL_GetError());

    std::atexit([] {
        renderer.reset();
        window.reset();
        enet_guard.reset();
        sdl_ttf_guard.reset();
        sdl_image_guard.reset();
        sdl_guard.reset();
        plibsys_guard.reset();
    });
}

std::shared_ptr<SDL_Window> get_window() {
    return window;
}

std::shared_ptr<SDL_Renderer> get_renderer() {
    return renderer;
}
} // namespace system_manager
} // namespace managers
} // namespace client
