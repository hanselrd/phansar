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

add_library(Box2D STATIC
    Box2D/Box2D/Collision/Shapes/b2ChainShape.cpp
    Box2D/Box2D/Collision/Shapes/b2CircleShape.cpp
    Box2D/Box2D/Collision/Shapes/b2EdgeShape.cpp
    Box2D/Box2D/Collision/Shapes/b2PolygonShape.cpp
    Box2D/Box2D/Collision/b2BroadPhase.cpp
    Box2D/Box2D/Collision/b2CollideCircle.cpp
    Box2D/Box2D/Collision/b2CollideEdge.cpp
    Box2D/Box2D/Collision/b2CollidePolygon.cpp
    Box2D/Box2D/Collision/b2Collision.cpp
    Box2D/Box2D/Collision/b2Distance.cpp
    Box2D/Box2D/Collision/b2DynamicTree.cpp
    Box2D/Box2D/Collision/b2TimeOfImpact.cpp
    Box2D/Box2D/Common/b2BlockAllocator.cpp
    Box2D/Box2D/Common/b2Draw.cpp
    Box2D/Box2D/Common/b2Math.cpp
    Box2D/Box2D/Common/b2Settings.cpp
    Box2D/Box2D/Common/b2StackAllocator.cpp
    Box2D/Box2D/Common/b2Timer.cpp
    Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
    Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
    Box2D/Box2D/Dynamics/Contacts/b2CircleContact.cpp
    Box2D/Box2D/Dynamics/Contacts/b2Contact.cpp
    Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
    Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
    Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
    Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
    Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
    Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2GearJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2Joint.cpp
    Box2D/Box2D/Dynamics/Joints/b2MotorJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2MouseJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2RopeJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2WeldJoint.cpp
    Box2D/Box2D/Dynamics/Joints/b2WheelJoint.cpp
    Box2D/Box2D/Dynamics/b2Body.cpp
    Box2D/Box2D/Dynamics/b2ContactManager.cpp
    Box2D/Box2D/Dynamics/b2Fixture.cpp
    Box2D/Box2D/Dynamics/b2Island.cpp
    Box2D/Box2D/Dynamics/b2World.cpp
    Box2D/Box2D/Dynamics/b2WorldCallbacks.cpp
    Box2D/Box2D/Rope/b2Rope.cpp)

target_include_directories(Box2D PUBLIC
    Box2D)

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
    Box2D
    Catch2
    enet
    nlohmann_json
    lua
    plibsysstatic)
