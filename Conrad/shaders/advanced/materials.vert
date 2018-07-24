#version 150 core
#define MAX_LIGHTS 10 // Must be synced with fragment shader!

// Inputs
in vec3 in_Vertex;
in vec3 in_VertexColor;
in vec2 in_TexCoord0;
in vec3 in_VertexNormal;

// Uniforms
uniform mat4 projection;
uniform mat4 camera;

uniform struct Light {
	int type;

	vec3 position;
	vec3 color;
	float intensity;
	float attenuation;

	/* Directional and cone */
	vec3 direction;
	float coneAngle;

	/* Shadow */
	mat4 world; // Light space matrix
	bool castShadow;
	sampler2D shadowMapTex;
} lights[MAX_LIGHTS];

// Mesh-specific uniforms
uniform mat4 modelview;


// Outputs
out vec3 frag_VertexColor;
out vec2 frag_TexCoord0;
out vec3 frag_FragmentPos; // Position of the fragment
out vec3 frag_Normal;
out vec4 fragPos_lightspace[MAX_LIGHTS];

void main()
{
	mat3 modelview3 = mat3(modelview);

	// To fragment
	frag_VertexColor = in_VertexColor;
	frag_TexCoord0 = in_TexCoord0;
	frag_FragmentPos = vec3(modelview * vec4(in_Vertex, 1.0));
	frag_Normal = in_VertexNormal;

	for(int i = 0;i < MAX_LIGHTS;i++) {
		fragPos_lightspace[i] = lights[i].world * vec4(frag_FragmentPos, 1.0);
	}

	gl_Position = projection * camera * modelview * vec4(in_Vertex, 1.0);
}