#ifndef COMMON_NETWORK_ADDRESS_HPP
#define COMMON_NETWORK_ADDRESS_HPP

#include <cstdint>
#include <enet/enet.h>
#include <string>

namespace common {
namespace network {
class address {
public:
    address() = default;
    explicit address(const std::string &host, std::uint16_t port);
    explicit address(ENetAddress address);

    operator const ENetAddress *() const;
    std::string get_host() const;
    std::uint16_t get_port() const;

private:
    ENetAddress _address;
};
} // namespace network
} // namespace common

#endif
