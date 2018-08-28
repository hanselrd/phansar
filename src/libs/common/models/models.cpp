#include "models.hpp"

namespace common {
namespace models {
namespace lua_api {
void init(sol::table &t) {
    sol::table models = t.create_named("models");

    models.new_usertype<entity>(
        "Entity",
        sol::constructors<entity(), entity(const core::types::vector3f &)>(),
        "move",
        &entity::move,
        "map_id",
        sol::property(&entity::get_map_id, &entity::set_map_id),
        "position",
        sol::property(&entity::get_position, &entity::set_position));

    models.new_usertype<player>("Player",
                                sol::constructors<player()>(),
                                "name",
                                sol::property(&player::get_name, &player::set_name),
                                "permissions",
                                sol::readonly_property(&player::get_permissions),
                                sol::base_classes,
                                sol::bases<entity>());
}
} // namespace lua_api
} // namespace models
} // namespace common
