#ifndef COMMON_CORE_TYPES_HPP
#define COMMON_CORE_TYPES_HPP

#include "sol.hpp"
#include <cstdint>
#include <type_traits>

namespace common {
namespace core {
namespace types {
template <class T> struct vector2 {
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");

    explicit vector2(T _x = T(), T _y = T()) : x(_x), y(_y) {
    }

    T x;
    T y;
};

template <class T> struct vector3 {
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");

    explicit vector3(T _x = T(), T _y = T(), T _z = T()) : x(_x), y(_y), z(_z) {
    }

    T x;
    T y;
    T z;
};

using vector2i = vector2<std::int32_t>;
using vector2u = vector2<std::uint32_t>;
using vector2f = vector2<float>;

using vector3i = vector3<std::int32_t>;
using vector3u = vector3<std::uint32_t>;
using vector3f = vector3<float>;

namespace lua_api {
void init(sol::table &t);
}
} // namespace types
} // namespace core
} // namespace common

#endif
