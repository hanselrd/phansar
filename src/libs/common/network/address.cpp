#include "address.hpp"
#include <vector>

namespace common {
namespace network {
address::address(const std::string &host, std::uint16_t port) {
    if (host.empty()) {
        _address.host = ENET_HOST_ANY;
    } else {
        enet_address_set_host(&_address, host.c_str());
    }

    if (port == 0) {
        _address.port = ENET_PORT_ANY;
    } else {
        _address.port = port;
    }
}

address::address(ENetAddress address) : _address(address) {
}

address::operator const ENetAddress *() const {
    return &_address;
}

std::string address::get_host() const {
    std::vector<char> buffer(16, '\0');
    enet_address_get_host_ip(&_address, buffer.data(), buffer.size());
    return std::string(buffer.begin(), buffer.end());
}

std::uint16_t address::get_port() const {
    return _address.port;
}
} // namespace network
} // namespace common
