#version 400 core

layout(vertices = 3) out;

in vec3 v_position[];
in vec3 v_normal[];
in vec2 v_uv[];

uniform mat4 V;

out vec3 tc_position[];
out vec3 tc_normal[];
out vec2 tc_uv[];

void main()
{
	tc_position[gl_InvocationID] = v_position[gl_InvocationID];
	tc_normal[gl_InvocationID] = v_normal[gl_InvocationID];
	tc_uv[gl_InvocationID] = v_uv[gl_InvocationID];
	
	if(gl_InvocationID == 0)
	{
		float level = 32;
		float distance = length((V * vec4(tc_position[gl_InvocationID], 1)).xyz);
		if (distance > 15 )
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
