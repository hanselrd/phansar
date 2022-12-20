#include <phansar/common/macro.hpp>
#include <phansar/common/network/socket.hpp>
#include <enet/enet.h>
#include <queue>
#include <unordered_map>

namespace phansar::common::network {
struct socket::impl {
  socket::type                                  type{};
  ENetAddress                                   address{};
  ENetHost *                                    host{};
  std::unordered_map<std::uint16_t, ENetPeer *> peers{};
  std::unordered_map<
      channel,
      std::queue<std::pair<std::uint16_t, std::vector<std::uint8_t>>>>
      queues{};
};

socket::socket(type _type) : m_impl{_type} {}

socket::socket(socket const & _other)                         = default;

auto socket::operator=(socket const & _other) -> socket &     = default;

socket::socket(socket && _other) noexcept                     = default;

auto socket::operator=(socket && _other) noexcept -> socket & = default;

socket::~socket()                                             = default;

void socket::open(std::uint32_t _host, std::uint16_t _port) {
  m_impl->address.host = _host;
  m_impl->address.port = _port;

  _open_internal();
}

void socket::open(std::string_view _host, std::uint16_t _port) {
  auto host = std::string{_host};
  enet_address_set_host(&m_impl->address, host.c_str());
  m_impl->address.port = _port;

  _open_internal();
}

void socket::open(std::uint16_t _port) {
  m_impl->address.host = ENET_HOST_ANY;
  m_impl->address.port = _port;

  _open_internal();
}

void socket::close() {
  if (! is_open()) {
    return;
  }

  if (get_type() == type::server) {
    for (auto & [id, peer] : m_impl->peers) {
      PH_LOG_DEBUG("Sending disconnect event to client {}", id);
      enet_peer_disconnect(peer, 0);
    }
  }

  poll(5000);

  for (auto & [id, peer] : m_impl->peers) {
    PH_LOG_DEBUG("Forcibly disconnecting client {}", id);
    enet_peer_reset(peer);
  }

  m_impl->peers.clear();

  enet_host_destroy(m_impl->host);
  m_impl->host = nullptr;
}

void socket::poll(std::uint32_t _timeout) {
  auto event = ENetEvent{};

  while (enet_host_service(m_impl->host, &event, _timeout) > 0) {
    switch (event.type) {
    case ENET_EVENT_TYPE_CONNECT:
      if (get_type() == type::server) {
        PH_LOG_DEBUG("Client {} connected", event.peer->incomingPeerID);
      } else {
        PH_LOG_DEBUG("Connected to server");
      }

      m_impl->peers.insert_or_assign(event.peer->incomingPeerID, event.peer);

      break;
    case ENET_EVENT_TYPE_DISCONNECT:
      if (get_type() == type::server) {
        PH_LOG_DEBUG("Client {} disconnected successfully, {} remaining",
                     event.peer->incomingPeerID,
                     m_impl->peers.size() - 1);
      } else {
        PH_LOG_DEBUG("Disconnected from server successfully");
      }

      event.peer->data = nullptr;

      m_impl->peers.erase(event.peer->incomingPeerID);

      break;
    case ENET_EVENT_TYPE_RECEIVE:
      if (get_type() == type::server) {
        PH_LOG_DEBUG(
            "Received packet from client {} on channel {} [{} @ {} byte(s)]",
            event.peer->incomingPeerID,
            event.channelID,
            static_cast<void *>(event.packet->data),
            event.packet->dataLength);
      } else {
        PH_LOG_DEBUG(
            "Received packet from server on channel {} [{} @ {} byte(s)]",
            event.channelID,
            static_cast<void *>(event.packet->data),
            event.packet->dataLength);
      }

      m_impl->queues[static_cast<channel>(event.channelID)].push(
          std::make_pair(event.peer->incomingPeerID,
                         std::vector<std::uint8_t>{
                             event.packet->data,
                             event.packet->data + event.packet->dataLength}));

      enet_packet_destroy(event.packet);

      break;
    default:
      break;
    }
  }
}

void socket::send(std::uint16_t        _client_id,
                  channel              _channel,
                  std::uint8_t const * _ptr,
                  std::size_t          _size) {
  PH_ASSERT(m_impl->host);
  PH_ASSERT(m_impl->peers.contains(_client_id));

  auto * peer   = m_impl->peers.at(_client_id);

  auto * packet = enet_packet_create(
      _ptr, _size, _channel_to_packet_flags_internal(_channel));

  enet_peer_send(
      peer, static_cast<std::underlying_type_t<channel>>(_channel), packet);
  enet_host_flush(m_impl->host);
}

void socket::broadcast(channel              _channel,
                       std::uint8_t const * _ptr,
                       std::size_t          _size) {
  PH_ASSERT(m_impl->host);
  PH_ASSERT(m_impl->peers.empty() == false);

  auto * packet = enet_packet_create(
      _ptr, _size, _channel_to_packet_flags_internal(_channel));

  enet_host_broadcast(m_impl->host,
                      static_cast<std::underlying_type_t<channel>>(_channel),
                      packet);
  enet_host_flush(m_impl->host);
}

auto socket::receive(std::uint16_t _client_id, channel _channel)
    -> std::optional<std::vector<std::uint8_t>> {
  if (m_impl->queues[_channel].empty()) {
    return std::nullopt;
  }

  if (auto const & [client_id, data] = m_impl->queues[_channel].front();
      client_id == _client_id) {
    m_impl->queues[_channel].pop();

    return data;
  }

  return std::nullopt;
}

auto socket::receive(channel _channel)
    -> std::optional<std::pair<std::uint16_t, std::vector<std::uint8_t>>> {
  if (m_impl->queues[_channel].empty()) {
    return std::nullopt;
  }

  auto tagged_data = m_impl->queues[_channel].front();
  m_impl->queues[_channel].pop();

  return tagged_data;
}

auto socket::num_clients() const -> std::size_t {
  return m_impl->peers.size();
}

auto socket::is_open() const -> bool {
  return m_impl->host != nullptr;
}

auto socket::get_type() const -> type {
  return m_impl->type;
}

void socket::_open_internal() {
  m_impl->host = enet_host_create(
      (get_type() == type::server) ? &m_impl->address : nullptr,
      (get_type() == type::server) ? 1024 : 1,
      static_cast<std::underlying_type_t<channel>>(channel::count),
      0,
      0);
  PH_ASSERT(m_impl->host);

  if (get_type() == type::client) {
    auto * peer = enet_host_connect(
        m_impl->host,
        &m_impl->address,
        static_cast<std::underlying_type_t<channel>>(channel::count),
        0);
    PH_ASSERT(peer);

    m_impl->peers.insert_or_assign(0, peer);
  }

  poll(5000);
}

auto socket::_channel_to_packet_flags_internal(channel _channel) const
    -> std::uint32_t {
  std::uint32_t flags = 0;

  switch (_channel) {
  case channel::reliable:
    flags |= ENET_PACKET_FLAG_RELIABLE;
    break;
  case channel::unreliable:
  case channel::fast:
    flags |= ENET_PACKET_FLAG_UNSEQUENCED;
    break;
  default:
    break;
  }

  return flags;
}
} // namespace phansar::common::network
