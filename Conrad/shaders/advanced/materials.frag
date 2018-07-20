#version 150 core

// Inputs
in vec3 frag_VertexColor;
in vec2 frag_TexCoord0;
in vec3 frag_FragmentPos;
in vec3 frag_Normal;


// Uniforms
uniform sampler2D tex;
uniform mat4 normalMatrix; // Transformations for the normals (same for every pixels so calculated by the CPU)
uniform vec3 lightPos; // One light for now..
uniform vec3 lightColor;
uniform vec3 cameraPos;

/* Light-related uniforms */
uniform vec3 ambientColor;
uniform float ambientStrength; 

uniform vec3 diffuseColor;
uniform float diffuseStrength;

uniform vec3 specularColor;
uniform float specularStrength;
uniform float specularExponent; // [0; 100]

// uniform vec3 emitColor; // emitting is not supported yet.


// Outputs
out vec4 out_Color;

void main()
{
	vec3 transformed_normal = mat3(normalMatrix) * frag_Normal;
	transformed_normal = normalize(transformed_normal);
	vec3 lightDir = normalize(lightPos - frag_FragmentPos); // Object -> Light

	/* Ambient */
	vec3 ambient = ambientStrength * ambientColor;

	/* Diffuse */
	vec3 diffuse = diffuseStrength * max(0.0, dot(transformed_normal, lightDir)) * diffuseColor;

	/* Specular */
	vec3 cameraDir = normalize(cameraPos - frag_FragmentPos); // Object -> Camera
	vec3 reflected_lightDir = reflect(-lightDir, transformed_normal);

	vec3 specular = specularStrength * pow(max(0.0, dot(cameraDir, reflected_lightDir)), specularExponent) * specularColor;

	out_Color = texture(tex, frag_TexCoord0) * vec4((ambient + diffuse + specular) * lightColor * frag_VertexColor, 1.0);

}
