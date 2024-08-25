#pragma once
#include "../AdvancedObject.h"

class Camera : public AdvancedObject
{
private:
	float fov;
	float near;
	float far;

public:
	Camera(const glm::ivec3& position, const glm::vec3& offset, const glm::vec3& rotation, float fov, float near, float far);
	~Camera() = default;

	void move(const glm::vec3& position) override;
	void rotate(const glm::vec3& rotation) override;

	glm::mat4 getProjection();
	glm::mat4 getView();

private:

};