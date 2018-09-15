#ifndef COMMON_SCOPES_SDL_HPP
#define COMMON_SCOPES_SDL_HPP

#include "base.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>

namespace common {
namespace scopes {
class sdl_scope : public internal::base<sdl_scope> {
public:
    explicit sdl_scope(std::uint32_t flags);
    ~sdl_scope();
};

class sdl_image_scope : public internal::base<sdl_image_scope> {
public:
    explicit sdl_image_scope(std::uint32_t flags);
    ~sdl_image_scope();
};

class sdl_mixer_scope : public internal::base<sdl_mixer_scope> {
public:
    explicit sdl_mixer_scope(std::uint32_t flags);
    ~sdl_mixer_scope();
};

// class sdl_net_scope : public internal::base<sdl_net_scope> {
// public:
//     sdl_net_scope();
//     ~sdl_net_scope();
// };

class sdl_ttf_scope : public internal::base<sdl_ttf_scope> {
public:
    sdl_ttf_scope();
    ~sdl_ttf_scope();
};
} // namespace scopes
} // namespace common

#endif
