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

    viewLoc = glGetUniformLocation(shaderID, "view");
    projectionLoc = glGetUniformLocation(shaderID, "projection");

	Camera::use();
}

void Camera::use(){
	glm::mat4 view = glm::lookAt(Position, Position + Front, Up);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(Fov), 800.0f / 600.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera::ProcessKeyboard(GLFWwindow *window, float deltaTime){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 1.5f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += cameraSpeed * Front;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= cameraSpeed * Front;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
}

