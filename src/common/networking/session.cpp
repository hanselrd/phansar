#include <phansar/common/macros.hpp>
#include <phansar/common/networking/session.hpp>

namespace phansar::common::networking {
session::session()
    : streamable<schema::Service::Message>{
          std::make_shared<std::vector<capnp::ReaderFor<schema::Service::Message>>>()} {}

auto session::logout(LogoutContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[session] {{logout}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
