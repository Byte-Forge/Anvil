layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 txCoord;
layout(location = 2) in vec4 color;

out vec2 coord;
out vec4 vertColor;

uniform vec2 translation;
uniform mat4 ortho;

void main(void)
{
    vec2 tran_pos = pos + translation;
	gl_Position = ortho * vec4(tran_pos,0.0f, 1.0f);
    coord = txCoord;
    vertColor = color;
}