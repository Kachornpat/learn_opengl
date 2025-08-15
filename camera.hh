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


		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;
		float Fov;


		Camera();
		glm::mat4 getView() const;
		void updateView(float yoffset, float xoffset);
		void updateFov(float yoffset);

	private:

		float Yaw;
		float Pitch;


		unsigned int viewLoc;
		unsigned int projectionLoc;

};
#endif