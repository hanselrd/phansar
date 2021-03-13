#ifndef PHANSAR_COMMON_NETWORKING_CHAT_HPP
#define PHANSAR_COMMON_NETWORKING_CHAT_HPP

#include <phansar.capnp.h>
#include <phansar/common/networking/bidi_streamable.hpp>

namespace phansar::common::networking {
class chat : public schema::Service::Chat::Server,
             public bidi_streamable<schema::Service::Chat::Packet> {
public:
    chat();
    virtual ~chat() = default;
};
} // namespace phansar::common::networking

#endif
