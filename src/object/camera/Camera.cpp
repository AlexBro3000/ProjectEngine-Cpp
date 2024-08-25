#include "Camera.h"
#include "../../system/window/Window.h"
#include <glm/ext.hpp>

Camera::Camera(const glm::ivec3& position, const glm::vec3& offset, const glm::vec3& rotation, float fov, float near, float far) :
	AdvancedObject(position, offset, rotation), fov(fov), near(near), far(far)
{ }

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

glm::mat4 Camera::getProjection()
{
	float aspect = (float)Window::getWidth() / (float)Window::getHeight();
	return glm::perspective(glm::radians(fov), aspect, near, far);
}

glm::mat4 Camera::getView()
{
	glm::vec3 pos = offset + (glm::vec3)position;
	return glm::lookAt(pos, pos + forward, up);
}