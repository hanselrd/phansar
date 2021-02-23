#ifndef PHANSAR_COMMON_NETWORKING_SERVICE_HPP
#define PHANSAR_COMMON_NETWORKING_SERVICE_HPP

#include <phansar.capnp.h>

namespace phansar::common::networking {
class service : public schema::Service::Server {
public:
    auto streamDown(StreamDownContext _context) -> kj::Promise<void> override;
    auto streamUp(StreamUpContext _context) -> kj::Promise<void> override;
    auto streamBidi(StreamBidiContext _context) -> kj::Promise<void> override;
    auto func(FuncContext _context) -> kj::Promise<void> override;
};
} // namespace phansar::common::networking

#endif
