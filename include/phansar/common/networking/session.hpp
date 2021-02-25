#ifndef PHANSAR_COMMON_NETWORKING_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_SESSION_HPP

#include <phansar.capnp.h>
#include <phansar/common/networking/streamable.hpp>

namespace phansar::common::networking {
class session final : public schema::Service::Session::Server,
                      public streamable<schema::Service::Message> {
public:
    session();

    auto logout(LogoutContext _context) -> kj::Promise<void> override;
};
} // namespace phansar::common::networking

#endif
