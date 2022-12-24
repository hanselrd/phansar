-- Lua Library inline imports
local function __TS__CountVarargs(...)
  return select("#", ...)
end

local function __TS__ArraySplice(self, ...)
  local args = { ... }
  local len = #self
  local actualArgumentCount = __TS__CountVarargs(...)
  local start = args[1]
  local deleteCount = args[2]
  if start < 0 then
    start = len + start
    if start < 0 then
      start = 0
    end
  elseif start > len then
    start = len
  end
  local itemCount = actualArgumentCount - 2
  if itemCount < 0 then
    itemCount = 0
  end
  local actualDeleteCount
  if actualArgumentCount == 0 then
    actualDeleteCount = 0
  elseif actualArgumentCount == 1 then
    actualDeleteCount = len - start
  else
    local ____deleteCount_0 = deleteCount
    if ____deleteCount_0 == nil then
      ____deleteCount_0 = 0
    end
    actualDeleteCount = ____deleteCount_0
    if actualDeleteCount < 0 then
      actualDeleteCount = 0
    end
    if actualDeleteCount > len - start then
      actualDeleteCount = len - start
    end
  end
  local out = {}
  for k = 1, actualDeleteCount do
    local from = start + k
    if self[from] ~= nil then
      out[k] = self[from]
    end
  end
  if itemCount < actualDeleteCount then
    for k = start + 1, len - actualDeleteCount do
      local from = k + actualDeleteCount
      local to = k + itemCount
      if self[from] then
        self[to] = self[from]
      else
        self[to] = nil
      end
    end
    for k = len - actualDeleteCount + itemCount + 1, len do
      self[k] = nil
    end
  elseif itemCount > actualDeleteCount then
    for k = len - actualDeleteCount, start + 1, -1 do
      local from = k + actualDeleteCount
      local to = k + itemCount
      if self[from] then
        self[to] = self[from]
      else
        self[to] = nil
      end
    end
  end
  local j = start + 1
  for i = 3, actualArgumentCount do
    self[j] = args[i]
    j = j + 1
  end
  for k = #self, len - actualDeleteCount + itemCount + 1, -1 do
    self[k] = nil
  end
  return out
end

local function __TS__Class(self)
  local c = { prototype = {} }
  c.prototype.__index = c.prototype
  c.prototype.constructor = c
  return c
end

local function __TS__New(target, ...)
  local instance = setmetatable({}, target.prototype)
  instance:____constructor(...)
  return instance
end

-- End of Lua Library inline imports
log = function(...)
  print(...)
end
pi = 3.14159
log("pi = " .. tostring(pi))
myList = { 1, 2, 3 }
myList[#myList + 1] = 4
table.remove(myList)
__TS__ArraySplice(myList, 1, 1)
for ____, e in ipairs(myList) do
  log("myList[elem] = " .. tostring(e))
end
repeat
  local ____switch5 = 0
  local ____cond5 = ____switch5 == 0
  if ____cond5 then
    log("0")
    break
  end
  ____cond5 = ____cond5 or ____switch5 == 1
  if ____cond5 then
    log("1")
    break
  end
until true
Empty = __TS__Class()
Empty.name = "Empty"
function Empty.prototype.____constructor(self)
end

Point = __TS__Class()
Point.name = "Point"
function Point.prototype.____constructor(self)
  self.x = 0
  self.y = 0
end

pt = __TS__New(Point)
print((tostring(pt.x) .. ", ") .. tostring(pt.y))
Greeter = __TS__Class()
Greeter.name = "Greeter"
function Greeter.prototype.____constructor(self)
  self.name = "hello"
end

G = __TS__New(Greeter)
print(G.name)
