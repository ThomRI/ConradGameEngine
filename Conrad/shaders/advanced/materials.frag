#version 150 core
#define MAX_LIGHTS 10 // Must by synced with vertex shader!
#define GAMMA 0.454545

/* Light types */
#define LIGHT_POINT 0
#define LIGHT_SPOT	1
#define LIGHT_SUN	2

#define SHADOW_BIAS_MIN 0.005
#define SHADOW_BIAS_MAX 0.01

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

/* Light-related */

uniform int nbrLights;
uniform struct Light {
	int type;

	vec3 position;
	vec3 color;
	float intensity;
	
	float linearAttenuation; // linear (a coeff)
	float quadAttenuation; // quadratic (b coeff)

	float spotExponent;

	/* Directional and cone */
	vec3 direction;
	float coneAngle;

	/* Shadow */
	mat4 world; // Light space matrix
	bool castShadow;
	sampler2D shadowMapTex;
} lights[MAX_LIGHTS];
uniform vec2 shadowMapTexelSize;
in vec4 fragPos_lightspace[MAX_LIGHTS];


// Outputs
out vec4 out_Color;

vec3 computeLight(Light, vec3);
vec3 computeShadow(Light, vec4, vec3);

void main()
{
	vec3 transformed_normal = normalize(mat3(normalMatrix) * frag_Normal);

	/* Lightning */
	vec3 global_light = vec3(0.0);
	vec3 global_shadow = vec3(0.0);

	/* Light objects (diffuse and specular) */
	int nbr_lights_castshadow = 0;
	for(int i = 0; i < nbrLights; i++) {	
		global_light += computeLight(lights[i], transformed_normal);


		if(lights[i].castShadow) {
			global_shadow += computeShadow(lights[i], fragPos_lightspace[i], transformed_normal);
			nbr_lights_castshadow++;
		}
	}

	/* Averaging global_light */
	if(nbrLights != 0) global_light / nbrLights;

	/* Averaging global_shadow (two lamps : one shadow, the other lits => global_shadow = 0.5) */
	if(nbr_lights_castshadow == 0) 	global_shadow = vec3(0.0);
	else							global_shadow /= nbr_lights_castshadow; // average

	// Light-Shadow : total_pixel_intensity = ambient + (1.0 - shadow) * (diffuse + specular)

	/* Shadow */
	global_light *= 1.0 - global_shadow; // light is 1 - shadow..

	/* Ambient */
	vec3 ambient = ambientStrength * ambientColor;
	global_light += ambient;
		

	/* Final color with gamma correction (pow) */
	out_Color = pow(texture(tex, frag_TexCoord0) * vec4(global_light * frag_VertexColor, 1.0), vec4(GAMMA));

}

vec3 computeLight(Light light, vec3 normal)
{
	vec3 lightDir; // Object -> Light !!
	float attenuationFactor;
	if(light.type == LIGHT_SUN) {
		lightDir = -normalize(light.direction);
		attenuationFactor = 1.0;
	} else {
		lightDir = light.position - frag_FragmentPos; // Object -> Light
		float distance = length(lightDir); // Getting the distance before normalization
		lightDir = normalize(lightDir);

		attenuationFactor = 1.0 / (1.0 + light.linearAttenuation * distance + light.quadAttenuation * pow(distance, 2));
		//attenuationFactor = 1.0;
	// REMINDER : lightDir is only normalized FROM HERE (don't move the 3 line block above) 
	}

	/* Restriction for cone */
	if(light.type == LIGHT_SPOT) {
		float dotP = dot(-lightDir, normalize(light.direction));
		attenuationFactor *= pow(dotP, light.spotExponent);

		float angle = degrees(acos(dotP)); // Angle between light direction and (Light -> Object) vector in degrees

		if(angle > light.coneAngle) {
			return vec3(0.0); // No light oustide the cone
		}
	}

	/* Diffuse */
	vec3 diffuse = diffuseStrength * max(0.0, dot(normal, lightDir)) * diffuseColor;
	//diffuse = vec3(0.0);

	/* Specular */
	vec3 cameraDir = normalize(cameraPos - frag_FragmentPos); // Object -> Camera
	vec3 reflected_lightDir = reflect(-lightDir, normal);

	vec3 specular = specularStrength * pow(max(0.0, dot(cameraDir, reflected_lightDir)), specularExponent) * specularColor;	

	//specular = vec3(0.0);

	return attenuationFactor * light.intensity * (diffuse + specular) * light.color;
}

vec3 computeShadow(Light light, vec4 fragpos_light, vec3 normal)
{
	vec3 lightDirScene = normalize(light.position - frag_FragmentPos); // Object -> Light in the scene pov

	/* Restriction for cone */
	/*if(light.type == LIGHT_SPOT) {
		float angle = degrees(acos(dot(-lightDirScene, normalize(light.direction))));

		if(angle > light.coneAngle) {
			return vec3(0.0); // No shadow
		}
	}*/

	// Perspective divide (in case of perspective matrix used for the shadow map generation)
	vec3 projCoords = fragpos_light.xyz / fragpos_light.w; // Now in range [-1; 1]

	// Depth map uses range [0, 1]
	projCoords = projCoords * 0.5 + 0.5; // Now in range [0, 1]
	if(projCoords.z > 1.0) return vec3(0.0); // for points light, allows not to cast shadow everywhere

	// Sample the depth from the shadow map
	float closestDepth = texture(light.shadowMapTex, projCoords.xy).r; // Red or green or blue is whatever (all 3 components are always the same in the shadow map)

	float currentDepth = projCoords.z;

	float bias = max(SHADOW_BIAS_MAX * (1.0 - dot(normal, lightDirScene)), SHADOW_BIAS_MIN);
	float shadow = 0.0;

	/* NO PCF */
	/* 
	float texDepth = texture(light.shadowMapTex, projCoords.xy).r;
	shadow = (currentDepth - bias > texDepth) ? 1.0 : 0.0;
	*/

	/* PCF Interpolation (+ or - 2 texels averaging) */
	vec2 texelSize = 1.0 / textureSize(light.shadowMapTex, 0);
	for(int x = -2; x <= 2; x++) {
		for(int y = -2; y <= 2; y++) {
			float pcfDepth = texture(light.shadowMapTex, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += (currentDepth - bias > pcfDepth) ? 1.0 : 0.0; // Amount of shadow
		}
	} shadow /= 25;

	return vec3(shadow);
}
