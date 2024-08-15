#include "Camera.h"
#include "../../system/window/Window.h"
#include <glm/ext.hpp>

Camera::Camera(const glm::vec3& position, const glm::ivec3& position_offset, const glm::vec3& rotation, float fov, float near, float far) :
	Object(position, position_offset, rotation), fov(fov), near(near), far(far)
{ }

Camera::~Camera()
{ }

glm::mat4 Camera::getProjection()
{
	float aspect = (float)Window::getWidth() / (float)Window::getHeight();
	return glm::perspective(glm::radians(fov), aspect, near, far);
}

glm::mat4 Camera::getView()
{
	glm::vec3 pos = (glm::vec3)position_offset + position;
	return glm::lookAt(pos, pos + forward, up);
}

void Camera::move(const glm::vec3& pos_delta)
{
	glm::vec3 pos = glm::vec3(0.0f);
	pos += forward * pos_delta.z;
	pos += right * pos_delta.x;
	pos += up * pos_delta.y;

	Object::move(pos);
}

void Camera::rotate(const glm::vec3& rot_delta)
{
	Object::rotate(rot_delta);
}