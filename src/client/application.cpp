#include <phansar/client/application.hpp>

namespace phansar::client {
application::application(int _argc, const char * const * _argv)
    : common::application{_argc, _argv} {}

void application::run() {}
} // namespace phansar::client
