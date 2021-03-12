#ifndef PHANSAR_COMMON_NETWORKING_STREAMABLE_HPP
#define PHANSAR_COMMON_NETWORKING_STREAMABLE_HPP

#include <phansar.capnp.h>

namespace phansar::common::networking {
template <class T>
class streamable : public schema::Service::Streamable<T>::Server {
public:
    using DownloadContext = typename schema::Service::Streamable<T>::Server::DownloadContext;
    using UploadContext   = typename schema::Service::Streamable<T>::Server::UploadContext;
    using BidiContext     = typename schema::Service::Streamable<T>::Server::BidiContext;

    explicit streamable(std::shared_ptr<std::vector<capnp::ReaderFor<T>>> _container);

    auto download(DownloadContext _context) -> kj::Promise<void> override;
    auto upload(UploadContext _context) -> kj::Promise<void> override;
    auto bidi(BidiContext _context) -> kj::Promise<void> override;

private:
    std::shared_ptr<std::vector<capnp::ReaderFor<T>>> m_container;
};
} // namespace phansar::common::networking

#include <phansar/common/networking/streamable.tpp>

#endif
