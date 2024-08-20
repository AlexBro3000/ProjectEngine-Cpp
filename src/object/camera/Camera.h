#pragma once
#include "../Object.h"

class Camera : public Object
{
private:
	float fov;
	float near;
	float far;

public:
	Camera(const glm::vec3& position, const glm::ivec3& position_offset, const glm::vec3& rotation, float fov, float near, float far);
	~Camera() = default;

	glm::mat4 getProjection();
	glm::mat4 getView();

	void move(const glm::vec3& position);
	void rotate(const glm::vec3& rotation);

private:
};