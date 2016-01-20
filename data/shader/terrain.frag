in vec3 position;
in vec2 uv;
in vec3 normal;
in vec3 material;

in vec3 eyeDir;
in vec3 lightDir;

in vec3 col;

uniform bool wireframe;
uniform vec3 lightPos;

uniform sampler2DArray DiffuseTextureSampler;
uniform sampler2DArray NormalTextureSampler;
uniform sampler2DArray SpecularTextureSampler;
uniform sampler2DArray AmbientTextureSampler;

out vec3 color;

void main()
{
	#ifdef WIREFRAME

		color = col;
		
	#else

		vec3 LightColor = vec3(1,1,1);
		float LightPower = 400000.0;

		vec3 MaterialDiffuseColor = texture(DiffuseTextureSampler, vec3(uv, material[0])).rgb;
		
		vec3 MaterialAmbientColor = texture(AmbientTextureSampler,  vec3(uv, material[0])).rgb;
		vec3 MaterialSpecularColor = texture(SpecularTextureSampler,  vec3(uv, material[0])).rgb * 0.3;

		vec3 texNormal = texture(NormalTextureSampler,  vec3(uv, material[0])).rgb*2.0 - 1.0;
		
		MaterialDiffuseColor = mix(MaterialDiffuseColor, texture(DiffuseTextureSampler, vec3(uv, material[1])).rgb, material[2]);
		MaterialAmbientColor = mix(MaterialAmbientColor, texture(AmbientTextureSampler,  vec3(uv, material[1])).rgb, material[2]);
		MaterialSpecularColor = mix(MaterialSpecularColor, texture(SpecularTextureSampler,  vec3(uv, material[0])).rgb * 0.3, material[2]);
		texNormal = mix(texNormal, texture(NormalTextureSampler,  vec3(uv, material[1])).rgb*2.0 - 1.0, material[2]);
			
		texNormal = normalize(texNormal);
		
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

	#endif
}