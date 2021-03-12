#ifndef PHANSAR_COMMON_NETWORKING_MODERATOR_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_MODERATOR_SESSION_HPP

#include <phansar.capnp.h>
#include <phansar/common/networking/session.hpp>

namespace phansar::common::networking {
class moderator_session : public virtual schema::Service::ModeratorSession::Server, public session {
public:
    ~moderator_session() override = default;

    auto ban(BanContext _context) -> kj::Promise<void> override;
    auto unban(UnbanContext _context) -> kj::Promise<void> override;
};
} // namespace phansar::common::networking

#endif
