#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "camera.h"

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

void Camera::setMovementSpeed(double movementSpeed) {
	if (movementSpeed <= 0) {
		std::cerr << "WARNING: Setting camera movement speed below or equal to 0" << std::endl;
		return;
	}

	this->movementSpeed = movementSpeed;
}

void Camera::setMouseSensitivity(double mouseSensitivity) {
	if (mouseSensitivity <= 0) {
		std::cerr << "WARNING: Setting mouse sensitivity below or equal to 0" << std::endl;
		return;
	}

	this->mouseSensitivity = mouseSensitivity;
}

void Camera::setZoom(float zoom) {
	if (zoom < 1.0f) {
		std::cerr << "WARNING: Setting camera zoom below of 1" << std::endl;
		return;
	}
	else if (zoom > 179.0f) {
		std::cerr << "WARNING: Setting camera zoom above of 179" << std::endl;
		return;
	}

	this->zoom = zoom;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	if (direction == CameraMovement::forward)
		position += front * velocity;
	if (direction == CameraMovement::backward)
		position -= front * velocity;
	if (direction == CameraMovement::right)
		position += right * velocity;
	if (direction == CameraMovement::left)
		position -= right * velocity;
}
void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (constrainPitch) {
		if (pitch > 89.0)
			pitch = 89.0;
		else if (pitch < -89.0)
			pitch = -89.0;
	}

	updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {
	zoom -= yOffset;
	if (zoom < 1.0)
		zoom = 1.0;
	else if (zoom > 179.0)
		zoom = 179.0;
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

