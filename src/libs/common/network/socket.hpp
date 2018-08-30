#ifndef COMMON_NETWORK_SOCKET_HPP
#define COMMON_NETWORK_SOCKET_HPP

#include "../core/json.hpp"
#include "address.hpp"
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
    void broadcast(const core::json &val, packet_flags flags = ENET_PACKET_FLAG_RELIABLE);
    void send(peer_id id, const core::json &val, packet_flags flags = ENET_PACKET_FLAG_RELIABLE);
    bool receive(peer_id &id, core::json &val);
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
