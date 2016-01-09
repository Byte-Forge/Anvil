#version 330 core
layout(location = 0) in vec3 vert;
layout(location = 1) in vec4 uv;
layout(location = 2) in vec3 normal;

out vec4 v_uv;
out vec3 v_normal;

void main(void)
{
	v_uv = uv;
	v_normal = normal;
    gl_Position = vec4(vert, 1.0);
}