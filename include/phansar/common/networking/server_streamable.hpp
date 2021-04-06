#ifndef PHANSAR_COMMON_NETWORKING_SERVER_STREAMABLE_HPP
#define PHANSAR_COMMON_NETWORKING_SERVER_STREAMABLE_HPP

#include <phansar.capnp.h>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::networking {
template <class T>
class server_streamable : public virtual schema::Service::ServerStreamable<T>::Server {
public:
    using PullContext = typename schema::Service::ServerStreamable<T>::Server::PullContext;

    explicit server_streamable(
        std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container);

    auto pull(PullContext _context) -> kj::Promise<void> override;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::networking

#include <phansar/common/networking/server_streamable.tpp>

#endif
