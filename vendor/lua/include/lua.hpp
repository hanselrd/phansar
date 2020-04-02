// lua.hpp
// Lua header files for C++
// <<extern "C">> not supplied automatically because Lua also compiles as C++

#ifndef LUA_INCLUDE_LUA_HPP
#define LUA_INCLUDE_LUA_HPP

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#endif
