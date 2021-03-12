#include <phansar/common/macros.hpp>
#include <phansar/common/networking/root_session.hpp>

namespace phansar::common::networking {
auto root_session::shutdown(ShutdownContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[root_session] {{shutdown}}: {}",
                _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
