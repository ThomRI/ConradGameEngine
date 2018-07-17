#version 150 core


// Inputs
in vec3 color;
in vec2 texCoord;


// Uniform
uniform sampler2D tex;


// Output
out vec4 out_Color;

void main()
{
    out_Color = texture(tex, texCoord) * vec4(color, 1.0);
}
