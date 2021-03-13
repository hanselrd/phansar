#include <phansar/common/macros.hpp>
#include <phansar/common/networking/server_streamable.hpp>

namespace phansar::common::networking {
template <class T>
server_streamable<T>::server_streamable(
    std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container)
    : m_container{std::move(_container)} {}

template <class T>
auto server_streamable<T>::pull(PullContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[server_streamable] {{pull}}: {}",
                _context.getParams().toString().flatten().cStr());

    auto params = _context.getParams();

    return [container = m_container, stream = params.getStream()]() mutable {
        const auto loop = [](const auto &                                               _self,
                             std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container,
                             typename schema::Service::Stream<T>::Client                _stream,
                             std::size_t _index = 0) {
            if (_index >= _container->size()) {
                return _stream.doneRequest().send().ignoreResult();
            }

            auto request = _stream.writeRequest();
            request.setPayload(*_container->at(_index).get());

            return request.send().then([&_self,
                                        container = std::move(_container),
                                        stream    = kj::mv(_stream),
                                        _index]() mutable {
                return _self(_self, std::move(container), kj::mv(stream), _index + 1);
            });
        };

        return loop(loop, std::move(container), kj::mv(stream));
    }();
}
} // namespace phansar::common::networking
