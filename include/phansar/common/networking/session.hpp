#ifndef PHANSAR_COMMON_NETWORKING_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_SESSION_HPP

#include <phansar.capnp.h>

namespace phansar::common::networking {
class session final : public schema::Service::Session::Server {
public:
    auto logout(LogoutContext _context) -> kj::Promise<void> override;
    auto download(DownloadContext _context) -> kj::Promise<void> override;
    auto upload(UploadContext _context) -> kj::Promise<void> override;
    auto bidi(BidiContext _context) -> kj::Promise<void> override;

private:
    std::shared_ptr<std::vector<capnp::ReaderFor<capnp::AnyPointer>>> m_container;
};
} // namespace phansar::common::networking

#endif
