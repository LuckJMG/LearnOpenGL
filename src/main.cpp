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
unsigned int loadTexture(char const* path);

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
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetScrollCallback(window, scrollCallback);

	// Check glad
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
	Object sphere { sphereModel, unlitColor };

	DirectionalLight directionalLight {
		glm::vec3 { -0.2f, -1.0f, -0.3f },
		glm::vec3 { 0.2f },
		glm::vec3 { 0.5f },
		glm::vec3 { 1.0f },
	};

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

	glm::vec3 lightColor = glm::vec3 { 1.0f };
	unlitColor.use();
	unlitColor.set("color", lightColor);
	sphere.position = glm::vec3 { -3.0f, 3.0f, -1.0f };
	sphere.scale = glm::vec3 { 0.25f };

	litColor.use();
	litColor.set("directionalLight.direction", directionalLight.direction);
	litColor.set("directionalLight.ambientIntensity", directionalLight.ambientIntensity);
	litColor.set("directionalLight.diffuseIntensity", directionalLight.diffuseIntensity);
	litColor.set("directionalLight.specularIntensity", directionalLight.specularIntensity);

	litColor.set("pointLightsAmount", 1);
	litColor.set("pointLights[0].position", pointLight.position);
	litColor.set("pointLights[0].constant", pointLight.constant);
	litColor.set("pointLights[0].linear", pointLight.linear);
	litColor.set("pointLights[0].quadratic", pointLight.quadratic);
	litColor.set("pointLights[0].ambientIntensity", pointLight.ambientIntensity);
	litColor.set("pointLights[0].diffuseIntensity", pointLight.diffuseIntensity);
	litColor.set("pointLights[0].specularIntensity", pointLight.specularIntensity);

	litColor.set("material.color", color);
	litColor.set("material.shininess", 32.0f);

	while(!glfwWindowShouldClose(window)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		litColor.use();
		litColor.set("view", view);
		litColor.set("projection", projection);
		litColor.set("cameraPosition", camera.position);

		unlitColor.use();
		unlitColor.set("view", view);
		unlitColor.set("projection", projection);

		cube.draw();
		sphere.draw();

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

unsigned int loadTexture(char const* path) {
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format = GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
