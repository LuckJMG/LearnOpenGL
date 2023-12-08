#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"

class Engine {
	public:
		static Window start(int width, int height, const char* title);
		static void stop() { glfwTerminate(); }
};

#endif
