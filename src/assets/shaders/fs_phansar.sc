$input v_position, v_normal, v_tangent, v_bitangent, v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(s_material_diffuse, 0);
SAMPLER2D(s_material_specular, 1);
SAMPLER2D(s_material_emissive, 2);
uniform vec4 u_material_ambient; // vec3
uniform vec4 u_material_diffuse; // vec3
uniform vec4 u_material_specular; // vec3
uniform vec4 u_material_shininess; // float

#define DIRECTIONAL_LIGHT_COUNT (1)
uniform vec4 u_directional_light_direction[DIRECTIONAL_LIGHT_COUNT]; // vec3
uniform vec4 u_directional_light_ambient[DIRECTIONAL_LIGHT_COUNT]; // vec3
uniform vec4 u_directional_light_diffuse[DIRECTIONAL_LIGHT_COUNT]; // vec3
uniform vec4 u_directional_light_specular[DIRECTIONAL_LIGHT_COUNT]; // vec3

#define POINT_LIGHT_COUNT (1)
uniform vec4 u_point_light_position[POINT_LIGHT_COUNT]; // vec3
uniform vec4 u_point_light_ambient[POINT_LIGHT_COUNT]; // vec3
uniform vec4 u_point_light_diffuse[POINT_LIGHT_COUNT]; // vec3
uniform vec4 u_point_light_specular[POINT_LIGHT_COUNT]; // vec3
uniform vec4 u_point_light_attenuation[POINT_LIGHT_COUNT]; // float[3]
#define u_point_light_attenuation_kc(_index) (u_point_light_attenuation[_index].x)
#define u_point_light_attenuation_kl(_index) (u_point_light_attenuation[_index].y)
#define u_point_light_attenuation_kq(_index) (u_point_light_attenuation[_index].z)

#define SPOT_LIGHT_COUNT (1)
uniform vec4 u_spot_light_position[SPOT_LIGHT_COUNT]; // vec3
uniform vec4 u_spot_light_direction[SPOT_LIGHT_COUNT]; // vec3
uniform vec4 u_spot_light_ambient[SPOT_LIGHT_COUNT]; // vec3
uniform vec4 u_spot_light_diffuse[SPOT_LIGHT_COUNT]; // vec3
uniform vec4 u_spot_light_specular[SPOT_LIGHT_COUNT]; // vec3
uniform vec4 u_spot_light_attenuation[SPOT_LIGHT_COUNT]; // float[3]
#define u_spot_light_attenuation_kc(_index) (u_spot_light_attenuation[_index].x)
#define u_spot_light_attenuation_kl(_index) (u_spot_light_attenuation[_index].y)
#define u_spot_light_attenuation_kq(_index) (u_spot_light_attenuation[_index].z)
uniform vec4 u_spot_light_cutoff[SPOT_LIGHT_COUNT]; // float[2]
#define u_spot_light_cutoff_inner(_index) (u_spot_light_cutoff[_index].x)
#define u_spot_light_cutoff_outer(_index) (u_spot_light_cutoff[_index].y)

vec3 calculate_directional_light(vec3 _light_direction, vec3 _light_ambient, vec3 _light_diffuse, vec3 _light_specular, vec3 _position, vec3 _normal, vec2 _texcoord0) {
    vec3 light_directionView = mul(u_view, vec4(_light_direction, 0.0)).xyz;
    vec3 light_dir = normalize(-light_directionView);
    vec3 view_dir = normalize(-_position);
    vec3 normal = normalize(_normal);

    float diffuse = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float specular = pow(max(dot(view_dir, reflect_dir), 0.0), u_material_shininess.x);

    vec3 result = (_light_ambient * u_material_ambient.xyz * texture2D(s_material_diffuse, _texcoord0).rgb) +
                  (_light_diffuse * u_material_diffuse.xyz * diffuse * texture2D(s_material_diffuse, _texcoord0).rgb) +
                  (_light_specular * u_material_specular.xyz * specular * texture2D(s_material_specular, _texcoord0).rgb);

    return result;
}

vec3 calculate_point_light(vec3 _light_position, vec3 _light_ambient, vec3 _light_diffuse, vec3 _light_specular, float _light_attenuation_kc, float _light_attenuation_kl, float _light_attenuation_kq, vec3 _position, vec3 _normal, vec2 _texcoord0) {
    vec3 light_positionView = mul(u_view, vec4(_light_position, 0.0)).xyz;
    vec3 light_dir = normalize(light_positionView - _position);
    vec3 view_dir = normalize(-_position);
    vec3 normal = normalize(_normal);

    float diffuse = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float specular = pow(max(dot(view_dir, reflect_dir), 0.0), u_material_shininess.x);

    float distance = length(light_positionView - _position);
    float attenuation = 1.0 / (_light_attenuation_kc + (_light_attenuation_kl * distance) + (_light_attenuation_kq * distance * distance));

    vec3 result = (_light_ambient * u_material_ambient.xyz * texture2D(s_material_diffuse, _texcoord0).rgb * attenuation) +
                  (_light_diffuse * u_material_diffuse.xyz * diffuse * texture2D(s_material_diffuse, _texcoord0).rgb * attenuation) +
                  (_light_specular * u_material_specular.xyz * specular * texture2D(s_material_specular, _texcoord0).rgb * attenuation);

    return result;
}

vec3 calculate_spot_light(vec3 _light_position, vec3 _light_direction, vec3 _light_ambient, vec3 _light_diffuse, vec3 _light_specular, float _light_attenuation_kc, float _light_attenuation_kl, float _light_attenuation_kq, float _light_cutoff_inner, float _light_cutoff_outer, vec3 _position, vec3 _normal, vec2 _texcoord0) {
    vec3 light_positionView = mul(u_view, vec4(_light_position, 0.0)).xyz;
    vec3 light_directionView = mul(u_view, vec4(_light_direction, 0.0)).xyz;
    vec3 light_dir = normalize(light_positionView - _position);
    vec3 view_dir = normalize(-_position);
    vec3 normal = normalize(_normal);

    float diffuse = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float specular = pow(max(dot(view_dir, reflect_dir), 0.0), u_material_shininess.x);

    float distance = length(light_positionView - _position);
    float attenuation = 1.0 / (_light_attenuation_kc + (_light_attenuation_kl * distance) + (_light_attenuation_kq * distance * distance));

    float theta = dot(light_dir, normalize(-light_directionView));
    float epsilon = _light_cutoff_inner - _light_cutoff_outer;
    float intensity = clamp((theta - _light_cutoff_outer) / epsilon, 0.0, 1.0);

    vec3 result = (_light_ambient * u_material_ambient.xyz * texture2D(s_material_diffuse, _texcoord0).rgb * attenuation * intensity) +
                  (_light_diffuse * u_material_diffuse.xyz * diffuse * texture2D(s_material_diffuse, _texcoord0).rgb * attenuation * intensity) +
                  (_light_specular * u_material_specular.xyz * specular * texture2D(s_material_specular, _texcoord0).rgb * attenuation * intensity);

    return result;
}

void main() {
    vec3 result = vec3_splat(0.0);

    for (int i = 0; i < DIRECTIONAL_LIGHT_COUNT; ++i) {
        result += calculate_directional_light(u_directional_light_direction[i].xyz, u_directional_light_ambient[i].xyz, u_directional_light_diffuse[i].xyz, u_directional_light_specular[i].xyz, v_position, v_normal, v_texcoord0);
    }

    // for (int i = 0; i < POINT_LIGHT_COUNT; ++i) {
    //     result += calculate_point_light(u_point_light_position[i].xyz, u_point_light_ambient[i].xyz, u_point_light_diffuse[i].xyz, u_point_light_specular[i].xyz, u_point_light_attenuation_kc(i), u_point_light_attenuation_kl(i), u_point_light_attenuation_kq(i), v_position, v_normal, v_texcoord0);
    // }

    // for (int i = 0; i < SPOT_LIGHT_COUNT; ++i) {
    //     result += calculate_spot_light(u_spot_light_position[i].xyz, u_spot_light_direction[i].xyz, u_spot_light_ambient[i].xyz, u_spot_light_diffuse[i].xyz, u_spot_light_specular[i].xyz, u_spot_light_attenuation_kc(i), u_spot_light_attenuation_kl(i), u_spot_light_attenuation_kq(i), u_spot_light_cutoff_inner(i), u_spot_light_cutoff_outer(i), v_position, v_normal, v_texcoord0);
    // }

    gl_FragColor = vec4(result + (texture2D(s_material_emissive, v_texcoord0).rgb * step(vec3_splat(1.0), vec3_splat(1.0) - texture2D(s_material_specular, v_texcoord0).rgb)), 1.0);
}
