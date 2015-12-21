#version 330 core
in vec2 coord;
uniform sampler2D tex;
out vec4 fragColor;

void main(void)
{
    fragColor = texture2D(tex, coord);
    if (fragColor.a < 0.1)
    {
        discard;
    }
}