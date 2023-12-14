#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
	public:
		Window(GLFWwindow* ID, int width, int height);

		static inline float time { 0.0f };
		static inline float deltaTime { 0.0f };

		static GLFWwindow* getID() { return ID; }
		static int getWidth() { return width; }
		static int getHeight() { return height; }

		static void update();
	
	private:
		static void setID(GLFWwindow* windowID) { ID = windowID; }
		static void setSize(int windowWidth, int windowHeight) {
			width = windowWidth;
			height = windowHeight;
		}

		static inline GLFWwindow* ID { NULL };
		static inline int width { 0 };
		static inline int height { 0 };
};

#endif

