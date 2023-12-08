#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
	public:
		Window(int width, int height, const char title[]);
		~Window();

		GLFWwindow* ID;
		GLFWwindow* getID() { return ID; }
		int getWidth() { return width; }
		int getHeight() { return height; }
		float getDeltaTime() { return deltaTime; }
		float getTime() { return time; }
	
		void resize(int width, int height);
		void update();
	
	private:
		int width;
		int height;

		float time;
		float deltaTime;
};

#endif

