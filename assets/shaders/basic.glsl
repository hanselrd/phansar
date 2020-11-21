#version 330 core

#pragma shader(vertex)

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

out vec4 v_color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
    v_color = a_color;
}

#pragma shader(fragment)

in vec4 v_color;

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main() {
    color = u_color;
    color = v_color;
}
