#version 400 core

in vec3 position;
in vec3 normal;
in vec2 uv;

in vec3 eyeDir;
in vec3 lightDir;

uniform vec3 lightPos;

uniform sampler2DArray DiffuseTextureSampler;
uniform sampler2D NormalTextureSampler;
uniform sampler2D SpecularTextureSampler;
uniform sampler2D AmbientTextureSampler;

out vec3 color;

void main()
{
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 2000.0;

	vec3 MaterialDiffuseColor = texture(DiffuseTextureSampler, vec3(uv, 0)).rgb;
	vec3 MaterialAmbientColor = texture(AmbientTextureSampler, uv).rgb;
	vec3 MaterialSpecularColor = texture(SpecularTextureSampler, uv).rgb * 0.3;

	vec3 texNormal = normalize(texture(NormalTextureSampler, uv).rgb*2.0 - 1.0);
	
	float distance = length(lightPos - position);
	
	vec3 n = texNormal; //apply the input normal here
	vec3 l = normalize(lightDir);
	float cosTheta = clamp( dot( n,l ), 0,1 );
	vec3 E = normalize(eyeDir);
	vec3 R = reflect(-l,n);
	float cosAlpha = clamp( dot( E,R ), 0,1 );

	color = 
		(MaterialAmbientColor * MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance)) +
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);
}