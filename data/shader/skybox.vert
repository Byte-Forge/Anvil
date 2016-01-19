layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

uniform mat4 MVP;
uniform vec3 CameraPosition;

out vec2 v_uv;
out vec3 v_normal;

void main(void)
{
	v_uv = uv;
	v_normal = normal;
    //gl_Position = V * P * vec4(vert, 1.0);
	gl_Position = MVP * vec4(vert + CameraPosition, 1.0);

}