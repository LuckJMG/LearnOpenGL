#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/engine.hpp"
#include "engine/window.hpp"
#include "engine/input.hpp"
#include "engine/utils/debug.hpp"

#include "engine/components/shader.hpp"
#include "engine/components/model.hpp"

#include "engine/objects/camera.hpp"
#include "engine/objects/lightSource.h"
#include "engine/objects/object.hpp"

void processInput();

int main() {
	Engine::start(800, 600, "LearnOpenGL");
	Camera camera { glm::vec3 { 0.0f, 0.0f, 3.0f } };
	Window::currentCamera = &camera;

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
	torch.transform.position = glm::vec3 { -3.0f, 3.0f, -1.0f };
	torch.transform.scale = glm::vec3 { 0.25f };

	litColor.set("pointLightsAmount", 1);
	litColor.set("pointLights[0].constant", pointLight.constant);
	litColor.set("pointLights[0].linear", pointLight.linear);
	litColor.set("pointLights[0].quadratic", pointLight.quadratic);
	litColor.set("pointLights[0].ambientIntensity", pointLight.ambientIntensity);
	litColor.set("pointLights[0].diffuseIntensity", pointLight.diffuseIntensity);
	litColor.set("pointLights[0].specularIntensity", pointLight.specularIntensity);

	sphere.transform.position = glm::vec3 { 0.0f, 2.0f, -5.0f };

	while(Engine::isRunning()) {
		Window::update();

		processInput();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = Window::getViewMatrix();
		glm::mat4 projection = Window::getProjectionMatrix();
		torch.transform.position.z += sin(Window::time);

		litColor.set("view", view);
		litColor.set("projection", projection);
		litColor.set("cameraPosition", camera.position);
		litColor.set("pointLights[0].position", torch.transform.position);

		unlitColor.set("view", view);
		unlitColor.set("projection", projection);

		litColor.set("material.color", color);
		litColor.set("material.shininess", 32.0f);
		cube.draw();

		litColor.set("material.color", color2);
		litColor.set("material.shininess", 256.0f);
		sphere.draw();

		torch.transform.position.z = -1.0f + sin(Window::time);
		torch.draw();
	}

	Engine::stop();
	return 0;
}

void processInput() {
	Camera& camera = *Window::currentCamera;

	if(Input::onKeyPress(Key::escape))
		glfwSetWindowShouldClose(Window::getID(), true);

	if (Input::onKeyPress(Key::W))
		camera.processKeyboard(CameraMovement::forward);
	if (Input::onKeyPress(Key::S))
		camera.processKeyboard(CameraMovement::backward);
	if (Input::onKeyPress(Key::D))
		camera.processKeyboard(CameraMovement::right);
	if (Input::onKeyPress(Key::A))
		camera.processKeyboard(CameraMovement::left);
	if (Input::onKeyPress(Key::E))
		camera.processKeyboard(CameraMovement::up);
	if (Input::onKeyPress(Key::Q))
		camera.processKeyboard(CameraMovement::down);

	if (Input::onKeyPress(Key::rightArrow))
		camera.processArrows(CameraMovement::right);
	if (Input::onKeyPress(Key::leftArrow))
		camera.processArrows(CameraMovement::left);
	if (Input::onKeyPress(Key::upArrow))
		camera.processArrows(CameraMovement::up);
	if (Input::onKeyPress(Key::downArrow))
		camera.processArrows(CameraMovement::down);
}

