#version 150 core

// Inputs
in vec3 in_Vertex;
in vec3 in_VertexColor;
in vec2 in_TexCoord0;
in vec3 in_VertexNormal;

// Uniforms
uniform mat4 projection;
uniform mat4 camera;

// Mesh-specific uniforms
uniform mat4 modelview;


// Outputs
out vec3 frag_VertexColor;
out vec2 frag_TexCoord0;
out vec3 frag_FragmentPos; // Position of the fragment
out vec3 frag_Normal;

void main()
{
	mat3 modelview3 = mat3(modelview);

	// To fragment
	frag_VertexColor = in_VertexColor;
	frag_TexCoord0 = in_TexCoord0;
	frag_FragmentPos = modelview3 * in_Vertex;
	frag_Normal = in_VertexNormal;

	gl_Position = projection * camera * modelview * vec4(in_Vertex, 1.0);
}