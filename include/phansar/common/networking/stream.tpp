#include <phansar/common/macros.hpp>
#include <phansar/common/networking/stream.hpp>

namespace phansar::common::networking {
template <class T>
auto stream<T>::write(WriteContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[stream] {{write}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}

template <class T>
auto stream<T>::done(DoneContext _context) -> kj::Promise<void> {
    PH_LOG_INFO("[stream] {{done}}: {}", _context.getParams().toString().flatten().cStr());

    return kj::READY_NOW;
}
} // namespace phansar::common::networking
