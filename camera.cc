#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "camera.hh"

Camera::Camera(glm::vec3 postion = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
				float yaw = YAW,
				float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
										MovementSpeed(SPEED),
										MouseSensitivity(SENSITIVITY),
										Zoom(ZOOM)
{

}