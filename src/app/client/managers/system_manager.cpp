/**
 * This file is part of Phansar.
 *
 * Copyright (C) 2018  Hansel De La Cruz
 *
 * Phansar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phansar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "system_manager.hpp"
#include <common/core/assert.hpp>
#include <common/core/log.hpp>
#include <common/scopes/scopes.hpp>
#include <cstdint>
#include <cstdlib>

namespace client {
namespace managers {
namespace system_manager {
namespace {
std::unique_ptr<common::scopes::plibsys_scope> plibsys_guard;
std::unique_ptr<common::scopes::sdl_scope> sdl_guard;
std::unique_ptr<common::scopes::sdl_image_scope> sdl_image_guard;
std::unique_ptr<common::scopes::sdl_mixer_scope> sdl_mixer_guard;
std::unique_ptr<common::scopes::sdl_ttf_scope> sdl_ttf_guard;
std::unique_ptr<common::scopes::enet_scope> enet_guard;

std::shared_ptr<common::core::dispatch_queue> dq;

std::shared_ptr<SDL_Window> window;
std::shared_ptr<SDL_Renderer> renderer;

std::uint64_t now_time = 0;
std::uint64_t last_time = 0;
float delta_time = 0.f;
float fps = 0.f;
} // namespace

void init() {
    ASSERT(!plibsys_guard && !sdl_guard && !sdl_image_guard && !sdl_mixer_guard && !sdl_ttf_guard &&
           !enet_guard && !dq && !window && !renderer);

    common::core::log::init("phansar.log");

    plibsys_guard = std::make_unique<common::scopes::plibsys_scope>();
    sdl_guard = std::make_unique<common::scopes::sdl_scope>(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    sdl_image_guard = std::make_unique<common::scopes::sdl_image_scope>(IMG_INIT_PNG);
    sdl_mixer_guard = std::make_unique<common::scopes::sdl_mixer_scope>(MIX_INIT_OGG);
    sdl_ttf_guard = std::make_unique<common::scopes::sdl_ttf_scope>();
    enet_guard = std::make_unique<common::scopes::enet_scope>();

    dq = std::make_shared<common::core::dispatch_queue>(std::thread::hardware_concurrency() - 1);
    ASSERT_ALWAYS(dq);

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

    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);

    now_time = SDL_GetPerformanceCounter();

    std::atexit([] {
        renderer.reset();
        window.reset();

        dq.reset();

        enet_guard.reset();
        sdl_ttf_guard.reset();
        sdl_mixer_guard.reset();
        sdl_image_guard.reset();
        sdl_guard.reset();
        plibsys_guard.reset();
    });
}

std::shared_ptr<common::core::dispatch_queue> get_dispatch_queue() {
    ASSERT(dq);
    return dq;
}

std::shared_ptr<SDL_Window> get_window() {
    ASSERT(window);
    return window;
}

std::shared_ptr<SDL_Renderer> get_renderer() {
    ASSERT(renderer);
    return renderer;
}

void update() {
    last_time = now_time;
    now_time = SDL_GetPerformanceCounter();
    delta_time = static_cast<float>(now_time - last_time) /
                 static_cast<float>(SDL_GetPerformanceFrequency());
    fps = 1.f / delta_time;
}

float get_delta_time() {
    return delta_time;
}

float get_fps() {
    return fps;
}
} // namespace system_manager
} // namespace managers
} // namespace client
