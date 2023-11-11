#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <glm/glm.hpp>

struct DirectionalLight {
	glm::vec3 direction {};
	glm::vec3 color { 0.0f };

	glm::vec3 ambientIntensity {};
	glm::vec3 diffuseIntensity {};
	glm::vec3 specularIntensity {};
};

struct PointLight {
	glm::vec3 position {};
	glm::vec3 color { 0.0f };

	glm::vec3 ambientIntensity {};
	glm::vec3 diffuseIntensity {};
	glm::vec3 specularIntensity {};

	float constant { 1.0f };
	float linear {};
	float quadratic {};
};

struct Spotlight {
	glm::vec3 position {};
	glm::vec3 direction {};
	float innerCutOffAngle { 45.0f };
	float outerCutOffAngle {};
	glm::vec3 color { 0.0f };

	glm::vec3 ambientIntensity {};
	glm::vec3 diffuseIntensity {};
	glm::vec3 specularIntensity {};
};

#endif

