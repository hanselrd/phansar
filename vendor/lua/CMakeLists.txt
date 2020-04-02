FetchContent_Declare(lua_git
    GIT_REPOSITORY https://github.com/lua/lua.git
    GIT_TAG        7288528a1e081d101a1bc19346a974088b6b8315)
FetchContent_GetProperties(lua_git)
if(NOT lua_git_POPULATED)
    FetchContent_Populate(lua_git)
    check_git_commit_hash(lua ${lua_git_SOURCE_DIR} master)
endif()

# add_subdirectory(${lua_git_SOURCE_DIR} ${lua_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(sources
    ${lua_git_SOURCE_DIR}/lapi.c
    ${lua_git_SOURCE_DIR}/lauxlib.c
    ${lua_git_SOURCE_DIR}/lbaselib.c
    # ${lua_git_SOURCE_DIR}/lbitlib.c
    ${lua_git_SOURCE_DIR}/lcode.c
    ${lua_git_SOURCE_DIR}/lcorolib.c
    ${lua_git_SOURCE_DIR}/lctype.c
    ${lua_git_SOURCE_DIR}/ldblib.c
    ${lua_git_SOURCE_DIR}/ldebug.c
    ${lua_git_SOURCE_DIR}/ldo.c
    ${lua_git_SOURCE_DIR}/ldump.c
    ${lua_git_SOURCE_DIR}/lfunc.c
    ${lua_git_SOURCE_DIR}/lgc.c
    ${lua_git_SOURCE_DIR}/linit.c
    ${lua_git_SOURCE_DIR}/liolib.c
    ${lua_git_SOURCE_DIR}/llex.c
    ${lua_git_SOURCE_DIR}/lmathlib.c
    ${lua_git_SOURCE_DIR}/lmem.c
    ${lua_git_SOURCE_DIR}/loadlib.c
    ${lua_git_SOURCE_DIR}/lobject.c
    ${lua_git_SOURCE_DIR}/lopcodes.c
    ${lua_git_SOURCE_DIR}/loslib.c
    ${lua_git_SOURCE_DIR}/lparser.c
    ${lua_git_SOURCE_DIR}/lstate.c
    ${lua_git_SOURCE_DIR}/lstring.c
    ${lua_git_SOURCE_DIR}/lstrlib.c
    ${lua_git_SOURCE_DIR}/ltable.c
    ${lua_git_SOURCE_DIR}/ltablib.c
    ${lua_git_SOURCE_DIR}/ltests.c
    ${lua_git_SOURCE_DIR}/ltm.c
    # ${lua_git_SOURCE_DIR}/lua.c
    ${lua_git_SOURCE_DIR}/lundump.c
    ${lua_git_SOURCE_DIR}/lutf8lib.c
    ${lua_git_SOURCE_DIR}/lvm.c
    ${lua_git_SOURCE_DIR}/lzio.c)

set(includes
    ${lua_git_SOURCE_DIR})

ph_add_generic_vendor_library(ph_vendor_lua "${sources}" "${includes}" "" "")
