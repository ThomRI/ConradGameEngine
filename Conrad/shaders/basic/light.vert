#version 150 core

// Inputs
in vec3 in_Vertex;
in vec3 in_Color;
in vec2 in_TexCoord0;
in vec3 in_VertexNormal;

// Uniform
uniform mat4 projection;
uniform mat4 modelview;

// Output
out vec3 color;
out vec2 texCoord;
out vec3 fragmentPosition;
out vec3 normal;

void main()
{
	vec4 pos = modelview * vec4(in_Vertex, 1.0);
	gl_Position = projection * pos;

	// To fragment
	color = in_Color;
	texCoord = in_TexCoord0;
	fragmentPosition = vec3(pos);
	normal = in_VertexNormal;
}