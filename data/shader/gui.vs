#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

layout(location = 0) in vec4 vert;
layout(location = 1) in vec2 coords;
layout(location = 0) uniform mat4 mvp;

void main(void)
{
    gl_Position = mvp * vert;
}