#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

Window::Window(GLFWwindow* ID, int width, int height):
	ID { ID }, width { width }, height { height } {
	glfwSetFramebufferSizeCallback(ID, framebufferSizeCallback);
}

void Window::update() {
	float lastFrame = time;
	time = static_cast<float>(glfwGetTime());
	deltaTime = time - lastFrame;

	glfwSwapBuffers(ID);
	glfwPollEvents();
}


void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

