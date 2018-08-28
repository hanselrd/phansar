#include "tcp_socket.hpp"
#include "../codec.hpp"
#include <iomanip>
#include <sstream>
#include <vector>

namespace common {
namespace network {
tcp_socket::tcp_socket(const std::string &host, std::uint16_t port) {
    IPaddress ip;
    if (host.empty()) {
        SDLNet_ResolveHost(&ip, nullptr, port);
    } else {
        SDLNet_ResolveHost(&ip, host.c_str(), port);
    }

    _socket = SDLNet_TCP_Open(&ip);
}

tcp_socket::tcp_socket(TCPsocket socket) : _socket(socket) {
}

tcp_socket::~tcp_socket() {
    SDLNet_TCP_Close(_socket);
}

tcp_socket tcp_socket::accept() {
    return tcp_socket(SDLNet_TCP_Accept(_socket));
}

json tcp_socket::receive() const {
    std::vector<std::uint8_t> buffer;

    buffer.resize(8);
    std::size_t bytes_read = 0;
    do {
        bytes_read +=
            SDLNet_TCP_Recv(_socket, buffer.data() + bytes_read, buffer.size() - bytes_read);
    } while (bytes_read != buffer.size());

    std::stringstream ss;
    ss << std::string(buffer.begin(), buffer.end());
    std::uint64_t size;
    ss >> std::hex >> size;

    buffer.resize(size);
    bytes_read = 0;
    do {
        bytes_read +=
            SDLNet_TCP_Recv(_socket, buffer.data() + bytes_read, buffer.size() - bytes_read);
    } while (bytes_read != buffer.size());

    auto encoded = std::string(buffer.begin(), buffer.end());
    auto decoded = codec::base64::decode(encoded);
    return json::from_cbor(decoded);
}

void tcp_socket::send(const json &j) {
    auto cbor = json::to_cbor(j);
    auto encoded = codec::base64::encode(cbor);

    std::stringstream ss;
    ss << std::setw(8) << std::hex << encoded.size() << encoded;

    std::size_t bytes_written = 0;
    do {
        bytes_written += SDLNet_TCP_Send(
            _socket, ss.str().c_str() + bytes_written, ss.str().size() - bytes_written);
    } while (bytes_written != ss.str().size());
}

ip_address tcp_socket::remote_address() const {
    return ip_address(*SDLNet_TCP_GetPeerAddress(_socket));
}

bool tcp_socket::valid() const {
    return _socket != nullptr;
}
} // namespace network
} // namespace common
