#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"

class Engine {
	public:
		static void start(int width, int height, const char* title);
		static bool isRunning() { return !glfwWindowShouldClose(Window::getID()); }
		static void stop() { 
			glfwTerminate(); 
			running = false;
		}

	private:
		static inline bool running { false };
};

#endif
