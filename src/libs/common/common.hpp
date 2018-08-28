#ifndef COMMON_COMMON_HPP
#define COMMON_COMMON_HPP

#include "bitmasks/bitmasks.hpp"
#include "core/core.hpp"
#include "models/models.hpp"
#include "scopes/scopes.hpp"

namespace common {
namespace lua_api {
void init(sol::table &t);
}
} // namespace common

#endif
