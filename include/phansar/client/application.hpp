#ifndef PHANSAR_CLIENT_APPLICATION_HPP
#define PHANSAR_CLIENT_APPLICATION_HPP

#include <phansar/common/application.hpp>

namespace phansar::client {
class application : public common::application {
public:
    application(int _argc, const char * const * _argv);

    void run() override;
};
} // namespace phansar::client

#endif
