#pragma once
#include "../../object/Object.h"

class Camera : public ObjDCPs, public ObjDRs {
private:
	float fov;
	float near, far;

public:
	Camera(const glm::ivec3& position, const glm::vec3& offset, const glm::vec3& rotation, float fov, float near, float far)
		: ObjDCPs(position, offset), ObjDRs(rotation), fov(fov), near(near), far(far) {}
	~Camera() = default;

	glm::mat4 getProjection() const;
	glm::mat4 getView() const;

	void move(const glm::vec3& position) override;
	void rotate(const glm::vec3& rotation) override;

private:
};