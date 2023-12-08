#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/engine.c"
#include "engine/engine.hpp"
#include "engine/window.hpp"
#include "engine/utils/debug.hpp"

#include "engine/components/shader.hpp"
#include "engine/components/model.hpp"

#include "engine/objects/camera.hpp"
#include "engine/objects/lightSource.h"
#include "engine/objects/object.hpp"

void processInput(GLFWwindow* window, float deltaTime);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main() {
	Window window = Engine::start(800, 600, "LearnOpenGL");

	Shader unlitColor { "src/shaders/model.vert", "src/shaders/unlitColor.frag" };
	Shader litColor { "src/shaders/model.vert", "src/shaders/litColor.frag" };
	Model cubeModel { "src/models/cube.obj" };
	Model sphereModel { "src/models/sphere.obj" };

	Object cube { cubeModel, litColor };
	Object sphere { sphereModel, litColor };
	Object torch { sphereModel, unlitColor };

	PointLight pointLight {
		glm::vec3 { -3.0f, 3.0f, -1.0f },
		1.0f,
		0.09f,
		0.032f,
		glm::vec3 { 0.2f },
		glm::vec3 { 0.5f },
		glm::vec3 { 1.0f }
	};

	glm::vec3 color = glm::vec3 { 1.0f, 0.0f, 0.0f };
	glm::vec3 color2 = glm::vec3 { 0.0f, 1.0f, 0.0f };

	glm::vec3 lightColor = glm::vec3 { 1.0f };
	unlitColor.set("color", lightColor);
	torch.position = glm::vec3 { -3.0f, 3.0f, -1.0f };
	torch.scale = glm::vec3 { 0.25f };

	litColor.set("pointLightsAmount", 1);
	litColor.set("pointLights[0].constant", pointLight.constant);
	litColor.set("pointLights[0].linear", pointLight.linear);
	litColor.set("pointLights[0].quadratic", pointLight.quadratic);
	litColor.set("pointLights[0].ambientIntensity", pointLight.ambientIntensity);
	litColor.set("pointLights[0].diffuseIntensity", pointLight.diffuseIntensity);
	litColor.set("pointLights[0].specularIntensity", pointLight.specularIntensity);

	sphere.position = glm::vec3 { 0.0f, 2.0f, -5.0f };

	while(!glfwWindowShouldClose(window.getID())) {
		processInput(window.getID(), window.deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), static_cast<float>(window.getWidth()) / window.getHeight(), 0.1f, 100.0f);
		torch.position.z += sin(window.deltaTime);

		litColor.set("view", view);
		litColor.set("projection", projection);
		litColor.set("cameraPosition", camera.position);
		litColor.set("pointLights[0].position", torch.position);

		unlitColor.set("view", view);
		unlitColor.set("projection", projection);

		litColor.set("material.color", color);
		litColor.set("material.shininess", 32.0f);
		cube.draw();

		litColor.set("material.color", color2);
		litColor.set("material.shininess", 256.0f);
		sphere.draw();

		torch.position.z = -1.0f + sin(window.time);
		torch.draw();

		window.update();
	}

	Engine::stop();
	return 0;
}

void processInput(GLFWwindow* window, float deltaTime) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.processKeyboard(CameraMovement::forward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processKeyboard(CameraMovement::backward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processKeyboard(CameraMovement::right, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processKeyboard(CameraMovement::left, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.processKeyboard(CameraMovement::up, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.processKeyboard(CameraMovement::down, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.processArrows(CameraMovement::right, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.processArrows(CameraMovement::left, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.processArrows(CameraMovement::up, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.processArrows(CameraMovement::down, deltaTime);
}

