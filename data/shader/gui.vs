#version 400

layout(location = 0)in vec4 vert;
layout(location = 1)in vec2 coords;
layout(location = 0) uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vert;
}