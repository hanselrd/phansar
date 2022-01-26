#ifndef PHANSAR_COMMON_NETWORK_SOCKET_HPP
#define PHANSAR_COMMON_NETWORK_SOCKET_HPP

#include <phansar/common/utility/pimpl.hpp>
#include <cstdint>
#include <optional>
#include <string_view>
#include <utility>
#include <vector>

namespace phansar::common::network {
class socket {
public:
    enum class type { server, client };
    enum class channel : std::uint8_t { reliable, unreliable, fast, count };

    explicit socket(type _type);
    socket(const socket & _other);
    auto operator=(const socket & _other) -> socket &;
    socket(socket && _other) noexcept;
    auto operator=(socket && _other) noexcept -> socket &;
    virtual ~socket();

    void open(std::uint32_t _host, std::uint16_t _port);
    void open(std::string_view _host, std::uint16_t _port);
    void open(std::uint16_t _port);
    void close();
    void poll(std::uint32_t _timeout = 0);
    void
    send(std::uint16_t _client_id, channel _channel, const std::uint8_t * _ptr, std::size_t _size);
    void broadcast(channel _channel, const std::uint8_t * _ptr, std::size_t _size);
    auto receive(std::uint16_t _client_id, channel _channel)
        -> std::optional<std::vector<std::uint8_t>>;
    auto receive(channel _channel)
        -> std::optional<std::pair<std::uint16_t, std::vector<std::uint8_t>>>;
    [[nodiscard]] auto num_clients() const -> std::size_t;
    [[nodiscard]] auto is_open() const -> bool;
    [[nodiscard]] auto get_type() const -> type;

private:
    void               _open_internal();
    [[nodiscard]] auto _channel_to_packet_flags_internal(channel _channel) const -> std::uint32_t;

    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::network

#endif
