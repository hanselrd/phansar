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

#include "socket.hpp"
#include "../../utils/assert/assert.hpp"
#include "../../utils/log/log.hpp"
#include "../../vendor/codec/codec.hpp"
#include <vector>

namespace common {
namespace network {
socket::socket(std::uint16_t port,
               std::size_t peer_count,
               std::size_t channel_limit,
               std::uint32_t incoming_bandwidth,
               std::uint32_t outgoing_bandwidth)
    : _host{nullptr, &enet_host_destroy} {
    address addr{"", port};
    _host = decltype(_host)(
        enet_host_create(addr, peer_count, channel_limit, incoming_bandwidth, outgoing_bandwidth),
        &enet_host_destroy);
}

socket::~socket() {
    ASSERT(_host);
    auto event = ENetEvent{};
    // send pending packets
    enet_host_service(_host.get(), &event, 1000);
    for (auto i = std::size_t{0}; i < _host->peerCount; ++i) {
        enet_peer_disconnect(&_host->peers[i], 0);
    }
}

void socket::connect(const address &addr, std::uint32_t connection_data) {
    ASSERT(_host);
    auto peer = enet_host_connect(_host.get(), addr, 2, connection_data);
    ASSERT(peer);
}

bool socket::listen(std::uint32_t timeout) {
    ASSERT(_host);
    auto event = ENetEvent{};
    auto ret = enet_host_service(_host.get(), &event, timeout);
    if (ret <= 0) {
        return false;
    }

    switch (event.type) {
    case ENET_EVENT_TYPE_CONNECT:
        event.peer->data = nullptr;
        _connect_queue.push(event.peer);
        LOGD("Peer {} connected", event.peer->incomingPeerID);
        break;
    case ENET_EVENT_TYPE_RECEIVE:
        // filter packets from peers waiting to be accepted
        if (_peers.count(event.peer->incomingPeerID) == 0) {
            break;
        }
        _receive_queue.emplace(event.peer->incomingPeerID,
                               packet_ptr{event.packet, &enet_packet_destroy});
        LOGD("Peer {} sent a packet", event.peer->incomingPeerID);
        break;
    case ENET_EVENT_TYPE_DISCONNECT:
        _disconnect_queue.push(event.peer->incomingPeerID);
        _peers.erase(event.peer->incomingPeerID);
        event.peer->data = nullptr;
        LOGD("Peer {} disconnected", event.peer->incomingPeerID);
        break;
    default:
        break;
    }

    return true;
}

ENetPeer *socket::get_peer(peer_id id) const {
    ASSERT(_host);
    auto it = _peers.find(id);
    if (it == _peers.end()) {
        return nullptr;
    }
    return it->second;
}

bool socket::accept(peer_id &id) {
    ASSERT(_host);
    if (_connect_queue.empty()) {
        return false;
    }
    auto peer = _connect_queue.front();
    _connect_queue.pop();
    id = peer->incomingPeerID;
    _peers[peer->incomingPeerID] = peer;
    return true;
}

void socket::broadcast(const vendor::json &val, packet_flags flags) {
    ASSERT(_host);
    auto cbor = vendor::json::to_cbor(val);
    auto encoded = vendor::codec::base64::encode(cbor);
    auto packet = enet_packet_create(encoded.c_str(), encoded.size() + 1, flags);
    auto channel = std::uint8_t{0};
    if (flags & ENET_PACKET_FLAG_RELIABLE) {
        channel = 1;
    } else if (flags & ENET_PACKET_FLAG_UNSEQUENCED) {
        channel = 2;
    }
    enet_host_broadcast(_host.get(), channel, packet);
    LOGD("Broadcasted {} to all peers", val.dump());
}

void socket::send(peer_id id, const vendor::json &val, packet_flags flags) {
    ASSERT(_host);
    auto peer = get_peer(id);
    ASSERT(peer != nullptr);
    auto cbor = vendor::json::to_cbor(val);
    auto encoded = vendor::codec::base64::encode(cbor);
    auto packet = enet_packet_create(encoded.c_str(), encoded.size() + 1, flags);
    auto channel = std::uint8_t{0};
    if (flags & ENET_PACKET_FLAG_RELIABLE) {
        channel = 1;
    } else if (flags & ENET_PACKET_FLAG_UNSEQUENCED) {
        channel = 2;
    }
    enet_peer_send(peer, channel, packet);
    LOGD("Sent {} to peer {}", val.dump(), id);
}

bool socket::receive(peer_id &id, vendor::json &val) {
    ASSERT(_host);
    if (_receive_queue.empty()) {
        return false;
    }
    auto packet = std::move(_receive_queue.front());
    _receive_queue.pop();
    id = packet.first;
    try {
        auto encoded =
            std::string(packet.second->data, packet.second->data + packet.second->dataLength);
        auto decoded = vendor::codec::base64::decode(encoded);
        val = vendor::json::from_cbor(decoded);
        LOGD("Received {} from peer {}", val.dump(), id);
        return true;
    } catch (...) {
        return false;
    }
}

void socket::disconnect(peer_id id, bool force, std::uint32_t disconnection_data) {
    ASSERT(_host);
    auto peer = get_peer(id);
    ASSERT(peer != nullptr);
    if (force) {
        enet_peer_disconnect_now(peer, disconnection_data);
        _disconnect_queue.push(id);
        _peers.erase(id);
    } else {
        enet_peer_disconnect(peer, disconnection_data);
    }
}
} // namespace network
} // namespace common
