#version 330 core

#pragma shader(vertex)

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 v_color;

void main() {
    gl_Position = position;
    v_color = color;
}

#pragma shader(fragment)

in vec4 v_color;

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main() {
    /* color = u_color; */
    color = v_color;
}
