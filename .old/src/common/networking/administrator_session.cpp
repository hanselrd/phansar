#include <phansar/common/macros.hpp>
#include <phansar/common/networking/administrator_session.hpp>

namespace phansar::common::networking {
struct administrator_session::impl {};

administrator_session::administrator_session() = default;

administrator_session::~administrator_session() = default;

auto administrator_session::restart(RestartContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[administrator_session] {{restart}}: {}",
                _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
