#include "window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "objects/camera.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

Window::Window(GLFWwindow* ID, int width, int height) {
	if (Window::getID()) {
		std::cerr << "There is an attempt to create a second window instance" << std::endl;
		exit(-1);
	}

	glfwSetFramebufferSizeCallback(ID, framebufferSizeCallback);

	setID(ID);
	setSize(width, height);
}

void Window::update() {
	glfwSwapBuffers(ID);
	glfwPollEvents();

	float lastFrame = time;
	time = static_cast<float>(glfwGetTime());
	deltaTime = time - lastFrame;

	view = currentCamera->getViewMatrix();
	projection = currentCamera->getProjectionMatrix();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

