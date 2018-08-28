#include "bitmasks.hpp"

namespace common {
namespace bitmasks {
namespace lua_api {
void init(sol::table &t) {
    sol::table bitmasks = t.create_named("bitmasks");

    bitmasks.new_enum("Permissions",
                      "NONE",
                      permissions::NONE,
                      "VETERAN",
                      permissions::VETERAN,
                      "DONOR",
                      permissions::DONOR,
                      "INTERN",
                      permissions::INTERN,
                      "ADVISOR",
                      permissions::ADVISOR,
                      "MODERATOR",
                      permissions::MODERATOR,
                      "ADMINISTRATOR",
                      permissions::ADMINISTRATOR,
                      "OWNER",
                      permissions::OWNER,
                      "ROOT",
                      permissions::ROOT);
}
} // namespace lua_api
} // namespace bitmasks
} // namespace common
