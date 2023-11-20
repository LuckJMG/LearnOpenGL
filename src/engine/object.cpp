#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.hpp"
#include "shader.hpp"

#include "object.hpp"

Object::Object(Model model, Shader shader): 
	model { model }, shader { shader }, modelMatrix { 1.0f }, 
	position { 0.0f }, rotation { 0.0f } {}

void Object::translate(glm::vec3 position) {
	shader.use();

	modelMatrix = glm::translate(modelMatrix, position);
	shader.set("model", modelMatrix);

	this->position = position;
}

void Object::rotate(glm::vec3 rotation) {
	shader.use();

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3 { 1.0f, 0.0f, 0.0f });
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3 { 0.0f, 1.0f, 0.0f });
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3 { 0.0f, 0.0f, 1.0f });
	shader.set("model", modelMatrix);

	this->rotation = rotation;
}

