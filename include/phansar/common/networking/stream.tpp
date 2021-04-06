#include <phansar/common/macros.hpp>
#include <phansar/common/networking/stream.hpp>
#include <phansar/vendor/capnproto.hpp>

namespace phansar::common::networking {
template <class T>
struct stream<T>::impl {
    std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> container;
};

template <class T>
stream<T>::stream(std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container)
    : m_impl{std::move(_container)} {}

template <class T>
auto stream<T>::write(WriteContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[stream] {{write}}: {}", _context.getParams().toString().flatten().cStr());

    auto params = _context.getParams();
    m_impl->container->push_back(capnp::clone(params.getPayload()));

    return kj::READY_NOW;
}

template <class T>
auto stream<T>::done(DoneContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[stream] {{done}}: {} [{}]",
                _context.getParams().toString().flatten().cStr(),
                m_impl->container->size());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
