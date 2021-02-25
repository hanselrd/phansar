#ifndef PHANSAR_COMMON_NETWORKING_SERVICE_HPP
#define PHANSAR_COMMON_NETWORKING_SERVICE_HPP

#include <phansar.capnp.h>

namespace phansar::common::networking {
class service final : public schema::Service::Server {
public:
    auto login(LoginContext _context) -> kj::Promise<void> override;
};
} // namespace phansar::common::networking

#endif
