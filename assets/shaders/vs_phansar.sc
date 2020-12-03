$input a_position, a_normal, a_tangent, a_bitangent, a_texcoord0
$output v_position, v_normal, v_tangent, v_bitangent, v_texcoord0

#include <bgfx_shader.sh>

uniform mat3 u_normal;

void main() {
    v_position = mul(u_modelView, vec4(a_position, 1.0)).xyz;
    v_normal = normalize(mul(u_normal, a_normal));
    v_tangent = normalize(mul(u_normal, a_tangent));
    v_bitangent = normalize(mul(u_normal, a_bitangent));
    v_texcoord0 = a_texcoord0;
#if BGFX_SHADER_LANGUAGE_GLSL
    v_texcoord0.y *= -1.0;
#endif

    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}
