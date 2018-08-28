#include "udp_socket.hpp"
#include "../codec.hpp"
#include <iomanip>
#include <numeric>
#include <sstream>
#include <vector>

namespace common {
namespace network {
udp_socket::udp_socket(std::uint16_t port) {
    _socket = SDLNet_UDP_Open(port);
    _packet = SDLNet_AllocPacket(std::numeric_limits<std::uint16_t>::max());
}

udp_socket::~udp_socket() {
    SDLNet_FreePacket(_packet);
    SDLNet_UDP_Close(_socket);
}

std::tuple<ip_address, json> udp_socket::receive() const {
    if (!SDLNet_UDP_Recv(_socket, _packet)) {
        return std::make_tuple(ip_address(), json());
    }

    auto encoded = std::string(_packet->data, _packet->data + _packet->len);
    auto decoded = codec::base64::decode(encoded);

    return std::make_tuple(ip_address(_packet->address), json::from_cbor(decoded));
}

void udp_socket::send(const ip_address &ip, const json &j) {
    auto cbor = json::to_cbor(j);
    auto encoded = codec::base64::encode(cbor);

    std::vector<std::uint8_t> bytes(encoded.begin(), encoded.end());

    _packet->address = ip.get_raw();
    _packet->data = bytes.data();
    _packet->len = bytes.size();

    SDLNet_UDP_Send(_socket, -1, _packet);
}
} // namespace network
} // namespace common
