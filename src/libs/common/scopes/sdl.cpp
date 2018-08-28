#include "sdl.hpp"
#include "../core/assert.hpp"
#include "../core/log.hpp"

namespace common {
namespace scopes {
sdl::sdl(std::uint32_t flags) {
    if (_guards > 1) {
        return;
    }

    MASSERT_ALWAYS(SDL_Init(flags) == 0, SDL_GetError());
    LOGI << "SDL initialized";
}

sdl::~sdl() {
    if (_guards > 1) {
        return;
    }

    SDL_Quit();
    LOGI << "SDL shutdown";
}

sdl_image::sdl_image(std::uint32_t flags) {
    if (_guards > 1) {
        return;
    }

    MASSERT_ALWAYS((IMG_Init(flags) & flags) == flags, IMG_GetError());
    LOGI << "SDL_image initialized";
}

sdl_image::~sdl_image() {
    if (_guards > 1) {
        return;
    }

    IMG_Quit();
    LOGI << "SDL_image shutdown";
}

sdl_mixer::sdl_mixer(std::uint32_t flags) {
    if (_guards > 1) {
        return;
    }

    MASSERT_ALWAYS((Mix_Init(flags) & flags) == flags, Mix_GetError());
    LOGI << "SDL_mixer initialized";
}

sdl_mixer::~sdl_mixer() {
    if (_guards > 1) {
        return;
    }

    Mix_Quit();
    LOGI << "SDL_mixer shutdown";
}

// sdl_net::sdl_net() {
//     if (_guards > 1) {
//         return;
//     }

//     MASSERT_ALWAYS(SDLNet_Init() == 0, SDLNet_GetError());
//     LOGI << "SDL_net initialized";
// }

// sdl_net::~sdl_net() {
//     if (_guards > 1) {
//         return;
//     }

//     SDLNet_Quit();
//     LOGI << "SDL_net shutdown";
// }

sdl_ttf::sdl_ttf() {
    if (_guards > 1) {
        return;
    }

    MASSERT_ALWAYS(TTF_Init() == 0, TTF_GetError());
    LOGI << "SDL_ttf initialized";
}

sdl_ttf::~sdl_ttf() {
    if (_guards > 1) {
        return;
    }

    TTF_Quit();
    LOGI << "SDL_ttf shutdown";
}
} // namespace scopes
} // namespace common
