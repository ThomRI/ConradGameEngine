#version 150 core

// Inputs 
in vec3 color; // Object color
in vec2 texCoord;
in vec3 fragmentPos;
in vec3 normal;

// Uniform
uniform sampler2D tex;
uniform mat4 normalMatrix;
uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 cameraPos;

// Output
out vec4 out_Color;

void main()
{
	vec3 transformed_normal = mat3(normalMatrix) * normal; // Transforming correctly the normals
	vec3 norm = normalize(transformed_normal);
	vec3 lightDir = normalize(lightPos - fragmentPos); // Object -> Light

	/* Ambient */
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

	/* Diffuse */
	float diffuseExponent = max(0.0, dot(norm, lightDir));
	vec3 diffuse = diffuseExponent * lightColor;

	/* Specular */
	float specularStrength = 1.0;
	vec3 cameraDir = normalize(cameraPos - fragmentPos); // Object -> Camera
	vec3 reflectDir = reflect(-lightDir, norm); // Reflection of (Light -> Object) // of norm

	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	out_Color = texture(tex, texCoord) * vec4((ambient + diffuse + specular) * color, 1.0);
}