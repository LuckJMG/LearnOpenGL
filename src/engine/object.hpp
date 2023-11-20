#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>

#include "shader.hpp"
#include "model.hpp"

class Object {
	public:
		Object(Model model, Shader shader);

		glm::vec3 getPosition() { return this->position; }
		glm::vec3 getRotation() { return this->rotation; }

		void draw() { this->model.draw(this->shader); }
		void translate(glm::vec3 position);
		void rotate(glm::vec3 rotation);

	private:
		Model model;
		Shader shader;

		glm::mat4 modelMatrix;
		glm::vec3 position;
		glm::vec3 rotation;
};

#endif

