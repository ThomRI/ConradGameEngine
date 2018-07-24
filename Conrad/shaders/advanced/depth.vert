#version 150 core

// Inputs
in vec3 in_Vertex;

// Uniforms
uniform mat4 world; // (Projection * Light view) matrix
uniform mat4 modelview;

void main()
{
	gl_Position = world * modelview * vec4(in_Vertex, 1.0);
}