#version 400 core

layout(triangles, equal_spacing, ccw) in;

in vec3 tc_position[];
in vec2 tc_uv[];
in vec3 tc_normal[];
in vec3 tc_material[];

uniform vec3 lightPos;

uniform mat4 M;
uniform mat4 V;
uniform mat3 MV3x3;
uniform mat4 MVP;
uniform sampler2DArray DisplacementTextureSampler;

out vec3 position;
out vec2 uv;
out vec3 normal;
out vec3 material;

out vec3 eyeDir;
out vec3 lightDir;

void main()
{
	vec3 position = gl_TessCoord.x * tc_position[0] + gl_TessCoord.y * tc_position[1] + gl_TessCoord.z * tc_position[2];
	uv = gl_TessCoord.x * tc_uv[0] + gl_TessCoord.y * tc_uv[1] + gl_TessCoord.z * tc_uv[2];
	normal = normalize(gl_TessCoord.x * tc_normal[0] + gl_TessCoord.y * tc_normal[1] + gl_TessCoord.z * tc_normal[2]);
	material = gl_TessCoord.x * tc_material[0] + gl_TessCoord.y * tc_material[1] + gl_TessCoord.z * tc_material[2];

	float height = mix(texture(DisplacementTextureSampler, vec3(uv, material[0])).x, texture(DisplacementTextureSampler, vec3(uv, material[1])).x, material[2]);

    position += normal * (height * 0.05f);
	
	gl_Position = MVP * vec4(position, 1);
	position = (M * vec4(position, 1)).xyz;
	
	vec3 position_cam = (V * M * vec4(position, 1)).xyz;
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
	vertexBitangent_modelspace = normalize(cross(normal, vertexTangent_modelspace)); 

	vec3 vertexTangent_cameraspace = MV3x3 * vertexTangent_modelspace;
	vec3 vertexBitangent_cameraspace = MV3x3 * vertexBitangent_modelspace;
	vec3 vertexNormal_cameraspace = MV3x3 * normal;
	
	mat3 TBN = transpose(mat3(
		vertexTangent_cameraspace,
		vertexBitangent_cameraspace,
		vertexNormal_cameraspace	
	)); 

	lightDir = TBN * lightDir_cam;
	eyeDir =  TBN * eyeDir_cam;
}
