#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "objects/camera.hpp"

class Window {
	public:
		Window(GLFWwindow* ID, int width, int height);

		static inline Camera* currentCamera { NULL };

		static inline float time { 0.0f };
		static inline float deltaTime { 0.0f };

		static GLFWwindow* getID() { return ID; }
		static int getWidth() { return width; }
		static int getHeight() { return height; }
		static float getAspectRatio() {
			return static_cast<float>(width) / height;
		}
		static glm::mat4 getViewMatrix() { return view; }
		static glm::mat4 getProjectionMatrix() { return projection; }

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

		static inline glm::mat4 view { 1.0f };
		static inline glm::mat4 projection { 1.0f };
};

#endif

