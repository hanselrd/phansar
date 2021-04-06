#ifndef PHANSAR_CLIENT_APPLICATION_HPP
#define PHANSAR_CLIENT_APPLICATION_HPP

#include <phansar/common/application.hpp>
#include <phansar/common/utility/pimpl.hpp>

namespace phansar::client {
class application : public common::application {
public:
    application(int _argc, const char * const * _argv);
    application(const application &) = default;
    auto operator=(const application &) -> application & = default;
    application(application &&)                          = default;
    auto operator=(application &&) -> application & = default;
    ~application();

    void run() override;

private:
    struct impl;
    common::utility::pimpl<impl> m_impl;
};
} // namespace phansar::client

#endif
