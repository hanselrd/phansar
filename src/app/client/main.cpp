#include "managers/input_manager.hpp"
#include "managers/system_manager.hpp"
#include <SDL2/SDL.h>
#include <common/common.hpp>
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>

using namespace common;
using namespace common::core;
using namespace client;

int main(int argc, char *argv[]) {
    try {
        managers::system_manager::init();

        auto window = managers::system_manager::get_window();
        auto renderer = managers::system_manager::get_renderer();

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
        auto pos = std::make_pair<float, float>(0.f, 0.f);

        float delta_time = 0.f, fps = 0.f;

        json outj;

        auto dq = managers::system_manager::get_dispatch_queue();

        // ENet event loop (worker thread)
        dq->dispatch([&] {
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
            managers::system_manager::update();

            SDL_Event sdl_event;
            while (SDL_PollEvent(&sdl_event)) {
                managers::input_manager::handle_event(sdl_event);
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

            delta_time = managers::system_manager::get_delta_time();
            fps = managers::system_manager::get_fps();
            LOGI << "fps: " << static_cast<std::uint32_t>(fps) << " \u0394: " << delta_time;

            auto key_states = managers::input_manager::get_keyboard_state();
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

            SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer.get());
            box.x = pos.first;
            box.y = pos.second;
            SDL_RenderCopy(renderer.get(), texture, &src_rect, &box);
            SDL_RenderPresent(renderer.get());
        }

        SDL_DestroyTexture(texture);
    } catch (...) {
    }

    return 0;
}
