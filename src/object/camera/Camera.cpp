#include "Camera.h"

#include "../../system/window/Window.h"

glm::mat4 Camera::getProjection() const
{
	float aspect = (float)Window::getWidth() / (float)Window::getHeight();
	return glm::perspective(glm::radians(fov), aspect, near, far);
}

glm::mat4 Camera::getView() const
{
	glm::vec3 position = glm::vec3(0.0f);
	return glm::lookAt(position, position + forward, up);
}

void Camera::move(const glm::vec3& position)
{
	glm::vec3 pos = glm::vec3(0.0f);
	pos += forward * position.z;
	pos += right * position.x;
	pos += up * position.y;

	AdvancedObject::move(pos);
}

void Camera::rotate(const glm::vec3& rotation)
{
	AdvancedObject::rotate(rotation);
}