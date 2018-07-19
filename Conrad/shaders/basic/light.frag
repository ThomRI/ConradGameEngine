#version 150 core

// Inputs 
in vec3 color;
in vec2 texCoord;
in vec3 fragmentPosition;
in vec3 normal;

// Uniform
uniform sampler2D tex;
uniform vec3 lightPos;

// Output
out vec4 out_Color;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragmentPosition);

	float diffuseExponent = max(0.0, dot(norm, lightDir));
	vec3 diffuse = diffuseExponent * vec3(1.0, 1.0, 1.0);

	out_Color = texture(tex, texCoord) * vec4(diffuse * color, 1.0);
}