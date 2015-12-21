#version 330 core
layout(location = 0) in vec2 vert;
layout(location = 1) in vec2 txCoord;

out vec2 coord;
void main(void)
{
    gl_Position = vec4(vert,0.0,1.0);
    coord = txCoord;
}