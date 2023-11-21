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

	modelMatrix[3] = glm::vec4{ position, 1.0f };
	shader.set("model", modelMatrix);

	this->position = position;
}

void Object::rotate(glm::vec3 rotation) {
	shader.use();

	glm::mat4 xRotation { 1.0f };
	xRotation[1][1] = cos(rotation.x);
	xRotation[1][2] = sin(rotation.x);
	xRotation[2][1] = -sin(rotation.x);
	xRotation[2][2] = cos(rotation.x);

	glm::mat4 yRotation { 1.0f };
	yRotation[0][0] = cos(rotation.y);
	yRotation[0][2] = sin(rotation.y);
	yRotation[2][0] = -sin(rotation.y);
	yRotation[2][2] = cos(rotation.y);

	glm::mat4 zRotation { 1.0f };
	zRotation[0][0] = cos(rotation.z);
	zRotation[0][1] = sin(rotation.z);
	zRotation[1][0] = -sin(rotation.z);
	zRotation[1][1] = cos(rotation.z);

	glm::mat4 rotationMatrix = zRotation * yRotation * xRotation;
	modelMatrix[0] = rotationMatrix[0];
	modelMatrix[1] = rotationMatrix[1];
	modelMatrix[2] = rotationMatrix[2];

	shader.set("model", modelMatrix);

	this->rotation = rotation;
}

