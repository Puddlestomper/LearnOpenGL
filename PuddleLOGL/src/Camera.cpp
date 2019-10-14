#include "pudpch.h"
#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float aspectRatio, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraTop)
	: aspectRatio(aspectRatio), pos(cameraPos), front(cameraFront), up(cameraTop), pitch(0.0f), yaw(-90.0f), fov(45.0f), cameraSpeed(2.0f) {}

Camera::Camera(float aspectRatio)
	: aspectRatio(aspectRatio), pos(0.0f, 0.0f, 3.0f), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), pitch(0.0f), yaw(-90.0f), fov(45.0f), cameraSpeed(2.0f) {}

glm::mat4 Camera::GetView() const
{
	return glm::lookAt(pos, pos + front, up);
}

glm::mat4 Camera::GetProjection() const
{
	return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewProjection() const
{
	return GetProjection() * GetView();
}

void Camera::OnUpdate(GLFWwindow* window, float dTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos += cameraSpeed * dTime * front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos -= cameraSpeed * dTime * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed * dTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos += glm::normalize(glm::cross(front, up)) * cameraSpeed * dTime;
}

void Camera::OnMouseScrolled(double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

void Camera::OnMouseMoved(double xpos, double ypos)
{
	static float lastX = 0, lastY = 0;
	static bool started = false;

	if (!started)
	{
		lastX = xpos;
		lastY = ypos;
		started = true;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	while (yaw >= 360.0f) yaw -= 360.0f;
	while (yaw < 0) yaw += 360.0f;

	glm::vec3 tempfront;
	tempfront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	tempfront.y = sin(glm::radians(pitch));
	tempfront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front = glm::normalize(tempfront);
}