#version 400 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_uv;

void main(){
    v_uv = in_uv;
	v_normal = in_normal;
    v_position = in_position;
}