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
class sdl : private internal::base<sdl> {
public:
    explicit sdl(std::uint32_t flags);
    ~sdl();
};

class sdl_image : private internal::base<sdl_image> {
public:
    explicit sdl_image(std::uint32_t flags);
    ~sdl_image();
};

class sdl_mixer : private internal::base<sdl_mixer> {
public:
    explicit sdl_mixer(std::uint32_t flags);
    ~sdl_mixer();
};

// class sdl_net : private internal::base<sdl_net> {
// public:
//     sdl_net();
//     ~sdl_net();
// };

class sdl_ttf : private internal::base<sdl_ttf> {
public:
    sdl_ttf();
    ~sdl_ttf();
};
} // namespace scopes
} // namespace common

#endif
