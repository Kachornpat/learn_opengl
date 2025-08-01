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

		float Yaw;
		float Pitch;
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

		Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

		glm::mat4 GetViewMatrix();
		void ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constraintPitch = true);
		void ProcessMouseScroll(float yoffset);

	private:
		void updateCameraVectors();
};
#endif