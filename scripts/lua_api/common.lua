-- This script serves as documentation for the game's phansar.common API

local common = phansar.common
local bitmasks = common.bitmasks
local core = common.core
local log = core.log
local models = common.models

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

-- core

-- log
log.verbose("verbose")
log.debug("debug")
log.info("info")
log.warning("warning")
log.error("error")
log.fatal("fatal")
log.none("none")

-- types
local v2f = core.types.Vector2f.new()
v2f.x = 1.2
v2f.y = 1.3
log.debug(string.format("v2f: (%g, %g) [%s]", v2f.x, v2f.y, v2f))

local v3f = core.types.Vector3f.new()
v3f.x = 1.4
v3f.y = 1.5
v3f.z = 1.6
log.debug(string.format("v3f: (%g, %g, %g) [%s]", v3f.x, v3f.y, v3f.z, v3f))

-- models

-- Entity
e1 = models.Entity.new()
e1.map_id = 10
log.debug(string.format("e1: position: (%g, %g, %g), map_id: %d [%s]",
    e1.position.x, e1.position.y, e1.position.z,
    e1.map_id,
    e1))

e2 = models.Entity.new(core.types.Vector3f.new(1.1, 2.2, 3.3))
e2:move(core.types.Vector3f.new(-2.2, -4.4, -6.6))
e2.map_id = 20
log.debug(string.format("e2: position: (%g, %g, %g), map_id: %d [%s]",
    e2.position.x, e2.position.y, e2.position.z,
    e2.map_id,
    e2))

-- Player
p = models.Player.new()
p.name = "player"
p.position = core.types.Vector3f.new(4.4, 5.5, 6.6)
p:move(core.types.Vector3f.new(-8.8, -11.0, -13.2))
p.map_id = 30
log.debug(string.format("p: name: %s, permissions: %d, position: (%g, %g, %g), map_id: %d [%s]",
    p.name,
    p.permissions,
    p.position.x, p.position.y, p.position.z,
    p.map_id,
    p))
