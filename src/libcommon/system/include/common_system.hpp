#ifndef LIBCOMMON_SYSTEM_INCLUDE_COMMON_SYSTEM_HPP
#define LIBCOMMON_SYSTEM_INCLUDE_COMMON_SYSTEM_HPP

namespace common::system {
void init(int argc, char ** argv, bool enable_logging = true);
void shutdown();
} // namespace common::system

#endif
