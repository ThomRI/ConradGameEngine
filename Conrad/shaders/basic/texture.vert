#version 150 core


// Inputs
in vec3 in_Vertex;
in vec3 in_Color;
in vec2 in_TexCoord0;


// Uniform
uniform mat4 projection;
uniform mat4 modelview;


// Output
out vec3 color;
out vec2 texCoord;

void main()
{

    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);

    // To fragment
    color = in_Color;
    texCoord = in_TexCoord0;
}
