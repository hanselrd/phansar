#ifndef PHANSAR_COMMON_NETWORKING_ROOT_SESSION_HPP
#define PHANSAR_COMMON_NETWORKING_ROOT_SESSION_HPP

#include <phansar.capnp.h>
#include <phansar/common/networking/administrator_session.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::networking {
class root_session : public schema::Service::RootSession::Server, public administrator_session {
public:
    root_session();
    root_session(const root_session &) = default;
    auto operator=(const root_session &) -> root_session & = default;
    root_session(root_session &&)                          = default;
    auto operator=(root_session &&) -> root_session & = default;
    ~root_session() override;

    auto shutdown(ShutdownContext _context) -> kj::Promise<void> override;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::networking

#endif
