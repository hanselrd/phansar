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

#include "graphics/circle/circle.hpp"
#include "graphics/polygon/polygon.hpp"
#include "graphics/rectangle/rectangle.hpp"
#include "graphics/text/text.hpp"
#include "graphics/triangle/triangle.hpp"
#include "managers/input_manager/input_manager.hpp"
#include "managers/resource_manager/resource_manager.hpp"
#include "managers/system_manager/system_manager.hpp"
#include "ui/window/window.hpp"
#include <SDL2/SDL.h>
#include <common/containers/dispatch_queue/dispatch_queue.hpp>
#include <common/containers/event_queue/event_queue.hpp>
#include <common/extlibs/json/json.hpp>
#include <common/network/address/address.hpp>
#include <common/network/socket/socket.hpp>
#include <common/utils/log/log.hpp>
#include <cstdint>
#include <enet/enet.h>
#include <fstream>
#include <memory>
#include <vector>

using namespace client;

int main(int argc, char *argv[]) {
    try {
        managers::system_manager::init();
        managers::resource_manager::init();

        auto window = managers::system_manager::get_window();
        auto renderer = managers::system_manager::get_renderer();

        volatile auto running = bool{true};

        // network::socket client(0, 1, 2, 57600 / 8, 14400 / 8);
        // client.connect(network::address("localhost", 5000));
        // network::socket::peer_id server = 0;

        managers::resource_manager::load<SDL_Surface>("assets/tilesets/rural.png");
        auto surface = managers::resource_manager::get<SDL_Surface>("assets/tilesets/rural.png");
        managers::resource_manager::load<TTF_Font>("assets/fonts/K2D-Bold.ttf", 40);
        auto font = managers::resource_manager::get<TTF_Font>("assets/fonts/K2D-Bold.ttf");
        auto texture = SDL_CreateTextureFromSurface(renderer.get(), surface->get());
#define PADDING (1)
        auto src_rect = SDL_Rect{// gid 6
                                 (16 * 5) + (PADDING * 5),
                                 (16 * 0) + (PADDING * 0),
                                 16,
                                 16};
        auto box = SDL_Rect{0, 0, 64, 64};
        auto pos = std::make_pair<float, float>(0.f, 0.f);

        auto delta_time = float{0.f};
        auto fps = float{0.f};

        auto in_json = common::extlibs::json{};
        auto out_json = common::extlibs::json{};
        auto peer_id = common::network::socket::peer_id{};

        auto dq = managers::system_manager::get_dispatch_queue();

        // ENet event loop (worker thread)
        // dq->dispatch([&] {
        //     while (running) {
        //         while (client.listen(1000)) {
        //             if (client.accept(id)) {
        //                 LOGI << "Hey, connected to server";
        //             }
        //             if (client.receive(id, inj)) {
        //                 LOGI << "Hey, received something from server";
        //             }
        //         }
        //         // ENetEvent enet_event;
        //         // while (enet_host_service(client.get(), &enet_event, 1000)) {
        //         //     switch (enet_event.type) {
        //         //     case ENET_EVENT_TYPE_CONNECT:
        //         //         LOGI << "Connected to server: " << std::hex <<
        //         //         enet_event.peer->address.host
        //         //              << ":" << std::dec << enet_event.peer->address.port;
        //         //         break;
        //         //     case ENET_EVENT_TYPE_RECEIVE:
        //         //         LOGI << "Received a packet";
        //         //         enet_packet_destroy(enet_event.packet);
        //         //         break;
        //         //     case ENET_EVENT_TYPE_DISCONNECT:
        //         //         LOGI << "Disconnected from server";
        //         //         break;
        //         //     default:
        //         //         break;
        //         //     }
        //         // }
        //     }
        // });

        auto eq = common::containers::event_queue<SDL_Event, std::uint32_t>(SDL_QUIT, SDL_KEYDOWN);
        eq.subscribe([](const SDL_Event &e) { LOGD << "Subscriber: event " << e.type; });

        auto ui_window = ui::window{common::components::vec2f{20.f, 20.f},
                                    common::components::vec2u{150, 250},
                                    SDL_Color{0x00, 0x99, 0x99, 0xFF}};

        auto red_rect = graphics::rectangle{common::components::vec2f{200, 50},
                                            common::components::vec2u{100, 100},
                                            common::components::color{0xFF, 0x00, 0x00, 0xBB},
                                            true};

        auto yellow_circle = graphics::circle{common::components::vec2f{200, 100},
                                              200,
                                              common::components::color{0xFF, 0xFF, 0x00, 0xCC},
                                              true};

        auto green_polygon = graphics::polygon{common::components::vec2f{10, 400},
                                               80,
                                               5,
                                               common::components::color{0x00, 0xFF, 0x00, 0xCC},
                                               false};

        auto orange_polygon_filled =
            graphics::polygon{common::components::vec2f{50, 250},
                              160,
                              6,
                              common::components::color{0xFF, 0xA5, 0x00, 0xCC},
                              true};

        auto pink_triangle = graphics::triangle{common::components::vec2f{600, 400},
                                                40,
                                                common::components::color{0xFF, 0x00, 0xFF, 0xCC},
                                                true};

        auto white_text = graphics::text{common::components::vec2f{200, 40},
                                         font->get(),
                                         graphics::text::type::BLENDED,
                                         common::components::color{0xFF, 0xFF, 0xFF, 0xBB}};
        white_text.set_string("Phansar");

        eq.subscribe([&](const SDL_Event &e) {
            switch (e.type) {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                case SDLK_TAB:
                    red_rect.set_filled(!red_rect.get_filled());
                    break;
                case SDLK_o:
                    red_rect.color_shift(common::components::color{0, 0, 0, 1});
                    break;
                }
            }
        });

        while (running) {
            managers::system_manager::update();

            SDL_Event sdl_event;
            while (SDL_PollEvent(&sdl_event)) {
                managers::input_manager::handle_event(sdl_event);
                eq.event(sdl_event, sdl_event.type);

                switch (sdl_event.type) {
                case SDL_QUIT:
                    running = false;
                    // outj = {{"disconnect", true}};
                    // client.send(server, outj);
                    break;
                default:
                    break;
                }
            }

            eq.update();
            ui_window.update();
            delta_time = managers::system_manager::get_delta_time();
            fps = managers::system_manager::get_fps();
            // LOGI << "fps: " << static_cast<std::uint32_t>(fps) << " \u0394: " << delta_time;
            white_text.set_string(std::string{"fps: "} +
                                  std::to_string(static_cast<std::uint32_t>(fps)) +
                                  " dt: " + std::to_string(delta_time));

            auto key_states = managers::input_manager::get_keyboard_state();
            if (key_states[SDL_SCANCODE_LEFT]) {
                red_rect.move(common::components::vec2f{-200 * delta_time, 0});
                // pos.first -= 200 * delta_time;
                // client.send(id, {{"move", {{"left", 200}}}});
            }
            if (key_states[SDL_SCANCODE_UP]) {
                red_rect.move(common::components::vec2f{0, -200 * delta_time});
                // pos.second -= 200 * delta_time;
                // client.send(id, {{"move", {{"up", 200}}}});
            }
            if (key_states[SDL_SCANCODE_RIGHT]) {
                red_rect.move(common::components::vec2f{200 * delta_time, 0});
                // pos.first += 200 * delta_time;
                // client.send(id, {{"move", {{"right", 200}}}});
            }
            if (key_states[SDL_SCANCODE_DOWN]) {
                red_rect.move(common::components::vec2f{0, 200 * delta_time});
                // pos.second += 200 * delta_time;
                // client.send(id, {{"move", {{"down", 200}}}});
            }

            SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer.get());
            box.x = pos.first;
            box.y = pos.second;
            SDL_RenderCopy(renderer.get(), texture, &src_rect, &box);
            white_text.draw();
            ui_window.render();
            yellow_circle.draw();
            green_polygon.draw();
            orange_polygon_filled.draw();
            pink_triangle.draw();
            red_rect.draw();
            SDL_RenderPresent(renderer.get());
        }

        SDL_DestroyTexture(texture);
    } catch (...) {
    }

    return 0;
}
