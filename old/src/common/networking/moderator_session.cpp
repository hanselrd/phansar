#include <phansar/common/macros.hpp>
#include <phansar/common/networking/moderator_session.hpp>

namespace phansar::common::networking {
struct moderator_session::impl {};

moderator_session::moderator_session() = default;

moderator_session::~moderator_session() = default;

auto moderator_session::ban(BanContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[moderator_session] {{ban}}: {}",
                _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}

auto moderator_session::unban(UnbanContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[moderator_session] {{unban}}: {}",
                _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
