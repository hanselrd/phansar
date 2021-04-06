#ifndef PHANSAR_COMMON_NETWORKING_MODERATOR_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_MODERATOR_SESSION_HPP

#include <phansar.capnp.h>
#include <phansar/common/networking/session.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::networking {
class moderator_session : public virtual schema::Service::ModeratorSession::Server, public session {
public:
    moderator_session();
    moderator_session(const moderator_session &) = default;
    auto operator=(const moderator_session &) -> moderator_session & = default;
    moderator_session(moderator_session &&)                          = default;
    auto operator=(moderator_session &&) -> moderator_session & = default;
    ~moderator_session() override;

    auto ban(BanContext _context) -> kj::Promise<void> override;
    auto unban(UnbanContext _context) -> kj::Promise<void> override;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::networking

#endif
