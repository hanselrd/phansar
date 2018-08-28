#ifndef COMMON_NETWORK_IP_ADDRESS_HPP
#define COMMON_NETWORK_IP_ADDRESS_HPP

#include <SDL2/SDL_net.h>
#include <cstdint>
#include <string>

namespace common {
namespace network {
class ip_address {
public:
    ip_address() = default;
    explicit ip_address(const std::string &host, std::uint16_t port);
    explicit ip_address(IPaddress ip);
    std::string get_host() const;
    std::uint16_t get_port() const;
    IPaddress get_raw() const;

private:
    IPaddress _ip;
};
} // namespace network
} // namespace common

#endif
