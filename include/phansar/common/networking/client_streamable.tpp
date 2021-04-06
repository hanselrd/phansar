#include <phansar/common/macros.hpp>
#include <phansar/common/networking/client_streamable.hpp>
#include <phansar/common/networking/stream.hpp>

namespace phansar::common::networking {
template <class T>
struct client_streamable<T>::impl {
    std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> container;
};

template <class T>
client_streamable<T>::client_streamable(
    std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container)
    : m_impl{std::move(_container)} {}

template <class T>
auto client_streamable<T>::push(PushContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[client_streamable] {{push}}: {}",
                _context.getParams().toString().flatten().cStr());

    auto results = _context.getResults();
    results.setStream(kj::heap<stream<T>>(m_impl->container));

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
