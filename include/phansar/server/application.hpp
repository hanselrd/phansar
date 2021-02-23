#ifndef PHANSAR_SERVER_APPLICATION_HPP
#define PHANSAR_SERVER_APPLICATION_HPP

#include <phansar/common/application.hpp>

namespace phansar::server {
class application : public common::application {
public:
    application(int _argc, const char * const * _argv);

    void run() override;

private:
    capnp::EzRpcServer m_server;
};
} // namespace phansar::server

#endif
