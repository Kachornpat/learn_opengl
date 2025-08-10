#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

enum Camera_Movement
{
	FORWARE,
	BACKWARD,
	UP,
	DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
	public:
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;

		float Yaw;
		float Pitch;

		float Fov;

		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;


		Camera(unsigned int shaderID);

		glm::mat4 GetViewMatrix();
		void use();
		void ProcessKeyboard(GLFWwindow *window, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constraintPitch = true);
		void ProcessMouseScroll(float yoffset);

	private:
		unsigned int viewLoc;
		unsigned int projectionLoc;
		void updateCameraVectors();
};
#endif