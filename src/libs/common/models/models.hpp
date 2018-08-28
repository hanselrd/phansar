#ifndef COMMON_MODELS_MODELS_HPP
#define COMMON_MODELS_MODELS_HPP

#include "../core/sol.hpp"
#include "entity.hpp"
#include "player.hpp"

namespace common {
namespace models {
namespace lua_api {
void init(sol::table &t);
}
} // namespace models
} // namespace common

#endif
