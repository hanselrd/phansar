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
#include <common/scopes/enet_scope/enet_scope.hpp>
#include <common/scopes/plibsys_scope/plibsys_scope.hpp>
#include <common/scopes/sdl_scope/sdl_scope.hpp>
#include <common/utils/assert/assert.hpp>
#include <common/utils/log/log.hpp>
#include <cstdint>
#include <cstdlib>

namespace client {
namespace managers {
namespace system_manager {
namespace {
auto _plibsys_guard = std::unique_ptr<common::scopes::plibsys_scope>{};
auto _sdl_guard = std::unique_ptr<common::scopes::sdl_scope>{};
auto _sdl_image_guard = std::unique_ptr<common::scopes::sdl_image_scope>{};
auto _sdl_mixer_guard = std::unique_ptr<common::scopes::sdl_mixer_scope>{};
auto _sdl_ttf_guard = std::unique_ptr<common::scopes::sdl_ttf_scope>{};
auto _enet_guard = std::unique_ptr<common::scopes::enet_scope>{};
auto _dq = std::shared_ptr<common::containers::dispatch_queue>{};
auto _window = std::shared_ptr<SDL_Window>{};
auto _renderer = std::shared_ptr<SDL_Renderer>{};
auto _now_time = std::uint64_t{0};
auto _last_time = std::uint64_t{0};
auto _delta_time = float{0.f};
auto _fps = float{0.f};
} // namespace

void init() {
    ASSERT(!_plibsys_guard && !_sdl_guard && !_sdl_image_guard && !_sdl_mixer_guard &&
           !_sdl_ttf_guard && !_enet_guard && !_dq && !_window && !_renderer);

    common::utils::log::init("phansar.log");

    _plibsys_guard = std::make_unique<common::scopes::plibsys_scope>();
    _sdl_guard = std::make_unique<common::scopes::sdl_scope>(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    _sdl_image_guard = std::make_unique<common::scopes::sdl_image_scope>(IMG_INIT_PNG);
    _sdl_mixer_guard = std::make_unique<common::scopes::sdl_mixer_scope>(MIX_INIT_OGG);
    _sdl_ttf_guard = std::make_unique<common::scopes::sdl_ttf_scope>();
    _enet_guard = std::make_unique<common::scopes::enet_scope>();

    _dq = std::make_shared<common::containers::dispatch_queue>(std::thread::hardware_concurrency() -
                                                               1);
    ASSERT_ALWAYS(_dq);

    _window = std::shared_ptr<SDL_Window>{
        SDL_CreateWindow(
            "Phansar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN),
        &SDL_DestroyWindow};
    MASSERT_ALWAYS(_window, SDL_GetError());

    _renderer = std::shared_ptr<SDL_Renderer>{
        SDL_CreateRenderer(
            _window.get(), -1, SDL_RENDERER_ACCELERATED /* | SDL_RENDERER_PRESENTVSYNC*/),
        &SDL_DestroyRenderer};
    MASSERT_ALWAYS(_renderer, SDL_GetError());

    SDL_SetRenderDrawBlendMode(_renderer.get(), SDL_BLENDMODE_BLEND);

    _now_time = SDL_GetPerformanceCounter();

    std::atexit([] {
        _renderer.reset();
        _window.reset();
        _dq.reset();
        _enet_guard.reset();
        _sdl_ttf_guard.reset();
        _sdl_mixer_guard.reset();
        _sdl_image_guard.reset();
        _sdl_guard.reset();
        _plibsys_guard.reset();
    });
    LOGI << "System manager initialized";
}

void update() {
    _last_time = _now_time;
    _now_time = SDL_GetPerformanceCounter();
    _delta_time = static_cast<float>(_now_time - _last_time) /
                  static_cast<float>(SDL_GetPerformanceFrequency());
    _fps = 1.f / _delta_time;

    ASSERT(_window);
    SDL_SetWindowTitle(
        _window.get(),
        ("Phansar | " + std::to_string(_fps) + " [" + std::to_string(_delta_time) + "]").c_str());
}

std::shared_ptr<common::containers::dispatch_queue> get_dispatch_queue() {
    ASSERT(_dq);
    return _dq;
}

std::shared_ptr<SDL_Window> get_window() {
    ASSERT(_window);
    return _window;
}

std::shared_ptr<SDL_Renderer> get_renderer() {
    ASSERT(_renderer);
    return _renderer;
}

float get_delta_time() {
    return _delta_time;
}

float get_fps() {
    return _fps;
}
} // namespace system_manager
} // namespace managers
} // namespace client
