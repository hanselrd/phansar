#include "ip_address.hpp"
#include "../serialize.hpp"
#include <sstream>

namespace common {
namespace network {
ip_address::ip_address(const std::string &host, std::uint16_t port) {
    if (host.empty()) {
        SDLNet_ResolveHost(&_ip, nullptr, port);
    } else {
        SDLNet_ResolveHost(&_ip, host.c_str(), port);
    }
}

ip_address::ip_address(IPaddress ip) : _ip(ip) {
}

std::string ip_address::get_host() const {
    auto parts = reinterpret_cast<const std::uint8_t *>(&_ip.host);
    std::ostringstream oss;
    oss << static_cast<std::uint32_t>(parts[0]) << "." << static_cast<std::uint32_t>(parts[1])
        << "." << static_cast<std::uint32_t>(parts[2]) << "."
        << static_cast<std::uint32_t>(parts[3]);
    return oss.str();
}

std::uint16_t ip_address::get_port() const {
    return serialize::ntoh16(_ip.port);
}

IPaddress ip_address::get_raw() const {
    return _ip;
}
} // namespace network
} // namespace common
