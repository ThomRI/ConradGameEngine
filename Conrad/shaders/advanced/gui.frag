#version 150 core

in vec2 frag_texCoord0;
uniform sampler2D tex;

out vec4 out_Color;

void main()
{
	out_Color = texture(tex, frag_texCoord0) * vec4(1.0);
}