#include <phansar/common/macros.hpp>
#include <phansar/common/networking/session.hpp>
#include <phansar/common/networking/stream.hpp>

namespace phansar::common::networking {
auto session::logout(LogoutContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[session] {{logout}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}

auto session::download(DownloadContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[session] {{download}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}

auto session::upload(UploadContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[session] {{upload}}: {}", _context.getParams().toString().flatten().cStr());

    auto results = _context.getResults();
    m_container  = std::make_shared<std::vector<capnp::ReaderFor<capnp::AnyPointer>>>();
    results.setStream(kj::heap<stream<capnp::AnyPointer>>(m_container));

    return kj::READY_NOW;
}

auto session::bidi(BidiContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[session] {{bidi}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
