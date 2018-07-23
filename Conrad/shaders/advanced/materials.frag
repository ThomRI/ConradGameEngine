#version 150 core
#define MAX_LIGHTS 10
#define GAMMA 0.454545

// Inputs
in vec3 frag_VertexColor;
in vec2 frag_TexCoord0;
in vec3 frag_FragmentPos;
in vec3 frag_Normal;


// Uniforms
uniform sampler2D tex;
uniform mat4 normalMatrix; // Transformations for the normals (same for every pixels so calculated by the CPU)
uniform vec3 cameraPos;

/* Mesh-related uniforms (material) */
uniform float ambientStrength; 
uniform vec3 ambientColor;

uniform float diffuseStrength;
uniform vec3 diffuseColor;

uniform float specularStrength;
uniform vec3 specularColor;

uniform float specularExponent; // [0; 100]
// uniform vec3 emitColor; // emitting is not supported yet.

/* Light-related uniforms */

uniform int nbrLights;
uniform struct Light {
	vec3 position;
	vec3 color;
	float intensity;
	float attenuation;
} lights[MAX_LIGHTS];


// Outputs
out vec4 out_Color;

vec3 computeLight(float, float, vec3, vec3, vec3);

void main()
{
	vec3 transformed_normal = normalize(mat3(normalMatrix) * frag_Normal);

	/* Lightning */
	vec3 global_light = vec3(0.0, 0.0, 0.0);

	/* Ambient */
	vec3 ambient = ambientStrength * ambientColor;

	/* Light objects (diffuse and specular) */
	for(int i = 0; i < nbrLights; i++) {
		vec3 lightDir = normalize(lights[i].position - frag_FragmentPos); // Object -> Light	
		global_light += computeLight(lights[i].intensity, lights[i].attenuation, lights[i].color, lights[i].position, transformed_normal);
	}
	global_light += ambient;
	

	/* Final color with gamma correction (pow) */
	out_Color = pow(texture(tex, frag_TexCoord0) * vec4(global_light * frag_VertexColor, 1.0), vec4(GAMMA));

}

vec3 computeLight(float intensity, float attenuation, vec3 lightColor, vec3 lightPos, vec3 normal)
{
	vec3 lightDir = lightPos - frag_FragmentPos; // Object -> Light
	float distance = length(lightDir); // Getting the distance before normalization
	lightDir = normalize(lightDir);

	float attenuationFactor = 1.0 / (1.0 + attenuation * pow(distance, 2));

	/* Diffuse */
	vec3 diffuse = diffuseStrength * max(0.0, dot(normal, lightDir)) * diffuseColor;

	/* Specular */
	vec3 cameraDir = normalize(cameraPos - frag_FragmentPos); // Object -> Camera
	vec3 reflected_lightDir = reflect(-lightDir, normal);

	vec3 specular = specularStrength * pow(max(0.0, dot(cameraDir, reflected_lightDir)), specularExponent) * specularColor;	

	return attenuationFactor * intensity * (diffuse + specular) * lightColor;
}
