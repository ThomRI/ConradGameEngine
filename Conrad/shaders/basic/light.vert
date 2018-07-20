#version 150 core

// Inputs
in vec3 in_Vertex;
in vec3 in_Color;
in vec2 in_TexCoord0;
in vec3 in_VertexNormal;

// Uniform
uniform mat4 projection;
uniform mat4 camera;
uniform mat4 modelview;

// Output
out vec3 color;
out vec2 texCoord;
out vec3 fragmentPos;
out vec3 normal;

void main()
{
	mat3 model3 = mat3(modelview);

	// To fragment
	color = in_Color;
	texCoord = in_TexCoord0;
	fragmentPos = model3 * in_Vertex;
	normal = in_VertexNormal;

	gl_Position = projection * camera * modelview * vec4(in_Vertex, 1.0);
}