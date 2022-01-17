#ifndef PHANSAR_COMMON_NETWORKING_ADMINISTRATOR_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_ADMINISTRATOR_SESSION_HPP

#include <phansar.capnp.h>
#include <phansar/common/networking/moderator_session.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::networking {
class administrator_session : public virtual schema::Service::AdministratorSession::Server,
                              public moderator_session {
public:
    administrator_session();
    administrator_session(const administrator_session &) = default;
    auto operator=(const administrator_session &) -> administrator_session & = default;
    administrator_session(administrator_session &&)                          = default;
    auto operator=(administrator_session &&) -> administrator_session & = default;
    ~administrator_session() override;

    auto restart(RestartContext _context) -> kj::Promise<void> override;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::networking

#endif
