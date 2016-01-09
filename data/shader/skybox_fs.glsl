#version 330 core

in vec4 v_uv;

uniform samplerCube DiffuseTextureSampler;
out vec4 fragColor;

void main(void)
{
    fragColor = texture(DiffuseTextureSampler, v_uv.xyz);
}