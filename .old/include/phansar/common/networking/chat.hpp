#ifndef PHANSAR_COMMON_NETWORKING_CHAT_HPP
#define PHANSAR_COMMON_NETWORKING_CHAT_HPP

#include <phansar.capnp.h>
#include <phansar/common/networking/bidi_streamable.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::networking {
class chat : public schema::Service::Chat::Server,
             public bidi_streamable<schema::Service::Chat::Packet> {
public:
    chat();
    chat(const chat &) = default;
    auto operator=(const chat &) -> chat & = default;
    chat(chat &&)                          = default;
    auto operator=(chat &&) -> chat & = default;
    virtual ~chat();

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::networking

#endif
