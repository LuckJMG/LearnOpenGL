#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.hpp"
#include "shader.hpp"

#include "object.hpp"

Object::Object(Model model, Shader shader): 
	position { 0.0f }, rotation { 0.0f }, scale { 1.0f }, 
	model { model }, shader { shader } {}

void Object::draw() { 
	shader.use();

	glm::mat4 modelMatrix { 1.0f };
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3 { 1.0f, 0.0f, 0.0f });
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3 { 0.0f, 1.0f, 0.0f });
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3 { 0.0f, 0.0f, 1.0f });
	modelMatrix = glm::scale(modelMatrix, scale);

	shader.set("model", modelMatrix);

	model.draw(shader); 
}
