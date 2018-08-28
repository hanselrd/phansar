#include "types.hpp"

namespace common {
namespace core {
namespace types {
namespace lua_api {
void init(sol::table &t) {
    sol::table types = t.create_named("types");

    types.new_usertype<vector2f>("Vector2f",
                                 sol::constructors<vector2f(), vector2f(float, float)>(),
                                 "x",
                                 &vector2f::x,
                                 "y",
                                 &vector2f::y);

    types.new_usertype<vector3f>("Vector3f",
                                 sol::constructors<vector3f(), vector3f(float, float, float)>(),
                                 "x",
                                 &vector3f::x,
                                 "y",
                                 &vector3f::y,
                                 "z",
                                 &vector3f::z);
}
} // namespace lua_api
} // namespace types
} // namespace core
} // namespace common
