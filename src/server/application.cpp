#include <phansar/server/application.hpp>

namespace phansar::server {
application::application(int _argc, const char * const * _argv)
    : common::application{_argc, _argv} {}

void application::run() {}
} // namespace phansar::server
