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

#ifndef LIBS_COMMON_NETWORK_SOCKET_SOCKET_HPP
#define LIBS_COMMON_NETWORK_SOCKET_SOCKET_HPP

#include "../../vendor/json/json.hpp"
#include "../address/address.hpp"
#include <cstdint>
#include <enet/enet.h>
#include <map>
#include <memory>
#include <queue>
#include <string>

namespace common {
namespace network {
class socket {
public:
    using peer_id = std::uint16_t;
    using packet_flags = std::uint8_t;

    explicit socket(std::uint16_t port,
                    std::size_t peer_count,
                    std::size_t channel_limit,
                    std::uint32_t incoming_bandwidth = 0,
                    std::uint32_t outgoing_bandwidth = 0);
    ~socket();

    void connect(const address &addr, std::uint32_t connection_data = 0);
    bool listen(std::uint32_t timeout);
    ENetPeer *get_peer(peer_id id) const;
    bool accept(peer_id &id);
    void broadcast(const vendor::json &val, packet_flags flags = ENET_PACKET_FLAG_RELIABLE);
    void send(peer_id id, const vendor::json &val, packet_flags flags = ENET_PACKET_FLAG_RELIABLE);
    bool receive(peer_id &id, vendor::json &val);
    void disconnect(peer_id id, bool force = false, std::uint32_t disconnection_data = 0);

private:
    std::unique_ptr<ENetHost, decltype(&enet_host_destroy)> _host;
    std::map<peer_id, ENetPeer *> _peers;
    std::queue<ENetPeer *> _connect_queue;
    using packet_ptr = std::unique_ptr<ENetPacket, decltype(&enet_packet_destroy)>;
    std::queue<std::pair<peer_id, packet_ptr>> _receive_queue;
    std::queue<peer_id> _disconnect_queue;
};
} // namespace network
} // namespace common

#endif
