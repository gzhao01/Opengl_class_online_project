#pragma once

#define GLEW_SATTIC
#include "GL/glew.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW		= -90.0f;//Æ«º½
const GLfloat PITCH		= 0.0f;//¸©Ñö½Ç
const GLfloat ZOOM		= 45.0f;
const GLfloat CAMERA_MOVEMENT_SPEED	    = 6.0f;//control the camera's moving speed

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		   GLfloat yaw = YAW, 
		   GLfloat pitch = PITCH)
		   :front(glm::vec3(0.0f,0.0f, -1.0f)), 
		   zoom(ZOOM),
		   cameraMovementSpeed(CAMERA_MOVEMENT_SPEED)
{
			this->position = position;
			this->worldUp = up;
			this->yaw = yaw;
			this->pitch = pitch;
			updateViewVectors();
}
	glm::mat4 getViewMatrix() {
		return glm::lookAt(this->position,this->position+this->front,this->up);
	}
	GLfloat GetZoom() {
		return this->zoom;
	}
	void updateViewVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(this->pitch))*cos(glm::radians(this->yaw));
		front.y = sin(glm::radians(this->pitch));
		front.z = cos(glm::radians(this->pitch))*sin(glm::radians(this->yaw));

		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front,this->worldUp));
		this->up = glm::normalize(glm::cross(this->right,this->front));
	}
	void processKeyboard(Camera_Movement direction, GLfloat deltaTime) {
		GLfloat velocity = this->cameraMovementSpeed * deltaTime;
		if (direction == FORWARD) {
			this->position += this->front * velocity;
		}
		if (direction == BACKWARD) {
			this->position -= this->front * velocity;
		}
		if (direction == LEFT) {
			this->position -= this->right * velocity;
		}
		if (direction == RIGHT) {
			this->position += this->right * velocity;
		}
	}
	glm::vec3 GetPosition() {
		return this->position;
	}
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;
	GLfloat zoom;
	GLfloat cameraMovementSpeed;
};



//GLfloat Camera::GetZoom() {
//	return this->zoom;
//}
//
//
//glm::mat4 Camera::getViewMatrix() {
//
//}
//
//void Camera::updateViewMatrix() {
//
//}