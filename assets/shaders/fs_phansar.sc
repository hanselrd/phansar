$input v_position, v_color0, v_texcoord0, v_normal

#include <bgfx_shader.sh>

// material
uniform vec4 u_material_ambient;
uniform vec4 u_material_diffuse;
uniform vec4 u_material_specular;
uniform vec4 u_material_tint;
SAMPLER2D(s_material_diffuse, 0);
SAMPLER2D(s_material_specular, 1);

uniform vec4 u_light_position;
uniform vec4 u_camera;

void main() {
    // ambient
    vec3 ambient_final = u_material_ambient.xyz;

    // diffuse
    vec3 pos_light_dir = normalize(v_position - u_light_position.xyz);
    float diffuse = clamp(dot(pos_light_dir, v_normal), 0, 1);
    vec3 diffuse_final = u_material_diffuse.xyz * diffuse;

    // specular
    vec3 light_pos_dir = normalize(u_light_position.xyz - v_position);
    vec3 reflect_dir = normalize(reflect(light_pos_dir, normalize(v_normal)));
    vec3 pos_view_dir = normalize(v_position - u_camera.xyz);
    float specular = pow(max(dot(pos_view_dir, reflect_dir), 0), 100);
    vec3 specular_final = u_material_specular.xyx * specular;

    gl_FragColor = texture2D(s_material_diffuse, v_texcoord0.xy) * v_color0 * u_material_tint * (vec4(ambient_final, 1.0) + vec4(diffuse_final, 1.0) + vec4(specular_final, 1.0));
}
