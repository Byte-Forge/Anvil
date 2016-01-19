#version 330 core
in vec2 coord;
in vec4 vertColor;

uniform sampler2D tex;
out vec4 fragColor;

void main(void)
{
    if(texture(tex, coord) == vec4(0, 0, 0, 1))
    	fragColor = vertColor;
	else
		fragColor = texture(tex, coord) * vertColor;
}