#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>

enum class CameraMovement {
	forward,
	backward,
	left,
	right,
	up,
	down,
};

class Camera {
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	float yaw;
	float pitch;

	float nearPlane;
	float farPlane;

	Camera(
		glm::vec3 position = glm::vec3(0.0f), 
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
		float yaw = -90.0f,  
		float pitch = 0.0f
	)
	: position { position }, worldUp { up }, yaw { yaw }, pitch { pitch }, 
		nearPlane { 0.1f }, farPlane { 100.0f }, movementSpeed { 1.0f }, 
		rotationSpeed { 100.0f }, zoom { 45.0f } {
		updateCameraVectors();
	};

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void setMovementSpeed(double movementSpeed);
	void setRotationSpeed(double rotationSpeed);
	float getZoom() { return zoom; };
	void setZoom(float zoom);

	void processKeyboard(CameraMovement direction);
	void processArrows(CameraMovement direction, bool constrainPitch = true);
	void processMouseScroll(float yOffset);

private:
	float movementSpeed;
	float rotationSpeed;
	float zoom;
	void updateCameraVectors();
};

#endif
