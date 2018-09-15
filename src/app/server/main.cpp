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

#include <common/common.hpp>
#include <csignal>
#include <memory>

using namespace common;
using namespace common::core;

volatile bool running = true;

int main(int argc, char *argv[]) {
    core::log::init("phansar-server.log");

    scopes::plibsys_scope guard1;
    scopes::enet_scope guard2;

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::string);
    sol::table phansar = lua.create_named_table("phansar");
    common::lua_api::init(phansar);

    lua.script_file("scripts/lua_api/common.lua");
    lua.script_file("scripts/lua_api/server.lua");

    std::signal(SIGINT, [](int signal) { running = false; });

    dispatch_queue dq(3);
    dq.dispatch([] {
        while (running) {
            SDL_Delay(1000);
        }
    });
    for (int i = 0; i < 10; ++i) {
        dq.dispatch([i] {
            LOGI << "[" << i << "]:"
                 << " dispatch";
        });
    }

    // ENetAddress address;
    // address.host = ENET_HOST_ANY;
    // address.port = 5000;

    network::socket server(5000, 64, 2);

    // auto server = std::unique_ptr<ENetHost, decltype(&enet_host_destroy)>(
    //     enet_host_create(address, 64, 2, 0, 0), &enet_host_destroy);

    network::socket::peer_id id;
    core::json j;

    while (running) {
        // accept all peer connections
        while (server.accept(id)) {
        }

        while (server.listen(1000)) {
            if (server.receive(id, j)) {
                // LOGI << "Hey, I received something from peer: " << id;
                j["peer"] = id;
                server.broadcast(j);
            }
        }

        // ENetEvent event;
        // while (enet_host_service(server.get(), &event, 1000)) {
        //     switch (event.type) {
        //     case ENET_EVENT_TYPE_CONNECT: {
        //         network::address tmp(event.peer->address);
        //         LOGI << "Client connected: " << tmp.get_host() << ":" << tmp.get_port();
        //     }
        //         event.peer->data = *reinterpret_cast<enet_uint16 **>(&event.peer->address.port);
        //         break;
        //     case ENET_EVENT_TYPE_RECEIVE:
        //         dq.dispatch([=] {
        //             LOGI << "Received a packet: " << reinterpret_cast<char
        //             *>(event.packet->data); enet_packet_destroy(event.packet);
        //         });
        //         break;
        //     case ENET_EVENT_TYPE_DISCONNECT: {
        //         network::address tmp(event.peer->address);
        //         LOGI << "Client disconnected: " << tmp.get_host() << ":" << tmp.get_port();
        //     }
        //         event.peer->data = nullptr;
        //         break;
        //     default:
        //         break;
        //     }
        // }
    }

    return 0;
}
