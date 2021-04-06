#ifndef PHANSAR_COMMON_NETWORKING_STREAM_HPP
#define PHANSAR_COMMON_NETWORKING_STREAM_HPP

#include <phansar.capnp.h>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::networking {
template <class T>
class stream : public schema::Service::Stream<T>::Server {
public:
    using WriteContext = typename schema::Service::Stream<T>::Server::WriteContext;
    using DoneContext  = typename schema::Service::Stream<T>::Server::DoneContext;

    explicit stream(std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container);
    stream(const stream &) = default;
    auto operator=(const stream &) -> stream & = default;
    stream(stream &&) noexcept                 = default;
    auto operator=(stream &&) noexcept -> stream & = default;
    virtual ~stream()                              = default;

    auto write(WriteContext _context) -> kj::Promise<void> override;
    auto done(DoneContext _context) -> kj::Promise<void> override;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::networking

#include <phansar/common/networking/stream.tpp>

#endif
