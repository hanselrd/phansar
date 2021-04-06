#ifndef PHANSAR_COMMON_NETWORKING_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_SESSION_HPP

#include <phansar.capnp.h>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::networking {
class session : public virtual schema::Service::Session::Server {
public:
    session();
    session(const session &) = default;
    auto operator=(const session &) -> session & = default;
    session(session &&)                          = default;
    auto operator=(session &&) -> session & = default;
    virtual ~session();

    auto globalChat(GlobalChatContext _context) -> kj::Promise<void> override;
    auto logout(LogoutContext _context) -> kj::Promise<void> override;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::networking

#endif
