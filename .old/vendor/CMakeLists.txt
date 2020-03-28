#
# This file is part of Phansar.
#
# Copyright (C) 2018  Hansel De La Cruz
#
# Phansar is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Phansar is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
#

project(vendor)

function(check_git_commit_hash name source_dir branch)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        OUTPUT_VARIABLE head_hash
        WORKING_DIRECTORY ${source_dir})

    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse origin/${branch}
        OUTPUT_VARIABLE origin_hash
        WORKING_DIRECTORY ${source_dir})

    message(STATUS "${name}: ${source_dir}")
    message(STATUS "${name}: (HEAD) ${head_hash}")

    if(NOT ${head_hash} STREQUAL ${origin_hash})
        message(WARNING "Newer commit ${name}: (origin/${branch}) ${origin_hash}")
    endif()
endfunction()

include(FetchContent)
FetchContent_Declare(Box2D_git
    GIT_REPOSITORY https://github.com/erincatto/Box2D.git
    GIT_TAG        ebb7c5e24ab289c394dffe5d56e3a4025c72c0fc)
FetchContent_GetProperties(Box2D_git)
if(NOT box2d_git_POPULATED)
    FetchContent_Populate(Box2D_git)
    check_git_commit_hash(Box2D ${box2d_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(Catch2_git
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        e70fd2a4b9a867c57c215b73d28bf911333bf45c)
FetchContent_GetProperties(Catch2_git)
if(NOT catch2_git_POPULATED)
    FetchContent_Populate(Catch2_git)
    check_git_commit_hash(Catch2 ${catch2_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(cppcodec_git
    GIT_REPOSITORY https://github.com/tplgy/cppcodec.git
    GIT_TAG        bd6ddf95129e769b50ef63e0f558fa21364f3f65)
FetchContent_GetProperties(cppcodec_git)
if(NOT cppcodec_git_POPULATED)
    FetchContent_Populate(cppcodec_git)
    check_git_commit_hash(cppcodec ${cppcodec_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(enet_git
    GIT_REPOSITORY https://github.com/lsalzman/enet.git
    GIT_TAG        0eaf48eeb0d94a18d079378d8b76d588832ce838)
FetchContent_GetProperties(enet_git)
if(NOT enet_git_POPULATED)
    FetchContent_Populate(enet_git)
    check_git_commit_hash(enet ${enet_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(json_git
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        456478b3c50d60100dbb1fb9bc931f370a2c1c28)
FetchContent_GetProperties(json_git)
if(NOT json_git_POPULATED)
    FetchContent_Populate(json_git)
    check_git_commit_hash(json ${json_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(lua_git
    GIT_REPOSITORY https://github.com/lua/lua.git
    GIT_TAG        69c7139ff88bf26e05d80bf19d0351e5c88d13a3)
FetchContent_GetProperties(lua_git)
if(NOT lua_git_POPULATED)
    FetchContent_Populate(lua_git)
    check_git_commit_hash(lua ${lua_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(plibsys_git
    GIT_REPOSITORY https://github.com/saprykin/plibsys.git
    GIT_TAG        e57dfc613163989bb536d980bec142fd7e35271d)
FetchContent_GetProperties(plibsys_git)
if(NOT plibsys_git_POPULATED)
    FetchContent_Populate(plibsys_git)
    check_git_commit_hash(plibsys ${plibsys_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(rttr_git
    GIT_REPOSITORY https://github.com/rttrorg/rttr.git
    GIT_TAG        b16fccf0fbbbf94064bf2a6c7c47f2b910ab31f1)
FetchContent_GetProperties(rttr_git)
if(NOT rttr_git_POPULATED)
    FetchContent_Populate(rttr_git)
    check_git_commit_hash(rttr ${rttr_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(sol2_git
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG        47fbab369fcd4ab572929a91975552d3be8dc00e)
FetchContent_GetProperties(sol2_git)
if(NOT sol2_git_POPULATED)
    FetchContent_Populate(sol2_git)
    check_git_commit_hash(sol2 ${sol2_git_SOURCE_DIR} develop)
endif()

FetchContent_Declare(spdlog_git
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        0f42744f5c34402541d47c2dfaa125155d33c8e3)
FetchContent_GetProperties(spdlog_git)
if(NOT spdlog_git_POPULATED)
    FetchContent_Populate(spdlog_git)
    check_git_commit_hash(spdlog ${spdlog_git_SOURCE_DIR} v1.x)
endif()

set(CEF_URL "http://opensource.spotify.com/cefbuilds/cef_binary_79.1.36%2Bg90301bd%2Bchromium-79.0.3945.130")
if(WIN32)
    FetchContent_Declare(cef_tarbz2
        URL            ${CEF_URL}_windows64.tar.bz2
        URL_HASH       SHA1=ce4673328a4473995f9bfedc03644560938b21ff)
elseif(UNIX)
    FetchContent_Declare(cef_tarbz2
        URL            ${CEF_URL}_linux64.tar.bz2
        URL_HASH       SHA1=e28d0da5e8f8e4bfbc4ebfab751c04bfcddd4366)
elseif(APPLE)
    FetchContent_Declare(cef_tarbz2
        URL            ${CEF_URL}_macosx64.tar.bz2
        URL_HASH       SHA1=7931b1bf6b34567ab956b0aab3f8111609e82095)
else()
    message(FATAL_ERROR "cef: platform not supported")
endif()
FetchContent_GetProperties(cef_tarbz2)
if(NOT cef_tarbz2_POPULATED)
    FetchContent_Populate(cef_tarbz2)
    message(STATUS "cef: ${cef_tarbz2_SOURCE_DIR}")
endif()

set(BOX2D_BUILD_TESTS OFF CACHE BOOL "")
set(BOX2D_BUILD_SAMPLES OFF CACHE BOOL "")
set(BOX2D_BUILD_DOCS OFF CACHE BOOL "")
add_subdirectory(${box2d_git_SOURCE_DIR} ${box2d_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(CATCH_BUILD_TESTING OFF CACHE BOOL "")
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "")
set(CATCH_INSTALL_HELPERS OFF CACHE BOOL "")
add_subdirectory(${catch2_git_SOURCE_DIR} ${catch2_git_BINARY_DIR} EXCLUDE_FROM_ALL)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${catch2_git_SOURCE_DIR}/contrib PARENT_SCOPE)

add_subdirectory(${enet_git_SOURCE_DIR} ${enet_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(JSON_BuildTests OFF CACHE BOOL "")
add_subdirectory(${json_git_SOURCE_DIR} ${json_git_BINARY_DIR} EXCLUDE_FROM_ALL)

add_library(lua STATIC
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

target_include_directories(lua PUBLIC
    ${lua_git_SOURCE_DIR})

set(PLIBSYS_TESTS OFF CACHE BOOL "")
set(PLIBSYS_BUILD_DOC OFF CACHE BOOL "")
add_subdirectory(${plibsys_git_SOURCE_DIR} ${plibsys_git_BINARY_DIR} EXCLUDE_FROM_ALL)

set(BUILD_RTTR_DYNAMIC OFF CACHE BOOL "")
set(BUILD_UNIT_TESTS OFF CACHE BOOL "")
set(BUILD_STATIC ON CACHE BOOL "")
set(BUILD_WITH_STATIC_RUNTIME_LIBS OFF CACHE BOOL "")
set(BUILD_WITH_RTTI ON CACHE BOOL "")
set(BUILD_BENCHMARKS OFF CACHE BOOL "")
set(BUILD_EXAMPLES OFF CACHE BOOL "")
set(BUILD_DOCUMENTATION OFF CACHE BOOL "")
set(BUILD_INSTALLER OFF CACHE BOOL "")
set(BUILD_PACKAGE OFF CACHE BOOL "")
set(USE_PCH OFF CACHE BOOL "")
set(CUSTOM_DOXYGEN_STYLE OFF CACHE BOOL "")
set(BUILD_WEBSITE_DOCU OFF CACHE BOOL "")
add_subdirectory(${rttr_git_SOURCE_DIR} ${rttr_git_BINARY_DIR} EXCLUDE_FROM_ALL)

add_subdirectory(${spdlog_git_SOURCE_DIR} ${spdlog_git_BINARY_DIR} EXCLUDE_FROM_ALL)

add_subdirectory(${cef_tarbz2_SOURCE_DIR} ${cef_tarbz2_BINARY_DIR} EXCLUDE_FROM_ALL)
add_custom_target(cef_resources ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${cef_tarbz2_SOURCE_DIR}/Resources resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${cef_tarbz2_SOURCE_DIR}/$<IF:$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>,Release,Debug> resources
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${cppcodec_git_SOURCE_DIR}
    ${enet_git_SOURCE_DIR}/include
    ${sol2_git_SOURCE_DIR}/single/include
    ${cef_tarbz2_SOURCE_DIR}
    ${cef_tarbz2_SOURCE_DIR}/include)

target_link_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_BINARY_DIR}/resources)

target_link_libraries(${PROJECT_NAME} INTERFACE
    box2d
    Catch2
    enet
    nlohmann_json
    lua
    plibsysstatic
    rttr_core_lib
    spdlog
    cef
    libcef_dll_wrapper)
