#include <phansar/common/macros.hpp>
#include <phansar/common/networking/service.hpp>
#include <phansar/common/networking/session.hpp>

namespace phansar::common::networking {
auto service::login(LoginContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[service] {{login}}: {}", _context.getParams().toString().flatten().cStr());

    auto params  = _context.getParams();
    auto results = _context.getResults();
    auto result  = results.initResult();

    if (params.getUsername() == "bob" && params.getPassword() == "password") {
        result.setOk(kj::heap<session>());
    } else {
        result.setErr("Failed to login");
    }

    return kj::READY_NOW;
}

/* auto service::streamDown(StreamDownContext _context) -> kj::Promise<void> { */
/*     PH_LOG_INFO("[service] {{streamDown}}: {}",
 * _context.getParams().toString().flatten().cStr()); */

/*     auto params = _context.getParams(); */

/*     return [stream = params.getStream()]() mutable { */
/*         const auto loop = [](const auto &                                              _self, */
/*                              schema::Service::Stream<schema::Service::Message>::Client _stream,
 */
/*                              std::size_t                                               _index) {
 */
/*             if (_index >= 10'000) { */
/*                 return _stream.doneRequest().send().ignoreResult(); */
/*             } */

/*             auto request = _stream.writeRequest(); */
/*             auto payload = request.initPayload(); */
/*             payload.setId(static_cast<std::uint32_t>(_index + 1)); */
/*             payload.setAuthor("Server"); */
/*             payload.setText("Welcome"); */

/*             return request.send().then([&_self, stream = kj::mv(_stream), _index]() mutable { */
/*                 return _self(_self, kj::mv(stream), _index + 1); */
/*             }); */
/*         }; */

/*         return loop(loop, kj::mv(stream), 0); */
/*     }(); */
/* } */
} // namespace phansar::common::networking
