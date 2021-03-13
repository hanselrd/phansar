#include <phansar/common/macros.hpp>
#include <phansar/common/networking/bidi_streamable.hpp>
#include <phansar/common/networking/stream.hpp>

namespace phansar::common::networking {
template <class T>
bidi_streamable<T>::bidi_streamable(
    std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container)
    : m_container{std::move(_container)} {}

template <class T>
auto bidi_streamable<T>::pushPull(PushPullContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[bidi_streamable] {{pushPull}}: {}",
                _context.getParams().toString().flatten().cStr());

    auto params  = _context.getParams();
    auto results = _context.getResults();
    results.setStream(kj::heap<stream<T>>(m_container));

    auto builder = kj::heapArrayBuilder<kj::Promise<void>>(1);
    builder.add([container = m_container, stream = params.getStream()]() mutable {
        const auto loop = [](const auto &                                               _self,
                             std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container,
                             typename schema::Service::Stream<T>::Client                _stream,
                             std::size_t _index = 0) -> kj::Promise<void> {
            if (_index >= _container->size()) {
                return kj::READY_NOW;
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
    }());

    return kj::joinPromises(builder.finish());
}
} // namespace phansar::common::networking
