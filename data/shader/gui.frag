in vec2 coord;
in vec4 vertColor;

uniform sampler2D tex;
uniform bool useTex;
out vec4 fragColor;

void main(void)
{
    if(useTex)
    	fragColor = texture(tex, coord)*vertColor;
	else
		fragColor = vertColor;
}