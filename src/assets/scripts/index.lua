print(m2.shininess)
assert(m2.shininess == 14)
m2.shininess = 15
print(m2.shininess)
assert(m2.shininess == 15)
m2.specular = { 11, 22, 33 }
print(m2.func)
m = material.new1()
m.shininess = 12
m.ambient = { 1, 2, 3 }
m.diffuse = { 4, 5, 6 }
m.specular = { 7, 8, 9 }
print(m.x)
m.x = 200
print(m.x)
print(m.number)
m.number = 101
print(m.number)
print(m.y)
print(color.red)
print(color.green)
vec3_to_string = function(v3) return string.format("[%d, %d, %d]", v3[1], v3[2], v3[3]) end
l:debug("printing from ts: " .. tostring(m))
for ____, e in ipairs(m.ambient) do
  l:info("ambient= " .. tostring(e))
end
for ____, e in ipairs(m.diffuse) do
  l:info("diffuse= " .. tostring(e))
end
for ____, e in ipairs(m.specular) do
  l:info("specular= " .. tostring(e))
end
l:info("shininess= " .. tostring(m.shininess))
l:warning("m= " .. vec3_to_string(m.ambient))
x, y, z = table.unpack(m.ambient)
l:error((((("x= " .. tostring(x)) .. " y= ") .. tostring(y)) .. " z= ") .. tostring(z))
do
  i = 0
  while i < #m.ambient do
    l:critical((("ambient[" .. tostring(i)) .. "]= ") .. tostring(m.ambient[i + 1]))
    i = i + 1
  end
end
