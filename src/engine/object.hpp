#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>

#include "shader.hpp"
#include "model.hpp"

class Object {
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Object(Model model, Shader shader);
		void draw();

	private:
		Model model;
		Shader shader;
};

#endif

