$input v_position, v_color0, v_texcoord0, v_normal

#include <bgfx_shader.sh>

// material
SAMPLER2D(s_material_diffuse, 0);
SAMPLER2D(s_material_specular, 1);
uniform vec4 u_material_ambient;
uniform vec4 u_material_diffuse;
uniform vec4 u_material_specular;
uniform vec4 u_material_tint;

uniform vec4 u_light_position;
uniform vec4 u_camera_position;

vec3 calc_ambient(vec3 u_material_ambient) {
    return u_material_ambient;
}

vec3 calc_diffuse(vec3 u_material_diffuse, vec3 v_position, vec3 v_normal, vec3 u_light_position) {
    vec3 pos_light_dir = normalize(v_position - u_light_position);
    float diffuse = clamp(dot(pos_light_dir, v_normal), 0, 1);
    return u_material_diffuse * diffuse;
}

vec3 calc_specular(vec3 u_material_specular, vec3 v_position, vec3 v_normal, vec3 u_light_position, vec3 u_camera_position) {
    vec3 light_pos_dir = normalize(u_light_position - v_position);
    vec3 reflect_dir = normalize(reflect(light_pos_dir, normalize(v_normal)));
    vec3 pos_view_dir = normalize(v_position - u_camera_position);
    float specular = pow(max(dot(pos_view_dir, reflect_dir), 0), 100);
    return u_material_specular * specular;
}

void main() {
    vec3 ambient_final = calc_ambient(u_material_ambient.xyz);
    vec3 diffuse_final = calc_diffuse(u_material_diffuse.xyz, v_position, v_normal, u_light_position.xyz);
    vec3 specular_final = calc_specular(u_material_specular.xyz, v_position, v_normal, u_light_position.xyz, u_camera_position.xyz);

    gl_FragColor = texture2D(s_material_diffuse, v_texcoord0.xy) * v_color0 * u_material_tint * (vec4(ambient_final, 1.0) + vec4(diffuse_final, 1.0) + vec4(specular_final, 1.0));
}
