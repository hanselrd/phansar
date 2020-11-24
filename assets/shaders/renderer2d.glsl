#version 330 core

#pragma shader(vertex)

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoord;

out vec2 v_texcoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
    v_texcoord = a_texcoord;
}

#pragma shader(fragment)

in vec2 v_texcoord;

layout(location = 0) out vec4 f_color;

uniform sampler2D u_texture;
uniform vec4 u_color;

void main() {
    f_color = texture(u_texture, v_texcoord) * u_color;
}
