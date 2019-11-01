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

project(extlibs)

function(check_git_commit_hash name source_dir branch)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        OUTPUT_VARIABLE head_hash
        WORKING_DIRECTORY ${source_dir})

    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse origin/${branch}
        OUTPUT_VARIABLE origin_hash
        WORKING_DIRECTORY ${source_dir})

    message(STATUS "${name}: ${box2d_git_SOURCE_DIR}")
    message(STATUS "${name}: (HEAD) ${head_hash}")

    if(NOT ${head_hash} STREQUAL ${origin_hash})
        message(WARNING "${name}: (origin/${branch}) ${origin_hash}")
    endif()
endfunction()

include(FetchContent)
FetchContent_Declare(Box2D_git
    GIT_REPOSITORY https://github.com/erincatto/Box2D.git
    GIT_TAG        ef96a4f17f1c5527d20993b586b400c2617d6ae1)
FetchContent_GetProperties(Box2D_git)
if(NOT box2d_git_POPULATED)
    FetchContent_Populate(Box2D_git)
    check_git_commit_hash(Box2D ${box2d_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(Catch2_git
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        5ac348cd6e788abbf18139289ae8f4722ab1ebe8)
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
    GIT_TAG        ea60d40f4a60a47d3be9560d8f7bc37c163fe47b)
FetchContent_GetProperties(json_git)
if(NOT json_git_POPULATED)
    FetchContent_Populate(json_git)
    check_git_commit_hash(json ${json_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(lua_git
    GIT_REPOSITORY https://github.com/lua/lua.git
    GIT_TAG        6e1aec7a677a9891f2f8ca57e039d9984fdc69bc)
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

FetchContent_Declare(plog_git
    GIT_REPOSITORY https://github.com/SergiusTheBest/plog.git
    GIT_TAG        f4c22b03d5d3aa753cca8e716636ac4eb29b0917)
FetchContent_GetProperties(plog_git)
if(NOT plog_git_POPULATED)
    FetchContent_Populate(plog_git)
    check_git_commit_hash(plog ${plog_git_SOURCE_DIR} master)
endif()

FetchContent_Declare(sol2_git
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG        88355fcdf85dfcf52c76e41f75b36cd6ba0b7954)
FetchContent_GetProperties(sol2_git)
if(NOT sol2_git_POPULATED)
    FetchContent_Populate(sol2_git)
    check_git_commit_hash(sol2 ${sol2_git_SOURCE_DIR} develop)
endif()

if(WIN32)
    FetchContent_Declare(cef_tarbz2
        URL            http://opensource.spotify.com/cefbuilds/cef_binary_78.2.9%2Bg4907ec5%2Bchromium-78.0.3904.70_windows64.tar.bz2
        URL_HASH       SHA1=e6bf6a838fe7f7ee640c3f06f95dec09b14b79ca)
elseif(UNIX)
    FetchContent_Declare(cef_tarbz2
        URL            http://opensource.spotify.com/cefbuilds/cef_binary_78.2.9%2Bg4907ec5%2Bchromium-78.0.3904.70_linux64.tar.bz2
        URL_HASH       SHA1=20e2abeec7d70a80b6a3c6a0a9ea92fdb6231a91)
elseif(APPLE)
    FetchContent_Declare(cef_tarbz2
        URL            http://opensource.spotify.com/cefbuilds/cef_binary_78.2.9%2Bg4907ec5%2Bchromium-78.0.3904.70_macosx64.tar.bz2
        URL_HASH       SHA1=f660ca33de62a576cf7b9f033b7e0966130f5580)
else()
    message(FATAL_ERROR "cef: platform not supported")
endif()
FetchContent_GetProperties(cef_tarbz2)
if(NOT cef_tarbz2_POPULATED)
    FetchContent_Populate(cef_tarbz2)
    message(STATUS "cef: ${cef_tarbz2_SOURCE_DIR}")
endif()

add_library(Box2D STATIC
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/Shapes/b2ChainShape.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/Shapes/b2CircleShape.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/Shapes/b2EdgeShape.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/Shapes/b2PolygonShape.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/b2BroadPhase.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/b2CollideCircle.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/b2CollideEdge.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/b2CollidePolygon.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/b2Collision.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/b2Distance.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/b2DynamicTree.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Collision/b2TimeOfImpact.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Common/b2BlockAllocator.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Common/b2Draw.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Common/b2Math.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Common/b2Settings.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Common/b2StackAllocator.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Common/b2Timer.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2CircleContact.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2Contact.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2GearJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2Joint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2MotorJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2MouseJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2RopeJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2WeldJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/Joints/b2WheelJoint.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/b2Body.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/b2ContactManager.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/b2Fixture.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/b2Island.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/b2World.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Dynamics/b2WorldCallbacks.cpp
    ${box2d_git_SOURCE_DIR}/Box2D/Rope/b2Rope.cpp)

target_include_directories(Box2D PUBLIC
    ${box2d_git_SOURCE_DIR})

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

add_subdirectory(${cef_tarbz2_SOURCE_DIR} ${cef_tarbz2_BINARY_DIR} EXCLUDE_FROM_ALL)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${cppcodec_git_SOURCE_DIR}
    ${enet_git_SOURCE_DIR}/include
    ${plog_git_SOURCE_DIR}/include
    ${sol2_git_SOURCE_DIR}/single/include
    ${cef_tarbz2_SOURCE_DIR}
    ${cef_tarbz2_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} INTERFACE
    Box2D
    Catch2
    enet
    nlohmann_json
    lua
    plibsysstatic
    libcef_dll_wrapper)
