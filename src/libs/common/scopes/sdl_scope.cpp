#include "sdl_scope.hpp"
#include "../core/assert.hpp"
#include "../core/log.hpp"

namespace common {
namespace scopes {
sdl_scope::sdl_scope(std::uint32_t flags) {
    if (get_guards() > 1) {
        return;
    }

    MASSERT_ALWAYS(SDL_Init(flags) == 0, SDL_GetError());
    LOGI << "SDL initialized";
}

sdl_scope::~sdl_scope() {
    if (get_guards() > 1) {
        return;
    }

    SDL_Quit();
    LOGI << "SDL shutdown";
}

sdl_image_scope::sdl_image_scope(std::uint32_t flags) {
    if (get_guards() > 1) {
        return;
    }

    MASSERT_ALWAYS((IMG_Init(flags) & flags) == flags, IMG_GetError());
    LOGI << "SDL_image initialized";
}

sdl_image_scope::~sdl_image_scope() {
    if (get_guards() > 1) {
        return;
    }

    IMG_Quit();
    LOGI << "SDL_image shutdown";
}

sdl_mixer_scope::sdl_mixer_scope(std::uint32_t flags) {
    if (get_guards() > 1) {
        return;
    }

    ASSERT_ALWAYS(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == 0);
    MASSERT_ALWAYS((Mix_Init(flags) & flags) == flags, Mix_GetError());
    LOGI << "SDL_mixer initialized";
}

sdl_mixer_scope::~sdl_mixer_scope() {
    if (get_guards() > 1) {
        return;
    }

    Mix_CloseAudio();
    Mix_Quit();
    LOGI << "SDL_mixer shutdown";
}

// sdl_net_scope::sdl_net_scope() {
//     if (get_guards() > 1) {
//         return;
//     }

//     MASSERT_ALWAYS(SDLNet_Init() == 0, SDLNet_GetError());
//     LOGI << "SDL_net initialized";
// }

// sdl_net_scope::~sdl_net_scope() {
//     if (get_guards() > 1) {
//         return;
//     }

//     SDLNet_Quit();
//     LOGI << "SDL_net shutdown";
// }

sdl_ttf_scope::sdl_ttf_scope() {
    if (get_guards() > 1) {
        return;
    }

    MASSERT_ALWAYS(TTF_Init() == 0, TTF_GetError());
    LOGI << "SDL_ttf initialized";
}

sdl_ttf_scope::~sdl_ttf_scope() {
    if (get_guards() > 1) {
        return;
    }

    TTF_Quit();
    LOGI << "SDL_ttf shutdown";
}
} // namespace scopes
} // namespace common
