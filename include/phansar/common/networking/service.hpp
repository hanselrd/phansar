#ifndef PHANSAR_COMMON_NETWORKING_SERVICE_HPP
#define PHANSAR_COMMON_NETWORKING_SERVICE_HPP

#include <phansar.capnp.h>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::common::networking {
class service : public schema::Service::Server {
public:
    service();
    service(const service &) = default;
    auto operator=(const service &) -> service & = default;
    service(service &&)                          = default;
    auto operator=(service &&) -> service & = default;
    virtual ~service();

    auto login(LoginContext _context) -> kj::Promise<void> override;

private:
    struct impl;
    utility::pimpl<impl> m_impl;
};
} // namespace phansar::common::networking

#endif
