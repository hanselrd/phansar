#ifndef PHANSAR_COMMON_NETWORKING_STREAM_HPP
#define PHANSAR_COMMON_NETWORKING_STREAM_HPP

#include <phansar.capnp.h>

namespace phansar::common::networking {
template <class T>
class stream : public schema::Service::Stream<T>::Server {
public:
    using WriteContext = typename schema::Service::Stream<T>::Server::WriteContext;
    using DoneContext  = typename schema::Service::Stream<T>::Server::DoneContext;

    auto write(WriteContext _context) -> kj::Promise<void> override;
    auto done(DoneContext _context) -> kj::Promise<void> override;
};
} // namespace phansar::common::networking

#include <phansar/common/networking/stream.tpp>

#endif
