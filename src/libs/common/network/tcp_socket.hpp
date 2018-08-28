#ifndef COMMON_NETWORK_TCP_SOCKET_HPP
#define COMMON_NETWORK_TCP_SOCKET_HPP

#include "../json.hpp"
#include "ip_address.hpp"
#include <SDL2/SDL_net.h>
#include <cstdint>
#include <memory>
#include <string>

namespace common {
namespace network {
class tcp_socket {
public:
    explicit tcp_socket(const std::string &ip, std::uint16_t port);
    explicit tcp_socket(TCPsocket socket);
    ~tcp_socket();
    tcp_socket accept();
    json receive() const;
    void send(const json &j);
    ip_address remote_address() const;
    bool valid() const;

private:
    TCPsocket _socket;
};
} // namespace network
} // namespace common

#endif
