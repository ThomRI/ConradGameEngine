#version 150 core
#define MAX_LIGHTS 5
#define GAMMA 0.454545

/* Light types */
#define LIGHT_POINT 0
#define LIGHT_SPOT	1

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
	int type;

	vec3 position;
	vec3 color;
	float intensity;
	float attenuation;

	/* Directional and cone */
	vec3 direction;

	float coneAngle;
} lights[MAX_LIGHTS];


// Outputs
out vec4 out_Color;

vec3 computeLight(Light, vec3);

void main()
{
	vec3 transformed_normal = normalize(mat3(normalMatrix) * frag_Normal);

	/* Lightning */
	vec3 global_light = vec3(0.0);

	/* Ambient */
	vec3 ambient = ambientStrength * ambientColor;
	global_light += ambient;

	/* Light objects (diffuse and specular) */
	for(int i = 0; i < nbrLights; i++) {	
		global_light += computeLight(lights[i], transformed_normal);
	}
		

	/* Final color with gamma correction (pow) */
	out_Color = pow(texture(tex, frag_TexCoord0) * vec4(global_light * frag_VertexColor, 1.0), vec4(GAMMA));

}

vec3 computeLight(Light light, vec3 normal)
{
	vec3 lightDir = light.position - frag_FragmentPos; // Object -> Light
	float distance = length(lightDir); // Getting the distance before normalization
	lightDir = normalize(lightDir);
	// REMINDER : lightDir is only normalized FROM HERE (don't move the 3 line block above) 

	/* Restriction for cone */
	if(light.type == LIGHT_SPOT) {
		float angle = degrees(acos(dot(-lightDir, normalize(light.direction)))); // Angle between light direction and (Light -> Object) vector

		if(angle > light.coneAngle) {
			return vec3(0.0); // No light oustide the cone
		}
	}


	float attenuationFactor = 1.0 / (1.0 + light.attenuation * pow(distance, 2));

	/* Diffuse */
	vec3 diffuse = diffuseStrength * max(0.0, dot(normal, lightDir)) * diffuseColor;

	/* Specular */
	vec3 cameraDir = normalize(cameraPos - frag_FragmentPos); // Object -> Camera
	vec3 reflected_lightDir = reflect(-lightDir, normal);

	vec3 specular = specularStrength * pow(max(0.0, dot(cameraDir, reflected_lightDir)), specularExponent) * specularColor;	

	return attenuationFactor * light.intensity * (diffuse + specular) * light.color;
}
