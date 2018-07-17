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
    // Position finale du vertex en 3D

    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);


    // Envoi des coordonnées de texture au Fragment Shader

    color = in_Color;
    texCoord = in_TexCoord0;
}
