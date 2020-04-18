--[[
  This file is part of Phansar.

  Copyright (C) 2018  Hansel De La Cruz

  Phansar is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Phansar is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
--]]

-- This script serves as documentation for the game's phansar.common API

local common = phansar.common
local bitmasks = common.bitmasks
local components = common.components
local models = common.models
local utils = common.utils
local log = utils.log

-- bitmasks

-- Permissions
log.debug("NONE: "..bitmasks.Permissions.NONE)
log.debug("VETERAN: "..bitmasks.Permissions.VETERAN)
log.debug("DONOR: "..bitmasks.Permissions.DONOR)
log.debug("INTERN: "..bitmasks.Permissions.INTERN)
log.debug("ADVISOR: "..bitmasks.Permissions.ADVISOR)
log.debug("MODERATOR: "..bitmasks.Permissions.MODERATOR)
log.debug("ADMINISTRATOR: "..bitmasks.Permissions.ADMINISTRATOR)
log.debug("OWNER: "..bitmasks.Permissions.OWNER)
log.debug("ROOT: "..bitmasks.Permissions.ROOT)
log.debug("(MODERATOR | DONOR): "..(bitmasks.Permissions.MODERATOR | bitmasks.Permissions.DONOR))

-- components

-- Color
local c = components.Color.new()
c.r = 10
c.g = 20
c.b = 30
c.a = 40
log.debug(string.format("c: (%g, %g, %g, %g) [%s]", c.r, c.g, c.b, c.a, c))

-- Rectf
local rf = components.Rectf.new()
rf.x = 1.1
rf.y = 1.2
rf.w = 1.3
rf.h = 1.4
log.debug(string.format("rf: (%g, %g, %g, %g) [%s]", rf.x, rf.y, rf.w, rf.h, rf))

-- Vec2f
local v2f = components.Vec2f.new()
v2f.x = 1.5
v2f.y = 1.6
log.debug(string.format("v2f: (%g, %g) [%s]", v2f.x, v2f.y, v2f))

-- Vec3f
local v3f = components.Vec3f.new()
v3f.x = 1.7
v3f.y = 1.8
v3f.z = 1.9
log.debug(string.format("v3f: (%g, %g, %g) [%s]", v3f.x, v3f.y, v3f.z, v3f))

-- models

-- Entity
local e1 = models.Entity.new()
e1.map_id = 10
log.debug(string.format("e1: position: (%g, %g, %g), map_id: %d [%s]",
    e1.position.x, e1.position.y, e1.position.z,
    e1.map_id,
    e1))

local e2 = models.Entity.new(components.Vec3f.new(1.1, 2.2, 3.3))
e2:move(components.Vec3f.new(-2.2, -4.4, -6.6))
e2.map_id = 20
log.debug(string.format("e2: position: (%g, %g, %g), map_id: %d [%s]",
    e2.position.x, e2.position.y, e2.position.z,
    e2.map_id,
    e2))

-- Player
local p = models.Player.new()
p.name = "player"
p.position = components.Vec3f.new(4.4, 5.5, 6.6)
p:move(components.Vec3f.new(-8.8, -11.0, -13.2))
p.map_id = 30
log.debug(string.format("p: name: %s, permissions: %d, position: (%g, %g, %g), map_id: %d [%s]",
    p.name,
    p.permissions,
    p.position.x, p.position.y, p.position.z,
    p.map_id,
    p))

-- utils

-- log
log.trace("trace")
log.debug("debug")
log.info("info")
log.warn("warn")
log.error("error")
log.critical("critical")