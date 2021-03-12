#ifndef PHANSAR_COMMON_NETWORKING_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_SESSION_HPP

#include <phansar.capnp.h>

namespace phansar::common::networking {
class session : public virtual schema::Service::Session::Server {
public:
    virtual ~session() = default;

    auto logout(LogoutContext _context) -> kj::Promise<void> override;
};
} // namespace phansar::common::networking

#endif
