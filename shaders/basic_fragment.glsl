#version 330 core

in vec3 normal;
in vec3 fragmentPosition;
in vec3 lightPosition;

uniform vec3 viewPosition;
uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 outColor;

void main() {
	float ambientStrength = 0.1f;
	vec3 ambientLight = lightColor * ambientStrength;

	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(lightPosition - fragmentPosition);
	float reflection = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuseLight = lightColor * reflection;

	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(-fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
	vec3 specularLight = specular * lightColor * specularStrength;

	vec3 result = (ambientLight + diffuseLight + specularLight) * objectColor;
	outColor = vec4(result, 1.0f);
}

