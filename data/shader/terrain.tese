layout(triangles, equal_spacing, ccw) in;

in vec3 tc_position[];
in vec2 tc_uv[];
in vec3 tc_normal[];
in vec3 tc_material[];

in float value;

uniform sampler2DArray DisplacementTextureSampler;

out vec3 e_position;
out vec2 e_uv;
out vec3 e_normal;
out vec3 e_material;

void main()
{
	e_position = gl_TessCoord.x * tc_position[0] + gl_TessCoord.y * tc_position[1] + gl_TessCoord.z * tc_position[2];
	e_uv = gl_TessCoord.x * tc_uv[0] + gl_TessCoord.y * tc_uv[1] + gl_TessCoord.z * tc_uv[2];
	e_normal = normalize(gl_TessCoord.x * tc_normal[0] + gl_TessCoord.y * tc_normal[1] + gl_TessCoord.z * tc_normal[2]);
	e_material = gl_TessCoord.x * tc_material[0] + gl_TessCoord.y * tc_material[1] + gl_TessCoord.z * tc_material[2];
	
	float height = mix(texture(DisplacementTextureSampler, vec3(e_uv, e_material[0])).x, texture(DisplacementTextureSampler, vec3(e_uv, e_material[1])).x, e_material[2]);

	e_position += e_normal * (height * 0.10f * value);
}
