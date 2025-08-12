#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hh"



Camera::Camera(unsigned int shaderID) : 
	Position(glm::vec3(0.0f, 0.0f, 3.0f)),
	Up(glm::vec3(0.0f, 1.0f, 0.0f)),
	Yaw(YAW),
	Pitch(PITCH),
	Front(glm::vec3(0.0f, 0.0f, -1.0f)),						
	MovementSpeed(SPEED),
	MouseSensitivity(SENSITIVITY),
	Zoom(ZOOM),
	Fov(45.0f)
{

	this->shaderID = shaderID;

}

void Camera::use() {

	viewLoc = glGetUniformLocation(shaderID, "view");
	projectionLoc = glGetUniformLocation(shaderID, "projection");

	glm::mat4 view = glm::lookAt(Position, Position + Front, Up);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(Fov), 800.0f / 600.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera::updateView(float yoffset, float xoffset) {
	Pitch -= yoffset;
	Yaw += xoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(direction);
}

void Camera::updateFov(float yoffset) {
	Fov -= yoffset;
	if (Fov < 1.0f)
		Fov = 1.0f;
	if (Fov > 45.0f)
		Fov = 45.0f;
}



