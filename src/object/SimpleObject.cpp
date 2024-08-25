#include "SimpleObject.h"

SimpleObject::SimpleObject(const glm::ivec3& position, const glm::vec3& offset) :
	position(position), offset(offset)
{
	SimpleObject::updatePosition();
}

void SimpleObject::move(const glm::vec3& position)
{
    SimpleObject::offset += position;
    SimpleObject::updatePosition();
}

glm::ivec3 SimpleObject::getPosition() const
{
	return position;
}

glm::vec3 SimpleObject::getOffset() const
{
	return offset;
}

void SimpleObject::setPosition(const glm::ivec3& position)
{
	SimpleObject::position = position;
	SimpleObject::updatePosition();
}

void SimpleObject::setOffset(const glm::vec3& offset)
{
	SimpleObject::offset = offset;
	SimpleObject::updatePosition();
}

void SimpleObject::updatePosition()
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