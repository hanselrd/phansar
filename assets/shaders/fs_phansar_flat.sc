$input v_position, v_normal, v_tangent, v_bitangent, v_texcoord0

#include <bgfx_shader.sh>

uniform vec4 u_material_color;

void main() {
    gl_FragColor = u_material_color;
}
