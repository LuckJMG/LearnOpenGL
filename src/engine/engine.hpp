#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine {
	public:
		static void start(int width, int height, const char* title);
		static void stop() { 
			glfwTerminate(); 
			isRunning = false;
		}

	private:
		static inline bool isRunning { false };
};

#endif
