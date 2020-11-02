#ifndef PHANSAR_COMMON_SYSTEM_HPP
#define PHANSAR_COMMON_SYSTEM_HPP

namespace phansar::common::system {
void init(int _argc, const char * const * _argv, bool _enable_config = true);
void shutdown();
} // namespace phansar::common::system

#endif
