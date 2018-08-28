project(extlibs)

set(CATCH_BUILD_TESTING OFF CACHE BOOL "")
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "")
set(CATCH_INSTALL_HELPERS OFF CACHE BOOL "")
add_subdirectory(Catch2)

add_subdirectory(enet)

set(JSON_BuildTests OFF CACHE BOOL "")
add_subdirectory(json)

add_library(lua STATIC
    lua/lapi.c
    lua/lauxlib.c
    lua/lbaselib.c
    # lua/lbitlib.c
    lua/lcode.c
    lua/lcorolib.c
    lua/lctype.c
    lua/ldblib.c
    lua/ldebug.c
    lua/ldo.c
    lua/ldump.c
    lua/lfunc.c
    lua/lgc.c
    lua/linit.c
    lua/liolib.c
    lua/llex.c
    lua/lmathlib.c
    lua/lmem.c
    lua/loadlib.c
    lua/lobject.c
    lua/lopcodes.c
    lua/loslib.c
    lua/lparser.c
    lua/lstate.c
    lua/lstring.c
    lua/lstrlib.c
    lua/ltable.c
    lua/ltablib.c
    lua/ltests.c
    lua/ltm.c
    # lua/lua.c
    lua/lundump.c
    lua/lutf8lib.c
    lua/lvm.c
    lua/lzio.c)

target_include_directories(lua PUBLIC
    lua)

set(PLIBSYS_TESTS OFF CACHE BOOL "")
set(PLIBSYS_BUILD_DOC OFF CACHE BOOL "")
add_subdirectory(plibsys)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    cppcodec
    enet/include
    plog/include
    sol2/single)

target_link_libraries(${PROJECT_NAME} INTERFACE
    Catch2
    enet
    nlohmann_json
    lua
    plibsysstatic)
