#ifndef PHANSAR_COMMON_NETWORKING_ADMINISTRATOR_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_ADMINISTRATOR_SESSION_HPP

#include <phansar.capnp.h>
#include <phansar/common/networking/moderator_session.hpp>

namespace phansar::common::networking {
class administrator_session : public virtual schema::Service::AdministratorSession::Server,
                              public moderator_session {
public:
    ~administrator_session() override = default;

    auto restart(RestartContext _context) -> kj::Promise<void> override;
};
} // namespace phansar::common::networking

#endif
