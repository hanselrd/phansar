#include <phansar/common/macros.hpp>
#include <phansar/common/networking/session.hpp>

namespace phansar::common::networking {
auto session::logout(LogoutContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[session] {{logout}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
