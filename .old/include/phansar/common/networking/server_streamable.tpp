#include <phansar/common/macros.hpp>
#include <phansar/common/networking/server_streamable.hpp>
#include <phansar/common/helpers.hpp>

namespace phansar::common::networking {
template <class T>
struct server_streamable<T>::impl {
    std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> container;
};

template <class T>
server_streamable<T>::server_streamable(
    std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container)
    : m_impl{std::move(_container)} {}

template <class T>
auto server_streamable<T>::pull(PullContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[server_streamable] {{pull}}: {}",
                _context.getParams().toString().flatten().cStr());

    auto params = _context.getParams();

    return [container = m_impl->container, stream = params.getStream()]() mutable {
        const auto loop = helpers::y_combinator([](auto &&                                               loop,
                             std::shared_ptr<std::vector<kj::Own<capnp::ReaderFor<T>>>> _container,
                             typename schema::Service::Stream<T>::Client                _stream,
                             std::size_t _index = 0) {
            if (_index >= _container->size()) {
                return _stream.doneRequest().send().ignoreResult();
            }

            auto request = _stream.writeRequest();
            request.setPayload(*_container->at(_index).get());

            return request.send().then([loop,
                                        container = std::move(_container),
                                        stream    = kj::mv(_stream),
                                        _index]() mutable {
                return loop(std::move(container), kj::mv(stream), _index + 1);
            });
        });

        return loop(std::move(container), kj::mv(stream));
    }();
}
} // namespace phansar::common::networking
