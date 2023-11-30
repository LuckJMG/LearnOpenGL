#version 330 core

#define MAX_LIGHTS 128

struct DirectionalLight {
	vec3 direction;

	vec3 ambientIntensity;
	vec3 diffuseIntensity;
	vec3 specularIntensity;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambientIntensity;
	vec3 diffuseIntensity;
	vec3 specularIntensity;
};

struct Spotlight {
	vec3 position;
	vec3 direction;

	float innerCutOffAngle;
	float outerCutOffAngle;

	float constant;
	float linear;
	float quadratic;

	vec3 ambientIntensity;
	vec3 diffuseIntensity;
	vec3 specularIntensity;
};

struct Material {
	sampler2D diffuseMap;
	sampler2D specularMap;
	float shininess;
};

in vec2 textureCoordinates;
in vec3 normal;
in vec3 fragmentPosition;

uniform vec3 cameraPosition;
uniform Material material;

uniform DirectionalLight directionalLight = DirectionalLight(
	vec3(0.0f),
	vec3(0.0f),
	vec3(0.0f),
	vec3(0.0f)
);

uniform int pointLightsAmount = 0;
uniform PointLight pointLights[MAX_LIGHTS];

uniform int spotlightsAmount = 0;
uniform Spotlight spotlights[MAX_LIGHTS];

out vec4 outColor;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDirection);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection);
vec3 calculateSpotlight(Spotlight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection);

void main() {
	vec3 norm = normalize(normal);
	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);

	vec3 result = calculateDirectionalLight(directionalLight, norm, viewDirection);

	for (int i = 0; i < pointLightsAmount; i++) {
		result += calculatePointLight(pointLights[i], norm, fragmentPosition, viewDirection);
	}

	for (int i = 0; i < spotlightsAmount; i++) {
		result += calculateSpotlight(spotlights[i], normal, fragmentPosition, viewDirection);
	}

	outColor = vec4(result, 1.0f);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDirection) {
	vec3 ambientLight = light.ambientIntensity * vec3(texture(material.diffuseMap, textureCoordinates));

	vec3 lightDirection = normalize(-light.direction);
	float diffuseIntensity = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuseLight = light.diffuseIntensity * diffuseIntensity * vec3(texture(material.diffuseMap, textureCoordinates));

	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularIntensity = pow(max(dot(cameraDirection, reflectDirection), 0.0f), material.shininess);
	vec3 specularLight = light.specularIntensity * specularIntensity * vec3(texture(material.specularMap, textureCoordinates));
	
	return ambientLight + diffuseLight + specularLight;
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection) {
	vec3 ambientLight = light.ambientIntensity * vec3(texture(material.diffuseMap, textureCoordinates));

	vec3 lightDirection = normalize(light.position - fragmentPosition);
	float diffuseIntensity = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuseLight = light.diffuseIntensity * diffuseIntensity * vec3(texture(material.diffuseMap, textureCoordinates));

	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularIntensity = pow(max(dot(cameraDirection, reflectDirection), 0.0f), material.shininess);
	vec3 specularLight = light.specularIntensity * specularIntensity * vec3(texture(material.specularMap, textureCoordinates));

	float distance = length(fragmentPosition - light.position);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

	return attenuation * (ambientLight + diffuseLight + specularLight);
}

vec3 calculateSpotlight(Spotlight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection) {
	vec3 ambientLight = light.ambientIntensity * vec3(texture(material.diffuseMap, textureCoordinates));

	vec3 lightDirection = normalize(light.position - fragmentPosition);
	float diffuseIntensity = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuseLight = light.diffuseIntensity * diffuseIntensity * vec3(texture(material.diffuseMap, textureCoordinates));

	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularIntensity = pow(max(dot(cameraDirection, reflectDirection), 0.0), material.shininess);
	vec3 specularLight = light.specularIntensity * specularIntensity * vec3(texture(material.specularMap, textureCoordinates));

	float distance = length(light.position - fragmentPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.innerCutOffAngle - light.outerCutOffAngle;
	float intensity = clamp((theta - light.outerCutOffAngle) / epsilon, 0.0f, 1.0f);

	return intensity * attenuation * (ambientLight + diffuseLight + specularLight);
}

