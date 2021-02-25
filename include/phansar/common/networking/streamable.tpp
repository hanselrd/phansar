#include <phansar/common/macros.hpp>
#include <phansar/common/networking/stream.hpp>
#include <phansar/common/networking/streamable.hpp>

namespace phansar::common::networking {
template <class T>
streamable<T>::streamable(std::shared_ptr<std::vector<capnp::ReaderFor<T>>> _container)
    : m_container{std::move(_container)} {}

template <class T>
auto streamable<T>::download(DownloadContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[streamable] {{download}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}

template <class T>
auto streamable<T>::upload(UploadContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[streamable] {{upload}}: {}", _context.getParams().toString().flatten().cStr());

    auto results = _context.getResults();
    results.setStream(kj::heap<stream<T>>(m_container));

    return kj::READY_NOW;
}

template <class T>
auto streamable<T>::bidi(BidiContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[streamable] {{bidi}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
