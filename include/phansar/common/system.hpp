#ifndef PHANSAR_COMMON_SYSTEM_HPP
#define PHANSAR_COMMON_SYSTEM_HPP

namespace phansar::common::system {
void init(int argc, const char * const * argv, bool enable_config = true);
void shutdown();
} // namespace phansar::common::system

#endif
