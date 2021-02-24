#include <phansar/common/macros.hpp>
#include <phansar/common/networking/stream.hpp>

namespace phansar::common::networking {
template <class T>
stream<T>::stream(std::shared_ptr<std::vector<capnp::ReaderFor<T>>> _container)
    : m_container{std::move(_container)} {}

template <class T>
auto stream<T>::write(WriteContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[stream] {{write}}: {}", _context.getParams().toString().flatten().cStr());

    auto params = _context.getParams();
    m_container->push_back(params.getPayload());

    return kj::READY_NOW;
}

template <class T>
auto stream<T>::done(DoneContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[stream] {{done}}: {} [{}]",
                _context.getParams().toString().flatten().cStr(),
                m_container->size());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
