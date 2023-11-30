#include <iostream>
#include <cmath>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/shader.hpp"
#include "engine/camera.hpp"
#include "engine/lightSource.h"
#include "engine/model.hpp"
#include "engine/object.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);  
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime { 0.0f };
float lastFrame { 0.0f };

std::ostream& operator<< (std::ostream& out, const glm::vec3& vector) {
	out << "(" << vector.x << ", " << vector.y << ", " << vector.z << ')';
	return out;
}

unsigned int SCREEN_WIDTH = 800;
unsigned int SCREEN_HEIGHT = 600;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetScrollCallback(window, scrollCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEPTH_TEST);

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

	while(!glfwWindowShouldClose(window)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		torch.position.z += sin(deltaTime);

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

		torch.position.z = -1.0f + sin(currentFrame);
		torch.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
} 

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.processMouseScroll(yOffset);
}

void processInput(GLFWwindow* window) {
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

