#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
	public:
		Window(GLFWwindow* ID, int width, int height);

		float time;
		float deltaTime;

		GLFWwindow* getID() { return ID; }
		int getWidth() { return width; }
		int getHeight() { return height; }
	
		void resize(int width, int height);
		void update();
	
	private:
		GLFWwindow* ID;
		int width;
		int height;

};

#endif

