#version 400 core

layout(vertices = 3) out;

in vec3 v_position[];
in vec2 v_uv[];
in vec3 v_normal[];
in vec3 v_material[];

uniform mat4 V;

out vec3 tc_position[];
out vec2 tc_uv[];
out vec3 tc_normal[];
out vec3 tc_material[];

void main()
{
	tc_position[gl_InvocationID] = v_position[gl_InvocationID];
	tc_uv[gl_InvocationID] = v_uv[gl_InvocationID];
	tc_normal[gl_InvocationID] = v_normal[gl_InvocationID];
	tc_material[gl_InvocationID] = v_material[gl_InvocationID];
	
	if(gl_InvocationID == 0)
	{
		float level = 32;

		float distance = length((V * vec4(tc_position[gl_InvocationID], 1)).xyz);
		if (distance > 10)
		{
			level /= 1.8;
		}
		if (distance > 20)
		{
			level /= 2.4;
		}
		if (distance > 25)
		{
			level = 1.0;
		}
	
		gl_TessLevelInner[0] = level;
		gl_TessLevelInner[1] = level;
		gl_TessLevelOuter[0] = level;
		gl_TessLevelOuter[1] = level;
		gl_TessLevelOuter[2] = level;
		gl_TessLevelOuter[3] = level;
	}
}
