declare const l: logger;
declare const m2: material;

print(m2.shininess);
assert(m2.shininess == 14);
m2.shininess = 15;
print(m2.shininess);
assert(m2.shininess == 15);
m2.specular = [11, 22, 33];
print(m2.func);

const m = material.new1();
m.shininess = 12;
m.ambient = [1, 2, 3];
m.diffuse = [4, 5, 6];
m.specular = [7, 8, 9];
print(m.x);
m.x = 200;
print(m.x);
print(m.number);
m.number = 101;
print(m.number);
print(m.y);
print(color.red);
print(color.green);

const vec3_to_string = (v3: [number, number, number]): string =>
    string.format("[%d, %d, %d]", v3[0], v3[1], v3[2]);

l.debug(`printing from ts: ${m}`);
for (const e of m.ambient) {
    l.info(`ambient= ${e}`);
}
for (const e of m.diffuse) {
    l.info(`diffuse= ${e}`);
}
for (const e of m.specular) {
    l.info(`specular= ${e}`);
}
l.info(`shininess= ${m.shininess}`);
l.warning(`m= ${vec3_to_string(m.ambient)}`);

const [x, y, z] = m.ambient;
l.error(`x= ${x} y= ${y} z= ${z}`);

for (let i = 0; i < m.ambient.length; ++i) {
    l.critical(`ambient[${i}]= ${m.ambient[i]}`);
}
