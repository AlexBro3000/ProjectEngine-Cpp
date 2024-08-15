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
	~Camera();

	glm::mat4 getProjection();
	glm::mat4 getView();

	void move(const glm::vec3& pos_delta);
	void rotate(const glm::vec3& rot_delta);

private:

};


//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "../../../utils/DefiningTypes.hpp"
//#include "../../../system/window/Window.h"
//
//// Параметры камеры
//const float SPEED       = 1.0f;
//const float SENSITIVITY = 0.1f;
//const float ZOOM        = 80.0f;
//// Параметры проекции
//const float NEAR        = 0.1f;
//const float FAR         = 100.0f;
//
//