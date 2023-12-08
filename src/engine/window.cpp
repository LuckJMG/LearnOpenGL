#include "window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

Window::Window(GLFWwindow* ID, int width, int height):
	ID { ID }, width { width }, height { height } {}

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
