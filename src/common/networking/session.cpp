#include <phansar/common/macros.hpp>
#include <phansar/common/networking/chat.hpp>
#include <phansar/common/networking/session.hpp>

namespace phansar::common::networking {
struct session::impl {};

session::session() = default;

session::~session() = default;

auto session::globalChat(GlobalChatContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[session] {{globalChat}}: {}", _context.getParams().toString().flatten().cStr());

    auto results = _context.getResults();
    auto result  = results.initResult();
    result.setOk(kj::heap<chat>());

    return kj::READY_NOW;
}

auto session::logout(LogoutContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[session] {{logout}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
