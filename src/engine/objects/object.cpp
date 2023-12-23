#include "object.hpp"

#include "../components/shader.hpp"
#include "../components/model.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Object::Object(Model model, Shader shader): 
	model { model }, 
	shader { shader }
	 {}

void Object::draw() { 
	transform.update(shader);
	model.draw(shader); 
}
