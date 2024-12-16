#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 in_color;

out vec3 out_color;

uniform mat4 pvm;

void main()
{
    gl_Position = pvm * vec4(pos, 1.0);
    out_color = in_color;
}
