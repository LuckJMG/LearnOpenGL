#include "transform.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"

void Transform::update(Shader& shader) {
	glm::mat4 modelMatrix { 1.0f };
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3 { 1.0f, 0.0f, 0.0f });
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3 { 0.0f, 1.0f, 0.0f });
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3 { 0.0f, 0.0f, 1.0f });
	modelMatrix = glm::scale(modelMatrix, scale);

	shader.set("model", modelMatrix);
}

