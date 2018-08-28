#include "common.hpp"

namespace common {
namespace lua_api {
void init(sol::table &t) {
    sol::table common = t.create_named("common");

    bitmasks::lua_api::init(common);
    core::lua_api::init(common);
    models::lua_api::init(common);
}
} // namespace lua_api
} // namespace common
