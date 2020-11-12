#version 330 core

#pragma shader(vertex)

layout(location = 0) in vec4 position;

void main() {
    gl_Position = position;
}

#pragma shader(fragment)

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main() {
    color = u_color;
}
