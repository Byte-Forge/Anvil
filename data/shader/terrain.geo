#version 400 core

layout(triangles) in;

//for wireframe
layout(line_strip, max_vertices = 3) out; 

//for default rendering
//layout(triangle_strip, max_vertices = 3) out;

in vec3 e_position[];
in vec2 e_uv[];
in vec3 e_normal[];
in vec3 e_material[];

uniform vec3 lightPos;

uniform mat4 M;
uniform mat4 V;
uniform mat3 MV3x3;
uniform mat4 MVP;

out vec3 position;
out vec2 uv;
out vec3 normal;
out vec3 material;

out vec3 eyeDir;
out vec3 lightDir;

void calculateLightingData(int i)
{
	//calculate tangents and binormals
	position = (M * vec4(e_position[i], 1)).xyz;

	vec3 position_cam = (V * M * vec4(e_position[i], 1)).xyz;
	vec3 eyeDir_cam = vec3(0,0,0) - position_cam;

	vec3 lightPos_cam = (V * vec4(lightPos, 1)).xyz;
	vec3 lightDir_cam = lightPos_cam + eyeDir_cam;

	vec3 vertexTangent_modelspace;
	vec3 vertexBitangent_modelspace;

	vec3 c1 = cross(normal, vec3(0.0, 0.0, 1.0)); 
	vec3 c2 = cross(normal, vec3(0.0, 1.0, 0.0)); 
	if (length(c1) > length(c2))
		vertexTangent_modelspace = c1;	
	else
		vertexTangent_modelspace = c2;	
	vertexTangent_modelspace = normalize(vertexTangent_modelspace);
	vertexBitangent_modelspace = normalize(cross(e_normal[i], vertexTangent_modelspace)); 

	vec3 vertexTangent_cameraspace = MV3x3 * vertexTangent_modelspace;
	vec3 vertexBitangent_cameraspace = MV3x3 * vertexBitangent_modelspace;
	vec3 vertexNormal_cameraspace = MV3x3 * e_normal[i];
	
	mat3 TBN = transpose(mat3(
		vertexTangent_cameraspace,
		vertexBitangent_cameraspace,
		vertexNormal_cameraspace	
	)); 

	lightDir = TBN * lightDir_cam;
	eyeDir =  TBN * eyeDir_cam;
}


void createPt(int i)
{
	material = e_material[i];
	normal = normalize(e_normal[i]);
    uv = e_uv[i];

	calculateLightingData(i);
	
    gl_Position = MVP * vec4(e_position[i], 1.0);
	EmitVertex();
}


void main()
{
	int i;
	for(i=0; i < gl_in.length(); i++)
	{
		createPt(i);
	}
	EndPrimitive();
	
	for(i=0; i < gl_in.length(); i++)
	{
		gl_Position = MVP * vec4(e_position[i], 1.0);
		EmitVertex();
		
		gl_Position = MVP * vec4(e_position[i] + e_normal[i], 1.0);
		EmitVertex();
		
		gl_Position = MVP * vec4(e_position[i] + e_normal[i] + vec3(0.1, 0.0, 0.01), 1.0);
		EmitVertex();
		
		EndPrimitive();
	}
}
