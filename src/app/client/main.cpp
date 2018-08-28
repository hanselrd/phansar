#include "gui/window.hpp"
#include <SDL2/SDL.h>
#include <common/common.hpp>
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>

using namespace common;
using namespace common::core;

int main(int argc, char *argv[]) {
    try {
        core::log::init("phansar.log");

        scopes::plibsys guard1;
        scopes::sdl guard2(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        scopes::sdl_image guard3(IMG_INIT_PNG);
        scopes::sdl_ttf guard4;
        scopes::enet guard5;

        auto window = SDL_CreateWindow("Phansar [SDL]",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       800,
                                       600,
                                       SDL_WINDOW_SHOWN);
        auto renderer = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            &SDL_DestroyRenderer);
        volatile bool running = true;

        ENetAddress address;
        enet_address_set_host(&address, "localhost");
        address.port = 5000;
        auto client = std::unique_ptr<ENetHost, decltype(&enet_host_destroy)>(
            enet_host_create(nullptr, 1, 2, 57600 / 8, 14400 / 8), &enet_host_destroy);
        auto server = enet_host_connect(client.get(), &address, 2, 0);
        enet_peer_timeout(server, 0, 0, 5000);
        ASSERT(server != nullptr);

        std::ifstream ifs("assets.psar", std::ios::binary);
        auto j = json::from_cbor(ifs);
        auto bytes = codec::base64::decode(j["tilesets"]["rural.png"].get<std::string>());
        LOGI << "rural.png: " << bytes.size() << " B";

        auto rw = SDL_RWFromMem(bytes.data(), bytes.size());
        auto temp = IMG_Load_RW(rw, true);
        auto texture = SDL_CreateTextureFromSurface(renderer.get(), temp);
        SDL_FreeSurface(temp);
#define PADDING (1)
        SDL_Rect src_rect{// gid 6
                          (16 * 5) + (PADDING * 5),
                          (16 * 0) + (PADDING * 0),
                          16,
                          16};
        SDL_Rect box{0, 0, 64, 64};
        auto pos = std::make_pair<double, double>(0., 0.);

        auto gui_window = client::gui::window(SDL_Rect{10, 10, 30, 50});

        std::uint64_t now_time = SDL_GetPerformanceCounter(), last_time = 0;
        double delta_time = 0., fps = 0.;

        json outj;

        dispatch_queue dq(std::thread::hardware_concurrency() - 1);

        // ENet event loop (worker thread)
        dq.dispatch([&] {
            while (running) {
                ENetEvent enet_event;
                while (enet_host_service(client.get(), &enet_event, 1000)) {
                    switch (enet_event.type) {
                    case ENET_EVENT_TYPE_CONNECT:
                        LOGI << "Connected to server: " << std::hex << enet_event.peer->address.host
                             << ":" << std::dec << enet_event.peer->address.port;
                        break;
                    case ENET_EVENT_TYPE_RECEIVE:
                        LOGI << "Received a packet";
                        enet_packet_destroy(enet_event.packet);
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        LOGI << "Disconnected from server";
                        break;
                    default:
                        break;
                    }
                }
            }
        });

        while (running) {
            SDL_Event sdl_event;
            while (SDL_PollEvent(&sdl_event)) {
                switch (sdl_event.type) {
                case SDL_QUIT:
                    running = false;
                    // outj = {{"disconnect", true}};
                    // client.send(server_ip, outj);
                    {
                        std::string message = "disconnect me";
                        auto packet = enet_packet_create(
                            message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
                        enet_peer_send(server, 0, packet);
                        enet_host_flush(client.get());
                    }
                    break;
                default:
                    break;
                }
            }

            last_time = now_time;
            now_time = SDL_GetPerformanceCounter();
            delta_time = static_cast<double>((now_time - last_time)) /
                         static_cast<double>(SDL_GetPerformanceFrequency());
            fps = static_cast<double>(SDL_GetPerformanceFrequency()) /
                  static_cast<double>(now_time - last_time);
            LOGI << "fps: " << static_cast<std::uint32_t>(fps) << " \u0394: " << delta_time;

            auto key_states = SDL_GetKeyboardState(nullptr);
            if (key_states[SDL_SCANCODE_LEFT]) {
                pos.first -= 200 * delta_time;
                // outj = {{"move", {{"left", 200}}}};
                // client.send(server_ip, outj);
            }
            if (key_states[SDL_SCANCODE_UP]) {
                pos.second -= 200 * delta_time;
                // outj = {{"move", {{"up", 200}}}};
                // client.send(server_ip, outj);
            }
            if (key_states[SDL_SCANCODE_RIGHT]) {
                pos.first += 200 * delta_time;
                // outj = {{"move", {{"right", 200}}}};
                // client.send(server_ip, outj);
            }
            if (key_states[SDL_SCANCODE_DOWN]) {
                pos.second += 200 * delta_time;
                // outj = {{"move", {{"down", 200}}}};
                // client.send(server_ip, outj);
            }

            gui_window.update(delta_time);

            SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer.get());
            box.x = pos.first;
            box.y = pos.second;
            SDL_RenderCopy(renderer.get(), texture, &src_rect, &box);
            gui_window.draw(renderer);
            SDL_RenderPresent(renderer.get());
        }

        SDL_DestroyTexture(texture);
        SDL_DestroyWindow(window);

    } catch (...) {
    }

    return 0;
}
