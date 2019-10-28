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

#include <common/containers/dispatch_queue/dispatch_queue.hpp>
#include <common/extlibs/json/json.hpp>
#include <common/extlibs/sol/sol.hpp>
#include <common/lua_api/lua_api.hpp>
#include <common/network/address/address.hpp>
#include <common/network/socket/socket.hpp>
#include <common/scopes/enet_scope/enet_scope.hpp>
#include <common/utils/log/log.hpp>
#include <csignal>

volatile auto running = bool{true};

int main(int argc, char *argv[]) {
    common::utils::log::init("phansar-server.log");

    auto guard = common::scopes::enet_scope{};

    auto lua = sol::state{};
    lua.open_libraries(sol::lib::base, sol::lib::string);
    auto phansar = lua.create_named_table("phansar");
    lua_api::init_common(phansar);

    lua.script_file("scripts/lua_api/common.lua");
    lua.script_file("scripts/lua_api/server.lua");

    std::signal(SIGINT, [](int signal) { running = false; });

    auto dq = common::containers::dispatch_queue{3};
    dq.dispatch([] {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
    });
    for (auto i = std::uint32_t{0}; i < 10; ++i) {
        dq.dispatch([i] {
            LOGI << "[" << i << "]:"
                 << " dispatch";
        });
    }

    // ENetAddress address;
    // address.host = ENET_HOST_ANY;
    // address.port = 5000;

    auto server = common::network::socket{5000, 64, 2};

    // auto server = std::unique_ptr<ENetHost, decltype(&enet_host_destroy)>(
    //     enet_host_create(address, 64, 2, 0, 0), &enet_host_destroy);

    auto id = common::network::socket::peer_id{};
    auto json = common::extlibs::json{};

    while (running) {
        // accept all peer connections
        while (server.accept(id)) {
        }

        while (server.listen(1000)) {
            if (server.receive(id, json)) {
                // LOGI << "Hey, I received something from peer: " << id;
                json["peer"] = id;
                server.broadcast(json);
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
