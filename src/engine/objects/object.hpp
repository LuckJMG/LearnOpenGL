#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>

#include "../components/shader.hpp"
#include "../components/model.hpp"
#include "../components/transform.hpp"

class Object {
	public:
		Transform transform {};

		Object(Model model, Shader shader);
		void draw();

	private:
		Model model;
		Shader shader;
};

#endif

