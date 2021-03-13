#ifndef PHANSAR_COMMON_NETWORKING_CLIENT_STREAMABLE_HPP
#define PHANSAR_COMMON_NETWORKING_CLIENT_STREAMABLE_HPP

#include <phansar.capnp.h>

namespace phansar::common::networking {
template <class T>
class client_streamable : public virtual schema::Service::ClientStreamable<T>::Server {
public:
    using PushContext = typename schema::Service::ClientStreamable<T>::Server::PushContext;

    explicit client_streamable(
        std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container);

    auto push(PushContext _context) -> kj::Promise<void> override;

private:
    std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> m_container;
};
} // namespace phansar::common::networking

#include <phansar/common/networking/client_streamable.tpp>

#endif
