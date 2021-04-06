#include <phansar/common/networking/chat.hpp>

namespace phansar::common::networking {
struct chat::impl {};

chat::chat()
    : bidi_streamable<schema::Service::Chat::Packet>{std::make_shared<
          std::vector<kj::Own<capnp::ReaderFor<schema::Service::Chat::Packet>>>>()} {}

chat::~chat() = default;
} // namespace phansar::common::networking
