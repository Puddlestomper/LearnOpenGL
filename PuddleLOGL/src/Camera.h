#pragma once

#include "glm/glm.hpp"

struct GLFWwindow;

class Camera
{
public:
	Camera(float aspectRatio, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraTop);
	Camera(float aspectRatio);

	glm::mat4 GetView() const;
	glm::mat4 GetProjection() const;
	glm::mat4 GetViewProjection() const;

	void OnUpdate(GLFWwindow* window, float dTime);

	void OnMouseScrolled(double xoffset, double yoffset);
	void OnMouseMoved(double xpos, double ypos);
private:
	float aspectRatio;
	glm::vec3 pos; //Positive z is out of the screen
	glm::vec3 front; //Direction camera is looking
	glm::vec3 up;
	float pitch;
	float yaw;
	float fov;
	float cameraSpeed;
};