#ifndef PHANSAR_COMMON_NETWORKING_SERVICE_HPP
#define PHANSAR_COMMON_NETWORKING_SERVICE_HPP

#include <phansar.capnp.h>

namespace phansar::common::networking {
class service final : public schema::Service::Server {
public:
    auto login(LoginContext _context) -> kj::Promise<void> override;
    auto streamDown(StreamDownContext _context) -> kj::Promise<void> override;
    auto streamUp(StreamUpContext _context) -> kj::Promise<void> override;
    auto streamBidi(StreamBidiContext _context) -> kj::Promise<void> override;
    auto func(FuncContext _context) -> kj::Promise<void> override;

private:
    std::shared_ptr<std::vector<capnp::ReaderFor<schema::Service::Message>>> m_container;
};
} // namespace phansar::common::networking

#endif
