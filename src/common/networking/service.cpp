#include <phansar/common/macros.hpp>
#include <phansar/common/networking/administrator_session.hpp>
#include <phansar/common/networking/moderator_session.hpp>
#include <phansar/common/networking/root_session.hpp>
#include <phansar/common/networking/service.hpp>
#include <phansar/common/networking/session.hpp>

namespace phansar::common::networking {
auto service::login(LoginContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[service] {{login}}: {}", _context.getParams().toString().flatten().cStr());

    auto params  = _context.getParams();
    auto results = _context.getResults();
    auto result  = results.initResult();

    if (params.getUsername() == "bob" && params.getPassword() == "password") {
        /* result.setOk(kj::heap<session>()); */
        /* result.setOk(kj::heap<moderator_session>()); */
        /* result.setOk(kj::heap<administrator_session>()); */
        result.setOk(kj::heap<root_session>());
    } else {
        result.setErr("Failed to login");
    }

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
