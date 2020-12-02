$input a_position, a_color0, a_texcoord0, a_normal
$output v_position, v_color0, v_texcoord0, v_normal

#include <bgfx_shader.sh>

uniform mat3 u_normal;

void main() {
    v_position = mul(u_modelView, vec4(a_position, 1.0)).xyz;
    v_color0 = a_color0;
    v_texcoord0 = a_texcoord0;
#if BGFX_SHADER_LANGUAGE_GLSL
    v_texcoord0.y *= -1.0;
#endif
    v_normal = mul(u_normal, a_normal);

    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}
