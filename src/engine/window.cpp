/*
#include "window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

Window::Window(int width, int height, const char title[]):
	width { width }, height { height }, time { 0.0f }, deltaTime { 0.0f } {
	ID = glfwCreateWindow(width, height, title, NULL, NULL);
	if (ID == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
}

Window::~Window() {
	glfwTerminate();
}

void Window::update() {
	float lastFrame = time;
	time = static_cast<float>(glfwGetTime());
	deltaTime = time - lastFrame;
}

void Window::resize(int width, int height) {
	framebufferSizeCallback(ID, width, height);
}


void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
} 
*/
