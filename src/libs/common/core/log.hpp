#ifndef COMMON_CORE_LOG_HPP
#define COMMON_CORE_LOG_HPP

#include "sol.hpp"
#include <plog/Log.h>
#include <string>

#if defined(__FILE__) && defined(__SOURCE_PATH_SIZE__)
#    define __FILENAME__ (__FILE__ + __SOURCE_PATH_SIZE__)
#else
#    define __FILENAME__ "unknown"
#endif

namespace common {
namespace core {
namespace log {
void init(const std::string &filename);

namespace lua_api {
void init(sol::table &t);
}
} // namespace log
} // namespace core
} // namespace common

#endif
