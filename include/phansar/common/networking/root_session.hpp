#ifndef PHANSAR_COMMON_NETWORKING_ROOT_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_ROOT_SESSION_HPP

#include <phansar.capnp.h>
#include <phansar/common/networking/administrator_session.hpp>

namespace phansar::common::networking {
class root_session : public schema::Service::RootSession::Server, public administrator_session {
public:
    ~root_session() override = default;

    auto shutdown(ShutdownContext _context) -> kj::Promise<void> override;
};
} // namespace phansar::common::networking

#endif
