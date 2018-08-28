#ifndef COMMON_NETWORK_UDP_SOCKET_HPP
#define COMMON_NETWORK_UDP_SOCKET_HPP

#include "../json.hpp"
#include "ip_address.hpp"
#include <SDL2/SDL_net.h>
#include <cstdint>
#include <memory>
#include <string>
#include <tuple>

namespace common {
namespace network {
class udp_socket {
public:
    explicit udp_socket(std::uint16_t port);
    ~udp_socket();
    std::tuple<ip_address, json> receive() const;
    void send(const ip_address &ip, const json &j);

private:
    UDPsocket _socket;
    UDPpacket *_packet;
};
} // namespace network
} // namespace common

#endif
