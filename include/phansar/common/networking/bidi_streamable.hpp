#ifndef PHANSAR_COMMON_NETWORKING_BIDI_STREAMABLE_HPP
#define PHANSAR_COMMON_NETWORKING_BIDI_STREAMABLE_HPP

#include <phansar.capnp.h>
#include <phansar/common/utility/pimpl.hpp>

#include <vector>

namespace phansar::common::networking {
template <class T>
class bidi_streamable : public virtual schema::Service::BidiStreamable<T>::Server {
public:
    using PushPullContext = typename schema::Service::BidiStreamable<T>::Server::PushPullContext;

    explicit bidi_streamable(std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container);

    auto pushPull(PushPullContext _context) -> kj::Promise<void> override;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::networking

#include <phansar/common/networking/bidi_streamable.tpp>

#endif
