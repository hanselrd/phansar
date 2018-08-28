#include "core.hpp"

namespace common {
namespace core {
namespace lua_api {
void init(sol::table &t) {
    sol::table core = t.create_named("core");

    log::lua_api::init(core);
    types::lua_api::init(core);
}
} // namespace lua_api
} // namespace core
} // namespace common
