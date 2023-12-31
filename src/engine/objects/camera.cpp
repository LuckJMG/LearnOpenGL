#include "camera.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../window.hpp"

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() {
	float fov = glm::radians(zoom);
	return glm::perspective(fov, Window::getAspectRatio(), nearPlane, farPlane);
}

void Camera::setMovementSpeed(double movementSpeed) {
	if (movementSpeed <= 0) {
		std::cerr << "WARNING: Setting camera movement speed below or equal to 0" << std::endl;
		return;
	}

	this->movementSpeed = movementSpeed;
}

void Camera::setRotationSpeed(double rotationSpeed) {
	if (rotationSpeed <= 0) {
		std::cerr << "WARNING: Setting mouse sensitivity below or equal to 0" << std::endl;
		return;
	}

	this->rotationSpeed = rotationSpeed;
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

void Camera::processKeyboard(CameraMovement direction) {
	float velocity = movementSpeed * Window::deltaTime;
	if (direction == CameraMovement::forward)
		position += front * velocity;
	if (direction == CameraMovement::backward)
		position -= front * velocity;
	if (direction == CameraMovement::right)
		position += right * velocity;
	if (direction == CameraMovement::left)
		position -= right * velocity;
	if (direction == CameraMovement::up)
		position += up * velocity;
	if (direction == CameraMovement::down)
		position -= up * velocity;
}
void Camera::processArrows(CameraMovement direction, bool constrainPitch) {
	float velocity = rotationSpeed * Window::deltaTime;

	if (direction == CameraMovement::left)
		yaw -= velocity;
	if (direction == CameraMovement::right)
		yaw += velocity;
	if (direction == CameraMovement::up)
		pitch += velocity;
	if (direction == CameraMovement::down)
		pitch -= velocity;

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

