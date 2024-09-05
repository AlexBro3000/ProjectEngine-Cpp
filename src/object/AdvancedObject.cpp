#include "AdvancedObject.h"

AdvancedObject::AdvancedObject(const glm::ivec3& position, const glm::vec3& offset, const glm::vec3& rotation)
	: position(position), offset(offset), rotation(rotation)
{
	AdvancedObject::updatePosition();
	AdvancedObject::updateRotation();
}

glm::ivec3 AdvancedObject::getPosition() const
{
	return position;
}

glm::vec3 AdvancedObject::getOffset() const
{
	return offset;
}

glm::vec3 AdvancedObject::getRotation() const
{
	return rotation;
}

glm::vec3 AdvancedObject::getForward() const
{
	return forward;
}

glm::vec3 AdvancedObject::getRight() const
{
	return right;
}

glm::vec3 AdvancedObject::getUp() const
{
	return up;
}

void AdvancedObject::setPosition(const glm::ivec3& position)
{
	AdvancedObject::position = position;
	AdvancedObject::updatePosition();
}

void AdvancedObject::setOffset(const glm::vec3& offset)
{
	AdvancedObject::offset = offset;
	AdvancedObject::updatePosition();
}

void AdvancedObject::setRotation(const glm::vec3& rotation)
{
	AdvancedObject::rotation = rotation;
	AdvancedObject::updateRotation();
}

void AdvancedObject::move(const glm::vec3& position)
{
	AdvancedObject::offset += position;
	AdvancedObject::updatePosition();
}

void AdvancedObject::rotate(const glm::vec3& rotation)
{
	AdvancedObject::rotation += rotation;
	AdvancedObject::updateRotation();
}

void AdvancedObject::updatePosition()
{
    for (int i = 0; i < 3; i++) {
        if (offset[i] >= 1.0f) {
            int delta = static_cast<int>(offset[i]);
            position[i] += delta;
			offset[i] -= delta;
        }
        else if (offset[i] < 0.0f) {
            int delta = static_cast<int>(-offset[i]) + 1;
            position[i] -= delta;
			offset[i] += delta;
        }
    }
}

void AdvancedObject::updateRotation()
{
    for (int i = 0; i < 3; i++) {
        rotation[i] = glm::mod(rotation[i], 360.0f);
    }

    glm::quat quat = glm::quat(glm::radians(rotation));
    forward = glm::normalize(glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)));
    right = glm::normalize(glm::rotate(quat, glm::vec3(1.0f, 0.0f, 0.0f)));
    up = glm::normalize(glm::rotate(quat, glm::vec3(0.0f, 1.0f, 0.0f)));
}