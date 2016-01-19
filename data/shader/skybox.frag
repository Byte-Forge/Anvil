#version 330 core

in vec2 v_uv;

//uniform samplerCube DiffuseTextureSampler;
uniform sampler2D DiffuseTextureSampler;
out vec3 fragColor;

void main(void)
{
    fragColor = texture2D(DiffuseTextureSampler, v_uv).rgb;
}