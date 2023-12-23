#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>

#include "shader.hpp"

class Transform {
	public:
		glm::vec3 position { 0.0f };
		glm::vec3 rotation { 0.0f };
		glm::vec3 scale { 1.0f };

		void update(Shader& shader);
};

#endif
