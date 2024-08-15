#include "Object.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Object::Object(const glm::vec3& position, const glm::ivec3& position_offset, const glm::vec3& rotation) :
	position(position), position_offset(position_offset), rotation(rotation)
{
	updatePosition();
	updateRotation();
}

void Object::setPosition(const glm::vec3& pos, const glm::ivec3& pos_offset)
{
	position = pos;
	position_offset = pos_offset;
	updatePosition();
}

void Object::setRotation(const glm::vec3& rot)
{
	rotation = rot;
	updateRotation();
}

glm::vec3 Object::getPosition() const
{
	return position;
}

glm::ivec3 Object::getPositionOffset() const
{
	return position_offset;
}

glm::vec3 Object::getRotation() const
{
	return rotation;
}

glm::vec3 Object::getForward() const
{
	return forward;
}

glm::vec3 Object::getRight() const
{
	return right;
}

glm::vec3 Object::getUp() const
{
	return up;
}

void Object::move(const glm::vec3& pos_delta)
{
    position += pos_delta;
    updatePosition();
}

void Object::rotate(const glm::vec3& rot_delta)
{
    rotation += rot_delta;
    updateRotation();
}

void Object::updatePosition()
{
    for (int i = 0; i < 3; i++) {
        if (position[i] >= 1.0f) {
            int offset = static_cast<int>(position[i]);
            position_offset[i] += offset;
            position[i] -= offset;
        }
        else if (position[i] < 0.0f) {
            int offset = static_cast<int>(-position[i]) + 1;
            position_offset[i] -= offset;
            position[i] += offset;
        }
    }
}

void Object::updateRotation()
{
    for (int i = 0; i < 3; i++) {
        rotation[i] = glm::mod(rotation[i], 360.0f);
    }

    glm::quat quat = glm::quat(glm::radians(rotation));
    forward = glm::normalize(glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)));
    right = glm::normalize(glm::rotate(quat, glm::vec3(1.0f, 0.0f, 0.0f)));
    up = glm::normalize(glm::rotate(quat, glm::vec3(0.0f, 1.0f, 0.0f)));
}