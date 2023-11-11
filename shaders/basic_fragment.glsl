#version 330 core

struct LightSource {
	vec3 position;
	vec3 direction;
	float innerCutOffAngle;
	float outerCutOffAngle;

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
uniform LightSource lightSource;

out vec4 outColor;

void main() {
	vec3 ambientLight = lightSource.ambientIntensity * texture(material.diffuseMap, textureCoordinates).rgb;

	vec3 lightDirection = normalize(lightSource.position - fragmentPosition);
	float theta = dot(lightDirection, normalize(-lightSource.direction));
	float epsilon = lightSource.innerCutOffAngle - lightSource.outerCutOffAngle;
	float intensity = clamp((theta - lightSource.outerCutOffAngle) / epsilon, 0.0, 1.0);
	
	vec3 norm = normalize(normal);
	float diffuse = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuseLight = lightSource.diffuseIntensity * diffuse * texture(material.diffuseMap, textureCoordinates).rgb;

	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
	vec3 specularLight = lightSource.specularIntensity * specular * texture(material.specularMap, textureCoordinates).rgb;

	vec3 result = ambientLight + intensity * (diffuseLight + specularLight);
	outColor = vec4(result, 1.0f);
}

